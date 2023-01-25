#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <string>

using namespace std;

class Expression;

class Parameter {
private:
	string IDstring;
public:
	Parameter(string newIDstring) {
		IDstring = newIDstring;
	}
	string getIDstring() {
		return IDstring;
	}
	void toString() {
		cout << IDstring;
	}
};

#endif