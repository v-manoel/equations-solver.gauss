#include "gauss_elim.hpp"
#include "equation.hpp"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

GaussElimination::GaussElimination(vector<Equation> _equations)
{
    equations = _equations;
}

bool GaussElimination::addEquation(Equation equation)
{
    equations.push_back(equation);
}

bool GaussElimination::EquationsAsMatrix()
{
    //Checks if this method was called before yet
    if(matrix.size())
    {
        cout << "Error - the matrix has already been defined " << endl;
        return false;
    }
    
    //Selects the bigger equation to define the matrix size
    for(unsigned i =0; i < equations.size(); i++)
        if(equations[i].getVariables().size() > variables.size())
        {
            variables = equations[i].getVariables();
        }

    //Check if the equation system makes a square matrix
    //The number of equations defines the rows size while the number of variables defines the cols size
    if(equations.size() != variables.size())
    {
        cout << "Error - The number of equations and number of variables don't match" << endl;
        return false;
    }

    //Builds the matrix with the matrix_size
    for(unsigned equation =0; equation < equations.size(); equation++)
    {
        vector<double> line;
        for(unsigned member =0; member < variables.size(); member++)
        {
            line.push_back(equations[equation].getElements()[variables[member]]);
        }
        //adds the result element in the last col
        line.push_back(equations[equation].getResult());
        matrix.push_back(line);
    }

    cout << "Augmented Matrix Builded !" << endl;
    printMatrix();

    return true;
}

bool GaussElimination::buildEchelonMatrix()
{
    
    //Try to Build the Augmented matrix 
    if(!EquationsAsMatrix())
        return false;

    //the number of lines is defined by the number of equations
    const unsigned n_lines = matrix.size();
    
    //The number of columns is defined by the maximum number of variables + one column for the results
    const unsigned n_cols = variables.size() +1; 

    //control variable to check pivot status
    bool pivo_is_zero = false;

    // Swap lines to organize pivos
    for(unsigned line = 0; line < n_lines; line++)
    {
        // If this line pivo is zero
        if(!matrix[line][line])
        {
            pivo_is_zero = true;
            for(unsigned swp_line = 0; swp_line < n_lines; swp_line++)
            {
                if(matrix[swp_line][line] && matrix[line][swp_line])
                {
                    vector<double> line_buffer = matrix[line];
                    matrix[line] = matrix[swp_line];
                    matrix[swp_line] = line_buffer;
                    pivo_is_zero = false;
                }
            }
        }

        if(pivo_is_zero)
        {
            cout << "Error - In position "<< matrix[line][line] <<" the pivot is zero !" << endl;
            return false;
        }
        

        cout << "Pivot configured" << endl;
        printMatrix();

        //Fill all cells bellow matrix[line][line] with zero
        for(unsigned next_line = line +1; next_line < n_lines; next_line++)
        {
            float k = matrix[next_line][line] / matrix[line][line];
            //Sum lines
            for(unsigned col = 0; col < n_cols; col++)
            {
                matrix[next_line][col] -= k * matrix[line][col];
            }
            
        }
    }

    cout << "Echelon Matrix Builded" << endl;
    printMatrix();

    return true;
}

map<char,double> GaussElimination::solveEquationSys(string& output_filename)
{
    map<char,double> equation_solution;
    
    if(!buildEchelonMatrix())
    {
        cout << "Error - it was not possible to build the Echelon Matrix" << endl;
        return equation_solution;
    }

    //the number of lines is defined by the number of equations
    const unsigned n_lines = matrix.size();
    
    //The number of columns is defined by the maximum number of variables + one column for the results
    const unsigned n_cols = variables.size() +1;

    //runs the matrix from the last to the first line, calculating the value of each variable
    for(int line = n_lines -1; line >= 0; line--)
    {
        // multiplies each variable by its coefficient, moves it to the side of the result of the equation (multiplying it by -1) and adds it to the result
        float sum = 0.0;
        for(int var = n_cols -2; var >= 0; var--) //Avoid the result columns
        {
            sum += -1*matrix[line][var]*equation_solution[variables[var]];
        }
        
        //adds the value of the result of the equation to the total sum and isolates the variable, dividing the total result by the coefficient of the variable
        equation_solution[variables[line]] = sum + matrix[line][n_cols -1];
        equation_solution[variables[line]] /= matrix[line][line];

    }

    //Writes the solution
    if(!equation_solution.size())
    {
        cout << "We can't solve your problem !";
        return equation_solution;
    }


    ofstream file(output_filename.c_str(), ofstream::app);
    for(auto const& element : equation_solution) {
        file << element.first << " = " << element.second << endl;
    }
    file << "< ------- end solution ------- >" << endl;
    file.close();

    return equation_solution;
}

void GaussElimination::printMatrix()
{
    for(unsigned i=0; i < matrix.size(); i++)
    {
        for(unsigned j=0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<double>> GaussElimination::getMatrix()
{
    return matrix;
}

vector<char> GaussElimination::getVariables()
{
    return variables;
}

bool GaussElimination::eraseAllEquations()
{
    equations.clear();
    variables.clear();
    matrix.clear();
}