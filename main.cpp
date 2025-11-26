#include <memory> 
#include <iostream>


using namespace std;

int main() {

    unique_ptr<int> x = make_unique<int>(10);

    cout << x << endl;
    return 0; 
}