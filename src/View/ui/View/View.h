#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_VIEW_VIEW_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_VIEW_VIEW_H_

#include "Controller/Controller.h"
#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/FileHandler/FileHandler.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/StatusBar/StatusBar.h"
#include "View/ui/TransformWidget/TransformWidget.h"
#include "View/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h"
#include "View/ui/dockWidgets/DockWidgetSettings/DockWidgetSettings.h"
#include "View/ui/menuBar/MenuBar/MenuBar.h"
#include "View/ui/menuBar/MenuFile/MenuFile.h"
#include "View/ui/menuBar/MenuViews/MenuViews.h"
#include "View/ui/modalWidgets/AboutWindow/AboutWindow.h"
#include "View/ui/modalWidgets/PreferencesWindow/PreferencesWindow.h"
#include "View/ui/styles/styles.h"
#include "View/ui/userInteractionWidgets/ModelEditor.h"
#include "View/ui/userInteractionWidgets/ModelViewer.h"

#define S21_MIN_MODEL_EDITOR_WIDTH (30)

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~View() override;
  void HandleWidgetSizeChanged();

 public slots:
  void SetMenu();
  void SetProgressBar();

  void LoadPreferences();
  void SavePreferences();

  void SetCorners();

  void SetModelEditorDockWidget();
  void SetSettingsDockWidget();
  void SetDockWidgets();

  void SetModelViewer();

  void OpenPreferencesWindow() const;
  void ClosePreferencesWindow() const;

  void OpenAboutWindow() const;
  void CloseAboutWindow() const;

  void CloseWindow();

  void mousePressEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      const QPoint pressed_pos = event->pos();
      EventHandler::Get().LeftMouseButtonPressed(pressed_pos);
    }

    QWidget::mousePressEvent(event);
  }

  void mouseReleaseEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      const QPoint released_pos = event->pos();
      EventHandler::Get().LeftMouseButtonReleased(released_pos);
    }

    QWidget::mouseReleaseEvent(event);
  }

  void ChangeOpenGLWidgetSize(QSize gl_new_size);

  void WidgetSizeChanged() { emit EventWidgetSizeChanged(); }

 signals:
  void EventChangeOpenGlWidgetSize(QSize gl_new_size);
  void EventWidgetSizeChanged();
  void UpdateStyles();

 protected:
  void resizeEvent(QResizeEvent *event) override {
    WidgetSizeChanged();
    QMainWindow::resizeEvent(event);
  }

 private:
  Controller *controller_;

  ModelViewer *model_viewer_;
  ModelEditor *model_editor_;
  PreferencesWindow *preferences_window_;
  AboutWindow *about_window_;

  DockWidgetSettings *dock_widget_settings_;
  DockWidgetModelEditor *dock_widget_model_editor_;

  MenuBar *menu_bar_;
  StatusBar *status_bar_;
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_VIEW_VIEW_H_