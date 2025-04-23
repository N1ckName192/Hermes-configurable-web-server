#include "Hermes/Test/TestFramework.h"
#include "Hermes/Router.h"
#include "Hermes/StaticFileHandler.h"
#include <boost/beast/http.hpp>

namespace Hermes {
namespace Test {

class RouterBasicTest : public TestCase {
public:
    RouterBasicTest() : TestCase("RouterBasic") {}

    bool run() override {
        Router router("static");
        router.addRoute("/test", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.body() = "OK";
        });

        boost::beast::http::request<boost::beast::http::string_body> req;
        req.target("/test");
        boost::beast::http::response<boost::beast::http::string_body> res;

        router.handleRequest(std::string(req.target()), req, res);

        return res.result() == boost::beast::http::status::ok && 
               res.body() == "OK";
    }
};

namespace {
    auto& test_runner = TestRunner::getInstance();
    auto* RouterBasic_test = new RouterBasicTest();
    struct TestRegistrar {
        TestRegistrar() {
            test_runner.addTest(RouterBasic_test);
        }
    };
    static TestRegistrar registrar;
}

} // namespace Test
} // namespace Hermes

int main() {
    return Hermes::Test::TestRunner::getInstance().runAllTests() ? 0 : 1;
} 