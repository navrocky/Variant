#include "variant.h"

#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

struct Foo
{
    int field;
};

void check(bool v, int line, const char* condition)
{
    if (!v)
    {
        stringstream ss;
        ss << "Error at line " << line << ": " << condition;
        throw std::runtime_error(ss.str());
    }
}

#define CHECK(cond) check(cond, __LINE__, #cond)

void exceptionExpected(std::function<void()> func)
{
    bool hasException = false;
    try
    {
        func();
    }
    catch (const exception&)
    {
        hasException = true;
    }
    CHECK(hasException);
}

int main()
{
    try
    {
        {
            Variant a = 10;
            CHECK(a.value<int>() == 10);
        }

        {
            Variant a;
            CHECK(a.isType<int>() == false);
        }

        {
            Variant a;
            exceptionExpected([&](){;
                CHECK(a.valueRef<int>() == 0);
            });
        }

        {
            Variant a;
            CHECK(a.value<int>() == 0);
        }

        {
            Variant a;
            CHECK(a.isEmpty());
            a = 10;
            CHECK(!a.isEmpty());
            a.clear();
            CHECK(a.isEmpty());
        }

        {
            auto a = Variant::fromValue(10);
            CHECK(a.value<int>() == 10);
        }

        {
            Variant a = 10;
            Variant b(a);
            CHECK(b.value<int>() == 10);
        }

        {
            Variant a = 10;
            Variant b;
            b = a;
            CHECK(b.value<int>() == 10);
        }

        {
            Variant a = 10;
            CHECK(a.isType<float>() == false);
        }

        {
            Variant a = 0;
            Variant b = 10;
            CHECK(a < b);
            CHECK(b > a);
            CHECK(b != a);
            CHECK(!(b == a));
        }

        {
            Variant a = 0;
            CHECK(a > -1);
            CHECK(a < 1);
            CHECK(a == Variant(0)); // VS2013 has a multiple overloads in this situation
            CHECK(a != 1);
        }

        {
            Variant a = Foo {10};
            CHECK(a.value<Foo>().field == 10);
        }

        {
            // we cannot check equality of types without equal operator
            Variant a = Foo {10};
            Variant b = Foo {20};

            exceptionExpected([&](){
                CHECK(a == b);
            });

            exceptionExpected([&](){
                CHECK(a != b);
            });
        }

        {
            // we cannot compare types without "less than" operator
            Variant a = Foo {10};
            Variant b = Foo {20};
            exceptionExpected([&](){
                CHECK(a < b);
            });

            exceptionExpected([&](){
                CHECK(a > b);
            });
        }

        {
            // we cannot compare incompatible types
            Variant a = 10;
            Variant b = 10.0;
            exceptionExpected([&](){
                CHECK(a == b);
            });
        }

        {
            Variant a = 10;
            Variant b;
            b = a;
            CHECK(a == b);
        }

        {
            Variant a = std::shared_ptr<int>();
            Variant b = std::shared_ptr<int>();
            b = a;
            CHECK(a == b);
            CHECK(!(a < b));
        }
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    cout << "All tests completed successfully" << endl;
    return 0;
}
