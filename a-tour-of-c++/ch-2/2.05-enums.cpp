#include<iostream>

using namespace std;

enum class RGBColor
{
    red,
    green,
    blue
};

enum class TrafficLightColor
{
    red,
    yellow,
    green
};

TrafficLightColor operator++(TrafficLightColor& t)
{
    switch (t) {
    case TrafficLightColor::green:
        t = TrafficLightColor::yellow;
        break;
    case TrafficLightColor::yellow:
        t = TrafficLightColor::red;
        break;
    case TrafficLightColor::red:
        t = TrafficLightColor::green;
        break;
    }

    return t;
}

enum BasicFooBarEnum
{
    foo,
    bar
};

enum BasicBazEnum
{
    baz
};


int main()
{
    RGBColor pixel = RGBColor::red;
    TrafficLightColor trafficLight = TrafficLightColor::red;

    if (pixel == RGBColor::green) {
        cout << "pixel is equal to RGBColor::green\n";
    } else {
        cout << "pixel is NOT equal to RGBColor::green\n";
    }

    // Error: no match for 'operator==' (operand types are 'RGBColor' and 'TrafficLightColor')
    // if (pixel == trafficLight) {
    //     cout << "pixel color is equal to traffic light color";
    // }

    BasicFooBarEnum foo = BasicFooBarEnum::foo;
    BasicBazEnum baz = BasicBazEnum::baz;

    cout << "foo: " << foo << "\n";
    cout << "baz: " << baz << "\n";

    // This is allowed but not good.
    // Warning: comparison between 'enum BasicFooBarEnum' and 'enum BasicBazEnum' [-Wenum-compare]
    if (foo == baz) {
        cout << "BasicFooBarEnum::foo is equal to BasicBazEnum::baz\n";
    }

    int fooInt = foo;
    int bazInt = baz;

    // Comparing the raw ints will work though
    if (fooInt == bazInt) {
        cout << "fooInt: " << fooInt << "\n";
        cout << "bazInt: " << bazInt << "\n";
        cout << "fooInt is equal to bazInt\n";
    }

    // Not allowed since RGBColor is an enum class and strongly typed
    // int x = RGBColor::red;

    // Allowed since BasicFooBarEnum is a plain enum
    int x = BasicFooBarEnum::foo;

    TrafficLightColor result;
    TrafficLightColor trafficLight2 = TrafficLightColor::red;
    result = ++trafficLight2;
    result = ++trafficLight2;

    cout << (trafficLight2 == TrafficLightColor::yellow
            ? "trafficLight2 is yellow"
            : "trafficLight2 is not yellow");
}
