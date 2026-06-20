cmake_minimum_required(VERSION 3.16)
project(msgme LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(msgme
    main.cpp
    src/bot.cpp
    src/config.cpp
    src/interactive.cpp
    src/send.cpp
    src/setuser.cpp
)

target_include_directories(msgme PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Curses REQUIRED)

find_library(PANEL_LIB panel REQUIRED)
find_library(MENU_LIB menu REQUIRED)

include(FetchContent)
FetchContent_Declare(tgbot-cpp
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp
    GIT_TAG v1.10)
FetchContent_MakeAvailable(tgbot-cpp)

target_link_libraries(msgme PRIVATE
    TgBot
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${CURSES_LIBRARIES}
    ${PANEL_LIB}
    ${MENU_LIB}
)

install(TARGETS msgme RUNTIME DESTINATION bin)
