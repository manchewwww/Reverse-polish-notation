#include "Operator.h"

Operator::Operator() : symbol('\0'), op('\0'), priority(-1), associativity('\0')
{
}
Operator::Operator(char symbol, char op, int priority, char associativity)
{
	setSymbol(symbol);
	setOperator(op);
	setAssociativity(associativity);
	setPriority(priority);
}


char Operator::getSymbol() const
{
	return symbol;
}

char Operator::getOperator() const
{
	return op;
}

char Operator::getAssociativity() const
{
	return associativity;
}

int Operator::getPriority() const
{
	return priority;
}

void Operator::setSymbol(char symbol)
{
	if (isalpha(symbol)) {
		this->symbol = symbol;
	}
	else {
		throw incorrect_expression("Invalid symbol. \n");
	}
}

void Operator::setOperator(char op)
{
	switch (op)
	{
	case '/':
	case '*':
	case '-':
	case '+': this->op = op;
		break;
	default:
		throw incorrect_expression("Invalid operator. \n");
		break;
	}
}

void Operator::setAssociativity(char associativity)
{
	switch (associativity)
	{
	case 'R':
	case 'L': this->associativity = associativity; break;
	default:
		throw incorrect_expression("Invalid associativity. \n");
		break;
	}
}

void Operator::setPriority(int priority)
{
	if (priority < 0) {
		throw incorrect_expression("Invalid priority");
	}
	this->priority = priority;
}
