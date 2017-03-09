// COPYRIGHT (C) 2017 Nicholas Gallimore (nfg3) All rights reserved.
//
// rational.hpp: Definition of rational class and its interace.

#include "rational.hpp"

#include <iostream>


// -------------------------------------------------------------------------- //
// Helper functions

// Compute the GCD (greatest common divider) of two integer values using Euclid's algorithm.
int
gcd(int a, int b)
{
  a = abs(a);   //make them to be positive numbers
  b = abs(b);
  if(a==0 || b==0){ //if one number is 0, always return 1
    return 1;
  }
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}


// Compute the LCM (Least Common Multiple) of two integer values.
int
lcm(int a, int b)
{
  a = abs(a); //make them positive
  b = abs(b);
  if(a == 0 || b == 0){
    throw "Integers can not be zero in calculating Least Common Multiple";
  }
  return (abs(a) / gcd(a, b)) * abs(b);
}


// -------------------------------------------------------------------------- //
// Rational implementation


//DO NOT CHANGE operators << and >> overloading functions
std::ostream&
operator<<(std::ostream& os, Rational r)
{
  return os << r.num() << '/' << r.den();
}

std::istream&
operator>>(std::istream& is, Rational& r)
{
  // Read the first integer, return on error.
  int p;
  is >> p;
  if (!is)
    return is;

  // Check for the divider. Assuming no spaces.
  if (is.peek() != '/') {
    r = Rational(p);
    return is;
  }
  is.get();

  int q;
  is >> q;
  if (!is)
    return is;
  if (q == 0) {
    is.setstate(std::ios::failbit);
    return is;
  }
  r = Rational(p, q);
  return is;
#if 0
  int p, q;
  char c;
  is >> p >> c >> q;
  if (!is)
    return is;
  // Require that the divider to be a '/'.
  if (c != '/') {
    is.setstate(std::ios::failbit);
    return is;
  }

  // Make sure that we didn't read p/0.

  r = Rational(p, q);
  return is;
#endif
}

Rational::Rational() {
    numerator = 0; denominator = 0;
}

Rational::Rational(int n) {
    numerator = n, denominator = 1;
}

Rational::Rational(int n, int d) {
    numerator = n;
    denominator = d;
}

// num1zero?
// num2zero?
// den1zero?
// den2zero?

// 4 T's / 4 F's
// TTTT
// FFFF

// 3 T's / 1 F
// TTTF
// TTFT
// TFTT
// FTTT

// 2 T's / 2 F's
// TTFF
// FFTT
// TFFT
// FTTF
// FTFT
// TFTF

// 1 T / 3 F's
// TFFF
// FTFF
// FFTF
// FFFT

bool Rational::operator==(Rational& obj) {
    return
    (obj.num() == 0 && num() == 0)
        ? 1
    : (obj.num() == num() && obj.den() == den())
        ? 1
    : (obj.den() == 0 && den() == 0 && (obj.num() != 0 || num() != 0))
        ? throw "Cannot divide non zero value by zero"
    : (obj.den() != 0 && den() != 0)
        ? lcm(obj.den(), den()) / den() * num() == lcm(obj.den(), den()) / obj.den() * obj.num()
        : ((obj.num() / obj.den()) == (num() / den()));
}

bool Rational::operator!=(Rational& obj) {
    return (gcd(obj.denominator, denominator) / denominator * numerator) != (gcd(obj.denominator, denominator) / obj.denominator * obj.numerator);
}

bool Rational::operator<(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? 1 : (gcd(obj.denominator, denominator) / denominator * numerator) < (gcd(obj.denominator, denominator) / obj.denominator * obj.numerator);
}

bool Rational::operator>(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? 1 : (gcd(obj.denominator, denominator) / denominator * numerator)
    > (gcd(obj.denominator, denominator) / obj.denominator * obj.numerator);
}

bool Rational::operator>=(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? 1 : (gcd(obj.denominator, denominator) / denominator * numerator)
    >= (gcd(obj.denominator, denominator) / obj.denominator * obj.numerator);
}
bool Rational::operator<=(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? 1 : (gcd(obj.denominator, denominator) / denominator * numerator)
    <= (gcd(obj.denominator, denominator) / obj.denominator * obj.numerator);
}

// Arithmetic operators
Rational& Rational::operator+(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational(gcd(obj.den(), denominator) / denominator * numerator + (gcd(obj.den(), denominator) / obj.den() * obj.num()), gcd(obj.den(), denominator)));
}

Rational& Rational::operator-(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational(gcd(obj.den(), denominator) / denominator * numerator - (gcd(obj.den(), denominator) / obj.den() * obj.num()), gcd(obj.den(), denominator)));
}
Rational& Rational::operator*(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *new Rational(obj.num() * numerator, obj.den() * denominator);
}
Rational& Rational::operator/(Rational& obj) {
    return (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *new Rational(obj.num() / numerator, obj.den() / denominator);

}
