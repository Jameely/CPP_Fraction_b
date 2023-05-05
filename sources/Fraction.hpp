#pragma once
#include <stdexcept>
#include <iostream>
#include <algorithm> // For __gcd; taken from the internet
#include <typeinfo> // For typeid(...)
#include <sstream>
#include <cmath>
// check the & in all function
using namespace std;
namespace ariel{
    class Fraction    // the class Fraction
    {
    private: 
        int numerator; 
        int denominator;
    public: 
        Fraction(int numerator ,int denominator);
        Fraction(int num);
        Fraction(double num);
        Fraction(float num);       
        Fraction();
        int getNumerator();
        int getDenominator();

        void simplify();

        friend Fraction operator+(const Fraction &fraction1, const Fraction &fraction2);
        // int +
        friend Fraction operator+(const int& NUM, const Fraction& fraction);
        //+ double
        friend Fraction operator+( const Fraction& frac,const double& NUM);  
        // double +
        friend Fraction operator+(const double& NUM, const Fraction& frac);
        friend Fraction operator+(const Fraction& frac,const int& num); 

///////////////////////////////////////////////////////////////////////////////////////////////

        friend Fraction operator-(const Fraction &fraction1 , const Fraction &fraction2);
        friend Fraction operator-(int fraction1 , const Fraction &fraction2);
        friend Fraction operator-(const Fraction &fraction1 , int fraction2);
        friend Fraction operator-(double fraction1 , const Fraction &fraction2);
        friend Fraction operator-(const Fraction &fraction1 ,double fraction2);

///////////////////////////////////////////////////////////////////////////////////////////////////////
        friend Fraction operator*(const Fraction &fraction1 , const Fraction &fraction2);
        friend Fraction operator*(int fraction1 , const Fraction &fraction2);
        friend Fraction operator*(const Fraction &fraction1 ,int fraction2);
        friend Fraction operator*(double fraction1 , const Fraction &fraction2);
        friend Fraction operator*(const Fraction &fraction1 , double fraction2);

//////////////////////////////////////////////////////////////////////////////////////////////////////

        friend Fraction operator/(const Fraction &fraction1 , const Fraction &fraction2);
        friend Fraction operator/(const Fraction &fraction1 , double fraction2);
        friend Fraction operator/(float fraction1 , const Fraction &fraction2);




///////////////////////////////////////////////////////////////////////////////////////////////////////

        Fraction& operator++();
        Fraction operator++(int num);
        Fraction& operator--();
        Fraction operator--(int num);
////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend bool operator==(const Fraction &fraction1 , const Fraction &fraction2);
        friend bool operator!=(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator>(const Fraction& fraction1 , const Fraction& fraction2);
        friend bool operator>(const Fraction& fraction1 , float fraction2);
        friend bool operator<(const Fraction& fraction1 , const Fraction& fraction2);
        friend bool operator<(const Fraction& fraction1 , float fraction2);
        friend bool operator>=(const Fraction& fraction1 , const Fraction& fraction2);
        friend bool operator>=(const Fraction& fraction1 , float fraction2);
        friend bool operator<=(const Fraction& fraction1 , const Fraction& fraction2);
        friend bool operator<=(const Fraction& fraction1 , float fraction2);        

//////////////////////////////////////////////////////////////////////////////////////////
        friend std::ostream& operator<<(std::ostream& osin, const Fraction& frac);
        friend std::istream& operator>>(std::istream& inst, Fraction& frac);

    };
}