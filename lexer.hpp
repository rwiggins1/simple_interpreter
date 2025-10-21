#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cctype>

namespace lexer {
	// Token types
	enum class TokenType {
		TRUE,      // T
		FALSE,     // F
		NOT,       // ~
		OR,        // v
		AND,       // ^
		IMPLIES,   // ->
		OPAREN,    // (
		CPAREN,    // )
		PERIOD,    // .
		T_EOF,       // End of input
		ERROR      // Invalid token
	};

	struct Token {
		TokenType type;
		std::string lexeme;
		size_t position;
	};

class Lex {
private:
	std::string input;
	size_t position = 0;
    
	void skipWhitespace() noexcept {
		while (position < input.length() && isspace(static_cast<unsigned char>(input[position]))) {
			position++;
		}
	}
    
public:
	explicit Lex(const std::string& str) : input(str) {}

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
			token.type = TokenType::T_EOF;
			token.position = position;
			return token;
		}
		
		char c = input[position];
		switch (c) {
			case 'T':
				token.type = TokenType::TRUE;
				token.lexeme = "T";
				break;
			case 'F':
				token.type = TokenType::FALSE;
				token.lexeme = "F";
				break;
			case '~':
				token.type = TokenType::NOT;
				token.lexeme = "~";
				break;
			case 'v':
				token.type = TokenType::OR;
				token.lexeme = "v";
				break;
			case '^':
				token.type = TokenType::AND;
				token.lexeme = "^";
				break;
			case '(':
				token.type = TokenType::OPAREN;
				token.lexeme = "(";
				break;
			case ')':
				token.type = TokenType::CPAREN;
				token.lexeme = ")";
				break;
			case '.':
				token.type = TokenType::PERIOD;
				token.lexeme = ".";
				break;
			case '-':
				if (position + 1 < input.length() && input[position + 1] == '>') {
					token.type = TokenType::IMPLIES;
					token.lexeme = "->";
				}
				else {
					token.type = TokenType::ERROR;
					token.lexeme = "-";
				}
				break;
			default:
				token.type = TokenType::ERROR;
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
