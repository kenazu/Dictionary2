# include <Siv3D.hpp> // OpenSiv3D v0.3.2
# include "SceneBase.h"
# include "SearchScene.h"
# include "AddWordScene.h"

void Main()
{
	Graphics::SetBackground(Palette::White);

	Window::SetTitle(U"辞書");
	Window::Resize(640, 480);

	FontAsset::Register(U"wordFont", 35);
	FontAsset::Register(U"tableNumFont", 15);
	FontAsset::Register(U"tableFont", 20);

	MyApp manager;
	manager.add<Empty>(U"Empty");
	manager.add<SearchScene>(U"SearchScene");
	manager.add<AddWordScene>(U"AddWordScene");
	manager.add<Test>(U"Test");


	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}