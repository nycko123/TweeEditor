cmake_minimum_required(VERSION 3.8)
project(TweeEdit)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH D:/Qt5.14.1/5.14.1/mingw73_64)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5LinguistTools)
find_package(Qt5PrintSupport)

set(TRANSLATE_FILES  translations/TweeSimpleEdit_pl_PL.ts translations/TweeSimpleEdit_zh_CN.ts)

qt5_create_translation(QM_FILES ${TRANSLATE_FILES})
qt5_add_translation(QM_FILES ${TRANSLATE_FILES})

set(RESOURCE_FILES resource.qrc)

set(DIALOG_HEADERS FindDialog.h TweeFirstUseDialog.h TweeLanguageDialog.h TweeBugReportDialog.h)
set(DIALOG_SOURCES FindDialog.cpp TweeFirstUseDialog.cpp TweeLanguageDialog.cpp TweeBugReportDialog.cpp)

set(MAINWINDOW_HEADERS mainwindow.h)
set(MAINWINDOW_SOURCES
        mainwindow_slots_help.cpp mainwindow_slots_file.cpp mainwindow_slots_edit.cpp
        mainwindow_oncreate.cpp mainwindow_events.cpp mainwindow_basic.cpp
        mainwindow_slots_view.cpp)

add_executable(TweeEdit main.cpp
          ${RESOURCE_FILES} ${DIALOG_HEADERS} ${DIALOG_SOURCES}
            ${MAINWINDOW_HEADERS} ${MAINWINDOW_SOURCES}
        ${RESOURCE_FILES}
        )

target_link_libraries(TweeEdit Qt5::Widgets Qt5::PrintSupport Qt5::Core Qt5::Gui)

qt5_use_modules(TweeEdit Core Widgets Gui LinguistTools PrintSupport)