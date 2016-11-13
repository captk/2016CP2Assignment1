/**
 * Simple 4-function calculator to demonstrate the use of Wordnum
 * 
 * Written for the topic COMP2711 Computer Programming 2
 * by Paul Calder
 * April 2015
 */

#include <iostream>
#include <unistd.h>

#include "Wordnum.h"

using namespace std;

int main(int argc, char** argv) {
    
    
    Wordnum n1, n2;
    char op;
    string input1, input2;
    int found;
    //cout << "Enter your expression:" << endl;
    ;
    for (int c; (c = getopt(argc, argv, "b")) != -1;) {
        switch (c) {
            case 'b': Wordnum::wordnumBritish();
                break;
            default:
                Wordnum::wordnumNormal();
                break;

        }
    }

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
            default:
                cout << "did not find operator" << endl;
                break;
        }
    }
   /*
    cout << 29+8036 << " = ";
    cout << Wordnum(29) + Wordnum(8036) << endl;
    
    cout << 20030001/3 << " = ";
    cout << Wordnum(20030001) / Wordnum(3) << endl;
    
    cout << endl;
    
    cout << 2000089*104 << " = ";
    cout << Wordnum("two_million_eighty_nine") * Wordnum("one_hundred_FOUR") << endl;

    cout << endl;
    
    cout << 20*11 << " = ";
    cout << Wordnum("twenty") * Wordnum("eleven") << endl;*/
    return 0;
}
