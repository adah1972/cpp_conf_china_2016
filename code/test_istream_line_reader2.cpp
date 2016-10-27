#include <iostream>
#include <string>
#include "istream_line_reader.h"

using namespace std;

int main()
{
    for (auto& line :
         istream_line_reader(cin)) {
        cout << line << '\n';
    }
}
