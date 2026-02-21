# Leaf

**Leaf** is a compiler for the Leaf programming language, implemented from scratch in C.

The compiler follows a conventional pipeline: **lexing** → **parsing** → **code generation**. Code generation may target native assembly (e.g. x86_64) or transpilation to another language (e.g. C); the final target is not yet fixed. For design notes and roadmap, see [Design notes](docs/design_notes.md) and [TODO](docs/TODO.md).

---

## Requirements

| Requirement | Version | Notes |
|-------------|---------|--------|
| [CMake](https://cmake.org/) | 3.20 or later | [Download](https://cmake.org/download/) |
| [GCC](https://gcc.gnu.org/) | — | Required. This project does not support MSVC. On Windows, use [MinGW-w64](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/); ensure `gcc` and `mingw32-make` are on your `PATH`. |

---

## Building

From the repository root:

```bash
cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc
cmake --build build
```

The resulting executable is `build/leaf` on Unix-like systems and `build/leaf.exe` on Windows.

---

## Running

Invoke the compiler with a Leaf source file as the first argument:

```bash
./build/leaf examples/Example.leaf
```

On Windows:

```batch
build\leaf.exe examples\Example.leaf
```

**Windows only:** A helper script configures, builds, and runs in one step. Without arguments it uses `examples/Example.leaf` by default.

```batch
scripts\build_and_run.bat
scripts\build_and_run.bat examples\Other.leaf
```

---

## Example source

The reference example is [`examples/Example.leaf`](examples/Example.leaf). It shows variable declarations, assignment, and a function signature:

```leaf
a : integer = 0
a := 0

b : integer
b := 0

defun foo (a:integer, b:integer):integer {

}
```

This file is used as the reference test case for the lexer and parser.

---

## License

This project is licensed under the BSD-3-Clause license. See [LICENSE](LICENSE) for the full text.
