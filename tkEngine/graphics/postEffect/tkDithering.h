/*!
 * @brief	ディザリング。
 */

#pragma once

#include <array>
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
		void SetLigRange(float range, float interpolateTime)
		{
			if (interpolateTime < 0.001f) {
				//即反映。
				m_cbCPU.ligRange = range;
				if (m_cbCPU.ligRange < 0.001f) {
					//0はあかん
					m_cbCPU.ligRange = 0.001f;
				}
			}
			else {
				//保管しましょう。
				m_ligRangeStart = m_cbCPU.ligRange;
				m_ligRangeTarget = range;
				m_ligRangeInterpolateTimer = 0.0f;
				m_ligRangeInterpolateEndTime = interpolateTime;
			}
		}
		void Disable()
		{
			m_isEnable = false;
			numPointLig = 0;
		}
		void Enable()
		{
			m_isEnable = true;
		}
		void DisablePointLig(float fadeOutTime)
		{
			if (fadeOutTime == 0.0f) {
				numPointLig = 0;
			}
			else {
				m_fadeOutTimer = 0.0f;
				m_fadeOutEndTime = fadeOutTime;
			}
		}
		CVector2 AddPointLig();
		CVector2 AddPointLig(CVector2 pos, float attn);
		
	private:
		struct SCb {
			float ligRange = 0.8f;
			int numPointLig = 0;	//ポイントライトの数。
		};
		struct SPointLig {
			CVector2 position;	//座標。
			float attn;			
		};
		enum {
			MAX_POINT_LIG = 1024	//最大ポイントライト数。
		};
		float m_fadeOutTimer = 0.0f;
		float m_fadeOutEndTime = 0.0f;

		float m_ligRangeInterpolateTimer = 0.0f;
		float m_ligRangeInterpolateEndTime = 0.0f;
		float m_ligRangeTarget = 0;
		float m_ligRangeStart = 0;

		int numPointLig = 0;
		CStructuredBuffer m_pointLigListSB;	//ポイントライトのリストのストラクチャーどバッファ。
		std::array<SPointLig, MAX_POINT_LIG> m_pointLigList;
		CConstantBuffer m_cbGPU;
		SCb m_cbCPU;
		bool m_isEnable = false;		//!<有効？
		CShader m_vsShader;				//!<頂点シェーダー
		CShader m_psShader;				//!<ピクセルシェーダー。
		CSamplerState m_samplerState;	//!<サンプラステート。
	};
}