/********************************************************************************
** Form generated from reading UI file 'fenetrePrincipal.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREPRINCIPAL_H
#define UI_FENETREPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenAgenda
{
public:
    QLabel *labelSemaine;
    QPushButton *bSemaineSuiv;
    QPushButton *bSemainePrec;
    QPushButton *bGoProjets;
    QTableWidget *tSemaine;
    QPushButton *bImport;
    QPushButton *bExport;
    QPushButton *pushButton;

    void setupUi(QWidget *FenAgenda)
    {
        if (FenAgenda->objectName().isEmpty())
            FenAgenda->setObjectName(QStringLiteral("FenAgenda"));
        FenAgenda->resize(591, 428);
        labelSemaine = new QLabel(FenAgenda);
        labelSemaine->setObjectName(QStringLiteral("labelSemaine"));
        labelSemaine->setGeometry(QRect(270, 20, 221, 31));
        labelSemaine->setAlignment(Qt::AlignCenter);
        bSemaineSuiv = new QPushButton(FenAgenda);
        bSemaineSuiv->setObjectName(QStringLiteral("bSemaineSuiv"));
        bSemaineSuiv->setGeometry(QRect(510, 20, 71, 31));
        bSemainePrec = new QPushButton(FenAgenda);
        bSemainePrec->setObjectName(QStringLiteral("bSemainePrec"));
        bSemainePrec->setGeometry(QRect(180, 20, 71, 31));
        bGoProjets = new QPushButton(FenAgenda);
        bGoProjets->setObjectName(QStringLiteral("bGoProjets"));
        bGoProjets->setGeometry(QRect(10, 10, 101, 71));
        tSemaine = new QTableWidget(FenAgenda);
        if (tSemaine->columnCount() < 1)
            tSemaine->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tSemaine->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tSemaine->rowCount() < 7)
            tSemaine->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tSemaine->setVerticalHeaderItem(6, __qtablewidgetitem7);
        tSemaine->setObjectName(QStringLiteral("tSemaine"));
        tSemaine->setGeometry(QRect(0, 100, 581, 241));
        tSemaine->setAutoFillBackground(true);
        bImport = new QPushButton(FenAgenda);
        bImport->setObjectName(QStringLiteral("bImport"));
        bImport->setGeometry(QRect(10, 370, 81, 31));
        bExport = new QPushButton(FenAgenda);
        bExport->setObjectName(QStringLiteral("bExport"));
        bExport->setGeometry(QRect(100, 370, 81, 31));
        pushButton = new QPushButton(FenAgenda);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(410, 370, 151, 31));

        retranslateUi(FenAgenda);

        QMetaObject::connectSlotsByName(FenAgenda);
    } // setupUi

    void retranslateUi(QWidget *FenAgenda)
    {
        FenAgenda->setWindowTitle(QApplication::translate("FenAgenda", "Agenda - Semainier", 0));
        labelSemaine->setText(QApplication::translate("FenAgenda", "TextLabel", 0));
        bSemaineSuiv->setText(QApplication::translate("FenAgenda", "Semaine\n"
"Suivante", 0));
        bSemainePrec->setText(QApplication::translate("FenAgenda", "Semaine\n"
"Precedante", 0));
        bGoProjets->setText(QApplication::translate("FenAgenda", "Passer en\n"
" vision Projets", 0));
        QTableWidgetItem *___qtablewidgetitem = tSemaine->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FenAgenda", "Planing", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tSemaine->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("FenAgenda", "Lundi", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tSemaine->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("FenAgenda", "Mardi", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tSemaine->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("FenAgenda", "Mercredi", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tSemaine->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("FenAgenda", "Jeudi", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tSemaine->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("FenAgenda", "Vendredi", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tSemaine->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("FenAgenda", "Samedi", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tSemaine->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("FenAgenda", "Dimanche", 0));
        bImport->setText(QApplication::translate("FenAgenda", "Importer\n"
"Semaine", 0));
        bExport->setText(QApplication::translate("FenAgenda", "Exporter\n"
"Semaine", 0));
        pushButton->setText(QApplication::translate("FenAgenda", "Programmer un \303\251v\303\250nement", 0));
    } // retranslateUi

};

namespace Ui {
    class FenAgenda: public Ui_FenAgenda {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREPRINCIPAL_H
