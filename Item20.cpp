#include <iostream>
#include <memory>

using namespace std;

int main() {
    // weak_ptr are created at birth from shared_ptr, pointing to the same place
    // as shared_ptr initializing them but they don’t affect the pointed-to 
    // object’s reference count, they manipulate the control the of second reference count

    auto spw = std::make_shared<Widget>(); // ref count = 1

    std::weak_ptr<Widget> wpw (spw); // ref count still 1
    spw = nullptr; // ref count is 0, wpw now dangles

    // if(wpw.expired()) ... we check to see if the initial pointer exists then: 

    // we need atomic operations to check and then give access to the object it points to
    // done by creating a !shared_ptr from weak_ptr!
    std::shared_ptr<Widget> spw1 = wpw.lock(); // returns null if weak_ptr has expired


    /*
    Potential use cases for std::weak_ptr include caching, observer lists, and the
    prevention of std::shared_ptr cycles.
    */


    return 0;
}
