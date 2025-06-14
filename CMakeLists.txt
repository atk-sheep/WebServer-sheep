cmake_minimum_required(VERSION 3.17)

project(WebServer)

set(CMAKE_CXX_STANDARD 17)

include(config/build.cmake)

option(WEBSERVER "enable webserver" ON)
option(ASIOTEST "enable asiotest" OFF)

if(WEBSERVER)
    add_executable(${PROJECT_NAME} webserver/main.cpp)

    file(GLOB_RECURSE src "${CMAKE_SOURCE_DIR}/src/*.cpp")

    message("${src}")

    target_sources(${PROJECT_NAME} PUBLIC ${src})

    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

if(ASIOTEST)
    add_executable(AsioTest asio_test/asioTest.cpp)

    target_include_directories(AsioTest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()


# install options
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/camera_gw/res/
#         DESTINATION ${CMAKE_BINARY_DIR}/bin/CameraGw/res)

# install(FILES ${CMAKE_BINARY_DIR}/bin/CameraProviderMaster_gateway
#         PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_EXECUTE WORLD_READ
#         RENAME Camera_in_gateway
#         DESTINATION ${CMAKE_BINARY_DIR}/bin/CameraGw)