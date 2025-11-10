cmake_minimum_required(VERSION 3.14)
project(Netflix)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Source files for the application
set(SOURCES
    AddCommand.cpp
    Movies.cpp
    Users.cpp
    DataManagement.cpp
    ConsoleMenu.cpp
    HelpCommand.cpp
    RecommendCommand.cpp
    App.cpp
)

# Add the main application executable (without Main.cpp)
add_executable(Netflix
    ${SOURCES}
    Main.cpp
)

# Add the test executable with Main.cpp (test harness)
add_executable(CommandTests
    ${SOURCES}
    Tests/AddCommandTests.cpp
    Tests/RecommendCommandTests.cpp
)

# Include directories for tests
target_include_directories(CommandTests PRIVATE ${CMAKE_SOURCE_DIR})

# Link GoogleTest libraries to the test executable
target_link_libraries(CommandTests gtest gtest_main pthread)
