/*!
 * @brief	ディザリング。
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
		//サンプラを作成。
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);

		m_cbGPU.Create(nullptr, sizeof(SCb));
		{
			//ポイントライト用のストラクチャバッファの作成。
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
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
			//フェードアウトが指定されている。
			//ポイントライトの効果を少しづつ弱くする。
			m_fadeOutTimer += GameTime().GetFrameDeltaTime();
			if (m_fadeOutTimer > m_fadeOutEndTime) {
				//ｆａｄｅおわり
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
			//ライトの範囲の変換に補間時間が設定されている・。
			m_ligRangeInterpolateTimer += GameTime().GetFrameDeltaTime();
			if (m_ligRangeInterpolateTimer > m_ligRangeInterpolateEndTime) {
				//補間終わり。
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

		//レンダリングステートをディザようにする。
		rc.OMSetDepthStencilState(DepthStencilState::disable);
		//現在のレンダリングターゲットを取得。
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		//レンダリングターゲットを切り替える。
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
			//画面の右上の領域①。
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 1:
			//画面の左上の領域①。(UIが表示されているのでちょっとずらす。
			pos.x = CMath::Lerp(pos.x, -0.3f, -0.6f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 2:
			//画面の左下の領域①。
			pos.x = CMath::Lerp(pos.x, -0.4f, -0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 3:
			//画面の右下の領域①。
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 4:
			//画面の左上の領域②。
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 5:
			//画面の右上の領域②。
			pos.x = CMath::Lerp(pos.x, 0.1f, 0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 6:
			//画面の左下の領域②。
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, -0.1f, -0.4f);
			break;
		case 7:
			//画面の右下の領域②。
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
	CVector2 CDithering::GeneratePointLigPosition_rand()
	{
		CVector2 pos;
		pos.x = Random().GetRandDouble();
		pos.y = Random().GetRandDouble();
		switch (rand() % 12) {

		case 0:
			//画面の右上の領域①。
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 1:
			//画面の左上の領域①。(UIが表示されているのでちょっとずらす。
			pos.x = CMath::Lerp(pos.x, -0.3f, -0.6f);
			pos.y = CMath::Lerp(pos.y, -0.3f, -0.6f);
			break;
		case 2:
			//画面の左下の領域①。
			pos.x = CMath::Lerp(pos.x, -0.4f, -0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 3:
			//画面の右下の領域①。
			pos.x = CMath::Lerp(pos.x, 0.4f, 0.8f);
			pos.y = CMath::Lerp(pos.y, 0.3f, 0.6f);
			break;
		case 4:
			//画面の左上の領域②。
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 5:
			//画面の右上の領域②。
			pos.x = CMath::Lerp(pos.x, 0.1f, 0.4f);
			pos.y = CMath::Lerp(pos.y, 0.1f, 0.4f);
			break;
		case 6:
			//画面の左下の領域②。
			pos.x = CMath::Lerp(pos.x, -0.1f, -0.4f);
			pos.y = CMath::Lerp(pos.y, -0.1f, -0.4f);
			break;
		case 7:
			//画面の右下の領域②。
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
		pos.y *= GraphicsEngine().Get2DSpaceScreenHeight() * -0.5f * (16.0f / 9.0f);
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