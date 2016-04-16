#ifndef __SPARKY_DEBUG_LOG_HPP__
#define __SPARKY_DEBUG_LOG_HPP__

/*
====================
CPP Includes
====================
*/
#ifdef _WIN32
#include <Windows.h>	// Window specific functionality. Used to change the colour of console statements.
#endif
#include <iostream>		// Printing messages to the console window.
#include <conio.h>		// Awaiting keyboard input from user.
#include <cstdlib>		// Exiting the application.

namespace sparky
{
	class DebugLog final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		enum eConsoleTextColours
		{
			CONSOLE_TEXT_COLOUR_DEFAULT = 7,
			CONSOLE_TEXT_COLOUR_BLUE = 1,
			CONSOLE_TEXT_COLOUR_LIGHT_BLUE = 9,
			CONSOLE_TEXT_COLOUR_YELLOW = 14,
			CONSOLE_TEXT_COLOUR_RED = 4,
			CONSOLE_TEXT_COLOUR_WHITE = 15
		};

	private:
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
		void printLine(void);

		////////////////////////////////////////////////////////////
		/// \brief Prints the variable T to the console window.
		///
		/// Used by the variadic templated printing methods for printing
		/// a single line to the console window.
		///
		/// \param line		The line to be printed to the console.
		///
		////////////////////////////////////////////////////////////
		template <typename T> static void printLine(const T& line);

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
		template <typename T, typename... Args> static void printLine(const T& line, const Args&... args);

		////////////////////////////////////////////////////////////
		/// \brief Sets the text colour for the next line of the console
		///		   window.
		///
		/// \param colour	The colour of the new line.
		///
		////////////////////////////////////////////////////////////
		static void setTextColour(eConsoleTextColours colour);

	public:
		/*
		====================
		Methods
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
		template <typename T> static void message(const T& msg);

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
		template <typename T, typename... Args> static void message(const T& msg, const Args&... args);

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
		template <typename T> static void warning(const T& msg);

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
		template <typename T, typename... Args> static void warning(const T& msg, const Args&... args);

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
		template <typename T> static void error(const T& error);

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
		template <typename T, typename... Args> static void error(const T& msg, const Args&... args);
	};

#include <sparky\utils\debug.inl>

}//namespace sparky

#endif//__SPARKY_DEBUG_LOG_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::DebugLog
///	\ingroup utils
///
/// sparky::DebugLog is a static class responsible for the
/// printing of warnings and errors that may occur throughout
/// the applications lifetime.
///
/// Each method is variadic and can be used to print infinite
/// amounts of error messages to the console window. DebugLog
/// is used throughout the application and be used by the user
/// with the following code.
///
/// \code
/// // Declare a integer
/// int number = 5;
///
/// // Provide pointless error checking to said integer
/// if (number == 5)
/// {
///		// Print a warning message
///		sparky::DebugLog::warning("Number shouldn't equal 5");
/// }
///
////////////////////////////////////////////////////////////