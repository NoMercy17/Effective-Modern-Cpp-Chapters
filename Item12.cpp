#include <iostream>
#include <memory>

using namespace std;

class Base {
public:
    Base(){
        cout << "Base CONST" << endl;
    }
    virtual void doWork() &{ // base class virtual function
        std::cout << "Base::doWork()\n";
    }

    // virtual void doWork() &; this version applies only when *this is lvalue
    // virtual void doWork() &&; this version applies when *this is rvalue
    
    // we check about what object are we working on, if its rvalue constructed or lvalue
    // similar to when we use const with our arguments that specify the state of the object as parameter
    
};

class Derived : public Base {
public:
    Derived(){
        cout << "Derive CONST" << endl;
    }
    void doWork() & override { // overrides Base::doWork
        std::cout << "Derived::doWork()\n";
    }
};

int main() {
    // base class pointer to derived class object
    std::unique_ptr<Base> pBase = std::make_unique<Derived>(); 

    pBase->doWork();




    return 0;
}
