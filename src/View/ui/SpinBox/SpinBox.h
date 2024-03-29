#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_H_

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "SpinBoxLineEdit.h"
#include "SpinBoxPushButton.h"

namespace s21 {

class SpinBox : public QWidget {
  Q_OBJECT

 public:
  explicit SpinBox(double initial_value = 0, double multiplier = 1,
                   QWidget *parent = nullptr);

  [[nodiscard]] double GetValue() const;
  void SetValue(const double new_value);
  [[nodiscard]] SpinBoxLineEdit *GetLineEdit() const { return line_edit_; }
  [[nodiscard]] SpinBoxPushButton *GetPushButton() const {
    return push_button_;
  }

 public slots:
  void ToggleEditing();

 signals:
  void EventValueChanged(double new_value);

 private:
  SpinBoxLineEdit *line_edit_;
  SpinBoxPushButton *push_button_;
  QWidget *current_widget_{};
  double current_value_;
  double multiplier_;
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_SPIN_BOX_SPIN_BOX_H_