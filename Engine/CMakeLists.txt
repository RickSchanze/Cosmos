cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake)
project(CosmosCode)
if (MSVC)
    add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif ()
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.h)

# 在这里控制是否开启Debug
#add_definitions(-DCOSMOS_DEBUG)

add_library(${PROJECT_NAME} ${SOURCE_FILES}
        ${HEADER_FILES} Source/Resource/Model.cpp Include/Resource/Model.h)

configure_file(${PROJECT_SOURCE_DIR}/Include/Global/ExternalVariables.h.in
        ${PROJECT_SOURCE_DIR}/Include/Global/ExternalVariables.h)

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

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)



