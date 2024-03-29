#include "TitleBar.h"

namespace s21 {

TitleBar::TitleBar(const QString &title, QWidget *parent) : QWidget(parent) {
  layout_ = new QHBoxLayout(this);
  layout_->setContentsMargins(0, 0, 0, 0);

  title_label_ = new QLabel(title, this);
  UpdateStyles();

  layout_->addWidget(title_label_);
}

TitleBar::~TitleBar() = default;

void TitleBar::UpdateStyles() const {
  title_label_->setStyleSheet(GetStylesFromFile(PATH_TITLE_BAR_STYLES_FILE));
}

}  // namespace s21