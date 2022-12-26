#include "pch.h"
#include "Effect.h"

#include "Texture.h"

#include <sstream>

using namespace dae;

Effect::Effect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
	m_pEffect = LoadEffect(pDevice, assetFile);

	InitTechniques();

	m_pMatWorldViewProjVariable = m_pEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
	if (m_pMatWorldViewProjVariable->IsValid() == false)
		std::wcout << L"m_pMatWorldViewProjVariable not valid!\n";

	m_pDiffuseMapVariable = m_pEffect->GetVariableByName("gDiffuseMap")->AsShaderResource();
	if (!m_pDiffuseMapVariable->IsValid())
		std::wcout << L"m_pDiffuseMapVariable not valid!\n";
}

Effect::~Effect()
{
	if (m_pDiffuseMapVariable) m_pDiffuseMapVariable->Release();
	if (m_pMatWorldViewProjVariable) m_pMatWorldViewProjVariable->Release();

	if (m_pAnisotropicTechnique) m_pAnisotropicTechnique->Release();
	if (m_pLinearTechnique) m_pLinearTechnique->Release();
	if (m_pPointTechnique) m_pPointTechnique->Release();

	if (m_pEffect) m_pEffect->Release();
}

void Effect::SetDiffuseMap(const std::string& filePath, ID3D11Device* pDevice) const
{
	const Texture* diffuseTexture = Texture::LoadFromFile(filePath, pDevice);

	if (m_pDiffuseMapVariable)
		m_pDiffuseMapVariable->SetResource(diffuseTexture->GetShaderResourceView());

	delete diffuseTexture;
}

void Effect::InitTechniques()
{
	m_pPointTechnique = m_pEffect->GetTechniqueByName("PointTechnique");
	if (!m_pPointTechnique->IsValid()) std::wcout << L"PointTechnique not valid\n";

	m_pLinearTechnique = m_pEffect->GetTechniqueByName("LinearTechnique");
	if (!m_pPointTechnique->IsValid()) std::wcout << L"LinearTechnique not valid\n";

	m_pAnisotropicTechnique = m_pEffect->GetTechniqueByName("AnisotropicTechnique");
	if (!m_pPointTechnique->IsValid()) std::wcout << L"AnisotropicTechnique not valid\n";
}


ID3DX11Effect* Effect::LoadEffect(ID3D11Device* pDevice, const std::wstring& assetFile)
{
	HRESULT result;
	ID3D10Blob* pErrorBlob{ nullptr };
	ID3DX11Effect* pEffect{};

	DWORD shaderFlags{ 0 };

#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	result = D3DX11CompileEffectFromFile
	(
		assetFile.c_str(),
		nullptr,
		nullptr,
		shaderFlags,
		0,
		pDevice,
		&pEffect,
		&pErrorBlob
	);

	if (FAILED(result))
	{
		if (pErrorBlob != nullptr)
		{
			const char* pErrors{ static_cast<char*>(pErrorBlob->GetBufferPointer()) };

			std::wstringstream ss;
			for (unsigned int i{}; i < pErrorBlob->GetBufferSize(); ++i)
			{
				ss << pErrors[i];
			}

			OutputDebugStringW(ss.str().c_str());
			pErrorBlob->Release();
			pErrorBlob = nullptr;

			std::wcout << ss.str() << "\n";
		}
		else
		{
			std::wstringstream ss;
			ss << "EffectLoader: Failed to CreateEffectFromFile!\nPath: " << assetFile;
			std::wcout << ss.str() << "\n";
			return nullptr;
		}
	}

	return pEffect;
}