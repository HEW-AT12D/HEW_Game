#include "../Precompiled/pch.h"
#include"Texture.h"

/**
 * @brief �e�N�X�`���̏�����
 * @param _Filename �t�@�C���p�X
 * @param _Transform �g�����X�t�H�[��
 * @param _Split �摜������
 * @param _Uv �摜�ԍ�
*/
void Texture::Init(const wchar_t* _Filename, Transform _Transform, XMFLOAT2 _Split, XMFLOAT2 _Uv)
{
	//UV���W��ݒ�
	uv.x = _Uv.x;
	uv.y = _Uv.y;
	//! �摜���������摜�ԍ��Ŋ����āA�����������Ԗڂ��g�������e���_���ƌv�Z
	vertexList[1].u = uv.x / split.x;
	vertexList[2].v = uv.y / split.y;
	vertexList[3].u = uv.x / split.x;
	vertexList[3].v = uv.y / split.y;

	// ���_�o�b�t�@���쐬����
	// �����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// �m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// �e�N�X�`���ǂݍ���
//	hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
	hr = DirectX::CreateWICTextureFromFileEx(m_pDevice, m_pDeviceContext, _Filename, 0, D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}
}


void Texture::Draw()
{
	transform.Getpo
}

void Texture::Uninit()
{

}