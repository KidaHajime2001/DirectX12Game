#include"Shield.h"
#include "Controller.h"
#include "ModelTypeData.h"
#include"Collision.h"
#include "PMDModel.h"
#include "XMF3Math.h"
Shield::Shield(CollisionTag _tag)
    :Actor(_tag)
    ,m_controller(Singleton<Controller>::GetInstance())
    ,m_model(Singleton<PMDModel>::GetInstance())
{

    m_param.mCollision->m_data.radius = 15;
}

Shield::~Shield()
{
}

void Shield::OnCollisionEnter(Collision* otherCollision)
{
    if (otherCollision->GetTag() == CollisionTag::EnemyBullet)
    {
        m_effect.PlayEffect(EffectType::EndEffect, otherCollision->GetPosition(), false);
    }
}

void Shield::Update(DirectX::XMFLOAT3 _pos)
{
    m_param.pos = _pos;
    if (m_controller.IsPushEnter(ButtonName::GAMEPAD_LEFT_SHOULDER))
    {
        m_shieldFlag = !m_shieldFlag;
    }

    if (m_shieldFlag)
    {
        m_shieldRadian++;
    }
    m_param.mCollision->m_isValidity = m_shieldFlag;
}

void Shield::Draw()
{ 
    //ÉVÅ[ÉãÉhê∂ê¨íÜèÇï`âÊ
    if (m_shieldFlag)
    {


        m_shieldRotate = XMF3Math::RotateVec2_XZ(XMFLOAT3(1, 0, 0), m_shieldRadian);

        m_model.Draw(GetPosition(),
            atan2(m_shieldRotate.x, m_shieldRotate.z),
            PMDModelType::ShieldRing);

        m_model.Draw(
            XMF3Math::AddXMFLOAT3(GetPosition(),XMF3Math::SetMagnitude(m_shieldRotate, m_shieldSpace)),
            atan2(m_shieldRotate.x, m_shieldRotate.z),
            PMDModelType::Shield);

        auto vec = XMF3Math::RotateVec2_XZ(m_shieldRotate, 120);

        m_model.Draw(XMF3Math::AddXMFLOAT3(GetPosition(),
            XMF3Math::SetMagnitude(vec, m_shieldSpace)),
            atan2(vec.x, vec.z),
            PMDModelType::Shield);


        vec = XMF3Math::RotateVec2_XZ(m_shieldRotate, -120);


        m_model.Draw(XMF3Math::AddXMFLOAT3(GetPosition(),
            XMF3Math::SetMagnitude(vec, m_shieldSpace)),
            atan2(vec.x, vec.z),
            PMDModelType::Shield);


    }
}
