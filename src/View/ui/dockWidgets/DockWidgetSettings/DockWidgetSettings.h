#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_SETTINGS_DOCK_WIDGET_SETTINGS_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_SETTINGS_DOCK_WIDGET_SETTINGS_H_

#include <QComboBox>
#include <QDebug>
#include <QDockWidget>
#include <QEvent>
#include <QFile>
#include <QLabel>
#include <QMoveEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QSplitter>
#include <QVBoxLayout>
#include <iostream>

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/styles/styles.h"

#define FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET (130)
#define FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET (18)
#define PROJECTION_TYPE_PERSPECTIVE_STRING "Perspective"
#define PROJECTION_TYPE_PARALLEL_STRING "Parallel"

#define CAMERA_MODE_FLY_STRING "Fly"
#define CAMERA_MODE_TURNABLE_STRING "Turnable"

#define DOCK_WIDGET_MARGIN_VALUE (4)

#define OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_DEFAULT "hideRightDockButton"
#define OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_CHECKED "hideRightDockButton_checked"

#define OBJECT_NAME_CAMERA_ICON_LABEL "cameraIconLabel"

namespace s21 {

namespace ProjectionTypeComboBoxIndex {
typedef enum {
  kPerspective = 0,
  kParallel = 1,
} ProjectionTypeComboBoxIndex;
}

namespace CameraModeComboBoxIndex {
typedef enum {
  kFly = 0,
  kTurnable = 1,
} CameraModeComboBoxIndex;
}

class DockWidgetSettings final : public QDockWidget {
  Q_OBJECT

 public:
  explicit DockWidgetSettings(QWidget *parent = nullptr);

 signals:
  void EventProjectionTypeChanged();
  void EventCameraModeChanged();
  void EventToggleRightDockWidget();

 private:
  void ToggleChecked();

  void SetCameraIconLabel() const;

  void SetProjectionTypeComboBox() const;

  void SetHideDockButton();

  void SetLayoutForWidget() const;

  void SetCameraModeComboBox() const;

  void UpdateDockWidgetModelEditorButtonStatus();

  void HandleProjectionTypeChanged(int index);
  void HandleCameraModeChanged(int index);

  void SaveProjectionTypeSettings() const;
  void LoadProjectionTypeSettings() const;

  void SaveCameraModeSettings() const;
  void LoadCameraModeSettings() const;
  void UpdateDockWidget();

  void ProjectionTypeChanged() { emit EventProjectionTypeChanged(); }
  void CameraModeChanged() { emit EventCameraModeChanged(); }
  void UpdateHideRightDockWidgetButtonStyle();
  void UpdateStyles();

  QLabel *camera_icon_label_;
  QComboBox *projection_type_combo_box_;
  QComboBox *camera_mode_combo_box_;
  QPushButton *hide_right_dock_button_;

  QWidget *central_widget_;
  QHBoxLayout *layout_;

  bool is_right_dock_button_checked_;
};

}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_SETTINGS_DOCK_WIDGET_SETTINGS_H_