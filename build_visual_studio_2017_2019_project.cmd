@echo off

echo "INIT MSVS Environment"
cd "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\" 
call vcvars64.bat
cd %~dp0

if exist build_vs (
    echo "DELETE build_vs directory"
    rd /s /q build_vs
)

echo "CREATE build_vs directory"
md build_vs

cd build_vs

echo "call cmake"
cmake -G "Visual Studio 15 2017" ^
	-A x64 ^
	../

cmake --build . --config Release -- -m:12
cmake --build . --config Debug -- -m:12
