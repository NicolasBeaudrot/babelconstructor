HEADERS += Canvas/SFMLCanvas.h \
    Canvas/QSFMLCanvas.hpp
SOURCES += Canvas/SFMLCanvas.cpp \
    Canvas/QSFMLCanvas.cpp \
    main.cpp
DESTDIR = "bin"
INCLUDEPATH += "../ExternLibrairie/SFML-1.6/include"
DEPENDPATH += "../ExternLibrairie/SFML-1.6/lib"
LIBS += -lsfml-graphics \
    -lsfml-window \
    -lsfml-system
FORMS += ui/main.ui
