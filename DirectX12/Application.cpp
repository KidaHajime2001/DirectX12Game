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
#include"GameLevel.h"
#include"Fade.h"
Application::Application()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_error(Singleton<Error>::GetInstance())
    , m_effect(Singleton<EffekseerManager>::GetInstance())
    , m_controller(Singleton<Controller>::GetInstance())
    , m_drawer(Singleton<StringDrawer>::GetInstance())
    , m_fps(Singleton<Fps>::GetInstance())
    , m_gamelevel(new GameLevel())
    /*, m_dxmng(Singleton<DirectXManager>::GetInstance)*/
{
    if (!m_device.Init())
    {
        return;
    }
    ShowWindow(m_device.hwnd, SW_SHOW);    //  ウィンドウ表示
    m_sceneBase = new Title(SceneTag::Title);
    m_sceneManager = new SceneManager();
    //  Effekseer関連初期化
    m_effect.Init();
    m_sceneBase->SetGameLevelClass(m_gamelevel);
}
Application::~Application()
{
    delete m_sceneManager;
    delete m_gamelevel;
}

void Application::Run()
{
	//  メッセージ格納変数
	MSG msg = {};
	//
    // 
     //  PMDモデルクラスのシングルトンインスタンス生成
    PMDModel& model = Singleton<PMDModel>::GetInstance();
    //  モデルを描画するための設定
    model.SetUp(1500);//描画数
     //  ESCキーが押されるまでループ
    while (!m_controller.IsPushEnter(ButtonName::GAMEPAD_START)) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //  もうアプリケーションが終わるって時にmessageがWM_QUITになる
        if (msg.message == WM_QUIT) {
            break;
        }

        //  エラーが発生したらループを抜ける
        if (m_error.IsOccurError())
        {
            return;
        }

       
        m_controller.Update();
        m_sceneBase->Update();
        m_fps.Update();


        //  全体の描画準備
        m_device.dx12->BeginDraw();

        //  PMDモデルクラスの更新
        
        m_sceneBase->DrawBackGround();
        //if (m_device.m_fade->GetState() != Fade::FadeState::Fadeing)
            //pmd
        {
            model.Update();
        }
        //  PipelineStateをPMD用に合わせる
        m_device.dx12->GetCommandList()->SetPipelineState(m_device.pmdRenderer->GetLinePipelineState());
        //  RootSignatureもPMD用に合わせる
        m_device.dx12->GetCommandList()->SetGraphicsRootSignature(m_device.pmdRenderer->GetRootSignature());
        m_device.dx12->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

        m_device.dx12->SetScene();
        m_sceneBase->DrawLine();
        m_device.dx12->GetCommandList()->SetPipelineState(m_device.pmdRenderer->GetPipelineState());
        m_device.dx12->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_device.dx12->SetScene();

        m_sceneBase->Draw();

        //文字
        {
            //  文字の描画をするための前準備
            m_device.dx12->GetCommandList()->SetDescriptorHeaps(1, m_device.heapForSpriteFont.GetAddressOf());
            m_device.spriteBatch->Begin(m_device.dx12->GetCommandList().Get());
            //シーンの文字表示
            m_sceneBase->DrawString();
            //m_fps.Draw();
            //  文字を描画した後の処理
            m_device.spriteBatch->End();
        }

        //エフェクト
        {
            //  エフェクトの描画
            m_effect.SyncronizeEffekseerCamera();
            m_effect.Draw();
        }
        Controller& controller = Singleton<Controller>::GetInstance();


        
        m_device.m_fade->Update();
        m_device.m_fade->Draw();
        


        //  描画の終了
        m_device.dx12->EndDraw();
        m_fps.Wait();
        {
            //  フリップ
            m_device.dx12->GetSwapchain()->Present(1, 0);
            m_device.gmemory->Commit(m_device.dx12->GetCmdQue());
        }
        
        if (m_sceneBase->GetNextSceneFlag())
        {
            
            if (m_device.m_fade->IsEnd())
            {
                //仮おき
                SceneBase* beforeScene = m_sceneBase;
                m_sceneBase = m_sceneManager->ScenePasser(m_sceneBase);
                if (!m_sceneBase)//nullptrでエラー吐いたら終了
                {
                    OutputDebugString("ScenePasserError");//出力にそう書く
                    return;
                }
                m_sceneBase->SetGameLevelClass(m_gamelevel);
                m_sceneBase->Init();
                delete beforeScene;//仮置きしておいたメモリを開放

                m_device.m_fade->FadeEnd();
            }

           

            m_device.m_fade->FadeStart();


            
        }
    }
    delete m_sceneBase;
    //  ゲーム終了処理
    m_device.Finalize();
    SingletonFinalizer::Finalize();

}
