#pragma once
# include <Siv3D.hpp>// OpenSiv3D v0.3.2

//�L�[�����������邱�Ƃň��Ԋu�Œl��������N���X
class KeyScroller
{
	Key m_plusKey;
	Key m_minusKey;

	int m_keyMove = 0;

	int m_intervalCount = 0;
	int m_INTERVAL = 0;

	int m_speedUpCount = 0;
	int m_SPEED_UP = 0;

public:

	KeyScroller() = default;

	KeyScroller(const Key& _plusKey, const Key& _minusKey) :
		m_plusKey(_plusKey), m_minusKey(_minusKey),
		m_keyMove(0), m_intervalCount(0), m_INTERVAL(8),
		m_speedUpCount(0),m_SPEED_UP(5) {}

	void update()
	{
		m_keyMove = 0;

		const int keyMove = m_plusKey.pressed() - m_minusKey.pressed();

		//���񐔈ȏ㑝�������瑝���Ԋu���������Ȃ�
		if (m_speedUpCount >= m_SPEED_UP)
		{
			m_intervalCount -= 2;
		}
		else
		{
			m_intervalCount--;
		}

		//���͂�����Ƃ����Ԋu�Œl�𑝌�������
		if (keyMove != 0 && m_intervalCount <= 0)
		{
			m_keyMove += keyMove;
			m_intervalCount = m_INTERVAL;
			m_speedUpCount++;
		}

		//�L�[�𗣂����烊�Z�b�g
		if (m_plusKey.up() || m_minusKey.up())
		{
			m_intervalCount = 0;
			m_speedUpCount = 0;
		}
	}

	int getKeyMove()const
	{
		return m_keyMove;
	}

};