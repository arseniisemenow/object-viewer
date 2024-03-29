#include "FileInformationWindow.h"

#include "ui_FileInformationWindow.h"

FileInformationWindow::FileInformationWindow()
    : ui_(new Ui::FileInformationWindow) {
  ui_->setupUi(this);
  setWindowModality(Qt::ApplicationModal);
  UpdateValues();

  connect(ui_->pushButton_close, &QPushButton::clicked, this,
          [=]() { this->close(); });
}

FileInformationWindow::~FileInformationWindow() { delete ui_; }
