#ifndef CPP4_3D_VIEWER_V_2_0_1_MATRIX_MATRIX_H_
#define CPP4_3D_VIEWER_V_2_0_1_MATRIX_MATRIX_H_

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace s21 {
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  ~Matrix();

  [[nodiscard]] bool EqMatrix(const Matrix &other) const;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double number);
  void MulMatrix(const Matrix &other);
  [[nodiscard]] Matrix Transpose() const;
  [[nodiscard]] Matrix CalcComplements() const;
  [[nodiscard]] double Determinant() const;
  [[nodiscard]] Matrix InverseMatrix() const;
  void SetToIdentity();

  [[nodiscard]] Matrix operator+(const Matrix &other) const;
  [[nodiscard]] Matrix operator-(const Matrix &other) const;
  [[nodiscard]] Matrix operator*(const Matrix &other) const;
  [[nodiscard]] Matrix operator*(const double number) const;
  [[nodiscard]] bool operator==(const Matrix &other) const;
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other) noexcept;
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(const double number);
  [[nodiscard]] double &operator()(int row, int column);
  [[nodiscard]] const double &operator()(int row, int column) const;

  [[nodiscard]] int GetCols() const;
  [[nodiscard]] int GetRows() const;

  void SetRows(int new_rows);
  void SetCols(int new_cols);

  [[nodiscard]] double **GetData() const;

 private:
  void ChangeSize(int rows, int cols);

  [[nodiscard]] Matrix GetMinorMatrix(int removed_row, int removed_col) const;

  void AllocateMemory();
  void FreeMemory();
  void CopyElements(const Matrix &other);

 private:
  int rows_{};
  int cols_{};
  double **matrix_{};
};

std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
Matrix operator*(const double number, Matrix &matrix);
}  // namespace s21

#endif
