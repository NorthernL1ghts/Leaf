@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "ROOT=%SCRIPT_DIR%.."
cd /d "%ROOT%"

set "BUILD_DIR=build"
set "CMAKE_GENERATOR=MinGW Makefiles"
set "CMAKE_C_COMPILER=gcc"
set "EXE_NAME=leaf.exe"
set "DEFAULT_LEAF_FILE=examples\Simple.leaf"

if not exist "CMakeLists.txt" (
    echo CMakeLists.txt not found in %ROOT%
    exit /b 1
)

cmake -B "%BUILD_DIR%" -G "%CMAKE_GENERATOR%" -DCMAKE_C_COMPILER=%CMAKE_C_COMPILER%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

cmake --build "%BUILD_DIR%"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

set "EXE="
for %%D in ("%BUILD_DIR%" "%BUILD_DIR%\Debug" "%BUILD_DIR%\Release") do (
    if not defined EXE if exist "%%~D\%EXE_NAME%" set "EXE=%%~D\%EXE_NAME%"
)
if "%EXE%"=="" (
    echo %EXE_NAME% not found under %BUILD_DIR%\
    exit /b 1
)

set "LEAF_FILE=%~1"
if "%LEAF_FILE%"=="" set "LEAF_FILE=%DEFAULT_LEAF_FILE%"
if not exist "%LEAF_FILE%" if "%~1" neq "" if "%~1"=="%~nx1" set "LEAF_FILE=examples\%~1"
if not exist "%LEAF_FILE%" (
    echo File not found: %LEAF_FILE%
    exit /b 1
)

"%EXE%" "%LEAF_FILE%"
set "EXIT_CODE=%ERRORLEVEL%"
echo Exit code: %EXIT_CODE%
exit /b %EXIT_CODE%
