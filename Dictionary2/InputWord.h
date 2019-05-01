#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.3.2


class InputWord
{
	String m_text;
	
	String m_fontName;

	Size m_size;
	bool m_hasChanged = false;

	KeyConjunction m_pasteKey;
	KeyConjunction m_deleteKey;

	bool m_isEnabled = false;

public:

	InputWord() = default;

	InputWord(const String& _fontName, const Size& _size, bool _enabled = true):
		m_fontName(_fontName),m_size(_size),
		m_hasChanged(false),m_isEnabled(_enabled), 
		m_pasteKey(KeyControl + KeyV),
		m_deleteKey(KeyControl + KeyD)
	{

	}

	void clear() { m_text.clear(); }

	void setEnabled(bool _enabled)
	{
		m_isEnabled = _enabled;
	}

	String getText()const { return m_text; }
	bool hasChanged()const { return m_hasChanged; }

	bool isEmpty()const { return m_text.isEmpty(); }

	bool isEnabled()const { return m_isEnabled; }

	void update()
	{
		m_hasChanged = false;

		if (!m_isEnabled) { return; }
		if (KeyTab.pressed()) { return; }


		const String preText = m_text;

		if (m_pasteKey.down())
		{
			String clipboardText;

			if (Clipboard::GetText(clipboardText))
			{
				m_text += clipboardText;
			}
		}

		else if (m_deleteKey.down())
		{
			clear();
		}
		else
		{
			TextInput::UpdateText(m_text);
		}

		if (m_text != preText)
		{
			m_hasChanged = true;
		}

	}

	void draw(const Point& _pos)const
	{
		const Point textOffset = _pos.movedBy(10, 0);

		//ògÇÃï`âÊ
		Rect(_pos, m_size).drawFrame(2, 0, m_isEnabled ? Palette::Blue : Palette::Black);
		FontAsset(m_fontName)(m_text).draw(textOffset, Palette::Black);

		if (!m_isEnabled) { return; }

		//ì_ñ≈Ç∑ÇÈÉJÅ[É\ÉãÇÃï`âÊ
		const Rect wordRegion = FontAsset(m_fontName)(m_text).region(_pos.movedBy(10, 0));
		const Point cursorPos = textOffset.movedBy(wordRegion.w, 0);
		const int offsetY = 5;

		if (InRange<int>(Time::GetMillisec() % 1500, 0, 750))
		{
			Rect(cursorPos.movedBy(5, offsetY), Size(3, m_size.y - offsetY * 2)).draw(Palette::Black);
		}
	}

	void draw(int _x, int _y)const { draw(Point(_x, _y)); }
	
};