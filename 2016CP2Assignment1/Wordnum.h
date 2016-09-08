/**
 * Wordnum: a class for computing with words
 *
 * Written for the topic COMP2711 Computer Programming 2
 * by Paul Calder
 * April 2015
 */

#ifndef WORDNUM_H_
#define WORDNUM_H_

#include <string>
#include <istream>
#include <ostream>
#include <iostream>

using namespace std;

/**
 * A class to read and write numbers in word form
 */

class Wordnum {
private:

    /**
     * Reads and writes number word text
     */
    static std::string write_number(int n);
    static int getTriad(string *, int, int);
    static int read_number(std::string n);
    static std::string triadToString(int n);
    static bool british;

    int value_;
    int totalTriads;

public:

    /**
     * Creates a Wordnum with the value of n
     */
    Wordnum(int n = 0) {
        value_ = n;
        int temp = value_;
        totalTriads = 1;
        while (temp / 1000 > 0) {
            totalTriads++;
            temp /= 1000;
        }
    }

    Wordnum(std::string n) {
        value_ = read_number(n);
        int temp = value_;
        totalTriads = 1;
        while (temp / 1000 > 0) {
            totalTriads++;
            temp /= 1000;
        }
    }

    //modify the class to output in british or normal format
    static void wordnumBritish();
    static void wordnumNormal();

    /**
     * Computes sum, difference, product, or quotion of n1 and n2
     */
    friend Wordnum operator+(const Wordnum& n1, const Wordnum& n2) {
        return Wordnum(n1.value_ + n2.value_);
    }

    friend Wordnum operator-(const Wordnum& n1, const Wordnum& n2) {
        return Wordnum(n1.value_ - n2.value_);
    }

    friend Wordnum operator*(const Wordnum& n1, const Wordnum& n2) {
        return Wordnum(n1.value_ * n2.value_);
    }

    friend Wordnum operator/(const Wordnum& n1, const Wordnum& n2) {
        return Wordnum(n1.value_ / n2.value_);
    }

    /**
     * Inserts or extracts a Wordnum on an IO stream
     */
    friend std::ostream& operator<<(std::ostream &out, const Wordnum& n);
    friend std::istream& operator>>(std::istream &in, Wordnum& n);

};

#endif
