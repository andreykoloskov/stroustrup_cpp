file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project10_12_a "main.cpp" "CharQueue1.cpp" ${INC_LOCAL})
add_executable (project10_12_b "main.cpp" "CharQueue2.cpp" ${INC_LOCAL})

install (TARGETS project10_12_a DESTINATION bin)
install (TARGETS project10_12_b DESTINATION bin)