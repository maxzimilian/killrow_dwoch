@echo off
del /F /Q main.exe

mingw32-make -f MakeFile

main.exe