#pragma once
#include "Operator.h"

class OperationSet {
public:
	OperationSet(std::istream& ifs);
	void add(char symbol, char op, int priority, char associativity); 
	bool contains(char symbol) const; 
	const Operator& get(char symbol) const;
private:
	Operator operators[26];
};