/********************************************************************************
** Form generated from reading UI file 'fenetreactivitetrad.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREACTIVITETRAD_H
#define UI_FENETREACTIVITETRAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_FenetreActiviteTrad
{
public:
    QDialogButtonBox *bOKcancel;
    QLabel *lTitre;
    QLabel *lAjouterAT;
    QLabel *lDuree;
    QDateTimeEdit *inDateTimeProg;
    QTimeEdit *inDuree;
    QLabel *lProgrammation;
    QLineEdit *inTitre;

    void setupUi(QDialog *FenetreActiviteTrad)
    {
        if (FenetreActiviteTrad->objectName().isEmpty())
            FenetreActiviteTrad->setObjectName(QStringLiteral("FenetreActiviteTrad"));
        FenetreActiviteTrad->resize(364, 173);
        bOKcancel = new QDialogButtonBox(FenetreActiviteTrad);
        bOKcancel->setObjectName(QStringLiteral("bOKcancel"));
        bOKcancel->setGeometry(QRect(200, 140, 156, 23));
        bOKcancel->setOrientation(Qt::Horizontal);
        bOKcancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lTitre = new QLabel(FenetreActiviteTrad);
        lTitre->setObjectName(QStringLiteral("lTitre"));
        lTitre->setGeometry(QRect(30, 50, 32, 16));
        lAjouterAT = new QLabel(FenetreActiviteTrad);
        lAjouterAT->setObjectName(QStringLiteral("lAjouterAT"));
        lAjouterAT->setGeometry(QRect(10, 10, 341, 20));
        lDuree = new QLabel(FenetreActiviteTrad);
        lDuree->setObjectName(QStringLiteral("lDuree"));
        lDuree->setGeometry(QRect(220, 50, 36, 16));
        inDateTimeProg = new QDateTimeEdit(FenetreActiviteTrad);
        inDateTimeProg->setObjectName(QStringLiteral("inDateTimeProg"));
        inDateTimeProg->setGeometry(QRect(118, 90, 112, 20));
        inDuree = new QTimeEdit(FenetreActiviteTrad);
        inDuree->setObjectName(QStringLiteral("inDuree"));
        inDuree->setGeometry(QRect(290, 50, 53, 20));
        lProgrammation = new QLabel(FenetreActiviteTrad);
        lProgrammation->setObjectName(QStringLiteral("lProgrammation"));
        lProgrammation->setGeometry(QRect(30, 90, 82, 16));
        inTitre = new QLineEdit(FenetreActiviteTrad);
        inTitre->setObjectName(QStringLiteral("inTitre"));
        inTitre->setGeometry(QRect(80, 50, 113, 20));

        retranslateUi(FenetreActiviteTrad);
        QObject::connect(bOKcancel, SIGNAL(accepted()), FenetreActiviteTrad, SLOT(accept()));
        QObject::connect(bOKcancel, SIGNAL(rejected()), FenetreActiviteTrad, SLOT(reject()));

        QMetaObject::connectSlotsByName(FenetreActiviteTrad);
    } // setupUi

    void retranslateUi(QDialog *FenetreActiviteTrad)
    {
        FenetreActiviteTrad->setWindowTitle(QApplication::translate("FenetreActiviteTrad", "Dialog", 0));
        lTitre->setText(QApplication::translate("FenetreActiviteTrad", "Titre : ", 0));
        lAjouterAT->setText(QApplication::translate("FenetreActiviteTrad", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">Ajouter une Activit\303\251 Traditionnelle</span></p></body></html>", 0));
        lDuree->setText(QApplication::translate("FenetreActiviteTrad", "Duree :", 0));
        lProgrammation->setText(QApplication::translate("FenetreActiviteTrad", "Programmation : ", 0));
    } // retranslateUi

};

namespace Ui {
    class FenetreActiviteTrad: public Ui_FenetreActiviteTrad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREACTIVITETRAD_H
