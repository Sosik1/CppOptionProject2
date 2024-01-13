# CMakeList.txt: projekt CMake dla elementu CppOptionProject, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CppOptionProject")

add_library(Option src/Option.cpp)
add_library(Portfolio src/Portfolio.cpp)
add_library(Experiment src/Experiment.cpp)
add_library(FileRW src/FileRW.cpp)

target_include_directories(Option PUBLIC include external)
target_include_directories(Portfolio PUBLIC include)
target_include_directories(Experiment PUBLIC include)
target_include_directories(FileRW PUBLIC include)

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (CppOptionProject "src/main.cpp")
target_link_libraries(CppOptionProject PRIVATE Option Portfolio Experiment FileRW)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppOptionProject PROPERTY CXX_STANDARD 20)
endif()

# Include directories
include_directories(include)

# Add tests
enable_testing()

add_executable(option_test "test/option_test.cpp")
target_link_libraries(option_test PRIVATE Option)
add_test(NAME option_test COMMAND option_test)

add_executable(portfolio_test "test/portfolio_test.cpp")
target_link_libraries(portfolio_test PRIVATE Option Portfolio)
add_test(NAME portfolio_test COMMAND portfolio_test)

add_executable(io_test "test/io_test.cpp")
target_link_libraries(io_test PRIVATE Experiment FileRW Option)
add_test(NAME io_test COMMAND io_test)