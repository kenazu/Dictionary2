#pragma once
# include <Siv3D.hpp>// OpenSiv3D v0.3.2
# include <HamFramework.hpp>

# include "Dictionary.h"
# include "ScrollBar.h"
# include "InputWord.h"
# include "KeyScroller.h"

namespace GameInfo
{
	//const String FirstScene = U"SearchScene";
	const String FirstScene = U"Test";
}

struct GameData
{

};

using MyApp = SceneManager<String, GameData>;

class Empty :public MyApp::Scene
{
	void updateFadeIn(double)override
	{
		changeScene(GameInfo::FirstScene, 0);
	}

public:

	Empty(const InitData& _init) :IScene(_init){}

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

