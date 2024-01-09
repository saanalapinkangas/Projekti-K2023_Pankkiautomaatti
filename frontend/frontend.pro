QT       += core gui serialport
QT +=network #lisätty http:tä varten

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosecard.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    withdrawalfailed.cpp \
    withdrawalsuccessful.cpp \
    logout.cpp \
    selectactionmenu.cpp \
    selectsum.cpp \
    showaccountbalance.cpp \
    showtransactions.cpp

HEADERS += \
    choosecard.h \
    login.h \
    logout.h \
    selectactionmenu.h \
    withdrawalfailed.h \
    withdrawalsuccessful.h \
    selectsum.h \
    mainwindow.h \
    showaccountbalance.h \
    showtransactions.h

FORMS += \
    choosecard.ui \
    login.ui \
    mainwindow.ui \
    withdrawalfailed.ui \
    withdrawalsuccessful.ui \
    logout.ui \
    mainwindow.ui \
    selectactionmenu.ui \
    selectsum.ui \
    showaccountbalance.ui \
    showtransactions.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/DLL_rfid/build/debug/ -lDLL_rfid

INCLUDEPATH += $$PWD/DLL_rfid
DEPENDPATH += $$PWD/DLL_rfid

win32: LIBS += -L$$PWD/RestApiDLL/build/debug/ -lRestApiDLL

INCLUDEPATH += $$PWD/RestApiDLL
DEPENDPATH += $$PWD/RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/pinUIDLL/build/release/ -lpinUIDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/pinUIDLL/build/debug/ -lpinUIDLL

INCLUDEPATH += $$PWD/pinUIDLL
DEPENDPATH += $$PWD/pinUIDLL
