#pragma once

#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template <typename T>
class Complex
{
private:
    T re;
    T im;

public:
    // Constructor
    Complex<T>(const T &re, const T &im);

    // Factory constructor
    static Complex<T> from_polar(const T &mod, const T &arg);

    // Getter
    T get_re() const;
    T get_im() const;
    tuple<T, T> get_cartesian() const;

    T get_mod() const;
    T get_arg() const;
    tuple<T, T> get_polar() const;

    // Setter
    void set_re(const T &re);
    void set_im(const T &im);
    void set_mod(const T &mod);
    void set_arg(const T &arg);

    // Static methods
    static tuple<T, T> to_cartesian(const T &mod, const T &arg);

    // Print function with precision
    void print(const unsigned int &precision = 2) const;

    // Print polar form
    void print_polar(const unsigned int &precision = 2) const;

    // Operator overloading
    friend ostream &
    operator<<(ostream &os, const Complex<T> complex)
    {
        os << fixed
           << setprecision(2)
           << complex.get_re()
           << setiosflags(ios::showpos)
           << complex.get_im()
           << "i"
           << resetiosflags(ios::showpos)
           << resetiosflags(ios::fixed);
        return os;
    }

    Complex<T> operator+(const Complex<T> &rhs) const;
    Complex<T> &operator+=(const Complex<T> &rhs);

    Complex<T> operator-(const Complex<T> &rhs) const;
    Complex<T> &operator-=(const Complex<T> &rhs);

    Complex<T> operator*(const Complex<T> &rhs) const;
    Complex<T> &operator*=(const Complex<T> &rhs);

    Complex<T> operator/(const Complex<T> &rhs) const;
    Complex<T> &operator/=(const Complex<T> &rhs);

    // Additional operations
    Complex<T> power(const double &exponent) const;

    vector<Complex<T>> root(const unsigned int &index = 2) const;

    bool equal_to(const Complex<T> &other) const;

    Complex<T> conjugate() const;
};

#include "complex.tpp"