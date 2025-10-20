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
		return (token.type == lexer::T_PERIOD) ? true: false;
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
	if (token.type == lexer::T_IMPLIES) {
		Lex->get();
		if (OT()) {
			return IT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::T_PERIOD || token.type == lexer::T_CPAREN 
		|| token.type == lexer::T_EOF){
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
	if(token.type == lexer::T_OR) {
		Lex->get();
		if (AT()) {
			return OT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::T_IMPLIES || token.type == lexer::T_PERIOD 
		|| token.type == lexer::T_CPAREN || token.type == lexer::T_EOF) {
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
	if (token.type == lexer::T_AND) {
		Lex->get();
		if (L()) {
			return AT_Tail();
		}
		return false;
	}
	else if (token.type == lexer::T_OR || token.type == lexer::T_IMPLIES
		|| token.type == lexer::T_PERIOD || token.type == lexer::T_CPAREN 
		|| token.type == lexer::T_EOF) {
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
	if (token.type == lexer::T_NOT) {
		return L();
	}
	return false;
}

bool A(){
	lexer::Token token = Lex->get();
	if (token.type == lexer::T_TRUE) {
		return true;
	}
	else if (token.type == lexer::T_FALSE) {
		return true;
	}
	else if (token.type == lexer::T_OPAREN) {
		if (IT()) {
			lexer::Token token = Lex->get();
			return (token.type == lexer::T_CPAREN) ? true: false;
		}
		return false;
	}
	return false;
}
}
