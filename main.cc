#include <iostream>
#include "complex.h"

using namespace std;

template <typename T>
void print(T input)
{
    cout << input << '\n';
}

int main()
{
    auto c1 = Complex<double>(20.0000, 309);

    print(c1);
    c1.print();
    c1.print_polar();

    return 0;
}