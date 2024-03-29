#include "SpinBoxPushButton.h"

namespace s21 {
SpinBoxPushButton::SpinBoxPushButton(double& initValue, double multiplier,
                                     QWidget* parent)
    : current_value_(initValue), multiplier_(multiplier) {
  setMinimumWidth(100);
  setMaximumWidth(200);
  SetupUi();
}

double SpinBoxPushButton::GetValue() { return current_value_; }

void SpinBoxPushButton::SetValue(double newValue) {
  current_value_ = newValue;

  step_size_ = (multiplier_ == multiplier_) ? multiplier_ : DELTA_VALUE;

  UpdateButtonText();
  emit EventValueChanged(current_value_);
}

void SpinBoxPushButton::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_mouse_pressed_ = true;
    last_mouse_pos_ = event->pos();
  }

  QPushButton::mousePressEvent(event);
}

void SpinBoxPushButton::mouseReleaseEvent(QMouseEvent* event) {
  is_mouse_pressed_ = false;
  QPushButton::mouseReleaseEvent(event);
}

void SpinBoxPushButton::mouseMoveEvent(QMouseEvent* event) {
  if (is_mouse_pressed_) {
    double deltaX = event->pos().x() - last_mouse_pos_.x();
    double deltaValue = deltaX / GetSingleStep();
    double newValue = current_value_ + deltaValue;
    SetValue(newValue);
    last_mouse_pos_ = event->pos();
  }

  QPushButton::mouseMoveEvent(event);
}
#ifdef Q_OS_MACOS
void SpinBoxPushButton::enterEvent(QEnterEvent* event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#elif defined(Q_OS_LINUX)
void SpinBoxPushButton::enterEvent(QEvent* event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#endif  // Q_OS_MACOS
void SpinBoxPushButton::leaveEvent(QEvent* event) {
  unsetCursor();
  QPushButton::leaveEvent(event);
}

void SpinBoxPushButton::SetupUi() {
  setFocusPolicy(Qt::NoFocus);

  setText(QString::number(current_value_));
}

double SpinBoxPushButton::GetSingleStep() const {
  return DELTA_VALUE / step_size_;
}

void SpinBoxPushButton::UpdateButtonText() {
  setText(QString::number(current_value_));
}
}  // namespace s21
