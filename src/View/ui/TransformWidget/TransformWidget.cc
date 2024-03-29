#include "TransformWidget.h"

#include <QVector3D>

#include "QtWidgets/qlabel.h"

namespace s21 {
TransformWidget::TransformWidget(QWidget* parent)
    : QWidget(parent)

{
  SetupUi();
  connect(this, &TransformWidget::AffineTransformationChanged,
          &EventHandler::Get(),
          &EventHandler::EventAffineTransformationChanged);

  connect(&EventHandler::Get(), &EventHandler::EventLoadAnotherModel,
          &EventHandler::Get(), &EventHandler::ClearSpinBoxes);
}

void TransformWidget::SetupUi() {
  QGridLayout* gridLayout = new QGridLayout(this);

  QStringList rowLabels = {"Position", "Rotation", "Scale"};
  QStringList colLabels = {"X", "Y", "Z"};

  for (int col = 0; col < 3; ++col) {
    QLabel* colLabel = new QLabel(colLabels[col]);
    colLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(colLabel, 0, col + 1);
  }

  for (int row = 0; row < 3; ++row) {
    QLabel* rowLabel = new QLabel(rowLabels[row]);
    gridLayout->addWidget(rowLabel, row + 1, 0);

    for (int col = 0; col < 3; ++col) {
      AddSpinBoxToLayout(gridLayout, row, col);
    }
  }
  setMaximumHeight(300);

  QPushButton* clearButton = new QPushButton("Clear");
  connect(clearButton, &QPushButton::clicked, &EventHandler::Get(),
          &EventHandler::ClearSpinBoxes);
  connect(&EventHandler::Get(), &EventHandler::EventClearSpinBoxes, this,
          &TransformWidget::ClearSpinBoxes);

  gridLayout->addWidget(clearButton, 4, 0, 1, 4, Qt::AlignCenter);
}

SpinBox* TransformWidget::CreateCustomSpinBox(int defaultValue,
                                              double multiplier) {
  SpinBox* spinBox = new SpinBox(defaultValue, multiplier, this);
  return spinBox;
}

void TransformWidget::AddSpinBoxToLayout(QGridLayout* layout, int row,
                                         int col) {
  int defaultValue = 0;
  double multiplier = 1;
  if (row > 1) {
    defaultValue = 1;
    multiplier = 0.05;
  }
  spin_box_matrix_[row][col] = CreateCustomSpinBox(defaultValue, multiplier);
  connect(spin_box_matrix_[row][col], &SpinBox::EventValueChanged, this,
          &TransformWidget::HandleSpinBoxValueChanged);

  layout->addWidget(spin_box_matrix_[row][col], row + 1, col + 1);
}

void TransformWidget::HandleSpinBoxValueChanged(int someValue) {
  std::array<QVector3D, 3> matrix{};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix[i][j] = spin_box_matrix_[i][j]->GetValue();
    }
  }
  emit AffineTransformationChanged(matrix);
}

void TransformWidget::ClearSpinBoxes() {
  for (int row = 0; row < 2; ++row) {
    for (int col = 0; col < 3; ++col) {
      spin_box_matrix_[row][col]->SetValue(0);
      spin_box_matrix_[row][col]->GetLineEdit()->SetValue(0);
      spin_box_matrix_[row][col]->GetPushButton()->SetValue(0);
    }
  }

  for (int row = 2; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      spin_box_matrix_[row][col]->SetValue(1);
      spin_box_matrix_[row][col]->GetLineEdit()->SetValue(1);
      spin_box_matrix_[row][col]->GetPushButton()->SetValue(1);
    }
  }
}
}  // namespace s21
