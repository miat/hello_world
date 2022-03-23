// Reference: https://stackoverflow.com/questions/1485983/calling-c-member-functions-via-a-function-pointer
#include <iostream>

class Animal {
  public:
    typedef Animal *(*NewAnimalFunction)(void);

    virtual void makeNoise() { std::cout << "M00f!" << std::endl; }
};

class Dog : public Animal {
  public:
    typedef void (Dog::*BarkFunction)(void);

    typedef Dog *(*NewDogFunction)(void);

    Dog() { }

    static Dog *newDog() { return new Dog; }

    virtual void makeNoise() { std::cout << "Woof!" << std::endl; }
};

int main(int argc, char *argv[]) {
    // Call member function via method pointer
    Dog *pDog = new Dog();
    Dog::BarkFunction pBark = &Dog::makeNoise;

    (pDog->*pBark)();

    // Construct instance via factory method
    Dog::NewDogFunction pNew = &Dog::newDog;

    Animal *pAnimal = (*pNew)();

    pAnimal->makeNoise();

    return 0;
}
