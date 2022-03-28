#include <iostream>
using std::cout;

class T;
class S {
  public:
    void hello() { cout << "hello\n"; }
    void (T::*pmf)();
};

class T {
  public:
    void bye() { cout << "bye\n"; }
    void (S::*pmf)();
};

S s;
T t;

int main()
{
    t.pmf = &S::hello;
    (s.*t.pmf)();

    s.pmf = &T::bye;
    (t.*s.pmf)();
}
