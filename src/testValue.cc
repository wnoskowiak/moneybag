#include "moneybag.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    Value v1(105);
    Value v2(45);
    Value v3(v2);
    Value v4 = v1;
    assert(v1 != v2);
    assert(!(v1 > v4));
    assert(v1 == v4);
    assert(v1 < 200);
    assert(v3 == 45);
    string s(v3);
    assert(s == "45");
    // cout << s;
}