#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_TRANSFORMATION_TRANSFORMATION_H_
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_TRANSFORMATION_TRANSFORMATION_H_

#include "Matrix/Matrix.h"

namespace s21 {
class Transformation {
 public:
  void Translate(double x_translate, double y_translate, double z_translate);
  void Rotate(double angle, double x_axis, double y_axis, double z_axis);
  void Scale(double x_scale, double y_scale, double z_scale);

  void SetModelMatrix(const Matrix &matrix);
  [[nodiscard]] const Matrix &GetModelMatrix() const;

 private:
  void RotateAroundX(double sin_theta, double cos_theta);
  void RotateAroundY(double sin_theta, double cos_theta);
  void RotateAroundZ(double sin_theta, double cos_theta);

  void UpdateColumnsAfterRotation(int first_row, int second_row,
                                  double sin_theta, double cos_theta);

 private:
  Matrix model_matrix_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_TRANSFORMATION_TRANSFORMATION_H_