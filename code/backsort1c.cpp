#include <algorithm>        // std::sort
#include <iostream>         // std::cin/cout
#include <string>           // std::string
#include <utility>          // std::pair/make_pair
#include <vector>           // std::vector
#include "nvwa/functional.h"
#include "istream_line_reader.h"

using namespace std;
using namespace nvwa;

vector<string> split(const string& str, char delim)
{
    vector<string> result;
    string::size_type last_pos = 0;
    string::size_type pos = str.find(delim);
    while (pos != string::npos) {
        result.emplace_back(
            str.substr(last_pos, pos - last_pos));
        last_pos = pos + 1;
        pos = str.find(delim, last_pos);
        if (pos == string::npos) {
            result.emplace_back(str.substr(last_pos));
        }
    }
    return result;
}

template <typename C>
string join(const C& str_list, char delim)
{
    string result;
    for (auto& item : str_list) {
        result += item;
        result += delim;
    }
    if (result.size() != 0) {
        result.resize(result.size() - 1);
    }
    return result;
}

template <typename C>
vector<string> backsort(C&& lines)
{
    vector<pair<string, string>> pairs;
    for (auto& line : lines) {
        auto split_line = split(line, '.');
        reverse(split_line.begin(),
                split_line.end());
        pairs.emplace_back(
            make_pair(join(split_line, '.'), line));
    }
    sort(pairs.begin(), pairs.end());
    return fmap([](const auto& pr) { return pr.second; },
                pairs);
}

int main()
{
    auto result = backsort(istream_line_reader(cin));
    for (auto& item : result) {
        cout << item << endl;
    }
}
