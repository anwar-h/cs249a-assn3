#include <iostream>

#include "QueueReactor.h"

using std::cout;
using std::endl;

void QueueReactor::onEnQ(int value) {
    cout << "Notification of enqueuing value: " << value << endl;
}

void QueueReactor::onDeQ(int value) {
    cout << "Notification of dequeuing value: " << value << endl;
}
