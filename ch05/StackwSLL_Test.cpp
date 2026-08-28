#include "../common/StackwSLL.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    StackwSLL<int> SwSLL;
    SwSLL.push(7);
    SwSLL.push(13);
    cout << SwSLL.top() << endl;
    SwSLL.pop();
    SwSLL.push(9);
    cout << SwSLL.top() << endl;
    cout << SwSLL.top() << endl;
    SwSLL.pop();
    StackwSLL<string> SwSLL2;
    SwSLL2.push("Bob");
    SwSLL2.push("Alice");
    cout << SwSLL2.top() << endl;
    SwSLL2.pop();
    SwSLL2.push("Eve");
    // A = [ ], size = 0
    // A = [7*], size = 1
    // A = [7, 13*], size = 2
    // A = [7*], outputs: 13
    // A = [7, 9*], size = 2
    // A = [7, 9*], outputs: 9
    // A = [7*], outputs: 9
    // B = [ ], size = 0
    // B = [Bob*], size = 1
    // B = [Bob, Alice*], size = 2
    // B = [Bob*], outputs: Alice
    // B = [Bob, Eve*], size = 2
}
