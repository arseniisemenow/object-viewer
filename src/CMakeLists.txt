cmake_minimum_required(VERSION 3.5)

project(3d_viewer_cpp VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL)

find_package(QT NAMES Qt6 Qt5 COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt6_add_resources(STYLE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/ui/styles/styles.qrc)
    qt6_add_resources(MEDIA_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/ui/media/media.qrc)
    qt6_add_resources(SHADERS_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/opengl/shaders.qrc)
elseif (${QT_VERSION_MAJOR} EQUAL 5)
    qt5_add_resources(STYLE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/ui/styles/styles.qrc)
    qt5_add_resources(MEDIA_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/ui/media/media.qrc)
    qt5_add_resources(SHADERS_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/View/opengl/shaders.qrc)
endif ()

set(PROJECT_SOURCES
        ${STYLE_RESOURCES}
        ${MEDIA_RESOURCES}
        ${SHADERS_RESOURCES}
        Matrix/Matrix.cc
        Matrix/Matrix.h
        View/opengl/Camera.cc
        View/opengl/Camera.h
        View/opengl/Constants.h
        View/opengl/Mesh.cc
        View/opengl/Mesh.h
        View/opengl/Renderer.cc
        View/opengl/Renderer.h
        View/opengl/OpenGLWidget/CameraMode.h
        View/opengl/OpenGLWidget/Transform.h
        View/opengl/OpenGLWidget/OpenGLWidget.cc
        View/opengl/OpenGLWidget/OpenGLWidget.h
        View/ui/modalWidgets/AboutWindow/AboutWindow.ui
        View/ui/modalWidgets/FileInformationWindow/FileInformationWindow.ui
        View/ui/modalWidgets/PreferencesWindow/PreferencesWindow.ui
        View/ui/structs.h
        View/ui/styles/global_styles.h
        View/ui/styles/styles.h
        View/ui/userInteractionWidgets/ModelEditor.h
        View/ui/userInteractionWidgets/ModelViewer.h
        View/ui/menuBar/MenuBar/MenuBar.h
        View/ui/RecentFile/RecentFile.h
        View/ui/modalWidgets/AboutWindow/AboutWindow.h
        View/ui/modalWidgets/FileDialog/FileDialog.h
        View/ui/modalWidgets/PreferencesWindow/PreferencesWindow.h
        View/ui/MediaProcessor/MediaProcessor.h
        View/ui/SpinBox/SpinBox.h
        View/ui/SpinBox/SpinBoxLineEdit.h
        View/ui/SpinBox/SpinBoxPushButton.h
        View/ui/TitleBar/TitleBar.h
        View/ui/TransformWidget/TransformWidget.h
        View/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h
        View/ui/dockWidgets/DockWidgetSettings/DockWidgetSettings.h
        View/ui/EventHandler/EventHandler.h
        View/ui/FileHandler/FileHandler.h
        View/ui/StatusBar/StatusBar.h
        View/ui/menuBar/MenuFile/MenuFile.h
        View/ui/menuBar/MenuMedia/MenuMedia.h
        View/ui/Preferences/Preferences.h
        View/ui/View/View.h
        View/ui/menuBar/MenuViews/MenuViews.h
        View/ui/ColorPushButton/ColorPushButton.h
        View/ui/modalWidgets/FileInformationWindow/FileInformationWindow.h
        View/ui/ColorPushButton/ColorPushButton.cc
        View/ui/MediaProcessor/MediaProcessor.cc
        View/ui/SpinBox/SpinBox.cc
        View/ui/SpinBox/SpinBoxLineEdit.cc
        View/ui/SpinBox/SpinBoxPushButton.cc
        View/ui/TitleBar/TitleBar.cc
        View/ui/TransformWidget/TransformWidget.cc
        View/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.cc
        View/ui/dockWidgets/DockWidgetSettings/DockWidgetSettings.cc
        View/ui/EventHandler/EventHandler.cc
        View/ui/menuBar/MenuFile/MenuFile.cc
        View/ui/menuBar/MenuMedia/MenuMedia.cc
        View/ui/Preferences/Preferences.cc
        View/ui/styles/styles.cc
        View/ui/View/View.cc
        View/ui/View/View.ui
        View/ui/menuBar/MenuBar/MenuBar.cc
        View/ui/menuBar/MenuViews/MenuViews.cc
        View/ui/modalWidgets/AboutWindow/AboutWindow.cc
        View/ui/modalWidgets/FileDialog/FileDialog.cc
        View/ui/modalWidgets/PreferencesWindow/PreferencesWindow.cc
        View/ui/userInteractionWidgets/ModelEditor.cc
        View/ui/modalWidgets/FileInformationWindow/FileInformationWindow.cc
        Controller/Controller.cc
        Controller/Controller.h
        common/ParseResult.h
        common/ParseErrorEnums.h
        common/MeshData.h
        Model/Model.cc
        Model/Model.h
        Model/Parser/Parser.cc
        Model/Parser/Parser.h
        Model/Transformation/Transformation.cc
        Model/Transformation/Transformation.h
        Model/ModelConstants.h
        Gif/Gif.h
        Gif/Gif.cc
        main.cc
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3d_viewer_cpp
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET 3d_viewer_cpp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(3d_viewer_cpp SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(3d_viewer_cpp
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()

target_link_libraries(3d_viewer_cpp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::OpenGL
        $<$<VERSION_LESS:${QT_VERSION_MAJOR},6>:GL> # Conditionally add QtOpenGLWidgets for Qt version less than 6
        $<$<VERSION_EQUAL:${QT_VERSION_MAJOR},6>:Qt${QT_VERSION_MAJOR}::OpenGLWidgets> # Add QtOpenGLWidgets only for Qt version 6
)

set_target_properties(3d_viewer_cpp PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3d_viewer_cpp)
endif ()
