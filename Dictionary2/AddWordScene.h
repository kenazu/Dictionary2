#pragma once
# include "SceneBase.h"


class AddWordScene :public MyApp::Scene
{
	KeyConjunction m_scrollRightKey = KeyConjunction(KeyControl, KeyRight);
	KeyConjunction m_scrollLeftKey = KeyConjunction(KeyControl, KeyLeft);


public:

	AddWordScene(const InitData& _init) :IScene(_init) {}

	void update()override
	{
		if (m_scrollLeftKey.down() || m_scrollRightKey.down())
		{
			changeScene(U"SearchScene", 500);
		}
	}

	void draw()const override
	{

	}
};
