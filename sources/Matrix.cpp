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

Matrix::Matrix(vector<double> matrix, int row, int col)
    : _matrix(move(matrix)), _row(row), _col(col){
    if (_row <= 0 || _col <= 0) {
        throw invalid_argument("Row and col are zero/negative!");
    }
    if (_matrix.size() != _row * _col){
        throw invalid_argument("Matrix size doesn't match the given row and col.");
    }
}

Matrix Matrix::operator+(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }
    vector<double> add_mat((unsigned long) (_row * _col), 0);
    for (unsigned long i = 0; i < _matrix.size(); ++i) {add_mat.at(i) = _matrix[i] + other._matrix[i];}
    Matrix add{add_mat, _row, _col};
    return add;
}

/**
 * Unary operator: +Matrix
 */
Matrix Matrix::operator+() {
    vector<double> add_mat((unsigned long) (_row * _col), 0);
    for (unsigned long i = 0; i < _matrix.size(); ++i) {add_mat.at(i) = _matrix[i];}
    Matrix plus{add_mat, _row, _col};
    return plus;
}

Matrix& Matrix::operator+=(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }

    for (unsigned long i = 0; i < _matrix.size(); ++i) {
        _matrix.at(i) += other._matrix[i];
    }
    return *this;
}

/**
 * Prefix method: ++Matrix
 */
Matrix& Matrix::operator++() {
    for (double &element : _matrix) {++element;}
    return *this;
}

/**
 * Postfix method: Matrix++
 */
Matrix Matrix::operator++(int) {
    Matrix cpy{_matrix, _row, _col}; /* Copy of current matrix*/
    ++*this;
    return cpy;
}

Matrix Matrix::operator-(const Matrix &other) {
    if (_row != other._row || _col != other._col) {
        throw invalid_argument("Matrices dimension isn't the same!");
    }

    vector<double> add_mat((unsigned long) (_row * _col), 0);

    for (unsigned long i = 0; i < _matrix.size(); ++i) {
        add_mat.at(i) = _matrix[i] - other._matrix[i];
    }
    Matrix add{add_mat, _row, _col};
    return add;
}

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

/**
 * Prefix method: --Matrix
 */
Matrix& Matrix::operator--() {
    for (double &element : _matrix) {--element;}
    return *this;
}

/**
 * Postfix method: Matrix--
 */
Matrix Matrix::operator--(int) {
    Matrix cpy{_matrix, _row, _col}; /* Copy of current matrix*/
    --*this;
    return cpy;
}



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

Matrix& Matrix::operator*=(const Matrix &other){
    *this = *this * other;
    return *this;
}

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

/**
 * Method compares by the following operator relations (">", ">=", "<", "<=")
 * @param a
 * @param b
 * @param Operator
 * @return
 */
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

/**
 * OUTPUT METHOD
 * @param os - output stream reference
 * @param matrix
 * @return
 */
ostream& zich::operator<<(ostream& os, const Matrix& matrix)
{
    if (matrix._matrix.size() != matrix._row * matrix._col){
        throw invalid_argument("Vector size doesn't match given matrix dimension.");
    }
    if (matrix._col == 1){
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



// [1 1 1], [3 4 5], [3 3 2]

void checkIfValid(string mat){
    string delim = ",";
    size_t pos;
    size_t cnt = 0;
    while ((pos = mat.find (delim)) != string::npos)
    {
        string token = mat.substr(0, pos); // store the substring
        if ((token[0] != '['|| token[token.length()-1] != ']') && (cnt == 0)){
            throw invalid_argument("Invalid matrix.");
        }
        else if ((mat.substr(0,2) != " [" || token[token.length()-1] != ']') && (cnt != 0)){
            throw invalid_argument("Invalid matrix.");
        }
        mat.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
        cnt++;
    }
}

/**
 * INPUT METHOD
 *
 * GET A MATRIX WITH THE FOLLOWING FORM: [1 3 5], [3 4 5], [6 7 8]
 *
 * @param is
 * @param matrix
 * @return
 */
istream& zich::operator>>(istream& is, Matrix& matrix)
{
    string checkMat;
    getline(is, checkMat);
    checkIfValid(checkMat);

    istringstream iss{checkMat};
    string mat;
    vector<double> mat_vec;

    int row = 1; int col = 0; int col_cnt = 0;
    do{
        iss >> mat;
        char last_ch = mat[mat.length() - 1];

        /* Remove unnecessary chars*/
        std::erase(mat, '[');
        std::erase(mat, ']');

        if(last_ch!= ',' && col == 0){
            mat_vec.push_back(stod(mat));
            col_cnt++;
        }
        else if (last_ch != ',' && col != 0){
            mat_vec.push_back(stod(mat));
        }
        else if (last_ch == ','){
            mat_vec.push_back(stod(mat.substr(0, mat.length() - 1)));
            col = col_cnt + 1;
            row++;
        }
    }
    while (iss.peek() != '\n');

    if (row == 1) {col = col_cnt;}
    matrix._row = row;
    matrix._col = col;
    matrix._matrix = mat_vec;
    return is;
}

Matrix zich::operator*(const Matrix &matrix, double scalar) {
    vector<double> add_mat((unsigned long) (matrix._row * matrix._col), 0);
    for (unsigned long i = 0; i < matrix._matrix.size(); ++i) {add_mat.at(i) = matrix._matrix[i] * scalar;}
    Matrix mul{add_mat, matrix._row, matrix._col};
    return mul;
}

Matrix zich::operator*(double scalar, const Matrix &matrix) {
    return matrix * scalar;
}


