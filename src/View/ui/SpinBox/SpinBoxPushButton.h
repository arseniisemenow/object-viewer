#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#define DELTA_VALUE (1)

namespace s21 {
class SpinBoxPushButton final : public QPushButton {
  Q_OBJECT

 public:
  SpinBoxPushButton(double &initValue, double multiplier,
                    QWidget *parent = nullptr);

  double GetValue();

  void SetValue(double newValue);

 protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

#ifdef Q_OS_MACOS

  void enterEvent(QEnterEvent *event) override;

#elif defined(Q_OS_LINUX)

  void enterEvent(QEvent *event) override;

#endif  // Q_OS_MACOS

  void leaveEvent(QEvent *event) override;

 signals:
  void EventValueChanged(double);

 private:
  void SetupUi();
  [[nodiscard]] double GetSingleStep() const;
  void UpdateButtonText();

  bool is_mouse_pressed_ = false;
  QPoint last_mouse_pos_;
  double &current_value_;
  double multiplier_;
  double step_size_{};
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_