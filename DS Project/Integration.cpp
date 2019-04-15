#include <cstdio>
#include<iostream>
#include <string>
#include<vector>
#include "exprtk.h"
using namespace std;
/**
We are using exprtk library, a library specialized in reading mathematical expressions
as strings and giving us the variables in a form we can play with (like: substitute the variable
for a value, or substitute for a range of values...etc.)
*/


template <typename T>
void evaluateExpression(std::string expression_string,
						int low_bound, int up_bound, double step,
						vector<double>* x_vector, vector<double>* y_vector) // I am telling that the x-vector and y-vector will be passed by reference in the main
{
   typedef exprtk::symbol_table<T> symbol_table_t; // Library specific
   typedef exprtk::expression<T>     expression_t; // Library specific
   typedef exprtk::parser<T>             parser_t; // Library specific

   T x; // depends on how I call the function from main(), 
   // If I call the function evaluateExpression<int> -> T will be int
   // If I call the function evaluateExpression<double> -> T will be double
   // If I call the function evaluateExpression<float> -> T will be float
   // This is the type of the variable I want to use

   symbol_table_t symbol_table; // Library specific
   symbol_table.add_variable("x",x); // any letter I will use in the expression
								     // as an unknown should be added like that

   symbol_table.add_constants();     // Handles adding constant expressions (e.g.: pi, e...etc.)

   expression_t expression; // Library specific
   expression.register_symbol_table(symbol_table); // Library specific

   parser_t parser; // Library specific
   parser.compile(expression_string,expression); // Library specific

   // This for loop evaluates the results of substituting a range of values (the x values)
   // into the equation, and produce y values
   // y = f(x) -> example: f(x) = 3x  -> range for x = 1,2,3,4,5 -> therefore y = 3,6,9,12,15
   for (x = T(low_bound); x <= T(up_bound); x += T(step))
   {
      T y = expression.value(); // Library specific, it sets the value of y to the value of the expression
	  x_vector->push_back(x); // we are using vectors because we can increase/decrease their size dynamically
	  // and add/remove elements from them dynamically
	  y_vector->push_back(y);
   }
}

double evaluateIntegral(vector<double> y_vector, double H)
{
	// We are calculating the integral using the trapezium rule:
	// Integration of y from x=x0 to x=xn using trapezium rule is:
	// (h/2)  [y0 + yn + 2*(y1+y2+y3...+yn-1)]
	// the h is step size
	double sum = 0;
	for (int i=1;i<=y_vector.size()-2;i++)
    {
		// This loop sums all elements from y1 to yn-1
		// since we are using vectore which are similar to arrays, the last element
		// in the vector is y_vector[n-1], if we want all the elements between the first and last
		// without including them in the sum, we loop from 1 to (n-1)-1 = n-2 
		sum+=y_vector[i];
    }
	int lastElement = y_vector.size()-1;
	double integral=(H/2.0)*(y_vector[0]+y_vector[lastElement]+2*sum);
	return integral;
}


int main()
{
	int lowerBound, upperBound;
	double stepSize;
	vector<double> x_vec,y_vec;
	string evaluatedExpression;
	cout<<"Please enter the expression: ";
	cin>>evaluatedExpression;
	cout<<"Lower bound: "; cin>>lowerBound;
	cout<<"Upper bound: "; cin>>upperBound;
	cout<<"Step size: "; cin>>stepSize;

	// x-vector and y-vector are passed by reference(&x_vec,&y_vec)
	evaluateExpression<double>(evaluatedExpression, lowerBound, upperBound, stepSize, &x_vec,&y_vec);
	cout<<"The definite integral is: "<<evaluateIntegral(y_vec,stepSize)<<endl;
   return 0;
}