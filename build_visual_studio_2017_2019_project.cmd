@echo off

echo "INIT MSVS2017_2019 Environment"
cd "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\" 
call vcvars64.bat
cd %~dp0

if not exist build_vs (
    echo "CREATE build_vs directory"
    md build_vs
)

cd build_vs

echo "call cmake"
cmake -G "Visual Studio 16 2019" ^
	-A x64 ^
	../

cmake --build . -- -m:12
