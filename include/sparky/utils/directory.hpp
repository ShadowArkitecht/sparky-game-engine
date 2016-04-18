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

#ifndef __SPARKY_DIRECTORY_HPP__
#define __SPARKY_DIRECTORY_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>					// Storage container for the files of the directory.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// The files are stored as Strings.

namespace sparky
{
	struct Directory final
	{
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<String> files;	// The files contained within the directory.

		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Directory object.
		///
		/// The default construction of the Directory object just sets
		/// the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit Directory(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Directory object.
		////////////////////////////////////////////////////////////
		~Directory(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Opens the specified file directory.
		///
		/// When the directory is opened, it checks to see if the 
		/// directory is a valid location. If it is, all of the files 
		/// are stored within the objects vector. 
		///
		/// \param directory	The directory to open.
		///
		/// \retval bool		True if the directory opened and loaded
		///						correctly. False if there were any issues.
		///
		////////////////////////////////////////////////////////////
		bool open(const String& directory);
	};

}//namespace sparky

#endif//__SPARKY_DIRECTORY_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Directory
///	\ingroup utils
///
/// sparky::Directory is used to open a folder directory and 
/// load the files contains within said directory. This struct
/// can be used to load all images within an assets folder, instead
/// of calling each individually. 
///
/// The Directory object provides additional error checking
/// to make sure that the directory exists and the files can be 
/// loaded. Below is a code exmaple:
///
/// \code
/// // Create a Directory object and opens a directory.
/// sparky::Directory directory;
/// directory.open("assets");
///
/// // Store the images loaded into the ResourceManager
/// ResourceManager::addTexture(directory.files);
///
////////////////////////////////////////////////////////////