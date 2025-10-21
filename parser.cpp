#include "lexer.hpp"
#include <stdexcept>

namespace parser {
static lexer::Lex* Lex;

bool IT();
bool IT_Tail();
bool OT();
bool OT_Tail();
bool AT();
bool AT_Tail();
bool L();
bool A();

bool B(lexer::Lex& lexer){
	Lex = &lexer;

	if (IT()) {
		lexer::Token token = Lex->get();
		return (token.type == lexer::TokenType::PERIOD) ? true: false;
	}
	return false;
}

bool IT(){
	if (OT()) {
		return IT_Tail();
	}
	return false;
}
bool IT_Tail(){
	lexer::Token token = Lex->peek();
	if (token.type == lexer::TokenType::IMPLIES) {
		Lex->get();
		if (OT()) {
			return IT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::TokenType::PERIOD || token.type == lexer::TokenType::CPAREN 
		|| token.type == lexer::TokenType::T_EOF){
		return true;
	}
	else {
		throw std::invalid_argument("expecting '->', '.', or ')' but got: " + token.lexeme);
	}
}

bool OT(){
	if (AT()) {
		return OT_Tail();
	}
	return false;
}
bool OT_Tail(){
	lexer::Token token = Lex->peek();
	if(token.type == lexer::TokenType::OR) {
		Lex->get();
		if (AT()) {
			return OT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::TokenType::IMPLIES || token.type == lexer::TokenType::PERIOD 
		|| token.type == lexer::TokenType::CPAREN || token.type == lexer::TokenType::T_EOF) {
		return true;
	}
	else {
		throw std::invalid_argument("expecting 'v', '->', '.', or ')' but got: " + token.lexeme);
	}
}

bool AT(){
	if (L()) {
		return AT_Tail();
	}
	return false;
}
bool AT_Tail(){
	lexer::Token token = Lex->peek();
	if (token.type == lexer::TokenType::AND) {
		Lex->get();
		if (L()) {
			return AT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::TokenType::OR || token.type == lexer::TokenType::IMPLIES
		|| token.type == lexer::TokenType::PERIOD || token.type == lexer::TokenType::CPAREN 
		|| token.type == lexer::TokenType::T_EOF) {
		return true;
	}
	else {
		throw std::invalid_argument("expecting '^', 'v', '->', '.', or ')' but got " + token.lexeme);
	}
}

bool L(){
	if (A()) {
		return true;
	}
	lexer::Token token = Lex->get();
	if (token.type == lexer::TokenType::NOT) {
		return L();
	}
	return false;
}

bool A(){
	lexer::Token token = Lex->get();
	if (token.type == lexer::TokenType::TRUE) {
		return true;
	}
	else if (token.type == lexer::TokenType::FALSE) {
		return true;
	}
	else if (token.type == lexer::TokenType::OPAREN) {
		if (IT()) {
			lexer::Token token = Lex->get();
			return (token.type == lexer::TokenType::CPAREN) ? true: false;
		}
		return false;
	}
	return false;
}
}
