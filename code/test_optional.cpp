#include <functional>
#include <iostream>
#include <ostream>
#include <nvwa/functional.h>

using namespace std;
using namespace nvwa;

template <typename T>
ostream& operator<<(ostream& os, const optional<T>& value)
{
    if (value.has_value()) {
        os << *value;
    } else {
        os << "invalid";
    }
    return os;
}

int main()
{
    auto sqr = [](auto x) { return x * x; };
    auto sqr_opt = lift_optional(sqr);
    auto plus_opt = lift_optional(plus<int>());
    auto invalid_value = optional<int>();
    cout << sqr_opt(make_optional(2)) << endl;                     // 4
    cout << sqr_opt(invalid_value) << endl;                        // invalid
    cout << plus_opt(make_optional(2), make_optional(3)) << endl;  // 5
    cout << plus_opt(make_optional(2), invalid_value) << endl;     // invalid
}
