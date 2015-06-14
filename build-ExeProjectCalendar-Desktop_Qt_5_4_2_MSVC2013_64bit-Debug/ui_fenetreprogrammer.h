/********************************************************************************
** Form generated from reading UI file 'fenetreprogrammer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREPROGRAMMER_H
#define UI_FENETREPROGRAMMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenetreProgrammer
{
public:
    QPushButton *bTache;
    QPushButton *bActiviteTraditionnelle;
    QDialogButtonBox *bOKCancel;

    void setupUi(QWidget *FenetreProgrammer)
    {
        if (FenetreProgrammer->objectName().isEmpty())
            FenetreProgrammer->setObjectName(QStringLiteral("FenetreProgrammer"));
        FenetreProgrammer->resize(301, 182);
        bTache = new QPushButton(FenetreProgrammer);
        bTache->setObjectName(QStringLiteral("bTache"));
        bTache->setGeometry(QRect(160, 20, 131, 91));
        bActiviteTraditionnelle = new QPushButton(FenetreProgrammer);
        bActiviteTraditionnelle->setObjectName(QStringLiteral("bActiviteTraditionnelle"));
        bActiviteTraditionnelle->setGeometry(QRect(10, 20, 131, 91));
        bOKCancel = new QDialogButtonBox(FenetreProgrammer);
        bOKCancel->setObjectName(QStringLiteral("bOKCancel"));
        bOKCancel->setGeometry(QRect(120, 140, 156, 23));
        bOKCancel->setStandardButtons(QDialogButtonBox::Cancel);

        retranslateUi(FenetreProgrammer);

        QMetaObject::connectSlotsByName(FenetreProgrammer);
    } // setupUi

    void retranslateUi(QWidget *FenetreProgrammer)
    {
        FenetreProgrammer->setWindowTitle(QApplication::translate("FenetreProgrammer", "Form", 0));
        bTache->setText(QApplication::translate("FenetreProgrammer", "Tache d'un\n"
"Projet", 0));
        bActiviteTraditionnelle->setText(QApplication::translate("FenetreProgrammer", "Activit\303\251\n"
"Traditionnelle", 0));
    } // retranslateUi

};

namespace Ui {
    class FenetreProgrammer: public Ui_FenetreProgrammer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREPROGRAMMER_H
