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

	void SetWorldViewProjectionMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}
	void SetWorldMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}
	void SetInvViewMatrixVariable(const Matrix& newValue) const
	{
		m_pMatInvViewVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}

	void SetDiffuseMap(const std::string& filePath, ID3D11Device* pDevice) const;
	void SetNormalMap(const std::string& filePath, ID3D11Device* pDevice) const;
	void SetSpecularMap(const std::string& filePath, ID3D11Device* pDevice) const;
	void SetGlossinessMap(const std::string& filePath, ID3D11Device* pDevice) const;

private:
	ID3DX11Effect* m_pEffect;

	ID3DX11EffectTechnique* m_pPointTechnique;
	ID3DX11EffectTechnique* m_pLinearTechnique;
	ID3DX11EffectTechnique* m_pAnisotropicTechnique;
	void InitTechniques();

	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable;
	ID3DX11EffectMatrixVariable* m_pMatWorldVariable;
	ID3DX11EffectMatrixVariable* m_pMatInvViewVariable;

	ID3DX11EffectShaderResourceVariable* m_pDiffuseMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pNormalMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pSpecularMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pGlossinessMapVariable;

	void InitVariables();

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
};