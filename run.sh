#!/usr/bin/sh

. ./build.sh

echo
echo "------------- Dost -------------"
echo "1. Run GUI (Graphical Interface)"
echo "2. Run TUI (Terminal Interface)"
echo "--------------------------------"
read option

if [ $option -eq 1 ]; then
	./build/gui/dost-gui
elif [ $option -eq 2 ]; then
	./build/tui/dost-tui
else
	echo "No such option"
fi
