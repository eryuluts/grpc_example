#include <test.grpc.pb.h>
#include <grpcpp/grpcpp.h>

class TestServiceImpl final : public test_service::TestService::Service
{
    grpc::Status DoTest(grpc::ServerContext *context, const test_service::TestReq *request,
                        test_service::TestRep *reply) override
    {
        reply->set_msg("Hello");
        return grpc::Status::OK;
    }
};

void RunServer(uint16_t port)
{
    std::string server_address = absl::StrFormat("localhost:%d", port);
    TestServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main()
{
    RunServer(8181);
    return 0;
}