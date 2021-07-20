#include "gauss_elim.hpp"
#include "equation.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

vector<Equation> load_equations_file(string& filename);

int main()
{

    char op = ' ';

    while(op != '0')
    {

    string in_filename, out_filename;
    //cout << "Type the Equations filename: ";
    //cin >> in_filename; //
    in_filename = "equations.txt";
    
    //cout << "Now Type a Name for the Solutions File: ";
    //cin >> out_filename; //
    out_filename = "solution.txt";

    vector<Equation> equations = load_equations_file(in_filename);
    GaussElimination gauss(equations);
    Equation result(gauss.solveEquationSys(out_filename));

    cout << result.toString() << endl;

    cout << "Do Solve Other Equations System ? (0) Não" << endl;
    cin >> op;
    }
}

vector<Equation> load_equations_file(string& filename)
{
    vector<Equation> equations;

    // Reads All equations into equations file
    ifstream equationsAsText(filename.c_str());
    string textline;
    while(getline(equationsAsText,textline))
    {
        // transforms an text in a equation
        equations.push_back(Equation(textline));
    }
    equationsAsText.close();
    return equations;
}