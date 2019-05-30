/*!
 * @brief	�f�B�U�����O�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDithering.h"
#include "tkEngine/graphics/tkPresetRenderState.h"


namespace tkEngine{
	namespace {
		const float ATTN = 0.4f;
	}
	CDithering::CDithering()
	{
	}
	CDithering::~CDithering()
	{
	}
	void CDithering::Release()
	{
	}
	void CDithering::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.ditheringConfig.isEnable;
		m_vsShader.Load("shader/dithering.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("shader/dithering.fx", "PSMain", CShader::EnType::PS);
		//�T���v�����쐬�B
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);

		m_cbGPU.Create(nullptr, sizeof(SCb));
		{
			//�|�C���g���C�g�p�̃X�g���N�`���o�b�t�@�̍쐬�B
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
			desc.ByteWidth = sizeof(SPointLig) * m_pointLigList.size();
			desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			desc.StructureByteStride = sizeof(SPointLig);
			m_pointLigListSB.Create(m_pointLigList.data(), desc);
		}
	}
	void CDithering::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		if (m_fadeOutEndTime > 0.0f) {
			//�t�F�[�h�A�E�g���w�肳��Ă���B
			//�|�C���g���C�g�̌��ʂ������Âキ����B
			m_fadeOutTimer += GameTime().GetFrameDeltaTime();
			if (m_fadeOutTimer > m_fadeOutEndTime) {
				//�������������
				m_fadeOutEndTime = 0.0f;
				numPointLig = 0;
			}
			else {
				float t = 1.0f - (m_fadeOutTimer / m_fadeOutEndTime);
				for (int i = 0; i < numPointLig; i++) {
					m_pointLigList[i].attn *= t;
				}
			}
		}
		
		if (m_ligRangeInterpolateEndTime > 0.0f) {
			//���C�g�͈̔͂̕ϊ��ɕ�Ԏ��Ԃ��ݒ肳��Ă���E�B
			m_ligRangeInterpolateTimer += GameTime().GetFrameDeltaTime();
			if (m_ligRangeInterpolateTimer > m_ligRangeInterpolateEndTime) {
				//��ԏI���B
				m_ligRangeInterpolateEndTime = 0.0f;
				m_ligRangeInterpolateTimer = 0.0f;
				m_cbCPU.ligRange = m_ligRangeTarget;
			}
			else {
				float t = m_ligRangeInterpolateTimer / m_ligRangeInterpolateEndTime;
				m_cbCPU.ligRange = CMath::Lerp(t, m_ligRangeStart, m_ligRangeTarget);
			}
		}
		
		BeginGPUEvent(L"enRenderStep_Dithering");

		m_cbCPU.numPointLig = numPointLig;
		rc.UpdateSubresource(m_cbGPU, &m_cbCPU);
		rc.UpdateSubresource(m_pointLigListSB, m_pointLigList.data());

		//�����_�����O�X�e�[�g���f�B�U�悤�ɂ���B
		rc.OMSetDepthStencilState(DepthStencilState::disable);
		//���݂̃����_�����O�^�[�Q�b�g���擾�B
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		postEffect->ToggleFinalRenderTarget();
		CRenderTarget* renderTargets[] = {
			&postEffect->GetFinalRenderTarget()
		};
		rc.PSSetConstantBuffer(0, m_cbGPU);
		rc.OMSetBlendState(AlphaBlendState::disable);
		rc.PSSetSampler(0, m_samplerState);
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, m_pointLigListSB.GetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		postEffect->DrawFullScreenQuad(rc);
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender);
		rc.PSUnsetShaderResource(0);
		EndGPUEvent();
	}
	CVector2 CDithering::GeneratePointLigPosition()
	{
		CVector2 pos;
		pos.x = Random().GetRandDouble();
		pos.y = Random().GetRandDouble();
		switch (numPointLig % 12) {

		case 0:
			//��ʂ̉E��̗̈�@�B
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 1:
			//��ʂ̍���̗̈�@�B(UI���\������Ă���̂ł�����Ƃ��炷�B
			pos.x = CMath::Lerp(pos.x, -0.3f, -0.6f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 2:
			//��ʂ̍����̗̈�@�B
			pos.x = CMath::Lerp(pos.x, -0.4f, -0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 3:
			//��ʂ̉E���̗̈�@�B
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 4:
			//��ʂ̍���̗̈�A�B
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 5:
			//��ʂ̉E��̗̈�A�B
			pos.x = CMath::Lerp(pos.x, 0.1f, 0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 6:
			//��ʂ̍����̗̈�A�B
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, -0.1f, -0.4f);
			break;
		case 7:
			//��ʂ̉E���̗̈�A�B
			pos.x = CMath::Lerp(pos.x, 0.1f, 0.4f);
			pos.y = CMath::Lerp(pos.y, -0.1f, -0.4f);
			break;
		case 8:
			pos.x = CMath::Lerp(pos.x, -0.4f, 0.4f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 9:
			pos.x = CMath::Lerp(pos.x, -0.4f, 0.4f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 10:
			pos.x = CMath::Lerp(pos.x, -0.3f, -0.6f);
			pos.y = CMath::Lerp(pos.y, -0.3f, 0.3f);
			break;
		case 11:
			pos.x = CMath::Lerp(pos.x, 0.3f, 0.6f);
			pos.y = CMath::Lerp(pos.y, -0.3f, 0.3f);
			break;
		}
		pos.x *= GraphicsEngine().Get2DSpaceScreenWidth() * 0.5f;
		pos.y *= GraphicsEngine().Get2DSpaceScreenHeight() * -0.5f * (16.0f/9.0f);
		return pos;
	}
	void CDithering::AddPointLig(CVector2 pos)
	{
		pos.x /= GraphicsEngine().Get2DSpaceScreenWidth() * 0.5f;
		pos.y /= GraphicsEngine().Get2DSpaceScreenHeight() * -0.5f * (16.0f / 9.0f);
		m_pointLigList[numPointLig].position = pos;
		m_pointLigList[numPointLig].attn = ATTN;
		numPointLig++;
	}
}