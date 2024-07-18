#include "CppUTest/TestHarness.h"
#include <sstream>
#include <cstring>

#include "../src/String.h"
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
	String s {};

	LONGS_EQUAL(0, s.getLength());
	STRCMP_EQUAL("", s.getText());
}

TEST(MyStringTest, CanCreateAStringFromCharArrayWithTheSameLength)
{
	String s {"Hello World"};

	LONGS_EQUAL(11, s.getLength());
	STRCMP_EQUAL("Hello World", s.getText());
}

TEST(MyStringTest, nullptrCharCreatesEmptyString)
{
	char* str = nullptr;
	String s {str};

	LONGS_EQUAL(0, s.getLength());
	STRCMP_EQUAL("", s.getText());
}

TEST(MyStringTest, CanAssignAStringFromCharArray)
{
	String s {};

	s = "Big World!";

	LONGS_EQUAL(10, s.getLength());
	STRCMP_EQUAL("Big World!", s.getText());
}

TEST(MyStringTest, CanConstructAStringFromAnotherString)
{
	String s1 {"Green world"};
	String s2 {s1};

	STRCMP_EQUAL(s1.getText(), s2.getText());
}

TEST(MyStringTest, CanStreamAsAnOutput)
{
	String s {"Test World"};

	std::cout << s << std::endl;
}

TEST(MyStringTest, CanGetResultOfAddingStrings)
{
	String s1 {"Test World"};
	String s2 {" is very good"};

	String s3 = s1 + s2;

	STRCMP_EQUAL("Test World is very good", s3.getText());
}

TEST(MyStringTest, CanAssignAStringFromAnotherString)
{
	String s1 {"Test World"};
	String s2 {" is very good"};

	s2 = s1;

	STRCMP_EQUAL(s1.getText(), s2.getText());
}

TEST(MyStringTest, CanCreateAStringFromRValueString)
{
	String s1 {std::move(String("Moved string"))};

	STRCMP_EQUAL("Moved string", s1.getText());
}

TEST(MyStringTest, CanAddACharStringToAString1)
{
	String s1 {"Test World"};
	String s2 = s1 + " is so green";

	STRCMP_EQUAL("Test World is so green", s2.getText());
}

TEST(MyStringTest, CanAddACharToAString)
{
	String s1 {"Test World"};
	String s2 = s1 + '!';

	STRCMP_EQUAL("Test World!", s2.getText());
}

TEST(MyStringTest, CanAddACharStringToAString2)
{
	String s1 {" is so green"};
	String s2 = "Test World" + s1;

	STRCMP_EQUAL("Test World is so green", s2.getText());
}

TEST(MyStringTest, CanUsePlusEqualsOperator)
{
	String s1 {"Test World"};
	String s2 {" is very good"};

	s1 += s2;

	STRCMP_EQUAL("Test World is very good", s1.getText());
}

TEST(MyStringTest, CanUsePlusEqualsCharStringOperator)
{
	String s1 {"Test World"};

	s1 += " is very good";

	STRCMP_EQUAL("Test World is very good", s1.getText());
}

TEST(MyStringTest, CanUsePlusEqualsRValueString)
{
	const char* str = "Test World is very good";
	String s1 {"Test World"};

	s1 += String {" is very good"};

	STRCMP_EQUAL(str, s1.getText());
}

TEST(MyStringTest, GreaterToLowerCompareEqualsFalse)
{
	String s1 {"Test World"};
	String s2 {"Test"};

	bool result = stringCaseInsensitiveComparator(s1, s2);

	CHECK_FALSE(result);
}

TEST(MyStringTest, LowerToGreaterCompareEqualsTrue)
{
	String s1 {"Test World"};
	String s2 {"Test"};

	bool result = stringCaseInsensitiveComparator(s2, s1);

	CHECK_TRUE(result);
}

TEST(MyStringTest, LowerToGreaterCompareEqualsTrueNoMatterCharCase)
{
	String s1 {"Test World"};
	String s2 {"test"};

	bool result = stringCaseInsensitiveComparator(s2, s1);

	CHECK_TRUE(result);
}

TEST(MyStringTest, GreaterToLowerCompareEqualsFalseNoMatterCharCase)
{
	String s1 {"Test World"};
	String s2 {"tEsT"};

	bool result = stringCaseInsensitiveComparator(s1, s2);

	CHECK_FALSE(result);
}

TEST(MyStringTest, CanReadFromAStream)
{
	String s{};
	std::istringstream in{"Test World is a new World!\n"};

	in >> s;

	STRCMP_EQUAL("Test World is a new World!", s.getText());
}

TEST(MyStringTest, CanPushBack)
{
	String s {"Hello"};

	s.pushBack(' ');
	s.pushBack('W');
	s.pushBack('o');
	s.pushBack('r');
	s.pushBack('l');
	s.pushBack('d');

	STRCMP_EQUAL("Hello World", s.getText());
}


