#include "Player.h"
#include"Singleton.h"
#include"Controller.h"
#include "ModelTypeData.h"
#include"Collision.h"
#include "PMDModel.h"
#include"XMF3Math.h"
#include"Camera.h"
#include<cmath>
#include"Sound.h"
#include"SoundType.h"
#include"SupportJSON.h"
Player::Player(CollisionTag _tag, bool Alive)
    :m_model(Singleton<PMDModel>::GetInstance())
    , m_controller(Singleton<Controller>::GetInstance())
    , m_camera(Singleton<Camera>::GetInstance())
    , m_sound(Singleton<Sound>::GetInstance())
    , m_json(Singleton<SupportJson>::GetInstance())
    ,Actor(_tag,Alive)
{
    Init();
    m_camera.SetPlayerPosition(GetPosition());
}

Player::~Player()
{

}

void Player::Update()
{
   
    m_param.mCollision->Update();
    m_camera.SetPlayerPosition(GetPosition());
    m_camera.Update();
    
    m_shotStatus.shotFlag = false;
    if (m_controller.IsPress(ButtonName::GAMEPAD_RIGHT_SHOULDER))
    {
        if (!m_shotStatus.shotFlag &&m_shotStatus.shotInterval==0)
        {
            m_sound.Play(SoundType::ShootSE,false,true);
            m_shotStatus.shotFlag= true;
            m_shotStatus.shotInterval = SHOT_COOL_FLAME;
        }
    }
    if (m_shotStatus.shotInterval!=0)//ショットフラグがたっているとき
    {
        --m_shotStatus.shotInterval;
        if (m_shotStatus.shotInterval < 0)
        {
            m_shotStatus.shotInterval = 0;
        }
    }

    if (m_controller.IsPushEnter(ButtonName::GAMEPAD_B)&& !m_jumpStatus.JumpFlag)
    {
        m_jumpStatus.JumpFlag = true;
        m_param.pos.y = m_jumpStatus.JumpPower;
    }
    if (m_jumpStatus.JumpFlag)
    {
        m_param.pos.y += m_jumpStatus.JumpPower;
        m_jumpStatus.JumpPower -= m_jumpStatus.Gravity;
        if (m_param.pos.y<0)
        {
            m_jumpStatus.Init();
            m_param.pos.y = 0;
        }
    }

    Move();
    TakeAim();

}

void Player::Draw()
{
    
   

    if (m_param.IsAlive)
    {
        m_model.Draw(GetPosition(),m_shotStatus.cosDirection, PMDModelType::Player);
    }
    
}

void Player::Init()
{
    XMFLOAT3 posData=m_json.GetXMFLOAT3(JsonDataType::Player,"Position");
    int radiusData = m_json.GetInt(JsonDataType::Player, "Radius");

    //  取得したデータを元に初
    SetPotision(posData);
   m_param.mCollision = new Collision(this, radiusData);
   SetAlive(true);
}

void Player::OnCollisionEnter(Collision* otherCollision)
{
    OutputDebugString("HitEnemy.\n");
    m_effect.PlayEffect(EffectType::DefeatRedEnemy,GetPosition(), false);
    
    SetAlive(false);
    
}

void Player::Move()
{
    //縦移動ベクトル
    XMFLOAT3 inputVec(0,0,0);

    //カメラから前方向を出す
    XMFLOAT3 Forward=XMF3Math::SubXMFLOAT3( m_param.pos,m_camera.GetPosition());
    //前方向ベクトルとして使いたいため上の部分は０に置き換える
    Forward.y = 0;
    //正規化
    Forward = XMF3Math::NormalizeXMFLOAT3(Forward);

    //外積から横方向を出す
    XMFLOAT3 RIGHT = XMF3Math::CrossXMFLOAT3(XMFLOAT3(0,1,0),Forward);

    //コントローラーの入力と統合
    XMFLOAT2 inputScalar = m_controller.GetLeftStickInput();

    inputVec    =XMF3Math::AddXMFLOAT3(inputVec ,XMF3Math::ScalarXMFLOAT3(Forward, inputScalar.y));
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(RIGHT, inputScalar.x));
    
    m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,inputVec);
}

void Player::TakeAim()
{
    //縦移動ベクトル
    XMFLOAT3 inputVec(0, 0, 0);

    //カメラから前方向を出す
    XMFLOAT3 Forward = XMF3Math::SubXMFLOAT3(m_param.pos, m_camera.GetPosition());
    //前方向ベクトルとして使いたいため上の部分は０に置き換える
    Forward.y = 0;
    //正規化
    Forward = XMF3Math::NormalizeXMFLOAT3(Forward);

    //外積から横方向を出す
    XMFLOAT3 RIGHT = XMF3Math::CrossXMFLOAT3(XMFLOAT3(0, 1, 0), Forward);

    //コントローラーの入力と統合
    XMFLOAT2 inputScalar = m_controller.GetRightStickInput();
    if ((inputScalar.x<=0.5f&&inputScalar.x >=-0.5f)&& (inputScalar.y <= 0.5f && inputScalar.y >= -0.5f))
    {
        return;
    }
    
    
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(Forward, inputScalar.y));
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(RIGHT, inputScalar.x));

    inputVec=XMF3Math::NormalizeXMFLOAT3(inputVec);
    m_shotStatus.cosDirection = atan2(inputVec.x, inputVec.z);

    m_shotStatus.shotDirection = inputVec;
    m_shotStatus.TmpShotDirection = m_shotStatus.shotDirection;
}

