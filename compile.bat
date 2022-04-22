CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"

cd curl-master/winbuild
nmake /f Makefile.vc mode=static

cd ../../discord-rpc-master
cmake -G "Visual Studio 16 2019" -A Win32 -S . -B "build32"
cmake --build build32 --config Release
cd ../
cmake -G "Visual Studio 16 2019" -A Win32 -S . -B "build32"
cmake --build build32 --config Release