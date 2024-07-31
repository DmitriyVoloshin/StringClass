#include <sstream>
#include <cstring>

#include "CppUTest/TestHarness.h"

#include "../src/mString.h"
#include "../src/utils.h"

TEST_GROUP(MyStringTest)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

TEST(MyStringTest, CanCreateAnEmptyString)
{
	mString s {};

	LONGS_EQUAL(0, s.getLength());
	STRCMP_EQUAL("", s.c_str());
}

TEST(MyStringTest, CanCreateAStringFromCharArrayWithTheSameLength)
{
	mString s {"Hello World"};

	LONGS_EQUAL(11, s.getLength());
	STRCMP_EQUAL("Hello World", s.c_str());
}

TEST(MyStringTest, nullptrCharCreatesEmptyString)
{
	char* str = nullptr;
	mString s {str};

	LONGS_EQUAL(0, s.getLength());
	STRCMP_EQUAL("", s.c_str());
}

TEST(MyStringTest, CanAssignAStringFromCharArray)
{
	mString s {};

	s = "Big World!";

	LONGS_EQUAL(10, s.getLength());
	STRCMP_EQUAL("Big World!", s.c_str());
}

TEST(MyStringTest, CanConstructAStringFromAnotherString)
{
	mString s1 {"Green world"};
	mString s2 {s1};

	STRCMP_EQUAL(s1.c_str(), s2.c_str());
}

TEST(MyStringTest, CanStreamAsAnOutput)
{
	mString s {"Test World"};

	std::cout << s << std::endl;
}

TEST(MyStringTest, CanGetResultOfAddingStrings)
{
	mString s1 {"Test World"};
	mString s2 {" is very good"};

	mString s3 = s1 + s2;

	STRCMP_EQUAL("Test World is very good", s3.c_str());
}

TEST(MyStringTest, CanAssignAStringFromAnotherString)
{
	mString s1 {"Test World"};
	mString s2 {" is very good"};

	s2 = s1;

	STRCMP_EQUAL("Test World", s1.c_str());
	STRCMP_EQUAL(s1.c_str(), s2.c_str());
}

TEST(MyStringTest, CanCreateAStringFromRValueString)
{
	mString s1 {std::move(mString("Moved string"))};

	STRCMP_EQUAL("Moved string", s1.c_str());
}

TEST(MyStringTest, MoveAssignmentKeepsSameObject)
{
	mString s1 {"Moved string"};

	s1 = std::move(s1);

	STRCMP_EQUAL("Moved string", s1.c_str());
}

TEST(MyStringTest, MoveAssignmentEmptiesRvalueObject)
{
	mString s1 {"Moved string"};
	mString s2 {};

	s2 = std::move(s1);

	STRCMP_EQUAL("Moved string", s2.c_str());
	STRCMP_EQUAL("", s1.c_str());
	LONGS_EQUAL(0, s1.getLength());
}

TEST(MyStringTest, CopyAssignmentSameObject)
{
	mString s1 {"Moved string"};

	const mString& s2 = s1;

	s1 = s2;

	STRCMP_EQUAL("Moved string", s1.c_str());
}

TEST(MyStringTest, CanAddACharStringToAString1)
{
	mString s1 {"Test World"};
	mString s2 = s1 + " is so green";

	STRCMP_EQUAL("Test World", s1.c_str());
	STRCMP_EQUAL("Test World is so green", s2.c_str());
}

TEST(MyStringTest, CanAddACharToAString)
{
	mString s1 {"Test World"};
	mString s2 = s1 + '!';

	STRCMP_EQUAL("Test World", s1.c_str());
	STRCMP_EQUAL("Test World!", s2.c_str());
}

TEST(MyStringTest, CanAddACharStringToAString2)
{
	mString s1 {" is so green"};
	mString s2 = "Test World" + s1;

	STRCMP_EQUAL(" is so green", s1.c_str());
	STRCMP_EQUAL("Test World is so green", s2.c_str());
}

TEST(MyStringTest, CanAddAnRvalueString)
{
	mString s1 {" is so green"};
	mString s2 = "Test World" + std::move(s1);

	STRCMP_EQUAL(" is so green", s1.c_str());
	STRCMP_EQUAL("Test World is so green", s2.c_str());
}

TEST(MyStringTest, CanUsePlusEqualsOperator)
{
	mString s1 {"Test World"};
	mString s2 {" is very good"};

	s1 += s2;

	STRCMP_EQUAL("Test World is very good", s1.c_str());
}

TEST(MyStringTest, CanUsePlusEqualsCharStringOperator)
{
	mString s1 {"Test World"};

	s1 += " is very good";

	STRCMP_EQUAL("Test World is very good", s1.c_str());
}

TEST(MyStringTest, CanUsePlusEqualsRValueString)
{
	const char* str = "Test World is very good";
	mString s1 {"Test World"};

	s1 += mString {" is very good"};

	STRCMP_EQUAL(str, s1.c_str());
}

TEST(MyStringTest, CanUsePlusEqualsSameObject)
{
	mString s1 {"Test World"};

	s1 += s1;

	STRCMP_EQUAL("Test WorldTest World", s1.c_str());
}

TEST(MyStringTest, CanUsePlusEqualsRValueSameString)
{
	mString s1 {"Test World"};

	s1 += std::move(s1);

	STRCMP_EQUAL("Test WorldTest World", s1.c_str());
}

TEST(MyStringTest, GreaterToLowerCompareEqualsFalse)
{
	mString s1 {"Test World"};
	mString s2 {"Test"};

	bool result = stringCaseInsensitiveComparator(s1, s2);

	CHECK_FALSE(result);
}

TEST(MyStringTest, LowerToGreaterCompareEqualsTrue)
{
	mString s1 {"Test World"};
	mString s2 {"Test"};

	bool result = stringCaseInsensitiveComparator(s2, s1);

	CHECK_TRUE(result);
}

TEST(MyStringTest, LowerToGreaterCompareEqualsTrueNoMatterCharCase)
{
	mString s1 {"Test World"};
	mString s2 {"test"};

	bool result = stringCaseInsensitiveComparator(s2, s1);

	CHECK_TRUE(result);
}

TEST(MyStringTest, GreaterToLowerCompareEqualsFalseNoMatterCharCase)
{
	mString s1 {"Test World"};
	mString s2 {"tEsT"};

	bool result = stringCaseInsensitiveComparator(s1, s2);

	CHECK_FALSE(result);
}

TEST(MyStringTest, CanReadFromAStream)
{
	mString s{};
	std::istringstream in{"Test World is a new World!\n"};

	in >> s;

	STRCMP_EQUAL("Test World is a new World!", s.c_str());
}

TEST(MyStringTest, CanPushBack)
{
	mString s {"Hello"};

	s.pushBack(' ');
	s.pushBack('W');
	s.pushBack('o');
	s.pushBack('r');
	s.pushBack('l');
	s.pushBack('d');

	STRCMP_EQUAL("Hello World", s.c_str());
}


