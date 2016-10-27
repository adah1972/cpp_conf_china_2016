#include <cstdio>
#include <string>
#include <nvwa/file_line_reader.h>

using namespace std;
using namespace nvwa;

int main()
{
    string line;
    for (auto& cline : file_line_reader(stdin)) {
        line.assign(cline);
        puts(line.c_str());
    }
}
