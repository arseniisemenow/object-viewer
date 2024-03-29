#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_PREFERENCES_PREFERENCES_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_PREFERENCES_PREFERENCES_H_

#include <QColor>
#include <QDir>
#include <QList>
#include <QMetaType>
#include <QSettings>
#include <QVariant>
#include <iostream>

#include "View/ui/RecentFile/RecentFile.h"
#include "View/ui/structs.h"

#define S21_COMPANY_NAME "s21"
#define S21_GLOBAL_SETTINGS_NAME "settings"
#define S21_DOCK_WIDGET_SETTINGS_NAME "dock_widget_settings"
#define S21_RECENT_FILES_SETTINGS_NAME "recent_files_settings"

#define DARK_GRAY_HEX_COLOR ("#050505")
#define ORANGE_HEX_COLOR ("#D24D00")
#define SKY_BLUE_HEX_COLOR ("#09c4ce")
#define LIGHT_GRAY_HEX_COLOR ("#DADAE2")
#define GRAY_HEX_COLOR ("#7B807B")

#define S21_DEFAULT_BACKGROUND_COLOR DARK_GRAY_HEX_COLOR

#define S21_DEFAULT_VERTEX_COLOR LIGHT_GRAY_HEX_COLOR
#define S21_DEFAULT_EDGE_COLOR GRAY_HEX_COLOR

#define S21_DEFAULT_SCALE (50.0)

#define S21_DEFAULT_VERTEX_SIZE (4.0)
#define S21_DEFAULT_EDGE_SIZE (1.0)

#define S21_BIG_NUMBER (1000000)

#define S21_DEFAULT_CAMERA_SPEED_VALUE (1)

#define S21_DEFAULT_NEAR_PLANE_VALUE (1)
#define S21_DEFAULT_FAR_PLANE_VALUE (100000)

#define STRINGIFY(x) #x

namespace s21 {
class Preferences {
 public:
  static Preferences &Get() {
    static Preferences instance;
    return instance;
  }

  ~Preferences();

  void SaveSceneScale();
  void SaveProjectionType();
  void SaveBackgroundColor();
  void SaveVertexDisplayMethod();
  void SaveVertexColor();
  void SaveVertexSize();
  void SaveEdgeType();
  void SaveEdgeColor();
  void SaveEdgeSize();
  void SaveLastOpenedDir();
  void SaveCameraMode();
  void SaveCameraSpeed();
  void SaveNearPlane();
  void SaveFarPlane();

  void LoadSceneScale();
  void LoadProjectionType();
  void LoadBackgroundColor();
  void LoadVertexDisplayMethod();
  void LoadVertexColor();
  void LoadVertexSize();
  void LoadEdgeType();
  void LoadEdgeColor();
  void LoadEdgeSize();
  void LoadLastOpenedDir();
  void LoadCameraMode();
  void LoadCameraSpeed();
  void LoadNearPlane();
  void LoadFarPlane();

  void Load();
  void Save();

  double GetScale();

  int GetProjectionType();

  QColor GetBackgroundColor();

  int GetVertexDisplayMethod();
  QColor GetVertexColor();
  double GetVertexSize();

  int GetEdgeType();
  QColor GetEdgeColor();
  double GetEdgeSize();
  CameraMode GetCameraMode();
  int GetCameraSpeed();
  int GetNearPlane();
  int GetFarPlane();

  int SetScale(double);
  int SetProjectionType(Projection::Type);

  int SetBackgroundColor(QColor);

  int SetVertexDisplayMethod(Vertex::DisplayMethod);
  int SetVertexColor(QColor);
  int SetVertexSize(double);

  int SetEdgeType(Edge::Type);
  int SetEdgeColor(QColor);
  int SetEdgeSize(double);

  int SetCameraMode(CameraMode cameraMode);
  int SetCameraSpeed(int newCameraSpeed);
  int SetNearPlane(int newNearPlane);
  int SetFarPlane(int newFarPlane);

  QSettings *settings;
  QSettings *dock_widget_settings;
  QSettings *recent_files_settings;

 private:
  Preferences() {
    settings = new QSettings(S21_COMPANY_NAME, S21_GLOBAL_SETTINGS_NAME);
    dock_widget_settings =
        new QSettings(S21_COMPANY_NAME, S21_DOCK_WIDGET_SETTINGS_NAME);
    recent_files_settings =
        new QSettings(S21_COMPANY_NAME, S21_RECENT_FILES_SETTINGS_NAME);
  };

  /*
   * Object parameters
   */
  double m_sceneScale = S21_DEFAULT_SCALE;
  /*
   * Viewer parameters
   */

  int projection_type_ = Projection::Type::kPerspective;

  QColor background_color_ = S21_DEFAULT_BACKGROUND_COLOR;

  int vertex_display_method_ = Vertex::DisplayMethod::kCircle;
  QColor vertex_color_ = S21_DEFAULT_VERTEX_COLOR;
  double vertex_size_ = S21_DEFAULT_VERTEX_SIZE;

  int edge_type_ = Edge::Type::kSolid;
  QColor edge_color_ = S21_DEFAULT_EDGE_COLOR;
  double edge_size_ = S21_DEFAULT_EDGE_SIZE;

  CameraMode camera_mode_ = CameraMode::kFly;
  int camera_speed_ = S21_DEFAULT_CAMERA_SPEED_VALUE;

  int near_plane_ = S21_DEFAULT_NEAR_PLANE_VALUE;
  int far_plane_ = S21_DEFAULT_FAR_PLANE_VALUE;

  /*
   * Current Object information
   */

  QString file_dir_{};
  int vertex_count_{};
  int edge_count_{};

  /*
   * Recent files
   */
  int recent_files_count_{0};
  QVector<RecentFile> recent_files_{};

  QString last_opened_dir_{};
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_PREFERENCES_PREFERENCES_H_