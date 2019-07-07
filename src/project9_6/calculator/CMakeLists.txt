project(calculator)
file(GLOB INC_LOCAL *.h *.hpp)
add_library (calculator STATIC "Calculator.cpp" "Lexer.cpp" "Parser.cpp" "Error.cpp" ${INC_LOCAL})
install(TARGETS calculator DESTINATION lib)

#install(FILES Calculator.h DESTINATION include)
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library (calculatorD SHARED "Calculator.cpp" "Lexer.cpp" "Parser.cpp" "Error.cpp" ${INC_LOCAL})
install(TARGETS calculatorD DESTINATION lib)

#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")