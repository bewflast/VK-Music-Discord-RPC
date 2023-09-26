cmake_minimum_required(VERSION 3.24)
project(Vk-Discord-RPC)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ext-libs/curl)
add_subdirectory(ext-libs/discord-rpc)
add_subdirectory(src)