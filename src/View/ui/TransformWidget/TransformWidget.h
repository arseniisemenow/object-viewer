#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TRANSFORM_WIDGET_TRANSFORM_WIDGET_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TRANSFORM_WIDGET_TRANSFORM_WIDGET_H_

#include <QGridLayout>
#include <QWidget>
#include <array>
#include <iostream>

#include "View/ui/SpinBox/SpinBox.h"

namespace s21 {

class TransformWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit TransformWidget(QWidget *parent = nullptr);
  void HandleSpinBoxValueChanged(int);
  void ClearSpinBoxes();

 signals:
  void AffineTransformationChanged(const std::array<QVector3D, 3> &matrix);

 private:
  void SetupUi();

  SpinBox *CreateCustomSpinBox(int, double);

  void AddSpinBoxToLayout(QGridLayout *layout, int row, int col);
  SpinBox *spin_box_matrix_[3][3]{};
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TRANSFORM_WIDGET_TRANSFORM_WIDGET_H_