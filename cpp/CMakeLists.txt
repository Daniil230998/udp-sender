cmake_minimum_required(VERSION 3.14)
project(udp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER message.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

add_executable(udp_server udp_server.cpp)

add_executable(udp_client udp_client.cpp)# overtaking.cpp overtaking.hpp)

target_link_libraries(udp_server pthread proto ${PROTOBUF_LIBRARY})

target_link_libraries(udp_client pthread proto ${PROTOBUF_LIBRARY})
