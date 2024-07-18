#ifndef UTILS_H_
#define UTILS_H_

#include <cstring>
#include "String.h"

inline char* getLowerCaseCharArray(const char* input)
{
	int inputSize = strlen(input) + 1;
	char* output = new char[inputSize];

	for (int i = 0; i < inputSize; i++)
	{
		output[i] = tolower(input[i]);
	}
	return output;
}

inline bool stringCaseInsensitiveComparator(const String &lhs, const String &rhs)
{
	char* lhsLower = getLowerCaseCharArray(lhs.getText());
	char* rhsLower = getLowerCaseCharArray(rhs.getText());

	bool result = strcmp(lhsLower, rhsLower) < 0;

	delete[] lhsLower;
	delete[] rhsLower;

	return result;
}

#endif /* UTILS_H_ */
