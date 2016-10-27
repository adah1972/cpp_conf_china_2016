#include <functional>       // std::bind/ref
#include <iostream>         // std::cin/cout
#include <istream>          // std::istream
#include <string>           // std::string
#include <vector>           // std::vector
#include <boost/coroutine2/all.hpp>
#include <range/v3/all.hpp>

using namespace std;
using namespace ranges;

typedef boost::coroutines2::coroutine<const string&> coro_t;

void read_istream(coro_t::push_type& yield, std::istream& is)
{
    for (;;) {
        string line;
        if (getline(is, line)) {
            yield(line);
        } else {
            break;
        }
    }
}

template <typename C>
vector<string> backsort(C&& lines)
{
    vector<pair<string, string>> pairs;
    for (const auto& line : lines) {
        auto split_line = action::split(line, '.');
        pairs.push_back(make_pair(
            to_<string>(split_line | view::reverse | view::join('.')),
            line));
    }
    ranges::sort(pairs);
    return pairs | view::transform([](const auto& pr)
                                   {
                                       return pr.second;
                                   });
}

int main(int argc, char* argv[])
{
    using namespace std::placeholders;
    vector<string> result =
        backsort(coro_t::pull_type(boost::coroutines2::fixedsize_stack(),
                                   bind(read_istream, _1, std::ref(cin))));
    for (auto& item : result) {
        cout << item << endl;
    }
}
