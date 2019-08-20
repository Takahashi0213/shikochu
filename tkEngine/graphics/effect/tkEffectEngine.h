/*!
 * @brief	�G�t�F�N�g�G���W���B
 */

#pragma once

#include "tkEngine/resource/tkResourceManager.h"

namespace tkEngine{
	class CPostEffect;
	using CEffectResourceManager = TResourceManager<Effekseer::Effect>;
	/*!
	 * @brief	�G�t�F�N�g�G���W���B
	 */
	class CEffectEngine : Noncopyable {
	public:
		CEffectEngine();
		~CEffectEngine();
		/*!
		 *@brief	����B
		 */
		void Release();
		/*!
		 *@brief	�������B
		 */
		void Init();
		/*!
		 *@brief	�X�V�B
		 */
		void Update();
		/*!
		 *@brief	�`��B
		 */
		void Render(CRenderContext& rc, CPostEffect* ps)
		{
			InternalRender(rc, ps, m_manager);
		}
		void PostRender(CRenderContext& rc, CPostEffect* ps)
		{
			InternalRender(rc, ps, m_postManager);
		}
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g���쐬�B
		 */
		Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath, bool isPost);
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g���Đ��B
		 */
		Effekseer::Handle Play(Effekseer::Effect* effect, bool isPost);
		/*!
		 *@brief	Effekseer�}�l�[�W���̎擾�B
		 */
		Effekseer::Manager& GetEffekseerManager(bool isPost)
		{
			if (isPost) {
				return *m_postManager;
			}
			return *m_manager;
		}
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g�̒�~�B
		 */
		void Stop(Effekseer::Handle handle, bool isPost);
		/*!
		 *@brief	���\�[�X�}�l�[�W�����擾�B
		 */
		CEffectResourceManager& GetResourceManager()
		{
			return m_resourcetManager;
		}
	private:
		void InternalRender(CRenderContext& rc, CPostEffect* ps, Effekseer::Manager* manager );
	private:
		CEffectResourceManager m_resourcetManager;	//���\�[�X�}�l�[�W���B
		Effekseer::Manager*	m_manager= nullptr;
		Effekseer::Manager* m_postManager = nullptr;
		EffekseerRenderer::Renderer*	m_renderer = nullptr;
		CRenderTarget m_addEffectBuffer;
		std::vector<int>	m_renderFlags;
		ID3D11BlendState* m_finalCombineAddBlendState = nullptr;
		CConstantBuffer m_cb;
		CShader		m_copyVS;					//!<�R�s�[�p�̒��_�V�F�[�_�[�B
		CShader		m_copyPS;					//!<�R�s�[�p�̒��_�V�F�[�_�[�B
	};
}