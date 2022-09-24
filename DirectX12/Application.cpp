#include "Application.h"
#include"Singleton.h"
#include"SingletonFinalizer.h"
#include"D12Device.h"
#include<Windows.h>
#include"Error.h"
#include "PmdModel.h"
#include "ModelTypeData.h"
#include"Controller.h"
#include"Player.h"
#include"SceneBase.h"
#include"Title.h"
#include"Game.h"
#include"SceneManager.h"
#include"EffekseerMng.h"
#include"DirectXManager.h"
#include"StringDrawer.h"
#include"Fps.h"
Application::Application()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_error(Singleton<Error>::GetInstance())
    , m_effect(Singleton<EffekseerManager>::GetInstance())
    , m_controller(Singleton<Controller>::GetInstance())
    , m_drawer(Singleton<StringDrawer>::GetInstance())
    , m_fps(Singleton<Fps>::GetInstance())
    /*, m_dxmng(Singleton<DirectXManager>::GetInstance)*/
{
    if (!m_device.Init())
    {
        return;
    }
    ShowWindow(m_device.hwnd, SW_SHOW);    //  �E�B���h�E�\��
    m_sceneBase = new Title(SceneTag::Title);
    m_sceneManager = new SceneManager();
    //  Effekseer�֘A������
    m_effect.Init();
}
Application::~Application()
{
    delete m_sceneBase;
}

void Application::Run()
{
	//  ���b�Z�[�W�i�[�ϐ�
	MSG msg = {};
	//
    // 
     //  PMD���f���N���X�̃V���O���g���C���X�^���X����
    PMDModel& model = Singleton<PMDModel>::GetInstance();
    //  ���f����`�悷�邽�߂̐ݒ�
    model.SetUp(1500);//�`�搔
     //  ESC�L�[���������܂Ń��[�v
    while (!m_controller.IsPushEnter(ButtonName::GAMEPAD_START)) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //  �����A�v���P�[�V�������I�����Ď���message��WM_QUIT�ɂȂ�
        if (msg.message == WM_QUIT) {
            break;
        }

        //  �G���[�����������烋�[�v�𔲂���
        if (m_error.IsOccurError())
        {
            return;
        }
        m_controller.Update();
        m_sceneBase->Update();
        m_fps.Update();
        /*if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_LEFT))
        {
            m_fps.SetFPS(15);
        }
        if (m_controller.GetControllerButtonState(ButtonName::GAMEPAD_RIGHT))
        {
            m_fps.SetFPS(60);
        }*/


        //  �S�̂̕`�揀��
        m_device.dx12->BeginDraw();
        m_sceneBase->DrawBackGround();
        //pmd
        {
            //  PipelineState��PMD�p�ɍ��킹��
            m_device.dx12->GetCommandList()->SetPipelineState(m_device.pmdRenderer->GetPipelineState());
            //  RootSignature��PMD�p�ɍ��킹��
            m_device.dx12->GetCommandList()->SetGraphicsRootSignature(m_device.pmdRenderer->GetRootSignature());
            m_device.dx12->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            m_device.dx12->SetScene(); 
            //  PMD���f���N���X�̍X�V
            model.Update();
            m_sceneBase->Draw();
        }

        //����
        {
             //  �����̕`������邽�߂̑O����
            m_device.dx12->GetCommandList()->SetDescriptorHeaps(1, m_device.heapForSpriteFont.GetAddressOf());
            m_device.spriteBatch->Begin(m_device.dx12->GetCommandList().Get());
            //�V�[���̕����\��
            m_sceneBase->DrawString();
            //m_fps.Draw();
            //  ������`�悵����̏���
            m_device.spriteBatch->End();
        }

        //�G�t�F�N�g
        {
            //  �G�t�F�N�g�̕`��
            m_effect.SyncronizeEffekseerCamera();
            m_effect.Draw();
        }

        //  �`��̏I��
        m_device.dx12->EndDraw();
        m_fps.Wait();
        {
            //  �t���b�v
            m_device.dx12->GetSwapchain()->Present(1, 0);
            m_device.gmemory->Commit(m_device.dx12->GetCmdQue());
        }
        if (m_sceneBase->GetNextSceneFlag())
        {
            //������
            SceneBase* beforeScene = m_sceneBase;
            m_sceneBase = m_sceneManager->ScenePasser(m_sceneBase);
            if (!m_sceneBase)//nullptr�ŃG���[�f������I��
            {
                OutputDebugString("ScenePasserError");//�o�͂ɂ�������
                return;
            }

            delete beforeScene;//���u�����Ă��������������J��
        }
    }
    
    //  �Q�[���I������
    m_device.Finalize();
    SingletonFinalizer::Finalize();

}
