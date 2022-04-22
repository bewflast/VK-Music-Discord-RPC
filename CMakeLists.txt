cmake_minimum_required(VERSION 3.17)
project(zaloopa)

set(CMAKE_CXX_STANDARD 17)

set(
        SOURCE_FILES
        ./src/main.cpp
        ./src/DRPC.cpp
        ./src/CURLClient.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/curl/include/)
include_directories(${PROJECT_SOURCE_DIR}/discord-rpc/include/)

link_directories(${PROJECT_SOURCE_DIR}/curl/builds/libcurl-vc-x86-release-static-ipv6-sspi-schannel/lib)
link_libraries(libcurl_a)

link_directories(${PROJECT_SOURCE_DIR}/discord-rpc/build32/src/Release)
link_libraries(discord-rpc)

add_executable(vdiscord ${SOURCE_FILES})
target_link_libraries(vdiscord ws2_32 crypt32 wldap32 normaliz)
target_link_libraries( vdiscord libcurl_a )
target_link_libraries(vdiscord discord-rpc)