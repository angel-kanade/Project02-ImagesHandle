/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *horizontalGroupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_Load;
    QPushButton *btn_Decompress;
    QPushButton *btn_Compress;
    QPushButton *btn_Gray;
    QPushButton *btn_Save;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lbl_show1;
    QLabel *lbl_show2;
    QLineEdit *led_show1;
    QLineEdit *led_show2;
    QSlider *ResizeSlider;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(712, 461);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalGroupBox = new QGroupBox(centralwidget);
        horizontalGroupBox->setObjectName("horizontalGroupBox");
        horizontalGroupBox->setGeometry(QRect(10, 10, 691, 61));
        horizontalLayout = new QHBoxLayout(horizontalGroupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        btn_Load = new QPushButton(horizontalGroupBox);
        btn_Load->setObjectName("btn_Load");

        horizontalLayout->addWidget(btn_Load);

        btn_Decompress = new QPushButton(horizontalGroupBox);
        btn_Decompress->setObjectName("btn_Decompress");

        horizontalLayout->addWidget(btn_Decompress);

        btn_Compress = new QPushButton(horizontalGroupBox);
        btn_Compress->setObjectName("btn_Compress");

        horizontalLayout->addWidget(btn_Compress);

        btn_Gray = new QPushButton(horizontalGroupBox);
        btn_Gray->setObjectName("btn_Gray");

        horizontalLayout->addWidget(btn_Gray);

        btn_Save = new QPushButton(horizontalGroupBox);
        btn_Save->setObjectName("btn_Save");

        horizontalLayout->addWidget(btn_Save);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 80, 691, 351));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lbl_show1 = new QLabel(layoutWidget);
        lbl_show1->setObjectName("lbl_show1");
        lbl_show1->setEnabled(true);
        lbl_show1->setFrameShape(QFrame::Panel);
        lbl_show1->setFrameShadow(QFrame::Plain);
        lbl_show1->setTextFormat(Qt::AutoText);
        lbl_show1->setScaledContents(false);
        lbl_show1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_show1, 1, 0, 1, 1);

        lbl_show2 = new QLabel(layoutWidget);
        lbl_show2->setObjectName("lbl_show2");
        lbl_show2->setFrameShape(QFrame::Panel);
        lbl_show2->setFrameShadow(QFrame::Plain);
        lbl_show2->setAlignment(Qt::AlignCenter);
        lbl_show2->setWordWrap(false);

        gridLayout->addWidget(lbl_show2, 1, 1, 1, 1);

        led_show1 = new QLineEdit(layoutWidget);
        led_show1->setObjectName("led_show1");
        led_show1->setFrame(true);
        led_show1->setReadOnly(true);

        gridLayout->addWidget(led_show1, 0, 0, 1, 1);

        led_show2 = new QLineEdit(layoutWidget);
        led_show2->setObjectName("led_show2");
        led_show2->setReadOnly(true);

        gridLayout->addWidget(led_show2, 0, 1, 1, 1);

        ResizeSlider = new QSlider(layoutWidget);
        ResizeSlider->setObjectName("ResizeSlider");
        ResizeSlider->setMinimum(1);
        ResizeSlider->setMaximum(200);
        ResizeSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(ResizeSlider, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        horizontalGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206\345\212\237\350\203\275\345\214\272", nullptr));
        btn_Load->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\345\233\276\347\211\207\345\210\260\345\267\246\344\276\247", nullptr));
        btn_Decompress->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213\345\267\246\345\233\276", nullptr));
        btn_Compress->setText(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\345\267\246\345\233\276\345\271\266\344\277\235\345\255\230", nullptr));
        btn_Gray->setText(QCoreApplication::translate("MainWindow", "\347\201\260\345\272\246\345\214\226\345\267\246\345\233\276", nullptr));
        btn_Save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\217\263\345\233\276", nullptr));
        lbl_show1->setText(QString());
        lbl_show2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
