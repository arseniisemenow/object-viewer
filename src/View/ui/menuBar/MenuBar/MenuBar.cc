#include "MenuBar.h"

namespace s21 {
MenuBar::MenuBar([[maybe_unused]] QWidget *parent, Controller *controller)
    : menu_file_{new MenuFile{"File", controller}},
      menu_media_{new MenuMedia{"Media"}},
      menu_help_{new QMenu{"Help"}} {
  UpdateStyle();

  application_menu_ = addMenu("s21_viewer");

  const auto action_about{new QAction{"About", this}};
  const auto action_preferences{new QAction{"Preferences", this}};
  const auto action_quit{new QAction{"Quit", this}};

  application_menu_->addAction(action_about);
  application_menu_->addAction(action_preferences);
  application_menu_->addAction(action_quit);

  menu_views_ = new MenuViews("Views");

  connect(action_preferences, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::OpenPreferencesWindow);
  connect(action_quit, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::CloseMainWindow);
  connect(action_about, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::OpenAboutWindow);

  addMenu(menu_file_);
  addMenu(menu_views_);
  addMenu(menu_media_);
}

void MenuBar::UpdateStyle() {
  menu_media_->setStyleSheet(GetStylesFromFile(PATH_MENU_BAR_STYLES_FILE));

  this->setStyleSheet(GetStylesFromFile(PATH_MENU_BAR_STYLES_FILE));
}
}  // namespace s21
