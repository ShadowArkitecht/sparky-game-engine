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
Private Methods
====================
*/
////////////////////////////////////////////////////////////
/// \brief Prints an empty line to the console window.
///
/// This method is used within the variadic error printing
/// methods to stop errors when using variadic templates.
///
////////////////////////////////////////////////////////////
inline void DebugLog::printLine()
{
	std::cout << std::endl;
}

////////////////////////////////////////////////////////////
/// \brief Prints the variable T to the console window.
///
/// Used by the variadic templated printing methods for printing
/// a single line to the console window.
///
/// \param line		The line to be printed to the console.
///
////////////////////////////////////////////////////////////
template <typename T>
inline void DebugLog::printLine(const T& line)
{
	std::cout << line << " ";
}

////////////////////////////////////////////////////////////
/// \brief Variadically prints lines to the console window.
///
/// Used for printing variadic amounts of lines to the console 
/// window. This method is utilised by the error and warning
/// methods so that all information can be displayed upon 
/// execution failure.
///
/// \param line		The first line to be printed to the console
/// \param args...	The variadic lines to be printed to the console.
///
////////////////////////////////////////////////////////////
template <typename T, typename... Args>
inline void DebugLog::printLine(const T& line, const Args&... args)
{
	std::cout << line << " ";
	printLine(args...);
}

////////////////////////////////////////////////////////////
/// \brief Sets the text colour for the next line of the console
///		   window.
///
/// \param colour	The colour of the new line.
///
////////////////////////////////////////////////////////////
inline void DebugLog::setTextColour(eConsoleTextColours colour)
{
#if _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
#endif
}
/*
====================
Public Methods
====================
*/
////////////////////////////////////////////////////////////
/// \brief Prints a blue message to the console window.
///
/// Messages can be used to print important statements to the
/// console window. They do not state any warnings or errors.
///
/// \param msg	The message to be printed to the console.
///
////////////////////////////////////////////////////////////
template <typename T>
inline void DebugLog::message(const T& msg)
{
	setTextColour(CONSOLE_TEXT_COLOUR_BLUE);
	std::cout << "MESSAGE: ";

	setTextColour(CONSOLE_TEXT_COLOUR_LIGHT_BLUE);
	printLine(msg);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);
}

////////////////////////////////////////////////////////////
/// \brief Variadically prints blue messages to the console window.
///
/// Messages can be used to print important statements to the
/// console window. They do not state any warnings or errors.
///
/// \param msg		The first message to be printed to the console.
/// \param ...args	The variadic message parameters to be printed to the console.
///
////////////////////////////////////////////////////////////
template<typename T, typename... Args>
inline void DebugLog::message(const T& msg, const Args&... args)
{
	setTextColour(CONSOLE_TEXT_COLOUR_BLUE);
	std::cout << "MESSAGE: ";

	setTextColour(CONSOLE_TEXT_COLOUR_LIGHT_BLUE);
	printLine(msg, args...);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);
}

////////////////////////////////////////////////////////////
/// \brief Prints an orange warning to the console window.
///
/// Warnings are used to print statements where the user
/// has made a non-fatal mistake during the application,
/// such as loading in the correct file with an incorrect
/// directory.
///
/// \param msg	The warning message to be printed to the console.
///
////////////////////////////////////////////////////////////
template <typename T>
inline void DebugLog::warning(const T& msg)
{
	setTextColour(CONSOLE_TEXT_COLOUR_RED);
	std::cout << "WARNING: ";

	setTextColour(CONSOLE_TEXT_COLOUR_YELLOW);
	printLine(msg);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);
}

////////////////////////////////////////////////////////////
/// \brief Variadically prints an orange warning to the console window.
///
/// Warnings are used to print statements where the user
/// has made a non-fatal mistake during the application,
/// such as loading in the correct file with an incorrect
/// directory.
///
/// \param msg		The first warning message to be printed to the console.
/// \param ...args	The variadic warnins to be printed to the console.
///
////////////////////////////////////////////////////////////
template<typename T, typename... Args>
inline void DebugLog::warning(const T& msg, const Args&... args)
{
	setTextColour(CONSOLE_TEXT_COLOUR_RED);
	std::cout << "WARNING: ";

	setTextColour(CONSOLE_TEXT_COLOUR_YELLOW);
	printLine(msg, args...);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);
}

////////////////////////////////////////////////////////////
/// \brief Prints an orange error message to the console window.
///
/// Errors are used to print statements where the user
/// has made a fatal mistake during the application,
/// such as OpenGL failing to initialise. The message will
/// be printed and the application is aborted.
///
/// \param msg	The error message to be printed to the console.
///
////////////////////////////////////////////////////////////
template<typename T>
inline void DebugLog::error(const T& msg)
{
	setTextColour(CONSOLE_TEXT_COLOUR_RED);
	std::cout << "ERROR: ";

	setTextColour(CONSOLE_TEXT_COLOUR_YELLOW);
	printLine(msg);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);

	getchar();
	exit(EXIT_FAILURE);
}

////////////////////////////////////////////////////////////
/// \brief Variadically prints an orange error message to the console window.
///
/// Errors are used to print statements where the user
/// has made a fatal mistake during the application,
/// such as OpenGL failing to initialise. The message will
/// be printed and the application is aborted.
///
/// \param msg		The first error message to be printed to the console.
/// \param ...args	The variadic errors to be printed to the console.
///
////////////////////////////////////////////////////////////
template<typename T, typename... Args>
inline void DebugLog::error(const T& msg, const Args&... args)
{
	setTextColour(CONSOLE_TEXT_COLOUR_RED);
	std::cout << "ERROR: ";

	setTextColour(CONSOLE_TEXT_COLOUR_YELLOW);
	printLine(msg, args...);
	std::cout << std::endl;

	setTextColour(CONSOLE_TEXT_COLOUR_DEFAULT);

	getchar();
	exit(EXIT_FAILURE);
}