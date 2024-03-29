#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CAMERA_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CAMERA_H_

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QVector3D>
#include <QWheelEvent>

#include "Constants.h"
#include "common/MeshData.h"

namespace s21 {
class Camera final : public QObject {
 public:
  Camera(const QVector3D &position, const QVector3D &up,
         float azimuth = constants::kDefaultAzimuthAngle,
         float elevation = constants::kDefaultElevationAngle);

  void ProcessKeyboard(QKeyEvent *event);
  void ProcessMousePress(QMouseEvent *event);
  void ProcessMouseMovement(QMouseEvent *event);
  void ProcessMouseScroll(QWheelEvent *event, const MeshData &object_data);
  void ProcessMouseRelease();

  void SetPosition(const QVector3D &position);
  void UpdateAnglesAndVectors(int delta_x, int delta_y);
  void UpdateCameraVectors();

  void SetLookAt(const QVector3D &target, const QVector3D &up);
  [[nodiscard]] QMatrix4x4 GetLookAtMatrix() const;

  void ApplyInertialMovement();

  void ResetOrthographicScale();
  void ClampElevation();

  [[nodiscard]] const QVector3D &GetPosition() const;
  [[nodiscard]] const QPoint &GetLastMousePosition() const;
  [[nodiscard]] float GetAzimuth() const;
  [[nodiscard]] float GetElevation() const;
  [[nodiscard]] float GetOrthoScale() const;
  [[nodiscard]] float GetFieldOfView() const;

 private:
  void StartInertialMovement() const;
  void StopInertialMovement() const;

 private:
  QVector3D position_{};
  QVector3D front_{};
  QVector3D right_{};
  QVector3D up_{};
  QVector3D world_up_{};

  float azimuth_{};
  float elevation_{};
  float sensitivity_{};

  float field_of_view_{};
  float zoom_speed_{};
  float ortho_scale_{};

  QPoint last_mouse_position_{};

  std::unique_ptr<QTimer> inertial_movement_timer_{};
  QVector2D mouse_delta_{};
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CAMERA_H_