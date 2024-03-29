#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_MESH_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_MESH_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Controller/Controller.h"
#include "Matrix/Matrix.h"
#include "View/opengl/OpenGLWidget/Transform.h"

namespace s21 {
class Mesh : protected QOpenGLFunctions {
 public:
  explicit Mesh(Controller *controller);
  ~Mesh();

  void InitializeBuffers();
  void Load(const MeshData &data);
  void Unload();
  void RenderEdges(QOpenGLShaderProgram &shader_program, GLint color_location);
  void RenderPoints(QOpenGLShaderProgram &shader_program, GLint color_location);

  void BindVertexBuffer();
  void BindIndexBuffer();
  void ReleaseVertexBuffer();
  void ReleaseIndexBuffer();
  void BindBuffers();
  void ReleaseBuffers();

  void ApplyTransformations(const Transform &transform);
  [[nodiscard]] const MeshData &GetData() const;
  [[nodiscard]] const Matrix &GetModelMatrix() const;

 private:
  Controller *controller_;

  QOpenGLBuffer vertex_buffer_{};
  QOpenGLBuffer index_buffer_{};
  MeshData data_{};

  GLint frag_color_location_{};

  Matrix model_matrix_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_MESH_H_