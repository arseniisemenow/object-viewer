#include "Camera.h"

#include <QObject>
#include <QtMath>
#include <cmath>

#include "View/ui/Preferences/Preferences.h"

namespace s21 {
Camera::Camera(const QVector3D& position, const QVector3D& world_up,
               float azimuth, float elevation)
    : position_{position},
      front_{constants::kDefaultFrontVector},
      world_up_{world_up},
      azimuth_{azimuth},
      elevation_{elevation},
      sensitivity_{constants::kDefaultSensitivity},
      field_of_view_{constants::kDefaultFieldOfView},
      zoom_speed_{constants::kDefaultZoomSpeed},
      ortho_scale_{constants::kDefaultOrthographicScale},
      inertial_movement_timer_{std::make_unique<QTimer>()} {
  connect(inertial_movement_timer_.get(), &QTimer::timeout, this,
          &Camera::ApplyInertialMovement);
  UpdateCameraVectors();
}

void Camera::ProcessKeyboard(QKeyEvent* event) {
  if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
    double speed_coefficient{0.2};
    double movement_speed{Preferences::Get().GetCameraSpeed() *
                          speed_coefficient};
    if (event->key() == Qt::Key_W) {
      position_ += movement_speed * front_;
    }
    if (event->key() == Qt::Key_S) {
      position_ -= movement_speed * front_;
    }
    if (event->key() == Qt::Key_A) {
      position_ -= movement_speed * right_;
    }
    if (event->key() == Qt::Key_D) {
      position_ += movement_speed * right_;
    }
  }
}

void Camera::ProcessMousePress(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    mouse_delta_ = QVector2D{0, 0};
    StopInertialMovement();
    last_mouse_position_ = event->pos();
    event->accept();
  }
}

void Camera::UpdateAnglesAndVectors(int delta_x, int delta_y) {
  azimuth_ += static_cast<float>(delta_x) * sensitivity_;
  elevation_ += static_cast<float>(delta_y) * sensitivity_;

  ClampElevation();
  UpdateCameraVectors();
}

void Camera::ProcessMouseMovement(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    QVector2D last_pos{last_mouse_position_};
    mouse_delta_ = QVector2D{event->pos()} - last_pos;

    const int delta_x{event->pos().x() - last_mouse_position_.x()};
    int delta_y{};
    if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
      delta_y = last_mouse_position_.y() - event->pos().y();
    } else {
      delta_y = event->pos().y() - last_mouse_position_.y();
    }

    UpdateAnglesAndVectors(delta_x, delta_y);

    last_mouse_position_ = event->pos();
    event->accept();
  }
}

void Camera::ProcessMouseScroll(QWheelEvent* event,
                                const MeshData& object_data) {
  if (Preferences::Get().GetCameraMode() == CameraMode::kTurnable) {
    const float delta{static_cast<float>(event->angleDelta().y())};
    position_.setZ(position_.z() + delta * zoom_speed_);
    if (position_.z() >=
        object_data.center[2] - constants::kMinimumDistanceToObjectCenter) {
      position_.setZ(object_data.center[2] -
                     constants::kMinimumDistanceToObjectCenter);
    }

    if (Preferences::Get().GetProjectionType() == Projection::Type::kParallel) {
      ortho_scale_ -= delta * constants::kOrthoScaleChangeSpeed;
      if (ortho_scale_ < constants::kMinimumOrthographicScale) {
        ortho_scale_ = constants::kMinimumOrthographicScale;
      }
    }
  }
}

void Camera::ProcessMouseRelease() { StartInertialMovement(); }

void Camera::SetPosition(const QVector3D& position) { position_ = position; }

QMatrix4x4 Camera::GetLookAtMatrix() const {
  QMatrix4x4 matrix{};
  matrix.lookAt(position_, front_ + position_, up_);
  return matrix;
}

void Camera::SetLookAt(const QVector3D& target, const QVector3D& up) {
  QMatrix4x4 view_matrix{};
  view_matrix.lookAt(position_, target, up);

  front_ = -view_matrix.column(2).toVector3D().normalized();
  right_ = view_matrix.column(0).toVector3D().normalized();
  up_ = view_matrix.column(1).toVector3D().normalized();

  azimuth_ = qRadiansToDegrees(std::atan2(-front_.x(), -front_.z())) - 90.0f;
  elevation_ = qRadiansToDegrees(std::asin(front_.y()));

  UpdateCameraVectors();
}

void Camera::ApplyInertialMovement() {
  if (Preferences::Get().GetCameraMode() == CameraMode::kTurnable) {
    mouse_delta_ *= constants::kInertialMovementDampingFactor;

    if (mouse_delta_.lengthSquared() < constants::kInertialMovementThreshold) {
      StopInertialMovement();
    }

    UpdateAnglesAndVectors(static_cast<int>(mouse_delta_.x()),
                           static_cast<int>(mouse_delta_.y()));
  }
}

void Camera::ResetOrthographicScale() {
  ortho_scale_ = constants::kDefaultOrthographicScale;
}

void Camera::ClampElevation() {
  if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
    elevation_ = qBound(-constants::kMaximumElevationAngle, elevation_,
                        constants::kMaximumElevationAngle);
  }
}

const QVector3D& Camera::GetPosition() const { return position_; }

const QPoint& Camera::GetLastMousePosition() const {
  return last_mouse_position_;
}

float Camera::GetAzimuth() const { return azimuth_; }

float Camera::GetElevation() const { return elevation_; }

float Camera::GetOrthoScale() const { return ortho_scale_; }

float Camera::GetFieldOfView() const { return field_of_view_; }

void Camera::UpdateCameraVectors() {
  front_.setX(std::cos(qDegreesToRadians(azimuth_)) *
              std::cos(qDegreesToRadians(elevation_)));
  front_.setY(std::sin(qDegreesToRadians(elevation_)));
  front_.setZ(std::sin(qDegreesToRadians(azimuth_)) *
              std::cos(qDegreesToRadians(elevation_)));
  front_ = front_.normalized();

  right_ = QVector3D::crossProduct(front_, world_up_).normalized();
  up_ = QVector3D::crossProduct(right_, front_).normalized();
}

void Camera::StartInertialMovement() const {
  if (Preferences::Get().GetCameraMode() == CameraMode::kTurnable) {
    if (!inertial_movement_timer_->isActive())
      inertial_movement_timer_->start(constants::kMillisecondsPerFrame);
  }
}

void Camera::StopInertialMovement() const {
  if (Preferences::Get().GetCameraMode() == CameraMode::kTurnable) {
    if (inertial_movement_timer_->isActive()) inertial_movement_timer_->stop();
  }
}

}  // namespace s21
