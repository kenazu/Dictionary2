#pragma once
# include "SceneBase.h"
# include "InputWord.h"
# include "Dictionary.h"
# include "KeyScroller.h"
# include "Table.h"
# include "ScrollBar.h"

class SearchScene :public ScrollScene
{
	InputWord m_inputWord;
	KeyScroller m_keyScroller;
	ScrollBar m_scrollBar;


	Dictionary m_dictionary;
	Table m_table;

	int m_initIdx = 0;
	Array<WordPair> m_searchResult;

	void setSearchResult(const Array<WordPair>& _result)
	{
		m_initIdx = 0;
		m_searchResult = _result;
		m_scrollBar.setRangeEnd(m_searchResult.size() - 1);
		m_scrollBar.setValue(m_initIdx);
	}

	void search()
	{
		if (m_inputWord.getText().isEmpty())
		{
			setSearchResult(m_dictionary.getDatas());
			return;
		}

		setSearchResult(m_dictionary.search(m_inputWord.getText()));
	}

	void scrollTable()
	{
		const int move = m_keyScroller.getKeyMove() + static_cast<int>(Mouse::Wheel());

		//キー入力があるときは開始インデックスの値を入力分増減する
		//スクロールバーの位置をm_initIdxに応じて変更する
		if (move != 0)
		{
			m_initIdx += move;
			m_initIdx = Clamp<int>(m_initIdx, 0, m_searchResult.size() - 1);
			m_scrollBar.setValue(m_initIdx);
		}
		//キー入力がないときは開始インデックスの値をスクロールバーの位置にする
		else
		{
			m_initIdx = Clamp<int>(m_scrollBar.getValue(), 0, m_searchResult.size() - 1);
		}
	}

	void loadFromConfig()
	{
		TextReader reader(U"config");

		String line;
		while (reader.readLine(line))
		{
			if (FileSystem::IsFile(line) && FileSystem::Extension(line) == U"csv")
			{
				m_dictionary.load(line);
			}
			else
			{
				Print << line <<  U"is not found or not csv";
			}
		}
	}

public:

	SearchScene(const InitData& _init) :ScrollScene(_init)
	{
		m_inputWord = InputWord(U"wordFont", Size(300, 50));
		m_keyScroller = KeyScroller(KeyDown, KeyUp);
		m_dictionary = Dictionary();
		m_table = Table();
		m_scrollBar = ScrollBar(0, 0, Point(610, 100), Size(20, 300));

		loadFromConfig();
		m_dictionary.sortLowerEnglish();

		search();
	}

	void update()override
	{
		m_keyScroller.update();
		m_inputWord.update();
		m_scrollBar.update();

		scrollTable();


		if (m_inputWord.hasChanged())
		{
			search();
		}

		updateScrollScene();
	}

	void draw()const override
	{
		m_inputWord.draw(50, 20);
		Line(0, 90, Window::Width(), 90).draw(Palette::Black);
		m_table.draw(Point(10, 100), m_searchResult, m_initIdx);
		m_scrollBar.draw();
	}
};
