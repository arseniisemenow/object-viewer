#include "Transformation.h"

#include <cmath>

#include "Model/ModelConstants.h"

namespace s21 {
void Transformation::Translate(double x_translate, double y_translate,
                               double z_translate) {
  model_matrix_(0, 3) += x_translate;
  model_matrix_(1, 3) += y_translate;
  model_matrix_(2, 3) += z_translate;
}

void Transformation::Rotate(double angle, double x_axis, double y_axis,
                            double z_axis) {
  angle = angle * constants::kPi / 180.0f;
  double sin_theta{std::sin(angle)};
  double cos_theta{std::cos(angle)};

  if (x_axis != 0.0) {
    if (x_axis < 0.0) {
      sin_theta = -sin_theta;
    }
    RotateAroundX(sin_theta, cos_theta);
  }
  if (y_axis != 0.0) {
    if (y_axis < 0.0) {
      sin_theta = -sin_theta;
    }
    RotateAroundY(sin_theta, cos_theta);
  }
  if (z_axis != 0.0) {
    if (z_axis < 0.0) {
      sin_theta = -sin_theta;
    }
    RotateAroundZ(sin_theta, cos_theta);
  }
}

void Transformation::Scale(double x_scale, double y_scale, double z_scale) {
  model_matrix_(0, 0) *= x_scale;
  model_matrix_(0, 1) *= x_scale;
  model_matrix_(0, 2) *= x_scale;
  model_matrix_(0, 3) *= x_scale;

  model_matrix_(1, 0) *= y_scale;
  model_matrix_(1, 1) *= y_scale;
  model_matrix_(1, 2) *= y_scale;
  model_matrix_(1, 3) *= y_scale;

  model_matrix_(2, 0) *= z_scale;
  model_matrix_(2, 1) *= z_scale;
  model_matrix_(2, 2) *= z_scale;
  model_matrix_(2, 3) *= z_scale;
}

void Transformation::SetModelMatrix(const Matrix& matrix) {
  model_matrix_ = matrix;
}

const Matrix& Transformation::GetModelMatrix() const { return model_matrix_; }

void Transformation::RotateAroundX(double sin_theta, double cos_theta) {
  UpdateColumnsAfterRotation(1, 2, sin_theta, cos_theta);
}

void Transformation::RotateAroundY(double sin_theta, double cos_theta) {
  UpdateColumnsAfterRotation(2, 0, sin_theta, cos_theta);
}

void Transformation::RotateAroundZ(double sin_theta, double cos_theta) {
  UpdateColumnsAfterRotation(0, 1, sin_theta, cos_theta);
}

void Transformation::UpdateColumnsAfterRotation(int first_row, int second_row,
                                                double sin_theta,
                                                double cos_theta) {
  for (int column{0}; column < 4; ++column) {
    double current_y{model_matrix_(first_row, column)};
    double current_z{model_matrix_(second_row, column)};

    model_matrix_(first_row, column) =
        current_y * cos_theta + current_z * sin_theta;
    model_matrix_(second_row, column) =
        current_z * cos_theta - current_y * sin_theta;
  }
}
}  // namespace s21
