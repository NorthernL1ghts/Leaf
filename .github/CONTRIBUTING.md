# Contributing to Leaf

Thank you for your interest in contributing.

## How to contribute

- **Bug fixes and features:** Open an issue to discuss first if the change is large, then open a pull request against `main`.
- **Documentation:** Fixes and improvements to the README, `docs/`, or comments in code are welcome via pull request.
- **Questions and ideas:** Open a [Discussion](https://github.com/NorthernL1ghts/Leaf/discussions) or an issue.

## Development setup

1. Clone the repo and ensure you have the [requirements](README.md#requirements) (CMake 3.20+, GCC).
2. Build from the repo root:
   ```bash
   cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc
   cmake --build build
   ```
3. Run the compiler with a Leaf file, e.g. `./build/leaf examples/Example.leaf`.

## Pull requests

- Use the pull request template and fill in the checklist.
- Keep changes focused; prefer several small PRs over one large one.
- Ensure the project still builds with GCC and that there are no new warnings.

## Code of conduct

This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md). By participating, you agree to uphold it.
