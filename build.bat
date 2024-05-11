@echo off

SET PATH=%PATH%;C:\msys64\mingw64\bin
C:\msys64\mingw64\bin\cmake -B build -G "MinGW Makefiles"
C:\msys64\mingw64\bin\cmake --build build
