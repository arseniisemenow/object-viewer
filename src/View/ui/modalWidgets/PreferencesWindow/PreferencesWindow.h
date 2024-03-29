#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_PREFERENCES_WINDOW_PREFERENCES_WINDOW_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_PREFERENCES_WINDOW_PREFERENCES_WINDOW_H_

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/menuBar/MenuBar/MenuBar.h"
#include "ui_PreferencesWindow.h"

namespace Ui {
class PreferencesWindow;
}
namespace s21 {

class PreferencesWindow final : public QDialog {
  Q_OBJECT

 public:
  explicit PreferencesWindow(QWidget *parent);
  ~PreferencesWindow() override;
  void UpdateStyles();

  void OpenPreferencesWindow() { emit EventOpenPreferencesWindow(); }

  void LockMainWindowInteraction();
  void SetButtonsConnections();

  void SaveBackgroundColor();
  void SaveCameraSpeed();
  void SaveNearPlane();
  void SaveFarPlane();

  void SaveVertexDisplayMethod();
  void SaveVertexColor();
  void SaveVertexSize();

  void SaveEdgeType();
  void SaveEdgeColor();
  void SaveEdgeSize();

  void SaveSettings();

  void LoadBackgroundColor();
  void LoadCameraSpeed();
  void LoadNearPlane();
  void LoadFarPlane();

  void LoadVertexDisplayMethodSettings();
  void LoadVertexColor();
  void LoadVertexSize();

  void LoadEdgeTypeSettings();
  void LoadEdgeColor();
  void LoadEdgeSize();

  void LoadSettings();

  void HandleApplyButtonClick();
  void HandleCancelButtonClick();
  void HandleOkButtonClick();
  void HandleResetSettingsButtonClick();

  void CloseWindow();
 signals:
  void EventOpenPreferencesWindow();

 private:
  Ui::PreferencesWindow *ui_;
};

namespace VertexDisplayMethodComboBoxIndex {
typedef enum {
  kNone = 0,
  kCircle = 1,
  kSquare = 2,
} VertexDisplayMethodComboBoxIndex;
}

namespace EdgeTypeComboBoxIndex {

typedef enum {
  kSolid = 0,
  kDashed = 1,
} EdgeTypeComboBoxIndex;

}
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_PREFERENCES_WINDOW_PREFERENCES_WINDOW_H_