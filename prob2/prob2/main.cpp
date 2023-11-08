#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

typedef enum type_operator {
	Plus = 0,
	Minus,
	Multiply
}type_operator;
int main()
{
	string input,token;
	inf_int fir_operand, sec_operand;
	type_operator command;
	while (true) {
		cout << "Input: ";
		getline(cin, input);
		if (input == "0")break;
		stringstream sstream(input);
		getline(sstream, token, ' ');
		fir_operand = token;
		getline(sstream, token, ' ');

		if (token == "+")command = Plus;
		else if (token == "-")command = Minus;
		else command = Multiply;

		getline(sstream, token, ' ');
		sec_operand = token;
		switch (command)
		{
		case Plus:
			cout << fir_operand + sec_operand;
			break;
		case Minus:
			cout << fir_operand - sec_operand;
			break;
		case Multiply:
			cout << fir_operand * sec_operand;
			break;
		default:
			break;
		}
	}
	return 0;
}