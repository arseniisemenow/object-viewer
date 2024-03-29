#include "DockWidgetSettings.h"

namespace s21 {

DockWidgetSettings::DockWidgetSettings(QWidget* parent)
    : QDockWidget(parent), is_right_dock_button_checked_(false) {
  central_widget_ = new QWidget(this);
  this->setWidget(central_widget_);

  this->setFeatures(QDockWidget::QDockWidget::NoDockWidgetFeatures);

  setFixedHeight(23);

  camera_icon_label_ = new QLabel();
  SetCameraIconLabel();

  projection_type_combo_box_ = new QComboBox();
  SetProjectionTypeComboBox();

  camera_mode_combo_box_ = new QComboBox();
  SetCameraModeComboBox();

  hide_right_dock_button_ = new QPushButton();
  SetHideDockButton();

  layout_ = new QHBoxLayout(central_widget_);
  SetLayoutForWidget();

  connect(&EventHandler::Get(),
          &EventHandler::EventToggledDockWidgetModelEditor, this,
          &DockWidgetSettings::UpdateDockWidgetModelEditorButtonStatus);

  connect(projection_type_combo_box_,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::HandleProjectionTypeChanged);

  connect(camera_mode_combo_box_,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::HandleCameraModeChanged);

  connect(&EventHandler::Get(), &EventHandler::EventResetSettings, this,
          &DockWidgetSettings::UpdateDockWidget);

  connect(this, &DockWidgetSettings::EventProjectionTypeChanged,
          &EventHandler::Get(), &EventHandler::ProjectionTypeChanged);
  connect(this, &DockWidgetSettings::EventCameraModeChanged,
          &EventHandler::Get(), &EventHandler::CameraModeChanged);

  connect(projection_type_combo_box_,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::HandleProjectionTypeChanged);
  connect(camera_mode_combo_box_,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::HandleCameraModeChanged);

  LoadProjectionTypeSettings();
  LoadCameraModeSettings();

  emit CameraModeChanged();
  emit ProjectionTypeChanged();

  UpdateHideRightDockWidgetButtonStyle();
}

void DockWidgetSettings::UpdateDockWidget() {
  LoadCameraModeSettings();
  LoadProjectionTypeSettings();
}

void DockWidgetSettings::UpdateStyles() {
  this->setStyleSheet(GetStylesFromFile(PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE));
  central_widget_->setStyleSheet(
      GetStylesFromFile(PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE));
}

void DockWidgetSettings::HandleProjectionTypeChanged(const int index) {
  SaveProjectionTypeSettings();

  if (index == ProjectionTypeComboBoxIndex::kParallel) {
    camera_mode_combo_box_->setItemData(CameraModeComboBoxIndex::kFly,
                                        QVariant(Qt::ItemIsEnabled),
                                        Qt::UserRole - 1);
    camera_mode_combo_box_->setCurrentIndex(CameraModeComboBoxIndex::kTurnable);
  } else {
    camera_mode_combo_box_->setItemData(
        CameraModeComboBoxIndex::kFly,
        QVariant(Qt::ItemIsEnabled | Qt::ItemIsSelectable), Qt::UserRole - 1);
  }
  emit ProjectionTypeChanged();
}

void DockWidgetSettings::HandleCameraModeChanged(int index) {
  SaveCameraModeSettings();
  emit CameraModeChanged();
}

void DockWidgetSettings::UpdateDockWidgetModelEditorButtonStatus() {
  ToggleChecked();
  UpdateHideRightDockWidgetButtonStyle();
}

void DockWidgetSettings::ToggleChecked() {
  is_right_dock_button_checked_ = !is_right_dock_button_checked_;
}

void DockWidgetSettings::SetCameraIconLabel() const {
  camera_icon_label_->setFixedSize(
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
  camera_icon_label_->setIndent(5);
  camera_icon_label_->setObjectName(OBJECT_NAME_CAMERA_ICON_LABEL);
}

void DockWidgetSettings::SetProjectionTypeComboBox() const {
  projection_type_combo_box_->addItem(PROJECTION_TYPE_PERSPECTIVE_STRING);
  projection_type_combo_box_->addItem(PROJECTION_TYPE_PARALLEL_STRING);
  projection_type_combo_box_->setFixedSize(
      FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
}

void DockWidgetSettings::SetHideDockButton() {
  hide_right_dock_button_->setFixedSize(
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);

  connect(hide_right_dock_button_, &QPushButton::clicked, &EventHandler::Get(),
          &EventHandler::ToggleDockWidgetModelEditor);
}

void DockWidgetSettings::SetLayoutForWidget() const {
  layout_->addWidget(camera_icon_label_);
  layout_->addWidget(projection_type_combo_box_);

  layout_->addItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

  layout_->addWidget(camera_mode_combo_box_);
  layout_->addWidget(hide_right_dock_button_);

  layout_->setContentsMargins(DOCK_WIDGET_MARGIN_VALUE, 0,
                              DOCK_WIDGET_MARGIN_VALUE, 0);
}

void DockWidgetSettings::UpdateHideRightDockWidgetButtonStyle() {
  if (is_right_dock_button_checked_) {
    hide_right_dock_button_->setObjectName(
        OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_CHECKED);
  } else {
    hide_right_dock_button_->setObjectName(
        OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_DEFAULT);
  }
  UpdateStyles();
}

void DockWidgetSettings::SetCameraModeComboBox() const {
  camera_mode_combo_box_->addItem(CAMERA_MODE_FLY_STRING);
  camera_mode_combo_box_->addItem(CAMERA_MODE_TURNABLE_STRING);
  camera_mode_combo_box_->setFixedSize(
      FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
}

void DockWidgetSettings::SaveProjectionTypeSettings() const {
  if (projection_type_combo_box_->currentIndex() ==
      ProjectionTypeComboBoxIndex::kPerspective) {
    Preferences::Get().SetProjectionType(Projection::Type::kPerspective);
  } else if (projection_type_combo_box_->currentIndex() ==
             ProjectionTypeComboBoxIndex::kParallel) {
    Preferences::Get().SetProjectionType(Projection::Type::kParallel);
  }
  Preferences::Get().Save();
}

void DockWidgetSettings::LoadProjectionTypeSettings() const {
  if (Preferences::Get().GetProjectionType() ==
      Projection::Type::kPerspective) {
    projection_type_combo_box_->setCurrentIndex(
        ProjectionTypeComboBoxIndex::kPerspective);
  } else if (Preferences::Get().GetProjectionType() ==
             Projection::Type::kParallel) {
    projection_type_combo_box_->setCurrentIndex(
        ProjectionTypeComboBoxIndex::kParallel);
  }
}

void DockWidgetSettings::SaveCameraModeSettings() const {
  if (camera_mode_combo_box_->currentIndex() == CameraModeComboBoxIndex::kFly) {
    Preferences::Get().SetCameraMode(CameraMode::kFly);
  } else if (camera_mode_combo_box_->currentIndex() ==
             CameraModeComboBoxIndex::kTurnable) {
    Preferences::Get().SetCameraMode(CameraMode::kTurnable);
  }
  Preferences::Get().Save();
}

void DockWidgetSettings::LoadCameraModeSettings() const {
  if (Preferences::Get().GetCameraMode() == CameraMode::kFly) {
    camera_mode_combo_box_->setCurrentIndex(CameraModeComboBoxIndex::kFly);
  } else if (Preferences::Get().GetCameraMode() == CameraMode::kTurnable) {
    camera_mode_combo_box_->setCurrentIndex(CameraModeComboBoxIndex::kTurnable);
  }
}

}  // namespace s21