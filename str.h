/*
The C++ Extended String Project v0.0

by Ali Aboul-Sauood
GitHub: https://github.com/ali-aboulsauood
Gmail: aliaboulsauood@gmail.com
*/

#pragma once

#include <string>
#include <array>
#include <vector>
#include <initializer_list>
#include <utility>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>

// returns the character of the opposite case to a given one.
inline char opposite_case(const char c)
{
	return std::isupper(c) ? std::tolower(c) : std::toupper(c);
}
// swaps the case of a given character (assigns a given character its opposite-case counterpart).
inline void swap_case(char& c)
{
	c = std::isupper(c) ? std::tolower(c) : std::toupper(c);
}

// The lowercase characters representing the English vowels.
constexpr std::array<char, 5> vowels = { 'a', 'e', 'i', 'o', 'u' };

// returns whether a character represents an English vowel (any of the letters a, e, i, o, and u, including their capital counterparts). By default, The letter (y) is not considered a vowel.
inline bool is_vowel(const char letter, const bool include_y = false)
{
	const char letter_l = std::tolower(letter);

	if (include_y && (letter_l == 'y'))
		return true;

	return (std::find(vowels.begin(), vowels.end(), letter_l) != vowels.end());
}
// returns whether a character represents an English vowel (none of the letters a, e, i, o, and u, including their capital counterparts). By default, The letter (y) is not considered a vowel.
inline bool is_consonant(const char letter, const bool is_y_vowel = false)
{
	return !is_vowel(letter, is_y_vowel);
}

// Whitespace characters, according to the default C locale
constexpr std::initializer_list<char> whitespaces = { ' ', '\t', '\n', '\v', '\f', '\r'};

// The extended string class
class str
{
	// The STL string from which this extended string is constructed.
	std::string _str;

	// converts a vector of STL strings to a vector of extended strings.
	static std::vector<str> vec_strs(const std::vector<std::string>& vec_std_strs)
	{
		std::vector<str> vec_strs = { };
		vec_strs.reserve(vec_std_strs.size());

		for (const std::string& string_ : vec_std_strs)
			vec_strs.emplace_back(string_);

		return vec_strs;
	}

public:
	// TODO: static functions that return a character array.

	// TODO: constructor-like static functions that return an STL string.
	
	// constructs an empty extended string.
	str() = default;
	// constructs an extended string from an STL string. By default, the entire string is copied, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str(const std::string& str_, const size_t start_pos = 0, const size_t len = std::string::npos) : _str(str_.substr(start_pos, len)) {}
	// constructs an extended string from a character array. By default, the entire array is copied, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str(const char* char_arr, const size_t pos = 0, const size_t len = std::string::npos) : _str(std::string(char_arr).substr(pos, len)) {}
	// constructs an extended string by copying another extended string. By default, the entire extended string is copied, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str(const str& other, const size_t start_pos = 0, const size_t len = std::string::npos) : _str(other._str.substr(start_pos, len)) {}
	// constructs an extended string by moving another extended string. By default, the entire extended string is assigned, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str(str&& other, const size_t start_pos = 0, const size_t len = std::string::npos) noexcept : _str(std::move(other._str))
	{
		if (start_pos != 0 && len != std::string::npos)
			_str = _str.substr(start_pos, len);
	}
	// constructs an extended string whose character sequence is the same as that of a given initializer list of characters.
	str(const std::initializer_list<char>& il) : _str(il) {}
	// constructs an extended string by joining the STL strings of a given STL container using a given delimiter (space by default).
	template<class Cont> str(const Cont& strs, const std::string& delim = " ") : _str(join(strs, delim)) {}
	
	// constructs an STL string by repeating a given character for a given number of times, with an optional separator placed between each two instances of the said character and an optional delimiter placed at the beginning and at the end of the string.
	static std::string repeat(const char c, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		std::string str_ = std::string();

		for (size_t i = 0; i < n; ++i)
		{
			str_.push_back(c);

			if (i != (n - 1))
				str_.append(sep);
		}

		str_.append(delim);

		return str_;

	}
	// constructs an STL string by repeating a given STL string for a given number of times, with an optional separator placed between each two instances of the said string and an optional delimiter placed at the beginning and at the end of the string.
	static std::string repeat(const std::string& str_, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		std::string str_r = std::string();

		for (size_t i = 0; i < n; ++i)
		{
			str_r.append(str_);

			if (i != (n - 1))
				str_r.append(sep);
		}

		str_r.append(delim);

		return str_r;

	}
	// constructs an STL string by repeating a given character array for a given number of times, with an optional separator placed between each two instances of the said array and an optional delimiter placed at the beginning and at the end of the string. 
	static std::string repeat(const char* char_arr, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		const std::string str_r = std::string(char_arr);

		return repeat(str_r, n, sep, delim);
	}

	// constructs an STL string by repeating a given STL string for a given number of times.
	friend std::string operator*(const std::string& str_, size_t n);
	// assigns the result of repeating a given STL string for a given number of times to the said string.
	friend std::string& operator*=(std::string& str_, size_t n);
	
	// constructs an extended string by repeating this extended string for a given number of times, with an optional separator placed between each two instances of the said string and an optional delimiter placed at the beginning and at the end of the string.
	str repeat(const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string()) const
	{
		return repeat(_str, n, sep, delim);
	}

	// constructs an extended string by repeating this extended string for a given number of times.
	str operator*(const size_t n) const
	{
		return repeat(n);
	}
	// assigns the result of repeating this extended string for a given number of times to this extended string.
	str& operator*=(const size_t n)
	{
		_str = repeat(_str, n);

		return *this;
	}

	// constructs an extended string by repeating a given character for a given number of times, with an optional separator placed between each two instances of the said character and an optional delimiter placed at the beginning and at the end of the string.
	str(const char c, const size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string()) : _str(repeat(c, n, sep, delim)) {}
	// constructs an extended string by repeating a given STL string for a given number of times, with an optional separator placed between each two instances of the said string and an optional delimiter placed at the beginning and at the end of the string.
	str(const std::string& str_, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string()) : _str(repeat(str_, n, sep, delim)) {}
	// constructs an extended string by repeating a given STL string for a given number of times, with an optional separator placed between each two instances of the said string and an optional delimiter placed at the beginning and at the end of the string.
	str(const char* char_arr, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string()) : _str(repeat(char_arr, n, sep, delim)) {}
	// constructs an extended string by repeating a given extended string for a given number of times, with an optional separator placed between each two instances of the said extended string and an optional delimiter placed at the beginning and at the end of the string.
	str(const str& other, const size_t n, const std::string& sep = std::string(), const std::string& delim = std::string()) : _str(repeat(other._str, n, sep, delim)) {}
	
	// constructs an STL string representing the sequence of decimal (base-10) digits representing a given number. For floating-point numbers, six digits are used to represent the non-integer part, and the trailing zeroes, if any, are omitted by default.
	template <class Number> static std::string to_string(const Number n, const bool trim_trailing_zeroes = true)
	{
		std::string str_ = std::to_string(n);

		if (trim_trailing_zeroes && str_.find('.') != std::string::npos)
		{
			str_ = r_trim(str_, "0");

			if (str_.back() == '.')
				str_.pop_back();
		}

		return str_;
	}
	// constructs an extended string representing the sequence of decimal (base-10) digits representing a given number. For floating-point numbers, six digits are used to represent the non-integer part, and the trailing zeroes, if any, are omitted by default.
	template<class Number> static str to_str(const Number n, const bool trim_trailing_zeroes = true)
	{
		return to_string(n, trim_trailing_zeroes);
	}

	/*
	// constructs an STL string representing the verbal representation of a given boolean value.
	static str to_string(const bool b, const bool capitalize_str, const std::pair<std::string, std::string>& vals_tf = { "true", "false" })
	{
		std::string str_ = (b ? vals_tf.first : vals_tf.second);

		if (capitalize_str)
			str_ = capitalize_front(str_);

		return str_; 
	}
	// constructs an extended string representing the verbal representation of a given boolean value.
	static str to_str(const bool b, const bool capitalize_str, const std::pair<std::string, std::string>& vals_tf = { "true", "false" })
	{
		return to_string(b, capitalize_str, vals_tf);
	}
	*/

	// Destroys this extended string.
	~str() = default;

	// TODO: Implement friend/static function versions of (operator=) and (assign) that return an STL string.
	
	// copy-assigns the value of an extended string to this extended string.
	str& operator=(const str& str_) = default;
	// move-assigns the value of an extended string to this extended string.
	str& operator=(str&& other) noexcept
	{
		if (*this != other)
			_str = std::move(other._str);

		return *this;
	}
	// assigns the value of an STL string to this extended string.
	str& operator=(const std::string& str_)
	{
		*this = str(str_);

		return *this;
	}
	// assigns the value of a character array to this extended string.
	str& operator=(const char* char_array)
	{
		*this = str(char_array);

		return *this;
	}
	// assigns the value of a character to this extended string.
	str& operator=(const char c)
	{
		*this = str(c);

		return *this;
	}
	// assigns the character sequence represented by an initializer list of characters to this extended string.
	str& operator=(const std::initializer_list<char>& il)
	{
		*this = str(il);

		return *this;
	}
	
	// copy-assigns the value of an extended string to this extended string. By default, the entire extended string is copied, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str& assign(const str& str_, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		return *this = str(str_, start_pos, len);
	}
	// move-assigns the value of an extended string to this extended string. By default, the entire extended string is moved, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	// TODO: Implement str& assign(str&& other, const size_t start_pos = 0, const size_t len = std::string::npos)
	// assigns the value of an STL string to this extended string. By default, the entire string is copied, but it is possible to define a substring by providing a starting offset and a length that includes the said offset.
	str& assign(const std::string& str_, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		return *this = str(str_, start_pos, len);
	}
	// assigns the value of a character array to this extended string. By default, the entire character array is copied, but it is possible to define a subarray by providing a starting offset and a length that includes the said offset.
	str& assign(const char* char_arr, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		return *this = str(char_arr, start_pos, len);
	}
	// assigns the value of a character repeated a given number of times (one by default), with an optional separator placed between each two instances of the said extended string and an optional delimiter placed at the beginning and at the end, to this extended string it is a member of.
	str& assign(const char c, const size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		return *this = str(c, n, sep, delim);
	}
	// assigns the character sequence of a given initializer list of characters to this extended string.
	str& assign(const std::initializer_list<char>& il)
	{
		return *this = str(il);
	}

	// TODO: Implement the extended string iterator class.
	
	// returns a random access iterator pointing to the beginning (the first character) of this extended string.
	std::string::iterator begin() noexcept
	{
		return _str.begin();
	}
	// returns a random access iterator pointing to the beginning (the first character) of this extended string.
	std::string::const_iterator begin() const noexcept
	{
		return _str.begin();
	}
	// returns a random access iterator pointing to the end (the after-the-last character) of this extended string.
	std::string::iterator end() noexcept
	{
		return _str.end();
	}
	// returns a random access iterator pointing to the end (the after-the-last character) of this extended string.
	std::string::const_iterator end() const noexcept
	{
		return _str.end();
	}

	// returns a reverse random access iterator pointing to the reverse beginning (the last character) of this extended string.
	std::string::reverse_iterator rbegin() noexcept
	{
		return _str.rbegin();
	}
	// returns a reverse random access iterator pointing to the reverse beginning (the last character) of this extended string.
	std::string::const_reverse_iterator rbegin() const noexcept
	{
		return _str.rbegin();
	}
	// returns a reverse random access iterator pointing to the reverse end (the before-the-first character) of this extended string.
	std::string::reverse_iterator rend() noexcept
	{
		return _str.rend();
	}
	// returns a reverse random access iterator pointing to the reverse end (the before-the-first character) of this extended string.
	std::string::const_reverse_iterator rend() const noexcept
	{
		return _str.rend();
	}

	// returns a random access iterator pointing to the beginning (the first character) of this extended string, where the said character is constant (cannot be modified through the iterator returned).
	std::string::const_iterator cbegin() const noexcept
	{
		return _str.cbegin();
	}
	// returns a random access iterator pointing to the end (the after-the-last character) of this extended string. where the said character is constant (cannot be modified through the iterator returned).
	std::string::const_iterator cend() const noexcept
	{
		return _str.cend();
	}

	// returns a reverse random access iterator pointing to the reverse beginning (the last character) of this extended string, where the said character is constant (cannot be modified through the iterator returned).
	std::string::const_reverse_iterator crbegin() const noexcept
	{
		return _str.crbegin();
	}
	// returns a reverse random access iterator pointing to the reverse end (the before-the-first character) of this extended string, where the said character is constant (cannot be modified through the iterator returned).
	std::string::const_reverse_iterator crend() const noexcept
	{
		return _str.crend();
	}

	// gets the STL string upon which this extended string is built.
	std::string get_str() const
	{
		return _str;
	}
	// gets the STL string upon which this extended string is built.
	std::string get_content() const
	{
		return _str;
	}

	// sets the STL string upon which this extended string is built.
	void set_str(const std::string& str_)
	{
		_str = str_;
	}
	// sets the STL string upon which this extended string is built.
	void set_content(const std::string& content)
	{
		_str = content;
	}

	// The STL string upon which this extended string is built.
	__declspec(property(get = get_str, put = set_str)) std::string str_;
	// The STL string upon which this extended string is built.
	__declspec(property(get = get_content, put = set_content)) std::string content;

	// returns a const-reference to the character array equivalent to this extended string (that is, an array of the same characters in the same order with the last element being the null terminator).
	const char* c_str() const noexcept
	{
		return _str.c_str();
	}
	// returns a const-reference to the character array equivalent to this extended string (that is, an array of the same characters in the same order with the last element being the null terminator).
	const char* data() const noexcept
	{
		return _str.data();
	}

	// returns the size (number of bytes that are occupied by the characters) of this extended string. If the said extended string contains no multibyte or variable-length characters, then the number returned by this method represents the number of characters of the said extended string.
	size_t size() const noexcept
	{
		return _str.size();
	}
	// returns the length (number of bytes that are occupied by the characters) of this extended string. If the said extended string contains no multibyte or variable-length characters, then the number returned by this method represents the number of characters of the said extended string.
	size_t length() const noexcept
	{
		return _str.length();
	}
	// returns the length (number of bytes that are occupied by the characters) of this extended string. If the said extended string contains no multibyte or variable-length characters, then the number returned by this method represents the number of characters of the said extended string.
	size_t len() const noexcept
	{
		return _str.length();
	}

	// returns the offset of the last byte of the character sequence occupied by an STL string. Useful in iteration statements.
	static size_t last_off(const std::string& str_) noexcept
	{
		return str_.empty() ? 0 : str_.length() - 1;
	}
	// returns the offset of the last byte of the character sequence occupied by this extended string. Useful in iteration statements.
	size_t last_off() const noexcept
	{
		return _str.empty() ? 0 : _str.length() - 1;
	}

	// returns the maximum size (number of bytes that are occupied by the characters) of this extended string based on known system or library implementations, though this extended string can fail to allocate storage at any point before reaching that size.
	size_t max_size() const noexcept
	{
		return _str.max_size();
	}
	// returns the maximum length (number of bytes that are occupied by the characters) of this extended string based on known system or library implementations, though this extended string can fail to allocate storage at any point before reaching that size.
	size_t max_length() const noexcept
	{
		return _str.max_size();
	}

	// resets the size (number of bytes that are occupied by the characters) of this extended string to a given size, removing any characters beyond that size or adding instances of a given character (the null terminator by default) to reach that size/length.
	void resize(const size_t len, const char c = char())
	{
		_str.resize(len, c);
	}

	// returns whether this extended string is empty (has a size/length of zero bytes). (To clear the contents of the string, use the method (clear)).
	bool empty() const noexcept
	{
		return _str.empty();
	}
	// returns whether this extended string is empty (has a size/length of zero bytes).
	bool is_empty() const noexcept
	{
		return _str.empty();
	}

	// clears this extended string (resets its size/length to zero bytes, removing all characters within it). (To check whether the string is empty, use the method (empty) or (is_empty)).
	void clear() noexcept
	{
		_str.clear();
	}

	// returns the capacity of (the number of bytes allocated to) the STL string upon which this extended string is built. this may be greater than or equal to the string size/length (number of bytes that are occupied by the characters of the string).
	size_t capacity() const noexcept
	{
		return _str.capacity();
	}
	// requests that the capacity of (the number of bytes allocated to) the STL string upon which this extended string is built is changed to be adapted to a planned change in size/length up to a given number. The request does not change the size/length of the string or its value, and is only guaranteed to be fulfilled if the given size/length is greater than the current capacity of the string.
	void reserve(const size_t len)
	{
		return _str.reserve(len);
	}
	// requests that the capacity of (the number of bytes allocated to) the STL string upon which this extended string is built is changed to a value equal to its size/length. The request does not change the size/length of the string or its value, and is not guaranteed to be fulfilled as the string implementation may be free to optimize otherwise and leave the string with a capacity greater than its size.
	void shrink_to_fit()
	{
		_str.shrink_to_fit();
	}

	// returns a reference to the character at a given offset from the first character of this extended string. If (pos) is greater than or equal to the string size/length, a null terminator is returned.
	char& operator[](const size_t pos)
	{
		char& c = _str[pos];

		if (pos >= _str.length())
			c = char();

		return c;
	}
	// returns a reference to the character at a given offset from the first character of this extended string. If (pos) is greater than or equal to the string size/length, a null terminator is returned.
	const char& operator[](const size_t pos) const
	{
		if (pos >= _str.length())
		{
			static const char& c = char();
			return c;
		}

		return _str[pos];

	}

	// returns a reference to the character at a given offset from the first character of this extended string. If (pos) is greater than or equal to the string size/length, an out-of-range exception is thrown.
	char& at(const size_t pos)
	{
		return _str.at(pos);
	}
	// returns a reference to the character at a given offset from the first character of this extended string. If (pos) is greater than or equal to the string size/length, an out-of-range exception is thrown.
	const char& at(const size_t pos) const
	{
		return _str.at(pos);
	}

	// returns a reference to the first character of this extended string.
	char& front()
	{
		return _str.front();
	}
	// returns a reference the first character of this extended string.
	const char& front() const
	{
		return _str.front();
	}
	
	// returns a reference to the last character of this extended string.
	char& back()
	{
		return _str.back();
	}
	// returns a reference to the last character of this extended string.
	const char& back() const
	{
		return _str.back();
	}

	// TODO: implement friend/static function versions of (operator+=) and (append) that return an STL string.

	// appends this extended string on its right hand side to this extended string.
	str& operator+=(const str& str_)
	{
		*this = _str.append(str_._str);

		return *this;
	}
	// appends an STL string to this extended string.
	str& operator+=(const std::string& str_)
	{
		*this = _str.append(str_);

		return *this;
	}
	// appends a character array to this extended string.
	str& operator+=(const char* char_array)
	{
		*this = _str.append(char_array);

		return *this;
	}
	// appends a character to this extended string.
	str& operator+=(const char c)
	{
		_str.push_back(c);

		return *this;
	}
	// appends the character sequence represented by an initializer list of characters to this extended string.
	str& operator+=(const std::initializer_list<char>& il)
	{
		*this = _str.append(il);

		return *this;
	}
	
	// appends an extended string to this extended string. A substring can be appended by defining a start offset from the first character and the number of characters including the one at the said offset.
	str& append(const str& str_, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		_str.append(str_._str.substr(start_pos, len));

		return *this;
	}
	// appends an STL string to this extended string. A substring can be appended by defining a start offset from the first character and the number of characters including the one at the said offset.
	str& append(const std::string& str_, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		*this = _str.append(str_.substr(start_pos, len));

		return *this;
	}
	// appends a character array to this extended string. A subarray can be appended by defining a start offset from the first character and the number of characters including the one at the said offset.
	str& append(const char* char_array, const size_t start_pos = 0, const size_t len = std::string::npos)
	{
		_str.append(std::string(char_array).substr(start_pos, len));

		return *this;
	}
	// appends a character to this extended string. The said character can be repeated for a defined number of times and a separator between each two instances of the said character, as well as a delimiter enclosing the repeated character sequence, can be defined as well.
	str& append(const char c, const size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		if (n == 1 && sep.empty() && delim.empty())
		{
			_str.push_back(c);

			return *this;
		}

		str str_ = str(c, n, sep, delim);

		return append(str_);
	}
	// appends an initializer list of characters to this extended string.
	str& append(const std::initializer_list<char>& il)
	{
		_str.append(il);

		return *this;
	}

	// TODO: implement corresponding (operator+=) and (prepend) functions.
	
	// pushes a character into the back of (appends a character to) this extended string.
	void push_back(const char c)
	{
		_str.push_back(c);
	}
	// "pushes" a character into the front of (prepends a character to) this extended string.
	void push_front(const char c)
	{
		_str = (c + _str);
	}
	// "pushes" a given number of characters (one by default) into the back (by default) or the front of this extended string. (appends/prepends a given number of characters to this extended string).
	void push(const char c, const size_t n = 1, const bool push_to_front = false)
	{
		if (n >= 1)
		{
			if (push_to_front)
			{
				for (size_t i = 1; i <= n; i++)
					push_front(c);
			}
			else
				_str.append(n, c);
		}
	}

	// pops (removes) the last character from the back of this extended string.
	void pop_back()
	{
		_str.pop_back();
	}
	// "pops" (removes) the first character from the front of this extended string.
	void pop_front()
	{
		_str.erase(0, 1);
	}
	// "pops" (removes) the last (by default) or first given number of characters (one by default) from the back of this extended string.
	void pop(const size_t n = 1, const bool pop_from_front = false)
	{
		if (n >= 1)
		{
			if (pop_from_front)
				_str.erase(0, n);
			else
				_str.erase(_str.length() - n, n);
		}
	}
	
	// Prefix decrement operator: pops (removes) the first character from the front of this extended string.
	str& operator--()
	{
		_str.erase(0, 1);

		return *this;
	}
	// Postfix decrement operator: pops (removes) the last character from the back of this extended string.
	str operator--(int)
	{
		_str.pop_back();

		return *this;
	}

	// TODO: implement static function versions of (insert) that return an STL string.
	
	// inserts a given extended string before the character at a given offset of this extended string. A substring can be inserted by defining a starting offset and a length that includes the said offset.
	str& insert(const size_t pos, const str& str_, const size_t sub_pos = 0, const size_t sub_len = std::string::npos)
	{
		_str.insert(pos, str_._str, sub_pos, sub_len);

		return *this;
	}
	// inserts a given STL string before the character at a given offset of this extended string. A substring can be inserted by defining a starting offset and a length that includes the said offset.
	str& insert(const size_t pos, const std::string& str_, const size_t sub_pos = 0, const size_t sub_len = std::string::npos)
	{
		_str.insert(pos, str_, sub_pos, sub_len);

		return *this;
	}
	// inserts a given character array before the character at a given offset of this extended string. A subarray can be inserted by defining a starting offset and a length that includes the said offset.
	str& insert(const size_t pos, const char* char_array, const size_t sub_pos = 0, const size_t sub_len = std::string::npos)
	{
		_str.insert(pos, std::string(char_array), sub_pos, sub_len);

		return *this;
	}
	// inserts a given character repeated for a given number of times (one by default) before the character at a given offset of this extended string, with an optional separator placed between each two instances of the said character and an optional delimiter placed at the beginning and at the end of the string.
	str& insert(const size_t pos, const char c, const size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		std::string str_ = repeat(c, n, sep, delim);

		_str.insert(pos, str_);

		return *this;
	}
	// inserts a given character repeated for a given number of times (one by default) before the character of this extended string pointed to by a given iterator, and returns an iterator pointing to the first character inserted.
	std::string::iterator insert(const std::string::iterator& iter, const char c, const size_t n = 1)
	{
		return _str.insert(iter, n, c);
	}
	// inserts the character sequence of a given initializer list of characters before the character of this extended string pointed to by a given iterator.
	str& insert(const std::string::iterator& iter, const std::initializer_list<char>& il)
	{
		_str.insert(iter, il);

		return *this;
	}

	// swaps the values of this extended string and another extended string.
	void swap(str& str_) noexcept
	{
		std::swap(_str, str_._str);
	}
	// swaps the values of this extended string and an STL string.
	void swap(std::string& str_)
	{
		std::swap(_str, str_);
	}
	// swaps the values of this extended string and a character array.
	void swap(char* char_array)
	{
		std::string str_ = char_array;

		std::swap(_str, str_);

		size_t str_len = str_.length();
		char_array = new char[str_len];
		for (size_t i = 0; i < str_len; ++i)
			char_array[i] = str_.at(i);
	}

	// returns the substring that starts from a given offset from the first character and spans a given number of characters starting from the said offset.
	str substr(const size_t pos = 0, const size_t len = std::string::npos) const
	{
		return _str.substr(pos, len);
	}

	// TODO: implement versions of (split) and (join) that take/return arrays and C++ STL containers supporting random access.
	
	// returns a C++ STL vector of substrings separated by a given delimiter (a space by default) in a given STL string. If the delimiter is an empty string, a vector containing the passed string is returned.
	static std::vector<std::string> split(const std::string& str_, const std::string& delim = " ")
	{
		if (delim.empty())
			return { str_ };
		
		size_t start_pos = 0, delim_pos = 0;
		const size_t str_len = str_.length(), delim_len = delim.length();

		std::vector<std::string> substrs = {};
		
		substrs.reserve(str_len / delim_len + 1);

		while ((delim_pos = str_.find(delim, start_pos)) != std::string::npos)
		{
			if (delim_pos != start_pos)
				substrs.push_back(str_.substr(start_pos, delim_pos - start_pos));

			start_pos = (delim_pos + delim_len);
		}

		if (start_pos < str_len)
			substrs.push_back(str_.substr(start_pos));

		return substrs;
	}
	// returns a C++ STL vector of substrings separated by a given delimiter (a space by default) in this extended string. If the delimiter is an empty string, a vector containing the passed string is returned.
	std::vector<str> split(const std::string& delim = " ") const
	{
		return vec_strs(split(_str, delim));
	}

	// joins the STL strings of a given C++ STL container into one STL string, separating them using a given delimiter (a space by default), and returns the said string.
	template<class Cont> static std::string join(const Cont& strs, const std::string& delim = " ")
	{
		std::string str_ = std::string();

		for (const std::string& _str_ : strs)
			str_.append(_str_ + delim);

		return str_.substr(0, str_.length() - delim.length());
	}

	// returns the STL string whose characters are the uppercase counterparts of another given STL string.
	static std::string to_upper(const std::string& str_)
	{
		std::string str_u = std::string();

		for (const char& c : str_)
			str_u.push_back(std::toupper(c));

		return str_u;
	}
	// returns the STL string whose characters are the lowercase counterparts of another given STL string.
	static std::string to_lower(const std::string& str_)
	{
		std::string str_l = std::string();

		for (const char& c : str_)
			str_l.push_back(std::tolower(c));

		return str_l;
	}
	// returns the STL string whose characters are the opposite case counterparts of another given STL string.
	static std::string swap_case(const std::string& str_)
	{
		std::string str_s = std::string();

		for (const char& c : str_)
			str_s.push_back(opposite_case(c));

		return str_s;
	}
	
	// returns a capitalized version of a given STL string (has the same character sequence, with the first character replaced by its uppercase counterpart and, by default, the rest of the characters are replaced by their lowercase counterparts).
	static std::string capitalize_front(const std::string& str_, const bool to_lower_rest = true)
	{
		const size_t len = str_.length();

		std::string str_cap = std::string();
		str_cap.reserve(len);

		str_cap.push_back(std::toupper(str_.front()));

		for (size_t i = 1; i < len; i++)
			str_cap.push_back(to_lower_rest ? std::tolower(str_.at(i)) : str_.at(i));

		return str_cap;
	}
	// returns a capitalized version of a given STL string (has the same character sequence, with the first character replaced by its uppercase counterpart and, by default, the rest of the characters are replaced by their lowercase counterparts).
	static std::string cap_f(const std::string& str_, const bool to_lower_rest = true)
	{
		const size_t len = str_.length();

		std::string str_cap = std::string();
		str_cap.reserve(len);

		str_cap.push_back(std::toupper(str_.front()));

		for (size_t i = 1; i < len; i++)
			str_cap.push_back(to_lower_rest ? std::tolower(str_.at(i)) : str_.at(i));

		return str_cap;
	}
	
	// returns an uncapitalized version of a given STL string (has the same character sequence, with the first character replaced by its lowercase counterpart and, by default, the rest of the characters are replaced by their uppercase counterparts).
	static std::string uncapitalize_front(const std::string& str_, const bool to_upper_rest = true)
	{
		const size_t len = str_.length();

		std::string str_cap = std::string();
		str_cap.reserve(len);

		str_cap.push_back(std::tolower(str_.front()));

		for (size_t i = 1; i < len; i++)
			str_cap.push_back(to_upper_rest ? std::toupper(str_.at(i)) : str_.at(i));

		return str_cap;
	}
	// returns an uncapitalized version of a given STL string (has the same character sequence, with the first character replaced by its lowercase counterpart and, by default, the rest of the characters are replaced by their uppercase counterparts).
	static std::string uncap_f(const std::string& str_, const bool to_upper_rest = true)
	{
		const size_t len = str_.length();

		std::string str_cap = std::string();
		str_cap.reserve(len);

		str_cap.push_back(std::tolower(str_.front()));

		for (size_t i = 1; i < len; i++)
			str_cap.push_back(to_upper_rest ? std::toupper(str_.at(i)) : str_.at(i));

		return str_cap;
	}

	// returns this extended string whose characters are the uppercase counterparts of this extended string.
	str to_upper() const
	{
		return to_upper(_str);
	}
	// returns this extended string whose characters are the lowercase counterparts of this extended string.
	str to_lower() const
	{
		return to_lower(_str);
	}
	// returns this extended string whose characters are the opposite case counterparts of this extended string.
	str swap_case() const
	{
		return swap_case(_str);
	}
	// returns a capitalized version of this extended string. (has the same character sequence, with the first character replaced by its uppercase counterpart and, by default, the rest of the characters are replaced by their lowercase counterparts).
	str capitalize_front(const bool to_lower_rest = true) const
	{
		return capitalize_front(_str, to_lower_rest);
	}
	// returns a capitalized version of this extended string. (has the same character sequence, with the first character replaced by its uppercase counterpart and, by default, the rest of the characters are replaced by their lowercase counterparts).
	str cap_f(const bool to_lower_rest = true) const
	{
		return cap_f(_str, to_lower_rest);
	}
	
	// returns an uncapitalized version of a given STL string (has the same character sequence, with the first character replaced by its lowercase counterpart and, by default, the rest of the characters are replaced by their uppercase counterparts).
	str uncapitalize_front(const bool to_upper_rest = true) const
	{
		return uncapitalize_front(_str, to_upper_rest);
	}
	// returns an uncapitalized version of a given STL string (has the same character sequence, with the first character replaced by its lowercase counterpart and, by default, the rest of the characters are replaced by their uppercase counterparts).
	str uncap_f(const bool to_upper_rest = true) const
	{
		return uncap_f(_str, to_upper_rest);
	}
	
	// returns the count of uppercase alphabetical characters (capital letters) in a given STL string.
	static size_t uppercase_count(const std::string& str_)
	{
		return std::count_if(str_.begin(), str_.end(), isupper);
	}
	// returns the count of lowercase alphabetical characters (small letters) in a given STL string.
	static size_t lowercase_count(const std::string& str_)
	{
		return std::count_if(str_.begin(), str_.end(), islower);
	}
	
	// returns the count of uppercase alphabetical characters (capital letters) in this extended string.
	size_t uppercase_count()
	{
		return std::count_if(_str.begin(), _str.end(), isupper);
	}
	// returns the count of lowercase alphabetical characters (capital letters) in this extended string.
	size_t lowercase_count()
	{
		return std::count_if(_str.begin(), _str.end(), islower);
	}
	
	// returns the count of characters representing English vowels in a given STL string. By default, the letter (y) is not considered a vowel.
	static size_t vowel_count(const std::string& str_, const bool include_y = false)
	{
		// TODO: use C++ STL algorithm function.

		size_t count = 0;

		for (const char& c : str_)
		{
			if (is_vowel(c, include_y))
				count++;
		}

		return count;
	}
	// returns the count of characters representing English consonants in a given STL string. By default, the letter (y) is not considered a vowel.
	static size_t consonant_count(const std::string& str_, const bool is_y_vowel = false)
	{
		return (str_.length() - vowel_count(str_, is_y_vowel));
	}

	// returns the count of characters representing English vowels in this extended string.
	size_t vowel_count(const bool include_y = false) const
	{
		return vowel_count(_str, include_y);
	}
	// returns the count of characters representing English vowels in of this extended string.
	size_t consonant_count(const bool is_y_vowel = false) const
	{
		return consonant_count(_str, is_y_vowel);
	}

	// returns the count of a given character in a given STL string. Counting is case-sensitive by default.
	static size_t count(const std::string& str_, const char c, const bool case_sensitive = true)
	{
		const size_t count_cs = std::count(str_.begin(), str_.end(), c);

		if (case_sensitive)
			return count_cs;
		
		const char _c = opposite_case(c);

		return (count_cs + std::count(str_.begin(), str_.end(), _c));
	}
	// returns the count of a given character in this extended string. Counting is case-sensitive by default.
	size_t count(const char c, const bool case_sensitive = true) const
	{
		return count(_str, c, case_sensitive);
	}
	
	// The possible space-trimming operations that can be performed on a character sequence.
	enum trim_operation : std::int8_t { left = -1, all = 0, right = +1 };

	// returns the STL string that is equivalent to another given STL string without the leading whitespaces (if any). (returns the left-trimmed version of a given STL string). A set of characters other than whitespaces can also be chosen for removal.
	static std::string l_trim(const std::string& str_, const std::string& chars = whitespaces)
	{
		const size_t start_pos = str_.find_first_not_of(chars);

		return str_.substr(start_pos);
	}
	// returns the STL string that is equivalent to another given STL string without the leading whitespaces (if any). (returns the left-trimmed version of a given STL string).
	static std::string trim_leading_spaces(const std::string& str_)
	{
		const size_t start_pos = str_.find_first_not_of(whitespaces);

		return str_.substr(start_pos);
	}

	// returns the STL string that is equivalent to a given STL string without the trailing spaces (if any). (returns the right-trimmed version of a given STL string). A set of characters other than whitespaces can also be chosen for removal.
	static std::string r_trim(const std::string& str_, const std::string& chars = whitespaces)
	{
		const size_t end_pos = str_.find_last_not_of(chars);

		return str_.substr(0, end_pos + 1);
	}
	// returns the STL string that is equivalent to a given STL string without the trailing spaces (if any). (returns the right-trimmed version of a given STL string).
	static std::string trim_trailing_spaces(const std::string& str_)
	{
		const size_t end_pos = str_.find_last_not_of(whitespaces);

		return str_.substr(0, end_pos + 1);
	}

	// returns the STL string that is equivalent to a given STL string without the leading, trailing or both leading and trailing spaces (the default) (if any). A set of characters other than whitespaces can also be chosen for removal.
	static std::string trim(const std::string& str_, const trim_operation trim_op = all, const std::string& chars = whitespaces)
	{
		switch (trim_op)
		{
		case left:
			return l_trim(str_, chars);
		case right:
			return r_trim(str_, chars);
		case all:
			return r_trim(l_trim(str_, chars), chars);
		}

		return str_;
	}
	// returns the STL string that is equivalent to a given STL string without the leading, trailing or both leading and trailing spaces (the default) (if any).
	static std::string trim_spaces(const std::string& str_)
	{
		return trim(str_, all);
	}
	
	// returns the extended string that is equivalent to this one without the leading spaces (if any). (returns the left-trimmed version of this extended string). A set of characters other than whitespaces can also be chosen for removal.
	str l_trim(const std::string& chars = whitespaces) const
	{
		return l_trim(_str, chars);
	}
	// returns this extended string that is equivalent to this one without the leading spaces (if any). (returns the left-trimmed version of this extended string).
	str trim_leading_spaces() const
	{
		return trim_leading_spaces(_str);
	}

	// returns the extended string that is equivalent to this one without the trailing spaces (if any). (returns the right-trimmed version of this extended string). A set of characters other than whitespaces can also be chosen for removal.
	str r_trim(const std::string& chars = whitespaces) const
	{
		return r_trim(_str, chars);
	}
	// returns this extended string that is equivalent to this one without the trailing spaces (if any). (returns the right-trimmed version of this extended string).
	str trim_trailing_spaces() const
	{
		return trim_trailing_spaces(_str);
	}

	// returns the extended string that is equivalent to this one without the leading, trailing or both leading and trailing spaces (the default) (if any). A set of characters other than whitespaces can also be chosen for removal.
	str trim(const trim_operation trim_op = all, const std::string& chars = whitespaces) const
	{
		return trim(_str, trim_op, chars);
	}
	// returns this extended string that is equivalent to this one without the leading, trailing or both leading and trailing spaces (the default) (if any).
	str trim_spaces(const trim_operation trim_op = all) const
	{
		return trim(_str, trim_op);
	}

	// returns the STL string that is equivalent to another, albeit without the characters representing punctuation marks.
	static std::string depunctuate(const std::string& str_)
	{
		std::string depunct_str = std::string();

		for (const char& c : str_)
		{
			if (!std::ispunct(c))
				depunct_str.push_back(c);
		}

		return depunct_str;
	}
	// returns the STL string that is equivalent to another, albeit without the characters representing punctuation marks.
	static std::string remove_punct(const std::string& str_)
	{
		std::string depunct_str = std::string();

		for (const char& c : str_)
		{
			if (!ispunct(c))
				depunct_str.push_back(c);
		}

		return depunct_str;
	}

	// returns this extended string that is equivalent to this one without the characters representing punctuation marks.
	str depunctuate() const
	{
		return depunctuate(_str);
	}
	// returns this extended string that is equivalent to this one without the characters representing punctuation marks.
	str remove_punct() const
	{
		return remove_punct(_str);
	}

	// returns an STL string containing the first character of each substring of a given STL string. By default, the substrings are delimited by whitespace characters, and the initials are separated by a space.
	static std::string initials(const std::string& str_, const bool capitalize_init = false, const std::string& delim = " ", const std::string& delims = whitespaces)
	{
		if (str_.empty())
			return {};

		std::string initials = {};

		bool is_initial = true;

		for (const char& c : str_)
		{
			const bool is_delim = (delims.find(c) != std::string::npos);

			if (is_initial && !is_delim)
			{
				initials.push_back(capitalize_init ? std::toupper(c) : c);
				
				if (!delim.empty())
					initials.append(delim);

				is_initial = is_delim;
			}
		}

		size_t initials_len = initials.length(), delim_len = delim.length();

		if (initials_len >= delim_len)
		{
			size_t del_pos = initials_len - delim_len;

			if (initials.substr(del_pos) == delim)
				initials.erase(del_pos);
		}

		return initials;
	}
	// returns an extended string containing the first character of each substring of this extended string. By default, the substrings are delimited by whitespace characters, and the initials are separated by a space.
	str initials(const bool capitalize_init = false, const std::string& delim = " ", const std::string& delims = whitespaces) const
	{
		return initials(_str, capitalize_init, delim, delims);
	}

	// returns an STL string equivalent to a given one with the first character of each whitespace-delimited substring replaced by its uppercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	static std::string capitalize(const std::string& str_, const std::string& delims = whitespaces)
	{
		if (str_.empty())
			return {};

		std::string str_cap = {};
		str_cap.reserve(str_.length());

		bool is_initial = true;

		for (const char& c : str_)
		{
			const bool is_delim = (delims.find(c) != std::string::npos);

			if (is_initial && !is_delim)
				str_cap.push_back(std::toupper(c));
			else
				str_cap.push_back(c);

			is_initial = is_delim;
		}

		return str_cap;
	}
	// returns an extended string equivalent this one with the first character of each whitespace-delimited substring replaced by its uppercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	str capitalize(const std::string& delims = whitespaces) const
	{
		return capitalize(_str, delims);
	}

	// returns an STL string equivalent a given one with the first character of each whitespace-delimited substring replaced by its uppercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	static std::string title(const std::string& str_, const std::string& delims = whitespaces)
	{
		if (str_.empty())
			return {};

		std::string str_cap = {};
		str_cap.reserve(str_.length());

		bool is_initial = true;

		for (const char& c : str_)
		{
			const bool is_delim = (delims.find(c) != std::string::npos);

			if (is_initial && !is_delim)
				str_cap.push_back(std::toupper(c));
			else
				str_cap.push_back(c);

			is_initial = is_delim;
		}

		return str_cap;
	}
	// returns an extended string whose character sequence equivalent to this one with the first character of each whitespace-delimited substring replaced by its uppercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	str title(const std::string& delims = whitespaces) const
	{
		return title(_str, delims);
	}

	// returns an STL string equivalent to this one with the first character of each whitespace-delimited substring replaced by its lowercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	static std::string uncapitalize(const std::string& str_, const std::string& delims = whitespaces)
	{
		if (str_.empty())
			return {};

		std::string str_uncap = {};
		str_uncap.reserve(str_.length());

		bool is_initial = true;

		for (const char& c : str_)
		{
			const bool is_delim = (delims.find(c) != std::string::npos);

			if (is_initial && !is_delim)
				str_uncap.push_back(std::tolower(c));
			else
				str_uncap.push_back(c);

			is_initial = is_delim;
		}

		return str_uncap;
	}
	// returns an extended string equivalent to this one with the first character of each whitespace-delimited substring replaced by its uppercase counterpart. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	str uncapitalize(const std::string& delims = whitespaces) const
	{
		return uncapitalize(_str, delims);
	}

	// returns the number of whitespace-delimited substrings in a given STL string. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	static size_t word_count(const std::string& str_, const std::string& delims = whitespaces)
	{
		if (str_.empty())
			return 0;

		size_t count = 0;

		bool is_new_word = true;

		for (const char& c : str_)
		{
			bool is_delim = (delims.find(c) != std::string::npos);

			if (is_new_word && !is_delim)
				++count;

			is_new_word = is_delim;
		}

		return count;
	}
	// returns the number of whitespace-delimited substrings in this extended string. (a delimiter or a set of delimiters other than whitespace characters can be defined).
	size_t word_count(const std::string& delims = whitespaces) const
	{
		return word_count(_str, delims);
	}

	// returns an STL string that is the result of reversing the order of the characters of a given one.
	static std::string reverse(const std::string& str_)
	{
		if (str_.empty())
			return {};

		std::string str_r = {};
		str_r.reserve(str_.length());

		for (auto iter = str_.rbegin(); iter != str_.rend(); ++iter)
			str_r.push_back(*iter);

		return str_r;
	}
	// returns an extended string that is the result of reversing the order of the characters of this one.
	str reverse() const
	{
		return reverse(_str);
	}

	// returns an STL string equivalent to a given one with the order of the substrings delimited by a given delimiter (a space by default) reversed.
	static std::string reverse_words(const std::string& str_, const std::string& delim = " ")
	{
		if (str_.empty())
			return {};

		std::vector<std::string> words = split(str_, delim);

		std::string str_r = {};
		str_r.reserve(str_.length());

		for (auto iter = words.rbegin(); iter != words.rend(); ++iter)
			str_r.append(*iter + delim);

		str_r.erase(str_r.length() - delim.length());

		return str_r;
	}
	// returns an extended string equivalent to a given one with the order of the substrings delimited by a given delimiter (a space by default) reversed.
	str reverse_words(const std::string& delim = " ") const
	{
		return reverse_words(_str, delim);
	}

	// TODO: static function versions of (find) that return an STL string.
	// TODO: document (find).
	
	size_t find(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find(to_lower(str_._str));

		return search_in.find(str_._str);
	}
	size_t find(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find(to_lower(str_));

		return search_in.find(str_);
	}
	size_t find(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find(to_lower(char_arr));

		return search_in.find(char_arr);
	}
	size_t find(const char* char_arr, const bool case_sensitive = true, const std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.find(char_arr, 0, n);
	}
	size_t find(const char c, const bool case_sensitive = true, const size_t pos = 0, const size_t len = 0) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find(std::tolower(c));

		return search_in.find(c);
	}

	size_t r_find(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).rfind(to_lower(str_._str));

		return search_in.rfind(str_._str);
	}
	size_t r_find(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).rfind(to_lower(str_));

		return search_in.rfind(str_);
	}
	size_t r_find(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).rfind(to_lower(char_arr));

		return search_in.rfind(char_arr);
	}
	size_t r_find(const char* char_arr, const bool case_sensitive = true, std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).rfind(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.rfind(char_arr, 0, n);
	}
	size_t r_find(const char c, const bool case_sensitive = true, const size_t pos = 0, const size_t len = 0) const noexcept
	{
		const std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).rfind(std::tolower(c));

		return search_in.rfind(c);
	}

	size_t find_first_of(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_of(to_lower(str_._str));

		return search_in.find_first_of(str_._str);
	}
	size_t find_first_of(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_of(to_lower(str_));

		return search_in.find_first_of(str_);
	}
	size_t find_first_of(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_of(to_lower(char_arr));

		return search_in.find_first_of(char_arr);
	}
	size_t find_first_of(const char* char_arr, const bool case_sensitive = true, const std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_of(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.find_first_of(char_arr, 0, n);
	}

	size_t find_last_of(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_of(to_lower(str_._str));

		return search_in.find_first_of(str_._str);
	}
	size_t find_last_of(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_of(to_lower(str_));

		return search_in.find_last_of(str_);
	}
	size_t find_last_of(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_of(to_lower(char_arr));

		return search_in.find_last_of(char_arr);
	}
	size_t find_last_of(const char* char_arr, const bool case_sensitive = true, const std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_of(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.find_last_of(char_arr, 0, n);
	}

	size_t find_first_not_of(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_not_of(to_lower(str_._str));

		return search_in.find_first_not_of(str_._str);
	}
	size_t find_first_not_of(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_not_of(to_lower(str_));

		return search_in.find_first_not_of(str_);
	}
	size_t find_first_not_of(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_not_of(to_lower(char_arr));

		return search_in.find_first_not_of(char_arr);
	}
	size_t find_first_not_of(const char* char_arr, const bool case_sensitive = true, std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_not_of(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.find_first_not_of(char_arr, 0, n);
	}
	size_t find_first_not_of(const char c, const bool case_sensitive = true, const size_t pos = 0, const size_t len = 0) const noexcept
	{
		const std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_first_not_of(std::tolower(c));

		return search_in.find_first_not_of(c);
	}

	size_t find_last_not_of(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const noexcept
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_not_of(to_lower(str_._str));

		return search_in.find_last_not_of(str_._str);
	}
	size_t find_last_not_of(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_not_of(to_lower(str_));

		return search_in.find_last_not_of(str_);
	}
	size_t find_last_not_of(const char* char_arr, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_not_of(to_lower(char_arr));

		return search_in.find_last_not_of(char_arr);
	}
	size_t find_last_not_of(const char* char_arr, const bool case_sensitive = true, std::string::size_type n = 0, const size_t pos = 0, const size_t len = 0) const
	{
		std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_not_of(to_lower(char_arr).c_str(), 0, n);
		
		return search_in.find_last_not_of(char_arr, 0, n);
	}
	size_t find_last_not_of(const char c, const bool case_sensitive = true, const size_t pos = 0, const size_t len = 0) const noexcept
	{
		const std::string search_in = _str.substr(pos, len);

		if (!case_sensitive)
			return to_lower(search_in).find_last_not_of(std::tolower(c));

		return search_in.find_last_not_of(c);
	}

	// TODO: static function versions of (replace) that return an STL string.
	// TODO: document (replace).
	
	str& replace(const str& replace_with, const size_t this_pos, const size_t this_len, const size_t that_pos = 0, const size_t that_len = std::string::npos)
	{
		_str.replace(this_pos, this_len, replace_with._str, that_pos, that_len);

		return *this;
	}
	str& replace(const str& replace_with, const std::string::const_iterator& this_begin, const std::string::const_iterator& this_end)
	{
		_str.replace(this_begin, this_end, replace_with._str);

		return *this;
	}
	str& replace(const std::string& replace_with, const size_t this_pos, const size_t this_len, const size_t that_pos = 0, const size_t that_len = std::string::npos)
	{
		_str.replace(this_pos, this_len, replace_with, that_pos, that_len);

		return *this;
	}
	str& replace(const std::string& replace_with, const std::string::const_iterator& this_begin, const std::string::const_iterator& this_end)
	{
		_str.replace(this_begin, this_end, replace_with);

		return *this;
	}
	str& replace(const char* replace_with, const size_t this_pos, const size_t this_len, const size_t that_pos = 0, const size_t that_len = std::string::npos)
	{
		_str.replace(this_pos, this_len, replace_with, that_pos, that_len);

		return *this;
	}
	str& replace(const char* replace_with, const std::string::const_iterator& this_begin, const std::string::const_iterator& this_end)
	{
		_str.replace(this_begin, this_end, replace_with);

		return *this;
	}
	str& replace(const char c, const size_t this_pos, const size_t this_len, const size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		_str.replace(this_pos, this_len, repeat(c, n, sep, delim));

		return *this;
	}
	str& replace(const char c, const std::string::const_iterator& this_begin, const std::string::const_iterator& this_end, size_t n = 1, const std::string& sep = std::string(), const std::string& delim = std::string())
	{
		_str.replace(this_begin, this_end, repeat(c, n, sep, delim));

		return *this;
	}
	str& replace(const std::initializer_list<char> replace_with, const std::string::const_iterator& this_begin, const std::string::const_iterator& this_end)
	{
		_str.replace(this_begin, this_end, replace_with);

		return *this;
	}
	
	static std::string& find_and_replace(std::string& str_, const std::string& to_find, const std::string& to_replace, const bool case_sensitive = true)
	{
		size_t pos = case_sensitive ? str_.find(to_find) : to_lower(str_).find(to_lower(to_find));
		const size_t len = str_.length();

		while (pos != std::string::npos)
		{
			str_.replace(pos, len, to_replace);
			pos = case_sensitive ? str_.find(to_find) : to_lower(str_).find(to_lower(to_find));
		}

		return str_;
	}
	str& find_and_replace(const str& to_find, const str& to_replace, const bool case_sensitive = true)
	{
		size_t pos = case_sensitive ? _str.find(to_find._str) : to_lower(_str).find(to_lower(to_find._str));
		const size_t len = length();

		while (pos != std::string::npos)
		{
			_str.replace(pos, len, to_replace._str);
			pos = case_sensitive ? _str.find(to_find._str) : to_lower(_str).find(to_lower(to_find._str));
		}

		return *this;
	}
	
	// TODO: static function versions of (compare) that take an STL string.
	// TODO: document (compare).
	
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of two STL strings . (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const std::string& str_l, const std::string& str_r, const bool case_sensitive = true, size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos) 
	{
		if (case_sensitive)
			return str_l.compare(pos_l, len_l, str_r.substr(pos_r, len_r));

		const std::string str_l_ = to_lower(str_l).substr(pos_l, len_l);
		const std::string str_r_ = to_lower(str_r).substr(pos_r, len_r);

		return str_l_.compare(str_r);
	}
	
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of two extended strings. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const str& str_l, const str& str_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		return compare(str_l._str, str_r._str, case_sensitive, pos_l, len_l, pos_r, len_r);
	}
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of this extended string and another. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	int compare(const str& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos, const size_t pos_ = 0, const size_t len_ = std::string::npos) const
	{
		return compare(*this, str_, case_sensitive, pos, len, pos_, len_);
	}

	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of an extended string on the left hand side and an STL string on the right hand side. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const str& str_l, const std::string& str_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		return compare(str_l._str, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of an STL string on the left hand side and an extended string on the right hand side. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const std::string& str_l, const str& str_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		return compare(str_l, str_r._str, case_sensitive, pos_l, len_l, pos_r, len_r);
	}
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of this extended string on the left hand side and an STL string on the right hand side. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	int compare(const std::string& str_, const bool case_sensitive = true, const size_t pos = 0, const size_t len = std::string::npos, const size_t pos_ = 0, const size_t len_ = std::string::npos) const
	{
		return compare(_str, str_, case_sensitive, pos, len, pos_, len_);
	}

	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of two character arrays. (sub-arrays can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two character arrays are equal.
	(B) smaller than zero
		if the first character of the left-hand array that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand array that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const char* char_arr_l, const char* char_arr_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		const std::string str_l = char_arr_l, str_r = char_arr_r;
		
		return compare(str_l, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}

	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of an STL string on the left hand side and a character array on the right hand side. (sub-strings/sub-arrays can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal.
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const std::string& str_l, const char* char_arr_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		const std::string str_r = char_arr_r;
		
		return compare(str_l, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of a character array on the left hand side and an STL string on the right hand side. (sub-strings/sub-arrays can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal (having the same character sequence).
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const char* char_arr_l, const std::string& str_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		const std::string str_l = char_arr_l;
		
		return compare(str_l, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}

	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of an extended string on the left hand side and a character array on the right hand side. (substrings/sub-arrays can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal (having the same character sequence).
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const str& str_l, const char* char_arr_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		const std::string str_r = char_arr_r;
		
		return compare(str_l, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}
	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequences of a character array on the left hand side and an extended string on the right hand side. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal (having the same character sequence).
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	static int compare(const char* char_arr_l, const str& str_r, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos)
	{
		const std::string str_l = char_arr_l;

		return compare(str_l, str_r, case_sensitive, pos_l, len_l, pos_r, len_r);
	}

	/*
	returns an integer indicating the result of performing a (by default, case-sensitive) lexicographical comparison between the character sequence of this extended string on the left hand side with that of a character array on the right hand side. (substrings can be defined through a starting offset and a length that includes the said offset).

	the returned value is:
	(A) equal to 0
		if the two strings are equal (having the same character sequence).
	(B) smaller than zero
		if the first character of the left-hand string that does not match has a smaller ASCII value, or if the entire left-hand string matches but has a smaller length.
	(C) greater than zero
		if the first character of the left-hand string that does not match has a greater ASCII value, or if the entire left-hand string matches but has a greater length.
	*/
	int compare(const char* char_arr, const bool case_sensitive = true, const size_t pos_l = 0, const size_t len_l = std::string::npos, const size_t pos_r = 0, const size_t len_r = std::string::npos) const
	{
		const std::string str_ = char_arr;
		
		return compare(_str, str_, case_sensitive, pos_l, len_l, pos_r, len_r);
	}

	// TODO: document comparison operators.
	
	friend bool operator==(const str&, const str&) noexcept;
	friend bool operator==(const str&, const std::string&);
	friend bool operator==(const str&, const char*);
	friend bool operator==(const std::string&, const str&);
	friend bool operator==(const char*, const str&);
	
	friend bool operator!=(const str&, const str&) noexcept;
	friend bool operator!=(const str&, const std::string&);
	friend bool operator!=(const str&, const char*);
	friend bool operator!=(const std::string&, const str&);
	friend bool operator!=(const char*, const str&);

	friend bool operator<(const str&, const str&) noexcept;
	friend bool operator<(const str&, const std::string&);
	friend bool operator<(const str&, const char*);
	friend bool operator<(const std::string&, const str&);
	friend bool operator<(const char*, const str&);
	
	friend bool operator<=(const str&, const str&) noexcept;
	friend bool operator<=(const str&, const std::string&);
	friend bool operator<=(const str&, const char*);
	friend bool operator<=(const std::string&, const str&);
	friend bool operator<=(const char*, const str&);
	
	friend bool operator>(const str&, const str&) noexcept;
	friend bool operator>(const str&, const std::string&);
	friend bool operator>(const str&, const char*);
	friend bool operator>(const std::string&, const str&);
	friend bool operator>(const std::string&, const char*);
	friend bool operator>(const char*, const str&);

	friend bool operator>=(const str&, const str&) noexcept;
	friend bool operator>=(const str&, const std::string&);
	friend bool operator>=(const str&, const char*);
	friend bool operator>=(const std::string&, const str&);
	friend bool operator>=(const std::string&, const char*);
	friend bool operator>=(const char*, const str&);

	// returns this extended string that is the result of concatenating two given extended strings.
	friend str operator+(const str&, const str&);
	// returns this extended string that is the result of concatenating an extended string with an STL string.
	friend str operator+(const str&, const std::string&);
	// returns this extended string that is the result of concatenating an STL string with an extended string.
	friend str operator+(const std::string&, const str&);
	// returns this extended string that is the result of concatenating an extended string with a character array.
	friend str operator+(const str&, const char*);
	// returns this extended string that is the result of concatenating a character array with an extended string.
	friend str operator+(const char*, const str&);
	// returns this extended string that is the result of concatenating an extended string with a character.
	friend str operator+(const str&, char);
	// returns this extended string that is the result of concatenating a character array with an extended string.
	friend str operator+(char, const str&);

	/*
	extracts characters from a given input stream and stores them into this extended string until a given character (a newline character, by default) is encountered (which will not be stored), or until the end-of-file (EOF) is encountered - whichever comes first.
	the content of this extended string before the call, if any, is replaced.
	
	The function returns the input stream from which characters were extracted.
	*/
	std::istream& getline(std::istream& input_stream, const char& delim = '\n')
	{
		return std::getline(input_stream, _str, delim);
	}
	/*
	extracts characters from a given input stream and stores them into a given extended string until a given character (a newline character, by default) is encountered (which will not be stored), or until the end-of-file (EOF) is encountered - whichever comes first.

	The function returns the input stream from which extraction has occurred.
	*/
	static std::istream& getline(std::istream& input_stream, str& str_, const char& delim = '\n')
	{
		return std::getline(input_stream, str_._str, delim);
	}
	
	// extracts a character sequence from a given input stream and stores it into a given extended string (replacing its content). Note that extraction stops at the first whitespace character or at the end-of-file (EOF), whichever comes first. The operator returns the input stream from which characters were extracted.			
	friend std::istream& operator>>(std::istream&, str&);
	// inserts a copy of the character sequence that is the content of a given extended string into a given output stream. The operator returns the output stream to which characters were inserted.
	friend std::ostream& operator<<(std::ostream&, const str&);
	
	// outputs an STL string followed by a newline to an output stream (the console by default), which is returned. The stream is not flushed by default.
	static std::ostream& print_line(const std::string& str_, const bool flush = false, std::ostream& output_stream = std::cout)
	{
		output_stream << str_ << (flush ? std::endl : '\n');

		return output_stream;
	}
	// outputs this extended string to an output stream (the console by default), which is returned. The stream is not flushed by default.
	std::ostream& print_line(const bool flush = false, std::ostream& output_stream = std::cout) const
	{
		output_stream << _str << (flush ? std::endl : '\n');

		return output_stream;
	}

	// outputs an STL string followed by a newline to a file. The stream is not flushed by default.
	static void print_line(const std::string& str_, const std::string& file_path, const bool flush = false)
	{
		std::fstream file_stream(file_path, std::ios::out);
		
		file_stream << str_ << (flush ? std::endl : '\n');
	}
	// outputs this extended string followed by a newline to a file. The stream is not flushed by default.
	void print_line(const std::string& file_path, const bool flush = false) const
	{
		std::fstream file_stream(file_path, std::ios::out);
		
		file_stream << _str << (flush ? std::endl : '\n');
	}
};

inline std::string operator*(const std::string& str_, const size_t n)
{
	return str::repeat(str_, n);
}
inline std::string& operator*=(std::string& str_, const size_t n)
{
	str_ = str::repeat(str_, n);

	return str_;
}

inline str operator*(const str& str_, const size_t n)
{
	return str_.repeat(n);
}
inline str& operator*=(str& str_, const size_t n)
{
	str_ = str_.repeat(n);

	return str_;
}

inline bool operator==(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str == str_r._str);
}
inline bool operator==(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str == stl_str_r);
}
inline bool operator==(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() == char_arr_r);
}
inline bool operator==(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l == str_r._str);
}
inline bool operator==(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l == str_r.c_str());
}

inline bool operator!=(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str != str_r._str);
}
inline bool operator!=(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str != stl_str_r);
}
inline bool operator!=(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() != char_arr_r);
}
inline bool operator!=(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l != str_r._str);
}
inline bool operator!=(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l != str_r.c_str());
}

inline bool operator<(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str < str_r._str);
}
inline bool operator<(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str < stl_str_r);
}
inline bool operator<(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() < char_arr_r);
}
inline bool operator<(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l < str_r._str);
}
inline bool operator<(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l < str_r.c_str());
}

inline bool operator<=(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str <= str_r._str);
}
inline bool operator<=(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str <= stl_str_r);
}
inline bool operator<=(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() <= char_arr_r);
}
inline bool operator<=(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l <= str_r._str);
}
inline bool operator<=(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l <= str_r.c_str());
}

inline bool operator>(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str > str_r._str);
}
inline bool operator>(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str > stl_str_r);
}
inline bool operator>(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() > char_arr_r);
}
inline bool operator>(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l > str_r._str);
}
inline bool operator>(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l > str_r.c_str());
}

inline bool operator>=(const str& str_l, const str& str_r) noexcept
{
	return (str_l._str >= str_r._str);
}
inline bool operator>=(const str& str_l, const std::string& stl_str_r)
{
	return (str_l._str >= stl_str_r);
}
inline bool operator>=(const str& str_l, const char* char_arr_r)
{
	return (str_l.c_str() >= char_arr_r);
}
inline bool operator>=(const std::string& stl_str_l, const str& str_r)
{
	return (stl_str_l >= str_r._str);
}
inline bool operator>=(const char* char_arr_l, const str& str_r)
{
	return (char_arr_l >= str_r.c_str());
}

inline str operator+(const str& str_l, const str& str_r)
{
	return (str_l._str + str_r._str);
}
inline str operator+(const str& str_, const std::string& std_str)
{
	return (str_._str + std_str);
}
inline str operator+(const std::string& std_str, const str& str_)
{
	return (std_str + str_._str);
}
inline str operator+(const str& str_, const char* char_array)
{
	return (str_._str + char_array);
}
inline str operator+(const char* char_array, const str& str_)
{
	return (char_array + str_._str);
}
inline str operator+(const str& str_, char c)
{
	return (str_._str + c);
}
inline str operator+(char c, const str& str_)
{
	return (c + str_._str);
}

inline std::istream& operator>>(std::istream& input_stream, str& str_)
{
	return std::operator>>(input_stream, str_._str);
}
inline std::ostream& operator<<(std::ostream& output_stream, const str& str_)
{
	return std::operator<<(output_stream, str_._str);
}