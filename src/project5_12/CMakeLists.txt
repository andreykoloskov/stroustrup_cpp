file(GLOB INC_LOCAL *.h *.hpp)
add_executable (project5_12 "Words.cpp" ${INC_LOCAL})
install (TARGETS project5_12 DESTINATION bin)