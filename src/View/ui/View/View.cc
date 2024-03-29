#include "View.h"

namespace s21 {
View::View(QWidget *parent, Controller *controller)
    : QMainWindow(parent),
      controller_(controller),
      about_window_(new AboutWindow()) {
  EventHandler::Get();
  Preferences::Get();
  FileHandler::Get(controller);

  preferences_window_ = new PreferencesWindow(this);

  model_viewer_ = new ModelViewer(this, controller);
  model_editor_ = new ModelEditor(this);

  connect(&EventHandler::Get(), &EventHandler::EventOpenPreferencesWindow, this,
          &View::OpenPreferencesWindow);
  connect(&EventHandler::Get(), &EventHandler::EventOpenAboutWindow, this,
          &View::OpenAboutWindow);
  connect(&EventHandler::Get(), &EventHandler::EventCloseMainWindow, this,
          &View::CloseWindow);
  connect(&FileHandler::Get(controller), &FileHandler::FileLoaded,
          model_viewer_->GetOpenGLWidget(), &OpenGLWidget::LoadMeshData);

  connect(this, &View::EventWidgetSizeChanged, &EventHandler::Get(),
          &EventHandler::WidgetSizeChanged);

  connect(&EventHandler::Get(), &EventHandler::EventWidgetSizeChanged, this,
          &View::HandleWidgetSizeChanged);

  connect(this, &View::EventChangeOpenGlWidgetSize, &EventHandler::Get(),
          &EventHandler::ChangeOpenGLWidgetSize);

  setGeometry(100, 100, 1280, 720);

  LoadPreferences();

  UpdateStyles();

  SetCorners();

  SetDockWidgets();

  SetMenu();
  SetProgressBar();

  SetModelViewer();
}

void View::HandleWidgetSizeChanged() {
  const QSize main_window_size = this->size();
  const QSize dock_widget_settings_size = dock_widget_settings_->size();
  const QSize dock_widget_model_editor_size = dock_widget_model_editor_->size();

  const int dock_widget_mode_editor_width =
      dock_widget_model_editor_size.width() *
      dock_widget_model_editor_->GetIsVisible();

  const int gl_new_width =
      main_window_size.width() - dock_widget_mode_editor_width;
  const int gl_new_height =
      main_window_size.height() - dock_widget_settings_size.height();

  const QSize gl_new_size(gl_new_width, gl_new_height);
  ChangeOpenGLWidgetSize(gl_new_size);
}

void View::ChangeOpenGLWidgetSize(const QSize gl_new_size) {
  emit EventChangeOpenGlWidgetSize(gl_new_size);
}

View::~View() = default;

void View::SetDockWidgets() {
  SetSettingsDockWidget();
  SetModelEditorDockWidget();
}

void View::SetCorners() {
  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void View::SetProgressBar() {
  status_bar_ = new StatusBar();
  setStatusBar(status_bar_);
}

void View::SetMenu() {
  menu_bar_ = new MenuBar(this, controller_);
  this->setMenuBar(menu_bar_);
}

void View::LoadPreferences() { Preferences::Get().Load(); }

void View::SavePreferences() { Preferences::Get().Save(); }

void View::SetSettingsDockWidget() {
  dock_widget_settings_ = new DockWidgetSettings(this);

  dock_widget_settings_->setFeatures(
      DockWidgetModelEditor::NoDockWidgetFeatures);

  const auto title_bar_widget = new QWidget;
  title_bar_widget->setFixedHeight(0);

  dock_widget_settings_->setTitleBarWidget(title_bar_widget);

  addDockWidget(Qt::BottomDockWidgetArea, dock_widget_settings_);
}

void View::SetModelViewer() { setCentralWidget(model_viewer_); }

void View::SetModelEditorDockWidget() {
  dock_widget_model_editor_ = new DockWidgetModelEditor();
  const auto transform_widget = new TransformWidget(this);

  dock_widget_model_editor_->setWidget(transform_widget);
  addDockWidget(Qt::RightDockWidgetArea, dock_widget_model_editor_);
  dock_widget_model_editor_->setFeatures(
      DockWidgetModelEditor::NoDockWidgetFeatures);
}

void View::OpenPreferencesWindow() const {
  preferences_window_->LoadSettings();
  preferences_window_->show();
}

void View::ClosePreferencesWindow() const { preferences_window_->close(); }

void View::OpenAboutWindow() const { about_window_->show(); }

void View::CloseAboutWindow() const { about_window_->close(); }

void View::CloseWindow() {
  //    Preferences::get().save();
  ClosePreferencesWindow();
  CloseAboutWindow();
  this->close();
}
}  // namespace s21
