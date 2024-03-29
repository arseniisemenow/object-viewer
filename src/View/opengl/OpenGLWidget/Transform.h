#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_TRANSFORM_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_TRANSFORM_H_

#include <QVector3D>

namespace s21 {
struct Transform {
  QVector3D translation{};
  QVector3D rotation_angles{};
  QVector3D scaling{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_TRANSFORM_H_