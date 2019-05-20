file(GLOB INC_LOCAL *.h *.hpp)

add_library (calculator STATIC "Calculator.cpp" "Lexer.cpp" "Parser.cpp" "Error.cpp" ${INC_LOCAL})

add_executable (project9_6 "main.cpp" "Calculator.h")

target_link_libraries(project9_6 calculator)

install(TARGETS project9_6 DESTINATION bin)