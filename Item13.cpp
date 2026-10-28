#include <iostream>
#include <vector>
#include <algorithm>

// PREFER CONST ITERATORS OVER ITERATORS

int main(){

    // C++ 11 makes it easier to work with const iterators!
    std::vector<int> values;

    // std::vector<int>::const_iterator
    auto it = std::find(values.cbegin(), values.cend(), 1983);

    values.insert(it, 1983);


    // in C++98 it was harder to achieve that

    typedef std::vector<int>::iterator Iter;
    typedef std::vector<int>::const_iterator ConstIter;


    ConstIter ci =
        std::find(static_cast<ConstIter>(values.begin()),
              static_cast<ConstIter>(values.end()),
              1983);

    //values.insert(static_cast<Iter>(ci), 198); // May not compile;


    return 0;
}


// for old c++ where we do not have the cbegin / cend we can implement it ourselves:

template<typename C>
auto cbegin(const C& container) -> decltype(std::begin(container)) 
{
    // if C = std::vector<int>
    // since the argument type is: const std::vector<int>& invoking the begin on const
    // yields a const iterator 
    return std::begin(container); 
}
