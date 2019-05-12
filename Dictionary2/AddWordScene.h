#pragma once
# include "SceneBase.h"
# include "Dictionary.h"
# include "InputWord.h"
# include "Table.h"
# include "KeyScroller.h"

class AddWordScene :public ScrollScene
{
	Table m_table;
	KeyScroller m_keyScroller;
	ScrollBar m_scrollBar;

	Array<WordPair> m_inputDatas;

	KeyConjunction m_addKey = KeyConjunction(KeyControl, KeyEnter);
	KeyConjunction m_saveKey = KeyConjunction(KeyControl, KeyS);

	int m_cursor = 0;
	int m_initIdx = 0;

	void scrollTable()
	{
		m_scrollBar.update();

		const int move = m_keyScroller.getKeyMove() + static_cast<int>(Mouse::Wheel());

		//キー入力があるときは開始インデックスの値を入力分増減する
		//スクロールバーの位置をm_initIdxに応じて変更する
		if (move != 0)
		{
			m_initIdx += move;
			m_initIdx = Clamp<int>(m_initIdx, 0, static_cast<int>(m_inputDatas.size() - 1));
			m_scrollBar.setValue(m_initIdx);
		}
		//キー入力がないときは開始インデックスの値をスクロールバーの位置にする
		else
		{
			m_initIdx = Clamp<int>(m_scrollBar.getValue(), 0, static_cast<int>(m_inputDatas.size() - 1));
		}
	}

	void addData(const String& _english, const String& _japanese)
	{
		m_inputDatas.push_back(WordPair(_english,_japanese));
		m_initIdx = 0;
		m_scrollBar.setRangeEnd(m_inputDatas.size() - 1);
		m_scrollBar.setValue(m_initIdx);
	}

public:

	AddWordScene(const InitData& _init) :ScrollScene(_init)
	{
		m_table = Table();
		m_keyScroller = KeyScroller(KeyDown, KeyUp);
		m_scrollBar = ScrollBar(0, 0, Point(610, 100), Size(20, 300));
	}

	void update()override
	{
		m_keyScroller.update();
		m_scrollBar.update();

		scrollTable();

		if (KeySpace.down())
		{
			addData(U"a", U"a");
		}

		updateScrollScene();
	}

	void draw()const override
	{
		Line(0, 90, Window::Width(), 90).draw(Palette::Black);
		m_table.draw(Point(10, 100), m_inputDatas, m_initIdx);
		m_scrollBar.draw();
	}
};
