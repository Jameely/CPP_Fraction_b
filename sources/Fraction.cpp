#include <stdexcept>
#include <iostream>
#include "Fraction.hpp"
#include <typeinfo> // For typeid(...)
#include <sstream>
#include <numeric>
using namespace ariel;
using namespace std;

namespace ariel{
        static constexpr double ROUNDED = 1000; //must round to the first 3 digits after the point.
        Fraction:: Fraction(int numerator ,int denominator):numerator(numerator),denominator(denominator){
                if (denominator == 0){
                        throw std::invalid_argument("Division by Zero Error!");
                }
        }
        Fraction:: Fraction(int num):numerator(num),denominator(1){}
        Fraction:: Fraction(double num):numerator(static_cast<int>(num*ROUNDED)),denominator(static_cast<int>(ROUNDED)){
            double rounded = round(num * ROUNDED) / ROUNDED;
            int n = static_cast<int>(rounded * ROUNDED);
            int d = static_cast<int>(ROUNDED);
            numerator = n;
            denominator = d;
        }
        Fraction:: Fraction(float num):numerator(static_cast<int>(num*ROUNDED)),denominator(static_cast<int>(ROUNDED)){}        
        Fraction:: Fraction(){
                this->denominator=1;
                this->numerator=0;
        }

        int Fraction::getNumerator(){return this->numerator;}     // Getter
        int Fraction::getDenominator(){return this->denominator;} // Getter

        void Fraction::simplify(){ // Help function to reduce the fraction after/before every Calculation
                int gcd = std::__gcd(numerator,denominator);
                denominator/=gcd;
                numerator/=gcd;
                } 

        /*
        in this function we implement the operatotr + between two fractions.
        use the int64_t to handle with large numbers and before the Answer we assert that there is no overflow
        */
        Fraction operator+(const Fraction & fraction1, const Fraction &fraction2){
                int lcm = std::lcm(fraction1.denominator,fraction2.denominator);
                int64_t DENO = static_cast<int64_t>(lcm);
                int64_t num1=static_cast<int64_t> (fraction1.numerator * (DENO / fraction1.denominator));
                int64_t num2=static_cast<int64_t> (fraction2.numerator * (DENO / fraction2.denominator));
                int64_t sum = num1+num2;
                if(DENO > std::numeric_limits<int>::max() || DENO < std::numeric_limits<int>::min() ||
                   num1 > std::numeric_limits<int>::max() || num1 < std::numeric_limits<int>::min() ||
                   num2 > std::numeric_limits<int>::max() || num2 < std::numeric_limits<int>::min() ||
                   sum  > std::numeric_limits<int>::max() || sum  < std::numeric_limits<int>::min() ){
                        throw std::overflow_error("Overflow during addition");
                   }
                Fraction temp(static_cast<int>(sum),DENO);
                temp.simplify();
                return temp;
        }

        // int + fraction
        Fraction operator+(const int& num, const Fraction& frac) {
            Fraction temp(num);
            Fraction res = temp+frac;
            res.simplify();
            return res;
        }
        //Fraction + int
        Fraction operator+(const Fraction& frac,const int& num) {
            Fraction temp(num);
            Fraction res = temp+frac;
            res.simplify();
            return res;
        }
        
        //Fraction + double 
        
        Fraction operator+(const Fraction& frac,const double& num) {
                Fraction temp(num);
                Fraction res=frac+temp;
                res.simplify();
                return res;
        }  
        // double + Fraction
        Fraction operator+(const double& num, const Fraction& frac) {
                Fraction Temp(num);
                Fraction res = frac+Temp;
                res.simplify();
                return res;
        }
        /*
        in this function we implement the operatotr - between two fractions.
        use the long long int to handle with large numbers and before the Answer we assert that there is no overflow
        */
        Fraction operator-(const Fraction &fraction1 , const Fraction &fraction2){
                int lcm = std::lcm(fraction1.denominator,fraction2.denominator);
                long long int DENO = static_cast<long long int>(lcm);
                long long int num1=static_cast<long long int> (fraction1.numerator * (DENO / fraction1.denominator));
                long long int num2=static_cast<long long int> (fraction2.numerator * (DENO / fraction2.denominator));
                int64_t sum = num1-num2;

                if(DENO > std::numeric_limits<int>::max() || DENO < std::numeric_limits<int>::min() ||
                   num1 > std::numeric_limits<int>::max() || num1 < std::numeric_limits<int>::min() ||
                   num2 > std::numeric_limits<int>::max() || num2 < std::numeric_limits<int>::min() ||
                   sum  > std::numeric_limits<int>::max() || sum  < std::numeric_limits<int>::min() ){
                        throw std::overflow_error("Overflow during subtraction");
                   }
                Fraction temp(static_cast<int>(sum),DENO);
                temp.simplify();
                return temp;
        }         
        
        //int - Fraction
        Fraction operator-(const int fraction1 , const Fraction &fraction2){
                Fraction temp1(fraction1);
                Fraction result = temp1 - fraction2;
                return result;
        }
        
        //Fraction - int 
        Fraction operator-(const Fraction &fraction1 , const int fraction2){
                Fraction temp1(fraction2);
                Fraction result = fraction1 - temp1;
                return result;

        }
        
        //double - fraction 
        Fraction operator-(const double fraction1 , const Fraction &fraction2){
                Fraction temp1(fraction1);
                Fraction result = temp1 - fraction2;
                return result;
        }
        //fraction - double
        Fraction operator-(const Fraction &fraction1 , const double fraction2){
                Fraction temp1(fraction2);
                Fraction result = fraction1 - temp1;
                return result;
        }
        /*
        in this function we implement the operatotr * between two fractions.
        before we begainning we must reduce the fractions to handle with large numbers (numbers that close to the max int)
        use the long long to handle with large numbers and before the Answer we assert that there is no overflow
        */
        Fraction operator*(const Fraction &fraction1, const Fraction &fraction2) {
                Fraction temp1(fraction1);
                Fraction temp2(fraction2);
                temp1.simplify();
                temp2.simplify();
        long long numer = static_cast<long long>(temp1.numerator) * temp2.numerator;
        long long denom = static_cast<long long>(temp1.denominator) * temp2.denominator;
        if (numer > std::numeric_limits<int>::max() || numer < std::numeric_limits<int>::min() ||
                denom > std::numeric_limits<int>::max() || denom < std::numeric_limits<int>::min()) {
                throw std::overflow_error("Overflow during multiplication");
        }
        Fraction result(static_cast<int>(numer), static_cast<int>(denom));
        result.simplify();
        return result;
        }

        // int * Fraction
        Fraction operator*(const int fraction1 , const Fraction &fraction2){
                Fraction temp1(fraction1);
                Fraction result = temp1*fraction2;
                result.simplify();
                return result;
        }
        // Fraction * int
        Fraction operator*(const Fraction &fraction1 ,const int fraction2){
                Fraction temp2(fraction2);
                Fraction result = temp2*fraction1;
                result.simplify();
                return result;                

        }
        // double * Fraction
        Fraction operator*(const double fraction1 , const Fraction &fraction2){
                Fraction temp1(fraction1);
                Fraction result = temp1*fraction2;
                result.simplify();
                return result;
        }
        //Fraction *double
        Fraction operator*(const Fraction &fraction1 , const double fraction2){
                Fraction temp2(fraction2);
                Fraction result = temp2*fraction1;
                result.simplify();
                return result;  
        }

        /*
        in this function we implement the operatotr / between two fractions.
        before we begainning we must reduce the fractions to handle with large numbers (numbers that close to the max int)
        use the long long to handle with large numbers and before the Answer we assert that there is no overflow
        */
        Fraction operator/(const Fraction &fraction1 , const Fraction &fraction2){
                Fraction temp1(fraction1);
                Fraction temp2(fraction2);
                temp1.simplify();
                temp2.simplify();
                int max = numeric_limits<int>::max();
                if(temp2.numerator==0){
                        throw std::runtime_error("Can't divide by zero");
                }
                if((temp1.numerator!=0 && temp2.denominator !=0) &&(temp1.numerator == max || temp2.denominator== max)){
                        throw std::overflow_error("Overflow during deviding!");
                }
                int Nume = temp1.numerator * temp2.denominator;
                int Deno = temp1.denominator * temp2.numerator;
                Fraction result(Nume,Deno);
                result.simplify();
                return result;
        }
        //Fraction / double
        Fraction operator/(const Fraction &fraction1 , const double fraction2){
                if(fraction2==0){
                        throw std::runtime_error("Can't Divide by Zero");
                }
                Fraction frac2(fraction2);
                Fraction result = fraction1/frac2;
                result.simplify();
                return result;
        }
        //float / Fraction
        Fraction operator/(const float fraction1 , const Fraction &fraction2){
                if(fraction2.numerator==0){
                        throw std::runtime_error("Can't Divide by Zero");
                }
                Fraction frac1(fraction1);
                Fraction result = frac1/fraction2;
                result.simplify();
                return result;
        }
        //post-increment operator ++
        Fraction& Fraction:: operator++(){
                this->numerator+=this->denominator;
                simplify();
                return (*this);
        }
        //pre-increment operator ++
        Fraction Fraction:: operator++(int num){
                Fraction old(*this);
                numerator+=denominator;
                simplify();
                return old;
                
        }
        //post-increment operator --
        Fraction& Fraction:: operator--(){
                this->numerator-=this->denominator;
                simplify();
                return (*this);
        }
        //pre-increment operator --
        Fraction Fraction:: operator--(int num){
                Fraction old(*this);
                numerator-=denominator;
                simplify();
                return old;
        }

        // == operator equals
        bool operator==(const Fraction &fraction1 , const Fraction &fraction2){
                double first  = static_cast<double>(fraction1.numerator)/fraction1.denominator;
                double second = static_cast<double>(fraction2.numerator)/fraction2.denominator;
                bool result = (std::round(first*ROUNDED)==std::round(second*ROUNDED));
                return result;
        }
        //!= operator not equals
        bool operator!=(const Fraction& fraction1, const Fraction& fraction2){
                return !(fraction1==fraction2);
        }
        /*
        in the next 8 function we implement the compare operators (with differnce data types)
        */
        bool operator>(const Fraction& fraction1 , const Fraction& fraction2){
                bool result = fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator;
                if (fraction1.denominator < 0 && fraction2.denominator > 0)
                {
                        return !result;
                }
                if(fraction2.denominator < 0 && fraction1.denominator > 0){
                        return !result;
                }
                return result;
        }
        bool operator>(const Fraction& fraction1 , const float num){
                Fraction fraction2(num);
                bool result = fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator;
                if (fraction1.denominator < 0 && fraction2.denominator > 0)
                {
                        return !result;
                }
                if(fraction2.denominator < 0 && fraction1.denominator > 0){
                        return !result;
                }
                return result;
        }
        bool operator<(const Fraction& fraction1 , const Fraction& fraction2){
                bool result = fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator;
                if (fraction1.denominator < 0 && fraction2.denominator > 0)
                {
                        return !result;
                }
                if(fraction2.denominator < 0 && fraction1.denominator > 0){
                        return !result;
                }
                return result;
        }
        bool operator<(const Fraction& fraction1 , const float num){
                Fraction fraction2(num);
                bool result = fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator;
                if (fraction1.denominator < 0 && fraction2.denominator > 0)
                {
                        return !result;
                }
                if(fraction2.denominator < 0 && fraction1.denominator > 0){
                        return !result;
                }
                return result;
        }
        bool operator>=(const Fraction& fraction1 , const Fraction& fraction2){
                return (fraction1>fraction2 || fraction1==fraction2);
        }
        bool operator>=(const Fraction& fraction1 , const float fraction2){
                return (fraction1>fraction2 || fraction1==fraction2);
        }
        bool operator<=(const Fraction& fraction1 , const Fraction& fraction2){
                return (fraction1<fraction2 || fraction1==fraction2);
        }
        bool operator<=(const Fraction& fraction1 , const float fraction2){
                return (fraction1<fraction2 || fraction1==fraction2);

        }
        //output operator
        std::ostream& operator<<(std::ostream& osin, const Fraction& frac){
                Fraction temp(frac);
                temp.simplify();
                if (temp.denominator>=0){
                        osin <<temp.numerator << "/" << temp.denominator;
                }
                else{
                        osin << "-" << std::abs(temp.numerator) << "/" << std::abs(temp.denominator);
                }
                return osin;
                }
        //input operator
        std::istream& operator>>(std::istream& inst, Fraction& frac){
                int numerator   =1;
                int denominator =1;
                if(!(inst >> numerator)){
                        throw std::runtime_error("Invalid input numerator!");
                }
                if(!(inst >> denominator)){
                        throw std::runtime_error("Invalid input denominator!");
                }
                if(denominator == 0){
                        throw std::runtime_error("Can't Divide by Zero");
                }
                frac = Fraction(numerator,denominator);
                frac.simplify();
                return inst;
}
}