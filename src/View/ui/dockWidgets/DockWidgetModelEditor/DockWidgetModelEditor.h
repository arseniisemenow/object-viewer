#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_MODEL_EDITOR_DOCK_WIDGET_MODEL_EDITOR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_MODEL_EDITOR_DOCK_WIDGET_MODEL_EDITOR_H_

#include <QtGui/qevent.h>

#include <QDockWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/TitleBar/TitleBar.h"
#include "View/ui/TransformWidget/TransformWidget.h"

namespace s21 {
class DockWidgetModelEditor final : public QDockWidget {
  Q_OBJECT

 public:
  DockWidgetModelEditor();
  ~DockWidgetModelEditor() override;

  void ToggleVisibility();
  [[nodiscard]] int GetIsVisible() const;

 signals:
  void EventToggledDockWidgetModelEditor(bool isVisible);
  void EventResized();

 private:
  void resizeEvent(QResizeEvent *event) override;
  void ToggledDockWidgetModelEditor(const bool visibility);

  bool is_visible_;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_DOCK_WIDGETS_DOCK_WIDGET_MODEL_EDITOR_DOCK_WIDGET_MODEL_EDITOR_H_
