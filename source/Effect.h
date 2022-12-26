#pragma once

using namespace dae;

class Effect
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& assetFile);
	virtual ~Effect();

	Effect(const Effect& other) = delete;
	Effect& operator=(const Effect& rhs) = delete;
	Effect(Effect&& other) = delete;
	Effect& operator=(Effect&& rhs) = delete;

	virtual ID3DX11Effect* GetEffect() const { return m_pEffect; }

	virtual ID3DX11EffectTechnique* GetPointTechnique() const { return m_pPointTechnique; }
	virtual ID3DX11EffectTechnique* GetLinearTechnique() const { return m_pLinearTechnique; }
	virtual ID3DX11EffectTechnique* GetAnisotropicTechnique() const { return m_pAnisotropicTechnique; }

	virtual void SetWorldViewProjectionMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}

	virtual void SetDiffuseMap(const std::string& filePath, ID3D11Device* pDevice) const;

protected:
	ID3DX11Effect* m_pEffect;

	ID3DX11EffectTechnique* m_pPointTechnique;
	ID3DX11EffectTechnique* m_pLinearTechnique;
	ID3DX11EffectTechnique* m_pAnisotropicTechnique;
	void InitTechniques();

	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable;

	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;

	virtual void InitMatrixVariables() {}
	virtual void InitShaderResourceVariables() {}

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};