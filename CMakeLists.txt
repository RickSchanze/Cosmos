cmake_minimum_required(VERSION 3.26)
set(CMAKE_TOOLCHAIN_FILE C:/Users/Echo/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(Cosmos)
if (MSVC)
    add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif ()
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Engine)
add_executable(Cosmos main.cpp)

set(COSMOS_ROOT ${PROJECT_SOURCE_DIR} CACHE STRING "Cosmos root path")
set(COSMOS_LOG_PATH ${COSMOS_ROOT}/Log CACHE STRING "Cosmos log directory path")

target_include_directories(Cosmos PUBLIC Engine/Include)
target_link_libraries(Cosmos PRIVATE CosmosCode)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
