file(GLOB INC_LOCAL *.h *.hpp)
add_executable (project6_18 "Calculator.cpp" ${INC_LOCAL})
install (TARGETS project6_18 DESTINATION bin)