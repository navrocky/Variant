#include <iostream>

#include "variant.h"

using namespace std;

struct Foo {
    int field;
};

void check(bool v, const char* condition)
{
    if (!v)
        throw std::runtime_error(condition);
}

#define CHECK(cond) check(cond, #cond)

void exceptionExpected(std::function<void()> func)
{
    bool hasException = false;
    try
    {
        func();
    }
    catch (const exception& e)
    {
        hasException = true;
    }
    CHECK(hasException);
}

int main()
{
    {
        Variant a = 10;
        CHECK(a.value<int>() == 10);
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
        CHECK(a == 0);
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
            CHECK(a != b);
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

    return 0;
}

