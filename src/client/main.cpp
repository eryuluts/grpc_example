#include <test.grpc.pb.h>
#include <grpcpp/grpcpp.h>

class TestClient
{
public:
    TestClient(std::shared_ptr<grpc::Channel> channel)
        : stub(test_service::TestService::NewStub(channel)) {}

    std::string DoTest()
    {
        test_service::TestReq req;
        test_service::TestRep resp;

        grpc::ClientContext context;
        auto status = stub->DoTest(&context, req, &resp);

        // Act upon its status.
        if (status.ok())
        {
            return resp.msg();
        }
        else
        {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<test_service::TestService::Stub> stub;
};

int main()
{
    TestClient client(
        grpc::CreateChannel("localhost:8181", grpc::InsecureChannelCredentials()));

    while (true)
    {
        std::string resp = client.DoTest();
        std::cout << "Response: " << resp << std::endl;
        absl::SleepFor(absl::Seconds(1));
    }
}