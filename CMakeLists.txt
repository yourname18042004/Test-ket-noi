cmake_minimum_required(VERSION 3.10)

project(PBL4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Add source files
set(SOURCES
    src/ClientTCP.cpp
)

include(FetchContent)

# Download and add nlohmann_json
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2  # You can specify the version or branch you need
)

FetchContent_MakeAvailable(nlohmann_json)

# Create an executable
add_executable(MyExecutable ${SOURCES})


target_link_libraries(MyExecutable PRIVATE nlohmann_json::nlohmann_json)
