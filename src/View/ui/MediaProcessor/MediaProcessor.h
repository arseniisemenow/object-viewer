#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MEDIA_PROCESSOR_MEDIA_PROCESSOR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MEDIA_PROCESSOR_MEDIA_PROCESSOR_H_

#include <QBuffer>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QImageWriter>
#include <QMessageBox>
#include <QMovie>
#include <QObject>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QProcess>
#include <QScreen>
#include <QThread>
#include <iostream>

#include "View/opengl/OpenGLWidget/OpenGLWidget.h"

namespace s21 {

class MediaProcessor final : public QObject {
  Q_OBJECT

 public:
  explicit MediaProcessor(QObject *parent = nullptr,
                          OpenGLWidget *open_gl_widget = nullptr);

 public slots:
  void CaptureAndSaveImage();
  void CaptureAndSaveAnimation();

 private:
  static QString GetSaveFilePath(const QString &file_type);
  OpenGLWidget *open_gl_widget_;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MEDIA_PROCESSOR_MEDIA_PROCESSOR_H_