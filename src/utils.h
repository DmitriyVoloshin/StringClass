#ifndef UTILS_H_
#define UTILS_H_

#include <cstring>

#include "mString.h"

inline char* getLowerCaseCharArray(const char* input)
{
	int inputSize = std::strlen(input) + 1;
	char* output = new char[inputSize];

	for (int i = 0; i < inputSize; i++)
	{
		output[i] = tolower(input[i]);
	}
	return output;
}

inline bool stringCaseInsensitiveComparator(const mString &lhs, const mString &rhs)
{
	char* lhsLower = getLowerCaseCharArray(lhs.c_str());
	char* rhsLower = getLowerCaseCharArray(rhs.c_str());

	bool result = std::strcmp(lhsLower, rhsLower) < 0;

	delete[] lhsLower;
	delete[] rhsLower;

	return result;
}

#endif /* UTILS_H_ */
