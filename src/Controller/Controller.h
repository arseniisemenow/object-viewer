#ifndef CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H_
#define CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H_

#include <array>
#include <string>

#include "Matrix/Matrix.h"
#include "Model/Model.h"
#include "common/ParseResult.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(Model* model);

  ParseResult ParseObjFile(const std::string& file_name);

  void SetModelMatrix(const Matrix& matrix);
  [[nodiscard]] const Matrix& GetModelMatrix() const;

  void Translate(const std::array<float, 3>& translation);
  void Rotate(double angle, const std::array<float, 3>& axes);
  void Scale(const std::array<float, 3>& scaling);

 private:
  Model* model_;
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_CONTROLLER_CONTROLLER_H_