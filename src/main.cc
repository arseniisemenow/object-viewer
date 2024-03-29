#include <QApplication>

#include "View/ui/View/View.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "en_US.UTF-8", 1);

  QApplication app(argc, argv);
  s21::Model model{};
  s21::Controller controller{&model};
  s21::View view{nullptr, &controller};
  view.show();
  return QApplication::exec();
}
