file(GLOB INC_LOCAL *.h *.hpp)
add_executable (project4_1 "HelloWorld.cpp" ${INC_LOCAL})
install (TARGETS project4_1 DESTINATION bin)