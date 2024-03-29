#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_

#include <QLineEdit>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>
#include <iostream>

#include "View/ui/EventHandler/EventHandler.h"

namespace s21 {
class SpinBoxLineEdit final : public QLineEdit {
  Q_OBJECT

 public:
  SpinBoxLineEdit(double &init_value, double multiplier,
                  QWidget *parent = nullptr);

  void HandleClickInWidget(const QPoint &click_pos);

  [[nodiscard]] double GetValue() const { return current_value_; }

  void SetValue(double new_value);

 public slots:
  void UpdateCurrentValue(const QString &text);

 signals:
  void EventValueChanged(double);
  void FocusOut();

 protected:
  void mousePressEvent(QMouseEvent *event) override;

  void focusOutEvent(QFocusEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

  [[nodiscard]] bool IsClickInsideTextRect(const QPoint &click_pos) const;
 signals:
  void EventEditingFinished(double value);

 private:
  double &current_value_;
  bool is_editable_;
  double multiplier_;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_