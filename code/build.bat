@echo off
IF NOT DEFINED clset (call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64)

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl -nologo -FC -Zi /EHsc /I ..\include ..\code\main.cpp /link /libpath:..\lib SDL2main.lib SDL2.lib opengl32.lib glew32.lib glew32s.lib /SUBSYSTEM:CONSOLE
popd