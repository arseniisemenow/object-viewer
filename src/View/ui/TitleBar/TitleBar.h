#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TITLE_BAR_TITLE_BAR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TITLE_BAR_TITLE_BAR_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QWidget>

#include "View/ui/styles/styles.h"

namespace s21 {

class TitleBar final : public QWidget {
  Q_OBJECT
 public:
  explicit TitleBar(const QString &title = "Default title name",
                    QWidget *parent = nullptr);
  ~TitleBar() override;

 private:
  void UpdateStyles() const;

  QHBoxLayout *layout_;
  QLabel *title_label_;
  QWidget *parent_{};
  QString title_;
};

}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_TITLE_BAR_TITLE_BAR_H_