
cmake_minimum_required(VERSION 3.10)
project(MatrixLibrary)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodanie katalogu z plikami nagłówkowymi
include_directories(include)

# Konfiguracja Google Test przy użyciu FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

# Pobranie i dodanie Google Test
FetchContent_MakeAvailable(googletest)

# Dodanie pliku testowego
add_executable(matrix_tests tests/matrix_tests.cpp)

# Linkowanie testów z biblioteką Google Test
target_link_libraries(matrix_tests gtest_main)

# Umożliwienie testowania przy pomocy CTest
enable_testing()

# Rejestrowanie testów w CTest
include(GoogleTest)
gtest_discover_tests(matrix_tests)

# Dodanie głównego programu
add_executable(matrix_main src/main.cpp)

# Linkowanie głównego programu (jeśli klasa matrix ma plik źródłowy, należy go dołączyć)
# Zakładając, że wszystkie definicje są w pliku nagłówkowym, nie ma potrzeby dodawania dodatkowych plików
# Jeśli masz plik matrix.cpp, dodaj go tutaj:
# target_sources(matrix_main PRIVATE src/matrix.cpp)

# (Opcjonalnie) Linkowanie bibliotek, jeśli są potrzebne
# target_link_libraries(matrix_main ...)