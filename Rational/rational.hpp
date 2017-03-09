// COPYRIGHT (C) 2017 Nicholas Gallimore (nfg3) All rights reserved.
//
// rational.hpp: Definition of rational class and its interace.

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <stdlib.h>


// Mathematical helper functions.
//
// NOTE: These are defined in rational.cpp.
int gcd(int, int);
int lcm(int, int);


// Represents a rational number. The rational numbers are the set of
// numbers that can be represented as the quotient of two integers.
class Rational
{
    
public:
    // Returns the numerator.
    int num() const { return numerator; };

    // Returns the denominator
    int den() const { return denominator; };
    
    // Default constructor
    Rational();
    
    // Constructor that takes an integer value
    Rational(int);
    
    // Constructor that takes a pair of integer values for numerator and denominator
    Rational(int, int);
    
    // Equality operators
    bool operator==(Rational&);
    bool operator!=(Rational&);
    bool operator<(Rational&);
    bool operator>(Rational&);
    bool operator>=(Rational&);
    bool operator<=(Rational&);
    
    // Arithmetic operators
    Rational& operator+(Rational);
    Rational& operator-(Rational);
    Rational& operator*(Rational);
    Rational& operator/(Rational);

private:
    int numerator, denominator;
};

// Stream operators
std::ostream& operator<<(std::ostream&, Rational);
std::istream& operator>>(std::istream&, Rational&);

#endif
