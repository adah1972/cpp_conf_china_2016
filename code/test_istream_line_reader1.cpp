#include <iostream>
#include <string>
#include "istream_line_reader.h"

using namespace std;

int main()
{
    istream_line_reader reader(cin);
    for (istream_line_reader::iterator
             it = reader.begin();
         it != reader.end(); ++it) {
        cout << *it << '\n';
    }
}
