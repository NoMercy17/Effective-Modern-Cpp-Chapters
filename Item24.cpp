#include <iostream>
using namespace std;

// Universal references vs rvalue references

template<typename T>
void f(std::vector<T>&& param); // rvalue reference

template<typename T>
void f(T&& param); // universal reference


// T&& - 2 meanings:
// 1. rvalue reference

// 2. either rvalue or lvalue(T&) reference, they can bind to const/non-const, to
// volatile/non-volatile and even const volatile objects. They can bind to anything
// so we call them
// UNIVERSAL references

// by using the auto keyword, we deduce the type , getting the universal ref
auto** var2 = var1; // var2 -> universal reference!

// if we use this instead:
Widget&& var1 = var2; // var2 is a rvalue reference


// for a reference to be universal, type deduction is neccessary but not sufficient
// we also need a crrect form, must be precisely
// "T&&"

template<typename T>
void f(std::vector<T>&& param); // param is an rvalue reference


// the simple presence of const disqualifies the ref from being universal
template<typename T>
void f(const T&& param); // rvalue ref

// C++ 14 lambda that does smth

auto randomFunc = [](auto&& func, auto&&... params){
//func is a universal reference that can be bound to any callable object, lvalue or
//rvalue. args is zero or more universal references
  
    //...
}


int main(){


    return 0;
}
