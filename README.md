# Dost
Social platforming project written with C++ and GTK4.


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

### Fedora >=39, RHEL >=9, CentOS Stream
```
# dnf install gcc make cmake gtk4-devel libadwaita-devel 
```

### Ubuntu >=23.10, Debian Unstable
```
# apt install gcc make cmake libgtk-4-dev libadwaita-1-dev
```

### Arch Linux, Manjaro
```
# pacman -Syu gcc make cmake gtk4 libadwaita
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
  - Install [MSYS2](https://github.com/msys2/msys2-installer/releases/download/2024-05-07/msys2-x86_64-20240507.exe)
  - On MSYS2 MINGW64 shell run the following command:
```
pacman -Syu mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake mingw-w64-x86_64-gtk4 mingw-w64-x86_64-libadwaita
```

## Building Steps
Open a terminal window at the root folder of the project.

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
