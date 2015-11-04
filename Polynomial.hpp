/*
 * Polynomial.hpp
 *
 *      Author: "Hans Dulimarta <dulimarh@cis.gvsu.edu>"
 */

#ifndef POLYNOM_H_
#define POLYNOM_H_

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <climits>
#include <math.h>

#include <unordered_map>   // we use a HASH MAP

using namespace std;

template<typename T>
class Polynomial {
private:
    /* coeffient and exponent of the polynom are stored as a pair<> */
    vector<pair<T,int>> poly;

public:
    /* each term is a pair of coefficient and exponent, the type of
     * coefficient is determined by <T>, but exponent is always an integer */

    Polynomial() {
    }

    Polynomial(const string& input) {
        load(input);
    }

    Polynomial(const Polynomial& other) {
        poly = other.poly;
    }

    ~Polynomial()
    {
        poly.clear();
    }

    Polynomial& operator= (const Polynomial& other) {
        poly = other.poly;
        return *this;
    }

    /* TODO: complete this function to multiply "this" polynomial (of M
     * terms) with the "other" polynomial (of N terms). Use the first 
     * technique described in question 5.13: (a) store the MN terms of the
     * product (b) sort them (c) combine like terms
     */
    Polynomial operator* (const Polynomial& other) const {
        Polynomial result;
        for(auto it = this->poly.begin(); it != poly.end(); ++it ){
            for(auto it2 = other.poly.begin(); it2 != poly.end(); ++it2) {
                auto a = it->first * it2->first;
                auto b = it->second * it2->second;

                for(auto it3 = result.poly.begin(); it3 != result.poly.end(); ++it3) {

                }
            }
        }

        return result;
    }

    /* TODO: complete this function to multiply "this" polynomial (of M
     * terms) with the "other" polynomial (of N terms). Use the alternate 
     * technique described in question 5.13. Hint, use a map (or
     * unordered_map) to merge like terms as they are computed.
     */
    Polynomial operator% (const Polynomial& other) const {
        Polynomial result;
        /* TODO: write your algorithm here */

        return result;
    }

    /* Return the highest degree in the polynomial */
    int maxDegree() const {
        return poly.front.second;
    }

    /* return the k-th exponent or zero when the polynom has no terms */
    int operator% (int k) {
        /* TODO: write your code here (around 3-4 lines of code) */
        if(poly.size() == 0){
            return 0;
        }
        return poly[k].second;
    }

    /* return the k-th coefficient, or zero when the polynom is empty */
    T operator[] (int k) const {
        /* TODO: write your code here (around 3-4 lines of code) */
        if(poly.size() == 0){
            return 0;
        }
        return poly[k].first;
    }

    /* TODO evaluate the polynom for the given value */
    T operator() (T arg) const {
        T eval = 0;
        for(int i = 0; i < poly.size(); i++){
           eval += pow(poly[i].first, poly[i].second);
        }
        return eval;
    }

    /* The following function "object" is needed for sorting
     * the polynomial terms in descending order of the exponent */
    struct exponent_comparator {
        bool operator() (const pair<T,int>& a, const pair<T,int>& b) {
            return a.second > b.second;
        }
    };

private:
    /* The load function reads in a string representation of a polynomial
     * and creates a vector of "polynomial terms".
     * The input string has the following format:
     *
     * [coeff int] [coeff int] .....
     *
     * For instance,   3x^5 - 7x^2 + 11 can be represented as one of 
     * the following string (whitespaces do not matter)
     *
     * [3 5] [-7 2] [11 0]
     * [3 5]   [-7   2]  [11 0]
     */
    void load(const string& polystring) {
        /* use a string input stream */
        stringstream input (polystring);
        const int L = polystring.length();
        T coeff;
        int expo = INT_MIN, last_expo;
        bool sortNeeded = false;

        /* skip the input, upto and including the '[' */
        input.ignore(L, '[');
        last_expo = expo;

        /* our string input stream is like a file, so we can check for
         * "end-of-file".... */
        while (!input.eof()) {
            input >> coeff >> expo;
            input.ignore(L, ']');

            if (fabs(coeff) > 1e-6)  /* include only non-zero coeffs */
            {
                poly.push_back(make_pair(coeff,expo));
                if (expo > last_expo)
                    sortNeeded = true;
                last_expo = expo;
            }
            input.ignore(L, '[');
        }

        /* sort the terms in increasing order of exponents */
        if (sortNeeded)
            sort(poly.begin(), poly.end(), exponent_comparator());
    }
};

#endif /* POLYNOM_H_ */