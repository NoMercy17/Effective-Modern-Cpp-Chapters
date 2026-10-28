#include <iostream>


class Widget{
public:
    bool isLucky(int number);

    // making sure its not called improper because of the implicit convertion
    bool isLucky(char) = delete;
    bool isLucky(bool) = delete;
    bool isLucky(double) = delete; // we also delete the float one!

    /*
    if(isLucky('a')) ....
    if(isLucky(true)) ....
    if(isLucky(3.5)) ....

    */

};


// Suppose we have a template that works with built-in pointers
template<typename T>
void processPointer(T* ptr);

// 2 special cases of raw pointers that we might want to avoid are: 
// void* -> no wait to increment/decrement or dereference them
// char* -> typically use in C-style to represent pointers to strings not individual char

// WE CAN DELETE THEM THEN

void processPointer(void* ptr) = delete;
void processPointer(char* ptr) = delete;

int main(){


    return 0;
}
