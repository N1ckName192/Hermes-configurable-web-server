cmake_minimum_required(VERSION 3.10)
project(Hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

find_package(Boost 1.88.0 REQUIRED COMPONENTS system filesystem)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
add_definitions(-D_WIN32_WINNT=0x0A00)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(SOURCES
    src/main.cpp
    src/Router.cpp
    src/HttpServer.cpp
    src/ProxyServer.cpp
    src/StaticFileHandler.cpp
    src/ConfigLoader.cpp
    src/TcpProxy.cpp
)

set(TEST_SOURCES
    src/tests/RouterTest.cpp
    src/Router.cpp
    src/StaticFileHandler.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE 
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
