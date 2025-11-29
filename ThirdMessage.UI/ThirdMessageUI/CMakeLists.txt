cmake_minimum_required(VERSION 3.16)

project(ThirdMessageUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appThirdMessageUI
    main.cpp
    Helpers/json_helper.hpp
    Models/login_model.h Models/login_model.cpp
    Models/friend_model.h Models/friend_model.cpp
    Models/message_model.h Models/message_model.cpp
)

qt_add_qml_module(appThirdMessageUI
    URI ThirdMessageUI
    QML_FILES
        qml/Main.qml
        qml/LoginWindow.qml
        qml/controls/SendButton.qml
        qml/controls/FriendListItem.qml
        qml/controls/MessageListItem.qml
        qml/controls/FriendSearchEdit.qml
        SOURCES
        MessageServices/websocket_service.h
        MessageServices/websocket_service.cpp
        ViewModels/main_viewmodel.cpp ViewModels/main_viewmodel.h
        ViewModels/login_viewmodel.cpp ViewModels/login_viewmodel.h
        MessageServices/network_service.h MessageServices/network_service.cpp
        MessageServices/message_service.h MessageServices/message_service.cpp
        Models/friend_listmodel.h Models/friend_listmodel.cpp
        Models/message_listmodel.h Models/message_listmodel.cpp
        RESOURCES
        Image/image.qrc
        config.ini
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

add_custom_command(TARGET appThirdMessageUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        $<TARGET_FILE_DIR:appThirdMessageUI>/config.ini
)

include(GNUInstallDirs)
install(TARGETS appThirdMessageUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)