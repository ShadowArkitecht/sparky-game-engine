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

#ifndef __SPARKY_STRING_HPP__
#define __SPARKY_STRING_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>	// Storage type for each character in the string.
#include <iostream>	// Printing out the string to the console screen.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class String;

	////////////////////////////////////////////////////////////
	/// \brief Operator for printing the contents of the String object to the console.
	/// 
	/// The user can prints the contents of the String to the 
	/// console window using the standard io within C++.
	/// 
	/// \param os		The stream that the string is being streamed into.
	/// \param string	The string to be streamed into the buffer.
	/// 
	/// \retval ostream A reference to the buffer stream.
	///
	////////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& os, const String& string);

	class String final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<char> m_data;	// Raw data of each character within the string.

	private:
		////////////////////////////////////////////////////////////
		/// \brief Inserts a null terminator.
		///
		/// This will insert a null termination character at the end
		/// of the current String object. Whenever the size or contents
		/// of the string is manipulated, this method is subsequently
		/// called to ensure correct termination.
		///
		////////////////////////////////////////////////////////////
		void nullTerminator(void);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a String object.
		///
		/// The default constructor creates a new String object with
		/// an empty array of characters.
		///
		////////////////////////////////////////////////////////////
		String(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a String object with a character array.
		///
		/// When the string is constructed, it is populated with the 
		/// contents of character pointer passed in as the parameter.
		/// To ensure correct behaviour, a null terminator is added
		/// to the end of the character array.
		///
		/// \param pData	The character data to populate the string.
		///
		////////////////////////////////////////////////////////////
		String(const char* pData);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the String object.
		///
		/// The String object destructor will clear the current
		/// character array and de-allocate the memory.
		///
		////////////////////////////////////////////////////////////
		~String(void);

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Performs an assignment operator from a "c-style" string.
		/// 
		/// \param pStr		The "c-style" string to convert.
		///
		/// \retval String&	A reference to this String object.
		///
		////////////////////////////////////////////////////////////
		String& operator=(const char* pStr);

		////////////////////////////////////////////////////////////
		/// \brief Performs a member-wise concatenation of two Strings.
		/// 
		/// When the user adds two String objects together, the result
		/// is concatenated and the two String are added to the same
		/// object and returned as a new instance.
		///
		/// \param string	The String object to be concatenated.
		///
		/// \retval String	The concatenation of two Strings.
		///
		////////////////////////////////////////////////////////////
		String operator+(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Performs a member-wise concatenation of an individual character.
		/// 
		/// Similar to the previous concatenation method, this operator
		/// will concatenate the single letter onto the end of the current
		/// String object and returned as an instance.
		///
		/// \param letter	The character to be added.
		///
		/// \retval String	Member-wise concatenation of a String and letter.
		///
		////////////////////////////////////////////////////////////
		String operator+(const char letter) const;

		////////////////////////////////////////////////////////////
		/// \brief performs a member-wise concatenation of two Strings, and assigns 
		///		   the result to the current String object.
		/// 
		/// When the user adds two String objects together, the result
		/// is concatenated and the two String are added to the same
		/// object. The result is assigned to this String object.
		///
		/// \param string	The String to be added.
		///
		/// \retval String	Member-wise concatenation of two String objects.
		///
		////////////////////////////////////////////////////////////
		const String& operator+=(const String& string);

		////////////////////////////////////////////////////////////
		/// \brief Performs a member-wise addition of a String and a 
		///		   character, and assigns the result to the String object.
		/// 
		/// Similar to the previous concatenation method, this operator
		/// will concatenate the single letter onto the end of the current
		/// String object and assign it to this String object.
		///
		/// \param letter	The character to be concatenated.
		///
		/// \retval String	Member-wise concatenation of a String and character.
		///
		////////////////////////////////////////////////////////////
		const String& operator+=(const char letter);

		////////////////////////////////////////////////////////////
		/// \brief Equality operator between two different String objects.
		/// 
		/// This will compare two different String objects. If they are
		/// identical to one another, the method will return true.
		///
		///	\param string The String to compare against.
		///
		/// \retval bool  True if the String objects are equal. False
		///				  if not.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Non-equality operator between two String instances.
		/// 
		/// This will compare two different String object. If they are
		/// not the same, the method will return true.
		///
		/// \param string	The String to compare against.
		///
		/// \retval bool	True if the String objects are not equal.
		///					False if not.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Compares two different String object and tests whether the 
		///		   object is less than the string parameter.
		///
		/// \param string	The string to compare against.
		///
		/// \retval bool	True if the object is less than the String 
		///					parameter. False if not.
		///
		////////////////////////////////////////////////////////////
		bool operator<(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Compares two different String object and tests whether the 
		///		   object is greater than the string parameter.
		///
		/// \param string	The string to compare against.
		///
		/// \retval bool	True if the object is greater than the String 
		///					parameter. False if not.
		///
		////////////////////////////////////////////////////////////
		bool operator>(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets a character within the String object.
		/// 
		/// This operator will retrieve the character at the given
		/// index of String object if it is not out of scope.
		///
		/// \param index	The index.
		///
		///	\retval char	A character at the specified index.
		///
		////////////////////////////////////////////////////////////
		char operator[](const unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets a character within the String object.
		/// 
		/// This operator will retrieve the character at the given
		/// index of String object if it is not out of scope.
		///
		/// \param index	The index.
		///
		///	\retval char	A character at the specified index.
		///
		////////////////////////////////////////////////////////////
		char& operator[](const unsigned int index);

		////////////////////////////////////////////////////////////
		/// \brief Hashes the String object for use within maps and hash tables.
		/// 
		/// \param key		The key of the hash table.
		///
		/// \retval uint	A hashed String uint variable.
		///
		////////////////////////////////////////////////////////////
		std::size_t operator()(const String& key) const;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Gets the current length of the String object.
		/// 
		/// The length of the String object is one less than the actual
		/// size, this is because the length ignores the null
		/// terminator which suffixes the String.
		/// 
		/// \retval uint	The length of the String object.
		///
		////////////////////////////////////////////////////////////
		unsigned int getLength(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the current size of the String object.
		/// 
		/// The size of the String object includes its overall length
		/// and the null terminator which suffixes the object.
		/// 
		/// \retval uint	The size of the String object.
		///
		////////////////////////////////////////////////////////////
		unsigned int getSize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Checks whether the string is empty.
		///
		/// The string object can only be empty if it contains no
		/// characters or the null terminator. isEmpty can provide
		/// additional error checking before any String manipulation.
		///
		/// \retval bool	True if the String object is empty. False
		///					if not.
		///
		////////////////////////////////////////////////////////////
		bool isEmpty(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the underlying "c-style" string of the String object.
		///
		/// This will convert the current String object to a "c-style" 
		/// string. This is used to provide communication with external
		/// libraries or API's, so that sparky::String can still be used.
		///
		/// \retval char*	The underlying String object character array.
		///
		////////////////////////////////////////////////////////////
		const char* getCString(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Reads a line from a standard I/O file and assigns it to 
		///        the target String object.
		///
		/// This method provides the functionality to use the String object
		/// with standard I/O file reading. This is used extensively in
		/// the sparky::Config class.
		///
		/// \param is		The I/O file being read.
		/// \param target	The target that the file line is being assigned to.
		///
		/// \retval istream Returns the current file being read.
		///
		////////////////////////////////////////////////////////////
		static std::istream& getline(std::istream& is, String& target);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Removes a character at the specified index of the String object.
		///
		/// Removes a character at the specified index, if it is within
		/// scope.
		///
		/// \param index	The index to remove.
		///
		////////////////////////////////////////////////////////////
		void remove(const unsigned int index);

		/////////////////////////////////////////////////////////////
		/// \brief Removes a string of characters from the String object.
		/// 
		/// This will remove all instances of characters from the String 
		/// object that match any of the characters in the String parameter.
		///
		/// \param characters	The characters to remove
		///
		////////////////////////////////////////////////////////////
		void remove(const String& characters);

		////////////////////////////////////////////////////////////
		/// \brief Clears the current String object of all characters.
		///
		/// Clearing allows for the re-use of String objects, without
		/// having to create new instances on the stack or heap.
		///
		////////////////////////////////////////////////////////////
		void clear(void);

		////////////////////////////////////////////////////////////
		/// \brief Identical to the Addition operators. Will append a String
		///		   onto this String object.
		///
		/// Appending is adding one string to the end of another. The same
		/// functionality is provided with the addition operators, although
		/// this provides a more clear indication on what is occuring to the
		/// String object.
		///
		/// \param string	The string to be appended
		///
		////////////////////////////////////////////////////////////
		void append(const String& string);

		////////////////////////////////////////////////////////////
		/// \brief Forces all characters in the String object to become lower-case.
		///
		///	\retval String	Returns a copy of this object.
		///
		////////////////////////////////////////////////////////////
		String toLower(void);

		////////////////////////////////////////////////////////////
		/// \brief Forces all characters in the String instance to become upper-case.
		/// 
		///	\retval String	Returns a copy of this object.
		///
		////////////////////////////////////////////////////////////
		String toUpper(void);

		////////////////////////////////////////////////////////////
		/// \brief Removes all trailing characters from the String object.
		///
		/// Trimming refers to removing characters that cannot be 
		/// typically seen by the user, this includes the null terminator,
		/// new lines and tabs.
		///
		////////////////////////////////////////////////////////////
		void trim(void);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the String object begins with a sequence of
		///		   characters.
		///
		/// This will test whether the String object begins with the string parameter, 
		/// the check is type-sensitive and will return true if they are identical.
		///
		/// \param string	The string that the object may begin with.
		///
		/// \retval bool	True if the String instance begins with the string parameter.
		///					False if not.
		///
		////////////////////////////////////////////////////////////
		bool beginsWith(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the String object ends with a sequence of
		///		   characters.
		///
		/// This will test whether the String object ends with the string parameter, 
		/// the check is type-sensitive and will return true if they are identical.
		///
		/// \param string	The string that the object may end with.
		///
		/// \retval bool	True if the String instance ends with the string parameter.
		///					False if not.
		///
		////////////////////////////////////////////////////////////
		bool endsWith(const String& string) const;

		////////////////////////////////////////////////////////////
		/// \brief Extracts a String from the String object.
		///
		/// Extracts a String from the specified String object by defining 
		/// an end and start point for extraction. If the end point is beyond 
		/// the scope of the String, the end point will be the last element
		/// of the string.
		/// 
		/// \param start	The start point for extraction.
		/// \param end		The end point for extraction.
		///
		/// \retval String	The specified substring of the String object.
		///
		////////////////////////////////////////////////////////////
		String substring(const unsigned int start, const unsigned int end) const;

		////////////////////////////////////////////////////////////
		/// \brief Swaps two String objects.
		///
		/// This method will swap the contents of two different
		/// String objects around.
		///
		/// \param string	The string to swap with.
		///
		////////////////////////////////////////////////////////////
		void swap(String& string);

		////////////////////////////////////////////////////////////
		/// \brief Concatenating a single string onto another.
		///
		/// Concatenation is similar to appending, the String is added
		/// onto the assigned object, the differences is that infinite
		/// amounts of string can be concatenated onto the returned object.
		///
		/// \param first	The first object to concatenated.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		static String concat(const T& first);

		////////////////////////////////////////////////////////////
		/// \brief Concatenating variadic amount of strings onto another.
		///
		/// Concatenation is similar to appending, the String is added
		/// onto the assigned object, the differences is that infinite
		/// amounts of string can be concatenated onto the returned object.
		///
		/// \param first	The first object to concatenated.
		/// \param args		The variadic objects to concatenate.
		///
		////////////////////////////////////////////////////////////
		template <typename T, typename... Args>
		static String concat(const T& first, const Args&... args);
	};

	////////////////////////////////////////////////////////////
	/// \brief Operator for printing the contents of the String object to the console.
	/// 
	/// The user can prints the contents of the String to the 
	/// console window using the standard io within C++.
	/// 
	/// \param os		The stream that the string is being streamed into.
	/// \param string	The string to be streamed into the buffer.
	/// 
	/// \retval ostream A reference to the buffer stream.
	///
	////////////////////////////////////////////////////////////
	inline std::ostream& operator<<(std::ostream& os, const String& string)
	{
		return os << string.getCString();
	}

	////////////////////////////////////////////////////////////
	/// \brief Concatenating a single string onto another.
	///
	/// Concatenation is similar to appending, the String is added
	/// onto the assigned object, the differences is that infinite
	/// amounts of string can be concatenated onto the returned object.
	///
	/// \param first	The first object to concatenated.
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	static String String::concat(const T& first)
	{
		return String(first);
	}

	////////////////////////////////////////////////////////////
	/// \brief Concatenating variadic amount of strings onto another.
	///
	/// Concatenation is similar to appending, the String is added
	/// onto the assigned object, the differences is that infinite
	/// amounts of string can be concatenated onto the returned object.
	///
	/// \param first	The first object to concatenated.
	/// \param args		The variadic objects to concatenate.
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename... Args>
	static String String::concat(const T& first, const Args&... args)
	{
		return String(first) + concat(args...);
	}

}//namespace sparky

#endif//__SPARKY_STRING_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::String
///	\ingroup utils
///
/// sparky::String is a basic re-implementation of C++ string
/// class specifically made for easily functionality with
/// Sparky. A sparky::String is container for a vector of
/// characters that can be easily manipulated without dynamic
/// allocation.
///
/// sparky::String contains several methods for simple
/// manipulation of characters; such as concatenation, easy
/// deletion and per index alterations. Below is an example:
///
/// \code 
/// // Declare a string
/// sparky::String str = "Hello";
///
/// // Append another string onto str
/// str.append(" World!");
///
/// // Store a substring of str
/// sparky::String sub = str.substring(0, 5);
///
/// // Delete the l letters in str
/// str.remove("l");
///
/// // Print the strings to the console
/// std::cout << str << std::endl;
/// std::cout << sub << std::endl;
///
////////////////////////////////////////////////////////////