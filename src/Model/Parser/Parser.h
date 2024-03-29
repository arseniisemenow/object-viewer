#ifndef CPP4_3D_VIEWER_V_2_0_1_MODEL_PARSER_PARSER_H_
#define CPP4_3D_VIEWER_V_2_0_1_MODEL_PARSER_PARSER_H_

#include <array>
#include <string>

#include "common/ParseResult.h"

namespace s21 {
class Parser {
 public:
  ParseResult ParseObjFile(const std::string &file_name);

 private:
  void GetVertexInfoFromLine(const std::string &line);
  void GetSurfaceInfoFromLine(const std::string &line);
  double ReadVertexCoordinate(std::string &line);
  int ReadVertexIndex(std::string &line);
  void ProcessVertexIndex(int vertex_index, bool &first_index_was_set,
                          int &first_index);
  void SkipToNextIndex(std::string &line);

  std::array<float, 3> CalculateBoundingBoxCenter();
  void ClearMeshData();

 private:
  ParseResult result_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_MODEL_PARSER_PARSER_H_