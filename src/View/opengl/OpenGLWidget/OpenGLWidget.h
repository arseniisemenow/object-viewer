#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_OPENGL_WIDGET_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_OPENGL_WIDGET_H_

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <thread>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <OpenGL/gl.h>
#endif  // QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

#include <QCoreApplication>
#include <QFileDialog>

#include "Controller/Controller.h"
#include "Gif/Gif.h"
#include "View/opengl/Camera.h"
#include "View/opengl/Constants.h"
#include "View/opengl/Mesh.h"
#include "View/opengl/Renderer.h"

namespace s21 {
class OpenGLWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  OpenGLWidget(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~OpenGLWidget() override;

  void LoadMeshData(const MeshData &data);

  void Screencast();

 public slots:
  void HandleProjectionTypeChanged();
  void HandleCameraModeChanged();
  void AssignAffineTransformations(const std::array<QVector3D, 3> &matrix);
  void AdjustSize(const QSize &size);
  void ClearMeshInformation();

 private slots:
  void UpdateFrame();

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Camera camera_;
  Mesh mesh_;
  Renderer renderer_;
  Transform main_mesh_transform_{};
  void ApplyInertialCameraMovement();
  void ResetCameraProperties();

  uint8_t image_[constants::kDefaultWidthForScreenCast * 2 *
                 constants::kDefaultHeightForScreenCast * 2 * 4]{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_OPENGL_WIDGET_H_
