///////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Sparky Engine
// 2016 - Benjamin Carter (benjamin.mark.carter@hotmail.com)
// 
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgement
//    in the product documentation would be appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
====================
CPP Includes
====================
*/
#include <algorithm>				// Transform needed for forcing all letters to upper or lower case.
#include <cctype>					// Lambda functions passed into std::transform.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// Class definiton.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	String::String(void)
		: m_data()
	{
	}

	////////////////////////////////////////////////////////////
	String::String(const char* pData)
		: m_data()
	{
		m_data.clear();
		m_data.assign(pData, pData + strlen(pData));
		// Insert terminator.
		nullTerminator();
	}

	////////////////////////////////////////////////////////////
	String::~String(void)
	{
		m_data.clear();
	}

	/*
	====================
	Operators
	====================
	*/
	String& String::operator=(const char* pStr)
	{
		m_data.clear();
		m_data.assign(pStr, pStr + strlen(pStr));
		// Insert terminator.
		nullTerminator();

		return *this;
	}

	////////////////////////////////////////////////////////////
	String String::operator+(const String& string) const
	{
		String result = *this;

		result.append(string);

		return result;
	}

	////////////////////////////////////////////////////////////
	String String::operator+(const char letter) const
	{
		String result = *this;

		result.remove(getLength());
		result.m_data.push_back(letter);
		result.nullTerminator();

		return result;
	}

	////////////////////////////////////////////////////////////
	const String& String::operator+=(const String& string)
	{
		append(string);

		return *this;
	}

	////////////////////////////////////////////////////////////
	const String& String::operator+=(const char letter)
	{
		if (!isEmpty())
		{
			remove(getLength());
		}

		m_data.push_back(letter);
		nullTerminator();

		return *this;
	}

	////////////////////////////////////////////////////////////
	bool String::operator==(const String& string) const
	{
		return m_data == string.m_data;
	}

	////////////////////////////////////////////////////////////
	bool String::operator!=(const String& string) const
	{
		return !(*this == string);
	}

	////////////////////////////////////////////////////////////
	bool String::operator<(const String& string) const
	{
		return strcmp(getCString(), string.getCString()) < 0;
	}

	////////////////////////////////////////////////////////////
	bool String::operator>(const String& string) const
	{
		return strcmp(getCString(), string.getCString()) > 0;
	}

	////////////////////////////////////////////////////////////
	char String::operator[](const unsigned int index) const
	{
		return m_data[index];
	}

	////////////////////////////////////////////////////////////
	char& String::operator[](const unsigned int index)
	{
		return m_data[index];
	}

	////////////////////////////////////////////////////////////
	std::size_t String::operator()(const String& key) const
	{
		std::size_t value = 0;

		for (char c : key.m_data)
		{
			value = 37 * value + c;
		}

		return value;
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	unsigned int String::getLength(void) const
	{
		return m_data.size() - 1;
	}

	////////////////////////////////////////////////////////////
	unsigned int String::getSize(void) const
	{
		return m_data.size();
	}

	////////////////////////////////////////////////////////////
	bool String::isEmpty(void) const
	{
		return m_data.empty();
	}

	////////////////////////////////////////////////////////////
	const char* String::getCString(void) const
	{
		return &m_data[0];
	}

	////////////////////////////////////////////////////////////
	std::istream& String::getline(std::istream& is, String& target)
	{
		char next;

		if (!target.isEmpty())
		{
			target.clear();
		}

		while (is.get(next))
		{
			target += next;

			if (next == '\n' || is.eof())
			{
				break;
			}
		}

		return is;
	}

	/*
	====================
	Private Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void String::nullTerminator(void)
	{
		if (m_data.back() != '\0')
		{
			m_data.push_back('\0');
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void String::remove(const unsigned int index)
	{
		m_data.erase(m_data.begin() + index);
	}

	////////////////////////////////////////////////////////////
	void String::remove(const String& characters)
	{
		for (const auto& c : characters.m_data)
		{
			m_data.erase(std::remove(m_data.begin(), m_data.end(), c), m_data.end());
		}
	}

	////////////////////////////////////////////////////////////
	void String::clear(void)
	{
		m_data.clear();
	}

	////////////////////////////////////////////////////////////
	void String::append(const String& string)
	{
		//remove the null terminator, don't one of these hanging around the middle of the vector
		if (!string.isEmpty())
		{
			if (!isEmpty())
			{
				//remove the null terminator
				remove(getLength());
			}

			m_data.insert(m_data.end(), string.m_data.begin(), string.m_data.end());

			nullTerminator();
		}
	}

	////////////////////////////////////////////////////////////
	String String::toLower(void)
	{
		std::transform(m_data.begin(), m_data.end(), m_data.begin(), std::tolower);
		return *this;
	}

	////////////////////////////////////////////////////////////
	String String::toUpper(void)
	{
		std::transform(m_data.begin(), m_data.end(), m_data.begin(), std::toupper);
		return *this;
	}

	////////////////////////////////////////////////////////////
	void String::trim(void)
	{
		m_data.erase(std::remove(m_data.begin(), m_data.end(), ' '), m_data.end());
		m_data.erase(std::remove(m_data.begin(), m_data.end(), '\r'), m_data.end());
		m_data.erase(std::remove(m_data.begin(), m_data.end(), '\t'), m_data.end());
		m_data.erase(std::remove(m_data.begin(), m_data.end(), '\n'), m_data.end());
	}

	////////////////////////////////////////////////////////////
	bool String::beginsWith(const String& begin) const
	{
		return begin.getSize() < this->getSize() && std::equal(begin.m_data.begin(), begin.m_data.end() - 1, m_data.begin());
	}

	////////////////////////////////////////////////////////////
	bool String::endsWith(const String& end) const
	{
		return end.getSize() < this->getSize() && std::equal(end.m_data.rbegin(), end.m_data.rend(), m_data.rbegin());
	}

	////////////////////////////////////////////////////////////
	String String::substring(const unsigned int start, const unsigned int end) const
	{
		String sub;

		sub.m_data.resize(end - start + 1);
		memcpy(&sub.m_data[0], getCString() + start, end - start);

		sub.nullTerminator();

		return sub;
	}

	////////////////////////////////////////////////////////////
	void String::swap(String& other)
	{
		m_data.swap(other.m_data);
	}
}