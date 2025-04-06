@echo off
echo Cleaning old build...
mkdir build
cd build
rmdir windows
mkdir windows

cd windows

echo Running CMake...
cmake -G "Unix Makefiles" ../..

echo Building Glyph...
make

start "" Glyph.exe