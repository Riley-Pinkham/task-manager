#include <iostream>
#include <string>
#include <chrono>
#include <thread>


void foo()
{
    std::cout << "foo called. waiting for a few seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "foo called. sleeped for 10sec" << std::endl;


}

void bar()
{

    std::cout << "bar called. waiting for a few seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
    std::cout << "bar called. sleeped for 20sec" << std::endl;

}

int main()
{

    /*
    *   Type conversion happens when one type is implicitly (automatically) or explicitly (Type Casting) converted
    *   into another type. We can see this with the example below. 
    */



    char a = 'a'; // this is a single char literal (1 byte)

    // "b" (with double quotes) is the string literal 
    const char* b = "b"; // This is a ptr to a string literal
    char c[] = "c"; // This is an array of characters that holds the string literal "c" This is 
    const char* d[] = {"abcd", "wxyz"}; // this is a pointer to an array of constant characters. 

    /* Note how there are many ways to work with string literals and characters. each one is slightly different
    *  and we should know the differences of each. Knowing how they behave is important. NOTE: char c[] = "c"; is
    *  an editable array. usually when working with string literals we use a pointer and make them const. 
    *  You can technically say char* b = "b", but your compiler will most likley give you a warning. 
    *  like this -> warning: "does not allow conversion from string literal to 'char *'"
    */

    std::cout << "size of a: " << sizeof(a) << std::endl; //should be one byte. 
    std::cout << "Size of b: " << sizeof(b) << std::endl; //should be the size of the pointer. When dereferenced it's the size of a single char
    std::cout << "Size of c: " << sizeof(c) << std::endl; //should be 2 bytes because string literals have null '\0' at the end
    std::cout << "d: " << *d << std::endl; // you can also index with []. Dereference is just pointing to the first string literal. 

    std::cout << "The Letter \x42 and \102" << std::endl; // Okay so we can only excape hex and octal. I thout decimal too, but that's not the case.


    // Rememver variables can usually be initilized through the types constructor. Strings are variable-length sequence of characters
    std::string some_string("this is a string literal that initilizes my string"); // Uses a constructor. 

    std::cout << "My initilized string: " << some_string << std::endl;

    // Initilizers mean the object gets a value the moment it's created
    
    // There's a difference in use of the = sign. Initilization vs assignment. 
    // Initilization
    int some_int = 1; // copy initilization (used the = sign)
    int some_int2(5); // direct initilization ( NO = Sign )
    int some_int3 = {10}; // copy initilization (used the = sign)
    int some_int4{15}; // direct initilization ( NO = Sign )

    int some_int5; //default initialized i.e. we dont give the variable a value explicitly. It's possibe this is uninitialized and the variable is undefined.  
    // NOTE to self: Always initilize built in types. 
    // Assignments
    some_int2 = some_int;

    std::cout << "Default initilized int. i.e. uninitilized bulit in type. What is it's value?: " << some_int5 << std::endl;

    extern int i; // declares but does not define i. extern delares the variable that will be defined elswhere. 
    int j; // declares and defines j

    // std::cout << "i is declared but not defined: " << i << std::endl; // This produces a linker error "Undefined symbols" if i is never defined(see below). 

    i = 10; // define i

    std::cout << "i is defined below main as: " << i << std::endl;


    // Testing threads. 

    /* I want to demonstrate how join() works. This main thread will not continue until we have finished each thread. 
    *  Foo waits for 10s and bar waits for 20 seconds. If I call .join on foo I should get a cout that its waiting
    *  and after 10s it will say it waited for 10s. same for bar, but with a 20s wait. If i join on foo first I should
    */

    std::thread foo_thread(foo);
    std::thread bar_thread(bar);


    std::cout << "called 2 threads to run foo and bar." << std::endl;

    // foo_thread.join();
    // std::cout << "Foo finished" << std::endl;
    // bar_thread.join();
    // std::cout << "bar finished" << std::endl;


    // Seeing what happends if I flip the joins. 
    bar_thread.join();
    std::cout << "bar finished" << std::endl;
    foo_thread.join();
    std::cout << "Foo finished" << std::endl;








    return 0;
}

/*Notice how this is defined below? We can use extern to declare above and then define below. 
* This allows us to not need to define before the program. It can "find it" in a way by not 
* needing to execute in "order". Also, this allows us to define variables exactly once, 
* but we can declared many times in many files.
*/
int i = 10; 