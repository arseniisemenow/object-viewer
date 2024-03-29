#include "ColorPushButton.h"

ColorPushButton::ColorPushButton(QWidget* parent) : QPushButton(parent) {
  connect(this, &ColorPushButton::clicked, this, &ColorPushButton::ChangeColor);
}

void ColorPushButton::UpdateButtonTitle(const QString& color_string) {
  setText(hex_color_code_);
  update();
}

void ColorPushButton::UpdateData(const QColor& color) {
  hex_color_code_ = color.name(QColor::HexRgb).toUpper();
  color_ = color;
  UpdateButtonTitle(hex_color_code_);
}

void ColorPushButton::paintEvent(QPaintEvent* event) {
  QPushButton::paintEvent(event);
  const QRect rect = this->rect();

  const int rounded_square_size = rect.height() - (rect.height() / 2);
  const int x = rect.right() - rounded_square_size - (rect.height() / 4);
  const int y = rect.top() + (rect.height() / 4);

  const QRect rounded_rect{x, y, rounded_square_size, rounded_square_size};

  QPainter painter(this);
  constexpr QColor border_color(100, 100, 100);

  painter.setPen(QPen(border_color, 0));
  painter.setBrush(QColor(hex_color_code_));
  painter.drawRoundedRect(rounded_rect, rounded_square_size,
                          rounded_square_size);
}

void ColorPushButton::ChangeColor() {
  QColorDialog dialog(QColor(hex_color_code_), this);
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  if (dialog.exec()) {
    UpdateData(dialog.currentColor());
  }
}

QColor ColorPushButton::GetColor() const { return color_; }