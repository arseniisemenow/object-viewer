#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_EVENT_HANDLER_EVENT_HANDLER_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_EVENT_HANDLER_EVENT_HANDLER_H_

#include "View/opengl/OpenGLWidget/OpenGLWidget.h"

namespace s21 {

class EventHandler final : public QObject {
  Q_OBJECT

 public:
  static EventHandler& Get() {
    static EventHandler instance;
    return instance;
  }

  ~EventHandler() override = default;

 private:
  EventHandler() = default;

 public slots:
  void OpenPreferencesWindow();
  void ClosePreferencesWindow();
  void OpenAboutWindow();
  void CloseAboutWindow();
  void CloseMainWindow();
  void RecentFilesChanged();
  void UpdateFileMenu();
  void OpenFileDialog();
  void CloseFile();

  void ApplySettings();
  void CancelSettings();
  void OkSettings();
  void ResetSettings();

  void OpenFile(const QString& file_name) { emit EventOpenFile(file_name); }

  void SelectButtonClicked() { emit EventSelectButtonClicked(); }

  void RecentFileActionClicked(const QString& file_path) {
    emit EventRecentFileActionClicked(file_path);
  }

  void FileDialogCloseWindow();
  void FileDialogUpdateSelectedPath(const QModelIndex& index);

  void ToggleDockWidgetModelEditor() {
    emit EventToggleDockWidgetModelEditor();
  }

  void ToggledDockWidgetModelEditor(const bool visibility) {
    WidgetSizeChanged();
    emit EventToggledDockWidgetModelEditor(visibility);
  }

  void LeftMouseButtonPressed(const QPoint& pressed_pos) {
    emit EventLeftMouseButtonPressed(pressed_pos);
  }

  void LeftMouseButtonReleased(const QPoint& released_pos) {
    emit EventLeftMouseButtonReleased(released_pos);
  }

  void ProjectionTypeChanged() { emit EventProjectionTypeChanged(); }

  void CameraModeChanged() { emit EventCameraModeChanged(); }

  void ChangeOpenGLWidgetSize(const QSize gl_new_size) {
    emit EventChangeOpenGLWidgetSize(gl_new_size);
  }

  void WidgetSizeChanged() { emit EventWidgetSizeChanged(); }

  void OpenFileInformation() { emit EventOpenFileInformation(); }

  void OpenGLWidgetRequired() { emit EventOpenGLWidgetRequired(); }

  void OpenGLWidgetGiven(OpenGLWidget* open_gl_widget) {
    emit EventOpenGLWidgetGiven(open_gl_widget);
  }

  void ClearSpinBoxes() { emit EventClearSpinBoxes(); }

  void LoadAnotherModel() { emit EventLoadAnotherModel(); }

 signals:
  void EventOpenPreferencesWindow();
  void EventClosePreferencesWindow();
  void EventOpenAboutWindow();
  void EventCloseAboutWindow();
  void EventCloseMainWindow();
  void EventRecentFilesChanged();
  void EventUpdateFileMenu();
  void EventOpenFileDialog();
  void EventCloseFile();

  void EventApplySettings();
  void EventCancelSettings();
  void EventOkSettings();
  void EventResetSettings();

  void EventRecentFileActionClicked(const QString&);
  void EventOpenFile(const QString&);
  void EventSelectButtonClicked();
  void EventFileDialogCloseWindow();
  void EventFileDialogUpdateSelectedPath(const QModelIndex& index);

  void EventToggleDockWidgetModelEditor();
  void EventToggledDockWidgetModelEditor(bool visibility);

  void EventLeftMouseButtonPressed(const QPoint& pressed_pos);
  void EventLeftMouseButtonReleased(const QPoint& released_pos);

  void EventProjectionTypeChanged();
  void EventCameraModeChanged();

  void EventChangeOpenGLWidgetSize(QSize new_size);

  void EventWidgetSizeChanged();

  void EventAffineTransformationChanged(const std::array<QVector3D, 3>& matrix);

  void EventOpenFileInformation();

  void EventOpenGLWidgetRequired();

  void EventOpenGLWidgetGiven(OpenGLWidget* open_gl_widget);

  void EventClearSpinBoxes();
  void EventLoadAnotherModel();
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_EVENT_HANDLER_EVENT_HANDLER_H_
