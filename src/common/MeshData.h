#ifndef CPP4_3D_VIEWER_V_2_0_1_COMMON_MESH_DATA_H_
#define CPP4_3D_VIEWER_V_2_0_1_COMMON_MESH_DATA_H_

#include <array>
#include <vector>

namespace s21 {
struct MeshData {
  std::vector<float> vertices{};
  std::vector<int> indices{};

  int number_of_vertices{};
  int number_of_edges{};

  std::array<float, 3> center{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_COMMON_MESH_DATA_H_