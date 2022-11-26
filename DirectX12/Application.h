#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Application
{
public:
	//‰Šú‰»
	Application();
	
	//‰ğ•ú
	~Application();
	
	//Às
	void Run();

private:

	//class FontWriter* m_fontWriter;

	//class Input&				m_Input;
	class D12Device&			m_device;
	class Fps&					m_fps;
	class EffekseerManager&		m_effect;
	class Error&				m_error;
	class Controller&			m_controller;
	class SceneBase*			m_sceneBase;
	class SceneManager*			m_sceneManager;
	class StringDrawer&			m_drawer;
	class GameLevel* m_gamelevel;
	/*class DirectXManager&		m_dxmng;*/
	float x, y, z;
	float fov = 45;
};

