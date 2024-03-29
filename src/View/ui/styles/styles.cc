#include "styles.h"

#include <QDebug>

namespace s21 {
QString ReadStylesFromFile(const QString &file_name) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "Failed to open styles file: " << file_name.toStdString()
              << std::endl;
    return "";
  }

  QTextStream input_stream_global(&file);
  QString styles_string = input_stream_global.readAll();

  file.close();
  return styles_string;
}

void ApplyGlobalVariables(QString &string) {
  QVector<QString> variable_names = {
      "@purple", "@purpleAlpha", "@gray0",  "@gray1", "@gray2",
      "@gray3",  "@gray4",       "@gray5",  "@gray6", "@gray7",
      "@gray8",  "@gray9",       "@gray10", "@gray11"};
  QVector<QString> replacements = {
      styles::kColorPurple, styles::kColorPurpleAlpha, styles::kColorGray0,
      styles::kColorGray1,  styles::kColorGray2,       styles::kColorGray3,
      styles::kColorGray4,  styles::kColorGray5,       styles::kColorGray6,
      styles::kColorGray7,  styles::kColorGray8,       styles::kColorGray9,
      styles::kColorGray10, styles::kColorGray11};

  for (int i = 0; i < variable_names.size(); ++i) {
    for (int j = i + 1; j < variable_names.size(); ++j) {
      if (variable_names[i].length() < variable_names[j].length()) {
        qSwap(variable_names[i], variable_names[j]);
        qSwap(replacements[i], replacements[j]);
      }
    }
  }

  // Perform replacements in the original string
  for (int i = 0; i < variable_names.size(); ++i) {
    string.replace(variable_names[i], replacements[i]);
  }
}

QString GetStylesFromFile(const QString &file_name) {
  QString styles_string = ReadStylesFromFile(file_name);

  ApplyGlobalVariables(styles_string);

  return styles_string;
}
}  // namespace s21
