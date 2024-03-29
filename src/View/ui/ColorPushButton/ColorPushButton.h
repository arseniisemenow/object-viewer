#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_COLOR_PUSH_BUTTON_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_COLOR_PUSH_BUTTON_H_

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

class ColorPushButton final : public QPushButton {
  Q_OBJECT

 public:
  explicit ColorPushButton(QWidget* parent = nullptr);
  void UpdateButtonTitle(const QString& color_string);
  void UpdateData(const QColor& color);
  void ChangeColor();
  [[nodiscard]] QColor GetColor() const;

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  QString hex_color_code_;
  QColor color_;
};
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_COLOR_PUSH_BUTTON_H_
