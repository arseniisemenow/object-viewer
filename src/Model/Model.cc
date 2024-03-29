#include "Model.h"

namespace s21 {
ParseResult Model::GetObjFileParseResult(const std::string &file_name) {
  return parser_.ParseObjFile(file_name);
}

void Model::SetModelMatrix(const Matrix &matrix) {
  transformation_.SetModelMatrix(matrix);
}

const Matrix &Model::GetModelMatrix() const {
  return transformation_.GetModelMatrix();
}

void Model::Translate(const std::array<float, 3> &translation) {
  transformation_.Translate(translation[0], translation[1], translation[2]);
}

void Model::Rotate(double angle, const std::array<float, 3> &axes) {
  transformation_.Rotate(angle, axes[0], axes[1], axes[2]);
}

void Model::Scale(const std::array<float, 3> &scaling) {
  transformation_.Scale(scaling[0], scaling[1], scaling[2]);
}
}  // namespace s21
