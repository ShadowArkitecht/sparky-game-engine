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

#ifndef __SPARKY_CONFIG_FILE_HPP__
#define __SPARKY_CONFIG_FILE_HPP__

/*
====================
CPP Includes
====================
*/
#include <map>						// The values of the configuration file are stored and retrieved from a map.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// Needed for searching for variables within the configuration file.

namespace sparky
{
	class ConfigFile final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::map<std::pair<String, String>, String> m_values;	// The mapped values which are read and then stored from the configuration file.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Removes any comments from the current line.
		///
		/// When a line is parsed from the config file, if the line 
		/// itself is a comment or there is an in-line comment on 
		/// the current line, it is removed from the parser.
		///
		/// \param line		The current line to check.
		///
		////////////////////////////////////////////////////////////
		void removeComments(String& line);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Config file.
		///
		/// The constructor for the config file only sets the member
		/// variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit ConfigFile(void);

		////////////////////////////////////////////////////////////
		/// \brief Default desctruction of the Config file.
		///
		/// Destructs the config file and clears the map of stored
		/// values.
		///
		////////////////////////////////////////////////////////////
		~ConfigFile(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves an int variable from the config file.
		///
		/// Retrieves an integer value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window and 0
		/// is returned.
		///
		/// \param variable		The name of the variable within the file.
		///
		/// \retval int			The value of the variable.
		///
		////////////////////////////////////////////////////////////
		int getInt(const String& variable) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves an unsigned int variable from the config file.
		///
		/// Retrieves an unsigned integer value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window and 0
		/// is returned.
		///
		/// \param variable		  The name of the variable within the file.
		///
		/// \retval unsigned int  The value of the variable.
		///
		////////////////////////////////////////////////////////////
		unsigned int getUInt(const String& variable) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves an boolean variable from the config file.
		///
		/// Retrieves a boolean value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window and false
		/// is returned.
		///
		/// \param variable		The name of the variable within the file.
		///
		/// \retval int			The value of the variable.
		///
		////////////////////////////////////////////////////////////
		bool getBoolean(const String& variable) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a float variable from the config file.
		///
		/// Retrieves an float value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window and 0
		/// is returned.
		///
		/// \param variable		The name of the variable within the file.
		///
		/// \retval int			The value of the variable.
		///
		////////////////////////////////////////////////////////////
		float getFloat(const String& variable) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves an double variable from the config file.
		///
		/// Retrieves an double value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window and 0
		/// is returned.
		///
		/// \param variable		The name of the variable within the file.
		///
		/// \retval int			The value of the variable.
		///
		////////////////////////////////////////////////////////////
		double getDouble(const String& variable) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves an string variable from the config file.
		///
		/// Retrieves a string value (by name) from the configuration
		/// file. If the value within the configuration is not found,
		/// a warning message is presented to the console window an empty
		/// string is returned.
		///
		/// \param variable		The name of the variable within the file.
		///
		/// \retval int			The value of the variable.
		///
		////////////////////////////////////////////////////////////
		String getString(const String& variable) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Opens and loads the configuration file.
		///
		/// Opens and loads the selected configuration file and stores all the 
		/// variables within the Config File object map. The variables and their 
		/// values can be retrieved by utilising the getter methods. If the file 
		/// contains an incorrectly formatted line, an error message is presented 
		/// to the console with a message indicating the mistake. 
		///
		/// \param fileName  The file location of the configuration file to load.
		///
		/// \retval bool Returns true if the file opened and parsed with no errors or syntax errors.
		///
		////////////////////////////////////////////////////////////
		bool open(const String& fileName);
	};

}//namespace sparky

#endif//__SPARKY_CONFIG_FILE_HPP__

////////////////////////////////////////////////////////////
/// \class spark::ConfigFile
/// \ingroup utils
///
/// sparky::Configfile is a configuration file parsing class
/// for loading and storing the variables of custom sparky
/// configuration files (.SCFG). These configuration files
/// can be used for the loading of Window and Camera variables.
///
/// The configuration files are useful for quickly changing 
/// values without re-compilation. Below is a small code example:
///
/// \code
/// // Create and load the configuration file.
/// sparky::ConfigFile file;
/// file.open("data/config.scfg");
///
/// // Print the values of the Window.
/// std::cout << file.getInt("Window.position_x") << std::endl;
/// std::cout << file.getBool(Window.full_screen") << std::endl;
/// std::cout << file.getString("Window.title") << std::endl;
///
////////////////////////////////////////////////////////////