#include "equation.hpp"
#include <map>
#include <vector>
#include <sstream>

using namespace std;

Equation::Equation(string& text)
{
    elements = parseEquation(text);
}

Equation::Equation(map<char,double> _elements)
{
    elements = _elements;
}

string Equation::toString()
{
    stringstream text_equation;

    text_equation << "";
    for (map<char,double>::iterator it=elements.begin(); it!=elements.end(); ++it)
    {
        text_equation << (it->second > 0 ? "+" : "") << it->second  << it->first << " ";
    }
    text_equation << endl;

    return text_equation.str();
}


map<char,double> Equation::parseEquation(string& text)
{
    map<char,double> equation_elements;
    
    //Removing spaces:
    size_t found =text.find(" ");
    while(found != string::npos)
    {
        text.erase(found,1);
        found =text.find(" ");
    }

    /*
    Building the equation:
        Checks if each string character is an alphabetic or a number.
        An alphabetic character defines the end position of a number.
        A number starts at the alphabetic position +1, and ends at the next alphabetic position -1.

        To check if a character is alphabetic, its correspondent ASCII value is used. 
        By the ASCII table, an alphabetic character has a value between 96 and 123 or 128 and 155

        A number is defined by a list of characters that starts at begin_number and ends at an alphabetic position
        if the number interval is smaller than 2 its means there is an implicit number (+1 or -1).

        the method ends up finding the result value of the equation that starts at the symbol "=" and ends at the last character of the string
    */
    unsigned begin_number = 0;
    for(unsigned index = 0; index < text.size(); index++)
    {
        //Checks if the character is alphabetic, it means it is a variable. 
        //Then there is a number that starts in begin_number and ends in the variable/char index.
        if((int(text[index]) > 96 && int(text[index]) < 123) || (int(text[index]+32) > 96 && int(text[index]+32) < 123))
        {
            unsigned number_size = index -begin_number;
            //Check if there is a implicit coeficient
            if(number_size < 2)
            {
                if(!number_size || text[begin_number] == '+')
                    equation_elements[text[index]] += 1.0;
                else if(text[begin_number] == '-')
                    equation_elements[text[index]] += -1.0;
            }

            equation_elements[text[index]] += atof(text.substr(begin_number, number_size).c_str()); //adds number of characters index - begin_number
            begin_number = index +1;
        }    
    }

    //Stores the result value
    unsigned result_index = text.find("=") + 1;
    equation_elements['='] += atof(text.substr(result_index, (text.size() - result_index)).c_str()); 

    return equation_elements;

}

vector<char> Equation::getVariables()
{
    vector<char> vars;

    for(auto const& element : elements) {
    if(element.first != '=')
        vars.push_back(element.first);
    }
    return vars;
}

vector<double> Equation::getCoefficients()
{
    vector<double> coeffs;

    for(auto const& element : elements) {
    if(element.first != '=')
        coeffs.push_back(element.second);
    }
    return coeffs;
}

double Equation::getResult()
{
    return elements['='];
}

map<char,double> Equation::getElements()
{
    return elements;
}