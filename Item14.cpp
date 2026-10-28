#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>


// most optimizable
// optimizers do not need to keep the runtime stack in an unwindable state nor to ensure the object
// are destroyed in reverse order if an exception occurs
// "possibly unwinding"
int f(int x) noexcept{
 	return x; 
}

// less optimizable
// unwinding
int f2(int x) throw() {
 	return x; 
}

// even less optimizable
int f3(int x){
    return x;
}

void moveVector(std::vector<int>& source, std::vector<int>& destination) noexcept {
    destination = std::move(source);
}

void swapVectors(std::vector<int>& first, std::vector<int>& second) noexcept {
    first.swap(second);
}


// For other functions the case is even stronger!
int main(){
    // with move semantics
    // std::vector::push_back takes advantage of this “move if you can, but
    // copy if you must”
    std::vector<int> original{1, 2, 3};
    std::vector<int> moved;
    moveVector(original, moved);
    std::cout << "Moved vector: ";
    for (const int& value : moved) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    // with swap operations
    std::vector<int> first{4, 5};
    std::vector<int> second{6, 7, 8};
    swapVectors(first, second);
    std::cout << "After noexcept swap, first has " << first.size()
              << " elements and second has " << second.size() << " elements.\n";

    return 0;
}
