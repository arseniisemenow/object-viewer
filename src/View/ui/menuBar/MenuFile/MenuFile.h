#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_FILE_MENU_FILE_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_FILE_MENU_FILE_H_

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QObject>
#include <QString>
#include <QVector>

#include "View/ui/EventHandler/EventHandler.h"
#include "View/ui/FileHandler/FileHandler.h"
#include "View/ui/Preferences/Preferences.h"
#include "View/ui/RecentFile/RecentFile.h"
#include "View/ui/modalWidgets/FileDialog/FileDialog.h"
#include "View/ui/modalWidgets/FileInformationWindow/FileInformationWindow.h"
#include "View/ui/styles/styles.h"

#define ACTION_TITLE_OPEN_FILE "Open File"
#define ACTION_TITLE_CLOSE_FILE "Close File"
#define ACTION_TITLE_FILE_INFORMATION "File Information"
#define ACTION_TITLE_RECENT_FILES "Recent Files"
#define ACTION_TITLE_CLEAR_MENU "Clear menu"

#define S21_MAX_RECENT_FILES (10)
namespace s21 {

class MenuFile final : public QMenu {
  Q_OBJECT

 public:
  explicit MenuFile(const QString &title = "Default Title",
                    Controller *controller = nullptr);

  void AddRecentFile(const RecentFile &recent_file);
  void UpdateRecentFiles();
  void ClearRecentFiles();
  void OpenFileDialog();
  QString GetFilePathFromAction(const QAction *action);
  void UpdateMenu();

  void SaveRecentFiles();
  void LoadRecentFiles();

 public slots:
  void HandleRecentFilesChanged();
  void RecentFileActionClicked(const QString &file_path);
  void OpenRecentFile();
  void OpenFileInformation() const;

  void UpdateFileInformation(const MeshData &data, const QString &file_name);
  void ClearFileInformation();

  void LoadAnotherModel() { emit EventLoadAnotherModel(); }

 signals:
  void EventRecentFileActionClicked(const QString &);
  void RecentFilesChanged();
  void EventLoadAnotherModel();

 private:
  Controller *controller_;
  QVector<RecentFile> recent_files_;

  QAction *open_file_action_;
  QAction *close_file_action_;
  QAction *file_information_action_;
  QMenu *recent_files_menu_;

  int number_of_vertices_{};
  int number_of_edges_{};
  QString open_file_name_{};

  int FillMenuWithRecentFiles();
};

}  // namespace s21
#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_MENU_BAR_MENU_FILE_MENU_FILE_H_