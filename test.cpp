#include <iostream>
#include "lexer.hpp"



int main() {

	lexer::Lex Lex("T->T");

	lexer::Token token1 = Lex.get();
	std::cout << "Token 1";
	std::cout << static_cast<const unsigned char>(token1.type);
	std::cout << "\n" << token1.lexeme;
	std::cout << "\n" << token1.position;

	lexer::Token token2 = Lex.get();
	std::cout << "\n\nToken 2";
	std::cout << static_cast<const unsigned char>(token2.type);
	std::cout << "\n" << token2.lexeme;
	std::cout << "\n" << token2.position;

	lexer::Token token3 = Lex.get();
	std::cout << "\n\nToken 3";
	std::cout << static_cast<const unsigned char>(token3.type);
	std::cout << "\n" << token3.lexeme;
	std::cout << "\n" << token3.position;

	return 0;
}
