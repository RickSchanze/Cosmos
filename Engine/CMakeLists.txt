cmake_minimum_required(VERSION 3.26)
set(CMAKE_TOOLCHAIN_FILE C:/Users/Echo/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(CosmosCode)
if (MSVC)
    add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif ()
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES}
        ${HEADER_FILES})

configure_file(${PROJECT_SOURCE_DIR}/Include/Global/GlobalDefinition.h.in
        ${PROJECT_SOURCE_DIR}/Include/Global/GlobalDefinition.h)

target_include_directories(${PROJECT_NAME} PUBLIC Include)
target_include_directories(${PROJECT_NAME} PRIVATE Source)

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

