#include "SpinBox.h"

namespace s21 {
SpinBox::SpinBox(const double initial_value, const double multiplier,
                 QWidget *parent)
    : QWidget(parent), current_value_(initial_value), multiplier_(multiplier) {
  line_edit_ = new SpinBoxLineEdit(current_value_, multiplier_, this);
  push_button_ = new SpinBoxPushButton(current_value_, multiplier_, this);
  constexpr int height{30};
  constexpr int width{100};
  push_button_->setMinimumWidth(width);
  push_button_->setMaximumWidth(width);

  line_edit_->setMinimumWidth(width);
  line_edit_->setMaximumWidth(width);

  line_edit_->setMinimumHeight(height);
  line_edit_->setMaximumHeight(height);

  push_button_->setMinimumHeight(height);
  push_button_->setMaximumHeight(height);

  connect(push_button_, &SpinBoxPushButton::EventValueChanged, this,
          &SpinBox::SetValue);
  connect(line_edit_, &SpinBoxLineEdit::EventValueChanged, this,
          &SpinBox::SetValue);

  const auto layout = new QVBoxLayout(this);
  layout->addWidget(line_edit_);
  layout->addWidget(push_button_);

  line_edit_->hide();

  connect(push_button_, &SpinBoxPushButton::clicked, this,
          &SpinBox::ToggleEditing);
  connect(line_edit_, &SpinBoxLineEdit::FocusOut, this,
          &SpinBox::ToggleEditing);
}

double SpinBox::GetValue() const { return current_value_; }

void SpinBox::ToggleEditing() {
  if (current_widget_ == push_button_) {
    push_button_->hide();
    line_edit_->SetValue(current_value_);
    line_edit_->show();
    line_edit_->selectAll();
    line_edit_->setFocus();
    line_edit_->setFixedSize(push_button_->size());
  } else {
    line_edit_->hide();
    current_value_ = line_edit_->GetValue();
    push_button_->SetValue(current_value_);
    push_button_->show();
  }
  if (current_widget_ == push_button_) {
    current_widget_ = line_edit_;
  } else {
    current_widget_ = push_button_;
  }
}

void SpinBox::SetValue(const double new_value) {
  current_value_ = new_value;
  emit EventValueChanged(new_value);
}
}  // namespace s21
