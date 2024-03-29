#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_RENDERER_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_RENDERER_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Camera.h"
#include "Constants.h"
#include "Mesh.h"

namespace s21 {
class Renderer : protected QOpenGLFunctions {
 public:
  Renderer(const QSize &screenSize);
  void InitializeRenderingEnvironment();
  void SetupShaders();

  void ClearBuffersAndBackgroundColor();

  void BindShaderProgram();
  void ReleaseShaderProgram();

  void UpdateProjectionMatrix(float field_of_view, float ortho_scale);
  void UpdateViewMatrix(const Camera &camera,
                        const std::array<float, 3> &main_mesh_center);
  void UpdateModelMatrix(Mesh &mesh, const Transform &transform);

  void RenderMesh(Mesh &mesh);
  void HandleResizing(int new_width, int new_height);

 private:
  QSize screen_size_{};
  float screen_ratio_{};

  QOpenGLShaderProgram shader_program_{};

  GLint projection_matrix_location_{};
  GLint view_matrix_location_{};
  GLint model_matrix_location_{};
  GLint frag_color_location_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_RENDERER_H_