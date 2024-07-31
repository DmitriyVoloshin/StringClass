#include <stdio.h>
#include <iostream>
#include <limits>

#include "mString.h"
#include "utils.h"


mString::~mString()
{
	delete[] text;
}

mString::mString()
{
	length = 1;
	text = new char[length];
	text[length - 1] = '\0';
}

mString::mString(const char* s)
{
	if (s != nullptr)
	{
		length = std::strlen(s) + 1;
		text = new char[length];

		std::strcpy(text, s);
		text[length - 1] = '\0';
	}
	else
	{
		length = 1;
		text = new char[length];
		text[length - 1] = '\0';
	}
}

mString::mString(const mString& s)
{
	length = s.length;
	text = new char[length];
	std::strcpy(text, s.text);
}

mString::mString(mString&& rval) noexcept
{
	length = rval.length;
	text = rval.text;

	rval.text = nullptr;
	rval.length = 0;
}

int mString::getLength() const noexcept
{
	return length - 1;
}

const char* mString::c_str() const noexcept
{
	return text;
}

void mString::pushBack(char c)
{
	size_t sumLength = length + 1;
	if (sumLength < length)
		return;

	char* sumText = new char[sumLength];

	std::strcpy(sumText, text);
	sumText[length - 1] = c;

	delete[] text;

	text = sumText;
	length = sumLength;

	text[length - 1] = '\0';
}

mString& mString::operator=(const mString &rhs)
{
	mString temp {rhs};
	swap(*this, temp);

	return *this;
}

mString& mString::operator=(mString&& rval) noexcept
{
	swap(*this, rval);
	return *this;
}

mString& mString::operator+=(const char* rhs)
{
	size_t charLength = std::strlen(rhs);

	size_t sumLength = length + charLength;
	if (sumLength < length)
		return *this;

	char* sumText = new char[sumLength];

	std::strcpy(sumText, text);
	std::strcpy(&sumText[length-1], rhs);

	delete[] text;

	text = sumText;
	length = sumLength;

	text[length - 1] = '\0';

	return *this;
}

mString& mString::operator+=(const mString& rhs)
{
	size_t sumLength = length + rhs.length - 1;

	if (sumLength < length)
		return *this;

	char* sumText = new char[sumLength];

	std::strcpy(sumText, text);
	std::strcpy(&sumText[length-1], rhs.text);

	delete[] text;
	text = sumText;
	length = sumLength;

	return *this;
}

mString& mString::operator+=(mString&& rhs)
{
	size_t sumLength = length + rhs.length - 1;

	if (sumLength < length)
		return *this;

	char* sumText = new char[sumLength];

	std::strcpy(sumText, text);
	std::strcpy(&sumText[length-1], rhs.text);

	delete[] text;
	text = sumText;
	length = sumLength;

	return *this;
}
// Test this
char& mString::operator[](size_t index)
{
	return text[index];
}
// Test this
bool mString::operator==(const mString& rhs) const
{
	return true;
}
// Test this
bool mString::operator<(const mString& rhs) const
{
	return true;
}


template <typename T>
mString operator+(T&& lhs, const mString& rhs)
{
	return mString();
}

template <typename T>
mString operator+(const mString& rhs, T&& lhs)
{
	return mString();
}


mString operator+(const mString& lhs, const mString& rhs)
{
	return std::move(mString {lhs} += rhs);
}


mString operator+(const mString& lhs, const char* rhs)
{
	return std::move(mString {lhs} += rhs);
}

mString operator+(const mString& lhs, char rhs)
{
	mString temp {lhs};
	temp.pushBack(rhs);
	return temp;
}


std::ostream& operator<< (std::ostream& stream, const mString& s)
{
	if (s.getLength() != 0) {
		stream << s.c_str();
	}
	return stream;
}

std::istream& operator>> (std::istream& stream, mString& s)
{
	char in;
	stream.get(in);
	while ((in != EOF) && (in != '\n'))
	{
		s.pushBack(in);
		stream.get(in);
	}
	return stream;
}

void swap(mString& lhs, mString& rhs) noexcept
{
	std::swap(lhs.length, rhs.length);
	std::swap(lhs.text, rhs.text);
}

