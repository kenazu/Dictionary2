#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>

# include "Dictionary.h"
# include "ScrollBar.h"
# include "InputWord.h"

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

	InputWord input;

public:

	Test(const InitData& _init) :IScene(_init) 
	{
		FontAsset::Register(U"font", 40);
		input = InputWord(U"font", Size(300, 50));

	}

	void update()override
	{
		input.update();

		if (KeySpace.pressed())
		{
			input.setEnabled(false);
		}
		else
		{
			input.setEnabled(true);
		}
	}

	void draw()const override
	{
		ClearPrint();
		Print << U"hasChaged:" << input.hasChanged();
		Print << U"isEmpty:" << input.isEmpty();
		Print << U"isEnabled:" << input.isEnabled();

		input.draw(50, 50);
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

