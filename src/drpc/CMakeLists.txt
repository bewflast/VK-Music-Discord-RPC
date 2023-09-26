set(PUBLIC_HEADER include/DRPC.h)
set(SOURCES source/DRPC.cpp)

add_library(drpc STATIC)

target_sources(drpc PRIVATE ${SOURCES})
target_include_directories(drpc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(drpc PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADER})

target_include_directories(drpc PUBLIC ${PROJECT_SOURCE_DIR}/ext-libs/discord-rpc/include)

target_link_libraries(drpc discord-rpc)
target_link_libraries(drpc curl-client)