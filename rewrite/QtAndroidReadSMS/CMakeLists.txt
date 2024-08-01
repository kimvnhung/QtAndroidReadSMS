cmake_minimum_required(VERSION 3.16)

project(QtAndroidReadSMS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file(GLOB_RECURSE RCCS ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)


qt_add_executable(appQtAndroidReadSMS
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RCCS}
)

# qt_add_qml_module(appQtAndroidReadSMS
#     URI QtAndroidReadSMS
#     VERSION 1.0
# )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtAndroidReadSMS PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtAndroidReadSMS
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtAndroidReadSMS
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appQtAndroidReadSMS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
