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

double
simplify(int a, int b) {
    double div = gcd(a, b);
    if (a == 0 || b == 0) return 1;
    return (div != 1) ? div : lcm(a, b);
}

Rational&
simplify(Rational& obj) {
    double factor = simplify(obj.num(), obj.den());
    return * new Rational(obj.num() / factor, obj.den() / factor);
}
// -------------------------------------------------------------------------- //
// Rational implementation


// operators << and >> overloading functions
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


// -------------------------------------------------------------------------- //
// Constructors


// Default construcotr
Rational::Rational()
{
    numerator = 0; denominator = 0;
}

// Integer constructor
Rational::Rational(int n)
{
    numerator = n, denominator = 1;
}

// Fraction constructor
Rational::Rational(int n, int d)
{
    // if a numerator with non zero value is being divided by 0
    if (n != 0 && d == 0) throw "Does not exist: Cannot divide non zero value by zero";

    numerator = n;
    denominator = d;
}


// -------------------------------------------------------------------------- //
// Equality Operators


// Equality operand
bool Rational::operator==(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return true
    (obj.num() == 0 && num() == 0) ? 1
    
    // if both numerators are the same and both denominators are the same return true
    : (obj.num() == num() && obj.den() == den()) ? 1

    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() == obj.num())
       
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() == commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 == 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 1;
}

// Inequality operand
bool Rational::operator!=(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return false
    (obj.num() == 0 && num() == 0) ? 0
    
    // if both numerators are the same and both denominators are the same return false
    : (obj.num() == num() && obj.den() == den()) ? 0
    
    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() != obj.num())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() != commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 != 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 0;
}

// Less than operand
bool Rational::operator<(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return false
    (obj.num() == 0 && num() == 0) ? 0
    
    // if both numerators are the same and both denominators are the same return false
    : (obj.num() == num() && obj.den() == den()) ? 0
    
    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() < obj.num())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() < commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 < 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 0;
}

// Greater than operand
bool Rational::operator>(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return false
    (obj.num() == 0 && num() == 0) ? 0
    
    // if both numerators are the same and both denominators are the same return false
    : (obj.num() == num() && obj.den() == den()) ? 0
    
    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() > obj.num())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() > commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 > 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 0;
}

// Greater than or equal to operand
bool Rational::operator>=(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return true
    (obj.num() == 0 && num() == 0) ? 1
    
    // if both numerators are the same and both denominators are the same return true
    : (obj.num() == num() && obj.den() == den()) ? 1
    
    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() >= obj.num())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() >= commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 >= 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 1;
}

// Less than or equal to operand
bool Rational::operator<=(Rational& obj)
{
    // finds lowest of gcd and lcm where gcd cannot equal 1
    double commonTerm = simplify(obj.den(), den());
    
    return
    
    // if both numerators are zero return true
    (obj.num() == 0 && num() == 0) ? 1
    
    // if both numerators are the same and both denominators are the same return true
    : (obj.num() == num() && obj.den() == den()) ? 1
    
    // if they already have same denominators just compare numerators
    : (obj.den() == den()) ? (num() <= obj.num())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to compare numerators
    : (obj.den() != 0 && den() != 0) ? commonTerm / den() * num() <= commonTerm / obj.den() * obj.num()
    
    // Must be case 0/0 <= 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : 1;
}


// -------------------------------------------------------------------------- //
// Arithmetic Operators


// Addition operand
Rational& Rational::operator+(Rational& obj)
{
    return
        
    // if both numerators are zero return zero
    (obj.num() == 0 && num() == 0) ? *new Rational()
    
    // if both numerators are the same and both denominators are the same return true
    : (obj.num() == num() && obj.den() == den()) ? *new Rational(num() + num(), den()) // adds num() twice instead of multiplying by 2 (faster?) note* => num == obj.num()
    
    // if they already have same denominators just add numerators
    : (obj.den() == den()) ? *new Rational(num() + obj.num(), den())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to add numerators
    : (obj.den() != 0 && den() != 0) ? simplify(*new Rational((num() * obj.den() + obj.num() * den()), den() * obj.den()))
    
    // Must be case 0/0 + 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : *new Rational(); // returns 0/0
}

// Subtraction operand
Rational& Rational::operator-(Rational& obj)
{
    return
    
    // if both numerators are zero return zero
    (obj.num() == 0 && num() == 0) ? *new Rational() // returns 0/0
    
    // if both numerators are the same and both denominators are the same
    : (obj.num() == num() && obj.den() == den()) ? *new Rational() // returns 0/0

    // if they already have same denominators just subtract numerators
    : (obj.den() == den()) ? *new Rational(num() - obj.num(), den())
    
    // If denominators non-zero divide lowest commonTerm by denominator to get scale factor then multiply scale factor by numerator for each to add numerators
    : (obj.den() != 0 && den() != 0) ? simplify(*new Rational((num() * obj.den() - obj.num() * den()), den() * obj.den()))
    
    // Must be case 0/0 - 0/0 but the input operator does not support dividing by 0 (e.g., 0/0) so this is extraneous
    : *new Rational(); // returns 0/0
}

// Multiplication operand
Rational& Rational::operator*(Rational& obj)
{
    return
    
    // if either numerators are zero return zero
    (obj.num() == 0 || num() == 0 || obj.den() == 0 || den() == 0) ? *new Rational() // returns 0/0
    
    // multiply common term'd numerator1 by common term'd numerator 2; same to denominators
    : *new Rational(num() * obj.num(), den() * obj.den());
}

// Division operand
Rational& Rational::operator/(Rational& obj)
{
    return
    
    // if either numerators are zero return zero
    (obj.num() == 0 || num() == 0 || obj.den() == 0 || den() == 0) ? *new Rational() // is implied that if any denom == 0 then numr also == 0 by constructor def
    
    // n1/d1 / n2/d2 == n1/d1 * d2/n1
    : simplify(*new Rational(num() * obj.den(), den() * obj.num()));
}
