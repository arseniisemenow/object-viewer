#include "MediaProcessor.h"

namespace s21 {

MediaProcessor::MediaProcessor(QObject *parent, OpenGLWidget *open_gl_widget)
    : QObject(parent), open_gl_widget_(open_gl_widget) {}

void MediaProcessor::CaptureAndSaveImage() {
  const QImage screenshot = open_gl_widget_->grabFramebuffer();

  const QString file_path = GetSaveFilePath("png");

  screenshot.save(file_path);

  std::cerr << "Image saved at: " << file_path.toStdString() << std::endl;
}

void MediaProcessor::CaptureAndSaveAnimation() {
  std::thread cast_gif(&OpenGLWidget::Screencast, open_gl_widget_);
  cast_gif.detach();
}

QString MediaProcessor::GetSaveFilePath(const QString &file_type) {
  const QString executable_path = QCoreApplication::applicationDirPath();

  const QString default_file_name = "output";

  QStringList supported_formats;
  supported_formats << "JPEG Image (*.jpg *.jpeg)"
                    << "Bitmap Image (*.bmp)";
  QString selected_filter;

  QString file_path = QFileDialog::getSaveFileName(
      nullptr, "Save File", executable_path + "/" + default_file_name,
      supported_formats.join(";;"), &selected_filter);

  QString selected_format;
  if (selected_filter.contains("JPEG")) {
    selected_format = "jpeg";
  } else if (selected_filter.contains("Bitmap")) {
    selected_format = "bmp";
  } else {
    selected_format = file_type;
  }

  const QFileInfo file_info(file_path);
  file_path = file_info.path() + QDir::separator() +
              file_info.completeBaseName() + "." + selected_format;

  return file_path;
}

}  // namespace s21