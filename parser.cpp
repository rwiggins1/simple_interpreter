#include "lexer.hpp"
#include <stack>
#include <stdexcept>

namespace parser {
static lexer::Lex* Lex;

std::stack<bool> values;


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
		return (token.type == lexer::TokenType::PERIOD);
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
			
			bool right = values.top(); values.pop();
			bool left = values.top(); values.pop();
			bool result = !left || right;
			values.push(result);

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
			
			bool right = values.top(); values.pop();
			bool left = values.top(); values.pop();
			bool result = left || right;
			values.push(result);

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
			
			bool right = values.top(); values.pop();
			bool left = values.top(); values.pop();
			bool result = left && right;
			values.push(result);

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
	// Check for '~' first before calling A()
	lexer::Token token = Lex->peek();
	if (token.type == lexer::TokenType::NOT) {
		Lex->get();
		if (L()) {
			bool val = values.top(); values.pop();
			values.push(!val);
			return true;
		}
		return false;
	}
	return A();
}

bool A(){
	lexer::Token token = Lex->get();
	if (token.type == lexer::TokenType::TRUE) {
		values.push(true);
		return true;
	}
	else if (token.type == lexer::TokenType::FALSE) {
		values.push(false);
		return true;
	}
	else if (token.type == lexer::TokenType::OPAREN) {
		if (IT()) {
			lexer::Token token = Lex->get();
			return (token.type == lexer::TokenType::CPAREN);
		}
		return false;
	}
	return false;
}

[[nodiscard]] static bool getResult() {
	if (values.empty()) {
		throw std::logic_error("Cannot get result - no value on stack");
	}

	return values.top();
}
}
