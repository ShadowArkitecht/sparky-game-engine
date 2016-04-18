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
#include <dirent.h>						// *nix for loading directories.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\directory.hpp>	// Class definition.
#include <sparky\utils\debug.hpp>		// Error checking for loading directories.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Directory::Directory(void)
		: files()
	{
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	bool Directory::open(const String& directory)
	{
		DIR* pDir = nullptr;
		dirent *pDirent = nullptr;

		// Open the directory.
		pDir = opendir(directory.getCString());

		// Error check the directories to make sure it exists.
		if (!pDir)
		{
			DebugLog::warning(directory, "is an incorrect file directory.");
			return false;
		}
		
		// Read all the files within the directory.
		while (pDirent = readdir(pDir))
		{
			// Make sure the files can be read.
			if (!pDirent)
			{
				DebugLog::warning("Failed to read files within directory.");
				return false;
			}

			// Push the files into the vector if they are not the directory links.
			if (pDirent->d_name[0] != '.')
			{
				files.push_back(pDirent->d_name);
			}
		}

		// Close the directory after use.
		closedir(pDir);
		return true;
	}

}//namespace sparky