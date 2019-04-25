/*!
 * @brief	�f�B�U�����O�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�f�B�U�����O�B
	 * @details
	 *  �ŏI�I�ȉ摜�Ƀm�C�Y�������邱�Ƃɂ���āA�}�b�n�o���h�Ȃǂ�
	 *  �A�[�e�B�t�@�N�g���y������B
	 */
	class CDithering : Noncopyable{
	public:
		CDithering();
		~CDithering();
		/*!
		 *@brief	�J���B
		 */
		void Release();
		/*!
		 *@brief	�������B
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	�`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void Render(CRenderContext& rc, CPostEffect* postEffect);
		void SetLigRange(float range)
		{
			m_cbCPU.ligRange = range;
			if (m_cbCPU.ligRange < 0.001f) {
				//0�͂�����
				m_cbCPU.ligRange = 0.001f;
			}
		}
		void Disable()
		{
			m_isEnable = false;
		}
		void Enable()
		{
			m_isEnable = true;
		}
	private:
		struct SCb {
			float ligRange = 0.8f;	
		};
		CConstantBuffer m_cbGPU;
		SCb m_cbCPU;
		bool m_isEnable = false;		//!<�L���H
		CShader m_vsShader;				//!<���_�V�F�[�_�[
		CShader m_psShader;				//!<�s�N�Z���V�F�[�_�[�B
		CSamplerState m_samplerState;	//!<�T���v���X�e�[�g�B
	};
}