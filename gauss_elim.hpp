#ifndef _GAUSS_ELIM_HPP_
#define _GAUSS_ELIM_HPP_

#include "equation.hpp"
#include <map>
#include <string>
#include <vector>

using namespace std;
class GaussElimination
{
    private:
        //Stores all equations of a equation system
        vector<Equation> equations;

        //Stores all variables symbols of the system 
        vector<char> variables;

        //Stores 
        vector<vector<double>> matrix;

    protected:
        bool EquationsAsMatrix();
        bool buildEchelonMatrix();

    public:
        GaussElimination(vector<Equation> _equations);
        bool addEquation(Equation equation);
        map<char,double> solveEquationSys(string& output_filename);
        void printMatrix();
        vector<vector<double>> getMatrix();
        vector<char> getVariables();
        bool eraseAllEquations();

        

};

#endif