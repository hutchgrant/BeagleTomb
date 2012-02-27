/********************************************************************************
** Form generated from reading UI file 'newplaylist.ui'
**
** Created: Wed Jan 25 22:06:58 2012
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPLAYLIST_H
#define UI_NEWPLAYLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newplaylist
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *PLSTATUS_lbl;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *PLNAME_entry;

    void setupUi(QDialog *newplaylist)
    {
        if (newplaylist->objectName().isEmpty())
            newplaylist->setObjectName(QString::fromUtf8("newplaylist"));
        newplaylist->resize(373, 195);
        buttonBox = new QDialogButtonBox(newplaylist);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 150, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        PLSTATUS_lbl = new QLabel(newplaylist);
        PLSTATUS_lbl->setObjectName(QString::fromUtf8("PLSTATUS_lbl"));
        PLSTATUS_lbl->setGeometry(QRect(90, 110, 211, 17));
        widget = new QWidget(newplaylist);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 351, 50));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        PLNAME_entry = new QLineEdit(widget);
        PLNAME_entry->setObjectName(QString::fromUtf8("PLNAME_entry"));

        verticalLayout->addWidget(PLNAME_entry);


        retranslateUi(newplaylist);
        QObject::connect(buttonBox, SIGNAL(accepted()), newplaylist, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newplaylist, SLOT(reject()));

        QMetaObject::connectSlotsByName(newplaylist);
    } // setupUi

    void retranslateUi(QDialog *newplaylist)
    {
        newplaylist->setWindowTitle(QApplication::translate("newplaylist", "New Playlist", 0, QApplication::UnicodeUTF8));
        PLSTATUS_lbl->setText(QApplication::translate("newplaylist", ".", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("newplaylist", "Enter playlist location and name:", 0, QApplication::UnicodeUTF8));
        PLNAME_entry->setText(QApplication::translate("newplaylist", "~/BeagleTomb/playlist/newplaylist.pl", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newplaylist: public Ui_newplaylist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPLAYLIST_H
