#include <iostream>
#include "lexer.hpp"
#include "parser.cpp"



int main() {

	lexer::Lex Lex("T^.");

	bool isSyntax = parser::B(Lex);

	std::cout << isSyntax;

	return 0;
}
