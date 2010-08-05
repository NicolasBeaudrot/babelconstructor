DESTDIR = "bin"
QT += xml
INCLUDEPATH += "../ExternLibrairie/SFML-1.6/include"
DEPENDPATH += "../ExternLibrairie/SFML-1.6/lib"
unix:LIBS += -lsfml-graphics -lsfml-window -lsfml-system
win32:LIBS += ..\ExternLibrairie\SFML-1.6\lib\libsfml-graphics.a ..\ExternLibrairie\SFML-1.6\lib\libsfml-window.a ..\ExternLibrairie\SFML-1.6\lib\libsfml-system.a
FORMS += ui/main.ui
HEADERS += Canvas/SFMLCanvas.h \
    Canvas/QSFMLCanvas.hpp \
    Element/listElement.h \
    Item/ItemFactory.h \
    Item/Item.h
SOURCES += Canvas/SFMLCanvas.cpp \
    Canvas/QSFMLCanvas.cpp \
    main.cpp \
    Item/ItemFactory.cpp \
    Item/Item.cpp
