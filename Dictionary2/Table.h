#pragma once
# include <Siv3D.hpp>// OpenSiv3D v0.3.2
# include "Dictionary.h"

class Table
{
	String m_NUM_FONT_NAME = U"tableNumFont";
	String m_CHAR_FONT_NAME = U"tableFont";

	Size m_cellSize = Size(280, 30);
	Size m_numCellSize = Size(30, m_cellSize.y);
	Size m_tableSize = Size(2, 10);

	Point m_fontOffset = Point(5, 0);

public:

	Table() {}

	Table(const Size& _tableSize) :m_tableSize(_tableSize) {}

	void draw(const Point& _pos, const Array<WordPair>& _data, size_t _initIdx = 0)const
	{
		//�c��
		Line(0, 0, 0, m_numCellSize.x * m_tableSize.y).movedBy(_pos).draw(Palette::Black);

		for (int x = 0; x <= m_tableSize.x; x++)
		{
			Line(m_cellSize.x * x, 0, m_cellSize.x * x, m_cellSize.y * m_tableSize.y).movedBy(_pos).movedBy(m_numCellSize.x, 0).draw(Palette::Black);
		}

		//����
		for (int y = 0; y <= m_tableSize.y; y++)
		{
			Line(0, m_cellSize.y * y, m_cellSize.x * m_tableSize.x + m_numCellSize.x, m_cellSize.y * y).movedBy(_pos).draw(Palette::Black);
		}


		for (size_t i = 0; i < static_cast<size_t>(m_tableSize.y) && i + _initIdx < _data.size(); i++)
		{
			FontAsset(m_NUM_FONT_NAME)(i + _initIdx + 1).drawAt(_pos.movedBy(0, m_numCellSize.y * i).movedBy(m_numCellSize / 2), Palette::Black);
			FontAsset(m_CHAR_FONT_NAME)(_data[i + _initIdx].first).draw(_pos.movedBy(0, m_cellSize.y * i).movedBy(m_cellSize.y, 0).movedBy(m_fontOffset), Palette::Black);
			FontAsset(m_CHAR_FONT_NAME)(_data[i + _initIdx].second).draw(_pos.movedBy(m_cellSize.x, m_cellSize.y * i).movedBy(m_cellSize.y, 0).movedBy(m_fontOffset), Palette::Black);
		}
	}

};