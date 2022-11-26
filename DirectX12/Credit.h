#pragma once
#include"SceneBase.h"
class Credit : public SceneBase
{
public:
	Credit(SceneTag _sceneTag);
	~Credit();
	void Draw()override;
	void Update()override;
	void DrawString()override;;
private:
	void ChangeImageAlpha();
	class StringDrawer& m_drawer;
	class Controller& m_controller;
	class SpriteDrawer& m_sprite;
	class Sound& m_sound;
	const float DefaultalphaMax = 1.0f;
	const float DefaultalphaMin = 0.3f;
	const float ChangedalphaMin = 0.0f;
	float m_alphaValue;
	float Code;
	const float DELTA = 0.01f;
	bool m_decisionFlag;
};