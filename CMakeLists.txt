cmake_minimum_required(VERSION 3.16)
project(msgme LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
include(FetchContent)
FetchContent_Declare(tgbot-cpp
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp
    GIT_TAG v1.10)
FetchContent_MakeAvailable(tgbot-cpp)

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
    GIT_TAG v7.0.0)
FetchContent_MakeAvailable(ftxui)

FetchContent_Declare(cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.6.2)
FetchContent_MakeAvailable(cli11)

target_link_libraries(msgme PRIVATE
    TgBot
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ftxui::screen
    ftxui::dom
    ftxui::component
    CLI11::CLI11
)

install(TARGETS msgme RUNTIME DESTINATION bin)
