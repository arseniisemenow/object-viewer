#ifndef CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STRUCTS_H_
#define CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STRUCTS_H_

#include <QMetaType>

namespace s21 {

enum class CameraMode {
  kNone = 0,
  kFly = 1 << 0,
  kTurnable = 1 << 1,
};

namespace OpenType {
enum OpenType {
  None = 0,
  Inspector = 1 << 0,
  RecentFiles = 1 << 1,
};
}

namespace Projection {
enum Type {
  kNone = 0,
  kPerspective = 1 << 0,
  kParallel = 1 << 1,
};
}

namespace Vertex {
enum DisplayMethod { kNone = 0, kCircle = 1 << 0, kSquare = 1 << 1 };
}

namespace Edge {
enum Type { kNone = 0, kSolid = 1 << 0, kDashed = 1 << 1 };
};

class DockWidgetSettings;
class DockWidgetModelEditor;

typedef struct {
  DockWidgetSettings *dock_widget_settings_;
  DockWidgetModelEditor *dock_widget_model_editor_;
} DockWidgets;

}  // namespace s21

Q_DECLARE_METATYPE(s21::CameraMode)

#endif  // CPP4_3D_VIEWER_V_2_0_1_VIEW_UI_STRUCTS_H_