#!bin/sh

echo Launching installation
cmake .
cmake --build .
cmake --install .

echo Cleaning directory..
rm cmake_install.cmake
rm CMakeCache.txt
rm Makefile
rm -r CMakeFiles
rm src/cmake_install.cmake
rm src/Makefile
rm -r src/CMakeFiles
rm src/noise
rm install_manifest.txt

echo Installation finished