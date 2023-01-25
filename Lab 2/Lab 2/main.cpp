#include "scanner.h"
#include "DatalogProgram.h"
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

	DatalogProgram parser(tokenVector);
	try {
		parser.parse();
	}
	catch(Token eToken){
		cout << "Failure!" << endl;
		cout << "  (" << tokenTypeArray[eToken.getType()] << ",\"" << eToken.getVal()
			<< "\"," << eToken.getLineNum() << ")" << endl;

		return 0;
	}
	parser.toString();

	return 0;
}