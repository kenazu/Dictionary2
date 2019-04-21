#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>

namespace GameInfo
{
	const String FirstScene = U"SearchScene";
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

