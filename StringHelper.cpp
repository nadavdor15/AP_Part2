#define SHOULD_GET_SPACES ",+,-,*,/,<,<=,>,>=,!=,==,=,(,),{,},[,],(),[],{},!,"
#define DOUBLE_CHAR_OPERANTS ",<=,>=,==,!=,"
#include "StringHelper.h"
#include <stdio.h>

using namespace std;

/*
* adds spaces to a line before and after operators.
* */
void StringHelper::addSpaces(string& line) {
  	string needSpaces = string(SHOULD_GET_SPACES);
  	string doubleCharSpaces = string(DOUBLE_CHAR_OPERANTS);
  	string seperator = ",";
	for (unsigned int i = 0; (i + 1) < line.length(); i++) {
		if (line[i] == '\"')
			while (line[++i] != '\"') {}
		if (needSpaces.find(seperator + line[i] + seperator) != string::npos) {
			if (doubleCharSpaces.find(seperator + line.substr(i, 2) + seperator) != string::npos) {
				line.insert(i + 2, " ");
				line.insert(i, " ");
				i++;
			} else {
		    	line.insert(i + 1, " ");
    			line.insert(i, " ");
    		}
    		i+=2;
	  	}
	}
}

/*
* returns a string concatenating a vector of strings.
* */
string StringHelper::getArgument(vector<string>& arguments) {
	string argument = "";
	for (string arg : arguments)
		argument += (arg + " ");
	return argument;
}

/*
* gets a string and splits it by a given set of strings.
* returns a vector of strings.
* */
vector<string> StringHelper::split(string line, const char* delim) {
	vector<string> commands;
	unsigned int firstIndex;
	while ((firstIndex = line.find_first_of(delim)) < line.length()) {
		string word = line.substr(0, firstIndex);
		if (word.length())
			commands.push_back(word);
		line = line.substr(++firstIndex);
	}
	if (line.length())
		commands.push_back(line);
	return commands;
}

/*
* returns whether the string s ends with the string suffix.
* */
bool StringHelper::endsWith(const string s, const string suffix) {
	unsigned int suffixLen = suffix.size();
	unsigned int sLen = s.size();
	if (sLen < suffixLen)
		return false;
	else 
		return (s.compare(sLen - suffixLen, suffixLen, suffix) == 0);
}

/*
* returns whether the string s starts with the string prefix.
* */
bool StringHelper::startsWith(const string s, const string prefix) {
	unsigned int prefixLen = prefix.size();
	unsigned int sLen = s.size();
	if (sLen < prefixLen)
		return false;
	else 
		return (s.compare(0, prefixLen, prefix) == 0);
}

/*
* splits a vector of strings to e vector of vectors of strings by a given character to split by.
* */
vector<vector<string>> StringHelper::splitVector(const vector<string>& vec, const char* delim) {
  vector<vector<string>> total;
  vector<string> current;
  auto end = vec.end();
  auto before = vec.begin();
  for (auto it = vec.begin(); it != end;) {
    if (it->find(delim) != string::npos) {
      current = vector<string>(before, it++);
      if (current.size())
        total.push_back(current);
      before = it;
    } else
      ++it;
  }
    current = vector<string>(before, end);
    if (current.size())
      total.push_back(current);
    return total;
}


/*
* removes all strings from a vector of strings untill reached the flag s.
* watch out! can remove the whole vector!
* returns a new vector.
*/
vector<string> StringHelper::removeUntill(vector<string> v, const string s) {
	while (v.begin()->compare(s) != 0 && v.size())
		v.erase(v.begin());
	if (v.size())
    	v.erase(v.begin());
	return v;
}

/*
* returns the next index where we have the string s in a vector of strings.
* */
int StringHelper::nextIndexOf(vector<string>::iterator itr, const string s, vector<string>::iterator end) {
	int i = 0;
	while (itr != end && itr->compare(s) != 0) {
		++itr;
		++i;
	}
	return i;
}
