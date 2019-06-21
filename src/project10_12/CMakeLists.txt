file(GLOB INC_LOCAL *.h *.hpp)

add_executable (project10_12 "main.cpp" "CharQueueList.cpp" "CharQueueVector.cpp" ${INC_LOCAL})
install (TARGETS project10_12 DESTINATION bin)