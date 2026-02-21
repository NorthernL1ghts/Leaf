# Design notes

*Informal idea buffer for the Leaf compiler. Nothing here is decided.*

---

## Ideas

### Identifier management

- **Symbol table**: a structured list of known identifiers, each with:
  - **Type** (e.g. `integer`, `fn (int, int) -> int`).
  - **Value or address**: compile-time literal, or a memory location / slot index for codegen.
- **Scoping**: push a new scope on block/function entry, pop on exit. Lookup walks from innermost scope outward; inner bindings shadow outer ones (e.g. parameters shadow globals).
- Enables `let` bindings and, later, closures if we add first-class functions.
- *Open:* one global table vs. per-function tables; how to represent generic/polymorphic types if we add them.

### Runtime evaluator vs compiler

- **Evaluator**: walk the AST and execute nodes (e.g. binary op → read two values, apply op, push result). Fast way to get "something that runs"; good for testing and debugging.
- **Compiler**: emit assembly or C. Better performance and a clear "real" implementation.
- **Shared piece**: lexer, parser, AST, type-checking, and symbol table can be shared; only the codegen path differs (interpreter loop vs. emitter).
- *Open:* ship both (`leaf run` vs `leaf compile`) or commit to compiler-only.

---

## Design constraints & preferences

| Constraint | Note |
|------------|------|
| **Statically typed** | Types checked at compile time; no dynamic dispatch unless we add a dedicated feature. |
| **Compiled** | Target is native or transpiled code, not a built-in interpreter. |
| **Whitespace agnostic** | Meaning does not depend on indentation. Use semicolons or explicit delimiters. |
| **Environments as nodes** | Environments could be first-class (Lisp-style), for meta-programming or reflection later. |
| **Simplicity first** | Small, focused language; avoid feature creep. |
| **Transpilation** | C (or similar) as an output target; reuse existing toolchains for linking and portability. |
| **Top-level calls** | Allow top-level `foo()`-style calls? TBD; affects whether a program is "list of decls" or "decls + main expression". |

---

## Identifier structure (scope)

Scoped bindings as a **linked list of frames**: each frame is a map (or list of bindings); the list is ordered from **innermost to outermost** scope.

```text
[ [ ID -> TYPE ], [ "a" -> integer ] ]
```

- **Lookup**: from head; first match wins (inner shadows outer).
- **Insert**: add to the current (head) frame.
- **Push scope**: prepend a new frame. **Pop scope**: drop the head frame.

---

## Example execution trees

Arithmetic and conditionals with a clear root and scope. Each subtree is an expression; operators are internal nodes, literals are leaves.

*Horizontal layout (root left, branches right):*

```text
  ROOT
    └── /
          ├── integer(34)
          ├── +
          └── integer(35)

  ROOT-x
    └── /
          └── +
                ├── integer(34)
                └── integer(35)

  ROOT-x
    └── ?
          ├── condition
          ├── integer(69)
          └── integer(420)
```

- **ROOT** — program or top-level scope.
- **/**, **+** — division, addition.
- **?** — conditional (condition ? then : else).
- **integer(n)** — integer literal; in codegen, a constant or immediate.

---

## Context: types and variables

Two layers for type-checking and codegen:

- **TYPES** — `TYPE_SYMBOL` → type info (size, alignment, name). Holds built-ins (`integer`, etc.) and later user types (structs, enums).
- **VARIABLES** — `VAR_SYMBOL` → `TYPE_SYMBOL`. Each variable is bound to a type; the type symbol points into the type table for layout and codegen.

*Optional:* **FUNCTIONS** — `FUN_SYMBOL` → signature (arg types + return type), and optionally AST or emitted code.

---

## Lexer & parser (reference)

- **Lexer**: one pass; emit tokens (identifier, literal, operator, keyword, punctuation). Skip comments and whitespace. Optional: attach source location (line/column) for errors.
- **Parser**: consume tokens, build AST. Main design points: expression precedence (`+` vs `*`), statement vs expression, and how blocks/scopes hook into the identifier structure above.
- **Errors**: use the existing error structure in `main.c`; report with a message and optional location.
