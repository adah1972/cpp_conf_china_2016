#include <algorithm>        // std::sort
#include <iostream>         // std::cin/cout
#include <string>           // std::string
#include <utility>          // std::pair/make_pair
#include <vector>           // std::vector

using namespace std;

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

vector<string> backsort(const vector<string>& lines)
{
    vector<pair<string, string>> pairs;
    for (auto& line : lines) {
        auto split_line = split(line, '.');
        reverse(split_line.begin(), split_line.end());
        pairs.emplace_back(make_pair(join(split_line, '.'), line));
    }
    sort(pairs.begin(), pairs.end());
    vector<string> result(pairs.size());
    transform(pairs.begin(), pairs.end(), result.begin(),
              [](const pair<string, string>& pr) { return pr.second; });
    return result;
}

int main()
{
    vector<string> input;
    for (;;) {
        string line;
        getline(cin, line);
        if (!cin) {
            break;
        }
        input.emplace_back(move(line));
    }
    vector<string> result = backsort(input);
    for (auto& item : result) {
        cout << item << endl;
    }
}
