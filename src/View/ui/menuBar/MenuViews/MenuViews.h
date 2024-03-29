#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_VIEWS_MENU_VIEWS_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_VIEWS_MENU_VIEWS_H_

#include <QAction>
#include <QDockWidget>
#include <QMenu>

#include "View/ui/structs.h"

namespace s21 {
class MenuViews final : public QMenu {
  Q_OBJECT

 public:
  explicit MenuViews(const QString &title, QWidget *parent = nullptr);

  void SetCheckedStatusModelEditorAction(bool visibility) const;

 private:
  QList<QAction *> dock_widget_actions_;
  QAction *action_model_editor_;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_VIEWS_MENU_VIEWS_H_