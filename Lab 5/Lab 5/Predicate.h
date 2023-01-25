#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"
#include <vector>
#include <iostream>

using namespace std;

class Predicate {
private:
	string ID;
	vector<Parameter> parameterVector;
public:
	Predicate(){}
	Predicate(string newID, vector<Parameter> newParameterVector) {
		ID = newID;
		parameterVector = newParameterVector;
	}
	void toString() {
		cout << ID << "(";
		for (unsigned int i = 0; i < parameterVector.size(); i++) {
			parameterVector.at(i).toString();
			if (i < (parameterVector.size() - 1)) cout << ",";
		}
		cout << ")";
	}

	string getID() {
		return ID;
	}
	vector<Parameter> getParamVector() {
		return parameterVector;
	}
};

#endif