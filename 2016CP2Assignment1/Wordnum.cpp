/**
 * Wordnum: a class for computing with words
 *
 * Written for the topic COMP2711 Computer Programming 2
 * by Paul Calder
 * April 2015
 */

#include "Wordnum.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * Convenience functions for manipulating number strings
 */

/**
 * Joins an array of component strings into a single string
 *
 * first points to the first component to use
 * last points to the component after the last to use
 * separator is the character to separate components
 *
 * For example:
 *
 *   string words[] = {"forty", "two"};
 *   string number = join(words+0, words+2, '_');
 *
 * number will contain "forty_two"
 */

string join(string* first, string* last, char separator) {
    ostringstream output;
    if (first < last) {
        output << *first++;
    }
    while (first < last) {
        output << separator << *first++;
    }
    return output.str();
}

/**
 * Splits a string into an array of component strings (assumed large enough)
 *
 * text is the string to split
 * first points to the first component to use
 * separator is the character that separates components
 * return value points to the component after the last used
 *
 * For example:
 *
 *   string words[10];     // enough for longest text
 *   string number = "forty_two";
 *   string* word = split(number, words, '_');
 * 
 * words[0] will contain "forty"
 * words[1] will contain "two"
 * word will point to words[2]    
 */

string* split(string text, string* first, char separator) {
    istringstream input(text);
    string token;
    while (getline(input, token, separator)) {
        if (token.length() > 0) *first++ = token;
    }
    return first;
}

/*
 * Wordnum implementation
 */

/**
 * IO operators
 */

ostream& operator<<(ostream& os, const Wordnum& n) {
    return os << Wordnum::write_number(n.value_);
}

istream& operator>>(istream& is, Wordnum& n) {
    string text;
    if (is >> text) {
        n.value_ = Wordnum::read_number(text);
    }
    return is;
}

/**
 * Map units digits into words
 */

string units[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
string teens[] = {
    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};
string decades[] = {
    "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
};

/**
 * Writes number word text
 *
 * n is the value of the number to write
 * returns the text for the number, with '_' between words
 */

//clean here
string Wordnum::write_number(int n) {

    string words[10];
    if (n < 10) {
        return units[n];
    } else if (n > 10 && n < 20) {
        return teens[n % 10 - 1];
    } else if (n == 10) {
        return decades[0];
    } else {
        if (n % 10 != 0) {
            words[0] = decades[(n / 10) - 1];
            words[1] = units[n % 10];
            return join(words + 0, words + 2, '_');
        }
        return decades[n / 10 - 1];
    }


}

/**
 * Reads number word text
 * 
 * n is the text of the number to read, with '_' between words
 * returns the value of the number
 */

int Wordnum::read_number(string n) {
    //reads input n string and converts each element to lower case
    int total = 0;
    for (int i = 0; i < n.length(); i++) {
        n[i] = tolower(n[i]);
    }
    string words[10]; // enough for longest text

    string* word = split(n, words, '_'); //calls split function
    for (int i = 0; i < 10; i++) {

        string currentWord = words[i];
        for (int i = 0; i < 10; ++i) {
            if (currentWord == units[i]) {
                total += i;
            }
        }
        for (int i = 0; i < 9; ++i) {

            if (currentWord == decades[i]) {
                total += (i + 1)*10;
            }
        }
        for (int i = 0; i < 9; ++i) {
            if (currentWord == teens[i]) {
                total += (i + 11);
            }
        }


    }

    return total;

}
