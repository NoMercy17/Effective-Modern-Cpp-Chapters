#include <iostream>
#include <type_traits>
#include <set>
using namespace std;
 
// Alternatives to overloading on universal references (Item 26 problems)
 
// PASS BY T&
//  -  giving up some efficiency to keep things simple might be a more attractive trade
//  -  no support for perfect-forwarding
// PASS BY VALUE
//  -  consider passing objects by value when you know you’ll copy them, ex:
//  -  no support for perfect-forwarding
 
class Person{
    public:
        explicit Person(std::string n) : name(std::move(n)) {} // we replace the T&& ctor
        explicit Person(int idx) : name(nameFromIdx(idx)) {}
 
    private:
        std::string name;
}
 
// TAG DISPATCH
//  - if we do not want to give up universal ref and we do not want to give up overloading?
 
//  -  A universal reference parameter generally provides an exact match for whatever’s passed in, but if the universal reference is
// part of a parameter list containing other parameters that are not universal
// references, sufficiently poor matches on the non-universal reference
// parameters can knock an overload with a universal reference out of the running
std::multiset<std::string> names;
template<typename T>
void logAndAdd(T&& name){
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
 
    names.emplace(std::forward<T>(name));
}
 
// instead of adding the overload (getting to Item26 problems) we'll implement the
// logAnddAdd function to delegate to 2 others
 
template<typename T>
void logAndAdd(T&& name){
    // logAndAddImpl(std::forward<T>(name), std::is_integral<T>());
    // small issue because the is_integral deduced type will be an lvalue reference,
    // so it will be false for any lvalue argument
    logAndAddImpl(std::forward<T>(name), std::is_integral<typename std::reference_t<T>>());
    // proper tag object to be created
}
 
// now for the case when std::is_integral is false
template<typename T>
void logAndAddImpl(T&& name, std::false_type){
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
 
    names.emplace(std::forward<T>(name));
}
// when std::is_integral true
 
void logAndAddImpl(int idx, std::true_type){
    logAndAdd(nameFromIdx(idx)); // as in Item26
}
 
// CONSTRAINING TEMPLATES THAT TAKE UNIVERSAL REFERENCES
 
// a technique one that lets you rachet down the conditions under which the function template
// that the universal reference is part of is permitted to be employed.
//    -- std::enable_if  -- a way to force compilers to behave as if the template didn't exist
// template are "enabled" by default, but a template using "enable_if" are said "disabled"
// if they do not meet the condition
 
// ex: we want to enable Person perfect-forwarding ctor only if the type isn t a Person
class Person{
    public:
        template<typename T, typename = typename std::enable_if<condition>::type>
        // The condition we want to specify is that T isn’t Person, it should be enabled only if T is a type OTHER than Person
        // keep in mind that  type deduced for a universal reference initialized with an
            // lvalue is always an lvalue reference (Person& type)
            // so we get Person == Person&, always false
 
        // we want to strip the const/volatile and whether its a reference -> std::decay<T>::type  type trait
        template<
            typename T,
            typename = typename std::enable_if<
                !std::is_same<Person, typename std::decay<T>::type>::value
            >::type
        >
        explicit Person(T&& n) : name(std::forward<T>(n)){}
 
 
}
 
 
// one last issue, a class derived from Person
class SpecialPerson: public Person {
    public:
        SpecialPerson(const SpecialPerson& rhs): Person(rhs) { }
        // copy ctor calls base class forwarding ctor, when passing SpecialPerson,
        // since its not the same as Person, not even with std::decay, universal reference
        // its enabled
 
        SpecialPerson(SpecialPerson&& rhs) : Person(std::move(rhs)){ }
        // move ctor calls base class forwarding ctor
};
 
//    copying and moving SpecialPerson objects would use the Person perfect-forwarding
//    constructor to copy or move their base class parts
// we need the fix the base class, since the derived its doing what it should do
 
// actual version
template<
    typename T,
    typename = typename std::enable_if<
        !std::is_base_of<Person, typename std::decay_t<T>>
    >::value
>
 
 
// REMEMBER

// Constraining templates via std::eenable_if permits the use of universal references and overloading together, but it controls the conditions under which compilers 
// may use the universal reference overloads
// Universal reference parameters often have efficiency advantages, but they typically have usability disadvantages.
 
int main()
{
    cout << "Hello, World!";
    return 0;
}
 
 
