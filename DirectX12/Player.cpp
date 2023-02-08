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
#include"Fps.h"
#include"Time.h"
#include"Shield.h"
Player::Player(CollisionTag _tag, bool _alive)
    :m_model(Singleton<PMDModel>::GetInstance())
    , m_fps(Singleton<Fps>::GetInstance())
    , m_controller(Singleton<Controller>::GetInstance())
    , m_camera(Singleton<Camera>::GetInstance())
    , m_sound(Singleton<Sound>::GetInstance())
    , m_json(Singleton<SupportJson>::GetInstance())
    , m_isAlive(_alive)
    , m_shotDirector(new PlayerShotDirector())
    , Actor(_tag)
    , m_cubeRotate(45)
    , m_inputFlameCount(0)
    , m_inputFlameFlag(false)
    , m_timer(new Time())
    ,m_shield(new Shield(CollisionTag::Shield))
    ,m_playerDirection(XMFLOAT3(0,0,0))
{
    Init();
}

Player::~Player()
{
    delete m_shotDirector;
    delete m_shield;
    delete m_timer;
    
}

void Player::Update()
{
    if (m_spreadStatus.shotFlag)
    {
        m_shotDirector->SpreadShot(
            
            m_shotStatus.shotFlag,
            m_param.pos,
            m_shotStatus.shotDirection,
            m_shotStatus.shotSpeed,
            m_shotStatus.barrelLevel
        );
    }
    else if (m_shotStatus.shotFlag)
    {
        m_shotDirector->NormalShot(

            m_shotStatus.shotFlag,
            m_param.pos,
            m_shotStatus.shotDirection,
            m_shotStatus.shotSpeed,
            m_shotStatus.barrelLevel
        );
    }
    //�ˌ��֘A�̍X�V
    m_shotDirector->Update(
  );
    //�J�����Ƀv���C���[�̈ʒu��n��
    m_camera.SetPlayerPosition(GetPosition());
    //�J�����X�V
    m_camera.Update();
    
    //�V���b�g�֘A
    m_shotStatus.shotFlag = false;
    if (m_controller.IsPress(ButtonName::GAMEPAD_RIGHT_SHOULDER))
    {
        //�C���^�[�o����0�Ȃ�
        if (!m_shotStatus.shotFlag &&m_shotStatus.shotInterval==0)
        {
            //�T�E���h�ƃt���O����
            m_sound.Play(SoundType::ShootSE,false,true);
            //�V���b�g�t���O��Shotdirector�p
            m_shotStatus.shotFlag= true;
            m_shotStatus.shotInterval = SHOT_COOL_FLAME;
            
            //���S�����A�e���ˎ��̂݃A�j���[�V����
            m_cubeRotate+=30;
            if (m_cubeRotate>=360)
            {
                m_cubeRotate = 0;
            }
        }
    }
    //0�łȂ��Ȃ�
    if (m_shotStatus.shotInterval!=0)
    {
        //�J�E���g������
        m_shotStatus.shotInterval -= 10 + m_shotStatus.intervalCount;
        if (m_shotStatus.shotInterval <= 0)
        {
            m_shotStatus.shotInterval = 0;
        }
    }
    //�V���b�g�֘A
    m_spreadStatus.shotFlag = false;
    if (m_controller.GetTiggerInputR()>0.3f)
    {
        //�C���^�[�o����0�Ȃ�
        if (!m_spreadStatus.shotFlag && m_spreadStatus.shotInterval == 0)
        {
            //�T�E���h�ƃt���O����
            m_sound.Play(SoundType::ShootSE, false, true);
            //�V���b�g�t���O��Shotdirector�p
            m_spreadStatus.shotFlag = true;
            m_spreadStatus.shotInterval = SPREAD_COOL_FLAME;
            m_shotStatus.shotInterval = SPREAD_COOL_FLAME;
            //���S�����A�e���ˎ��̂݃A�j���[�V����
            m_cubeRotate += 30;
            if (m_cubeRotate >= 360)
            {
                m_cubeRotate = 0;
            }
        }
    }
    //0�łȂ��Ȃ�
    if (m_spreadStatus.shotInterval != 0)
    {
        //�J�E���g������
        m_spreadStatus.shotInterval -= 10 + m_spreadStatus.intervalCount;
        if (m_spreadStatus.shotInterval <= 0)
        {
            m_spreadStatus.shotInterval = 0;
        }
    }
    m_shield->Update(GetPosition());
   
    //�ړ��֘A
    Move();

    //�ˌ��̌����֘A
    TakeAim();

    //�ړ�����
    RestrictionsPosition();

    //�G�ɓ��������ۂ̏���
    //�q�b�g�X�g�b�v�����
    if (m_timer->CheakTime())
    {
        m_fps.SetFPS(60);
        m_isAlive = false;
    }
    
}

void Player::RestrictionsPosition()
{
    float x = GetPosition().x;
    float z = GetPosition().z;
    if (x<=-100)
    {
        m_param.pos=XMFLOAT3(-100, GetPosition().y, GetPosition().z);
    }
    if (x >= 100)
    {
        m_param.pos = XMFLOAT3(100, GetPosition().y, GetPosition().z);
    }
    if (z <= -100)
    {
        m_param.pos = XMFLOAT3(GetPosition().x, GetPosition().y, -100);
    }
    if (z >= 100)
    {
        m_param.pos = XMFLOAT3(GetPosition().x, GetPosition().y, 100);
    }
}


void Player::Draw()
{
    if (m_isAlive)
    {
        m_shotDirector->Draw();
        m_model.Draw(GetPosition(), atan2(m_playerDirection.x, m_playerDirection.z), PMDModelType::Player);
        m_model.Draw(XMF3Math::AddXMFLOAT3(GetPosition(),XMF3Math::SetMagnitude(m_shotStatus.shotDirection,-1)),XMF3Math::DegreeForRadian(m_cubeRotate), PMDModelType::PlayerCube);
       
        m_shield->Draw();
       
            

    }
}

void Player::Init()
{
    XMFLOAT3 posData=m_json.GetXMFLOAT3(JsonDataType::Player,"Position");
    int radiusData = m_json.GetInt(JsonDataType::Player, "Radius");

    //  �擾�����f�[�^�����ɏ�����
    SetPotision(posData);
    m_param.mCollision->m_data.radius=radiusData;
    m_isAlive = true;
}

void Player::OnCollisionEnter(Collision* otherCollision)
{
    if (otherCollision->GetTag() == CollisionTag::Enemy
        || otherCollision->GetTag() == CollisionTag::EnemyBullet)
    {
        OutputDebugString("HitEnemy.\n");
        m_effect.PlayEffect(EffectType::DefeatPlayer, GetPosition(), false);
        m_sound.Play(SoundType::DefeatEnemySE, false, true);

        //HitStop�݂����ȓ���
        m_fps.SetFPS(15);
        m_timer->SetTimer(0.3f);

        m_param.mCollision->m_isValidity = false;
    }
    if (otherCollision->GetTag() == CollisionTag::ReinforceShotInterval)
    {
        m_shotStatus.intervalCount +=3;
        m_spreadStatus.intervalCount +=8;
    }
    if (otherCollision->GetTag() == CollisionTag::ReinforceAddtoShot)
    {
        m_spreadStatus.barrelLevel++;
        m_shotStatus.barrelLevel++;
    }
    
}



void Player::Move()
{
    //�c�ړ��x�N�g��
    XMFLOAT3 inputVec(0,0,0);

    //�J��������O�������o��
    XMFLOAT3 Forward=XMF3Math::SubXMFLOAT3( m_param.pos,m_camera.GetPosition());
    //�O�����x�N�g���Ƃ��Ďg���������ߏ�̕����͂O�ɒu��������
    Forward.y = 0;
    //���K��
    Forward = XMF3Math::NormalizeXMFLOAT3(Forward);

    //�O�ς��牡�������o��
    XMFLOAT3 RIGHT = XMF3Math::CrossXMFLOAT3(XMFLOAT3(0,1,0),Forward);

    //�R���g���[���[�̓��͂Ɠ���
    XMFLOAT2 inputScalar = m_controller.GetLeftStickInput();

    // ������x�̓��͂̓f�b�h�]�[���Ƃ��Đ؂�̂Ă�
    //�}�C�i�X���͂ɑΉ����邽�߂ɐ�Βl�v�Z
    if (abs(inputScalar.x)<=DEADZONE)
    {
        inputScalar.x = 0;
    }
    if (abs(inputScalar.y)<= DEADZONE)
    {
        inputScalar.y = 0;
    }
    inputVec    =XMF3Math::AddXMFLOAT3(inputVec ,XMF3Math::ScalarXMFLOAT3(Forward, inputScalar.y));
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(RIGHT, inputScalar.x));
    MoveEffect(XMF3Math::LengthXMFLOAT3(inputVec));

    m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,inputVec);
}

void Player::TakeAim()
{
    //�c�ړ��x�N�g��
    XMFLOAT3 inputVec(0, 0, 0);

    //�J��������O�������o��
    XMFLOAT3 Forward = XMF3Math::SubXMFLOAT3(m_param.pos, m_camera.GetPosition());
    //�O�����x�N�g���Ƃ��Ďg���������ߏ�̕����͂O�ɒu��������
    Forward.y = 0;
    //���K��
    Forward = XMF3Math::NormalizeXMFLOAT3(Forward);

    //�O�ς��牡�������o��
    XMFLOAT3 RIGHT = XMF3Math::CrossXMFLOAT3(XMFLOAT3(0, 1, 0), Forward);

    //�R���g���[���[�̓��͂Ɠ���
    XMFLOAT2 inputScalar = m_controller.GetRightStickInput();
    if ((inputScalar.x<=0.5f&&inputScalar.x >=-0.5f)&& (inputScalar.y <= 0.5f && inputScalar.y >= -0.5f))
    {
        return;
    }
    
    
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(Forward, inputScalar.y));
    inputVec = XMF3Math::AddXMFLOAT3(inputVec, XMF3Math::ScalarXMFLOAT3(RIGHT, inputScalar.x));

    inputVec=XMF3Math::NormalizeXMFLOAT3(inputVec);
    m_playerDirection = inputVec;
    m_shotStatus.cosDirection = atan2(m_playerDirection.x, m_playerDirection.z);

    m_shotStatus.shotDirection = inputVec;
}

void Player::MoveEffect(const float _inputSize)
{
    m_inputFlameCount++;
    //�G�t�F�N�g�p�ړ��J�E���g��10�Ŋ����
    //���͂����ȏ�ŃG�t�F�N�g
    if (_inputSize>= DEADZONE&&(m_inputFlameCount%10)==0)
    {
        m_effect.PlayEffect(EffectType::PlayerMove,GetPosition(),false);
    }
}

