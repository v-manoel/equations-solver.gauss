#ifndef _EQUATION_HPP_
#define _EQUATION_HPP_

#include <map>
#include <string>
#include <vector>

using namespace std;

//Represents a equation and its methods
class Equation
{
    private:
        //Stores variables, coefficients, and result of an equation as a list of key-value
        map<char,double> elements; 

    public:
        Equation(); //Builds an empty equation object
        Equation(string& text); //Builds an equation by a text
        Equation(map<char,double> _elements); //Builds an equation by a elements list

        string toString(); //Turns the equation object into text
        map<char,double> parseEquation(string& text); //Turns text into a equation elements struct
        vector<char> getVariables(); //Builds a vector of characters that contains equation's variables 
        vector<double> getCoefficients(); //Builds a vector of double values that contais equation's coefficients
        double getResult(); //Gives the equation's result
        map<char,double> getElements(); //Gives a list with all equation elements
};

#endif
