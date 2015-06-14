QT+= widgets
QT+= xml
QT+= core
QT+= gui
HEADERS += \
    tache.h \
    projet.h \
    duree.h \
    exception.h \
    projetmanager.h \
    precedencemanager.h \
    precedence.h \
    evenement.h \
    activitetraditionnelle.h \
    tachemanager.h \
    iterator.h \
    programmation.h \
    semaine.h \
    agenda.h \
    fenetreGestionProjet.h \
    fenetreprogrammer.h \
    fenetrePrincipal.h \
    fenetreactivitetrad.h \
    fenetreprogrammertache.h

SOURCES += \
    tache.cpp \
    main.cpp \
    projet.cpp \
    duree.cpp \
    tachemanager.cpp \
    projetmanager.cpp \
    precedencemanager.cpp \
    precedence.cpp \
    evenement.cpp \
    activitetraditionnelle.cpp \
    programmation.cpp \
    semaine.cpp \
    agenda.cpp \
    fenetreGestionProjet.cpp \
    fenetreprogrammer.cpp \
    fenetrePrincipal.cpp \
    fenetreactivitetrad.cpp \
    fenetreprogrammertache.cpp

FORMS += \
    fenetreprogrammer.ui \
    fenetrePrincipal.ui \
    fenetreactivitetrad.ui \
    fenetreprogrammertache.ui

