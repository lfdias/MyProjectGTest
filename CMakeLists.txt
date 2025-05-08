# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e padrão do C++
project(MyMathProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Diretórios de cabeçalho
include_directories(include)

# Adicionar o Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Separação clara entre os arquivos fonte do projeto e de teste
set(SOURCE_FILES
    src/my_math.cpp     # DIFERENÇA: Adiciona os arquivos de código-fonte do projeto.

)

set(TEST_FILES
    test/test_my_math.cpp # DIFERENÇA: Testes organizados em uma variável separada.
    test/main_test_runner.cpp    # DIFERENÇA: Adiciona um arquivo `main` para rodar todos os testes.
)

# Adicionar todos os arquivos no executável
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES}) # DIFERENÇA: Integra os arquivos de teste e do projeto.

# Linkar o Google Test e pthread
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
