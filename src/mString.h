#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <iostream>

class mString {

private:
	std::size_t length;
	char* text;

	void addNullTerminator();

public:
	~mString();

	mString();
	mString(const char* s);
	mString(const mString& s);
	mString(mString&& rval) noexcept;

	int getLength() const noexcept;
	const char* c_str() const noexcept;

	void pushBack(char c);

	//mString& operator=(const char* rhs); // implement me
	mString& operator=(const mString &rhs);
	mString& operator=(mString &&rval) noexcept;

	mString& operator+=(char rhs); // implement me
	mString& operator+=(const char* rhs);
	mString& operator+=(const mString& rhs);
	mString& operator+=(mString&& rhs);
	char& operator[](size_t index);

	bool operator==(const mString& rhs) const;
	bool operator<(const mString& rhs) const;
	//bool operator>(const mString& rhs) const;  // implement me

	friend void swap(mString& lhs, mString& rhs) noexcept;
};

mString operator+(const mString& lhs, const mString& rhs);
mString operator+(const mString& lhs, const char* rhs);
//mString operator+(const char* rhs, const mString& lhs); // implement me
mString operator+(const mString& lhs, char rhs); // implement me
//mString operator+(char lhs, const mString& rhs); // implement me

std::ostream& operator<< (std::ostream& stream, const mString& s);
std::istream& operator>> (std::istream& stream, mString& s);
bool stringCaseInsensitiveComparator(const mString &lhs, const mString &rhs);


#endif /* MY_STRING_H_ */
