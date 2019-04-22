#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>

# include "Dictionary.h"

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
	Dictionary dictionary;

	Array<WordPair> datas;

public:

	Test(const InitData& _init) :IScene(_init) 
	{
		dictionary = Dictionary(U"test.csv");
		dictionary.sortLowerEnglish();
		datas = dictionary.getDatas();
	}

	void update()override
	{
		if (KeySpace.down())
		{
			datas = dictionary.search(U"");
		}
		if (KeyS.down())
		{
			datas = dictionary.search(U"a");
		}
	}

	void draw()const override
	{
		ClearPrint();

		for (const auto& data : datas)
		{
			Print << U"[" << data.first << U"," << data.second << U"]";
		}
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

