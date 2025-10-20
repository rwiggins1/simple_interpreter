#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cctype>

namespace lexer {
	// Token types
	enum TokenType {
		T_TRUE,      // T
		T_FALSE,     // F
		T_NOT,       // ~
		T_OR,        // v
		T_AND,       // ^
		T_IMPLIES,   // ->
		T_OPAREN,    // (
		T_CPAREN,    // )
		T_PERIOD,    // .
		T_EOF,       // End of input
		T_ERROR      // Invalid token
	};   

	struct Token {
		TokenType type;
		std::string lexeme;
		size_t position;
	};

class Lex {
private:
	std::string input;
	size_t position;
    
	void skipWhitespace() {
		while (position < input.length() && isspace(static_cast<unsigned char>(input[position]))) {
			position++;
		}
	}
    
public:
	Lex(const std::string& str) : input(str), position(0) {}

	Token peek() {
		size_t savedPosition = position;
		Token token = get();
		position = savedPosition;
		return token;
	}

	// get next token
	Token get() {
		skipWhitespace();

		Token token;

		if (position >= input.length()) {
			token.type = T_EOF;
			token.position = position;
			return token;
		}
		
		char c = input[position];
		switch (c) {
			case 'T':
				token.type = T_TRUE;
				token.lexeme = "T";
				break;
			case 'F':
				token.type = T_FALSE;
				token.lexeme = "F";
				break;
			case '~':
				token.type = T_NOT;
				token.lexeme = "~";
				break;
			case 'v':
				token.type = T_OR;
				token.lexeme = "v";
				break;
			case '^':
				token.type = T_AND;
				token.lexeme = "^";
				break;
			case '(':
				token.type = T_OPAREN;
				token.lexeme = "(";
				break;
			case ')':
				token.type = T_CPAREN;
				token.lexeme = ")";
				break;
			case '.':
				token.type = T_PERIOD;
				token.lexeme = ".";
				break;
			case '-':
				if (position + 1 < input.length() && input[position + 1] == '>') {
					token.type = T_IMPLIES;
					token.lexeme = "->";
				}
				else {
					token.type = T_ERROR;
					token.lexeme = "-";
				}
				break;
			default:
				token.type = T_ERROR;
				token.lexeme = std::string(1, c);
				break;
		}
		
		token.position = position;
		position += token.lexeme.length();
		return token;
	}
};
}

#endif
