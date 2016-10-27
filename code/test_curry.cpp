#include <functional>
#include <iostream>
#include <nvwa/functional.h>

using namespace std;

int main()
{
    auto curried_plus = nvwa::make_curry<int(int, int)>(plus<int>());
    auto plus_1 = curried_plus(1);
    cout << curried_plus(1)(1) << endl;
    cout << plus_1(1) << endl;
}
