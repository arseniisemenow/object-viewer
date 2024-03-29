#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_FILE_HANDLER_FILE_HANDLER_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_FILE_HANDLER_FILE_HANDLER_H_

#include <QObject>
#include <string>

#include "View/ui/EventHandler/EventHandler.h"

namespace s21 {
class FileHandler final : public QObject {
  Q_OBJECT

 public:
  static FileHandler &Get(Controller *controller) {
    static FileHandler instance{controller};
    return instance;
  }

  ~FileHandler() override = default;

  void Open(const QString &file_name) {
    auto result{controller_->ParseObjFile(file_name.toStdString())};
    if (result.error == ModelLoadingError::kNoModelLoadingError) {
      emit FileLoaded(result.mesh_data, file_name);
    }
  }

  void Close() { emit FileClosed(); }

 signals:
  void FileLoaded(const MeshData &data, const QString &file_name);
  void FileClosed();

 private:
  explicit FileHandler(Controller *controller) : controller_(controller) {
    connect(&EventHandler::Get(), &EventHandler::EventOpenFile, this,
            &FileHandler::Open);
    connect(&EventHandler::Get(), &EventHandler::EventRecentFileActionClicked,
            this, &FileHandler::Open);
    connect(&EventHandler::Get(), &EventHandler::EventCloseFile, this,
            &FileHandler::Close);
  }

  Controller *controller_;
};
}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_FILE_HANDLER_FILE_HANDLER_H_