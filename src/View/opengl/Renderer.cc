#include "Renderer.h"

#include <iostream>

#include "Constants.h"
#include "View/ui/Preferences/Preferences.h"

namespace s21 {

Renderer::Renderer(const QSize &screenSize)
    : screen_size_{screenSize},
      screen_ratio_{static_cast<float>(screen_size_.width()) /
                    static_cast<float>(screen_size_.height())} {}

void Renderer::InitializeRenderingEnvironment() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void Renderer::SetupShaders() {
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/vertexShader.vert");
  shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/fragmentShader.frag");
  if (!shader_program_.link()) {
    std::cerr << "Shader program failed to link:"
              << shader_program_.log().toStdString();
  }

  projection_matrix_location_ =
      shader_program_.uniformLocation("projectionMatrix");
  view_matrix_location_ = shader_program_.uniformLocation("viewMatrix");
  model_matrix_location_ = shader_program_.uniformLocation("modelMatrix");
  frag_color_location_ = shader_program_.uniformLocation("fragColor");
}

void Renderer::ClearBuffersAndBackgroundColor() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  const QColor background_color{Preferences::Get().GetBackgroundColor()};
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1.0f);
}

void Renderer::BindShaderProgram() { shader_program_.bind(); }

void Renderer::ReleaseShaderProgram() { shader_program_.release(); }

void Renderer::UpdateProjectionMatrix(const float field_of_view,
                                      const float ortho_scale) {
  QMatrix4x4 projection_matrix{};

  if (Preferences::Get().GetProjectionType() ==
      Projection::Type::kPerspective) {
    const int near_plane{Preferences::Get().GetNearPlane()};
    const int far_plane{Preferences::Get().GetFarPlane()};
    projection_matrix.perspective(field_of_view, screen_ratio_,
                                  static_cast<float>(near_plane),
                                  static_cast<float>(far_plane));
  } else {
    projection_matrix.ortho(
        -ortho_scale * screen_ratio_, ortho_scale * screen_ratio_, -ortho_scale,
        ortho_scale, constants::kDefaultOrthographicNearPlane,
        constants::kDefaultOrthographicFarPlane);
  }

  shader_program_.setUniformValue(projection_matrix_location_,
                                  projection_matrix);
}

void Renderer::UpdateViewMatrix(const Camera &camera,
                                const std::array<float, 3> &main_mesh_center) {
  QMatrix4x4 view_matrix{};

  if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
    view_matrix = camera.GetLookAtMatrix();
  } else {
    view_matrix.setToIdentity();
    view_matrix.translate(camera.GetPosition());
    view_matrix.rotate(camera.GetElevation(), constants::kXAxis);
    view_matrix.rotate(camera.GetAzimuth(), constants::kYAxis);
    view_matrix.translate(-main_mesh_center[0], -main_mesh_center[1],
                          -main_mesh_center[2]);
  }

  shader_program_.setUniformValue(view_matrix_location_, view_matrix);
}

void Renderer::UpdateModelMatrix(Mesh &mesh, const Transform &transform) {
  mesh.ApplyTransformations(transform);
  Matrix model_matrix{mesh.GetModelMatrix()};
  QMatrix4x4 converted{};
  for (int i{0}; i < 4; ++i) {
    for (int j{0}; j < 4; ++j) {
      converted(i, j) = model_matrix(i, j);
    }
  }
  shader_program_.setUniformValue(model_matrix_location_, converted);
}

void Renderer::RenderMesh(Mesh &mesh) {
  mesh.RenderEdges(shader_program_, frag_color_location_);
  if (Preferences::Get().GetVertexDisplayMethod() !=
      Vertex::DisplayMethod::kNone) {
    mesh.RenderPoints(shader_program_, frag_color_location_);
  }
}

void Renderer::HandleResizing(const int new_width, const int new_height) {
  screen_size_.setWidth(new_width);
  screen_size_.setHeight(new_height);
  screen_ratio_ = static_cast<float>(screen_size_.width()) /
                  static_cast<float>(screen_size_.height());
}

}  // namespace s21
