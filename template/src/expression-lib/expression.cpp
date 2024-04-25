#include "expression.h"
#include "OperationSet.h"
#include <fstream>
#include <stack>
#include <math.h>

bool isBiggerOrEq(char f, char s, const OperationSet& operators)
{
	if (f == '(') {
		return false;
	}
	Operator first = operators.get(f);
	Operator second = operators.get(s);
	if (first.getPriority() > second.getPriority()) {
		return true;
	}
	else if (first.getPriority() < second.getPriority()) {
		return false;
	}
	else {
		if ((first.getAssociativity() == second.getAssociativity())) {
			if (first.getAssociativity() == 'R') {
				return false;
			}
			return true;
		}
		else {
			throw incorrect_expression("Operator with equal priority must be with equal associativity. ");
		}
	}
}

double calculate(std::stack<double>& nums, std::stack<char>& ops, const OperationSet& operators) {
	char symbol = ops.top();
	ops.pop();
	double second = nums.top();
	nums.pop();
	double first = nums.top();
	nums.pop();
	switch (operators.get(symbol).getOperator())
	{
	case '+': return (first + second);
	case '-': return (first - second);
	case '*': return (first * second);
	case '/':
		if (second != 0) {
			return (first / second);
		}
		else {
			throw incorrect_expression("Divisor must be different from 0 \n");
		}
	default:
		break;
	}
}

double calculateExpr(const char* expr, const OperationSet& operators)
{
	std::stack<char> ops;
	std::stack<double> nums;
	std::string newExpr;
	int i = 0;
	while (expr[i] != '\0') {
		if (expr[i] == ' ') {
			i++;
			continue;
		}
		else if (expr[i] == '(') {
			ops.push(expr[i]);
			i++;
		}
		else if (expr[i] == ')') {
			while (ops.top() != '(') {
				nums.push(calculate(nums, ops, operators));
			}
			ops.pop();
			i++;
		}
		else if (isalpha(expr[i])) {
			while (!ops.empty() && isBiggerOrEq(ops.top(), expr[i], operators)) {
				nums.push(calculate(nums, ops, operators));
			}
			ops.push(expr[i]);
			i++;
		}
		else if (isdigit(expr[i])) {
			bool hasPoint = false;
			int counter = 0;
			double number = 0;
			while (expr[i] != ' ' && expr[i] != '\0') {
				if (expr[i] == '.') {
					i++;
					hasPoint = true;
					continue;
				}
				(number *= 10) += (expr[i++] - '0');
				if (hasPoint) {
					counter++;
				}
			}
			number *= std::pow(0.1, counter);
			nums.push(number);
		}
		else if (expr[i] == '-') {
			i++;
			bool hasPoint = false;
			int counter = 0;
			double number = 0;
			while (expr[i] != ' ' && expr[i] != '\0') {
				if (expr[i] == '.') {
					i++;
					hasPoint = true;
					continue;
				}
				(number *= 10) += (expr[i++] - '0');
				if (hasPoint) {
					counter++;
				}
			}
			number *= std::pow(0.1, counter);
			number *= (-1);
			nums.push(number);
		}
	}
	while (!ops.empty()) {
		nums.push(calculate(nums, ops, operators));
	}
	return nums.top();
}

bool isEmpty(const char* expr)
{
	int i = 0;
	while (expr[i] != '\0') {
		if (expr[i] != ' ') {
			return false;
		}
		i++;
	}
	return true;
}

bool isValid(const char* expr, const OperationSet& ops)
{
	int i = 0;
	bool valid = true;
	std::stack<char> brackets;
	while (expr[i] != '\0') {
		if (expr[i] == ' ') {
			i++;
			continue;
		}
		else if (isdigit(expr[i]) && valid) {
			bool hasPoint = false;
			while (expr[i] != ' ' && expr[i] != '\0') {
				if (expr[i] == '.' && !hasPoint) {
					i++;
					hasPoint = true;
					continue;
				}
				if (!isdigit(expr[i++])) {
					return false;
				}
			}
			valid = false;
		}
		else if (expr[i] == '-' && valid) {
			bool hasPoint = false;
			i++;
			if (expr[i] == ' ') {
				return false;
			}
			while (expr[i] != ' ' && expr[i] != '\0') {
				if (expr[i] == '.' && !hasPoint) {
					i++;
					hasPoint = true;
					continue;
				}
				else if (!isdigit(expr[i++])) {
					return false;
				}
			}
			valid = false;
		}
		else if (isalpha(expr[i]) && !valid) {
			if (!ops.contains(expr[i])) {
				return false;
			}
			else if (expr[++i] != ' ') {
				return false;
			}
			valid = true;
		}
		else if (expr[i] == '(' && valid) {
			brackets.push(expr[i]);
			if (expr[++i] != ' ') {
				return false;
			}

		}
		else if (expr[i] == ')' && !valid) {
			if (brackets.empty()) {
				return false;
			}
			brackets.pop();
			if (expr[++i] != ' ' && expr[i] != '\0') {
				return false;
			}
		}
		else {
			return false;
		}
	}
	if (!brackets.empty()) {
		return false;
	}
	return true;
}

double evaluate(const char* expression, std::istream& ops)
{
	if (expression == nullptr) {
		throw  incorrect_expression("Expression must be different from nullptr.\n ");
	}
	else if (isEmpty(expression)) {
		return 0;
	}
	OperationSet operators(ops);
	if (!isValid(expression, operators)) {
		throw incorrect_expression("Invalid expression.\n");
	}

	return calculateExpr(expression, operators);
}