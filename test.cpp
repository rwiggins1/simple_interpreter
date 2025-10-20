#include <iostream>
#include "lexer.hpp"



int main() {

	lexer::Lex Lex("T->T");

	lexer::Token token1 = Lex.getToken();
	std::cout << "\n" << token1.type;
	std::cout << "\n" << token1.lexeme;
	std::cout << "\n" << token1.position;

	lexer::Token token2 = Lex.getToken();
	std::cout << "\n\n" << token2.type;
	std::cout << "\n" << token2.lexeme;
	std::cout << "\n" << token2.position;

	lexer::Token token3 = Lex.getToken();
	std::cout << "\n\n" << token3.type;
	std::cout << "\n" << token3.lexeme;
	std::cout << "\n" << token3.position;

	return 0;
}
