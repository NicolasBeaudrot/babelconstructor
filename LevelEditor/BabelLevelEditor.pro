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
DESTDIR = "bin"
INCLUDEPATH += "../ExternLibrairie/SFML-1.6/include"
DEPENDPATH += "../ExternLibrairie/SFML-1.6/lib"
LIBS += -lsfml-graphics \
    -lsfml-window \
    -lsfml-system
FORMS += ui/main.ui
