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

//define the boolean, british. This is required for compilation.
bool Wordnum::british;

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
//billion is incorrectly spelt because this assignment does not accept billions
string triads[] = {
    "", "thousand", "million", "billlion", "trillion", "quadrillion", "quintillion", "hexillion",
    "heptillion", "octillion", "nonillion"
};

/**
 * flag the class to operate in british mode
 * 
 * Returns:
 * nothing
 */
void Wordnum::wordnumBritish() {
    Wordnum::british = true;
    //cout << "Would you like a cup of tea?" << endl;
}

/**
 * flag the class to operate normally
 * 
 * Returns:
 * nothing
 */
void Wordnum::wordnumNormal() {
    Wordnum::british = false;
    //cout << "Out of tea." << endl;
}

/**
 * Writes number word text
 *
 * Parameters:
 * -n: integer value of the number to write
 * 
 * Returns:
 * The text for the number, with '_' between words
 */

//go through each triad and convert each one to a string

string Wordnum::write_number(int n) {

    //cout << endl << "writing number: " << n << endl;
    bool isHundreds = false;

    //storage for strings that need concatenation
    string words[16] = {"", "", "", "", "", "", "", "","","","","","","","",""};

    //variable that tracks how many strings need to be concatenated
    int count = 0;

    //variable that tracks the place value of a particular triad
    int place = 1000000000;

    //deal with negative numbers here
    if (n < 0) {
        words[count] = "negative";
        n *= -1;
        count++;
    }
    
    if (n > 100) {
        //cout << "n is bigger than 100" << endl;
        isHundreds = true;
    }
    //Searches billions, millions then thousands for triads in that order
    for (int i = 3; i >= 0; i--) {


        if (n / place > 0) {
            words[count] = triadToString(n / place);
            if (isHundreds && n < 100 && british) {
                words[count].insert(0, "and_");
                //cout << "inserting and_" << endl;
            }

            count++;
            if (triads[i] != "") {
                words[count] = triads[i];
                count++;
            }
        }
        n %= place;
        place /= 1000;
    }

    //if there are no strings to concatenate, then the value must be zero
    if (count == 0) return "zero";

    return join(words + 0, words + count, '_');

}

/**
 * Function that takes a triad (a three digit int) and returns the equivalent
 * value in words as a string type. This function has unknown behaviour when
 * passed ints that are more than three digits.
 *
 * Parameters:
 * -n: a three digit int
 *
 * Returns:
 * String containing words that represent the value of the int
 */

string Wordnum::triadToString(int n) {

    //cout << endl << "converting to string: " << n << endl;

    //each word is a digit
    string words[3] = {"", "", ""};

    //count is a tracking variable that helps with how many words need to be
    //joined
    int count = 0;

    //here we deal with hundreds, very annoying, very messy
    if (n / 100 > 0) {
        words[0] = units[n / 100] + "_hundred";
        if (n % 100 == 0) return words[0];
        n = n % 100;
        count++;
    }

    //First check if the number is greater than 10
    if (n / 10 == 0) {
        words[count] = units[n];

        //add and when appropriate
        if (british && count > 0) words[count].insert(0, "and_");
        count++;
        return join(words + 0, words + count, '_');
    }//If it's not greater than 10, then is it between 10 and 20 non-inclusive?
    else if (n > 10 && n < 20) {
        words[count] = teens[n % 10 - 1];
        if (british && count > 0) words[count].insert(0, "and_");
        count++;
        return join(words + 0, words + count, '_');
    }//Then is it 10?
    else if (n == 10) {
        words[count] = decades[0];
        if (british && count > 0) words[count].insert(0, "and_");
        count++;
        return join(words + 0, words + count, '_');
    }//Ok, then it must be strictly greater than 19
    else {

        //cout << "decades: " << decades[n /10 -1] << endl;
        words[count] = decades[n / 10 - 1];
        if (british && count > 0) words[count].insert(0, "and_");
        if (n % 10 != 0) {
            if (british) words[count].append("-");
            else words[count].append("_");
            words[count].append(units[n % 10]);
        }
        count++;

        return join(words + 0, words + count, '_');
    }


}

/**
 * read_number takes the input string (inString), which may be a British style
 * string, and returns the value of the number as an int total
 * If the input string is a negative number i.e  ‘negative’ is the first element 
 * in the input string then the total will change sign - be multiplied by -1
 * 
 * Paramters:
 * -inString: the text of the number to read, with '_' between words
 * 
 * Returns:
 * An integer value that is equivalent to inString
 */

int Wordnum::read_number(string inString) {
    //reads input n string and converts each element to lower case
    //cout << "reading number: " << inString << endl;
    int sign = 1;
    int total = 0;

    //prep string to lower case
    for (int i = 0; i < inString.length(); i++) {
        inString[i] = tolower(inString[i]);
    }

    //convert British to normal
    while (inString.find("_and") != string::npos) {
        inString.erase(inString.find("_and"), 4);
    }

    while (inString.find("-") != string::npos) {
        inString.replace(inString.find("-"), 1, "_");
    }

    string words[16]; // enough for longest text

    string* word = split(inString, words, '_'); //calls split function

    for (int i = 0; i < 16; i++){
        //cout << words[i] << endl;
    }
    //index of a found word
    int startIndex = 0;

    //lets deal with negative numbers here
    if (words[0] == "negative") {
        sign = -1;
        words[0].clear();
        startIndex = 1;
    }

    for (int i = 0; i < 16; i++) {
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
                //cout << triadTotal << endl;
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
    total += getTriad(words, startIndex, 15);

    //cout << "number read was: " << total*sign << endl;
    return total * sign;

}

/* Once the indices that represents a triad are located, getTriad()
 * will convert the words pointed to by the indices into an integer value
 * This function does not return the actual place value of the triad
 * Anything searched through will be erased afterwards, BEWARE
 *
 * Parameters:
 * -words: an array of words
 * -start: index of where to start searching in words
 * -end: index of where to stop the search
 *
 * Returns:
 * An integer value that is equivalent to the triad given.
 */
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