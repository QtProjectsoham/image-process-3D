/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_YZ;
    QPushButton *loadimage;
    QLabel *label_imagename;
    QLabel *label;
    QLabel *xdimension;
    QLabel *label_2;
    QLabel *ydimension;
    QLabel *label_4;
    QLabel *zdimension;
    QSlider *slider_x;
    QLabel *label_3;
    QLabel *label_5;
    QSlider *slider_y;
    QLabel *label_6;
    QSlider *slider_z;
    QSpinBox *spinBox_x;
    QSpinBox *spinBox_y;
    QSpinBox *spinBox_z;
    QPushButton *binarize;
    QPushButton *DT;
    QPushButton *histogram_equilization;
    QPushButton *ccl;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_XY;
    QLabel *label_XZ;
    QLabel *ipfilename;
    QLabel *label_7;
    QLabel *nocc;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 674);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_YZ = new QLabel(centralWidget);
        label_YZ->setObjectName(QStringLiteral("label_YZ"));
        label_YZ->setGeometry(QRect(410, 330, 391, 291));
        label_YZ->setScaledContents(true);
        loadimage = new QPushButton(centralWidget);
        loadimage->setObjectName(QStringLiteral("loadimage"));
        loadimage->setGeometry(QRect(810, 0, 101, 51));
        label_imagename = new QLabel(centralWidget);
        label_imagename->setObjectName(QStringLiteral("label_imagename"));
        label_imagename->setGeometry(QRect(900, 10, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(920, 0, 21, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        xdimension = new QLabel(centralWidget);
        xdimension->setObjectName(QStringLiteral("xdimension"));
        xdimension->setGeometry(QRect(950, 0, 31, 51));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(990, 0, 21, 51));
        label_2->setFont(font);
        ydimension = new QLabel(centralWidget);
        ydimension->setObjectName(QStringLiteral("ydimension"));
        ydimension->setGeometry(QRect(1020, 0, 41, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1060, 0, 21, 51));
        label_4->setFont(font);
        zdimension = new QLabel(centralWidget);
        zdimension->setObjectName(QStringLiteral("zdimension"));
        zdimension->setGeometry(QRect(1090, 10, 51, 31));
        slider_x = new QSlider(centralWidget);
        slider_x->setObjectName(QStringLiteral("slider_x"));
        slider_x->setGeometry(QRect(870, 120, 221, 22));
        slider_x->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(840, 110, 21, 51));
        label_3->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(840, 140, 21, 51));
        label_5->setFont(font);
        slider_y = new QSlider(centralWidget);
        slider_y->setObjectName(QStringLiteral("slider_y"));
        slider_y->setGeometry(QRect(870, 150, 211, 22));
        slider_y->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(840, 170, 21, 41));
        label_6->setFont(font);
        slider_z = new QSlider(centralWidget);
        slider_z->setObjectName(QStringLiteral("slider_z"));
        slider_z->setGeometry(QRect(870, 180, 211, 22));
        slider_z->setOrientation(Qt::Horizontal);
        spinBox_x = new QSpinBox(centralWidget);
        spinBox_x->setObjectName(QStringLiteral("spinBox_x"));
        spinBox_x->setGeometry(QRect(1100, 120, 42, 22));
        spinBox_y = new QSpinBox(centralWidget);
        spinBox_y->setObjectName(QStringLiteral("spinBox_y"));
        spinBox_y->setGeometry(QRect(1100, 150, 42, 22));
        spinBox_z = new QSpinBox(centralWidget);
        spinBox_z->setObjectName(QStringLiteral("spinBox_z"));
        spinBox_z->setGeometry(QRect(1100, 180, 42, 22));
        binarize = new QPushButton(centralWidget);
        binarize->setObjectName(QStringLiteral("binarize"));
        binarize->setGeometry(QRect(840, 220, 71, 41));
        DT = new QPushButton(centralWidget);
        DT->setObjectName(QStringLiteral("DT"));
        DT->setGeometry(QRect(920, 220, 81, 41));
        histogram_equilization = new QPushButton(centralWidget);
        histogram_equilization->setObjectName(QStringLiteral("histogram_equilization"));
        histogram_equilization->setGeometry(QRect(1010, 220, 121, 41));
        ccl = new QPushButton(centralWidget);
        ccl->setObjectName(QStringLiteral("ccl"));
        ccl->setGeometry(QRect(840, 270, 81, 31));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 391, 311));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_XY = new QLabel(layoutWidget);
        label_XY->setObjectName(QStringLiteral("label_XY"));
        label_XY->setScaledContents(true);

        horizontalLayout->addWidget(label_XY);

        label_XZ = new QLabel(centralWidget);
        label_XZ->setObjectName(QStringLiteral("label_XZ"));
        label_XZ->setGeometry(QRect(410, 10, 391, 311));
        label_XZ->setScaledContents(true);
        ipfilename = new QLabel(centralWidget);
        ipfilename->setObjectName(QStringLiteral("ipfilename"));
        ipfilename->setGeometry(QRect(810, 60, 331, 41));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(850, 310, 101, 31));
        nocc = new QLabel(centralWidget);
        nocc->setObjectName(QStringLiteral("nocc"));
        nocc->setGeometry(QRect(950, 315, 61, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1148, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(slider_x, SIGNAL(valueChanged(int)), spinBox_x, SLOT(setValue(int)));
        QObject::connect(slider_y, SIGNAL(valueChanged(int)), spinBox_y, SLOT(setValue(int)));
        QObject::connect(slider_z, SIGNAL(valueChanged(int)), spinBox_z, SLOT(setValue(int)));
        QObject::connect(spinBox_x, SIGNAL(valueChanged(int)), slider_x, SLOT(setValue(int)));
        QObject::connect(spinBox_y, SIGNAL(valueChanged(int)), slider_y, SLOT(setValue(int)));
        QObject::connect(spinBox_z, SIGNAL(valueChanged(int)), slider_z, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_YZ->setText(QString());
        loadimage->setText(QApplication::translate("MainWindow", "Load Image", 0));
        label_imagename->setText(QString());
        label->setText(QApplication::translate("MainWindow", "X", 0));
        xdimension->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Y", 0));
        ydimension->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Z", 0));
        zdimension->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "X", 0));
        label_5->setText(QApplication::translate("MainWindow", "Y", 0));
        label_6->setText(QApplication::translate("MainWindow", "Z", 0));
        binarize->setText(QApplication::translate("MainWindow", "Binarize", 0));
        DT->setText(QApplication::translate("MainWindow", "DT", 0));
        histogram_equilization->setText(QApplication::translate("MainWindow", "Histogram Equilization", 0));
        ccl->setText(QApplication::translate("MainWindow", "CCL", 0));
        label_XY->setText(QString());
        label_XZ->setText(QString());
        ipfilename->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "No. of components", 0));
        nocc->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
