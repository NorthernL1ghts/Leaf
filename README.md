# Leaf

A compiler for the **Leaf** programming language, implemented from scratch.

## Overview

Leaf compiles Leaf source code into runnable output. The codebase is structured along a conventional pipeline: lexing, parsing, and code generation. Codegen may target native assembly (e.g. x86_64) or a transpilation path (e.g. emit C and use an existing toolchain); the approach is still open.

## Example and testing

The repository includes a reference example that defines valid, compilable Leaf syntax:

- **`examples/Example.leaf`** — variables, assignment, and a function signature (e.g. `defun foo(a:integer, b:integer):integer`).

This file serves as a concrete target for the lexer and parser and as a minimal test case as the compiler is developed.

## Project layout

| Path        | Description                                      |
| ----------- | ------------------------------------------------- |
| `docs/`     | Design notes, roadmap (e.g. [docs/TODO.md](docs/TODO.md)), and other documentation. |
| `examples/` | Sample Leaf sources used for development and validation. |

## License

BSD-3-Clause. See [LICENSE](LICENSE).
