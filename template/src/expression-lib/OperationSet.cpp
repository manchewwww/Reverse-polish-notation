#include "OperationSet.h"

OperationSet::OperationSet(std::istream& ifs)
{
	while (true) {
		char symbol, op, assoc;
		int priority;
		ifs >> symbol;
		if (ifs.eof()) {
			return;
		}
		ifs >> op >> priority >> assoc;
		add(symbol, op, priority, assoc);
		ifs.get();
	}
}

void OperationSet::add(char symbol, char op, int priority, char associativity)
{
	if (isalpha(symbol))
		operators[tolower(symbol) - 'a'] = Operator(tolower(symbol), op, priority, associativity);
	else
		throw incorrect_expression("Symbol of operator is incorrect. \n");
}

bool OperationSet::contains(char symbol) const
{
	if (isalpha(symbol))
		return !(operators[tolower(symbol) - 'a'].getSymbol() == '\0');
	else
		throw incorrect_expression("Symbol of operator is invalid. \n");
}

const Operator& OperationSet::get(char symbol) const
{
	if (contains(symbol)) {
		return operators[tolower(symbol) - 'a'];
	}
	else {
		throw incorrect_expression("Symbol of operator is not contains. \n");
	}

}
