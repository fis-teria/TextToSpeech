cmake_minimum_required(VERSION 3.5)

project(Text2Speach VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D MS_WIN64 -IC:/Python310/include -LC:/Python310/libs -IC:/local/include -LC:/local/lib")
if(MINGW)
    set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/")
    message("MINGW")
else()
    if(MSVC)
        set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64/")
        message("MSVC")
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets LinguistTools WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)
get_target_property(QtCore_location Qt5::Multimedia LOCATION)
get_target_property(QtCore_location Qt5::Concurrent LOCATION)
get_target_property(QtCore_location Qt5::WebEngineWidgets LOCATION)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

set(TS_FILES Text2Speach_ja_JP.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ml_window.h
    ml_window.cpp
    ml_window.ui
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Text2Speach
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Text2Speach APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt--/qt--dd--xecutable.html#target--reation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Text2Speach SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Text2Speach
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
#add include Path
set(WIN_INCLUDE
    C:/local/include
    C:/Python310/include
    ${Qt5Multimedia_INCLUDE_DIRS}
)

set(WIN_LIB
    C:/local/lib
    C:/Python310/libs
#    C:/Python310/libs/python3.lib
#    C:/Python310/libs/python310.lib
#    C:/local/lib/boost_python310.lib
)

set(WIN_LIB_MSVC
    C:/local/libs
    C:/Python310/libs
)

if(WIN32)
    if(MINGW)
        include_directories(${WIN_INCLUDE})
        #include_directories(${header_dir_list})
        link_directories(${WIN_LIB})
        message("WIN_LIB" ${WIN_LIB})
    else()
        if(MSVC)
            include_directories(${WIN_INCLUDE})
            link_directories(${WIN_LIB_MSVC})
        else()
        endif()
    endif()
else()
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()

# get include path
get_directory_property(INCLUDE_PATH INCLUDE_DIRECTORIES)
set(_TMP_RESULT "")
set(_GLUE "") # effective glue is empty at the beginning
foreach(SINGLE_PATH ${INCLUDE_PATH})
    set(_TMP_RESULT "${_TMP_RESULT}${_GLUE}${SINGLE_PATH}")
    set(_GLUE ":") # delimiter
endforeach()
set(INCLUDE_PATH ${_TMP_RESULT})
message("${INCLUDE_PATH}")

message("${QT_QMAKE_EXECUTABLE}")
# library namesS
set(DEPENDENT_LIBS
    python3
    python310
    boost_python310
)

message("${DEPENDENT_LIBS}")

set(Boost_DEBUG ON)

target_link_libraries(Text2Speach PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Gui Qt5::Multimedia Qt5::Concurrent Qt5::WebEngineCore Qt5::WebEngineWidgets ${DEPENDENT_LIBS})
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Text2Speach)
endif()

set_target_properties(Text2Speach PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Text2Speach
    BUNDLE DESTINATION .
    LIBRARY DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION
    ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Text2Speach)
endif()
