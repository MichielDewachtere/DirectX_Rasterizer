#pragma once
#include "Effect.h"

class MeshEffect final : public Effect
{
public:
	MeshEffect(ID3D11Device* pDevice, const std::wstring& assetFile);
	virtual ~MeshEffect() override;

	MeshEffect(const MeshEffect& other) = delete;
	MeshEffect& operator=(const MeshEffect& rhs) = delete;
	MeshEffect(MeshEffect&& other) = delete;
	MeshEffect& operator=(MeshEffect&& rhs) = delete;

	void SetWorldMatrixVariable(const Matrix& newValue) const
	{
		m_pMatWorldVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}
	void SetInvViewMatrixVariable(const Matrix& newValue) const
	{
		m_pMatInvViewVariable->SetMatrix(reinterpret_cast<const float*>(&newValue));
	}

	void SetNormalMap(const std::string& filePath, ID3D11Device* pDevice) const;
	void SetSpecularMap(const std::string& filePath, ID3D11Device* pDevice) const;
	void SetGlossinessMap(const std::string& filePath, ID3D11Device* pDevice) const;

private:
	ID3DX11EffectMatrixVariable* m_pMatWorldVariable;
	ID3DX11EffectMatrixVariable* m_pMatInvViewVariable;

	ID3DX11EffectShaderResourceVariable* m_pNormalMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pSpecularMapVariable;
	ID3DX11EffectShaderResourceVariable* m_pGlossinessMapVariable;

	virtual void InitMatrixVariables() override;
	virtual void InitShaderResourceVariables() override;
};

