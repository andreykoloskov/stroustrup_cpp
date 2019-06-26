file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project11_19_a "main.cpp" "ptr.cpp" ${INC_LOCAL})
install (TARGETS project11_19_a DESTINATION bin)