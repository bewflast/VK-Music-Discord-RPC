add_definitions(-DCURL_STATICLIB)
set(PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/CURLClient.h)
set(SOURCES source/CURLClient.cpp)

add_library(curl-client STATIC)

target_sources(curl-client PRIVATE ${SOURCES})
target_include_directories(curl-client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(curl-client PROPERTIES PUBLIC_HEADER include/CURLClient.h)

target_link_libraries(curl-client libcurl)