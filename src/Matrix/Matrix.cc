#include "Matrix.h"

namespace s21::constants {
constexpr double kPrecision{1e-7};
constexpr int kDefaultMatrixSize{4};
}  // namespace s21::constants

namespace s21 {
Matrix::Matrix()
    : Matrix{constants::kDefaultMatrixSize, constants::kDefaultMatrixSize} {}

Matrix::Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument{
        "Matrix::Matrix(int, int): Matrix has improper dimensions. "
        "Rows and columns must be greater than zero."};
  }

  AllocateMemory();
}

Matrix::Matrix(const Matrix& other) : rows_{other.rows_}, cols_{other.cols_} {
  AllocateMemory();
  CopyElements(other);
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_{std::exchange(other.rows_, 0)},
      cols_{std::exchange(other.cols_, 0)},
      matrix_{std::exchange(other.matrix_, nullptr)} {}

Matrix::~Matrix() { FreeMemory(); }

[[nodiscard]] bool Matrix::EqMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  bool are_equal{true};
  for (int i{0}; i < rows_ && are_equal; ++i) {
    for (int j{0}; j < cols_ && are_equal; ++j) {
      if (std::abs(matrix_[i][j] - other(i, j)) > constants::kPrecision)
        are_equal = false;
    }
  }

  return are_equal;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument{
        "Matrix::SumMatrix(const Matrix&): Matrix dimensions are not "
        "compatible for addition. "
        "Both matrices must have the same number of rows and columns."};
  }

  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument{
        "Matrix::SubMatrix(const Matrix&): Matrix dimensions are not "
        "compatible for addition. "
        "Both matrices must have the same number of rows and columns."};
  }

  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void Matrix::MulNumber(const double number) {
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] *= number;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument{
        "Matrix::MulMatrix(const Matrix&): Matrix dimensions are not "
        "compatible for multiplication. "
        "Number of columns in the first matrix must be equal to the number of "
        "rows in the second matrix."};
  }

  Matrix result{other.rows_, cols_};
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < other.cols_; ++j) {
      double element{0.0};
      for (int k{0}; k < other.rows_; ++k) {
        element += matrix_[i][k] * other(k, j);
      }
      result(i, j) = element;
    }
  }

  *this = result;
}

[[nodiscard]] Matrix Matrix::Transpose() const {
  Matrix transposed{cols_, rows_};

  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      transposed(j, i) = matrix_[i][j];
    }
  }

  return transposed;
}

[[nodiscard]] Matrix Matrix::CalcComplements() const {
  if (cols_ != rows_) {
    throw std::invalid_argument{
        "Matrix::CalcComplements(): Matrix dimensions are not compatible "
        "for complements calculation. "
        "The matrix must be square."};
  }

  Matrix complements{rows_, cols_};
  if (rows_ == 1) {
    complements(0, 0) = 1;
  } else {
    for (int row{0}; row < rows_; ++row) {
      for (int column{0}; column < cols_; ++column) {
        Matrix minor_matrix{GetMinorMatrix(row, column)};
        complements(row, column) =
            pow(-1, row + column) * minor_matrix.Determinant();
      }
    }
  }

  return complements;
}

[[nodiscard]] double Matrix::Determinant() const {
  if (cols_ != rows_) {
    throw std::invalid_argument{
        "Matrix::Determinant(): Matrix dimensions are not compatible for "
        "determinant calculation. "
        "The matrix must be square."};
  }

  double determinant{0.0};

  int matrix_size{rows_};
  if (matrix_size == 1) {
    determinant = matrix_[0][0];
  } else if (matrix_size == 2) {
    determinant += matrix_[0][0] * matrix_[1][1];
    determinant -= matrix_[0][1] * matrix_[1][0];
  } else {
    for (int row{0}, column{0}; row < matrix_size; ++row) {
      Matrix cofactor_matrix{GetMinorMatrix(row, column)};
      double cofactor{cofactor_matrix.Determinant()};
      cofactor *= std::pow(-1, row + column) * matrix_[row][column];
      determinant += cofactor;
    }
  }

  return determinant;
}

[[nodiscard]] Matrix Matrix::InverseMatrix() const {
  if (cols_ != rows_) {
    throw std::invalid_argument{
        "Matrix::InverseMatrix(): Matrix dimensions are not compatible for "
        "inverse matrix calculation. "
        "The matrix must be square."};
  }
  if (Determinant() == 0.0) {
    throw std::runtime_error{
        "Matrix::InverseMatrix(): Matrix is singular, and its inverse does "
        "not exist. "
        "The determinant of the matrix is zero."};
  }

  Matrix inverse{rows_, cols_};
  if (rows_ == 1) {
    inverse(0, 0) = 1.0 / matrix_[0][0];
  } else {
    inverse = CalcComplements().Transpose();
    inverse.MulNumber(1.0 / Determinant());
  }

  return inverse;
}

void Matrix::SetToIdentity() {
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      if (i == j) {
        matrix_[i][j] = 1;
      } else {
        matrix_[i][j] = 0;
      }
    }
  }
}

[[nodiscard]] Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result{*this};
  result.SumMatrix(other);
  return result;
}

[[nodiscard]] Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result{*this};
  result.SubMatrix(other);
  return result;
}

[[nodiscard]] Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result{*this};
  result.MulMatrix(other);
  return result;
}

[[nodiscard]] Matrix Matrix::operator*(const double number) const {
  Matrix result{*this};
  result.MulNumber(number);
  return result;
}

Matrix operator*(const double number, Matrix& matrix) {
  matrix.MulNumber(number);
  return matrix;
}

[[nodiscard]] bool Matrix::operator==(const Matrix& other) const {
  return EqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) return *this;

  FreeMemory();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory();
  CopyElements(other);

  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this == &other) return *this;

  FreeMemory();
  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);

  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

[[nodiscard]] double& Matrix::operator()(int row, int column) {
  if (row < 0 || column < 0 || row >= rows_ || column >= cols_) {
    throw std::out_of_range{
        "Matrix::operator()(int, int): Index out of range. "
        "Row and column indices must be non-negative and within the matrix "
        "dimensions."};
  }

  return matrix_[row][column];
}

[[nodiscard]] const double& Matrix::operator()(int row, int column) const {
  if (row < 0 || column < 0 || row >= rows_ || column >= cols_) {
    throw std::out_of_range{
        "Matrix::operator()(int, int) const: Index out of range. "
        "Row and column indices must be non-negative and within the matrix "
        "dimensions."};
  }

  return matrix_[row][column];
}

[[nodiscard]] int Matrix::GetCols() const { return cols_; }

[[nodiscard]] int Matrix::GetRows() const { return rows_; }

void Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::out_of_range{
        "Matrix::SetRows(int): New number of rows is out of range. "
        "It must be a positive integer."};
  }
  if (new_rows == rows_) return;

  ChangeSize(new_rows, cols_);
}

void Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::out_of_range{
        "Matrix::SetCols(int): New number of columns is out of range. "
        "It must be a positive integer."};
  }
  if (new_cols == cols_) return;

  ChangeSize(rows_, new_cols);
}

void Matrix::ChangeSize(int new_rows, int new_cols) {
  Matrix result{new_rows, new_cols};
  int number_of_rows_to_copy{std::min(new_rows, rows_)};
  int number_of_cols_to_copy{std::min(new_cols, cols_)};
  for (int i{0}; i < number_of_rows_to_copy; ++i) {
    for (int j{0}; j < number_of_cols_to_copy; ++j) {
      result(i, j) = matrix_[i][j];
    }
  }

  *this = result;
}

Matrix Matrix::GetMinorMatrix(int removed_row, int removed_col) const {
  Matrix minor_matrix{rows_ - 1, cols_ - 1};
  int minor_matrix_row{0};
  for (int row{0}; row < rows_; ++row) {
    int minor_matrix_column{0};
    for (int column{0}; column < cols_; ++column) {
      if (row != removed_row && column != removed_col) {
        minor_matrix(minor_matrix_row, minor_matrix_column++) =
            matrix_[row][column];
      }
    }
    if (row != removed_row) ++minor_matrix_row;
  }

  return minor_matrix;
}

void Matrix::AllocateMemory() {
  matrix_ = new double* [static_cast<std::size_t>(rows_)] {};
  for (int i{0}; i < rows_; ++i) {
    matrix_[i] = new double[static_cast<std::size_t>(cols_)]{};
  }
}

void Matrix::FreeMemory() {
  if (matrix_) {
    for (int i{0}; i < rows_; ++i) {
      if (matrix_[i]) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void Matrix::CopyElements(const Matrix& other) {
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] = other(i, j);
    }
  }
}

double** Matrix::GetData() const { return matrix_; }

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
  for (int i{0}; i < matrix.GetRows(); ++i) {
    for (int j{0}; j < matrix.GetCols(); ++j) {
      out << matrix(i, j) << ' ';
    }
    out << '\n';
  }

  return out;
}
}  // namespace s21
