# Defines a list of header files for the project. In this case, there is only one header file named Example.hpp.
set(Headers
    ../src/Example.hpp
)

# Defines a list of source files for the project. In this case, there is only one source file named Example.cpp.
set(Sources
    ../src/Example.cpp
)

#  Creates a static library using the defined source and header files. The name of the library will be the value of the This variable.
add_library(${This} STATIC ${Sources} ${Headers})
