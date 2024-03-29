#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_ABOUT_WINDOW_ABOUT_WINDOW_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_ABOUT_WINDOW_ABOUT_WINDOW_H_

#include <QDialog>
#include <QPixmap>

#include "ui_AboutWindow.h"

#define PATH_COMPANY_LOGO ":/company_logo.png"

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog {
  Q_OBJECT

 public:
  explicit AboutWindow();
  ~AboutWindow() override;

  void LockMainWindowInteraction();

  void CloseWindow();

 private:
  Ui::AboutWindow *ui_;
};

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_ABOUT_WINDOW_ABOUT_WINDOW_H_