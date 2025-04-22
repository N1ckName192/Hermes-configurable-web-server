cmake_minimum_required(VERSION 3.10)
project(Hermes)

set(CMAKE_CXX_STANDARD 17)

# Пути к Boost
set(BOOST_ROOT "C:/boost")

# Найти Boost
find_package(Boost REQUIRED COMPONENTS system)

# Инклуды
include_directories(
    include
    ${Boost_INCLUDE_DIRS}
)

# Определение _WIN32_WINNT
add_definitions(-D_WIN32_WINNT=0x0601)

# Исходники
set(SOURCE_FILES
    src/main.cpp
    src/HttpServer.cpp
    src/Router.cpp
    src/ProxyServer.cpp
)

# Создание исполняемого файла
add_executable(Hermes-configurable-web-server ${SOURCE_FILES})

# Линковка Boost
target_link_libraries(Hermes-configurable-web-server
    PRIVATE 
    Boost::system
    Boost::headers
)