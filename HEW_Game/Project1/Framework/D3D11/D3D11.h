#pragma once
#include "../../pch.h"

#define SCREEN_WIDTH (640)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (480)	// �E�C���h�E�̍���

//////////////////////////////////////////////////
//				DirectX�t���[�����[�N				//
//////////////////////////////////////////////////
// TODO:�Q�[���N���X��D3D11�N���X���p������ׂ��H�����o�ϐ��ɂƂǂ߂Ă����ׂ��H
// TODO:2024/10/4 D3D11��Init�֐���������Ɋ֐���������A�G���[�f���Ă镔�����d�v�Ȃ̂ł����̗���𗝉�����

class D3D11
{
public:
	D3D11();
	~D3D11();

	ID3D11Device *GetDevice(void);                 //!m_Device�̃Q�b�^�[
	ID3D11DeviceContext* GetDeviceContext(void);   //!m_DeviceContext�̃Q�b�^�[
	IDXGISwapChain* GetSwapChain(void);            //! �X���b�v�`�F�C�����_�u���o�b�t�@�@�\
	ID3D11Buffer* GetConststBuffer(void);                 //! �萔�o�b�t�@�p�ϐ�
	HRESULT Init(HWND hwnd);		// �������i�Q�[���N���X�ł͂��̏����������������ꍇ���Q�[���̏������������s�ɂ���j
	void StartRender(void);			// �`�揈��
	void FinishRender(void);		// �`��I������
	void Release(void);				// �I������

	// �V�F�[�_�[�n����
	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
		D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout);
	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader);

	// �V�F�[�_�[�R���p�C��
	HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

private:

	//--------------------------------------------------------------------------------------
	// �����o�ϐ��i�錾����cpp���ł̂ݗL�����ǂ��ł��g�������ꍇ��extern�i�O���Q�Ɓj���g���j
	//--------------------------------------------------------------------------------------
	// ��ID3D11�Ŏn�܂�|�C���^�^�̕ϐ��́A�������K�v������
	// �f�o�C�X��DirectX�̊e��@�\�����
	ID3D11Device* m_pDevice;
	// �R���e�L�X�g���`��֘A���i��@�\
	ID3D11DeviceContext* m_pDeviceContext;
	// �X���b�v�`�F�C�����_�u���o�b�t�@�@�\
	IDXGISwapChain* m_pSwapChain;
	// �����_�[�^�[�Q�b�g���`����\���@�\
	ID3D11RenderTargetView* m_pRenderTargetView;
	// �f�v�X�o�b�t�@
	ID3D11DepthStencilView* m_pDepthStencilView;
	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;
	// ���_�V�F�[�_�[�I�u�W�F�N�g
	ID3D11VertexShader* m_pVertexShader;
	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3D11PixelShader* m_pPixelShader;
	// �T���v���[�p�ϐ�
	ID3D11SamplerState* m_pSampler;
	// �萔�o�b�t�@�p�ϐ�
	ID3D11Buffer* m_pConstantBuffer;
	// �u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j
	ID3D11BlendState* m_pBlendState;

	//ID3D11ConstantBuffer* m_pConstantBuffer;
};

D3D11::D3D11()
{
}

D3D11::~D3D11()
{
}


// �\���̂̒�`
// ���_�f�[�^��\���\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;

	//�F
	float r, g, b, a;

	// �e�N�X�`�����W�iUV���W�j
	float u, v;
};

// �萔�o�b�t�@�p�\����
struct ConstBuffer
{
	// ���_�J���[�s��
	DirectX::XMFLOAT4 color;
	// UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	// �v���W�F�N�V�����ϊ��s��
	DirectX::XMMATRIX matrixProj;
	// ���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;
};



// Direct3D����̊ȗ����}�N��
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }
