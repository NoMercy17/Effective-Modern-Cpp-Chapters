#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
using namespace std;



// *A parameter, even T&& is an lvalue, eventho its type is rvalue-referenced-to...*

// std::move doesn't move anything, PERFORMS AN UNCONDITIONAL CAST, its argument to RVALUE
// std::forward doesn't forward anything, PERFORMS A CAST only if a condition is met

template<typename T>
decltype(auto) move(T&& param) {
    // remove_ref is a safeguard so that even if the type of T would be a ref, int&, T&&
    // would become a rvalue
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
    // basically a cast...
}

// std::move takes a reference to the object (universal ref) and returns a ref to the same object



// Since text is const, std::move(text) is equal to 
// const std::string&&, which cannot use std::string's move constructor;
// value is initialized by copying instead. Drop const to allow the move.
class Annotation {
public:
    explicit Annotation(const std::string text)
        : value(std::move(text)) {}

private:
    std::string value;
};



int main(){



    return 0;
}
