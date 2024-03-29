#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STYLES_STYLES_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STYLES_STYLES_H_

#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

#include "global_styles.h"

// #define PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE
// "frontend/ui/styles/DockWidgetSettingsStyles.qss"
#define PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE ":/DockWidgetSettingsStyles.qss"
#define PATH_FILE_DIALOG_STYLES_FILE ":/FileDialogStyles.qss"
#define PATH_MENU_BAR_STYLES_FILE ":/MenuBarStyles.qss"
#define PATH_MAIN_WINDOW_STYLES_FILE ":/MainWindowStyles.qss"
#define PATH_TITLE_BAR_STYLES_FILE ":/TitleBarStyles.qss"
#define PATH_PREFERENCES_WINDOW_STYLES_FILE ":/PreferencesWindowStyles.qss"

namespace s21 {
QString GetStylesFromFile(const QString &fileName);
}

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STYLES_STYLES_H_