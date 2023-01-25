#include "DatalogProgram.h"
#include <algorithm>

void DatalogProgram::nextToken() {
	token = tokenVector.at(tokenNum);
	tokenNum++;
	//cout << "Got token: " << token.getVal() << endl;
}

void DatalogProgram::match(TokenType type) {
	if (token.getType() == type); // nextToken();
	else throw token;
}

void DatalogProgram::parse() {
	nextToken();
	if (token.getType() == SCHEMES) {
		match(SCHEMES); nextToken();
		match(COLON); nextToken();
		scheme(); schemeList();
	}
	else throw token;
	if (token.getType() == FACTS) {
		match(FACTS); nextToken();
		match(COLON); nextToken();
		factList();
	}
	else throw token;
	if (token.getType() == RULES) {
		match(RULES); nextToken(); 
		match(COLON); nextToken(); 
		ruleList();
	}
	else throw token;
	if (token.getType() == QUERIES) {
		match(QUERIES); nextToken(); 
		match(COLON); nextToken(); 
		queryList();
	}
	else throw token;
	if (token.getType() != EOFILE) throw token;
}

void DatalogProgram::schemeList() {
	if (token.getType() == ID) {
		scheme(); schemeList();
	}
}

void DatalogProgram::factList() {
	if (token.getType() == ID) {
		fact(); factList();
	}
}

void DatalogProgram::ruleList() {
	if (token.getType() == ID) {
		rule(); ruleList();
	}
}

void DatalogProgram::queryList() {
	if (token.getType() == ID) {
		query(); queryList();
	}
}

void DatalogProgram::scheme() {
	if (token.getType() == ID) {
		string newID;
		vector<Parameter> newParameterVector;
		match(ID); newID = token.getVal(); nextToken(); 
		match(LEFT_PAREN); nextToken(); 
		match(ID); Parameter newParam(token.getVal()); newParameterVector.push_back(newParam); nextToken();
		newParameterVector = idList(newParameterVector); 
		match(RIGHT_PAREN); nextToken();
		Predicate scheme(newID, newParameterVector);
		schemesVector.push_back(scheme);
	}
	else throw token;
}

void DatalogProgram::fact() {
	if (token.getType() == ID) {
		string newID;
		vector<Parameter> newParameterVector;
		match(ID); newID = token.getVal(); nextToken();
		match(LEFT_PAREN); nextToken();
		match(STRING); Parameter newParam(token.getVal()); newParameterVector.push_back(newParam);
		domainVector.push_back(token.getVal()); nextToken();
		newParameterVector = stringList(newParameterVector); 
		match(RIGHT_PAREN); nextToken();
		match(PERIOD); nextToken();
		Predicate fact(newID, newParameterVector);
		factsVector.push_back(fact);
	}
	else throw token;
}

void DatalogProgram::rule() {
	if (token.getType() == ID) {
		vector<Predicate> newPredicateVector;
		Predicate newHeadPredicate = headPredicate();
		match(COLON_DASH); nextToken();
		Predicate newPredicate = predicate(); newPredicateVector.push_back(newPredicate);
		newPredicateVector = predicateList(newPredicateVector);
		match(PERIOD); nextToken();
		Rule rule(newHeadPredicate, newPredicateVector);
		rulesVector.push_back(rule);
	}
	else throw token;
}

void DatalogProgram::query() {
	if (token.getType() == ID) {
		Predicate query = predicate();
		match(Q_MARK); nextToken();
		queriesVector.push_back(query);
	}
	else throw token;
}

Predicate DatalogProgram::headPredicate() {
	if (token.getType() == ID) {
		//match(ID); match(LEFT_PAREN); match(ID); idList(); match(RIGHT_PAREN);

		string newID;
		vector<Parameter> newParameterVector;
		match(ID); newID = token.getVal(); nextToken();
		match(LEFT_PAREN); nextToken();
		match(ID); Parameter newParam(token.getVal()); 
		newParameterVector.push_back(newParam); nextToken();
		newParameterVector = idList(newParameterVector);
		match(RIGHT_PAREN); nextToken();
		Predicate headPredicate(newID, newParameterVector);
		return headPredicate;
	}
	else throw token;
}

Predicate DatalogProgram::predicate() {
	if (token.getType() == ID) {
		string newID;
		vector<Parameter> newParameterVector;
		match(ID); newID = token.getVal(); nextToken(); 
		match(LEFT_PAREN); nextToken();
		Parameter newParameter = parameter(); newParameterVector.push_back(newParameter);
		newParameterVector = parameterList(newParameterVector); 
		match(RIGHT_PAREN); nextToken();
		Predicate newPredicate(newID, newParameterVector);
		return newPredicate;
	}
	else throw token;
}

vector<Predicate> DatalogProgram::predicateList(vector<Predicate> newPredicateVector) {
	vector<Predicate> newerPredicateVector = newPredicateVector;
	if (token.getType() == COMMA) {
		match(COMMA); nextToken(); 
		Predicate newPredicate = predicate();
		newerPredicateVector.push_back(newPredicate);
		newerPredicateVector = predicateList(newerPredicateVector);
	}
	return newerPredicateVector;
}

vector<Parameter> DatalogProgram::parameterList(vector<Parameter> newParameterVector) {
	vector<Parameter> newerParameterVector = newParameterVector;
	if (token.getType() == COMMA) {
		match(COMMA); nextToken(); 
		Parameter newParameter = parameter();
		newerParameterVector.push_back(newParameter);
		newerParameterVector = parameterList(newerParameterVector);
	}
	return newerParameterVector;
}

vector<Parameter> DatalogProgram::stringList(vector<Parameter> newParameterVector) {
	vector<Parameter> newerParameterVector = newParameterVector;
	if (token.getType() == COMMA) {
		match(COMMA); nextToken();
		match(STRING); Parameter newParam(token.getVal()); domainVector.push_back(token.getVal()); 
		newerParameterVector.push_back(newParam); nextToken();
		newerParameterVector = stringList(newerParameterVector);
	}
	return newerParameterVector;
}

vector<Parameter> DatalogProgram::idList(vector<Parameter> newParameterVector) {
	//vector<Parameter> newerParameterVector = newParameterVector;
	if (token.getType() == COMMA) {
		match(COMMA); nextToken(); 
		match(ID); Parameter newParam(token.getVal());
		newParameterVector.push_back(newParam); nextToken();
		newParameterVector = idList(newParameterVector);
	}
	return newParameterVector;
}

Parameter DatalogProgram::parameter() {
	string newID;
	if (token.getType() == ID) {
		match(ID); newID = token.getVal(); nextToken();
	}
	else if (token.getType() == LEFT_PAREN) {
		newID = expression();
	}
	else if (token.getType() == STRING) {
		match(STRING); newID = token.getVal(); nextToken();
	}
	else throw token;
	Parameter newParameter(newID);
	return newParameter;
}

string DatalogProgram::expression() {
	string newExpression = "";
	if (token.getType() == LEFT_PAREN) {
		match(LEFT_PAREN); nextToken(); newExpression = newExpression + "(";
		Parameter leftParameter = parameter();
		newExpression = newExpression + leftParameter.getIDstring();
		bool isAdd = op();
		if (isAdd) newExpression = newExpression + "+";
		else newExpression = newExpression + "*";
		Parameter rightParameter = parameter();
		newExpression = newExpression + rightParameter.getIDstring();
		match(RIGHT_PAREN); nextToken(); newExpression = newExpression + ")";
		return newExpression;
	}
	else throw token;
}

bool DatalogProgram::op() {
	bool isAdd;
	if (token.getType() == ADD) {
		match(ADD); isAdd = true; nextToken();
	}
	else if (token.getType() == MULTIPLY) {
		match(MULTIPLY); isAdd = false; nextToken();
	}
	else throw token;
	return isAdd;
}

void DatalogProgram::toString() {
	cout << "Success!" << endl;
	cout << "Schemes(" << schemesVector.size() << "):" << endl;
	for (unsigned i = 0; i < schemesVector.size(); i++) {
		cout << "  ";
		schemesVector.at(i).toString();
		cout << endl;
	}
	cout << "Facts(" << factsVector.size() << "):" << endl;
	for (unsigned i = 0; i < factsVector.size(); i++) {
		cout << "  ";
		factsVector.at(i).toString();
		cout << "." << endl;
	}
	cout << "Rules(" << rulesVector.size() << "):" << endl;
	for (unsigned i = 0; i < rulesVector.size(); i++) {
		cout << "  ";
		rulesVector.at(i).toString();
		cout << "." << endl;
	}
	cout << "Queries(" << queriesVector.size() << "):" << endl;
	for (unsigned i = 0; i < queriesVector.size(); i++) {
		cout << "  ";
		queriesVector.at(i).toString();
		cout << "?" << endl;
	}
	sort(domainVector.begin(), domainVector.end());
	domainVector.erase(unique(domainVector.begin(), domainVector.end()), domainVector.end());
	cout << "Domain(" << domainVector.size() << "):" << endl;
	for (unsigned i = 0; i < domainVector.size(); i++) {
		cout << "  " << domainVector.at(i) << endl;
	}
}