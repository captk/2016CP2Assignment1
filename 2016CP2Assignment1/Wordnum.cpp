/**
 * Wordnum: a class for computing with words
 *
 * Written for the topic COMP2711 Computer Programming 2
 * by Paul Calder
 * April 2015
 * 
 * Completed by:
 * Aurora Williams
 * Cuong Ngo
 * Semester 2 2016
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
 * Map units' digits into words
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

//maybe put hundreds somewhere here.
//string hundreds = "hundred"
string triads[] = {
    "", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "hexillion",
    "heptillion", "octillion", "nonillion"
};

/**
 * Writes number word text
 *
 * n is the value of the number to write
 * returns the text for the number, with '_' between words
 */

//go through each triad and convert each one to a string

string Wordnum::write_number(int n) {

    //cout << "write_number running with: " << n << endl;
    string words[8] = {"", "", "", "", "", "", "", ""};
    int count = 0;
    int place = 1000000000;

    for (int i = 3; i >= 0; i--) {
        //cout << "looking for a triad" << endl;
        if (n / place > 0) {
            //cout << "Found a non-zero triad for: " << triads[i] << endl;
            words[count] = triadToString(n / place);
            count++;
            if (triads[i] != ""){
                words[count] = triads[i];
                count++;
            }
        }
        n %= place;
        place /= 1000;
    }

    return join(words + 0, words + count, '_');

}

//Aurora's slightly altered int converter

string Wordnum::triadToString(int n) {
    //cout << "converting " << n << " into a string" << endl;
    //each word is a digit
    string words[3] = {"", "", ""};
    int count = 0;

    if (n / 100 > 0) {
        //cout << "found hundreds!" << endl;
        words[0] = units[n / 100] + "_hundred";
        n = n % 100;
        count++;
    }

    if (n / 10 == 0) {
        //cout << "units only" << endl;
        words[count] = units[n];
        count++;
        return join(words + 0, words + count, '_');
    } else if (n > 10 && n < 20) {
        //cout << "teens found" << endl;
        words[count] = teens[n % 10 - 1];
        return join(words + 0, words + count, '_');
    } else if (n == 10) {
        //cout << "only decades" << endl;
        words[1] = decades[0];
        return join(words + 0, words + count, '_');
    } else {
        //cout << "more than nineteen" << endl;
        words[count] = decades[n / 10 - 1];
        count++;
        if (n % 10 != 0) {
            //cout << "with a unit" << endl;
            words[count] = units[n % 10];
            count++;
        }

        return join(words + 0, words + count, '_');
    }


}

/**
 * Reads number word text
 * 
 * n is the text of the number to read, with '_' between words
 * returns the value of the number
 */

int Wordnum::read_number(string inString) {
    //reads input n string and converts each element to lower case
    //cout << "reading number: " << inString << endl;
    int sign = 1;
    int total = 0;
    for (int i = 0; i < inString.length(); i++) {
        inString[i] = tolower(inString[i]);
    }
    string words[10]; // enough for longest text

    string* word = split(inString, words, '_'); //calls split function

    //index of a found word
    int startIndex = 0;

    //lets deal with negative numbers here
    if (words[0] == "negative") {
        sign = -1;
        words[0].clear();
        startIndex = 1;
    }

    for (int i = 0; i < 10; i++) {
        //cout << "searching word " << i  << ": " << words[i] << endl;

        //for each word,
        //run through our triad array and find any of the triads present
        //currently triad is 10 strings long
        //we are traversing from the last element to the first so that we only deal
        //with the biggest triad at any point. This makes extracting the triad
        //easier
        for (int j = 10; j > 0; j--) {
            //cout << "Finding triad " << j<<": " << triads[j] << endl;
            if (words[i].find(triads[j]) != string::npos) {

                //erase this word if we find it
                //cout << "erasing word, \"" << words[i] << "\" which has length"
                //<< words[i].length() << endl;
                words[i].erase(0, words[i].length());

                //get the triad value
                int triadTotal = getTriad(words, startIndex, i);

                //put the triad in the right place value
                for (int k = 0; k < j; k++) {
                    triadTotal *= 1000;
                }

                total += triadTotal;

                //now the next starting index for the search is the one after
                //the triad identifier
                startIndex = i + 1;
            }
        }
    }

    //now to search the rest of the word array for the unit triad
    total += getTriad(words, startIndex, 9);
    //cout << "word's numerical total: " << total * sign << endl;
    return total * sign;

}

//search for the value of a particular triad in the array, words[]
//start is the index to start searching from
//end is the index AFTER the last index that will be searched
//this function will return the numerical value of the triad
//this function does not return the actual place value of the triad
//anything searched through will be erased afterwards, BEWARE

int Wordnum::getTriad(string *words, int start, int end) {
    //cout << "getTriad running" << endl;
    int total = 0;

    //look for the hundreds first
    //if it exists, it should be found one index after start
    if (words[start + 1] == "hundred") {
        //cout << "hundreds found!" << endl;
        for (int i = 0; i < 10; i++) {

            //find the numerical value of the hundred place
            if (words[start] == units[i]) {
                total += i * 100;
                //delete all traces of the hundreds
                words[start].erase(0, words[start].length());
            }
        }
        //delete so we don't run into again
        words[start + 1].erase(0, words[start + 1].length());
    }

    //see if the word matches any in our arrays
    //the word will be erased even if not found
    //this makes sense as one word should only correspond to one digit
    for (int k = start; k < end; k++) {
        string currentWord = words[k];
        //cout << currentWord << endl;

        //find current word in the unit string
        for (int i = 0; i < 10; ++i) {
            if (currentWord == units[i]) {
                total += i;
            }
        }

        //find current word in decades
        for (int i = 0; i < 9; ++i) {

            if (currentWord == decades[i]) {
                total += (i + 1)*10;
            }
        }

        //find current word in teens
        for (int i = 0; i < 9; ++i) {
            if (currentWord == teens[i]) {
                total += (i + 11);
            }
        }

        words[k].erase(0, words[k].length());
    }
    return total;
}