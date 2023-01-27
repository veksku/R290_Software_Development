QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += warn_on
QMAKE_CXXFLAGS += $(shell Magick++-config)
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wextra
LIBS += $(shell Magick++-config --ldflags --libs)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cuvar_izlaza.cpp \
    src/displayElement.cpp \
    src/edge.cpp \
    src/element.cpp \
    src/enumi.cpp \
    src/pregovarac.cpp \
    src/CuvarSlike.cpp \
    src/isecanje.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/proizvodjac_projektant.cpp \
    src/skaliranje.cpp \
    src/slika.cpp \
    src/spajanje.cpp \
    src/tacka.cpp \
    src/transformacija_prvog_reda.cpp \
    src/transformacija_drugog_reda.cpp \
    src/enhance.cpp

HEADERS += \
    inc/CuvarSlike.hpp \
    inc/GotovaSlika.hpp \
    inc/cuvar_izlaza.hpp \
    inc/displayElement.hpp \
    inc/edge.hpp \
    inc/element.hpp \
    inc/enumi.hpp \
    inc/isecanje.hpp \
    inc/mainwindow.hpp \
    inc/proizvodjac_projektant.hpp \
    inc/skaliranje.hpp \
    inc/slika.hpp \
    inc/spajanje.hpp \
    inc/tacka.hpp \
    inc/transformacija.hpp \
    inc/pregovarac.hpp \
    inc/transformacija_prvog_reda.hpp \
    inc/transformacija_drugog_reda.hpp \
    inc/enhance.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources/Resources.qrc




