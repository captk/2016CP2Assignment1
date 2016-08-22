/**
 * Simple 4-function calculator to demonstrate the use of Wordnum
 * 
 * Written for the topic COMP2711 Computer Programming 2
 * by Paul Calder
 * April 2015
 */

#include <iostream>

#include "Wordnum.h"

using namespace std;

int main () {
    Wordnum n1, n2;
    char op;
    while (cin >> n1 >> op >> n2) {
        switch (op) {
            case '+': cout << n1 + n2 << endl;
                break;
            case '-': cout << n1 - n2 << endl;
                break;
            case '*': cout << n1 * n2 << endl;
                break;
            case '/': cout << n1 / n2 << endl;
                break;
        }
    }
    return 0;
}
