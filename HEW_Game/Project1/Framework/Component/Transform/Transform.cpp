#include "../../../pch.h"
#include "Transform.h"


// セッター
void Transform::SetPosition(Vector3 _Position) {
	m_Position = _Position;
}

void Transform::SetRotation(Vector3 _Rotation) {
	m_Position = _Rotation;
}

void Transform::SetScale(Vector3 _Scale) {
	m_Position = _Scale;
}

Vector3 Transform::GetPosition(void) {
	return m_Position;
}

Vector3 Transform::GetRotation(void) {
	 return m_Rotation;
 }

Vector3 Transform::GetPosition(void) {
	 return m_Rotation;
 }


// 行列変換
Matrix Transform::ConvertMatrix(void) {
	XMMATRIX WorldPos, WorldRot, WorldScale;
	WorldPos = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);			// 座標ををワールド行列へ
	WorldRot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);	// 角度をワールド行列へ
	WorldScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);						// スケール（大きさ）をワールド行列へ
	return WorldPos * WorldRot * WorldScale;
	// TODO:1105ここまで！→ワールド行列への変換を完成させる

}

