# Propositional Logic Interpreter

A C++ interpreter for propositional logic expressions that lexes, parses, and evaluates boolean equations using recursive descent parsing.

## Features

- **Lexical Analysis**: Tokenizes propositional logic expressions
- **Syntax Analysis**: Recursive descent parser that handles precedence
- **Semantic Evaluation**: Stack-based evaluation of boolean expressions
- **Operator Support**: NOT (`~`), AND (`^`), OR (`v`), IMPLIES (`->`)

## Supported Grammar

The interpreter implements the following formal grammar:

```
B  → IT '.'
IT → OT IT'
IT' → '->' OT IT' | ε
OT → AT OT'
OT' → 'v' AT OT' | ε
AT → L AT'
AT' → '^' L AT' | ε
L  → '~' L | A
A  → 'T' | 'F' | '(' IT ')'
```

## Building

Requires CMake 3.10+ and a minimum C++17 compiler.

```bash
mkdir build && cd build
cmake ..
make
```

This produces two executables:
- `interpreter` - Main interpreter binary
- `test` - Lexer testing

## Usage

Currently configured for programmatic use. Modify `main.cpp` to evaluate different expressions:

```cpp
std::string input = "TvF.";  // true OR false
lexer::Lex lex(input);

if (parser::B(lex)) {
    bool result = parser::getResult();
    std::cout << (result ? "True" : "False");
} else {
    std::cout << "Syntax invalid";
}
```

### Example Expressions

| Expression | Meaning | Result |
|------------|---------|--------|
| `T.` | True | True |
| `~F.` | NOT False | True |
| `T^F.` | True AND False | False |
| `TvF.` | True OR False | True |
| `F->T.` | False IMPLIES True | True |
| `T->(F->T).` | Nested implication | True |
| `~(T^F).` | NOT (True AND False) | True |

