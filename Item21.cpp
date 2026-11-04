#include <iostream>
#include <memory>
#include <vector>
using namespace std;
 
 
// potential risk if the computePriority gives an exception, the dinamically allocated Widget
// will be leaked because it will never be stored in std::shared_ptr
processWidget(std::shared_ptr<Widget>(new Widget), 
            computePriority());
 
processWidget(std::make_shared<Widget>(), computerPriority());

// or to make it exception safe without the make func: 

std::shared_ptr<Widget> spw(new Widget, cusDel);
processWidget(spw, computePriority());
 

// control block contains beside the reference count that keep track of the shared_ptr
// that refers to it, a second reference that tracks how many weak_ptr refers to it
 
int main()
{
    auto upw1 = std::make_unique<Widget>();     // with make func
    std::unique_ptr<Widget> upw2{new Widget};   // without make func
 
   
    auto spw1 = std::make_shared<Widget>();
    std::shared_ptr<Widget> spw2{new Widget};
 

    // does 2 allocations
    std::shared_ptr<Widget> spw(new Widget);
    // one memory allocation for Widget object and the second for the control block

    // allocate one chunk of memory that holds both
    auto spw = std::make_shared<Widget>();



    // we should prefer not default to make functions, based on our circumstances

    // 1: make functions do not permit custom deleters, but std::unique_ptr / std::shared_ptr
    // ctor do

    std::unique_ptr<Widget, decltype(widgetDeleter)> upw(new Widget, widgetDeleter);
    std::shared_ptr<Widget> spw(new Widget, widgetDeleter); 

    // 2: How are the make func implemented when creating an object that overloads
    //  both the init_list and without, using brances prefers the 
    //  initializer_list while the parenthesis prefers ctor

    // given that the make_fnc perferct-forward -> here we use the ctor one
    auto upv = std::make_unique<std::vector<int>>(10, 20);
    auto spv = std::make_shared<std::vector<int>>(10, 20);


    // a work-arround to use the initializer list:

    auto init_list = {1,2,3,4};
    auto spv = std::make_shared<std::vector<int>(init_list)>;


    // Some edge cases where problems may occur, with shared_ptr:
    // 1: Using make func to create object of types that have custom delete / new operators
    // is not the best idea given that the memory allocated by std::allocate_shared
    // is the size of allocated object and not:
    // OBJECT + size Control Block

    return 0;
}
