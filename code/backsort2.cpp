#include <fstream>          // std::ifstream
#include <functional>       // std::bind/ref
#include <iostream>         // std::cin/cout
#include <istream>          // std::istream
#include <string>           // std::string
#include <vector>           // std::vector
#include <nvwa/file_line_reader.h>
#include <boost/coroutine2/all.hpp>
#include <range/v3/all.hpp>

using namespace std;
using namespace std::placeholders;
using namespace nvwa;
using namespace ranges;

typedef boost::coroutines2::coroutine<const string&> coro_t;

void cat(coro_t::push_type& yield, int files_cnt, char* file_names[])
{
    for (int i = 0; i < files_cnt; ++i) {
        FILE* fp = fopen(file_names[i], "r");
        if (!fp) continue;
        for (auto& line : file_line_reader(fp)) {
            yield(line);
        }
        fclose(fp);
    }
}

template <typename C>
vector<string> backsort(C&& lines)
{
    vector<pair<string, string>> pairs;
    for (const string& line : lines) {
        auto split_line = action::split(line, '.');
        pairs.emplace_back(make_pair(
            to_<string>(split_line | view::reverse | view::join('.')),
            line));
    }
    ranges::sort(pairs);
    return pairs | view::values;
}

int main(int argc, char* argv[])
{
    vector<string> result;
    if (argc > 1) {
        result = backsort(coro_t::pull_type(
            boost::coroutines2::fixedsize_stack(),
            bind(cat, _1, argc - 1, argv + 1)));
    } else {
        result = backsort(file_line_reader(stdin));
    }
    for (auto& item : result) {
       cout << item << endl;
    }
}
