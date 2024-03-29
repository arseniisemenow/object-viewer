#include "MenuFile.h"

namespace s21 {

MenuFile::MenuFile(const QString &title, Controller *controller)
    : controller_(controller) {
  setTitle(title);

  open_file_action_ = new QAction(ACTION_TITLE_OPEN_FILE);
  close_file_action_ = new QAction(ACTION_TITLE_CLOSE_FILE);
  file_information_action_ = new QAction(ACTION_TITLE_FILE_INFORMATION);
  recent_files_menu_ = new QMenu(ACTION_TITLE_RECENT_FILES);

  connect(open_file_action_, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::OpenFileDialog);
  connect(&EventHandler::Get(), &EventHandler::EventOpenFileDialog, this,
          &MenuFile::OpenFileDialog);

  connect(close_file_action_, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::CloseFile);
  connect(&EventHandler::Get(), &EventHandler::EventCloseFile,
          &EventHandler::Get(), &EventHandler::ClearSpinBoxes);

  connect(this, &MenuFile::RecentFilesChanged, &EventHandler::Get(),
          &EventHandler::UpdateFileMenu);
  connect(&EventHandler::Get(), &EventHandler::EventUpdateFileMenu, this,
          &MenuFile::UpdateMenu);
  connect(&EventHandler::Get(), &EventHandler::EventResetSettings, this,
          &MenuFile::UpdateMenu);
  connect(this, &MenuFile::EventRecentFileActionClicked, &EventHandler::Get(),
          &EventHandler::RecentFileActionClicked);

  connect(file_information_action_, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::OpenFileInformation);
  connect(&EventHandler::Get(), &EventHandler::EventOpenFileInformation, this,
          &MenuFile::OpenFileInformation);

  connect(&FileHandler::Get(controller), &FileHandler::FileLoaded, this,
          &MenuFile::UpdateFileInformation);
  connect(&FileHandler::Get(controller), &FileHandler::FileClosed, this,
          &MenuFile::ClearFileInformation);

  connect(this, &MenuFile::EventLoadAnotherModel, &EventHandler::Get(),
          &EventHandler::LoadAnotherModel);

  UpdateMenu();
}

void MenuFile::UpdateMenu() { HandleRecentFilesChanged(); }

int MenuFile::FillMenuWithRecentFiles() {
  for (const auto &recent_file : recent_files_) {
    const auto recent_file_action = new QAction(recent_file.path);
    connect(recent_file_action, &QAction::triggered, this,
            &MenuFile::OpenRecentFile);
    recent_files_menu_->addAction(recent_file_action);
  }

  const auto clear_recent_files_action = new QAction(ACTION_TITLE_CLEAR_MENU);
  connect(clear_recent_files_action, &QAction::triggered, this,
          &MenuFile::ClearRecentFiles);
  recent_files_menu_->addSeparator();
  recent_files_menu_->addAction(clear_recent_files_action);

  return recent_files_.count() > 0;
}

void MenuFile::AddRecentFile(const RecentFile &recent_file) {
  for (int i = 0; i < recent_files_.size(); i++) {
    if (recent_files_[i].path == recent_file.path) {
      recent_files_.removeAt(i);
    }
  }

  recent_files_.prepend(recent_file);

  while (recent_files_.size() > S21_MAX_RECENT_FILES) {
    recent_files_.removeLast();
  }
  SaveRecentFiles();
  emit RecentFilesChanged();
}

void MenuFile::ClearRecentFiles() {
  recent_files_.clear();
  SaveRecentFiles();
  emit RecentFilesChanged();
}

void MenuFile::OpenFileDialog() {
  auto *file_dialog = new FileDialog(1000, 600);
  file_dialog->setNameFilters({"obj"});
  file_dialog->SetRootPath(QDir::homePath());

  if (file_dialog->exec() == QDialog::Accepted) {
    const QString path = file_dialog->GetSelectedPath();
    const QString name = file_dialog->getSelectedFileName();

    const RecentFile recent_file{name, path};
    this->AddRecentFile(recent_file);
    LoadAnotherModel();
  }
}

void MenuFile::OpenFileInformation() const {
  const auto file_information_window = new FileInformationWindow();
  file_information_window->setFilePath(open_file_name_);
  file_information_window->setVertexCount(number_of_vertices_);
  file_information_window->setEdgeCount(number_of_edges_);
  file_information_window->show();
}

void MenuFile::UpdateFileInformation(const MeshData &data,
                                     const QString &file_name) {
  number_of_vertices_ = data.number_of_vertices;
  number_of_edges_ = data.number_of_edges;
  open_file_name_ = file_name;
}

void MenuFile::ClearFileInformation() {
  number_of_vertices_ = 0;
  number_of_edges_ = 0;
  open_file_name_.clear();
}

void MenuFile::OpenRecentFile() {
  const auto action = qobject_cast<QAction *>(sender());
  if (action) {
    const QString file_path = GetFilePathFromAction(action);
    const QFileInfo file_info(file_path);
    if (!file_path.isEmpty()) {
      const QString &path = file_path;
      const QString name = file_info.fileName();

      const RecentFile recent_file{name, path};

      AddRecentFile(recent_file);
      RecentFileActionClicked(path);
      LoadAnotherModel();
    }
  }
}

QString MenuFile::GetFilePathFromAction(const QAction *action) {
  const QString file_name = action->text();
  for (const auto &recent_file : recent_files_) {
    if (recent_file.path == file_name) {
      return recent_file.path;
    }
  }
  return "";
}

void MenuFile::HandleRecentFilesChanged() {
  clear();
  recent_files_menu_->clear();

  LoadRecentFiles();

  addAction(open_file_action_);

  int is_recent_files = FillMenuWithRecentFiles();

  if (is_recent_files) {
    addMenu(recent_files_menu_);
  }
  addAction(file_information_action_);
  addAction(close_file_action_);
}

void MenuFile::SaveRecentFiles() {
  QVariantList recent_files_list{};

  for (const auto &file : recent_files_) {
    QVariantMap file_data{};
    file_data["name"] = file.name;
    file_data["path"] = file.path;
    recent_files_list.append(file_data);
  }

  Preferences::Get().recent_files_settings->setValue(STRINGIFY(recentFiles),
                                                     recent_files_list);
}

void MenuFile::LoadRecentFiles() {
  QVariantList recent_files_list =
      Preferences::Get()
          .recent_files_settings->value(STRINGIFY(recentFiles))
          .toList();
  recent_files_.clear();

  for (const QVariant &file_data : recent_files_list) {
    if (file_data.type() == QVariant::Map) {
      QVariantMap file_map = file_data.toMap();
      RecentFile file{};
      file.name = file_map["name"].toString();
      file.path = file_map["path"].toString();
      recent_files_.append(file);
    }
  }
}

void MenuFile::RecentFileActionClicked(const QString &file_path) {
  emit EventRecentFileActionClicked(file_path);
}

}  // namespace s21
