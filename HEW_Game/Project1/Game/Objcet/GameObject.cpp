#include "../../Framework/Precompiled/pch.h"
#include "pch.h"
#include "GameObject.h"

void GameObject::Init(const wchar_t* imgname, int sx, int sy)
{
	//UV���W��ݒ�
	m_Split.x = sx;
	m_Split.y = sy;
	vertices[1].u = 1.0f / m_Split.x;
	vertices[2].v = 1.0f / m_Split.y;
	vertices[3].u = 1.0f / m_Split.x;
	vertices[3].v = 1.0f / m_Split.y;

	// ���_�o�b�t�@���쐬����
	// �����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertices);	// �m�ۂ���o�b�t�@�T�C�Y���w��ivector�Ȃ̂Œ��Ӂj
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertices.data();	// VRAM�ɑ���f�[�^���w��ivector�Ȃ̂Œ��Ӂj
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = d3d11->GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// �e�N�X�`���ǂݍ���
//	hr = DirectX::CreateWICTextureFromFile(Device, imgname, NULL, &m_pTextureView);
	hr = DirectX::CreateWICTextureFromFileEx(d3d11->GetDevice(), d3d11->GetDeviceContext(), imgname, 0, D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}
}

void GameObject::Draw()
{
	//���_�o�b�t�@��ݒ�
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	d3d11->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
	d3d11->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTextureView);

	//�萔�o�b�t�@���X�V
	ConstBuffer cb;

	// �v���W�F�N�V�����ϊ��s����쐬
	cb.matrixProj = DirectX::XMMatrixOrthographicLH( SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// ���I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
	cb.matrixWorld = DirectX::XMMatrixScaling(transform.GetScale().x, transform.GetScale().y, transform.GetScale().z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(transform.GetRotation().z * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	float u = (float)m_Number.x / m_Split.x;
	float v = (float)m_Number.y / m_Split.y;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	//���_�J���[�̃f�[�^���쐬
	cb.color = color;

	// �s����V�F�[�_�[�ɓn��
	d3d11->GetDeviceContext()->UpdateSubresource(d3d11->GetConststBuffer(), 0, NULL, &cb, 0, 0);

	d3d11->GetDeviceContext()->Draw(4, 0); // �`�施��
}

void GameObject::Uninit()
{
	//�J������
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTextureView);
}

void GameObject::SetPosition(Vector3 _Pos) 
{
	//���W���Z�b�g����
	transform.SetPosition(_Pos);
}

void GameObject::SetScale(Vector3 _Size) 
{
	//�傫�����Z�b�g����
	transform.SetScale(_Size);
}

void GameObject::SetRotation(Vector3 _Rot) 
{
	//�p�x���Z�b�g����
	transform.SetRotation(_Rot);
}
void GameObject::SetColor(Vector4 _Color)
{
	//�F���Z�b�g����
	color.x = _Color.x;
	color.y = _Color.y;
	color.z = _Color.z;
	color.w = _Color.w;
}

Vector3 GameObject::GetPosition(void)
{
	//���W���Q�b�g
	return transform.GetPosition();
}
  
Vector3 GameObject::GetScale(void)
{
	//�傫�����Q�b�g
	return transform.GetScale();
}

Vector3 GameObject::GetRotation(void)
{
	//�p�x���Q�b�g
	return transform.GetRotation();
}

Vector4 GameObject::GetColor(void)
{
	//�F���Q�b�g
	return color;
}
            
