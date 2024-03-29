#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_BAR_MENU_BAR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_BAR_MENU_BAR_H_

#include <QMenuBar>
#include <memory>

#include "View/ui/menuBar/MenuFile/MenuFile.h"
#include "View/ui/menuBar/MenuMedia/MenuMedia.h"
#include "View/ui/menuBar/MenuViews/MenuViews.h"
#include "View/ui/structs.h"
#include "View/ui/styles/styles.h"

namespace s21 {

class MenuBar final : public QMenuBar {
  Q_OBJECT
 public:
  explicit MenuBar(QWidget *parent = nullptr, Controller *controller = nullptr);

  void OpenPreferencesWindow();
  void CloseWindow();
  void OpenAboutWindow();

 signals:
  void EventOpenPreferencesWindow();
  void EventCloseWindow();
  void EventOpenAboutWindow();

 private:
  void UpdateStyle();

  QMenu *application_menu_;
  MenuFile *menu_file_;
  MenuViews *menu_views_;
  QMenu *menu_media_;
  QMenu *menu_help_;
};

}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_BAR_MENU_BAR_H_