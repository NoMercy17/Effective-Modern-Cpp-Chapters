#include <iostream>
using namespace std;


// use std::move on rvalue ref and std::forward on universal ref

// Never apply std::move or std::forward to local objects if they would
// otherwise be eligible for the return value optimization
// (except when you’re passing it to a function and you know you won’t be using the variable any longer)

class Widget{
    public:
        Widget(Widget&& rhs) : name(std::move(rhs.name)), p(std::move(rhs.p)) {}
        //  rvalue references should be unconditionally cast to rvalues 
    
    private:
        std::string name;
        std::shared_ptr<OurDataStructure> p;
}


class Widget2 {
    public:
        template<typename T>
        void setName(T&& newName){ 
            name = std::forward<T>(newName); 
        }

        
}

/*
the fact is that replacing a template taking a
universal reference with a pair of functions overloaded on lvalue
references and rvalue references is likely to incur a runtime cost
*/

class Widget {
public:
    void setName(const std::string& newName){
        name = newName; 
    }

    void setName(std::string&& newName){
        name = std::move(newName);
    }
};


template<typename T>
void setSignText(T&& text){
    sign.setText(text);
    
    auto now = std::chrono::system_clock::now();
    signHistory.add(now, std::forward<T>(text)); // conditionally cast to rvalue
    // we want to apply the std::move / std::forward on only the final use of the reference

}
 
// there is nothing to be lost(much to be gained possibly) by applying std::move
// to rvalue references being returned by functions that return by value


// we cast lhs to be an rvalue in the return so that it will be moved into the return of the func
Matrix operator+(Matrix&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return std::move(lhs); 
    // if we omit the std::move, the lhs will be copied into the return of the func
    // we want to return by moving here (if the matrix does support it), being more efficient
    // we actually return a reference to w
}

// same idea for the universal references

template<typename T> Fraction
reduceAndCopy(T&& frac) {
    frac.reduce();
    return std::forward<T>(frac);
}
// If the call to std::forward were omitted, frac would be
// unconditionally copied into reduceAndCopy’s return value.



// we do not need to optimize so that we turn any copy into a move
// given that we are aware of the RTO (return value optimization)
// every decent compiler will employ the RTO

// 1. if the type of the local object is the same as that returned by the function
// 2. the local object is what’s being returned


// its ok if:

Widget makeWidget(){ // 'copying version'
    Widget w;
    return w; // 'copy' w into return value
}

// if the conditions for the RVO are met, but compilers choose not to perform
// copy elision, the object being returned must be treated as an rvalue

// 


int main() 
{
    cout << "Hello, World!";
    return 0;
}
