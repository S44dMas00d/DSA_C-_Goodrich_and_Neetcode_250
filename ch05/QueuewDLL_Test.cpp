#include "../common/QueuewDLL.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    QueuewDLL<int> QwDLL;
    cout << QwDLL.empty() << endl;
    cout << QwDLL.size() << endl;
    QwDLL.enqueue(1);
    QwDLL.enqueue(2);
    QwDLL.enqueue(3);
    QwDLL.enqueue(4);
    cout << QwDLL.empty() << endl;
    cout << QwDLL.size() << endl;
    QwDLL.dequeue();
    cout << QwDLL.empty() << endl;
    cout << QwDLL.size() << endl;
    cout << QwDLL.front() << endl;
    QwDLL.dequeue();
    cout << QwDLL.front() << endl;
    QwDLL.dequeue();
    cout << QwDLL.front() << endl;
}
