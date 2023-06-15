# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindow.ui'
##
## Created by: Qt User Interface Compiler version 6.4.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QAbstractItemView, QApplication, QFormLayout, QGroupBox,
    QHBoxLayout, QHeaderView, QLabel, QLayout,
    QLineEdit, QMainWindow, QMenuBar, QPushButton,
    QSizePolicy, QStatusBar, QTableWidget, QTableWidgetItem,
    QVBoxLayout, QWidget)

from mplwidget import MplWidget

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(918, 575)
        icon = QIcon()
        iconThemeName = u"applications-development"
        if QIcon.hasThemeIcon(iconThemeName):
            icon = QIcon.fromTheme(iconThemeName)
        else:
            icon.addFile(u".", QSize(), QIcon.Normal, QIcon.Off)

        MainWindow.setWindowIcon(icon)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout = QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.widget = QWidget(self.centralwidget)
        self.widget.setObjectName(u"widget")
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widget.sizePolicy().hasHeightForWidth())
        self.widget.setSizePolicy(sizePolicy)
        self.horizontalLayout = QHBoxLayout(self.widget)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.groupBox_2 = QGroupBox(self.widget)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setEnabled(True)
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy1)
        self.groupBox_2.setLayoutDirection(Qt.LeftToRight)
        self.groupBox_2.setAutoFillBackground(False)
        self.groupBox_2.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.groupBox_2.setFlat(False)
        self.groupBox_2.setCheckable(False)
        self.horizontalLayout_3 = QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.horizontalLayout_3.setContentsMargins(9, 9, -1, -1)
        self.labelImgRef = QLabel(self.groupBox_2)
        self.labelImgRef.setObjectName(u"labelImgRef")
        sizePolicy2 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.labelImgRef.sizePolicy().hasHeightForWidth())
        self.labelImgRef.setSizePolicy(sizePolicy2)
        self.labelImgRef.setMaximumSize(QSize(300, 100))
        self.labelImgRef.setPixmap(QPixmap(u"resources/img.png"))
        self.labelImgRef.setScaledContents(True)
        self.labelImgRef.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)

        self.horizontalLayout_3.addWidget(self.labelImgRef)

        self.label_3 = QLabel(self.groupBox_2)
        self.label_3.setObjectName(u"label_3")
        sizePolicy3 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_3.sizePolicy().hasHeightForWidth())
        self.label_3.setSizePolicy(sizePolicy3)
        self.label_3.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.label_3.setWordWrap(True)

        self.horizontalLayout_3.addWidget(self.label_3)


        self.horizontalLayout.addWidget(self.groupBox_2)

        self.groupBox = QGroupBox(self.widget)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy3.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy3)
        self.groupBox.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.formLayout = QFormLayout(self.groupBox)
        self.formLayout.setObjectName(u"formLayout")
        self.formLayout.setHorizontalSpacing(2)
        self.formLayout.setVerticalSpacing(6)
        self.label = QLabel(self.groupBox)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.label)

        self.lineEditN = QLineEdit(self.groupBox)
        self.lineEditN.setObjectName(u"lineEditN")

        self.formLayout.setWidget(0, QFormLayout.FieldRole, self.lineEditN)

        self.label_2 = QLabel(self.groupBox)
        self.label_2.setObjectName(u"label_2")

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.label_2)

        self.lineEditM = QLineEdit(self.groupBox)
        self.lineEditM.setObjectName(u"lineEditM")

        self.formLayout.setWidget(1, QFormLayout.FieldRole, self.lineEditM)

        self.pushButtonRun = QPushButton(self.groupBox)
        self.pushButtonRun.setObjectName(u"pushButtonRun")

        self.formLayout.setWidget(2, QFormLayout.SpanningRole, self.pushButtonRun)


        self.horizontalLayout.addWidget(self.groupBox)

        self.groupBox_3 = QGroupBox(self.widget)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.groupBox_3.setEnabled(True)
        sizePolicy1.setHeightForWidth(self.groupBox_3.sizePolicy().hasHeightForWidth())
        self.groupBox_3.setSizePolicy(sizePolicy1)
        self.groupBox_3.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.horizontalLayout_4 = QHBoxLayout(self.groupBox_3)
        self.horizontalLayout_4.setSpacing(10)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(9, 0, 9, -1)
        self.labelRes = QLabel(self.groupBox_3)
        self.labelRes.setObjectName(u"labelRes")
        sizePolicy4 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.labelRes.sizePolicy().hasHeightForWidth())
        self.labelRes.setSizePolicy(sizePolicy4)
        self.labelRes.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.labelRes.setWordWrap(True)

        self.horizontalLayout_4.addWidget(self.labelRes)

        self.labelResX = QLabel(self.groupBox_3)
        self.labelResX.setObjectName(u"labelResX")
        sizePolicy4.setHeightForWidth(self.labelResX.sizePolicy().hasHeightForWidth())
        self.labelResX.setSizePolicy(sizePolicy4)
        self.labelResX.setScaledContents(False)
        self.labelResX.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.labelResX.setWordWrap(True)

        self.horizontalLayout_4.addWidget(self.labelResX)

        self.labelResT = QLabel(self.groupBox_3)
        self.labelResT.setObjectName(u"labelResT")
        sizePolicy4.setHeightForWidth(self.labelResT.sizePolicy().hasHeightForWidth())
        self.labelResT.setSizePolicy(sizePolicy4)
        self.labelResT.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.labelResT.setWordWrap(True)

        self.horizontalLayout_4.addWidget(self.labelResT)

        self.horizontalLayout_4.setStretch(0, 30)
        self.horizontalLayout_4.setStretch(1, 35)
        self.horizontalLayout_4.setStretch(2, 35)

        self.horizontalLayout.addWidget(self.groupBox_3)


        self.verticalLayout.addWidget(self.widget)

        self.widget_2 = QWidget(self.centralwidget)
        self.widget_2.setObjectName(u"widget_2")
        self.widget_2.setEnabled(True)
        sizePolicy4.setHeightForWidth(self.widget_2.sizePolicy().hasHeightForWidth())
        self.widget_2.setSizePolicy(sizePolicy4)
        self.horizontalLayout_2 = QHBoxLayout(self.widget_2)
        self.horizontalLayout_2.setSpacing(0)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.tableWidget = QTableWidget(self.widget_2)
        self.tableWidget.setObjectName(u"tableWidget")
        font = QFont()
        font.setPointSize(9)
        self.tableWidget.setFont(font)
        self.tableWidget.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.tableWidget.setAlternatingRowColors(True)

        self.horizontalLayout_2.addWidget(self.tableWidget)

        self.graph = MplWidget(self.widget_2)
        self.graph.setObjectName(u"graph")

        self.horizontalLayout_2.addWidget(self.graph)

        self.horizontalLayout_2.setStretch(0, 30)
        self.horizontalLayout_2.setStretch(1, 30)

        self.verticalLayout.addWidget(self.widget_2)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 918, 22))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"\"\u041d\u0435\u0441\u0442\u0430\u0446\u0438\u043e\u043d\u0430\u0440\u043d\u043e\u0435 \u0443\u0440\u0430\u0432\u043d\u0435\u043d\u0438\u0435 \u0442\u0435\u043f\u043b\u043e\u043f\u0440\u043e\u0432\u043e\u0434\u043d\u043e\u0441\u0442\u0438\", \u0417\u043e\u0440\u0438\u043d \u041e.\u0410., 382003_3", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("MainWindow", u"\u0421\u043f\u0440\u0430\u0432\u043a\u0430 \u043f\u043e \u0437\u0430\u0434\u0430\u0447\u0435", None))
        self.labelImgRef.setText("")
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"u(x;t) - \u0442\u0435\u043c\u043f\u0435\u0440\u0430\u0442\u0443\u0440\u0430 \u0441\u0442\u0435\u0440\u0436\u043d\u044f \u0432 \u0442\u043e\u0447\u043a\u0435\n"
"x (\u043f\u043e\u043f\u0435\u0440\u0435\u0447\u043d\u043e\u043c \u0441\u0435\u0447\u0435\u043d\u0438\u0435 \u0441\u0442\u0435\u0440\u0436\u043d\u044f)\n"
"\u0432 \u043c\u043e\u043c\u0435\u043d\u0442 \u0432\u0440\u0435\u043c\u0435\u043d\u0438 t\n"
"u(x;t) - ?", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"\u041f\u0430\u0440\u0430\u043c\u0435\u0442\u0440\u044b \u0441\u0447\u0451\u0442\u0430", None))
#if QT_CONFIG(tooltip)
        self.label.setToolTip(QCoreApplication.translate("MainWindow", u"\u0427\u0438\u0441\u043b\u043e \u0440\u0430\u0437\u0431\u0438\u0435\u043d\u0438\u0439 \u043f\u043e x\n"
"(\u043f\u043e\u043f\u0435\u0440\u0435\u0447\u043d\u043e\u043c\u0443 \u0441\u0435\u0447\u0435\u043d\u0438\u044e \u0441\u0442\u0435\u0440\u0436\u043d\u044f)", None))
#endif // QT_CONFIG(tooltip)
        self.label.setText(QCoreApplication.translate("MainWindow", u"n =", None))
#if QT_CONFIG(statustip)
        self.lineEditN.setStatusTip(QCoreApplication.translate("MainWindow", u"\u0412\u0432\u043e\u0434 \u0447\u0438\u0441\u043b\u0430 \u0440\u0430\u0437\u0431\u0438\u0435\u043d\u0438\u0439 \u043f\u043e x (\u043f\u043e\u043f\u0435\u0440\u0435\u0447\u043d\u043e\u043c\u0443 \u0441\u0435\u0447\u0435\u043d\u0438\u044e \u0441\u0442\u0435\u0440\u0436\u043d\u044f)", None))
#endif // QT_CONFIG(statustip)
        self.lineEditN.setText(QCoreApplication.translate("MainWindow", u"100", None))
#if QT_CONFIG(tooltip)
        self.label_2.setToolTip(QCoreApplication.translate("MainWindow", u"\u0427\u0438\u0441\u043b\u043e \u0440\u0430\u0437\u0431\u0438\u0435\u043d\u0438\u0439 \u043f\u043e t (\u0432\u0440\u0435\u043c\u0435\u043d\u0438)", None))
#endif // QT_CONFIG(tooltip)
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"m =", None))
#if QT_CONFIG(statustip)
        self.lineEditM.setStatusTip(QCoreApplication.translate("MainWindow", u"\u0412\u0432\u043e\u0434 \u0447\u0438\u0441\u043b\u0430 \u0440\u0430\u0437\u0431\u0438\u0435\u043d\u0438\u0439 \u043f\u043e t (\u0432\u0440\u0435\u043c\u0435\u043d\u0438)", None))
#endif // QT_CONFIG(statustip)
        self.lineEditM.setText(QCoreApplication.translate("MainWindow", u"100", None))
#if QT_CONFIG(statustip)
        self.pushButtonRun.setStatusTip(QCoreApplication.translate("MainWindow", u"\u041d\u0430\u0445\u043e\u0436\u0434\u0435\u043d\u0438\u0435 \u0447\u0438\u0441\u043b\u0435\u043d\u043d\u043e\u0433\u043e \u0440\u0435\u0448\u0435\u043d\u0438\u044f V (\u0442\u0435\u043c\u043f\u0435\u0440\u0430\u0442\u0443\u0440\u044b \u0441\u0442\u0435\u0440\u0436\u043d\u044f) \u0432 \u0443\u0437\u043b\u0430\u0445 \u0434\u0432\u0443\u043c\u0435\u0440\u043d\u043e\u0439 \u0441\u0435\u0442\u043a\u0438 (x[i]; t[j]), \u043f\u043e\u0441\u0442\u0440\u043e\u0435\u043d\u0438\u0435 \u0433\u0440\u0430\u0444\u0438\u043a\u0430 \u0442\u0435\u043c\u043f\u0435\u0440\u0430\u0442\u0443\u0440 \u043f\u043e \u044d\u0442\u0438\u043c \u0434\u0430\u043d\u043d\u044b\u043c", None))
#endif // QT_CONFIG(statustip)
        self.pushButtonRun.setText(QCoreApplication.translate("MainWindow", u"\u0412\u044b\u0447\u0438\u0441\u043b\u0438\u0442\u044c", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("MainWindow", u"\u0421\u043f\u0440\u0430\u0432\u043a\u0430 \u043f\u043e \u0440\u0435\u0437\u0443\u043b\u044c\u0442\u0430\u0442\u0430\u043c", None))
        self.labelRes.setText("")
        self.labelResX.setText("")
        self.labelResT.setText("")
#if QT_CONFIG(statustip)
        self.tableWidget.setStatusTip(QCoreApplication.translate("MainWindow", u"\u0422\u0430\u0431\u043b\u0438\u0446\u0430 V(x,t) \u0432 \u0443\u0437\u043b\u0430\u0445 \u0434\u0432\u0443\u043c\u0435\u0440\u043d\u043e\u0439 \u0441\u0435\u0442\u043a\u0438 (x[i]; t[j])", None))
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(statustip)
        self.graph.setStatusTip(QCoreApplication.translate("MainWindow", u"\u0413\u0440\u0430\u0444\u0438\u043a \u0442\u0435\u043c\u043f\u0435\u0440\u0430\u0442\u0443\u0440", None))
#endif // QT_CONFIG(statustip)
    # retranslateUi

