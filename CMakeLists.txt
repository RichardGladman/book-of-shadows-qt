cmake_minimum_required(VERSION 3.16)

project(BookOfShadows VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BookOfShadows
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        polarity/polarityframe.h polarity/polarityframe.cpp polarity/polarityframe.ui
        polarity/polaritymodel.h polarity/polaritymodel.cpp
        settings/settingsframe.h settings/settingsframe.cpp settings/settingsframe.ui
        polarity/polarityform.h polarity/polarityform.cpp polarity/polarityform.ui
        polarity/polarityviewdialog.h polarity/polarityviewdialog.cpp polarity/polarityviewdialog.ui
        colours/colourframe.h colours/colourframe.cpp colours/colourframe.ui
        colours/colourmodel.h colours/colourmodel.cpp
        colours/colourform.h colours/colourform.cpp colours/colourform.ui
        gods/godframe.h gods/godframe.cpp gods/godframe.ui
        gods/godmodel.h gods/godmodel.cpp
        gods/godform.h gods/godform.cpp gods/godform.ui
        herbs/herbframe.h herbs/herbframe.cpp herbs/herbframe.ui
        herbs/herbform.h herbs/herbform.cpp herbs/herbform.ui
        herbs/herbmodel.h herbs/herbmodel.cpp
        planets/planetsframe.h planets/planetsframe.cpp planets/planetsframe.ui
        planets/planetmodel.h planets/planetmodel.cpp
        planets/planetform.h planets/planetform.cpp planets/planetform.ui
        animals/animalframe.h animals/animalframe.cpp animals/animalframe.ui
        animals/animalmodel.h animals/animalmodel.cpp
        animals/animalform.h animals/animalform.cpp animals/animalform.ui
        trees/treesframe.h trees/treesframe.cpp trees/treesframe.ui
        trees/treemodel.h trees/treemodel.cpp
        trees/treeform.h trees/treeform.cpp trees/treeform.ui
        zodiac/zodiacmodel.h zodiac/zodiacmodel.cpp
        zodiac/zodiacform.h zodiac/zodiacform.cpp zodiac/zodiacform.ui
        zodiac/zodiacframe.h zodiac/zodiacframe.cpp zodiac/zodiacframe.ui
        about/aboutdialog.h about/aboutdialog.cpp about/aboutdialog.ui
        notes/notemodel.h notes/notemodel.cpp
        dbinitializer.h dbinitializer.cpp
        runestones/runestoneframe.h runestones/runestoneframe.cpp runestones/runestoneframe.ui
        runestones/runestoneform.h runestones/runestoneform.cpp runestones/runestoneform.ui
        runestones/runestonecorresponderchooser.h runestones/runestonecorresponderchooser.cpp runestones/runestonecorresponderchooser.ui
        runestones/runestonemodel.h runestones/runestonemodel.cpp
        tarot/tarotmodel.h tarot/tarotmodel.cpp
        tarot/tarotcorresponderchooser.h tarot/tarotcorresponderchooser.cpp tarot/tarotcorresponderchooser.ui
        tarot/tarotform.h tarot/tarotform.cpp tarot/tarotform.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BookOfShadows APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BookOfShadows SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BookOfShadows
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BookOfShadows PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BookOfShadows)
endif()
set_target_properties(BookOfShadows PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BookOfShadows
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BookOfShadows)
endif()
