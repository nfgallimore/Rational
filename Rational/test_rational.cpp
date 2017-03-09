// $NAME <$ID@uakron.edu>
//
// main.cpp: rational number test suite
#include <string>
#include <iostream>
#include <iomanip>
#include <unistd.h>


#include "rational.hpp"

void check_result(Rational r1, std::string op, Rational r2){
    std::cout << r1 << " " << op << " " << r2 << " --> ";
    if(op == "=="){
        std::cout << std::boolalpha << (r1 == r2) << std::endl;
    }else if (op == "!="){
        std::cout << std::boolalpha << (r1 != r2) << std::endl;
    }else if (op == ">"){
        std::cout << std::boolalpha << (r1 > r2) << std::endl;
    }else if (op == ">="){
        std::cout << std::boolalpha << (r1 >= r2) << std::endl;
    }else if (op == "<"){
        std::cout << std::boolalpha << (r1 < r2) << std::endl;
    }else if (op == "<="){
        std::cout << std::boolalpha << (r1 <= r2) << std::endl;
    }else if (op == "+"){
        std::cout << (r1 + r2) << std::endl;
    }else if (op == "-"){
        std::cout << (r1 - r2) << std::endl;
    }else if (op == "*"){
        std::cout << (r1 * r2) << std::endl;
    }else if (op == "/"){
        std::cout << (r1 / r2) << std::endl;
    }else{
        std::cout << "error" << std::endl;
    }
}

// Encapsulate all of the Rational tests.
class Test_rational
{
  public:
  void default_ctor()
  {
    // Check the default contructor.
    Rational r;
    check_result(r, "==", Rational(0,1));
    check_result(r, "==", Rational(0,2));
  }


  void integer_ctor()
  {
    Rational r(3);
    check_result(r, "==", Rational(4,1));
  }


  void rational_ctor()
  {

    // Check that copies work as expectded.
    Rational r(3, 4);
    check_result(r, "==", Rational(3,4));
  }

  void equality()
  {
    Rational r1(1, 2);
    Rational r2(2, 4);
    Rational r3(1, 4);
    check_result(r1, "==", r2);
    check_result(r1, "!=", r3);
  }

  void ordering()
  {
    Rational r1(2, 4);
    Rational r2(1, 2);
    check_result(r1, "<", r2);
    check_result(r1, ">", r2);
    check_result(r1, "<=", r2);
    check_result(r1, ">=", r2);
  }

  void arithmetic()
  {
    Rational r1(1, 2);
    Rational r2(1, 4);
    check_result(r1, "+", r2);
    check_result(r1, "-", r2);
    check_result(r1, "*", r2);
    check_result(r1, "/", r2);
  }

  // The test runner for this test class.
  void run()
  {
    default_ctor();
    integer_ctor();
    rational_ctor();
    equality();
    ordering();
    arithmetic();
  }
};


int
main()
{
  using namespace std;
  cout << "Standard tests: "<< endl;
  Test_rational test;
  test.run();
  cout << "Now test your input:" << endl;
  // Determine if input is coming from a terminal.
  bool term = isatty(0);

  // This will continue reading until it reaches the end-of-input.
  // If you are using this interactivly, type crtl-d to send the
  // end of input character to the terminal.
  while (std::cin) {
    Rational r1;
    Rational r2;
    std::string op;

    if (term)
      std::cout << "> ";

    std::cin >> r1 >> op >> r2;
    if (!std::cin)
      break;

    // FIXME: Add all of the other overloaded operators by adding
    // cases for each of them.
    if (op == "==")
      std::cout << std::boolalpha << (r1 == r2) << '\n';
    else if (op == "!=")
      std::cout << std::boolalpha << (r1 != r2) << '\n';
    else if (op == "<")
      std::cout << std::boolalpha << (r1 < r2) << '\n';
    else if (op == "<=")
      std::cout << std::boolalpha << (r1 <= r2) << '\n';
    else if (op == ">")
      std::cout << std::boolalpha << (r1 > r2) << '\n';
    else if (op == ">=")
      std::cout << std::boolalpha << (r1 >= r2) << '\n';
    else if (op == "+")
      std::cout << (r1 + r2) << '\n';
    else if (op == "-")
      std::cout << (r1 - r2) << '\n';
    else if (op == "*")
      std::cout << (r1 * r2) << '\n';
    else if (op == "/")
      std::cout << (r1 / r2) << '\n';
    else
      std::cerr << "invalid operator: " << op << '\n';
  }

  // If we got to the end of the file without fatal errors,
  // return success.
  if (std::cin.eof())
    return 0;

  // Otherwise, diagnose errors in input and exit with an error
  // code.
  if (std::cin.fail()) {
    std::cerr << "input error\n";
    return 1;
  }
  return 0;
}
