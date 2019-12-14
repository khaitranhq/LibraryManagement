#pragma once

#include <string>
using namespace std;

string toUpper(string s) {
	for (int i = 0; i < s.size(); ++i)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] += ('A' - 'a');
	return s;
}