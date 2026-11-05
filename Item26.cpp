#include <iostream>
#include <multiset>
#include <string>
#include <chrono>
using namespace std;


// initial code snipper
std::multiset<std::string> names;
void logAndAdd(const std::string& name){
    auto now = std::chrono::system_clock::now();

    log(now, "logAndAdd");

    names.emplace(name);
}

class Person {
public:
    template<typename T>
    explicit Person(T&& n) : name(std::forward<T>(n)) {} // perfect forwarding

    explicit Person(int idx) : name(nameFromIdx(idx)) {} // int ctor

    Person(const Person& rhs); // compiler generated
    Person(Person&& rhs); // compiler generated

private: std::string name
};

int main(){

    // three potential calls:
    std::string petName{"Darla"};

    logAndAdd(petName); // pass lvalue std::string, the .emplace will copy it into the names multiset 

    logAndAdd(std::string("Persephone")); // pass rvalue std::string, its value 'could' be moved,
    // but since name is lvalue
    logAndAdd("Patty Dog"); // pass string literal, name is still copied into names
    // even tho we have a string literal, emplace can use the string literal to creade the
    // std::string directly into the multiset, we are paying for a copy yet makes no reason
    // to pay for even a move, less a copy!



    // better approach
    template<typename T>
    void logAndAdd(T&& name){
        auto now = std::chrono::system_clock::now();
        log(now, "logAndAdd");
        names.emplace(std::forward<t>(name));   
    
    }

    logAndAdd(petName); // as before, copy lvalue into multiset
    logAndAdd(std::string("Persephone")); // move rvalue instead of copying
    logAndAdd("Patty Dog"); // create std::string directly into multiset instead of copying a temp string


    // if we have an overloaded logAndAdd func:
    void logAndAdd(int idx) {
        auto now = std::chrono::system_clock::now();
        log(now, "logAndAdd");
        names.emplace(nameFromIdx(idx));
    } 

    // !! Functions taking universal references are the greediest functions !!
    // They instantiate to create exact matches for almost any type of argument

    //  This is why combining overloading and universal references is
    //  almost always a bad idea


    //solution for this overloading would be working with a class(person)


    Person p("Nancy");

    auto cloneOfP(p); //tries creating a person from p but it uses the perfect forwarding...
    //  initialize Person’s std::string data member with a Person object 


    // p could be passed to either the copy constructor or the instantiated
    // template. Calling the copy constructor would require adding const to p to matchthe copy
    // constructor's params type

    Person p2("Nancy");
    auto cloneOfP2(p2);
    
    return 0;
}



