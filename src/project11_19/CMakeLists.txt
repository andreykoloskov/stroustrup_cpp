file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project11_19 "main.cpp" "ptr.cpp" ${INC_LOCAL})
install (TARGETS project11_19 DESTINATION bin)