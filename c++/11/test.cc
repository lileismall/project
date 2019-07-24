
#include <iostream>

using namespace std;

void F(int a) {
    cout << "int a" <<endl;
    cout << a << endl;
}

void F(int &&a) {
    cout << "int &&a" <<endl;
    cout << a << endl;
}

template<class A>
void G(A &&a) {
    return F(forward<A>(a));  //1
     /* return F(a);        //2 */
    //  
}

int main() {
    int i = 2;
    G(i);
    G(5);

    return 0;
}
