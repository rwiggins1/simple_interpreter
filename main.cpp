#include <iostream>
#include "lexer.hpp"
#include "parser.cpp"



int main() {
	std::string input = "F->F."; // true
	lexer::Lex Lex(input);

	bool isSyntax = parser::B(Lex);

	if (isSyntax) {
		bool expression = parser::getResult();

		if (expression) {
			std::cout << "True";
		}
		else {
			std::cout << "False";
		}
	}
	else {
		std::cout << "Syntax invalid";
	}


	return 0;
}
