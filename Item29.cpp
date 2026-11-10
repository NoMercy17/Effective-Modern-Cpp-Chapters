#include <iostream>

// ----------
// ASSUME that move operations are not present, not cheap and not used
// In code with known types or support for move semantics, there is no need for assumptions.
// ----------


// std::array is essentially a built-in array with an STL interface, different from the other standard containers, 
//      each of which stores its contents on the heap
// objects of such containers hold only a pointer to the heap memory(substract of the real way)
// the pointer makes it possible to 'move' the contents of the entire container in constant time, we copy the pointer
//      to the container's contents from the source container to target

std::vector<Widget> vw1;
auto vw2 = std::move(vw1);


// std::array lacks that pointer, the contents are stored directly in the std::array object
std::array<Widget, 10000> aw1;
auto aw2 = std::move(aw1); // runs in linear time not constant! All elements are moved into aw2

// Assuming thhat Widget offers move support moving the std::array will be faster than copying
// Yet both of them will have linear-time computentional complexity


// On the other hand, std::string offers constant-time move and linear-time copy

/*
    Many string implementations employ the small
    string optimization (SSO). With the SSO, “small” strings (e.g., those
    with a capacity of no more than 15 characters) are stored in a buffer
    within the std::string object having no heap-allocated storage is used.

    --> Moving small strings using an SSO-based implementation is no faster than copying them
*/

// the underlying copy operation may be replaced by the move operation only if the move operation is known to not throw! (noexcept)


int main(){


    return 0;
}
