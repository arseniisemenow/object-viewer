#include "MenuViews.h"

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h"

namespace s21 {

MenuViews::MenuViews(const QString &title, QWidget *parent) {
  this->setTitle(title);

  action_model_editor_ = new QAction("Model Editor");
  action_model_editor_->setCheckable(true);
  SetCheckedStatusModelEditorAction(true);

  connect(action_model_editor_, &QAction::toggled, &EventHandler::Get(),
          &EventHandler::ToggleDockWidgetModelEditor);

  /* Set right action status when dock widget is toggled */
  connect(&EventHandler::Get(),
          &EventHandler::EventToggledDockWidgetModelEditor, this,
          &MenuViews::SetCheckedStatusModelEditorAction);

  dock_widget_actions_.append(action_model_editor_);

  for (QAction *action : dock_widget_actions_) {
    this->addAction(action);
  }
}

void MenuViews::SetCheckedStatusModelEditorAction(const bool visibility) const {
  /* Temporarily disabling all signals to prevent a feedback loop */
  action_model_editor_->blockSignals(true);
  action_model_editor_->setChecked(visibility);
  action_model_editor_->blockSignals(false);
}

}  // namespace s21