#include <stdio.h>

#include "String.h"
#include "utils.h"

#include <iostream>

String::~String()
{
	delete[] text;
}

String::String()
{
	length = 1;
	text = new char[length];
	text[length - 1] = '\0';
	//std::cout << "In String()\n";
}

String::String(const char* s)
{
	if (s != nullptr)
	{
		length = strlen(s) + 1;
		text = new char[length];

		strcpy(text, s);
		text[length - 1] = '\0';
	}
	else
	{
		length = 1;
		text = new char[length];
		text[length - 1] = '\0';
	}
	//std::cout << "In String(const char* )\n";
}

String::String(const String& s)
{
	length = s.length; // а не тот ли самый объект тут?
	text = new char[length];
	strcpy(text, s.text);
	//std::cout << "In String(const String& )\n";
}

String::String(String&& rval)
{
	length = rval.length; // а не тот ли самый объект тут?
	text = rval.text;

	rval.text = nullptr;
	rval.length = 0;
	//std::cout << "In String(String&& )\n";
}

int String::getLength() const
{
	return length - 1;
}

const char* String::getText() const
{
	return text;
}

void String::pushBack(char c)
{
	int sumLength = length + 1;
	char* sumText = new char[sumLength];

	strcpy(sumText, text);
	sumText[length - 1] = c;

	delete[] text;

	text = sumText;
	length = sumLength;

	text[length - 1] = '\0';
}

String& String::operator=(const String &rhs)
{
	if (this != &rhs)
	{
		delete[] text;

		length = rhs.length;
		text = new char[length];

		strcpy(text, rhs.text);
		//std::cout << "In operator=(const String& )\n";
	}
	return *this;
}

String& String::operator=(String &&rval)
{
	if (this != &rval)
	{
		delete[] text;

		text = rval.text;
		length = rval.length;

		rval.text = nullptr;
		rval.length = 0;
		//std::cout << "In operator=(String&& )\n";
	}
	return *this;
}

String& String::operator+=(const char* rhs)
{
	int charLength = strlen(rhs);

	int sumLength = length + charLength;
	char* sumText = new char[sumLength];

	strcpy(sumText, text);
	strcpy(&sumText[length-1], rhs);

	delete[] text;

	text = sumText;
	length = sumLength;

	text[length - 1] = '\0';

	//std::cout << "In operator+=(char* )\n";
	return *this;
}

String& String::operator+=(const String& rhs)
{
	int sumLength = length + rhs.length - 1;

	char* sumText = new char[sumLength];

	strcpy(sumText, text);
	strcpy(&sumText[length-1], rhs.text);

	delete[] text;
	text = sumText;
	length = sumLength;

	//std::cout << "In operator+=(String& )\n";

	return *this;
}

String& String::operator+=(String&& rhs)
{
	int sumLength = length + rhs.length - 1;

	char* sumText = new char[sumLength];

	strcpy(sumText, text);
	strcpy(&sumText[length-1], rhs.text);

	delete[] text;
	text = sumText;
	length = sumLength;

	//std::cout << "In operator+=(String&& )\n";

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	//std::cout << "In operator+(String, String)\n";
	return String {lhs} += rhs;
}


String operator+(const String& lhs, const char* rhs)
{
	//std::cout << "In operator+(String, char*)\n";
	return String {lhs} += rhs;
}

String operator+(const String& lhs, char rhs)
{
	String temp {lhs};
	temp.pushBack(rhs);
	return temp;
}

std::ostream& operator<< (std::ostream& stream, const String& s)
{
	//std::cout << "In operator<<()\n";
	if (s.getLength() != 0) {
		stream << s.getText();
	}
	return stream;
}

std::istream& operator>> (std::istream& stream, String& s)
{
	//std::cout << "In operator>>()\n";
	char in;
	stream.get(in);
	while ((in != EOF) && (in != '\n'))
	{
		s.pushBack(in);
		stream.get(in);
	}
	return stream;
}
