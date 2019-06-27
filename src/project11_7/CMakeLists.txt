file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project11_7 "main.cpp" "String.cpp" ${INC_LOCAL})
install (TARGETS project11_7 DESTINATION bin)