#pragma once
# include "SceneBase.h"

class AddWordScene :public ScrollScene
{

public:

	AddWordScene(const InitData& _init) :ScrollScene(_init) {}

	void update()override
	{
		updateScrollScene();
	}

	void draw()const override
	{

	}
};
