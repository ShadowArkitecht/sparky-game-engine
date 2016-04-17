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
#include <fstream>					// Loads in the configuration file, similar to a txt file.
#include <sstream>					// Creating string values from variables read in from the file.
#include <string>
/*
====================
Class Includes
====================
*/
#include <sparky\utils\config.hpp>	// Class definition.
#include <sparky\utils\debug.hpp>  // Printing warnings and errors to the console screen.

namespace sparky
{
	/*
	====================
	Constant Variables
	====================
	*/
	const char COMMENT_SYMBOL = '#';
	const int UNDEFINED = -1;

	/*
	====================
	Ctor and Dtor
	====================
	*/
	ConfigFile::ConfigFile(void)
		: m_values()
	{
	}

	ConfigFile::~ConfigFile(void)
	{
		m_values.clear();
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	int ConfigFile::getInt(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "int"));

		if (itr != m_values.end())
		{
			std::stringstream ss(itr->second.getCString());
			int value = 0;
			ss >> value;

			return value;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return 0;
	}

	unsigned int ConfigFile::getUInt(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "uint"));

		if (itr != m_values.end())
		{
			std::stringstream ss(itr->second.getCString());
			int value = 0;
			ss >> value;

			return value;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return 0;
	}

	bool ConfigFile::getBoolean(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "bool"));

		if (itr != m_values.end())
		{
			if (itr->second.getLength() == 5)
			{
				return false;
			}

			return true;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return false;
	}


	float ConfigFile::getFloat(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "float"));

		if (itr != m_values.end())
		{
			std::stringstream ss(itr->second.getCString());
			float value = 0.0f;
			ss >> value;

			return value;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return 0.0f;
	}

	double ConfigFile::getDouble(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "double"));

		if (itr != m_values.end())
		{
			std::stringstream ss(itr->second.getCString());
			double value = 0.0;
			ss >> value;

			return value;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return 0.0;
	}

	String ConfigFile::getString(const String& variable) const
	{
		auto itr = m_values.find(std::make_pair(variable, "string"));

		if (itr != m_values.end())
		{
			return itr->second;
		}

		DebugLog::warning(variable, ": incorrect variable name or datatype");
		return "";
	}

	/*
	====================
	Private Methods
	====================
	*/
	void ConfigFile::removeComments(String& line)
	{
		for (unsigned int i = 0; i < line.getLength(); i++)
		{
			if (line[i] == COMMENT_SYMBOL)
			{
				line = line.substring(0, i);
				line.trim();

				break;
			}
		}
	}

	/*
	====================
	Methods
	====================
	*/
	bool ConfigFile::open(const String& fileName)
	{
		//checks that config file has the correct file extension
		if (!fileName.endsWith(".scfg"))
		{
			DebugLog::error(fileName, "has incorrect file extension");
			return false;
		}

		std::ifstream file;

		file.open(fileName.getCString(), std::ios::in | std::ios::binary);
		//checks if the file has successfully opened or not
		if (file.fail())
		{
			DebugLog::error(fileName, "configuration has failed to open.");
			return false;
		}

		String currentLine;
		String section;

		int lineNumber = 1;

		while (file.good())
		{
			String::getline(file, currentLine);
			//remove whitespace and carriage returns from the current line
			currentLine.trim();
			//if the current line is empty, it will not parse it
			if (currentLine.isEmpty() || currentLine[0] == '\0')
			{
				lineNumber++;
				continue;
			}
			//checks if the current line is a comment, it will not parse it
			if (currentLine[0] == COMMENT_SYMBOL)
			{
				lineNumber++;
				continue;
			}
			//if the current line being checked is an initialisation of a section
			if (currentLine[0] == '[')
			{
				//it substracts two in order to skip the terminator and closing square bracket
				section = currentLine.substring(1, currentLine.getLength() - 1);
				lineNumber++;
				continue;
			}
			//set to undefined as if they stay as this value, the current line read has not been parsed correctly
			int namePos = UNDEFINED;
			int dataPos = UNDEFINED;
			//loops through the current string and records the positions where name and datatype start
			for (unsigned int i = 0; i < currentLine.getLength(); i++)
			{
				if (currentLine[i] == ':' && namePos == UNDEFINED)
				{
					namePos = i;
				}
				else if (currentLine[i] == '=' && dataPos == UNDEFINED)
				{
					dataPos = i;
				}
			}
			//if the positions are undefined, there is undefined behaviour or errors on the current line in the config file
			if (namePos == UNDEFINED || dataPos == UNDEFINED)
			{
				DebugLog::warning("Error parsing line", lineNumber, ": ", currentLine);
				lineNumber++;
				continue;
			}
			//stores the variable name from the current line and forces all letters to be lower-case
			String variable = currentLine.substring(0, namePos).toLower();
			//stores the data type from the current line and forces all letters to be lower-case
			String datatype = currentLine.substring(namePos + 1, dataPos).toLower();
			//stores the value from the current line
			String value = currentLine.substring(dataPos + 1, currentLine.getLength());

			//remove any potential inline comments next to the value
			this->removeComments(value);

			//if the variable is not in the global section of the config file, add it to the current set section
			if (!section.isEmpty())
			{
				String s = section + "." + variable;
				variable = s;
			}
			//checks to see if the current variable being parsed has already been declared within the config file
			bool contained = false;
			for (const auto& itr : m_values)
			{
				//checks to see if it matches any of the current variables
				if (itr.first.first == variable)
				{
					DebugLog::warning(variable, "has already been declared within the config file", lineNumber, "will not be parsed");
					contained = true;
				}
			}
			//if a variable is already in the config file, the current line is not parsed
			if (contained)
			{
				lineNumber++;
				continue;
			}

			auto isDigit = [](const char* pLine)
			{
				std::string line = pLine;
				return line.find_first_not_of("-.0123456789") == std::string::npos;
			};

			//all number based values are checked to make sure they contain numbers and not undefined information
			//if any of do contain undefined behaviour, they are not parsed from the config file
			if ((datatype == "int" || datatype == "uint" || datatype == "float" || datatype == "double") 
					&& !isDigit(value.getCString()))
			{
				DebugLog::warning(variable, "on line", lineNumber, "is not an integer value");
				lineNumber++;
				continue;
			}

			else if (datatype == "bool")
			{
				if (value != "false" && value != "true")
				{
					DebugLog::warning(variable, "on line", lineNumber, "is not set to a correct boolean expression");
					lineNumber++;
					continue;
				}
			}
			//string is checked to make sure that it follows the convention of opening and closing speech marks
			else if (datatype == "string")
			{
				char begin = value[0];
				char end = value[value.getLength() - 1];

				if (begin != '\"' || end != '\"')
				{
					DebugLog::warning(variable, "on line", lineNumber, "is not a correctly formatted string");
					lineNumber++;
					continue;
				}
				else
				{
					value = value.substring(1, value.getLength() - 1);
				}
			}
			//if none of the previous statements and check fail, then the current variable, its datatype and value are added to the map
			m_values.insert(std::make_pair(std::make_pair(variable, datatype), value));
			lineNumber++;
		}
		//closes the file as the class is done from reading from it
		file.close();
		return true;
	}

}//namespace sparky