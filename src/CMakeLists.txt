add_executable(vk-discord main.cpp)
add_subdirectory(curlclient)
add_subdirectory(drpc)

target_link_libraries(vk-discord curl-client)
target_link_libraries(vk-discord drpc)