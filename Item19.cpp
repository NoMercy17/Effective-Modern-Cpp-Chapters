#include <iostream>
#include <memory>
using namespace std;

    /*
    What a std::shared_ptr stores:
        A shared_ptr object typically contains two pointers: one to the managed object
        and one to a control block. The control block is separate from the shared_ptr
        object; it is stored in dynamically allocated memory. Its location may be chosen
        by a custom allocator, if one was supplied.

        The control block stores the shared ownership (strong) reference count and the
        weak reference count. It also stores a copy of the custom deleter, if one was
        supplied, and a copy of the custom allocator, if one was supplied. It may contain
        other bookkeeping data as well.

        Therefore, the reference count is not stored directly inside the shared_ptr
        object. Each shared_ptr object points to the managed object and shares access to
        that object's control block. Using std::make_shared commonly combines         allocation of the object and control block into one allocation, but the control block
        is still separate from the shared_ptr object itself.
    */

    /*
    Reasoning: Do not create a shared_ptr from `this` when the object is already
    managed by a shared_ptr. That would create a second control block, so both
    owners could try to delete the same object. Derive the class from
    
    std::enable_shared_from_this and call shared_from_this() to get another
    shared_ptr that uses the existing control block. Call it only after the object
    is already managed by a shared_ptr.
    */

    /* Unsafe example (creates a separate control block):
       std::shared_ptr<Widget> self(this);
    */

    /* Safe example:
       class Widget : public std::enable_shared_from_this<Widget> {
       public:
           std::shared_ptr<Widget> getShared() {
               return shared_from_this();
           }
       };

       auto widget = std::make_shared<Widget>();
       auto sameOwner = widget->getShared();
    */

    /*
    If sp1 and sp2 are std::shared_ptrs to different objects, 
    the assignment sp1 = sp2 modifies sp1 such that it points to the object 
    pointed to by sp2 resulting in count value for the object initially pointed to by sp1 is
    decremented, while that for the object initially pointed to by sp2 is incremented
    */

    /*
    Because reference count exists, it brings performance implications:
        - shared_ptr twice the size of raw pointer(since they contain a raw pointer for the resource 
        and one for resource's reference count)
        - shared_ptr reference count is always dynamically allocated, but the allocation 
        of the resource is AVOIDED TO BE DYNAMIC when pointer is created with !!make_shared!!
        - increments/decrements of the reference count must be atomic, assume read/write of them 
        is costly
    */


    /*
    Move construction/operator is faster than copy construction/operator because:
        when we move the old to new ptr, the old source ptr stops pointing to the resource
        and as result, no reference count manipulation !!required!!


    */

auto loggingDel = [](Widget *pw){
    makeLogEntry(pw);
    delete pw;
};

std::unique_ptr<Widget, decltype(loggingDel)> up_ptr(new Widget, loggingDel);
std::shared_ptr<Widget> shar_ptr(new Widget, loggingDel); // deleter type not part of ptr type


// shared ptr more flexible so that 
auto customDeleter1 = [](Widget *pw) { … };
auto customDeleter2 = [](Widget *pw) { … };


std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
std::shared_ptr<Widget> pw2(new Widget, customDeleter2);

// and are added together easily

std::vector<std::shared_ptr<Widget>> vpw {pw1, pw2};

int main() 
{
    std::shared_ptr<int> ptr = std::make_shared<int>(31);
    std::shared_ptr<int> ptr2 = ptr;
    std::shared_ptr<int> ptr3 = ptr;

    ptr2 = nullptr;

    cout << ptr.use_count() << endl; // 2 
    cout << *ptr << endl;


    // Regarding the control Block (reference count, weak count, and OtherSection)
    // the shared pointer creates a new control block when:
        // - std::make_shared always creates a control block
        // - shared_ptr is constructed from unique_ownership pointer
        // - when std::shared constructor is called with raw pointer

    auto pw = new Widget;


    std::shared_ptr<Widget> spw1(pw, loggingDel); // creates control block for *pw

    std::shared_ptr<Widget> spw2(pw, loggingDel); // creates 2nd control block for *pw

//      multiple reference counts, and multiple reference counts
//      means the object will be destroyed multiple times
//      very very bad

    // we can use the new keyword if needed to pass raw ptr so its clearer 

    // 
    std::shared_ptr<Widget> spw1(new Widget, loggingDel);
    return 0;
}
