#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CONSTANTS_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CONSTANTS_H_

#include <QVector3D>
#include <QVector4D>

namespace s21::constants {
inline constexpr int kNumberOfVertexCoordinates{3};
inline constexpr int kNumberOfEdgePoints{2};

inline constexpr float kDefaultAzimuthAngle{-90.0f};
inline constexpr float kDefaultElevationAngle{0.0f};
inline constexpr float kDefaultFieldOfView{45.0f};
inline constexpr float kDefaultPerspectiveNearPlane{0.1f};
inline constexpr float kDefaultPerspectiveFarPlane{10000.0f};
inline constexpr float kDefaultOrthographicNearPlane{-1000.0f};
inline constexpr float kDefaultOrthographicFarPlane{1000.0f};
inline constexpr float kDefaultOrthographicScale{2.0f};
inline constexpr float kDefaultEdgeWidth{1.0f};
inline constexpr float kDefaultPointSize{1.0f};
inline constexpr float kDefaultSensitivity{0.2f};
inline constexpr float kDefaultZoomSpeed{0.0075f};
inline constexpr QVector4D kDefaultBackgroundColor{0.0f, 0.0f, 0.0f, 1.0f};
inline constexpr QVector3D kDefaultEdgeColor{1.0f, 1.0f, 1.0f};
inline constexpr QVector3D kDefaultPointColor{1.0f, 1.0f, 1.0f};
inline constexpr QVector3D kDefaultTranslation{0.0f, 0.0f, 0.0f};
inline constexpr QVector3D kDefaultRotationAngles{0.0f, 0.0f, 0.0f};
inline constexpr QVector3D kDefaultScaling{1.0f, 1.0f, 1.0f};
inline constexpr float kDefaultCameraSpeed{0.05f};
inline constexpr QVector3D kDefaultCameraPosition{0.0f, 0.0f, -5.0f};
inline constexpr QVector3D kDefaultFrontVector{0.0f, 0.0f, 1.0f};
inline constexpr QVector3D kWorldUpVector{0.0f, 1.0f, 0.0f};

inline constexpr float kOrthoScaleChangeSpeed{0.002f};
inline constexpr float kInertialMovementDampingFactor{0.95f};
inline constexpr float kInertialMovementThreshold{0.01f};

inline constexpr float kMinimumFieldOfView{1.0f};
inline constexpr float kMaximumFieldOfView{80.0f};
inline constexpr float kMaximumElevationAngle{89.0f};
inline constexpr float kMinimumOrthographicScale{1.0f};
inline constexpr float kMinimumDistanceToObjectCenter{2.0f};

inline constexpr QVector3D kXAxis{1.0f, 0.0f, 0.0f};
inline constexpr QVector3D kYAxis{0.0f, 1.0f, 0.0f};

inline constexpr int kMillisecondsPerFrame{16};

inline constexpr int kDefaultWidthForScreenCast{640};
inline constexpr int kDefaultHeightForScreenCast{480};
inline constexpr int kDefaultDelayForScreenCast{100};
inline constexpr int kDefaultDurationScreenCast{5};

}  // namespace s21::constants

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_OPENGL_CONSTANTS_H_