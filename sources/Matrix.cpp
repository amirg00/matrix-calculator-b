/**
 * @author Amir Gillette
 * @date 30-03-22
 */

#include <sstream>
#include <stdexcept>
using namespace std;
#include "Matrix.hpp"
using namespace zich;


/**************************************************/
//==================== Methods ====================/
/**************************************************/

// Constructor
Matrix::Matrix(vector<double> matrix, int row, int col)
: _matrix(move(matrix)), _row(row), _col(col){
    if (_row <= 0 || _col <= 0) {
        throw invalid_argument("Row and col are zero/negative!");
    }
    if (_matrix.size() != _row * _col){
        throw invalid_argument("Matrix size doesn't match the given row and col.");
    }
}

// Plus operation for a matrix: mat1 + mat2
Matrix Matrix::operator+(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    vector<double> add_mat((unsigned long) (_row * _col), 0);
    for (unsigned long i = 0; i < _matrix.size(); ++i) {add_mat.at(i) = _matrix[i] + other._matrix[i];}
    Matrix add{add_mat, _row, _col};
    return add;
}

// Unary operator: +Matrix
Matrix Matrix::operator+() {
    vector<double> add_mat((unsigned long) (_row * _col), 0);
    for (unsigned long i = 0; i < _matrix.size(); ++i) {add_mat.at(i) = _matrix[i];}
    Matrix plus{add_mat, _row, _col};
    return plus;
}

// Insertion for a matrix: mat1 += mat2
Matrix& Matrix::operator+=(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    for (unsigned long i = 0; i < _matrix.size(); ++i) {_matrix.at(i) += other._matrix[i];}
    return *this;
}


// Prefix method: ++Matrix
Matrix& Matrix::operator++() {
    for (double &element : _matrix) {++element;}
    return *this;
}

// Postfix method: Matrix++
Matrix Matrix::operator++(int) {
    Matrix cpy{_matrix, _row, _col}; /* Copy of current matrix*/
    ++*this;
    return cpy;
}

// Minus operation for a matrix: mat1 - mat2
Matrix Matrix::operator-(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    vector<double> add_mat((unsigned long) (_row * _col), 0);
    for (unsigned long i = 0; i < _matrix.size(); ++i) {add_mat.at(i) = _matrix[i] - other._matrix[i];}
    Matrix add{add_mat, _row, _col};
    return add;
}

// Unary operator for minus: -Matrix
Matrix Matrix::operator-() {
    vector<double> add_mat((unsigned long) (_row * _col), 0);

    for (unsigned long i = 0; i < _matrix.size(); ++i){
        if (_matrix[i] == 0){
            add_mat.at(i) = 0;
        }
        else{
            add_mat.at(i) = _matrix[i] * (-1);
        }
    }
    Matrix minus{add_mat, _row, _col};
    return minus;
}

Matrix& Matrix::operator-=(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    for (unsigned long i = 0; i < _matrix.size(); ++i) {_matrix.at(i) -= other._matrix[i];}
    return *this;
}

// Prefix method: --Matrix
Matrix& Matrix::operator--() {
    for (double &element : _matrix) {--element;}
    return *this;
}

//Postfix method: Matrix--
Matrix Matrix::operator--(int) {
    Matrix cpy{_matrix, _row, _col}; /* Copy of current matrix*/
    --*this;
    return cpy;
}


// Matrices multiplication: mat1 * mat2
Matrix Matrix::operator*(const Matrix &other){
    if (_col != other._row) {
        throw invalid_argument("Cannot multiply by definition.!");
    }

    // Multiplication matrix's dimension by definition.
    vector<double> add_mat((unsigned long) (_row * other._col), 0);
    for (unsigned long i = 0, m = 0; i < _row; ++i) {
        for (unsigned long j = 0; j < other._col; ++j) {
            double sum = 0;
            for (unsigned long k = 0; k < _col; ++k) {
                sum += _matrix[i*(unsigned long) (_col) + k] * other._matrix[k*(unsigned long) (other._col) + j];
            }
            add_mat.at(m++) = sum;
        }
    }
    Matrix add{add_mat, _row, other._col};
    return add;
}

// mat1 *= mat2
Matrix& Matrix::operator*=(const Matrix &other){
    *this = *this * other;
    return *this;
}

// mat1 *= scalar
Matrix& Matrix::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

bool Matrix::operator>(const Matrix &other) const{
    return Matrix::compareByOperator(*this, other, ">");
}

bool Matrix::operator>=(const Matrix &other) const{
    return Matrix::compareByOperator(*this, other, ">=");
}

bool Matrix::operator<(const Matrix &other) const{
    return Matrix::compareByOperator(*this, other, "<");
}

bool Matrix::operator<=(const Matrix &other) const{
    return Matrix::compareByOperator(*this, other, "<=");
}

// Method checks if two matrices are equivalent,
// meaning that they have the same elements.
bool Matrix::operator==(const Matrix &other) const{
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    for (unsigned long i = 0; i < _matrix.size(); ++i) {
        if (_matrix[i] != other._matrix[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const{
    return !(*this == other);
}

/**************************************************/
//================== Friend Functions =============/
/**************************************************/

//Method compares by the following operator relations (">", ">=", "<", "<=").
bool Matrix::compareByOperator(const Matrix &a, const Matrix &b, const string &Operator) {
    if (a._row != b._row || a._col != b._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }

    double sumA = 0; double sumB = 0;
    for (unsigned long i = 0; i < a._matrix.size(); ++i) {
        sumA += a._matrix[i];
        sumB += b._matrix[i];
    }
    bool relation = false;
    if (Operator == ">") {relation = sumA > sumB;}
    else if (Operator == ">=") {relation = sumA >= sumB;}
    else if (Operator == "<")  {relation = sumA < sumB;}
    else if (Operator == "<=") {relation = sumA <= sumB;}
    return relation;
}

// Output method for a matrix, by a given matrix object.
ostream& zich::operator<<(ostream& os, const Matrix& matrix)
{
    /*Validation check */
    if (matrix._matrix.size() != matrix._row * matrix._col){
        throw invalid_argument("Vector size doesn't match given matrix dimension.");
    }
    if (matrix._col == 1){ /*Matrix has only one column*/
        for (unsigned long i = 0; i < matrix._matrix.size(); ++i) {
            os << '[' << matrix._matrix[i] << ']';
            if (i != matrix._matrix.size() - 1){os << '\n';}
        }
    }
    else{
        for (unsigned long i = 0; i < matrix._matrix.size(); ++i) {
            if(i == 0){
                os << '[' << matrix._matrix[i] << ' ';
            }
            else if (i == matrix._matrix.size() - 1){
                os << matrix._matrix[i] << ']';
            }
            else if ((i + 1) % (unsigned long) (matrix._col) == 0){
                os << matrix._matrix[i] << ']' << '\n' << '[';
            }
            else{
                os << matrix._matrix[i] << ' ';
            }
        }
    }
    return os;
}

// Function gets a string and checks validation to be a matrix.
// Note: the check in which a matrix doesn't match given col and row properties isn't included here.
void checkIfValid(string mat){
    char delim = ',';
    string token;
    for (unsigned long i = 0, comma_cnt = 0, lbr_cnt = 0, rbr_cnt = 0; i < mat.length(); ++i) {
        token += mat[i];
        if (mat[i] == delim){ /*Reached a comma*/
            comma_cnt++;
            token = token.substr(0, token.length()-1);
            if ((token[0] != '['|| token[token.length()-1] != ']') && (comma_cnt == 1)){
                throw invalid_argument("Invalid matrix!");
            }
            if ((token.substr(0,2) != " [" || token[token.length()-1] != ']') && (comma_cnt != 1)){
                throw invalid_argument("Invalid matrix!");
            }
            if (lbr_cnt != 1 || rbr_cnt != 1){ /*Only one left and right square brackets are allowed*/
                throw invalid_argument("Only one left and right square brackets are allowed!");
            }
            rbr_cnt = 0; lbr_cnt = 0;
            token = "";
        }
        /*Count left bracket, and check that there isn't a space right after*/
        else if (mat[i] == '['){
            lbr_cnt++;
            if (mat[i+1] == ' '){
                throw invalid_argument("Invalid matrix.");
            }
        }
        /*Count right bracket, and check that there isn't a space before*/
        else if (mat[i] == ']'){
            rbr_cnt++;
            if (mat[i-1] == ' '){
                throw invalid_argument("Invalid matrix.");
            }
        }
    }

}

// Input function: GET A MATRIX WITH THE FOLLOWING FORM: [1 3 5], [3 4 5], [6 7 8] for example.
// Function inserts the data to matrix's properties.
istream& zich::operator>>(istream& is, Matrix& matrix)
{
    string checkMat;
    getline(is, checkMat);
    checkIfValid(checkMat);

    /*Get the matrix's properties with string stream to split*/
    vector<double> mat_vec;
    stringstream ss{checkMat};
    string split;
    size_t col_cnt = 0;
    size_t row_cnt = 0;

    /*Split first by a comma - the string is valid so yields a valid result*/
    while (getline(ss, split, ',')) {
        if (row_cnt != 0) {split = split.substr(1, split.length()-1);}
        cout << split << endl;
        std::erase(split, '['); std::erase(split, ']');
        stringstream ss_split{split};
        string num;
        /*Split with a space to get the float numbers*/
        while (getline(ss_split, num, ' ')) {
            mat_vec.push_back(stod(num));
            if (row_cnt == 0){col_cnt++;}
        }
        row_cnt++;
    }

    if(mat_vec.size() != row_cnt*col_cnt){
        throw invalid_argument("Matrix doesn't match its given row and column properties!");
    }
    matrix._row = row_cnt;
    matrix._col = col_cnt;
    matrix._matrix = mat_vec;
    return is;
}

// Multiplication of a matrix by scalar function on right side.
// I.e.: mat * scalar
Matrix zich::operator*(const Matrix &matrix, double scalar) {
    vector<double> add_mat((unsigned long) (matrix._row * matrix._col), 0);
    for (unsigned long i = 0; i < matrix._matrix.size(); ++i) {add_mat.at(i) = matrix._matrix[i] * scalar;}
    Matrix mul{add_mat, matrix._row, matrix._col};
    return mul;
}

// Multiplication of a matrix by scalar function on left side.
// I.e.: mat * scalar
Matrix zich::operator*(double scalar, const Matrix &matrix) {
    return matrix * scalar;
}