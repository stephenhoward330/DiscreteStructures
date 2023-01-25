#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include "Parameter.h"

using namespace std;

class Parameter;

class Expression {
private:
	bool isPlus; // False == *
	Parameter* leftParam;
	Parameter* rightParam;
public:
	Expression(bool newIsPlus, Parameter* newLeftParam, Parameter* newRightParam) {
		isPlus = newIsPlus;
		leftParam = newLeftParam;
		rightParam = newRightParam;
	}
	void toString();
};

#endif