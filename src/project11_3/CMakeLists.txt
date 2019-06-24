file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project11_3 "int.cpp" ${INC_LOCAL})
install (TARGETS project11_3 DESTINATION bin)