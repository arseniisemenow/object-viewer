#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H_
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H_

#include "Matrix/Matrix.h"
#include "Parser/Parser.h"
#include "Transformation/Transformation.h"

namespace s21 {
class Model {
 public:
  Model() = default;

  ParseResult GetObjFileParseResult(const std::string& file_name);

  void SetModelMatrix(const Matrix& matrix);
  [[nodiscard]] const Matrix& GetModelMatrix() const;

  void Translate(const std::array<float, 3>& translation);
  void Rotate(double angle, const std::array<float, 3>& axes);
  void Scale(const std::array<float, 3>& scaling);

 private:
  Parser parser_{};
  Transformation transformation_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_MODEL_H_