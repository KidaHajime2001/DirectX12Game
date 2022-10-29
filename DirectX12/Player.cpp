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
#include"PlayerShotDirector.h"
Player::Player(CollisionTag _tag, bool _alive)
    :m_model(Singleton<PMDModel>::GetInstance())
    , m_controller(Singleton<Controller>::GetInstance())
    , m_camera(Singleton<Camera>::GetInstance())
    , m_sound(Singleton<Sound>::GetInstance())
    , m_json(Singleton<SupportJson>::GetInstance())
    , m_isAlive(_alive)
    , m_shotDirector(new PlayerShotDirector())
    ,Actor(_tag)
    ,m_cubeRotate(45)
    ,m_inputFlameCount(0)
    ,m_inputFlameFlag(false)
{
    Init();
    m_camera.SetPlayerPosition(GetPosition());
    
}

Player::~Player()
{
    delete m_shotDirector;
}

void Player::Update()
{
    m_shotDirector->Update(IsShotFlag(),GetPosition(),GetShotDirection(),GetShotSpeed());
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
            m_cubeRotate+=30;
            if (m_cubeRotate>=360)
            {
                m_cubeRotate = 0;
            }
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
    if (m_isAlive)
    {
        m_shotDirector->Draw();
        m_model.Draw(GetPosition(), m_shotStatus.cosDirection, PMDModelType::Player);
        m_model.Draw(XMF3Math::AddXMFLOAT3(GetPosition(),XMF3Math::SetMagnitude(m_shotStatus.shotDirection,-1)),XMF3Math::DegreeForRadian(m_cubeRotate), PMDModelType::PlayerCube);

    }
}

void Player::Init()
{
    XMFLOAT3 posData=m_json.GetXMFLOAT3(JsonDataType::Player,"Position");
    int radiusData = m_json.GetInt(JsonDataType::Player, "Radius");

    //  取得したデータを元に初
    SetPotision(posData);
    m_param.mCollision->m_data.radius=radiusData;
    m_isAlive = true;
    m_param.mCollision->m_isValidity = false;
}

void Player::OnCollisionEnter(Collision* otherCollision)
{
    OutputDebugString("HitEnemy.\n");
    m_isAlive = false;
    
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

    // ある程度の入力はデッドゾーンとして切り捨てる
    //マイナス入力に対応するために絶対値計算
    if (abs(inputScalar.x)<=DEADZONE)
    {
        inputScalar.x = 0;
    }
    if (abs(inputScalar.y)<= DEADZONE)
    {
        inputScalar.y = 0;
    }
    //コントローラー未接続用移動処理
    if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_UP))
    {
        inputScalar.y += 1;
    }
    if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_DOWN))
    {
        inputScalar.y -= 1;
    }
    if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_RIGHT))
    {
        inputScalar.x += 1;
    }
    if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_LEFT))
    {
        inputScalar.x -= 1;
    }
   
    inputVec    =XMF3Math::AddXMFLOAT3(inputVec ,XMF3Math::ScalarXMFLOAT3(Forward, inputScalar.y));
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(RIGHT, inputScalar.x));
    MoveEffect(XMF3Math::LengthXMFLOAT3(inputVec));

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
}

void Player::MoveEffect(const float _inputSize)
{
    m_inputFlameCount++;
    if (_inputSize>= 0.4f&&(m_inputFlameCount%10)==0)
    {
        m_effect.PlayEffect(EffectType::PlayerMove,GetPosition(),false);
    }
}

