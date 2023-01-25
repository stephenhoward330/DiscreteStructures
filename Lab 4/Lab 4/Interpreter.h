#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {
private:
	DatalogProgram datalogProgram;
	Database database;
public:
	Interpreter(DatalogProgram newParser) {
		datalogProgram = newParser;
	}
	void interpretSchemes();
	void interpretFacts();
	void evaluateRules();
	void evaluateQueries();
	void interpretAll() {
		interpretSchemes();
		interpretFacts();
		evaluateRules();
		evaluateQueries();
	}
	Relation evaluatePredicate(Predicate predicate);
};

#endif