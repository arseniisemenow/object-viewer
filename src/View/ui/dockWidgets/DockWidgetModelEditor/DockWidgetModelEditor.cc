#include "DockWidgetModelEditor.h"

namespace s21 {
DockWidgetModelEditor::DockWidgetModelEditor() {
  is_visible_ = true;

  auto* title_bar = new TitleBar("Object properties", this);
  setTitleBarWidget(title_bar);

  connect(&EventHandler::Get(), &EventHandler::EventToggleDockWidgetModelEditor,
          this, &DockWidgetModelEditor::ToggleVisibility);
  connect(this, &DockWidgetModelEditor::EventToggledDockWidgetModelEditor,
          &EventHandler::Get(), &EventHandler::ToggledDockWidgetModelEditor);
  connect(this, &DockWidgetModelEditor::EventResized, &EventHandler::Get(),
          &EventHandler::EventWidgetSizeChanged);
};

DockWidgetModelEditor::~DockWidgetModelEditor() = default;

void DockWidgetModelEditor::ToggleVisibility() {
  if (is_visible_) {
    this->hide();
    is_visible_ = false;
  } else {
    this->show();
    is_visible_ = true;
  }

  ToggledDockWidgetModelEditor(is_visible_);
}

int DockWidgetModelEditor::GetIsVisible() const { return is_visible_; }

void DockWidgetModelEditor::resizeEvent(QResizeEvent* event) {
  emit EventResized();
  QDockWidget::resizeEvent(event);
}

void DockWidgetModelEditor::ToggledDockWidgetModelEditor(
    const bool visibility) {
  emit EventToggledDockWidgetModelEditor(visibility);
}
}  // namespace s21
