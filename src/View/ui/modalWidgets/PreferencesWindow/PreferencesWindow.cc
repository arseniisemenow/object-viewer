#include "PreferencesWindow.h"

namespace s21 {
PreferencesWindow::PreferencesWindow(QWidget *parent)
    : QDialog(parent), ui_(new Ui::PreferencesWindow) {
  ui_->setupUi(this);

  LockMainWindowInteraction();

  SetButtonsConnections();

  LoadSettings();
  UpdateStyles();
}

PreferencesWindow::~PreferencesWindow() { delete ui_; }

void PreferencesWindow::UpdateStyles() {
  this->setStyleSheet(GetStylesFromFile(PATH_PREFERENCES_WINDOW_STYLES_FILE));
}

void PreferencesWindow::SetButtonsConnections() {
  connect(ui_->pushButton_apply, &QPushButton::clicked, &EventHandler::Get(),
          &EventHandler::ApplySettings);
  connect(&EventHandler::Get(), &EventHandler::EventApplySettings, this,
          &PreferencesWindow::HandleApplyButtonClick);

  connect(ui_->pushButton_cancel, &QPushButton::clicked, &EventHandler::Get(),
          &EventHandler::CancelSettings);
  connect(&EventHandler::Get(), &EventHandler::EventCancelSettings, this,
          &PreferencesWindow::HandleCancelButtonClick);

  connect(ui_->pushButton_ok, &QPushButton::clicked, &EventHandler::Get(),
          &EventHandler::OkSettings);
  connect(&EventHandler::Get(), &EventHandler::EventOkSettings, this,
          &PreferencesWindow::HandleOkButtonClick);

  connect(ui_->pushButton_resetSettings, &QPushButton::clicked,
          &EventHandler::Get(), &EventHandler::ResetSettings);
  connect(&EventHandler::Get(), &EventHandler::EventResetSettings, this,
          &PreferencesWindow::HandleResetSettingsButtonClick);

  connect(this, &PreferencesWindow::EventOpenPreferencesWindow,
          &EventHandler::Get(), &EventHandler::EventOpenPreferencesWindow);
}

void PreferencesWindow::LockMainWindowInteraction() { setModal(true); }

void PreferencesWindow::LoadVertexDisplayMethodSettings() {
  if (Preferences::Get().GetVertexDisplayMethod() ==
      Vertex::DisplayMethod::kNone) {
    ui_->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::kNone);
  } else if (Preferences::Get().GetVertexDisplayMethod() ==
             Vertex::DisplayMethod::kCircle) {
    ui_->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::kCircle);
  } else if (Preferences::Get().GetVertexDisplayMethod() ==
             Vertex::DisplayMethod::kSquare) {
    ui_->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::kSquare);
  }
}

void PreferencesWindow::LoadEdgeTypeSettings() {
  if (Preferences::Get().GetEdgeType() == Edge::Type::kSolid) {
    ui_->comboBox_edgeType->setCurrentIndex(EdgeTypeComboBoxIndex::kSolid);
  } else if (Preferences::Get().GetEdgeType() == Edge::Type::kDashed) {
    ui_->comboBox_edgeType->setCurrentIndex(EdgeTypeComboBoxIndex::kDashed);
  }
}

void PreferencesWindow::LoadVertexSize() {
  int vertexSize = Preferences::Get().GetVertexSize();
  ui_->spinBox_vertexSize->setValue(vertexSize);
}

void PreferencesWindow::LoadEdgeSize() {
  int edgeSize = Preferences::Get().GetEdgeSize();
  ui_->spinBox_edgeSize->setValue(edgeSize);
}

void PreferencesWindow::LoadCameraSpeed() {
  int cameraSpeed = Preferences::Get().GetCameraSpeed();
  ui_->spinBox_cameraSpeed->setValue(cameraSpeed);
}

void PreferencesWindow::LoadNearPlane() {
  int nearPlane = Preferences::Get().GetNearPlane();
  ui_->spinBox_nearPlane->setValue(nearPlane);
}

void PreferencesWindow::LoadFarPlane() {
  int farPlane = Preferences::Get().GetFarPlane();
  ui_->spinBox_farPlane->setValue(farPlane);
}

void PreferencesWindow::SaveVertexDisplayMethod() {
  if (ui_->comboBox_vertexDisplayMethod->currentIndex() ==
      VertexDisplayMethodComboBoxIndex::kNone) {
    Preferences::Get().SetVertexDisplayMethod(Vertex::DisplayMethod::kNone);
  } else if (ui_->comboBox_vertexDisplayMethod->currentIndex() ==
             VertexDisplayMethodComboBoxIndex::kCircle) {
    Preferences::Get().SetVertexDisplayMethod(Vertex::DisplayMethod::kCircle);
  } else if (ui_->comboBox_vertexDisplayMethod->currentIndex() ==
             VertexDisplayMethodComboBoxIndex::kSquare) {
    Preferences::Get().SetVertexDisplayMethod(Vertex::DisplayMethod::kSquare);
  }
}

void PreferencesWindow::SaveEdgeType() {
  if (ui_->comboBox_edgeType->currentIndex() == EdgeTypeComboBoxIndex::kSolid) {
    Preferences::Get().SetEdgeType(Edge::Type::kSolid);
  } else if (ui_->comboBox_edgeType->currentIndex() ==
             EdgeTypeComboBoxIndex::kDashed) {
    Preferences::Get().SetEdgeType(Edge::Type::kDashed);
  }
}

void PreferencesWindow::SaveBackgroundColor() {
  QColor color = ui_->colorPushButton_backgroundColor->GetColor();
  Preferences::Get().SetBackgroundColor(color);
}

void PreferencesWindow::LoadBackgroundColor() {
  QColor color = Preferences::Get().GetBackgroundColor();
  ui_->colorPushButton_backgroundColor->UpdateData(color);
}

void PreferencesWindow::SaveVertexColor() {
  QColor color = ui_->colorPushButton_vertexColor->GetColor();
  Preferences::Get().SetVertexColor(color);
}

void PreferencesWindow::SaveCameraSpeed() {
  int cameraSpeed = ui_->spinBox_cameraSpeed->value();
  Preferences::Get().SetCameraSpeed(cameraSpeed);
}

void PreferencesWindow::SaveNearPlane() {
  int nearPlane = ui_->spinBox_nearPlane->value();
  Preferences::Get().SetNearPlane(nearPlane);
}

void PreferencesWindow::SaveFarPlane() {
  int farPlane = ui_->spinBox_farPlane->value();
  Preferences::Get().SetFarPlane(farPlane);
}

void PreferencesWindow::LoadVertexColor() {
  QColor color = Preferences::Get().GetVertexColor();
  ui_->colorPushButton_vertexColor->UpdateData(color);
}

void PreferencesWindow::SaveEdgeColor() {
  QColor color = ui_->colorPushButton_edgeColor->GetColor();
  Preferences::Get().SetEdgeColor(color);
}

void PreferencesWindow::LoadEdgeColor() {
  QColor color = Preferences::Get().GetEdgeColor();
  ui_->colorPushButton_edgeColor->UpdateData(color);
}

void PreferencesWindow::SaveVertexSize() {
  Preferences::Get().SetVertexSize(ui_->spinBox_vertexSize->value());
}

void PreferencesWindow::SaveEdgeSize() {
  Preferences::Get().SetEdgeSize(ui_->spinBox_edgeSize->value());
}

void PreferencesWindow::LoadSettings() {
  LoadBackgroundColor();
  LoadCameraSpeed();
  LoadNearPlane();
  LoadFarPlane();

  LoadVertexSize();
  LoadVertexDisplayMethodSettings();
  LoadVertexColor();

  LoadEdgeSize();
  LoadEdgeTypeSettings();
  LoadEdgeColor();
}

void PreferencesWindow::SaveSettings() {
  SaveBackgroundColor();
  SaveCameraSpeed();
  SaveNearPlane();
  SaveFarPlane();

  SaveVertexSize();
  SaveVertexDisplayMethod();
  SaveVertexColor();

  SaveEdgeSize();
  SaveEdgeType();
  SaveEdgeColor();

  Preferences::Get().Save();
}

void PreferencesWindow::HandleApplyButtonClick() { SaveSettings(); }

void PreferencesWindow::HandleCancelButtonClick() { CloseWindow(); }

void PreferencesWindow::HandleOkButtonClick() {
  SaveSettings();
  CloseWindow();
}

void PreferencesWindow::HandleResetSettingsButtonClick() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Reset settings", "Are you sure you want to reset all settings?",
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    Preferences::Get().settings->clear();
    Preferences::Get().Load();

    OpenPreferencesWindow();
    SaveSettings();
  }
}

void PreferencesWindow::CloseWindow() { close(); }
}  // namespace s21
