#ifndef NODE_H
#define NODE_H

#include <set>

using namespace std;

class Node {
private:
	set<int> adjNodes;
	bool visitFlag;
	bool usedFlag;
	int postNum;
public:
	Node() {
		visitFlag = false;
		usedFlag = false;
		postNum = 0;
	}
	void addEdge(int nodeID) {
		adjNodes.insert(nodeID);
	}

	void setFlag(bool newFlag) {
		visitFlag = newFlag;
	}
	void setUFlag(bool newFlag) {
		usedFlag = newFlag;
	}
	void setPostNum(int pNum) {
		postNum = pNum;
	}

	set<int> getAdjNodes() {
		return adjNodes;
	}
	bool getVisitFlag() {
		return visitFlag;
	}
	bool getUsedFlag() {
		return usedFlag;
	}
	int getPostNum() {
		return postNum;
	}

	bool hasLoop(int nodeID) {
		bool loop = false;
		for (set<int>::iterator iter = adjNodes.begin(); iter != adjNodes.end(); iter++) {
			if (nodeID == *iter) loop = true;
		}
		return loop;
	}
	void toString() {
		bool mult = false;
		for (set<int>::iterator iter = adjNodes.begin(); iter != adjNodes.end(); iter++) {
			if (mult) cout << ",";
			cout << "R" << *iter;
			mult = true;
		}
	}
};

#endif