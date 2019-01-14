
#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <vector>
#include <string>

using namespace std;

class StringHelper {
public:
	static void addSpaces(string& line);
	static string getArgument(vector<string>& arguments);
	static vector<string> split(string line, const char* delim);
	static bool endsWith(const string s, const string suffix);
	static bool startsWith(const string s, const string prefix);
	static vector<vector<string>> splitVector(const vector<string>& vec, const char* delim);
	static vector<string> removeUntill(vector<string> v, const string s);
	static int nextIndexOf(vector<string>::iterator itr, const string s, vector<string>::iterator end);

};

#endif