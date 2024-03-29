#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_EDITOR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_EDITOR_H_

#include <QWidget>

#include "QtWidgets/qscrollarea.h"

namespace s21 {
class ModelEditor : public QWidget {
  Q_OBJECT

 public:
  explicit ModelEditor(QWidget *parent = nullptr){};

  ~ModelEditor() override = default;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_USER_INTERACTION_WIDGETS_MODEL_EDITOR_H_