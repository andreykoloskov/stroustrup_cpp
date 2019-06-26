file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project11_19_b "main.cpp" "assoc.cpp" ${INC_LOCAL})
install (TARGETS project11_19_b DESTINATION bin)