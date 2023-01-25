#include "scanner.h"
#include <string>
#include <fstream>

using namespace std;

vector<Token> Scanner::scanToken(string fileName) {
	ifstream in;
	TokenType tokenType;
	string value = "";
	int line = 1;
	int lineJump = 0;
	int c = 0;

	in.open(fileName);

	vector<Token> tokenVector;

	while (c != EOF) {
		value = "";
		lineJump = 0;

		c = in.get();

		switch (c) {
		case EOF:
			tokenType = EOFILE;
			value = "";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '\n':
			line++;
			break;
		case ',':
			tokenType = COMMA;
			value = ",";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '.':
			tokenType = PERIOD;
			value = ".";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '?':
			tokenType = Q_MARK;
			value = "?";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '(':
			tokenType = LEFT_PAREN;
			value = "(";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case ')':
			tokenType = RIGHT_PAREN;
			value = ")";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '*':
			tokenType = MULTIPLY;
			value = "*";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '+':
			tokenType = ADD;
			value = "+";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case ':':
			if (in.peek() == '-') {
				in.get();
				tokenType = COLON_DASH;
				value = ":-";
				tokenVector.push_back(Token(tokenType, value, line));
				break;
			}
			tokenType = COLON;
			value = ":";
			tokenVector.push_back(Token(tokenType, value, line));
			break;
		case '\'': //string case
			while (in.peek() != EOF) {
				value += c;
				c = in.get();
				if (c == '\n') lineJump++;
				if (c == '\'' && in.peek() == '\'') {
					value += c;
					c = in.get();
				}
				else if (c == '\'') break;
			}
			if (c == '\'') { 
				value += c;
				tokenType = STRING;
				tokenVector.push_back(Token(tokenType, value, line));
			}
			else { // unterminating string
				value += c;
				tokenType = UNDEFINED;
				tokenVector.push_back(Token(tokenType, value, line));
			}
			line += lineJump;
			break;
		case '#': //comment case
			if (in.peek() == '|') { //multiline comment
				while (in.peek() != EOF) {
					value += c;
					c = in.get();
					if (c == '\n') lineJump++;
					if (c == '|' && in.peek() == '#') break;
				}
				if (in.peek() == EOF) { // unterminating multiline comment
					value += c;
					tokenType = UNDEFINED;
					tokenVector.push_back(Token(tokenType, value, line));
				}
				else { 
					value += c;
					c = in.get();
					value += c;
					tokenType = COMMENT;
					tokenVector.push_back(Token(tokenType, value, line));
				}
			}
			else { //single line comment
				while ((in.peek() != '\n') && (in.peek() != EOF)) {
					value += c;
					c = in.get();
				}
				value += c;
				tokenType = COMMENT;
				tokenVector.push_back(Token(tokenType, value, line));
			}
			line += lineJump;
			break;
		default: // Schemes, Facts, Rules, Queries, and IDs
			if (isalpha(c)) {
				while (isalpha(in.peek()) || isdigit(in.peek())) {
					value += c;
					c = in.get();
				}
				value += c;
				if (value == "Schemes") {
					tokenType = SCHEMES;
				}
				else if (value == "Facts") {
					tokenType = FACTS;
				}
				else if (value == "Rules") {
					tokenType = RULES;
				}
				else if (value == "Queries") {
					tokenType = QUERIES;
				}
				else {
					tokenType = ID;
				}
				tokenVector.push_back(Token(tokenType, value, line));
			}
			else if (isspace(c)); // spaces
			else { // Undefined tokens
				tokenType = UNDEFINED;
				value = c;
				tokenVector.push_back(Token(tokenType, value, line));
			}
		}
	}

	in.close();

	return tokenVector;
}