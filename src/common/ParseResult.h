#ifndef CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_RESULT_H_
#define CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_RESULT_H_

#include "MeshData.h"
#include "ParseErrorEnums.h"

namespace s21 {
struct ParseResult {
  MeshData mesh_data{};
  ModelLoadingError error{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_COMMON_PARSE_RESULT_H_
