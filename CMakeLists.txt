cmake_minimum_required(VERSION 3.10)
project(msgme)

# --- Compiler settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
set(Boost_USE_MULTITHREADED ON)

# --- Dependencies ---
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL REQUIRED)

# --- Include directories ---
# Remove /usr/local/include per tgbot-cpp instructions
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OPENSSL_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

# --- Source files ---
file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

# --- Link libraries ---
# Adjust path to your TgBot installation if needed.
# On Linux (Arch, Ubuntu, etc.), if you installed tgbot-cpp with `sudo make install`,
# the static library will be in /usr/local/lib/libTgBot.a
target_link_libraries(${PROJECT_NAME}
    /usr/local/lib/libTgBot.a
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
)

# --- Install target ---
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
