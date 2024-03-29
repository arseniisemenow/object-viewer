#include "EventHandler.h"

namespace s21 {

void EventHandler::OpenPreferencesWindow() {
  emit EventOpenPreferencesWindow();
}

void EventHandler::ClosePreferencesWindow() {
  emit EventClosePreferencesWindow();
}

void EventHandler::OpenAboutWindow() { emit EventOpenAboutWindow(); }

void EventHandler::CloseAboutWindow() { emit EventCloseAboutWindow(); }

void EventHandler::CloseMainWindow() { emit EventCloseMainWindow(); }

void EventHandler::RecentFilesChanged() { emit EventRecentFilesChanged(); }

void EventHandler::UpdateFileMenu() { emit EventUpdateFileMenu(); }

void EventHandler::OpenFileDialog() { emit EventOpenFileDialog(); }

void EventHandler::CloseFile() { emit EventCloseFile(); }

void EventHandler::ApplySettings() { emit EventApplySettings(); }

void EventHandler::CancelSettings() { emit EventCancelSettings(); }

void EventHandler::OkSettings() { emit EventOkSettings(); }

void EventHandler::ResetSettings() { emit EventResetSettings(); }

void EventHandler::FileDialogCloseWindow() {
  emit EventFileDialogCloseWindow();
}

void EventHandler::FileDialogUpdateSelectedPath(const QModelIndex &index) {
  emit EventFileDialogUpdateSelectedPath(index);
}

}  // namespace s21