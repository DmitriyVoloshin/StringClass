#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <iostream>

class String {

private:
	int length;
	char* text;

	void addNullTerminator();

public:
	~String();

	String();
	String(const char* s);
	String(const String& s);
	String(String&& rval);

	int getLength() const;
	const char* getText() const;

	void pushBack(char c);

	String& operator=(const String &rhs);
	String& operator=(String &&rval);

	String& operator+=(const char* rhs);
	String& operator+=(const String& rhs);
	String& operator+=(String&& rhs);
};

String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const String& lhs, char rhs);

std::ostream& operator<< (std::ostream& stream, const String& s);
std::istream& operator>> (std::istream& stream, String& s);
bool stringCaseInsensitiveComparator(const String &lhs, const String &rhs);


#endif /* MY_STRING_H_ */
