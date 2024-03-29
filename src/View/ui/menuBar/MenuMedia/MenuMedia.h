#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_MEDIA_MENU_MEDIA_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_MEDIA_MENU_MEDIA_H_

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QVector>

#include "View/opengl/OpenGLWidget/OpenGLWidget.h"
#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/MediaProcessor/MediaProcessor.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/styles/styles.h"

#define ACTION_TITLE_CREATE_IMAGE "Create image"
#define ACTION_TITLE_CREATE_ANIMATION "Create animation"

namespace s21 {

class MenuMedia final : public QMenu {
  Q_OBJECT

 public:
  explicit MenuMedia(const QString &title = "Default Title");

  void RequireOpenGlWidget() { emit EventRequireOpenGlWidget(); }

 private:
  QAction *create_image_action_;
  QAction *create_animation_action_;

  MediaProcessor *media_processor_;

 signals:
  void EventRequireOpenGlWidget();
};

}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_MEDIA_MENU_MEDIA_H_