#include <iostream>
#include <tuple>
#include <vector>
#include <nvwa/functional.h>

using namespace std;
using namespace nvwa;

template <typename T>
constexpr auto sum(T x)
{
    return x;
}

template <typename T1, typename T2, typename... Targ>
constexpr auto sum(T1 x, T2 y, Targ... args)
{
    return sum(x + y, args...);
}

int main()
{
    (void)sum<int, int, int, int, int>;  // GCC requires this instantiation

    auto sqr = [](auto x) { return x * x; };
    auto sqr_list = [sqr](auto x) { return fmap(sqr, x); };
    auto sum_list = [](auto x) { return reduce(plus<int>(), x); };
    vector<int> v{1, 2, 3, 4, 5};
    tuple<int, int, int, int, int> t{1, 2, 3, 4, 5};

    auto sum_sqr_list = compose(sum_list, sqr_list);
    cout << sum_sqr_list(v) << endl;
    // 55

    cout << pipeline(v, sqr_list, sum_list) << endl;
    // 55

    cout << apply(sum<int, int, int, int, int>, fmap(sqr, t)) << endl;
    // 55

    cout << reduce(plus<int>(), fmap(sqr, t), 0) << endl;
    // 55
}
