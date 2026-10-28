#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>

using namespace std;

enum class Status : uint32_t;
enum Color : uint8_t; // forward-declared unscoped enum with fixed underlying type


enum Color : uint8_t {Black, White, Red}; // must match the forward declaration

enum class Color2 {Black, White, Red}; // underlying type int

void continueProcessing(Status s); // use of fwd-declarated enum so the header of these files
// do not require any recompilation if we add 1 or more status value


enum class Status : uint32_t{ // 32 bit
    good = 0,
    failed = 1,
    incomplete = 100,
    corrupt = 200,
    complex_value = 0xFFFFFFF,
};


// CASE WHERE UNSCOPED ENUMS MIGHT BE MORE USEFUL

using UserInfo = std::tuple<std::string, std::string, std::size_t>; // positions can be hard to understand
UserInfo uInfo{"Alice", "alice@example.com", 42};
auto emailByPosition = std::get<1>(uInfo); // auto deduces std::string (a copy)

// An unscoped enum can supply a compile-time tuple index.
enum UserInfoFields {
    uName,
    uEmail,
    uReputation
};
UserInfoFields selectedField = uEmail; // this variable itself has type UserInfoFields
auto emailByEnum = std::get<uEmail>(uInfo); // uEmail is index 1; result is a std::string copy

// If UserInfoFields were declared as `enum class`, we cast it manually
// auto email = std::get<static_cast<std::size_t>(UserInfoFields::uEmail)>(uInfo);




int main() 
{

    if(Red < 14) // unscoped one
        cout << "Stupid" << endl;

    // if(Color2::Red < 14) - ERROR
        // cout << "Double stupid!" << endl;

    // we twist if needed buy manually converting
    if(static_cast<int>(Color2::Red) < 2)
        cout << "Somewhat stupid" << endl;
    


    return 0;
}
