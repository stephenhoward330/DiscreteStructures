#include "Expression.h"

void Expression::toString() {
	cout << "(";

	cout << "we here" << endl;

	leftParam->toString();
	if (isPlus == true) cout << "+";
	else cout << "*";
	rightParam->toString();
	cout << ")";
}