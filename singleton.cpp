// Reference: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include <iostream>

class Singleton {

  public:
    static Singleton &get_instance() {
        static Singleton instance; // Guaranteed to be destroyed.

        return instance;
    }

    Singleton(Singleton const &) = delete;

    void operator=(Singleton const &) = delete;

    void hello() { std::cout << "hello world\n"; }

  private:
    Singleton() { }
};

int main() { Singleton::get_instance().hello(); }
