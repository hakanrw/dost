# Dost
Social platforming project written with C++

## Author
Ahmet Hakan Candar
20220702022

## Project Structure
This project consists of three subprojects
  - `lib` the base library that handles graphs and people
  - `tui` a terminal interface to interact with the base library
  - `gui` a graphical user interface to interact with the base library

## Building Steps
For building all subprojects, do either
  - `./build.sh` (UNIX) or `build.bat` (NT)
Or
  - `cmake -B build` Create Makefile
  - `cmake --build build` Build with Make

## Running
Do either
  - `./run.sh` (UNIX) or `run.bat` (NT)
Or
  - `./build/tui/dost-tui` (UNIX) or `build\tui\dost-tui.exe` (NT)
