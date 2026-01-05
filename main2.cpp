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
class Obj {
    public:
        int a = 5;

};

// pass by reference
void fun1(const Obj& a, Obj& b){
    //Cant chang a
    // a.a = 15; // expression must be a modifiable lvalue. A is const so It cannot be modified..
    b.a = 20; // We can see a problem here if Obj a and Obj b refer to the same object. It will get changed. 
    //Can chang b
};

// pass by reference and value
void fun2(const Obj& a, Obj b){
    //Cant chang a
    // a.a = 15; // expression must be a modifiable lvalue. A is const so It cannot be modified..
    b.a = 30; // We can see a problem here if Obj a and Obj b refer to the same object. It will get changed. 
    //Can chang b
};

// pass by reference but check that objects are not the same. 
void fun3(const Obj& a, Obj& b){
    if(&a == &b){
        std::cout << "Object a dna Object b refer to the same object." << std::endl;
    } else {
        std::cout << "Let's change the value of Obj 2 to be the same as Obj 1!" << std::endl;
        std::cout << "Value of object 1: " << a.a << std::endl;
        std::cout << "Value of object 2: " << b.a << std::endl;
        std::cout << "...Changing Value of Object 2..." << std::endl;
        b.a = a.a; 
        std::cout << "New Value of Object 2: " << b.a << std::endl;
    }
};


int main()
{

    /*
    *   Type conversion happens when one type is implicitly (automatically) or explicitly (Type Casting) converted
    *   into another type. We can see this with the example below. 
    */



    // char a = 'a'; // this is a single char literal (1 byte)

    // "b" (with double quotes) is the string literal 
    // const char* b = "b"; // This is a ptr to a string literal
    // char c[] = "c"; // This is an array of characters that holds the string literal "c" This is 
    // const char* d[] = {"abcd", "wxyz"}; // this is a pointer to an array of constant characters. 

    /* Note how there are many ways to work with string literals and characters. each one is slightly different
    *  and we should know the differences of each. Knowing how they behave is important. NOTE: char c[] = "c"; is
    *  an editable array. usually when working with string literals we use a pointer and make them const. 
    *  You can technically say char* b = "b", but your compiler will most likley give you a warning. 
    *  like this -> warning: "does not allow conversion from string literal to 'char *'"
    */

    // std::cout << "size of a: " << sizeof(a) << std::endl; //should be one byte. 
    // std::cout << "Size of b: " << sizeof(b) << std::endl; //should be the size of the pointer. When dereferenced it's the size of a single char
    // std::cout << "Size of c: " << sizeof(c) << std::endl; //should be 2 bytes because string literals have null '\0' at the end
    // std::cout << "d: " << *d << std::endl; // you can also index with []. Dereference is just pointing to the first string literal. 

    // std::cout << "The Letter \x42 and \102" << std::endl; // Okay so we can only excape hex and octal. I thout decimal too, but that's not the case.


    // Rememver variables can usually be initilized through the types constructor. Strings are variable-length sequence of characters
    // std::string some_string("this is a string literal that initilizes my string"); // Uses a constructor. 

    // std::cout << "My initilized string: " << some_string << std::endl;

    // Initilizers mean the object gets a value the moment it's created
    
    // There's a difference in use of the = sign. Initilization vs assignment. 
    // Initilization
    // int some_int = 1; // copy initilization (used the = sign)
    // int some_int2(5); // direct initilization ( NO = Sign )
    // int some_int3 = {10}; // copy initilization (used the = sign)
    // int some_int4{15}; // direct initilization ( NO = Sign )

    // int some_int5; //default initialized i.e. we dont give the variable a value explicitly. It's possibe this is uninitialized and the variable is undefined.  
    // NOTE to self: Always initilize built in types. 
    // Assignments
    // some_int2 = some_int;

    // std::cout << "Default initilized int. i.e. uninitilized bulit in type. What is it's value?: " << some_int5 << std::endl;

    // extern int i; // declares but does not define i. extern delares the variable that will be defined elswhere. 
    // int j; // declares and defines j

    // std::cout << "i is declared but not defined: " << i << std::endl; // This produces a linker error "Undefined symbols" if i is never defined(see below). 

    // i = 10; // define i

    // std::cout << "i is defined below main as: " << i << std::endl;


    // Testing threads. 

    /* I want to demonstrate how join() works. This main thread will not continue until we have finished each thread. 
    *  Foo waits for 10s and bar waits for 20 seconds. If I call .join on foo I should get a cout that its waiting
    *  and after 10s it will say it waited for 10s. same for bar, but with a 20s wait. If i join on foo first I should
    */

    // std::thread foo_thread(foo);
    // std::thread bar_thread(bar);


    // std::cout << "called 2 threads to run foo and bar." << std::endl;

    // foo_thread.join();
    // std::cout << "Foo finished" << std::endl;
    // bar_thread.join();
    // std::cout << "bar finished" << std::endl;


    // Seeing what happends if I flip the joins. 
    // bar_thread.join();
    // std::cout << "bar finished" << std::endl;
    // foo_thread.join();
    // std::cout << "Foo finished" << std::endl;



    // pointers and references. 

    int a;
    
    std::cout << "An uninitilized integer 'a' has garbage values" << std::endl; 
    std::cout << "value of a: " << a << std::endl;

    int* b; 
    std::cout << "an uninitilized pointer b has an address that some \"random\" address. the value is could be anything." << std::endl;
    //std::cout << "address of b: " << b << " Value of b: " << *b << std::endl; // if we try to assign this to somethign like '*b = 12' this could cause a segmentation fault. 

    int* c = nullptr; 

    std::cout << "c is initilized to nothing (nullptr)." << std::endl; // We CAN NOT dereference a nullptr. This has undefined behavior. Probably a segmentation fault. 
    
    // DOES NOT RUN: std::cout << "address of c: " << c << "Value of c: " << *c << std::endl; //dereferecing of *c caused a segmentation fault. 
    std::cout << "Address of c: " << std::endl; // we can still get it's address though which should be absolutly noting.
    if(c == nullptr)
    {
        std::cout << "(Checked if c == nullptr) Address of c is nullprt" << std::endl;
    }

    // So how do we initialize the value of what the prt points to? there's a few ways. 
    /**
     * 1. create another int you can point it do
     * 2. use the new operator along with a direct initialization
     */

    // 1. create another int you can point it do

    int d = 12; 
    c = &d; // c is assigned the new address of where 12 is stored. 

    std::cout << "The address of d: " << &d << " What c points to c: " << c << std::endl;
    std::cout << "Both have values 12. Value of d: " << d << " Dereference c to get the value it points to *c: " << *c << std::endl;

    // now lets change the value of d
    d = 15;
    std::cout << "Address of d: " << &d << " Value of d: " << d << std::endl;
    // notice. c still points to the address of d. 
    std::cout << "Address of c: " << c << " Value of c is now 15 *c: " << *c << std::endl; // Changing the value of d did not change it's address

    // 2. use the new operator along with a direct initialization
    int* e = new int(6);

    std::cout << "address of e: " << e << " Value of *e: " << *e << std::endl; // notice we can do this because we have initilized the value the ptr points to. 

    delete e; // new operator allocates memory on the heap. We must clean it up to avoid memory leak

    // NOTE with deleting using arrays. 
    char* f = new char[6](); // f points to an array of 6 characters. "hello\0". add the '()' to value-initialize everything to 0

    for(int i = 0; i < 6; i++){ 
        if(f[i] == 0){
            std::cout << '0';
        }
    }
    std::cout << std::endl; 

    f[0] = 'h';
    f[1] = 'e';
    f[2] = 'l';
    f[3] = 'l';
    f[4] = 'o';
    f[5] = '\0';

    for(int i = 0; i < 6; i++){
        if(f[i] != '\0'){
            std::cout << f[i];
        }
    }
    std::cout << std::endl; 

    // If we just delete f like 'delete f' we delete the pointer that points to the first character in the array 'h'
    // this leaks the memory leaving ello\0 in the memory. No way to free it up because we lost our ptr to it. 

    delete[] f; 

    // now how about references? let's look deeper into this by compairing memory addresses. 
    // int& g; // Notice that references are required to be initialized at instantiation. reference works as an alias for an existing variable
    int g = 25;
    int& h = g;

    std::cout << "Address of g: " << &g << " Value of g: " << g << std::endl;
    std::cout << "Address of the reference var h: " << &h << " Value of the reference h: " << h << std::endl;
    // notice how both share the same address and point to the same value? 

    // just like pointers if we change the value of one it changes it for the other. but we can just assign it directly. 

    h = 50;

    std::cout << "Value of g: " << g << " Value of h: " << h << std::endl; 
    std::cout << "Address of g: " << &g << std::endl;
    std::cout << "Address of h: " << &h << std::endl;
    // Changing one changes the other. 

    /**
     * Difference between ptrs and references. 
     * Pointers: 
     * 1. pointers can be reassigned to point to a different object. 
     * 2. pointers require the dereferencing * to get to the value they point to
     * 3. pointers are assigned to things using the & address of operator. 
     * 4. Can be declared without initialization (should point to noting i.e. nullptr not dangling)
     * 5. used the -> arror operator. 
     * 6. Can reassign the pointer to point to a different object. 
     * References: 
     * 1. Cannot point to nothing. It must be initilized. 
     * 2. Uses the . operaotr 
     * 3. Cannot be reassigned to another object. Its bound to the origional "Address spot". It's the primary practical difference between references and pointers:
     * 4. Pass by reference also doesnt copy the object. 
     */

    class A{
        public: 
        int a = 18; 

    };

    class B{
        public:
        int a = 19;
    };

    A someA;
    A someAC; 
    B someB;

    //ptr to an A
    A* myA = &someA; 
    //reference to a B
    B& myB = someB; 


    //operator usage. 

    std::cout << "Use of -> " << myA->a << std::endl;
    std::cout << "Use of . " << myB.a << std::endl; 

    std::cout << "myA points to someA object at address: " << myA << std::endl; 

    // reassign myA to a different object. 
    myA = &someAC;
    myA->a = 333; 
    std::cout << "myA now points do a completly differnt object. The address is: " << myA << std::endl; 

    std::cout <<"Check this by compairing the values of the public member a in each object." << std::endl;

    std::cout << "myA->a: " << myA->a << std::endl; 
    std::cout << "No longer the same as it was before at someA " << someA.a << std::endl;

    // Object Slicing? here's what you need to know

    class baseClass{
        protected:
        char charA = 'A', charB = 'B';
        public:
        virtual void getStuff()
        {
            std::cout << charA << " " << charB << std::endl;
        };
        virtual ~baseClass() = default;
    };

    class derivedClass : public baseClass {
        protected:
        //I want ints too
        int intA = 4, intB = 5;
        public:
        void getStuff() override {
            std::cout << charA << " " << charB << "\n"
            << intA << " " << intB << std::endl;
        }
    };

    //Lets instantiate a derivedClass 

    derivedClass myDerivedClass; 

    //We can get our ints and our chars

    std::cout << "We get chars and ints" << std::endl;
    myDerivedClass.getStuff();

    //now lets "Slice" our myDerivedClass

    baseClass myBaseClass = myDerivedClass; // no longer have access to derived class ints

    std::cout << "slicing occures" << std::endl; 
    myBaseClass.getStuff();
    // but if we use pointers...

    baseClass* myBasePtr = &myDerivedClass; //Same with a pointer. 

    std::cout << "Now we have a base ptr pointing to the address of derived class i.e. baseClass* myBasePtr = &myDerivedClass;" << std::endl;
    std::cout << "call the myBasePtr on getStuff should get ints and chars." << std::endl;
    myBasePtr->getStuff();

    Obj myObj; 
    Obj& myObjRef = myObj;

    std::cout << "myObj holds an int value of 5. Value: " << myObj.a << ", but when we call fun1(const Obj& a, Obj& b) we see that if they refer to the same Obj it can be changed" << std::endl;
    std::cout << "While the first parameter is const and the second is not if they reference the same Obj we should't chagne b" << std::endl;

    std::cout << "...Calling fun1(myObj, myObjRef)..." << std::endl;

    fun1(myObj, myObjRef);

    std::cout << "Checking value of myObj again. Value: " << myObj.a << std::endl;

    std::cout << "Value now evaluates to 20.... Let's keep that 20 and call fun2." << std::endl;
    std::cout << "fun2 uses a const Obj& a, and a Obj b. Pass by value NOT reference. If it's truly a local copy after \n function runs it should still be 20 NOT 30" << std::endl;

    std::cout << "...Calling fun2(myObj, myObjRef)..." << std::endl;

    fun2(myObj, myObjRef);

    std::cout << "Checking value of myObj again. Value: " << myObj.a << std::endl;

    std::cout << "Let's use fun3" << std::endl;

    fun3(myObj, myObjRef);

    std::cout << "Now with different Objs" << std::endl; 
    Obj newObj; 

    fun3(newObj, myObj);


    return 0;
}

/*Notice how this is defined below? We can use extern to declare above and then define below. 
* This allows us to not need to define before the program. It can "find it" in a way by not 
* needing to execute in "order". Also, this allows us to define variables exactly once, 
* but we can declared many times in many files.
*/
int i = 10; 