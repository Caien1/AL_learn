@echo off
w:
mkdir out
g++ .\code\main.cpp -o .\out\main.exe -lUser32 -mwindows -lGdi32 -Wall



