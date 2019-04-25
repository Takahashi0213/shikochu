/*!
 * @brief	ディザリング。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	ディザリング。
	 * @details
	 *  最終的な画像にノイズを混ぜることによって、マッハバンドなどの
	 *  アーティファクトを軽減する。
	 */
	class CDithering : Noncopyable{
	public:
		CDithering();
		~CDithering();
		/*!
		 *@brief	開放。
		 */
		void Release();
		/*!
		 *@brief	初期化。
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	描画。
		*@param[in]		rc		レンダリングコンテキスト。
		*/
		void Render(CRenderContext& rc, CPostEffect* postEffect);
		void SetLigRange(float range)
		{
			m_cbCPU.ligRange = range;
			if (m_cbCPU.ligRange < 0.001f) {
				//0はあかん
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
		bool m_isEnable = false;		//!<有効？
		CShader m_vsShader;				//!<頂点シェーダー
		CShader m_psShader;				//!<ピクセルシェーダー。
		CSamplerState m_samplerState;	//!<サンプラステート。
	};
}