#include <iostream>
#include <string>
#include "Project.h"
using namespace std;

bool Differentiation::check_variables(string equation)//check en el equation hrf wahed mn A to Z
{
	char symbol = '\0';
	for (int i = 0; i < equation.size(); i++)
	{
		if ((equation[i] >= 'a'&& equation[i] <= 'z') || (equation[i] >= 'A'&& equation[i] <= 'Z'))
		{
			if (symbol == '\0')
				symbol = equation[i];
			else
			{
				if (symbol != equation[i])
					return false;
			}

		}
	}
	return true;
}

char Differentiation::get_symbol(string equation)
{
	for (int i = 0; i < equation.size(); i++)
	{
		if ((equation[i] >= 'a'&& equation[i] <= 'z') || (equation[i] >= 'A'&& equation[i] <= 'Z'))
		{
			return equation[i];
		}
	}
	return '\0';
}

string Differentiation::differentiate(string term, char symbol) //term
{
	// 52 * x * 4 * x / 2 * x * 3
	string result = ""; //ay arkam aw signs htt7t fl result
	int symbolCounter = 0;
	for (int i = 0; i < term.size(); i++) //loop bgeb feha el result 2*8*1 w bgeb el symbol counter
	{
		if (term[i] == symbol)
		{
			if (i == 0)//
			{
				symbolCounter++;
				continue;
			}
			if (term[i - 1] == '*')
			{
				symbolCounter++;
				continue;
			}
			else
			{
				symbolCounter--;
				continue;
			}
		}

		if (term[i] == '*' || term[i] == '/')
			continue;

		// ma3na enena wslna hena en el term[i] msh symbol wala operator
		// yb2a akeed rqm

		if (i == 0) //lw e term const. bs?
		{
			result += term[i]; //3shan ahseb awl term
			continue;
		}

		if (term[i - 1] == '*' || term[i - 1] == '/')
		{
			if (result == "")
			{
				if (term[i - 1] == '*')
					result += term[i];
				else
					result += "1/" + term[i];
			}
			else
			{
				result += term[i - 1];
				result += term[i];
			}
			continue;
		}

		// ma3na eny wslt hena en ana wa2f 3la eaqam w ely 2bly raqam
		result += term[i];
	}

	// 5rgna mn el loop m3ana result fyha kol el 2rqam bl signs bt3thom

	if (symbolCounter == 0)//mesh xs
		return "0";

	if (result == "") //x*x*x*x f h7ot feha el symbol counter
		result += std::to_string(symbolCounter);
	else
	{
		result += "*";
		result += std::to_string(symbolCounter);
		result = std::to_string(computeEquation(result));
	}


	if (symbolCounter < 0)
	{
		// x ^ -2
		// -2 * x ^ -3
		// = -2 * 1 / x * 1 / x * 1 / x
		for (int i = symbolCounter - 1; i < 0; i++)
		{
			if (result == "")
				result += "1/" + symbol;
			else
			{
				result += "*1/"; //3shan myrg3sh el asc ll *1/x+symbol w ytl3 3k
				result += symbol;
			}
		}
	}
	else
	{
		// x ^ 3
		// 3 * x ^ 2
		// = 3 * x * x
		for (int i = 0; i < symbolCounter - 1; i++) //3shan ytl3le el answer mdroba bl xs
		{
			if (result == "")
				result += symbol;
			else
				result += "*";
			result += symbol;
		}
	}

	return result;
}


float Differentiation::computeEquation(string equation)
{
	float number = 1;
	string sNumber = "";
	char sign = '*';
	for (int i = 0; i < equation.size(); i++)
	{
		if (equation[i] == '*' || equation[i] == '/')
		{
			if (sign == '*')
				number *= std::stof(sNumber); //ht7wlha l float??
			else
				number /= std::stof(sNumber);

			sNumber = "";
			sign = equation[i];
			continue;
		}
		sNumber += equation[i];
	}

	if (sign == '*') //a5er term
		number *= std::stof(sNumber);
	else
		number /= std::stof(sNumber);

	return number;
}

string Differentiation::symbolic_differentiation(string equation)
{
	bool is_one_variable = check_variables(equation);
	if (is_one_variable == false)
		//cout<<"invaled equation" da lw m3mlnash el gui
		return "invaled equation"; //return zy break bttl3 brra
	char symbol = get_symbol(equation); //ageb el symbol x wlla ...
	string result = "";
	string term = "";
	char sign = '\0';
	string termDiff = "";
	for (int i = 0; i < equation.size(); i++)
	{
		if (equation[i] == '+' || equation[i] == '-')
		{
			termDiff = differentiate(term, symbol);
			if (sign == '\0')
				result += termDiff;
			else
			{
				if (termDiff[0] == '-')
					result += termDiff;
				else
					result += sign + termDiff;
			}
			term = "";
			sign = equation[i];
			continue;
		}
		else
			term += equation[i];
	}
	termDiff = differentiate(term, symbol);
	if (sign == '\0')
		result += termDiff;
	else
	{
		if (termDiff[0] == '-')
			result += termDiff;
		else
			result += sign + termDiff;
	}
	return result;
}

string Differentiation::numerical_differentiation(string equation, float nums[], int size)
{
	string result = "";
	string diff = symbolic_differentiation(equation);

	char symbol = get_symbol(diff);
	for (int i = 0; i < size; i++)
	{
		float calculation = replace(diff, symbol, nums[i]);
		result += "when x = " + std::to_string(nums[i]) + " it's " + std::to_string(calculation) + "\n";
	}
	return result;
}

float Differentiation::replace(string equation, char symbol, float num)
{
	// replace bt7seb el final result
	float result = 0;
	string term = "";
	char sign = '+';
	for (int i = 0; i < equation.size(); i++)
	{
		if (i == 0 && equation[i] == '-')
		{
			sign = '-';
			continue;
		}

		if (equation[i] == '+' || equation[i] == '-')
		{
			if (sign == '+')
				result += calculate(term, symbol, num);
			else
				result -= calculate(term, symbol, num);
			sign = equation[i];
			term = "";
			continue;
		}

		term += equation[i];
	}
	if (term != "")
	{
		if (sign == '+')
			result += calculate(term, symbol, num);
		else
			result -= calculate(term, symbol, num);
	}
	return result;
}

float Differentiation::calculate(string term, char symbol, float num)
{
	string replacedTerm = "";
	for (int i = 0; i < term.size(); i++)
	{
		if (term[i] == symbol)
			replacedTerm += std::to_string(num);
		else
			replacedTerm += term[i];
	}

	char sign = '*';
	float result = 1;
	string n = "";

	// 123/43*55
	for (int i = 0; i < replacedTerm.size(); i++) {
		if (replacedTerm[i] == '*' || replacedTerm[i] == '/')
		{
			if (n != "")
			{
				if (sign == '*')
					result *= std::stof(n); // stoi bt7wel el string le integer
				else
					result /= std::stof(n);
			}
			n = "";
			sign = replacedTerm[i];
			continue;
		}

		n += replacedTerm[i];
	}

	if (n != "")
	{
		if (sign == '*')
			result *= std::stof(n);
		else
			result /= std::stof(n);
	}


	return result;
}