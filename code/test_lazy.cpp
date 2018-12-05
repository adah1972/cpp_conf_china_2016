#include <iostream>
#include <functional>
#include <vector>
#include <nvwa/functional.h>
#include <range/v3/all.hpp>
#include <boost/coroutine2/all.hpp>

using namespace std;
using namespace std::placeholders;
using namespace nvwa;

template <typename Rs, typename Fn, typename Rng>
auto fmap_view_impl(
    typename boost::coroutines2::coroutine<Rs>::push_type& yield,
    Fn&& f, Rng&& inputs)
{
    for (auto& x : inputs) {
        yield(f(x));
    }
}

template <typename Fn, typename Rng>
auto fmap_view(Fn&& f, Rng&& inputs)
{
    typedef decltype(f(*begin(inputs))) result_type;
    (void)fmap_view_impl<result_type, Fn, Rng>;  // GCC hack
    return typename boost::coroutines2::coroutine<result_type>::pull_type(
        boost::coroutines2::fixedsize_stack(),
        bind(fmap_view_impl<result_type, Fn, Rng>,
             _1,
             forward<Fn>(f),
             forward<Rng>(inputs)));
}

int main()
{
    auto sqr = [](auto x) { return x * x; };
    auto sqr_list = [sqr](auto x) { return fmap(sqr, x); };
    auto sum_list = [](auto x) { return reduce(plus<int>(), x); };
    vector<int> v{1, 2, 3, 4, 5};

    // Eager
    auto sum_sqr_list = compose(sum_list, sqr_list);
    cout << sum_sqr_list(v) << endl;

    // Lazy
    cout << sum_list(fmap_view(sqr, v)) << endl;

    // Lazy using ranges
    cout << ranges::accumulate(v | ranges::view::transform(sqr), 0) << endl;
}
