#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_VIEWER_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_VIEWER_H_

#include <QWidget>

#include "View/opengl/OpenGLWidget/OpenGLWidget.h"
#include "View/ui/EventHandler/EventHandler.h"

namespace s21 {
class ModelViewer final : public QWidget {
  Q_OBJECT

 public:
  explicit ModelViewer(QWidget *parent = nullptr,
                       Controller *controller = nullptr) {
    open_gl_widget_ = new OpenGLWidget(this, controller);

    connect(&EventHandler::Get(), &EventHandler::EventOpenGLWidgetRequired,
            this, &ModelViewer::OpenGlWidgetGive);

    connect(this, &ModelViewer::EventOpenGLWidgetGiven, &EventHandler::Get(),
            &EventHandler::OpenGLWidgetGiven);
  }

  ~ModelViewer() override = default;

  void OpenGlWidgetGive() { emit EventOpenGLWidgetGiven(open_gl_widget_); }

  [[nodiscard]] const OpenGLWidget *GetOpenGLWidget() const {
    return open_gl_widget_;
  }
 signals:
  void EventOpenGLWidgetGiven(OpenGLWidget *open_gl_widget);

 private:
  Controller *controller_;
  OpenGLWidget *open_gl_widget_;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_VIEWER_H_