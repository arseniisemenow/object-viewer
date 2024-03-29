#include "Controller.h"

namespace s21 {
Controller::Controller(Model* model) : model_{model} {}

ParseResult Controller::ParseObjFile(const std::string& file_name) {
  return model_->GetObjFileParseResult(file_name);
}

void Controller::SetModelMatrix(const Matrix& matrix) {
  model_->SetModelMatrix(matrix);
}

const Matrix& Controller::GetModelMatrix() const {
  return model_->GetModelMatrix();
}

void Controller::Translate(const std::array<float, 3>& translation) {
  model_->Translate(translation);
}

void Controller::Rotate(double angle, const std::array<float, 3>& axes) {
  model_->Rotate(angle, axes);
}

void Controller::Scale(const std::array<float, 3>& scaling) {
  model_->Scale(scaling);
}
}  // namespace s21
