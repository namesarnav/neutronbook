#include <memory> 
#include <iostream>
#include "Order.h"



using namespace std;

int main() {

    unique_ptr<int> x = make_unique<int>(10);

    cout << x << endl;  
    return 0; 
}