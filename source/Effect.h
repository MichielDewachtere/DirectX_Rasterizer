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

	ID3DX11Effect* GetEffect() const { return m_pEffect; }

	ID3DX11EffectTechnique* GetPointTechnique() const { return m_pPointTechnique; }
	ID3DX11EffectTechnique* GetLinearTechnique() const { return m_pLinearTechnique; }
	ID3DX11EffectTechnique* GetAnisotropicTechnique() const { return m_pAnisotropicTechnique; }

	void SetMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}
	void SetDiffuseMap(const std::string& filePath, ID3D11Device* pDevice) const;

private:
	ID3DX11Effect* m_pEffect;

	ID3DX11EffectTechnique* m_pPointTechnique;
	ID3DX11EffectTechnique* m_pLinearTechnique;
	ID3DX11EffectTechnique* m_pAnisotropicTechnique;
	void InitTechniques();

	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable;
	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;
	void InitVariables();

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};