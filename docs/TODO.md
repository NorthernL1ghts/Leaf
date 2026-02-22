# Leaf compiler — TODO

High-level roadmap. Order is roughly: lex → parse → codegen.

---

## 1. Lexer

- [x] Lex source into tokens (identifiers, literals, operators, keywords, etc.).

## 2. Parser

- [ ] Parse the token stream into an AST — a tree that represents the structure and meaning of the program.

## 3. Code generation

- [ ] Turn the AST into something runnable. Options:
  - **Native:** emit assembly (e.g. x86_64) and link.
  - **Transpile:** emit another language (e.g. C) and feed that into an existing compiler.

---

*No fixed plan — we’ll pick direction as we go.*

---

## Fix these urgently

- [x] `file_contents` does not check for NULL malloc return values.

- [ ] Tokens do not need to be linked lists, or have create/free functions.
  - We can also remove `print_tokens` while we are at it.

- [ ] When lexing, zero out the given token pointer using memset.

- [ ] Get rid of `integer_t`; just use `long long` and move on.

- [ ] Complete the change to `parse_expr`: accept `char* source`, `char** end`, and `Node* result`. Get rid of `working_node` completely and use `result`. Get rid of root node allocation — that will be handled at a higher level; just use `result`.

- [ ] Parse in a while loop, instead of just parsing a single expression.
  - Maybe a parsing context contains multiple environments (for types, defined variables, etc.). That would let the parser look up variable-access symbols to ensure they are defined and have the right type.
  - This is also where the operator environment could live: a mapping of operators to functions that apply them.
  - Each would need to record what kind of operator it is (e.g. prefix unary, postfix unary, infix binary, etc.). We need a way to define a new operator programmatically that doesn’t suck.

---

## Miscellaneous

**Unnamed variables**

It would be nice if an assignment and/or variable declaration could have no identifier and instead work on a single unnamed variable in the environment.
