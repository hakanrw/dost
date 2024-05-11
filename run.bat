@echo off
call build.bat

echo.
echo ------------- Dost -------------
echo 1. Run GUI (Graphical Interface)
echo 2. Run TUI (Terminal Interface)
echo --------------------------------
set /p option=

IF "%option%" == "1" (
    call build\gui\dost-gui.exe
) ELSE (
	IF "%option%" == "2" (
		call build\tui\dost-tui.exe
	) ELSE (
		echo No such option
	)
)