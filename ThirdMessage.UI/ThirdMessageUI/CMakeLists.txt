cmake_minimum_required(VERSION 3.16)

project(ThirdMessageUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appThirdMessageUI
    main.cpp
        ViewModels/LoginVIewModel.cpp
        ViewModels/LoginVIewModel.h
        Helpers/JsonHelper.hpp
        Models/LoginModel.cpp
        Models/LoginModel.h
)

qt_add_qml_module(appThirdMessageUI
    URI ThirdMessageUI
    QML_FILES
        qml/Main.qml
        qml/controls/SendButton.qml
        SOURCES MessageServices/websocket_service.h MessageServices/websocket_service.cpp
        SOURCES ViewModels/MainViewModel.cpp ViewModels/MainViewModel.h
        QML_FILES qml/LoginWindow.qml
        SOURCES MessageServices/networkservice.h MessageServices/networkservice.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appThirdMessageUI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appThirdMessageUI
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appThirdMessageUI
    PRIVATE Qt6::Quick
)
target_link_libraries(appThirdMessageUI PRIVATE Qt6::Core)
target_link_libraries(appThirdMessageUI PRIVATE Qt6::WebSockets)
target_link_libraries(appThirdMessageUI PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appThirdMessageUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
