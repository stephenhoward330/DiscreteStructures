#ifndef PARAMETER_H
#define PARAMETER_H

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
		return this->IDstring;
	}
	void toString() {
		cout << IDstring;
	}
};

#endif