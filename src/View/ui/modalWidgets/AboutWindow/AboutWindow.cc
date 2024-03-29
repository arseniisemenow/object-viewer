#include "AboutWindow.h"

AboutWindow::AboutWindow() : ui_(new Ui::AboutWindow) {
  ui_->setupUi(this);

  LockMainWindowInteraction();
  const QPixmap pixmap_image(PATH_COMPANY_LOGO);
  ui_->label_image->setPixmap(
      pixmap_image.scaled(150, 150, Qt::KeepAspectRatio));

  connect(ui_->pushButton_close, &QPushButton::clicked, this,
          &AboutWindow::CloseWindow);
}

AboutWindow::~AboutWindow() { delete ui_; }

void AboutWindow::LockMainWindowInteraction() { setModal(true); }

void AboutWindow::CloseWindow() { this->close(); }
