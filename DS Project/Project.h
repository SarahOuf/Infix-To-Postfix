#include <string>
#include <iostream>

using namespace std;

template <class T>

class StackInfix 
{
	 
	    T elements;
		T* arr;
		int capacity;
	
public:

		StackInfix(); 
        ~StackInfix(void);
		T top();
        void push(T c);
		void pop();
		bool isempty();
		void Expand();
		int Length();


	
		
};

class Differentiation
{
private: //mhdsh hyst5dmha mn el main 'function mos3da'
	bool check_variables(string);
	char get_symbol(string);
	string differentiate(string,char);
	float replace(string, char, float);
	float calculate(string, char, float);
	float computeEquation(string);

public: //htednh mn el main
	string symbolic_differentiation(string);
	string numerical_differentiation(string, float[], int);
};
