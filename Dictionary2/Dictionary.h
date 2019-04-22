#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.3.2

//«‘‚Ì‰p“ú‚ÌƒyƒA
//first  = English
//second = Japanese 
using WordPair = std::pair<String, String>;

class Dictionary
{
	Array<WordPair> m_datas;


public:

	Dictionary() {}

	Dictionary(const FilePath& _path)
	{
		load(_path);
	}
	
	bool load(const FilePath& _path)
	{
		CSVData reader(_path);

		if (reader.isEmpty()) { return false; }

		m_datas.clear();

		for (size_t row = 0; row < reader.rows(); row++)
		{
			if (reader.columns(row) == 2)
			{
				const auto english = reader.getOr<String>(row, 0, U"");
				const auto japanese = reader.getOr<String>(row, 1, U"");

				add(english,japanese);
			}
		}

		return true;
	}

	bool save(const FilePath& _path)
	{
		CSVData writer;

		for (const auto& data : m_datas)
		{
			writer.writeRow(data.first,data.second);
		}

		return writer.save(_path);
	}

	void add(const WordPair& _data)
	{
		m_datas.push_back(_data);
	}

	void add(const String& _english, const String& _japanese)
	{
		add(WordPair(_english, _japanese));
	}

	void adds(const Array<WordPair>& _datas)
	{
		for (const auto& d : _datas)
		{
			add(d);
		}
	}

	void sortEnglish()
	{
		const auto compareFunc = [](const WordPair & _a, const WordPair & _b) {return _a.first < _b.first; };
		std::sort(m_datas.begin(), m_datas.end(), compareFunc);
	}

	void sortLowerEnglish()
	{
		const auto compareFunc = [](const WordPair & _a, const WordPair & _b) {return _a.first.lowercased() < _b.first.lowercased(); };
		std::sort(m_datas.begin(), m_datas.end(), compareFunc);
	}

	void sortJapanese()
	{
		const auto compareFunc = [](const WordPair & _a, const WordPair & _b) {return _a.second < _b.second; };
		std::sort(m_datas.begin(), m_datas.end(), compareFunc);
	}

	Array<WordPair> getDatas()const
	{
		return m_datas;
	}

	Array<WordPair> search(const String& _searchWord)const
	{
		Array<WordPair> result;

		for (const auto& data : m_datas)
		{
			if (matchWord(_searchWord.lowercased(),data.first.lowercased()))
			{
				result.push_back(data);
			}
		}

		return result;
	}

	bool matchWord(const String& _searchWord, const String& _matchWord)const
	{
		if (_searchWord.length() > _matchWord.length()) { return false; }

		for (unsigned int i = 0; i < _searchWord.length(); i++)
		{
			if (_searchWord[i] != _matchWord[i])
			{
				return false;
			}
		}

		return true;
	}
};