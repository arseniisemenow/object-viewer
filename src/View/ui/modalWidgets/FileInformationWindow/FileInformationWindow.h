#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_FILE_INFORMATION_WINDOW_FILE_INFORMATION_WINDOW_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_FILE_INFORMATION_WINDOW_FILE_INFORMATION_WINDOW_H_

#include <QWidget>

#include "QtWidgets/qdialog.h"
#include "ui_FileInformationWindow.h"

namespace Ui {
class FileInformationWindow;
}

class FileInformationWindow : public QDialog {
  Q_OBJECT

 public:
  explicit FileInformationWindow();
  ~FileInformationWindow() override;

  void setVertexCount(const int count) {
    vertex_count_ = count;
    UpdateValues();
  }
  void setEdgeCount(const int count) {
    edge_count_ = count;
    UpdateValues();
  }
  void setFilePath(const QString &file_path) {
    file_path_ = file_path;
    UpdateValues();
  }
  void UpdateVertexCount() const {
    ui_->label_vertexCountValue->setText(QString::number(vertex_count_));
  }
  void UpdateEdgeCount() const {
    ui_->label_edgeCountValue->setText(QString::number(edge_count_));
  }
  void UpdateFilePath() const { ui_->label_filePathValue->setText(file_path_); }

  void UpdateValues() const {
    UpdateVertexCount();
    UpdateEdgeCount();
    UpdateFilePath();
  }

 private:
  Ui::FileInformationWindow *ui_;
  QString file_path_{""};
  int vertex_count_{0};
  int edge_count_{0};
};

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MODAL_WIDGETS_FILE_INFORMATION_WINDOW_FILE_INFORMATION_WINDOW_H_