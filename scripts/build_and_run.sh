#!/bin/sh
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$ROOT"

BUILD_DIR="build"
CMAKE_GENERATOR="Unix Makefiles"
CMAKE_C_COMPILER="gcc"
EXE_NAME="leaf"
DEFAULT_LEAF_FILE="examples/Example.leaf"

if [ ! -f "CMakeLists.txt" ]; then
    echo "CMakeLists.txt not found in $ROOT"
    exit 1
fi

cmake -B "$BUILD_DIR" -G "$CMAKE_GENERATOR" -DCMAKE_C_COMPILER="$CMAKE_C_COMPILER"
cmake --build "$BUILD_DIR"

EXE=""
for d in "$BUILD_DIR" "$BUILD_DIR/Debug" "$BUILD_DIR/Release"; do
    if [ -x "$d/$EXE_NAME" ]; then
        EXE="$d/$EXE_NAME"
        break
    fi
done
if [ -z "$EXE" ]; then
    echo "$EXE_NAME not found under $BUILD_DIR/"
    exit 1
fi

LEAF_FILE="${1:-$DEFAULT_LEAF_FILE}"
if [ ! -f "$LEAF_FILE" ] && [ -n "$1" ] && [ "$1" = "$(basename "$1")" ]; then
    LEAF_FILE="examples/$1"
fi
if [ ! -f "$LEAF_FILE" ]; then
    echo "File not found: $LEAF_FILE"
    exit 1
fi

EXIT_CODE=0
"$EXE" "$LEAF_FILE" || EXIT_CODE=$?
echo "Exit code: $EXIT_CODE"
exit "$EXIT_CODE"
