#include <iostream>
#include <vector>
#include <algorithm>

#include "String.h"
#include "utils.h"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << std::endl <<"No parameters passed." << std::endl;
		std::cout << "Please add executable parameters." << std::endl;
		std::cout << "Usage example:\n ./StringClass.exe firstString secondString oneMoreString etc.." << std::endl;
		std::cout << "To use spaces in strings place them in quotes. Usage example:" << std::endl;
		std::cout << "./StringClass.exe \"long long string\" \"one more string\"" << std::endl;
		return 1;
	}

	std::vector<mString> myStrings;
	myStrings.reserve(10);

	for (int i = 1; i < argc; i++)
	{
		myStrings.push_back(mString{argv[i]});
	}

	std::cout << std::endl << "Entered strings are: " << std::endl;
	for(const mString& s : myStrings)
	{
		std::cout << s << std::endl;
	}

	std::cout << std::endl;

	std::sort(myStrings.rbegin(), myStrings.rend(), stringCaseInsensitiveComparator);
	std::cout << "Your input in reverse lexicographical order:" << std::endl;
	for(auto s : myStrings)
	{
		std::cout << s << std::endl;
	}
	
	return 0;
}
