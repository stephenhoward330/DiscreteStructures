#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include "token.h"
#include <vector>
#include <string>

using namespace std;

class DatalogProgram {
private:
	int tokenNum;
	Token token;
	vector<Token> tokenVector;

	vector<Predicate> schemesVector;
	vector<Predicate> factsVector;
	vector<Rule> rulesVector;
	vector<Predicate> queriesVector;
	vector<string> domainVector;
public:
	DatalogProgram(vector<Token> newTokenVector) {
		tokenVector = newTokenVector;
		tokenNum = 0;
	}
	void nextToken();
	void match(TokenType type);
	void parse();

	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	Predicate headPredicate();
	Predicate predicate();
	vector<Predicate> predicateList(vector<Predicate> newPredicateVector);
	vector<Parameter> parameterList(vector<Parameter> newParameterVector);
	vector<Parameter> stringList(vector<Parameter> newParameterVector);
	vector<Parameter> idList(vector<Parameter> newParameterVector);
	Parameter parameter();
	string expression();
	bool op();

	void toString();
};

#endif