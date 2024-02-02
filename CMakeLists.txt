cmake_minimum_required(VERSION 3.22)

project(grpc_test
    LANGUAGES CXX
)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(models)
add_subdirectory(src/server)
add_subdirectory(src/client)
