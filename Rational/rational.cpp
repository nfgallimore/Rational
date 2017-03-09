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

//bool Rational::operator==(Rational& obj) {
//    return
//    (obj.num() == 0 && num() == 0)
//        ? 1
//    : (obj.num() == num() && obj.den() == den())
//        ? 1
//    : (obj.den() == 0 && den() == 0 && (obj.num() != 0 || num() != 0))
//        ? throw "Cannot divide non zero value by zero"
//    : (obj.den() != 0 && den() != 0)
//        ? lcm(obj.den(), den()) / den() * num() == lcm(obj.den(), den()) / obj.den() * obj.num()
//        : ((obj.num() / obj.den()) == (num() / den()));
//}

bool Rational::operator==(Rational& obj) {
    // both nums 0
    if (obj.num() == 0 && num() == 0) {
        return true;
    }
    // both nums same and both dens same
    else if (obj.num() == num() && obj.den() == den()) {
        return true;
    }
    // if both denominators are 0 and at least one of the numerators is not 0
    else if (obj.den() == 0 && den() == 0 && (obj.num() != 0 || num() != 0)) {
        throw "Non zero numerator with zero denominator";
    }
    if (obj.den() == den()) {
        return (num() == obj.num());
    }
    // both denominators have values
    else if (obj.den() != 0 && den() != 0) {
        double commonMult = (double)lcm(obj.den(), den())
        , commonDiv = ((double)gcd(obj.den(), den()))
        , commonTerm = ((commonMult > commonDiv) && (commonDiv != 1)) ? commonDiv : commonMult
        
        // using memory for clarity
        , factor1 = commonTerm / den()
        , factor2 = commonTerm / obj.den()
        
        , numerator1 = factor1 * num()
        , numerator2 = factor2 * obj.num();
        
        return numerator1 == numerator2;
        
    }
    // must be case 0/0 == 0/0
    else return true;
}



bool Rational::operator!=(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? ((double)gcd(obj.den(), den()) / den() * num()) != ((double)gcd(obj.den(), den()) / obj.den() * obj.num())
    : ((double)lcm(obj.den(), den()) / den() * num()) != ((double)lcm(obj.den(), den()) / obj.den() * obj.num());
}

bool Rational::operator<(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? ((double)gcd(obj.den(), den()) / den() * num()) < ((double)gcd(obj.den(), den()) / obj.den() * obj.num())
    : ((double)lcm(obj.den(), den()) / den() * num()) < ((double)lcm(obj.den(), den()) / obj.den() * obj.num());
}

bool Rational::operator>(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? ((double)gcd(obj.den(), den()) / den() * num()) > ((double)gcd(obj.den(), den()) / obj.den() * obj.num())
    : ((double)lcm(obj.den(), den()) / den() * num()) > ((double)lcm(obj.den(), den()) / obj.den() * obj.num());
}

bool Rational::operator>=(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? ((double)gcd(obj.den(), den()) / den() * num()) >= ((double)gcd(obj.den(), den()) / obj.den() * obj.num())
    : ((double)lcm(obj.den(), den()) / den() * num()) >= ((double)lcm(obj.den(), den()) / obj.den() * obj.num());
}
bool Rational::operator<=(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? ((double)gcd(obj.den(), den()) / den() * num()) <= ((double)gcd(obj.den(), den()) / obj.den() * obj.num())
    : ((double)lcm(obj.den(), den()) / den() * num()) <= ((double)lcm(obj.den(), den()) / obj.den() * obj.num());
}

// Arithmetic operators
Rational& Rational::operator+(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational((double)gcd(obj.den(), den()) / den() * num() + ((double)gcd(obj.den(), den()) / obj.den() * obj.num()), (double)gcd(obj.den(), den())))
    : (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational((double)lcm(obj.den(), den()) / den() * num() + ((double)lcm(obj.den(), den()) / obj.den() * obj.num()), (double)gcd(obj.den(), den())));
}

Rational& Rational::operator-(Rational& obj) {
    return ((double)gcd(obj.den(), den()) != 1)
    ? (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational((double)gcd(obj.den(), den()) / den() * num() - ((double)gcd(obj.den(), den()) / obj.den() * obj.num()), (double)gcd(obj.den(), den())))
    : (obj.num() == 0 && num() == 0) ? *new Rational(0, 0) : *(new Rational((double)lcm(obj.den(), den()) / den() * num() - ((double)lcm(obj.den(), den()) / obj.den() * obj.num()), (double)gcd(obj.den(), den())));
}
Rational& Rational::operator*(Rational& obj) {
    int gcd1 = (double)gcd(obj.num(), obj.den()), gcd2 = (double)gcd(num(), den());
    return (obj.num() == 0 && num() == 0)
        ? *new Rational(0, 0)
        : (gcd1 != 1) && (gcd2 != 1)
            ? *new Rational(gcd1 * gcd2, 1)
            : *new Rational(obj.num() * num(), obj.den() * den());
}
Rational& Rational::operator/(Rational& obj) {
    int gcd1 = (double)gcd(num(), den()), gcd2 = (double)gcd(obj.num(), obj.den());
    return (obj.num() == 0 && num() == 0)
        ? *new Rational(0, 0)
        : (gcd1 != 1) && (gcd2 != 1)
            ? *new Rational(gcd1 / gcd2, 1)
            : *new Rational(num() / obj.num(), den() / obj.den());
}
