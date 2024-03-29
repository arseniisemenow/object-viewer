#include "OpenGLWidget.h"

#include <QTimer>
#include <clocale>
#include <cmath>
#include <filesystem>
#include <iostream>

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/modalWidgets/FileDialog/FileDialog.h"

namespace s21 {
OpenGLWidget::OpenGLWidget(QWidget *parent, Controller *controller)
    : QOpenGLWidget{parent},
      mesh_(controller),
      camera_{constants::kDefaultCameraPosition, constants::kWorldUpVector},
      renderer_{
          size(),
      } {
  QTimer *timer{new QTimer{this}};
  connect(timer, &QTimer::timeout, this, &OpenGLWidget::UpdateFrame);
  timer->start(constants::kMillisecondsPerFrame);
  setFocusPolicy(Qt::StrongFocus);

  connect(&EventHandler::Get(), &EventHandler::EventProjectionTypeChanged, this,
          &OpenGLWidget::HandleProjectionTypeChanged);
  connect(&EventHandler::Get(), &EventHandler::EventCameraModeChanged, this,
          &OpenGLWidget::HandleCameraModeChanged);
  connect(&EventHandler::Get(), &EventHandler::EventChangeOpenGLWidgetSize,
          this, &OpenGLWidget::AdjustSize);
  connect(&EventHandler::Get(), &EventHandler::EventAffineTransformationChanged,
          this, &OpenGLWidget::AssignAffineTransformations);
  connect(&EventHandler::Get(), &EventHandler::EventCloseFile, this,
          &OpenGLWidget::ClearMeshInformation);
}

OpenGLWidget::~OpenGLWidget() = default;

void OpenGLWidget::ClearMeshInformation() { mesh_.Unload(); }

void OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  mesh_.InitializeBuffers();
  renderer_.InitializeRenderingEnvironment();
  renderer_.SetupShaders();

  main_mesh_transform_.translation = {constants::kDefaultTranslation};
  main_mesh_transform_.rotation_angles = {constants::kDefaultRotationAngles};
  main_mesh_transform_.scaling = {constants::kDefaultScaling};
}

void OpenGLWidget::paintGL() {
  renderer_.ClearBuffersAndBackgroundColor();

  renderer_.BindShaderProgram();

  renderer_.UpdateProjectionMatrix(camera_.GetFieldOfView(),
                                   camera_.GetOrthoScale());
  renderer_.UpdateViewMatrix(camera_, mesh_.GetData().center);

  if (mesh_.GetData().indices.size() != 0 &&
      mesh_.GetData().vertices.size() != 0) {
    renderer_.UpdateModelMatrix(mesh_, main_mesh_transform_);
    renderer_.RenderMesh(mesh_);
  }

  renderer_.ReleaseShaderProgram();
  glReadPixels(0, 0, constants::kDefaultWidthForScreenCast,
               constants::kDefaultHeightForScreenCast, GL_RGBA,
               GL_UNSIGNED_BYTE, image_);
}

void OpenGLWidget::HandleProjectionTypeChanged() {
  if (Preferences::Get().GetProjectionType() == Projection::Type::kParallel) {
    camera_.ResetOrthographicScale();
  } else {
    camera_.SetPosition(constants::kDefaultCameraPosition);
  }
}

void OpenGLWidget::HandleCameraModeChanged() { ResetCameraProperties(); }

void OpenGLWidget::AssignAffineTransformations(
    const std::array<QVector3D, 3> &matrix) {
  main_mesh_transform_.translation = {matrix[0]};
  main_mesh_transform_.rotation_angles = {matrix[1]};
  main_mesh_transform_.scaling = {matrix[2]};
}

void OpenGLWidget::AdjustSize(const QSize &size) {
  resizeGL(size.width(), size.height());
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
  camera_.ProcessMousePress(event);
  update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  camera_.ProcessMouseMovement(event);
  update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)
  camera_.ProcessMouseRelease();
  update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
  camera_.ProcessMouseScroll(event, mesh_.GetData());
  update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
  camera_.ProcessKeyboard(event);
  update();
}

void OpenGLWidget::resizeGL(int width, int height) {
  resize(width, height);
  renderer_.HandleResizing(width, height);
}

void OpenGLWidget::UpdateFrame() { update(); }

void OpenGLWidget::LoadMeshData(const MeshData &data) {
  mesh_.Load(data);
  ResetCameraProperties();
}

void OpenGLWidget::ApplyInertialCameraMovement() {
  camera_.ApplyInertialMovement();
  update();
}

void OpenGLWidget::ResetCameraProperties() {
  camera_.ClampElevation();
  camera_.UpdateCameraVectors();
  if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
    camera_.SetLookAt({mesh_.GetData().center[0], mesh_.GetData().center[1],
                       mesh_.GetData().center[2]},
                      constants::kWorldUpVector);
  }
  camera_.SetPosition(constants::kDefaultCameraPosition);
}

void OpenGLWidget::Screencast() {
  QString exe_path{QCoreApplication::applicationDirPath()};
  QDir dir{exe_path};

  QString file_path{"./Screencast.gif"};
  int delay{constants::kDefaultDelayForScreenCast};
  int total_length{constants::kDefaultDurationScreenCast * 1000};
  GifWriter gif_writer{};

  GifBegin(&gif_writer, dir.filePath(file_path).toStdString().c_str(),
           constants::kDefaultWidthForScreenCast,
           constants::kDefaultHeightForScreenCast, delay);

  for (int timer{0}; timer <= total_length; timer += delay) {
    GifWriteFrame(&gif_writer, image_, constants::kDefaultWidthForScreenCast,
                  constants::kDefaultHeightForScreenCast, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds{delay});
  }

  GifEnd(&gif_writer);

  std::cerr << "Screencast saved at: " << dir.filePath(file_path).toStdString()
            << std::endl;
}

}  // namespace s21