#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STATUS_BAR_STATUS_BAR_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STATUS_BAR_STATUS_BAR_H_

#include <QLabel>
#include <QObject>
#include <QProgressBar>
#include <QStatusBar>

#define DEFAULT_PROGRESS_BAR_HEIGHT (15)

namespace s21 {

class StatusBar final : public QStatusBar {
  Q_OBJECT
 public:
  StatusBar() {
    vertex_label_ = new QLabel("");
    polygons_label_ = new QLabel("");

    progress_bar_label_ = new QLabel("");
    progress_bar_ = new QProgressBar();
    setFixedHeight(DEFAULT_PROGRESS_BAR_HEIGHT);

    setStyleSheet(
        "QStatusBar{"
        "border: 0px;"
        "background-color: rgb(55, 55, 55);"
        "}");
  }

  void SetVertexCount(const int count) const {
    vertex_label_->setText("Vertices: " + QString::number(count));
  }
  void SetPolygonsCount(const int count) const {
    polygons_label_->setText("Polygons: " + QString::number(count));
  }
  void SetProgress(const int value) const { progress_bar_->setValue(value); }
  void SetProgressBarTitle(const QString &title) const {
    progress_bar_label_->setText(title);
  }

 private:
  QLabel *vertex_label_;
  QLabel *polygons_label_;
  QLabel *progress_bar_label_;
  QProgressBar *progress_bar_;
};

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STATUS_BAR_STATUS_BAR_H_