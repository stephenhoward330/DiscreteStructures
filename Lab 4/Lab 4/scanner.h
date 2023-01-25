#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include "token.h"

using namespace std;

class Scanner {
private:
public:
	vector<Token> scanToken(string fileName);
};

#endif