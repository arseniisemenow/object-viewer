#include "Preferences.h"

namespace s21 {

Preferences::~Preferences(){};

void Preferences::SaveSceneScale() {
  Preferences::Get().settings->setValue(STRINGIFY(m_sceneScale), m_sceneScale);
}
// dockWidgetSettings
void Preferences::SaveProjectionType() {
  Preferences::Get().dock_widget_settings->setValue(STRINGIFY(m_projectionType),
                                                    projection_type_);
}
void Preferences::SaveBackgroundColor() {
  Preferences::Get().settings->setValue(STRINGIFY(m_backgroundColor),
                                        background_color_);
}
void Preferences::SaveVertexDisplayMethod() {
  Preferences::Get().settings->setValue(STRINGIFY(m_vertexDisplayMethod),
                                        vertex_display_method_);
}
void Preferences::SaveVertexColor() {
  Preferences::Get().settings->setValue(STRINGIFY(m_vertexColor),
                                        vertex_color_);
}
void Preferences::SaveVertexSize() {
  Preferences::Get().settings->setValue(STRINGIFY(m_vertexSize), vertex_size_);
}
void Preferences::SaveEdgeType() {
  Preferences::Get().settings->setValue(STRINGIFY(m_edgeType), edge_type_);
}
void Preferences::SaveEdgeColor() {
  Preferences::Get().settings->setValue(STRINGIFY(m_edgeColor), edge_color_);
}
void Preferences::SaveEdgeSize() {
  Preferences::Get().settings->setValue(STRINGIFY(m_edgeSize), edge_size_);
}

void Preferences::SaveLastOpenedDir() {
  Preferences::Get().settings->setValue(STRINGIFY(m_lastOpenedDir),
                                        last_opened_dir_);
}

// dockWidgetSettings
void Preferences::SaveCameraMode() {
  Preferences::Get().dock_widget_settings->setValue(
      STRINGIFY(m_cameraMode), static_cast<int>(camera_mode_));
}
void Preferences::SaveCameraSpeed() {
  Preferences::Get().settings->setValue(STRINGIFY(m_cameraSpeed),
                                        camera_speed_);
}
void Preferences::SaveNearPlane() {
  Preferences::Get().settings->setValue(STRINGIFY(m_nearPlane), near_plane_);
}

void Preferences::SaveFarPlane() {
  Preferences::Get().settings->setValue(STRINGIFY(m_farPlane), far_plane_);
}

void Preferences::Save() {
  std::cerr << "Preferences::save()\n";
  SaveSceneScale();
  SaveBackgroundColor();
  SaveCameraSpeed();
  SaveNearPlane();
  SaveFarPlane();

  SaveVertexDisplayMethod();
  SaveVertexColor();
  SaveVertexSize();

  SaveEdgeType();
  SaveEdgeColor();
  SaveEdgeSize();

  SaveLastOpenedDir();
  SaveProjectionType();
  SaveCameraMode();
}

void Preferences::LoadSceneScale() {
  m_sceneScale =
      Preferences::Get()
          .settings->value(STRINGIFY(m_sceneScale), S21_DEFAULT_SCALE)
          .toDouble();
}

// dockWidgetSettings
void Preferences::LoadProjectionType() {
  projection_type_ =
      Preferences::Get()
          .dock_widget_settings
          ->value(STRINGIFY(m_projectionType), Projection::Type::kPerspective)
          .toInt();
}

void Preferences::LoadBackgroundColor() {
  background_color_ = Preferences::Get()
                          .settings
                          ->value(STRINGIFY(m_backgroundColor),
                                  QColor(S21_DEFAULT_BACKGROUND_COLOR))
                          .value<QColor>();
}

void Preferences::LoadVertexDisplayMethod() {
  vertex_display_method_ = Preferences::Get()
                               .settings
                               ->value(STRINGIFY(m_vertexDisplayMethod),
                                       Vertex::DisplayMethod::kCircle)
                               .toInt();
}

void Preferences::LoadVertexColor() {
  vertex_color_ =
      Preferences::Get()
          .settings
          ->value(STRINGIFY(m_vertexColor), QColor(S21_DEFAULT_VERTEX_COLOR))
          .value<QColor>();
}

void Preferences::LoadVertexSize() {
  vertex_size_ =
      Preferences::Get()
          .settings->value(STRINGIFY(m_vertexSize), S21_DEFAULT_VERTEX_SIZE)
          .toInt();
}

void Preferences::LoadEdgeType() {
  edge_type_ = Preferences::Get()
                   .settings->value(STRINGIFY(m_edgeType), Edge::Type::kSolid)
                   .toInt();
}

void Preferences::LoadEdgeColor() {
  edge_color_ =
      Preferences::Get()
          .settings
          ->value(STRINGIFY(m_edgeColor), QColor(S21_DEFAULT_EDGE_COLOR))
          .value<QColor>();
}

void Preferences::LoadEdgeSize() {
  edge_size_ =
      Preferences::Get()
          .settings->value(STRINGIFY(m_edgeSize), S21_DEFAULT_EDGE_SIZE)
          .toDouble();
}

void Preferences::LoadLastOpenedDir() {
  last_opened_dir_ =
      Preferences::Get()
          .settings->value(STRINGIFY(m_lastOpenedDir), QDir::homePath())
          .toString();
}

// dockWidgetSettings
void Preferences::LoadCameraMode() {
  camera_mode_ = Preferences::Get()
                     .dock_widget_settings
                     ->value(STRINGIFY(m_cameraMode),
                             QVariant::fromValue(CameraMode::kFly))
                     .value<CameraMode>();
}

void Preferences::LoadCameraSpeed() {
  camera_speed_ =
      Preferences::Get()
          .settings
          ->value(STRINGIFY(m_cameraSpeed), S21_DEFAULT_CAMERA_SPEED_VALUE)
          .value<int>();
}

void Preferences::LoadNearPlane() {
  near_plane_ =
      Preferences::Get()
          .settings->value(STRINGIFY(m_nearPlane), S21_DEFAULT_NEAR_PLANE_VALUE)
          .value<int>();
}

void Preferences::LoadFarPlane() {
  far_plane_ =
      Preferences::Get()
          .settings->value(STRINGIFY(m_farPlane), S21_DEFAULT_FAR_PLANE_VALUE)
          .value<int>();
}

void Preferences::Load() {
  std::cerr << "Preferences::load()\n";
  LoadSceneScale();
  LoadBackgroundColor();
  LoadCameraSpeed();
  LoadNearPlane();
  LoadFarPlane();

  LoadVertexDisplayMethod();
  LoadVertexColor();
  LoadVertexSize();

  LoadEdgeType();
  LoadEdgeColor();
  LoadEdgeSize();

  LoadProjectionType();
  LoadCameraMode();
}

double Preferences::GetScale() { return m_sceneScale; }
// dockWidgetSettings
int Preferences::GetProjectionType() { return projection_type_; }

QColor Preferences::GetBackgroundColor() { return background_color_; }

int Preferences::GetVertexDisplayMethod() { return vertex_display_method_; }

QColor Preferences::GetVertexColor() { return vertex_color_; }

double Preferences::GetVertexSize() { return vertex_size_; }

int Preferences::GetEdgeType() { return edge_type_; }

QColor Preferences::GetEdgeColor() { return edge_color_; }

double Preferences::GetEdgeSize() { return edge_size_; }
// dockWidgetSettings
CameraMode Preferences::GetCameraMode() { return camera_mode_; }
int Preferences::GetCameraSpeed() { return camera_speed_; }
int Preferences::GetNearPlane() { return near_plane_; }
int Preferences::GetFarPlane() { return far_plane_; }

int Preferences::SetScale(double newSceneScale) {
  if (newSceneScale <= 0) {
    return 1;
  }
  if (newSceneScale > S21_BIG_NUMBER) {
    return 1;
  }
  m_sceneScale = newSceneScale;
  return 0;
}

// dockWidgetSettings
int Preferences::SetProjectionType(Projection::Type newProjectionType) {
  if (newProjectionType == Projection::Type::kNone) {
    return 1;
  }
  projection_type_ = newProjectionType;
  return 0;
}
// dockWidgetSettings
int Preferences::SetCameraMode(CameraMode newCameraMode) {
  if (camera_mode_ == CameraMode::kNone) {
    return 1;
  }
  camera_mode_ = newCameraMode;
  return 0;
}

int Preferences::SetBackgroundColor(QColor newColor) {
  background_color_ = newColor;
  return 0;
}

int Preferences::SetVertexDisplayMethod(
    Vertex::DisplayMethod newVertexDisplayMethod) {
  vertex_display_method_ = newVertexDisplayMethod;
  return 0;
}

int Preferences::SetVertexColor(QColor newColor) {
  vertex_color_ = newColor;
  return 0;
}

int Preferences::SetVertexSize(double newSize) {
  if (newSize <= 0) {
    return 1;
  }
  if (newSize > S21_BIG_NUMBER) {
    return 1;
  }
  vertex_size_ = newSize;
  return 0;
}

int Preferences::SetEdgeType(Edge::Type newEdgeType) {
  if (newEdgeType == Edge::Type::kNone) {
    return 1;
  }
  edge_type_ = newEdgeType;
  return 0;
}

int Preferences::SetEdgeColor(QColor newColor) {
  edge_color_ = newColor;
  return 0;
}

int Preferences::SetEdgeSize(double newSize) {
  if (newSize <= 0) {
    return 1;
  }
  if (newSize > S21_BIG_NUMBER) {
    return 1;
  }
  edge_size_ = newSize;
  return 0;
}

int Preferences::SetCameraSpeed(int newCameraSpeed) {
  camera_speed_ = newCameraSpeed;
  return 0;
}
int Preferences::SetNearPlane(int newNearPlane) {
  near_plane_ = newNearPlane;
  return 0;
}
int Preferences::SetFarPlane(int newFarPlane) {
  far_plane_ = newFarPlane;
  return 0;
}

}  // namespace s21