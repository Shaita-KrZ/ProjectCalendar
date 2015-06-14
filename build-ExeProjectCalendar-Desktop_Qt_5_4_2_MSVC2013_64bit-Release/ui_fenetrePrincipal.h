/********************************************************************************
** Form generated from reading UI file 'fenetrePrincipal.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETREPRINCIPAL_H
#define UI_FENETREPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenAgenda
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelSemaine;
    QPushButton *bSemaineSuiv;
    QTableWidget *tSemaine;
    QPushButton *bProgrammer;
    QPushButton *bGoProjets;
    QPushButton *bImport;
    QPushButton *bExport;
    QPushButton *bSemainePrec;

    void setupUi(QWidget *FenAgenda)
    {
        if (FenAgenda->objectName().isEmpty())
            FenAgenda->setObjectName(QStringLiteral("FenAgenda"));
        FenAgenda->resize(876, 347);
        gridLayout_2 = new QGridLayout(FenAgenda);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        labelSemaine = new QLabel(FenAgenda);
        labelSemaine->setObjectName(QStringLiteral("labelSemaine"));
        labelSemaine->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelSemaine, 1, 4, 1, 1);

        bSemaineSuiv = new QPushButton(FenAgenda);
        bSemaineSuiv->setObjectName(QStringLiteral("bSemaineSuiv"));

        gridLayout_2->addWidget(bSemaineSuiv, 1, 5, 1, 1);

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
        tSemaine->setMinimumSize(QSize(0, 241));
        tSemaine->setAutoFillBackground(true);
        tSemaine->setDragEnabled(true);
        tSemaine->setAlternatingRowColors(true);
        tSemaine->setShowGrid(true);

        gridLayout_2->addWidget(tSemaine, 2, 0, 1, 6);

        bProgrammer = new QPushButton(FenAgenda);
        bProgrammer->setObjectName(QStringLiteral("bProgrammer"));

        gridLayout_2->addWidget(bProgrammer, 3, 4, 1, 2);

        bGoProjets = new QPushButton(FenAgenda);
        bGoProjets->setObjectName(QStringLiteral("bGoProjets"));

        gridLayout_2->addWidget(bGoProjets, 1, 0, 1, 1);

        bImport = new QPushButton(FenAgenda);
        bImport->setObjectName(QStringLiteral("bImport"));

        gridLayout_2->addWidget(bImport, 3, 0, 1, 1);

        bExport = new QPushButton(FenAgenda);
        bExport->setObjectName(QStringLiteral("bExport"));

        gridLayout_2->addWidget(bExport, 3, 1, 1, 1);

        bSemainePrec = new QPushButton(FenAgenda);
        bSemainePrec->setObjectName(QStringLiteral("bSemainePrec"));

        gridLayout_2->addWidget(bSemainePrec, 1, 3, 1, 1);


        retranslateUi(FenAgenda);

        QMetaObject::connectSlotsByName(FenAgenda);
    } // setupUi

    void retranslateUi(QWidget *FenAgenda)
    {
        FenAgenda->setWindowTitle(QApplication::translate("FenAgenda", "Agenda - Semainier", 0));
        labelSemaine->setText(QApplication::translate("FenAgenda", "TextLabel", 0));
        bSemaineSuiv->setText(QApplication::translate("FenAgenda", "Semaine\n"
"Suivante", 0));
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
        bProgrammer->setText(QApplication::translate("FenAgenda", "Programmer un \303\251v\303\250nement", 0));
        bGoProjets->setText(QApplication::translate("FenAgenda", "Passer en\n"
" vision Projets", 0));
        bImport->setText(QApplication::translate("FenAgenda", "Importer\n"
"Semaine", 0));
        bExport->setText(QApplication::translate("FenAgenda", "Exporter\n"
"Semaine", 0));
        bSemainePrec->setText(QApplication::translate("FenAgenda", "Semaine\n"
"Precedante", 0));
    } // retranslateUi

};

namespace Ui {
    class FenAgenda: public Ui_FenAgenda {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETREPRINCIPAL_H
