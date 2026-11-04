#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

// before Pimpl Idiom
class Widget {
    public:
        Widget();

    private:
        std::string name;
        std::vector<double> data;
        Gadget g1, g2, g3; // user-defined
};

// after

// widget.h for example
// widget.h file -> visible and used by the clients!
class Widget {
    public:
        Widget();
        ~Widget();
    private:
        struct Impl; // we declare implementation struct
        Impl *pImpl; // and a pointer to it
};
// also now the widget class doesn't need to depend on the headers for string, vector...
// incomplete type -> Widget::Impl, we can declare a pointer to it tho



// widget.cpp
#include "gadget.h"
#include <string>
#include <vector>
#include "widget.h"


struct Widget::Impl {
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget() : pImpl(new Impl){}

Widget::~Widget() { delete pImpl; }



// old implementaqtion, modern version with smart pointer:
// widget.h
class Widget {
    public:
        Widget();
    private:
        struct Impl;
        std::unique_ptr<Impl> iImpl;
};
// widget.cpp
#include "gadget.h"
#include <string>
#include <vector>
#include "widget.h"

struct Widget::Impl {
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget(): pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() = default;  // fix, for the incomplete issue

// problem with std::unique_ptr and incomplete types, to become complete type we need 
// to have the compiler see the Widget's destructor 


// classes using pImpl Idiom are natural candidates for move support, since the move generated 
// operation perform a move on the std::unique_ptr

// to make the type complete we declare it in widget.hpp 
class Widget {
    public:
        Widget();
        ~Widget();
        Widget(Widget&& rhs);
        Widget& operator=(Widget&& rhs);
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
};
 
 
int main(){


    return 0;
}
