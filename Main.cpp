//
// Created by Amir on 11/04/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Matrix.hpp"
using namespace zich;

int main() {

    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size
    cout << a << endl;
    /* prints [1 0 0]
             [0 1 0]
             [0 0 1]*/

    cout << (-a) << endl;
    /* prints [-1 0 0]
             [0 -1 0]
             [0 0 -1]*/
    cout << (3*a) << endl;
    /* prints [3 0 0]
              [0 3 0]
              [0 0 3]*/

    Matrix b{arr, 3, 3};
    a *= -3;
    cout << (a+b) << endl;  // prints the 0 matrix
    cout << (b-a) << endl;
    /* prints [6 0 0]
              [0 6 0]
              [0 0 6]*/


    //input and output
    Matrix inMat1{{0},1,1};
    cout << "Enter your first matrix:  " ;
    cin >> inMat1;
    cout << "Your Matrix is: \n" << inMat1 << endl;
    Matrix inMat2{{0},1,1};
    cout << "Enter your second matrix:  ";
    cin >> inMat2;
    cout << "Your  second Matrix is: \n" << inMat2 << endl;
    cout << "**" <<endl;
    cout << "+ operator \n" << inMat1+inMat2 <<endl;
    cout << "- operator \n" << inMat1-inMat2 <<endl;
    cout << "* operator \n" << inMat1*inMat2 <<endl;
    cout << "**" <<endl;
    double scalar;
    cout << "Choose a scalar: " ;
    cin >> scalar;
    cout << "Your first matrix multiplication by the scalar is: \n" << scalar * inMat1 << endl <<endl;
    cout << "Your second matrix multiplication by the scalar is: \n" << scalar * inMat2 << endl;
    cout << "End of main!" << endl;
    return 0;
}