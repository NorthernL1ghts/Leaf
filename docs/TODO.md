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
