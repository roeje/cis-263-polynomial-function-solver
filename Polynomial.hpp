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


public:
    /* each term is a pair of coefficient and exponent, the type of
     * coefficient is determined by <T>, but exponent is always an integer */
    vector<pair<T,int>> poly;

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
//        typename vector<std::pair<T, int>>::const_iterator it;

        for(auto it = poly.begin(); it != poly.end(); ++it ){
            for(auto it2 = other.poly.begin(); it2 != other.poly.end(); ++it2) {
                auto a = (it->first * it2->first);
                auto b = (it->second + it2->second);
                bool flag = true;
                for(auto it3 = result.poly.begin(); it3 != result.poly.end(); ++it3) {
                    if (it3->second == b) {
                        it3->first += a;
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    result.poly.push_back(make_pair(a,b));
                }

            }
        }
        sort(result.poly.begin(), result.poly.end(), exponent_comparator());
        return result;
    }

    /* TODO: complete this function to multiply "this" polynomial (of M
     * terms) with the "other" polynomial (of N terms). Use the alternate
     * technique described in question 5.13. Hint, use a map (or
     * unordered_map) to merge like terms as they are computed.
     */
    Polynomial operator% (const Polynomial& other) const {
        Polynomial result;
        map<int, float> pairMap;
        for(auto it = poly.begin(); it != poly.end(); ++it){
            for(auto it2 = other.poly.begin(); it2 != other.poly.end(); ++it2) {
                auto coef = it->first * it2->first;
                auto exp = it->second + it2->second;
                if(pairMap.find(exp) == pairMap.end()) {
                    pairMap[exp] = coef;
                }
                else {
                    pairMap[exp] += coef;
                }
            }
        }
        for(auto itr = pairMap.rbegin(); itr != pairMap.rend(); ++itr) {
            result.poly.push_back(make_pair(itr->second, itr->first));
        }
        return result;
    }

    /* Return the highest degree in the polynomial */
    int maxDegree() const {
        if(poly.empty()) {
            return 0;
        }
        else {
            return poly.front().second;
        }

    }

    /* return the k-th exponent or zero when the polynom has no terms */
    int operator% (int k) {
        /* TODO: write your code here (around 3-4 lines of code) */
        if(poly.empty()){
            return 0;
        }
        else {
            return poly.at(k).second;
        }

    }

    /* return the k-th coefficient, or zero when the polynom is empty */
    T operator[] (int k) const {
        /* TODO: write your code here (around 3-4 lines of code) */
        if(poly.empty()){
            return 0;
        }
        try{
            return poly.at(k).first;
        }catch(const out_of_range& ex ){
            return 0;
        }

    }

    /* TODO evaluate the polynom for the given value */
    T operator() (T arg) const {
        T eval = 0;
        for(auto itr = this->poly.begin(); itr != this->poly.end(); ++itr) {
            eval += (itr->first * pow(arg, itr->second));
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