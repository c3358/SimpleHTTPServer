#include "StringUtils.h"

#include <algorithm>
#include <functional>
#include <sstream>

namespace utils
{
	std::vector<std::string> split(std::string string, std::string delim, int count)
	{
		std::vector<std::string> rv;

		size_t n = string.find(delim);

		while (n != std::string::npos && count != 0) {
			//Add the first part of the string to the vector
			rv.push_back(string.substr(0, n));
			//Erase the cut part (we include the delimnator this time
			string.erase(0, n + delim.length());

			//Set the variables
			n = string.find(delim);
			count--;
		}

		//Add the rest of the string to the vector, if not empty
		if (!string.empty()) rv.push_back(string);

		return rv;
	}

	std::string
	concat(std::initializer_list<std::string> args, std::string delim, int beginOffset, int endOffset)
	{
		std::ostringstream os;
		//Std::copy expects a pointer to 1 past the last element of an array. So, by subtracting one here, it copies all but the last.
		std::copy(args.begin() + beginOffset, args.end() - endOffset,
				  std::ostream_iterator<std::string>(os, delim.c_str()));
		//args.end() returns a pointer to 1 past the last element of an array. So, we need to subtract one.
		os << *(args.end() - 1);

		return os.str();
	}

	std::string concat(std::vector<std::string> args, std::string delim, int beginOffset, int endOffset)
	{
		std::ostringstream os;
		std::copy(args.begin() + beginOffset, args.end() - endOffset,
				  std::ostream_iterator<std::string>(os, delim.c_str()));
		os << args.back();

		return os.str();
	}

	void ltrim(std::string &string)
	{
		string.erase(string.begin(),
					 std::find_if(string.begin(), string.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	void rtrim(std::string &string)
	{
		string.erase(
				std::find_if(string.rbegin(), string.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
				string.end());
	}

	void trim(std::string &string)
	{
		ltrim(string);
		rtrim(string);
	}

	bool beginsWith(std::string str, std::string begin)
	{
		return str.substr(0, begin.length()) == begin;
	}

	bool endsWith(std::string str, std::string end)
	{
		size_t beginIndex = str.length() - end.length();
		return str.substr(beginIndex, end.length()) == end;
	}

	void replace(std::string &src, std::string sub, std::string replace, int count)
	{
		while (count != 0) {
			size_t index = 0;
			///Find the substring
			index = src.find(sub, index);
			if (index == std::string::npos) break;

			//Replace
			src.replace(index, sub.length(), replace);

			//Move the variables
			index += sub.length();
			count--;
		}
	}
}