#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<sstream>
#include "Project.cpp"
#include<cstdio>
#include<vector>
#include"exprtk.h"
using namespace std;

int priority(char a) 
{
    int temp;
    if (a == '^')
        temp = 1;
    else  if (a == '*' || a == '/')
        temp = 2;
    else  if (a == '+' || a == '-')
        temp = 3;
    return temp;
}

string InfixtoPostfix ( string infix)
{

	StackInfix<char> operator_stack;

    stringstream output;   //output for string

	for (int i = 0; i < infix.length(); i++) 
	{
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') 
		{
			while (!operator_stack.isempty() && priority(operator_stack.top()) <= priority(infix[i])) 
			{
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.push(infix[i]);
        } 
		else if (infix[i] == '(') 
		{
            operator_stack.push(infix[i]);
        } 
		else if (infix[i] == ')') 
		{
            while (operator_stack.top() != '(') 
			{
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
        } 
		else 
		{
            output << infix[i];
        }
    }

	while (!operator_stack.isempty()) 
	{
        output << operator_stack.top();
        operator_stack.pop();
    }
	return (output.str());
   // cin.ignore(numeric_limits<streamsize>::max(), '\n');  //because if enter is pressed the console won't be closed
	

}

void menu()
{
	cout<<"Choose a number from (1 to 4)"<< endl << endl;
	cout<<"1- Infix to postfix conversion"<< endl << endl;
	cout<<"2- Numerical differentiation"<< endl << endl;
	cout<<"3- Symbolic differentiation"<< endl << endl;
	cout<<"4- Numerical integration"<< endl << endl;

}

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

void welcome()
{
	std::string line_;
	ifstream file("welcome.txt"); 
	if (file.is_open())   
	{
		while (getline(file, line_))   
		{
			std::cout << line_ << '\n';    
		}
		file.close();
	}
	else
		std::cout << "file is not open" << '\n';  
}

void goodbye()
{
	system("color 09");  
	std::string line_;
	ifstream file("goodbye.txt");  
	if (file.is_open()) 
	{
		while (getline(file, line_))  
		{
			std::cout << line_ << '\n';  
		}
		file.close();
	}
	else
		std::cout << "file is not open" << '\n';   

}





int main() 
{
	int choiceNum;
	char ch;
	ofstream Savefile;
	string name;

	do 
	{
	system("color 09");
	welcome();
	Savefile.open("Operations.txt", std::ios::out | std::ios::app);
	cout<<"Please enter your name: ";
	getline(cin , name);
	Savefile << name;
	Savefile << endl << endl;
	menu();
	cin>>choiceNum;

	system("cls");

	if ( choiceNum == 1)
	{
		string infix;
		system("color 06");
		cout<<" Infix to Postfix Conversion"<< endl << endl;
		cout << "Enter an arithmetic expression: " << endl;
		cin>>infix;
		Savefile<<"The infix expression :"<< infix;
		Savefile<< endl << endl;
		Savefile<<"The postfix expression :"<<InfixtoPostfix(infix);
		Savefile<< endl<< endl;
		cout <<"The postfix expression :"<<InfixtoPostfix(infix)<< endl;
	}

	else if ( choiceNum == 2)
	{
		system("color 05");
		cout<<" Numerical Differentiation"<< endl << endl;
		Differentiation d;
		string equation;
		int size;
		float* arr = new float [];
		cout<<"Enter your equation :";
		cin>>equation;
		Savefile<<"Equation before numerical diff : "<< equation;
		Savefile<< endl << endl;
		cout<<"Enter the number of points you want evaluated :";
		cin>>size;
		cout<<"enter your points :";
		for ( int i = 0 ; i < size ; i++)
		{
			cin>>arr[i];
		}
		Savefile<<"Equation after numerical diff : "<<d.numerical_differentiation(equation , arr , size);
		Savefile<< endl << endl;
		cout<<d.numerical_differentiation(equation , arr , size)<< endl;

	}
	else if( choiceNum == 3)
	{
		system("color 07");
		cout<<" Symbolic Differentiation :"<< endl << endl;
		string equation;
		Differentiation d;
		cout<<"Enter you equation :";
		cin>>equation;
		Savefile<<"Equation before symbolic diff : "<< equation;
		Savefile<< endl << endl;
		cout<<d.symbolic_differentiation(equation)<< endl;
		Savefile<<"Equation after symbolic diff : "<<d.symbolic_differentiation(equation);
		Savefile<< endl << endl;
	}

	else if ( choiceNum == 4)
	{
		system("color 0b");
		cout<<" Numerical Integration by Trapizuim Rule"<< endl << endl;
		int lowerBound, upperBound;
	double stepSize;
	vector<double> x_vec,y_vec;
	string evaluatedExpression;
	cout<<"Please enter the expression: ";
	cin>>evaluatedExpression;
	Savefile<<"Equation before integration :"<<evaluatedExpression;
	Savefile<< endl << endl;
	cout<<"Lower bound: "; cin>>lowerBound;
	cout<<"Upper bound: "; cin>>upperBound;
	cout<<"Step size: "; cin>>stepSize;

	// x-vector and y-vector are passed by reference(&x_vec,&y_vec)
	evaluateExpression<double>(evaluatedExpression, lowerBound, upperBound, stepSize, &x_vec,&y_vec);
	cout<<"The definite integral is: "<<evaluateIntegral(y_vec,stepSize)<<endl;
	Savefile<<"The define integral is : "<<evaluateIntegral(y_vec,stepSize);
	Savefile<< endl << endl;
	
	}

	cout<<"Do you want to make another operation? (y/n)" << endl << endl;
	cin>>ch;
	system("cls");

	}
    while( ch == 'y');
	goodbye();   
	system("pause");


    return 0;
}
