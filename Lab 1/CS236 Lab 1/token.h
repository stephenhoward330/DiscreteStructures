#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, 
	ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFILE };

class Token {
private:
	TokenType type;
	string val;
	int lineNum;
public:
	Token(TokenType newType, string newVal, int newLineNum) {
		type = newType;
		val = newVal;
		lineNum = newLineNum;
	}
	TokenType getType() {
		return type;
	}
	string getVal() {
		return val;
	}
	int getLineNum() {
		return lineNum;
	}
};

#endif