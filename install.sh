#!bin/sh

echo Launching installation
cmake .
cmake --build .
echo Cleaning directory..
rm cmake_install.cmake
rm CMakeCache.txt
rm Makefile
rm -r CMakeFiles
rm src/cmake_install.cmake
rm src/Makefile
rm -r src/CMakeFiles
mv src/noise ./noise
echo Installation finished