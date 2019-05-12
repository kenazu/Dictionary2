#pragma once
# include <Siv3D.hpp>// OpenSiv3D v0.3.2
# include <HamFramework.hpp>

# include "Dictionary.h"
# include "ScrollBar.h"
# include "InputWord.h"
# include "KeyScroller.h"


struct SceneData
{
	Array<String> sceneNames = { U"SearchScene",U"AddWordScene" };
	int sceneIdx = 0;

	void changeIdx(int _move)
	{
		sceneIdx += _move;

		if (sceneIdx < 0)
		{
			sceneIdx = static_cast<int>(sceneNames.size() - 1);
		}
		else if (sceneIdx > sceneNames.size() - 1)
		{
			sceneIdx = 0;
		}
	}

	String getSceneName()const
	{
		return sceneNames[sceneIdx];
	}
};

using MyApp = SceneManager<String, SceneData>;

class Empty :public MyApp::Scene
{
	void updateFadeIn(double)override
	{
		getData().changeIdx(1);
		changeScene(getData().getSceneName(), 0);
	}

public:

	Empty(const InitData& _init) :IScene(_init){}

};

class ScrollScene :public MyApp::Scene
{
	KeyConjunction m_scrollLeftKey = KeyConjunction(KeyControl, KeyLeft);
	KeyConjunction m_scrollRightKey = KeyConjunction(KeyControl, KeyRight);
	

protected:

	bool downScrollLeftKey()const
	{
		return m_scrollLeftKey.down();
	}

	bool downScrollRightKey()const
	{
		return m_scrollRightKey.down();
	}

	bool scrollLeft()
	{
		getData().changeIdx(-1);
		return changeScene(getData().getSceneName(), 500);
	}

	bool scrollRight()
	{
		getData().changeIdx(-1);
		return changeScene(getData().getSceneName(), 500);
	}

	void updateScrollScene()
	{
		if (downScrollLeftKey())
		{
			scrollLeft();
		}
		else if (downScrollRightKey())
		{
			scrollRight();
		}
	}

public:

	ScrollScene(const InitData& _init) :IScene(_init) {}
};

class Test :public MyApp::Scene
{
	KeyScroller scroller;
	int count = 0;

public:

	Test(const InitData& _init) :IScene(_init) 
	{
		scroller = KeyScroller(KeyDown, KeyUp);
	}

	void update()override
	{
		scroller.update();
		count += scroller.getKeyMove();
	}

	void draw()const override
	{
		ClearPrint();
		Print << count;
	}
};

/*
# include "SceneBase.h"

class SceneName :public MyApp::Scene
{
public:

	SceneName(const InitData& _init) :IScene(_init){}

	void update()override
	{

	}

	void draw()const override
	{

	}
};

----------------------------------

MyApp manager;
manager.add<Empty>(U"Empty");

*/

