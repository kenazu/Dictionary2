#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.3.2


class ScrollBar
{
	Point m_pos;
	Size m_size;

	Rect m_knob;

	//value�͈̔�
	int m_rangeBegin;
	int m_rangeEnd;

	//�o�[�̈ʒu���狁�߂��l(range�͈̔͂̒l)
	int m_value;

	bool m_isGrabbed;

	

	std::pair<int, int> getKnobYRange()const
	{
		const int rangeBegin = getBarColider().pos.y;
		const int rangeEnd = getBarColider().pos.y + getBarColider().size.y - m_knob.size.y;
		return std::make_pair(rangeBegin,rangeEnd);
	}

	//�m�u�̈ʒu�X�V
	//�͈͂�ύX������Ăяo��
	void setKnob()
	{
		//�m�u�̍����͑S�̂̍�����1/3~1�{
		const float divideNum = Clamp<float>((m_rangeEnd - m_rangeBegin + 1) / 1.7f, 1.0f, 3.0f);
		const int sizeY = static_cast<int>(m_size.y / divideNum);
		m_knob = Rect(m_pos, m_size.x, sizeY);
	}

public:

	ScrollBar() = default;

	ScrollBar(int _begin, int _end, const Point& _pos, const Size& _size) :
		m_rangeBegin(_begin), m_rangeEnd(_end),
		m_pos(_pos), m_size(_size), m_knob(_pos,_size),
		m_isGrabbed(false), m_value(_begin)
	{
		setKnob();
	}


	void setValue(int _value)
	{
		if (!InRange(_value, m_rangeBegin, m_rangeEnd) || m_rangeBegin == m_rangeEnd)
		{
			return;
		}

		m_value = _value;

		//�m�u���o�[�̂ǂ̂��炢�̈ʒu�ɂ��邩
		const float scale = static_cast<float>(m_value - m_rangeBegin) / (m_rangeEnd - m_rangeBegin);

		m_knob.pos.y = m_pos.y + static_cast<int>(scale * (m_size.y - m_knob.size.y));
	}

	void setRangeBegin(int _begin)
	{
		if (m_rangeEnd < _begin)
		{
			m_rangeBegin = m_rangeEnd;
		}
		else
		{
			m_rangeBegin = _begin;
		}

		//�͈͕ύX�����̂Ńm�u�̈ʒu���X�V
		setKnob();
		//value���͈͓��Ɏ��܂�悤�ɂ���
		setValue(Clamp(m_value, m_rangeBegin, m_rangeEnd));
	}

	void setRangeEnd(int _end)
	{
		if (m_rangeBegin > _end)
		{
			m_rangeEnd = m_rangeBegin;
		}
		else
		{
			m_rangeEnd = _end;
		}

		//�͈͕ύX�����̂Ńm�u�̈ʒu���X�V
		setKnob();
		//value���͈͓��Ɏ��܂�悤�ɂ���
		setValue(Clamp(m_value, m_rangeBegin, m_rangeEnd));
	}

	int getValue()const
	{
		return m_value;
	}

	Rect getBarColider()const
	{
		return Rect(m_pos, m_size);
	}

	int getRangeBegin()const { return m_rangeBegin; }
	int getRangeEnd()const { return m_rangeEnd; }

	//value�𑝌�������
	void move(int _move)
	{
		if (_move == 0 || m_isGrabbed) { return; }

		setValue(m_value + _move);
	}

	void update()
	{
		if (getBarColider().mouseOver() && MouseL.down())
		{
			m_isGrabbed = true;
		}

		else if (MouseL.up())
		{
			m_isGrabbed = false;
		}

		if (m_isGrabbed && m_rangeBegin != m_rangeEnd)
		{
			m_knob.setCenter(static_cast<int>(m_knob.center().x), Cursor::Pos().y);

			//�m�u���o�[�͈͓̔��Ɏ��܂�悤�ɏC������
			m_knob.pos.y = Clamp(m_knob.pos.y, getKnobYRange().first, getKnobYRange().second);

			//�m�u�̈ʒu����value��ݒ肷��
			const float scale = static_cast<float>(m_knob.pos.y - m_pos.y) / (m_size.y - m_knob.size.y);
			m_value = m_rangeBegin + static_cast<int>(scale * (m_rangeEnd - m_rangeBegin));

		}
	}

	void draw()const
	{
		Rect(m_pos, m_size).drawFrame(0, 2, Palette::Black);
		m_knob.draw(Palette::Gray);
	}

};