#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line;
    for (;;) {
        getline(cin, line);
        if (!cin) {
            break;
        }
        cout << line << '\n';
    }
}
