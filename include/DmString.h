// Adapted by Demi3D in 2006. Updated for the cross-platform restoration.

// Copyright (C) 2002-2006 Nikolaus Gebhardt
// This file is originally part of the "Irrlicht Engine" by Nikolaus Gebhart

/*
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Please note that the Irrlicht Engine is based in part on the work of the 
  Independent JPEG Group, the zlib and the libPng. This means that if you use
  the Irrlicht Engine in your product, you must acknowledge somewhere in your
  documentation that you've used the IJG code. It would also be nice to mention
  that you use the Irrlicht Engine, the zlib and libPng. See the README files 
  in the jpeglib, the zlib and libPng for further informations.
*/

#ifndef __DmString__
#define __DmString__

#include "DmTypes.h"
#include "DmArray.h"

namespace demi
{

template <class T>
class string
{
public:

	//! Default constructor
	string()
	: allocated(1), used(1), s_array(0)
	{
		s_array = new T[1];
		s_array[0] = 0x0;
	}



	//! Constructor
	string(const string<T>& other)
	: allocated(0), used(0), s_array(0)
	{
		*this = other;
	}


	//! Constructs a string from an int
	string(int number)
	: allocated(0), used(0), s_array(0)
	{
		// store if negative and make positive

		bool negative = false;
		if (number < 0)
		{
			number *= -1;
			negative = true;
		}

		// temporary buffer for 16 numbers

		char tmpbuf[16];
		tmpbuf[15] = 0;
		sig idx = 15;	

		// special case '0'

		if (!number) 
		{
			tmpbuf[14] = '0';
			*this = &tmpbuf[14];
			return;
		}

		// add numbers

		while(number && idx)
		{
			idx--;	
			tmpbuf[idx] = (char)('0' + (number % 10));
			number = number / 10;					
		}

		// add sign

		if (negative)
		{
			idx--;
			tmpbuf[idx] = '-';			
		}

		*this = &tmpbuf[idx];
	}



	//! Constructor for copying a string from a pointer with a given lenght
	template <class B>
	string(const B* c, sig lenght)
	: allocated(0), used(0), s_array(0)
	{
		if (!c)
			return;

        allocated = used = lenght+1;
		s_array = new T[used];

		for (sig l = 0; l<lenght; ++l)
			s_array[l] = (T)c[l];

		s_array[lenght] = 0;
	}



	//! Constructor for unicode and ascii strings
	template <class B>
	string(const B* c)
	: allocated(0), used(0), s_array(0)
	{
		*this = c;
	}



	//! destructor
	~string()
	{
		delete [] s_array;
	}


	array<string<T>> split(const T delim)
	{
		array<string<T>> arr;
		if(findFirst(delim) > -1)
		{
			string<T> buf = *this;
			while(buf.size() > 0)
			{
				string<T> spl;
				int f = buf.findFirst(delim);
				if(f == -1)
				{
					spl = buf;
					buf = "";
				}
				else
				{
					spl = buf.subString(0,f);
					buf = buf.subString(f+1,buf.size()-(f+1));
				}
				arr.push_back(spl);
			}
		}
		return arr;
	}


	//! Assignment operator
	string<T>& operator=(const string<T>& other) 
	{
		if (this == &other)
			return *this;

		delete [] s_array;
		allocated = used = other.size()+1;
		s_array = new T[used];

		const T* p = other.c_str();
		for (sig i=0; i<used; ++i, ++p)
			s_array[i] = *p;

		return *this;
	}



	//! Assignment operator for strings, ascii and unicode
	template <class B>
	string<T>& operator=(const B* c) 
	{
		if (!c)
		{
			if (!s_array)
			{
				s_array = new T[1];
				allocated = 1;
				used = 1;
			}
			s_array[0] = 0x0;
			return *this;
		}

		if ((void*)c == (void*)s_array)
			return *this;

		sig len = 0;
		const B* p = c;
		while(*p)
		{
			++len;
			++p;
		}

		// we'll take the old string for a while, because the new string could be
		// a part of the current string.
		T* olds_array = s_array;

        allocated = used = len+1;
		s_array = new T[used];

		for (sig l = 0; l<len+1; ++l)
			s_array[l] = (T)c[l];

		delete [] olds_array;
		return *this;
	}

	//! Add operator for other strings
	string<T> operator+(const string<T>& other) 
	{ 
		string<T> str(*this); 
		str.append(other); 

		return str; 
	} 

	//! Add operator for strings, ascii and unicode 
	template <class B> 
	string<T> operator+(const B* c) 
	{ 
		string<T> str(*this); 
		str.append(c); 

		return str; 
	}



	//! Direct access operator
	T& operator [](const sig index)  const
	{
//		_IRR_DEBUG_BREAK_IF(index>=used) // bad index

		return s_array[index];
	}


	//! Comparison operator
	bool operator ==(const T* str) const
	{
		int i;
		for(i=0; s_array[i] && str[i]; ++i)
			if (s_array[i] != str[i])
				return false;

		return !s_array[i] && !str[i];
	}



	//! Comparison operator
	bool operator ==(const string<T>& other) const
	{
		for(sig i=0; s_array[i] && other.s_array[i]; ++i)
			if (s_array[i] != other.s_array[i])
				return false;

		return used == other.used;
	}



	//! Is smaller operator
	bool operator <(const string<T>& other) const
	{
		for(sig i=0; s_array[i] && other.s_array[i]; ++i)
			if (s_array[i] != other.s_array[i])
				return (s_array[i] < other.s_array[i]);

		return used < other.used;
	}



	//! Equals not operator
	bool operator !=(const string<T>& other) const
	{
		return !(*this == other);
	}


    
	//! Returns length of string
	/** \return Returns length of the string in characters. */
	sig size() const
	{
		return used-1;
	}



	//! Returns character string
	/** \return Returns pointer to C-style zero terminated string. */
	const T* c_str() const
	{
		return s_array;
	}



	//! Makes the string lower case.
	void make_lower()
	{
		const T A = (T)'A';
		const T Z = (T)'Z';
		const T diff = (T)'a' - A;

		for (sig i=0; i<used; ++i)
		{
			if (s_array[i]>=A && s_array[i]<=Z)
				s_array[i] += diff;
		}
	}



	//! Makes the string upper case.
	void make_upper()
	{
		const T a = (T)'a';
		const T z = (T)'z';
		const T diff = (T)'A' - a;

		for (sig i=0; i<used; ++i)
		{
			if (s_array[i]>=a && s_array[i]<=z)
				s_array[i] += diff;
		}
	}



	//! Compares the string ignoring case.
	/** \param other: Other string to compare.
	\return Returns true if the string are equal ignoring case. */
	bool equals_ignore_case(const string<T>& other) const
	{
		for(sig i=0; s_array[i] && other[i]; ++i)
			if (toLower(s_array[i]) != toLower(other[i]))
				return false;

		return used == other.used;
	}


	//! compares the first n characters of the strings
	bool equalsn(const string<T>& other, int len)
	{
		int i;
		for(i=0; s_array[i] && other[i] && i < len; ++i)
			if (s_array[i] != other[i])
				return false;

		// if one (or both) of the strings was smaller then they
		// are only equal if they have the same lenght
		return (i == len) || (used == other.used);
	}


	//! compares the first n characters of the strings
	bool equalsn(const T* str, int len)
	{
		int i;	
		for(i=0; s_array[i] && str[i] && i < len; ++i)
			if (s_array[i] != str[i])
				return false;

		// if one (or both) of the strings was smaller then they
		// are only equal if they have the same lenght
		return (i == len) || (s_array[i] == 0 && str[i] == 0);
	}


	//! Appends a character to this string
	/** \param character: Character to append. */
	void append(T character)
	{
		if (used + 1 > allocated)
			reallocate((sig)used + 1);

		used += 1;

		s_array[used-2] = character;
		s_array[used-1] = 0;
	}

	//! Appends a string to this string
	/** \param other: String to append. */
	void append(const string<T>& other)
	{
		--used;

		sig len = other.size();
		
		if (used + len + 1 > allocated)
			reallocate((sig)used + (sig)len + 1);

		for (sig l=0; l<len+1; ++l)
			s_array[l+used] = other[l];

		used = used + len + 1;
	}


	//! Appends a string of the length l to this string.
	/** \param other: other String to append to this string.
	 \param length: How much characters of the other string to add to this one. */
	void append(const string<T>& other, sig length)
	{
		sig len = other.size();

		if (len < length)
		{
			append(other);
			return;
		}

		len = length;
		--used;
		
		if (used + len > allocated)
			reallocate((sig)used + (sig)len);

		for (sig l=0; l<len; ++l)
			s_array[l+used] = other[l];

		used = used + len;
	}


	//! Reserves some memory.
	/** \param count: Amount of characters to reserve. */
	void reserve(sig count)
	{
		if (count < allocated)
			return;

		reallocate(count);
	}


	//! finds first occurrence of character in string
	/** \param c: Character to search for.
	\return Returns position where the character has been found,
	or -1 if not found. */
	sig findFirst(T c) const
	{
		for (sig i=0; i<used; ++i)
			if (s_array[i] == c)
				return i;

		return -1;
	}

	//! finds first occurrence of a character of a list in string
	/** \param c: List of strings to find. For example if the method
	should find the first occurance of 'a' or 'b', this parameter should be "ab".
	\param count: Amount of characters in the list. Ususally, 
	this should be strlen(ofParameter1)
	\return Returns position where one of the character has been found,
	or -1 if not found. */
	sig findFirstChar(T* c, int count) const
	{
		for (sig i=0; i<used; ++i)
			for (int j=0; j<count; ++j)
				if (s_array[i] == c[j])
					return i;

		return -1;
	}


	//! Finds first position of a character not in a given list.
	/** \param c: List of characters not to find. For example if the method
	 should find the first occurance of a character not 'a' or 'b', this parameter should be "ab".
	\param count: Amount of characters in the list. Ususally, 
	this should be strlen(ofParameter1)
	\return Returns position where the character has been found,
	or -1 if not found. */
	template <class B> 
	sig findFirstCharNotInList(B* c, int count) const
	{
		for (int i=0; i<used; ++i)
		{
            int j;
			for (j=0; j<count; ++j)
				if (s_array[i] == c[j])
					break;

			if (j==count)
				return i;
		}

		return -1;
	}

	//! Finds last position of a character not in a given list.
	/** \param c: List of characters not to find. For example if the method
	 should find the first occurance of a character not 'a' or 'b', this parameter should be "ab".
	\param count: Amount of characters in the list. Ususally, 
	this should be strlen(ofParameter1)
	\return Returns position where the character has been found,
	or -1 if not found. */
	template <class B> 
	sig findLastCharNotInList(B* c, int count) const
	{
		for (int i=used-2; i>=0; --i)
		{
            int j;
			for (j=0; j<count; ++j)
				if (s_array[i] == c[j])
					break;

			if (j==count)
				return i;
		}

		return -1;
	}

	//! finds next occurrence of character in string
	/** \param c: Character to search for.
	\param startPos: Position in string to start searching. 
	\return Returns position where the character has been found,
	or -1 if not found. */
	sig findNext(T c, sig startPos) const
	{
		for (sig i=startPos; i<used; ++i)
			if (s_array[i] == c)
				return i;

		return -1;
	}


	//! finds last occurrence of character in string
	//! \param c: Character to search for.
	//! \return Returns position where the character has been found,
	//! or -1 if not found.
	sig findLast(T c) const
	{
		for (sig i=used-1; i>=0; --i)
			if (s_array[i] == c)
				return i;

		return -1;
	}


	//! Returns a substring
	//! \param begin: Start of substring.
	//! \param length: Length of substring.
	string<T> subString(sig begin, sig length)
	{
		if (length <= 0)
			return string<T>("");

		string<T> o;
		o.reserve(length+1);

		for (sig i=0; i<length; ++i)
			o.s_array[i] = s_array[i+begin];

		o.s_array[length] = 0;
		o.used = o.allocated;

		return o;
	}


	void operator += (T c)
	{
		append(c);
	}

	void operator += (const string<T>& other)
	{
		append(other);
	}

	void operator += (int i)
	{
		append(string<T>(i));
	}

	//! replaces all characters of a special type with another one
	void replace(T toReplace, T replaceWith)
	{
		for (sig i=0; i<used; ++i)
			if (s_array[i] == toReplace)
				s_array[i] = replaceWith;
	}

	//! trims the string.
	/** Removes whitespace from begin and end of the string. */
	void trim()
	{
		const char whitespace[] = " \t\r\n";
		const int whitespacecount = sizeof(whitespace) - 1;

		// find start and end of real string without whitespace
		int begin = findFirstCharNotInList(whitespace, whitespacecount);
		if (begin == -1)
			return;

		int end = findLastCharNotInList(whitespace, whitespacecount);
		if (end == -1)
			return;

		*this = subString(begin, (end +1) - begin);
	}


	//! Erases a character from the string. May be slow, because all elements 
	//! following after the erased element have to be copied.
	//! \param index: Index of element to be erased.
	void erase(int index)
	{
		if (index < 0 || index >= used - 1) return;

		for (int i=index+1; i<used; ++i)
			s_array[i-1] = s_array[i];

		--used;
	}

    	

private:

	//! Returns a character converted to lower case
	T toLower(const T& t) const
	{
		if (t>=(T)'A' && t<=(T)'Z')
			return t + ((T)'a' - (T)'A');
		else
			return t;
	}

	//! Reallocate the s_array, make it bigger or smaler
	void reallocate(sig new_size)
	{
		T* old_s_array = s_array;

		s_array = new T[new_size];
		allocated = new_size;
		
		sig amount = used < new_size ? used : new_size;
		for (sig i=0; i<amount; ++i)
			s_array[i] = old_s_array[i];

		if (allocated < used)
			used = allocated;
		
		delete [] old_s_array;
	}


	//--- member variables

	T* s_array;
	sig allocated;
	sig used;
};


//! Typedef for character strings
typedef string<char> stringc;

//! Typedef for wide character strings
typedef string<wchar_t> stringw;

}

#endif

