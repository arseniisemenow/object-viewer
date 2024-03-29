#include "Mesh.h"

#include "Constants.h"
#include "View/ui/Preferences/Preferences.h"

namespace s21 {

Mesh::Mesh(Controller *controller)
    : controller_(controller),
      vertex_buffer_{QOpenGLBuffer::Type::VertexBuffer},
      index_buffer_{QOpenGLBuffer::Type::IndexBuffer} {}

Mesh::~Mesh() {}

void Mesh::InitializeBuffers() {
  initializeOpenGLFunctions();
  vertex_buffer_.create();
  index_buffer_.create();
  vertex_buffer_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  index_buffer_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  BindVertexBuffer();
  glVertexAttribPointer(
      0, constants::kNumberOfVertexCoordinates, GL_FLOAT, GL_FALSE,
      constants::kNumberOfVertexCoordinates * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  ReleaseVertexBuffer();
}

void Mesh::Load(const MeshData &data) {
  Unload();

  data_ = data;

  BindBuffers();

  vertex_buffer_.allocate(nullptr, 0);
  index_buffer_.allocate(nullptr, 0);
  vertex_buffer_.allocate(data_.vertices.data(),
                          data_.number_of_vertices *
                              constants::kNumberOfVertexCoordinates *
                              sizeof(float));
  index_buffer_.allocate(data_.indices.data(),
                         data_.number_of_edges *
                             constants::kNumberOfEdgePoints *
                             static_cast<int>(sizeof(int)));

  ReleaseBuffers();
}

void Mesh::Unload() {
  data_.vertices.clear();
  data_.indices.clear();
  data_.number_of_edges = 0;
  data_.number_of_vertices = 0;
  data_.center = {0.0f, 0.0f, 0.0f};
}

void Mesh::RenderEdges(QOpenGLShaderProgram &shader_program,
                       const GLint color_location) {
  BindBuffers();

  if (Preferences::Get().GetEdgeType() == Edge::Type::kDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 10);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(Preferences::Get().GetEdgeSize());

  shader_program.setUniformValue(color_location,
                                 Preferences::Get().GetEdgeColor());
  glDrawElements(GL_LINES,
                 data_.number_of_edges * constants::kNumberOfEdgePoints,
                 GL_UNSIGNED_INT, nullptr);

  ReleaseBuffers();
}

void Mesh::RenderPoints(QOpenGLShaderProgram &shader_program,
                        GLint color_location) {
  BindBuffers();

  if (Preferences::Get().GetVertexDisplayMethod() ==
      Vertex::DisplayMethod::kCircle) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(static_cast<float>(Preferences::Get().GetVertexSize()));

  shader_program.setUniformValue(color_location,
                                 Preferences::Get().GetVertexColor());
  glDrawArrays(GL_POINTS, 0, data_.number_of_vertices);

  ReleaseBuffers();
}

void Mesh::BindVertexBuffer() { vertex_buffer_.bind(); }

void Mesh::BindIndexBuffer() { index_buffer_.bind(); }

void Mesh::ReleaseVertexBuffer() { vertex_buffer_.release(); }

void Mesh::ReleaseIndexBuffer() { index_buffer_.release(); }

void Mesh::BindBuffers() {
  BindVertexBuffer();
  BindIndexBuffer();
}

void Mesh::ReleaseBuffers() {
  ReleaseVertexBuffer();
  ReleaseIndexBuffer();
}

void Mesh::ApplyTransformations(const Transform &transform) {
  model_matrix_.SetToIdentity();

  controller_->SetModelMatrix(model_matrix_);

  controller_->Scale(
      {transform.scaling.x(), transform.scaling.y(), transform.scaling.z()});
  controller_->Rotate(transform.rotation_angles.x(), {1.0, 0.0, 0.0});
  controller_->Rotate(transform.rotation_angles.y(), {0.0, 1.0, 0.0});
  controller_->Rotate(transform.rotation_angles.z(), {0.0, 0.0, 1.0});
  controller_->Translate({transform.translation.x(), transform.translation.y(),
                          transform.translation.z()});

  model_matrix_ = controller_->GetModelMatrix();
}

const MeshData &Mesh::GetData() const { return data_; }

const Matrix &Mesh::GetModelMatrix() const { return model_matrix_; }

}  // namespace s21