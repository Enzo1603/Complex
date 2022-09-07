#include <cmath>
#include <tuple>
#include <vector>

// TODO: Write Tests

// Constructor
template <typename T>
Complex<T>::Complex(const T &re, const T &im)
{
    this->set_re(re);
    this->set_im(im);
}

// Factory constructor
template <typename T>
Complex<T> Complex<T>::from_polar(const T &mod, const T &arg)
{
    auto [re, im] = Complex<T>::to_cartesian(mod, arg);
    return Complex<T>(re, im);
}

// Getter
template <typename T>
T Complex<T>::get_re() const
{
    return this->re;
}

template <typename T>
T Complex<T>::get_im() const
{
    return this->im;
}

template <typename T>
tuple<T, T> Complex<T>::get_cartesian() const
{
    return make_tuple(this->get_re(), this->get_im());
}

template <typename T>
T Complex<T>::get_mod() const
{
    T modulus = pow(pow(this->get_re(), 2) + pow(this->get_im(), 2), 0.5);
    return modulus;
}

template <typename T>
T Complex<T>::get_arg() const
{
    T argument = acos(this->get_re() / this->get_mod());

    if (this->get_re() < 0 && this->get_im() < 0)
    {
        argument += M_PI / 2;
    }
    else if (this->get_re() == 0 && this->get_im() < 0)
    {
        argument += M_PI;
    }
    else if (this->get_re() > 0 && this->get_im() < 0)
    {
        argument += 1.5 * M_PI;
    }
    return argument;
}

template <typename T>
tuple<T, T> Complex<T>::get_polar() const
{
    return make_tuple(this->get_mod(), this->get_arg());
}

// Setter
template <typename T>
void Complex<T>::set_re(const T &re)
{
    this->re = re;
}

template <typename T>
void Complex<T>::set_im(const T &im)
{
    this->im = im;
}

template <typename T>
void Complex<T>::set_mod(const T &mod)
{
    T argument = this->get_arg();
    auto [re, im] = this->to_cartesian(mod, argument);
    this->set_re(re);
    this->set_im(im);
}

template <typename T>
void Complex<T>::set_arg(const T &arg)
{
    T modulus = this->get_mod();
    auto [re, im] = this->to_cartesian(modulus, arg);
    this->set_re(re);
    this->set_im(im);
}

// Static methods
template <typename T>
tuple<T, T> Complex<T>::to_cartesian(const T &mod, const T &arg)
{
    T re = mod * cos(arg);
    T im = mod * sin(arg);
    return make_tuple(re, im);
}

// Print function with precision
template <typename T>
void Complex<T>::print(const unsigned int &precision) const
{
    cout << fixed
         << setprecision(precision)
         << this->get_re()
         << setiosflags(ios::showpos)
         << this->get_im()
         << "i\n"
         << resetiosflags(ios::showpos)
         << resetiosflags(ios::fixed);
}

// Print polar form
template <typename T>
void Complex<T>::print_polar(const unsigned int &precision) const
{
    cout << fixed
         << setprecision(precision)
         << this->get_mod()
         << " cis("
         << this->get_arg() / M_PI
         << "π)\n"
         << resetiosflags(ios::showpos)
         << resetiosflags(ios::fixed);
}

// Operator overloading

template <typename T>
Complex<T> Complex<T>::operator+(const Complex<T> &rhs) const
{
    T new_re = this->get_re() + rhs.get_re();
    T new_im = this->get_im() + rhs.get_im();
    return Complex<T>(new_re, new_im);
}

template <typename T>
Complex<T> &Complex<T>::operator+=(const Complex<T> &rhs)
{
    this->set_re(this->get_re() + rhs.get_re());
    this->set_im(this->get_im() + rhs.get_im());
    return *this;
}

template <typename T>
Complex<T> Complex<T>::operator-(const Complex<T> &rhs) const
{
    T new_re = this->get_re() - rhs.get_re();
    T new_im = this->get_im() - rhs.get_im();
    return Complex<T>(new_re, new_im);
}

template <typename T>
Complex<T> &Complex<T>::operator-=(const Complex<T> &rhs)
{
    this->set_re(this->get_re() - rhs.get_re());
    this->set_im(this->get_im() - rhs.get_im());
    return *this;
}

template <typename T>
Complex<T> Complex<T>::operator*(const Complex<T> &rhs) const
{
    T modulus1 = this->get_mod();
    T argument1 = this->get_arg();

    T modulus2 = rhs.get_mod();
    T argument2 = rhs.get_arg();

    T modulus = modulus1 * modulus2;
    T argument = argument1 + argument2;
    return Complex<T>::from_polar(modulus, argument);
}

template <typename T>
Complex<T> &Complex<T>::operator*=(const Complex<T> &rhs)
{
    this->set_mod(this->get_mod() * rhs.get_mod());
    this->set_arg(this->get_arg() + rhs.get_arg());
    return *this;
}

template <typename T>
Complex<T> Complex<T>::operator/(const Complex<T> &rhs) const
{
    T modulus1 = this->get_mod();
    T argument1 = this->get_arg();

    T modulus2 = rhs.get_mod();
    T argument2 = rhs.get_arg();

    T modulus = modulus1 / modulus2;
    T argument = argument1 - argument2;
}

template <typename T>
Complex<T> &Complex<T>::operator/=(const Complex<T> &rhs)
{
    this->set_mod(this->get_mod() / rhs.get_mod());
    this->set_arg(this->get_arg() + rhs.get_arg());
    return *this;
}

// Additional operations
template <typename T>
Complex<T> Complex<T>::power(const double &exponent) const
{
    T modulus = this->get_mod();
    T argument = this->get_arg();

    auto result_modulus = pow(modulus, exponent);
    T result_argument = argument * exponent;

    return Complex<T>::from_polar(result_modulus, result_argument);
}

template <typename T>
vector<Complex<T>> Complex<T>::root(const unsigned int &index) const
{
    vector<Complex<T>> results{};
    auto first = this->power(1.0 / index);
    results.push_back(first);

    T modulus = first.get_mod();
    T argument = first.get_arg();
    auto k = 2 * M_PI / index;
    for (unsigned int i = 1; i < index; ++i)
    {
        auto complex = Complex<T>::from_polar(modulus, argument + i * k);
        results.push_back(complex);
    }

    return results;
}

template <typename T>
bool Complex<T>::equal_to(const Complex<T> &other) const
{
    if (this->get_re() != other.get_re())
    {
        return false;
    }
    if (this->get_im() != other.get_im())
    {
        return false;
    }
    return true;
}

template <typename T>
Complex<T> Complex<T>::conjugate() const
{
    T real = this->get_re();
    T imag = this->get_im();
    return Complex<T>(real, imag);
}
