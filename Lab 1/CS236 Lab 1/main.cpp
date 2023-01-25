#include "scanner.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	string tokenTypeArray[] = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "MULTIPLY",
		"ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "EOF" };

	string filename = argv[1];

	vector<Token> tokenVector;

	Scanner newScanner;
	tokenVector = newScanner.scanToken(filename);

	for (unsigned int i = 0; i < tokenVector.size(); i++) {
		cout << "(" << tokenTypeArray[tokenVector.at(i).getType()] << ",\"" << tokenVector.at(i).getVal()
			<< "\"," << tokenVector.at(i).getLineNum() << ")" << endl;
	}
	cout << "Total Tokens = " << tokenVector.size() << endl;

	return 0;
}