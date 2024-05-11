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


## Required Libraries
The project requires the following components to be installed
  - gcc
  - make
  - CMake
  - GTK4
  - libadwaita

### Fedora, CentOS, RHEL
```
# dnf install gcc make cmake gtk4-devel libadwaita-devel 
```

### Ubuntu, Debian, Mint
```
# apt install gcc make cmake gtk4-dev libadwaita-dev 
```

### Arch, Manjaro
```
# pacman -S gcc make cmake gtk4 libadwaita
```

### macOS with Brew
First, ensure C/C++ compiler and make is installed via XCode
```
$ xcode-select --install
```
Install the remaining components
```
# brew install cmake gtk4 libadwaita
```

### Windows
  - Install and add MinGW-w64 to PATH `https://github.com/niXman/mingw-builds-binaries/releases`
  - Install CMake `https://cmake.org/download/`

Building the `gui` project is not possible on Windows, although you can still build and run `tui`.


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
  - Terminal Interface: `./build/tui/dost-tui` (UNIX) or `build\tui\dost-tui.exe` (NT)
  - Graphical Interface: `./build/gui/dost-gui` (UNIX) or `build\gui\dost-gui.exe` (NT)
