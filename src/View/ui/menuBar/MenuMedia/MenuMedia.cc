#include "MenuMedia.h"

namespace s21 {

MenuMedia::MenuMedia(const QString &title) {
  setTitle(title);

  create_image_action_ = new QAction(ACTION_TITLE_CREATE_IMAGE);
  create_animation_action_ = new QAction(ACTION_TITLE_CREATE_ANIMATION);

  connect(this, &MenuMedia::EventRequireOpenGlWidget, &EventHandler::Get(),
          &EventHandler::OpenGLWidgetRequired);
  connect(&EventHandler::Get(), &EventHandler::EventOpenGLWidgetGiven, this,
          [=](OpenGLWidget *open_gl_widget) {
            media_processor_ = new MediaProcessor(this, open_gl_widget);
            connect(create_image_action_, &QAction::triggered, this,
                    [this]() { media_processor_->CaptureAndSaveImage(); });
            connect(create_animation_action_, &QAction::triggered, this,
                    [this]() { media_processor_->CaptureAndSaveAnimation(); });
          });

  RequireOpenGlWidget();

  addAction(create_image_action_);
  addAction(create_animation_action_);
}

}  // namespace s21