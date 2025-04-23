#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace Hermes {
namespace Test {

class TestCase {
public:
    TestCase(const std::string& name) : name_(name) {}
    virtual ~TestCase() = default;
    
    virtual bool run() = 0;
    const std::string& getName() const { return name_; }
    
protected:
    std::string name_;
};

class TestRunner {
public:
    static TestRunner& getInstance() {
        static TestRunner instance;
        return instance;
    }
    
    void addTest(TestCase* test) {
        tests_.push_back(test);
    }
    
    bool runAllTests() {
        bool allPassed = true;
        std::cout << "\nRunning tests...\n";
        
        for (auto* test : tests_) {
            std::cout << "Test: " << test->getName() << " - ";
            bool passed = test->run();
            std::cout << (passed ? "PASSED" : "FAILED") << "\n";
            allPassed &= passed;
        }
        
        return allPassed;
    }
    
private:
    TestRunner() = default;
    ~TestRunner() {
        for (auto* test : tests_) {
            delete test;
        }
    }
    std::vector<TestCase*> tests_;
};

#define TEST_CASE(name) \
class name##Test : public Hermes::Test::TestCase { \
public: \
    name##Test() : TestCase(#name) {} \
    bool run() override; \
}; \
static name##Test name##_instance; \
bool name##Test::run()

#define REGISTER_TEST(name) \
    Hermes::Test::TestRunner::getInstance().addTest<name##Test>()

} // namespace Test
} // namespace Hermes 