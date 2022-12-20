#pragma once

using namespace dae;

class Effect final
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& assetFile);
	~Effect();

	Effect(const Effect& other) = delete;
	Effect& operator=(const Effect& rhs) = delete;
	Effect(Effect&& other) = delete;
	Effect& operator=(Effect&& rhs) = delete;

	ID3DX11Effect* GetEffect() const;
	ID3DX11EffectTechnique* GetTechnique() const;

	void SetMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}

private:
	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;

	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable;

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};