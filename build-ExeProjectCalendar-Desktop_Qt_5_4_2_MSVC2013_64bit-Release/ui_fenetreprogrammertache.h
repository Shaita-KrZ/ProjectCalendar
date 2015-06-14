/********************************************************************************
** Form generated from reading UI file 'fenetreprogrammertache.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREPROGRAMMERTACHE_H
#define UI_FENETREPROGRAMMERTACHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FenetreProgrammerTache
{
public:
    QGridLayout *gridLayout;
    QLabel *lProjet;
    QLabel *lDateHeure;
    QDialogButtonBox *bCancel;
    QComboBox *inProjet;
    QComboBox *inTache;
    QComboBox *inTache2;
    QDateTimeEdit *inDateHeure;
    QLabel *lTache;
    QDialogButtonBox *bOK;

    void setupUi(QDialog *FenetreProgrammerTache)
    {
        if (FenetreProgrammerTache->objectName().isEmpty())
            FenetreProgrammerTache->setObjectName(QStringLiteral("FenetreProgrammerTache"));
        FenetreProgrammerTache->resize(400, 300);
        gridLayout = new QGridLayout(FenetreProgrammerTache);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lProjet = new QLabel(FenetreProgrammerTache);
        lProjet->setObjectName(QStringLiteral("lProjet"));

        gridLayout->addWidget(lProjet, 0, 0, 1, 1);

        lDateHeure = new QLabel(FenetreProgrammerTache);
        lDateHeure->setObjectName(QStringLiteral("lDateHeure"));

        gridLayout->addWidget(lDateHeure, 4, 0, 1, 1);

        bCancel = new QDialogButtonBox(FenetreProgrammerTache);
        bCancel->setObjectName(QStringLiteral("bCancel"));
        bCancel->setOrientation(Qt::Horizontal);
        bCancel->setStandardButtons(QDialogButtonBox::Cancel);

        gridLayout->addWidget(bCancel, 6, 1, 1, 1);

        inProjet = new QComboBox(FenetreProgrammerTache);
        inProjet->setObjectName(QStringLiteral("inProjet"));

        gridLayout->addWidget(inProjet, 0, 1, 1, 1);

        inTache = new QComboBox(FenetreProgrammerTache);
        inTache->setObjectName(QStringLiteral("inTache"));

        gridLayout->addWidget(inTache, 1, 1, 1, 1);

        inTache2 = new QComboBox(FenetreProgrammerTache);
        inTache2->setObjectName(QStringLiteral("inTache2"));

        gridLayout->addWidget(inTache2, 2, 1, 1, 1);

        inDateHeure = new QDateTimeEdit(FenetreProgrammerTache);
        inDateHeure->setObjectName(QStringLiteral("inDateHeure"));

        gridLayout->addWidget(inDateHeure, 4, 1, 1, 1);

        lTache = new QLabel(FenetreProgrammerTache);
        lTache->setObjectName(QStringLiteral("lTache"));

        gridLayout->addWidget(lTache, 1, 0, 1, 1);

        bOK = new QDialogButtonBox(FenetreProgrammerTache);
        bOK->setObjectName(QStringLiteral("bOK"));
        bOK->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(bOK, 5, 1, 1, 1);


        retranslateUi(FenetreProgrammerTache);
        QObject::connect(bCancel, SIGNAL(accepted()), FenetreProgrammerTache, SLOT(accept()));
        QObject::connect(bCancel, SIGNAL(rejected()), FenetreProgrammerTache, SLOT(reject()));

        QMetaObject::connectSlotsByName(FenetreProgrammerTache);
    } // setupUi

    void retranslateUi(QDialog *FenetreProgrammerTache)
    {
        FenetreProgrammerTache->setWindowTitle(QApplication::translate("FenetreProgrammerTache", "Dialog", 0));
        lProjet->setText(QApplication::translate("FenetreProgrammerTache", "Projet :", 0));
        lDateHeure->setText(QApplication::translate("FenetreProgrammerTache", "Date & heure :", 0));
        lTache->setText(QApplication::translate("FenetreProgrammerTache", "Tache :", 0));
    } // retranslateUi

};

namespace Ui {
    class FenetreProgrammerTache: public Ui_FenetreProgrammerTache {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREPROGRAMMERTACHE_H
