add_library(models OBJECT test.proto)
target_link_libraries(models PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(models PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")


protobuf_generate(TARGET models)
protobuf_generate(TARGET models
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
)