#pragma once
#include "expression.h"
#include <iostream>
#include <string>
#include <cctype>

class Operator {
public:
	Operator();
	Operator(char symbol, char op, int priority, char associativity);

	char getSymbol() const;
	char getOperator() const;
	char getAssociativity() const;
	int getPriority() const;
private:
	void setSymbol(char symbol);
	void setOperator(char op);
	void setAssociativity(char associativity);
	void setPriority(int priority);
private:
	char symbol;
	char op;
	char associativity;
	int priority;
};