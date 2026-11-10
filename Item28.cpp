#include <iostream>

// Reference collapsing

// regarding lvalue and rvalue encoding means:
// the T parameter will encode wheter the argument is lvalue or rvalue
template<typename T>
void func(T&& param) {

}
// lvalue are deduced as T&, rvalue are deduced as T
// This is known as "universal reference" or "forwarding reference" in C++11 and later

//  !REFERENCES TO REFERENCES ARE ILLEGAL!

// int x;
// auto& & rx = x;


// the compiler is doing that when we pass that lvalue, since T is Widget&, the param is
// void func(Widget& &&param) reference to a reference which should NOT BE OK!

// when compilers generate references to references, reference collapsing dictates what happens next

// 4 types of combinations: lvalue to lvalue ...

// Reference collapse to a single reference according to the rule: 
// "If either reference is lvalue, the result is lvalue. If neither is lvalue, the result is rvalue reference"


// Reference collapsing, key part of std::forward
template<typename T>
void f(T&& fParam)
{

    someFunc(std::forward<T>(fParam));
}

// the std::forward could be implemented like this:

template<typename T>
T&& forward(typename remove_reference<T>::type& param){ // similar to namespace std implementation
    return static_cast<T&&>(param);
}

// for lvalue the forward implementation yields: T = Widget&

Widget& && forward(typename remove_reference<Widget&>::type& param){ // the remove_reference<Widget&>::type yiels Wdiget from that
    return static_cast<Widget& &&>(param);
}

// after reference collapsing we get: 
Widget& forward(Widget& param){ 
    return static_cast<Widget&>(param);
}

// for rvalue the forward implementation yields: T = Widget, substituting Widget from T we get:
Widget&& forward(typename remove_reference<Widget>::type& param){
    return static_cast<Widget&&>(param);
}

// that yields

Widget&& forward(Widget& param){ 
    return static_cast<Widget&&>(param); 
}

// Reference collapsing occur in 4 contexts:
// 1. Template instantiation
// 2. 'auto' type generation

/*
Widget w;

auto&& w1 = w; initialize w1 with lvalue -> type for auto is Widget&

Widget& &&w1 = w; after reference collapsing we get 

Widget& w1 = w; w1 = lvalue ref

---------------------------


auto&& w2 = widgetFactory(); // we initialize w2 with rvalue -> type for auto is Widget

Widget&& w2 = widgetFactory(); -> w2 rvalue ref

*/

int main(){
    Widget w; // lvalue
    Widget widgetFactory(); // returns rvalue

    func(w); // T deduced to be Widget&, param is Widget&
    func(widgetFactory()); // T deduced to be Widget, param is Widget&&

    return 0;
}
