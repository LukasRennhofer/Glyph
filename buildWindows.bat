@echo off
echo Cleaning old build...
cd build
rmdir /s /q windows
mkdir windows

cd windows

echo Running CMake...
cmake -G "Unix Makefiles" ../..

echo Building Glypth...
make

echo Copying Assets...
xcopy /e /i /h ..\..\src\resources resources