from PySide6.QtWidgets import QApplication, QDialog
from PySide6.QtCore import QFile, QIODevice, QTimer,QDateTime
from PySide6 import QtWidgets
from PySide6 import QtCore, QtGui, QtUiTools
from pyside_dynamic import *
import sys
import os 
import signal

class DMM_GUI(QDialog):

    def __init__(self):
        super(DMM_GUI, self).__init__()
        print(os.path.dirname(os.path.realpath(__file__)))
        loadUi("./../../../GUI/UI/dmm.ui", self)

        self.TopButtonMenu.StandardMenu.MenuHomeButton.clicked.connect(self.__HomeButtonPressed())

    def __HomeButtonPressed(self):
        #self.setCurrentIndex(widget.currentIndex() - 1)
        self.DMMPages.SetCurrentIndex(self.DMMPages.indexOf(self.DMMPages.DrinkConfigPage))
    
    def __ConfigurationButtonPressed(self):
        self.DMMPages.SetCurrentIndex(self.DMMPages.indexOf(self.DMMPages.ConfigGlassPage))




if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(True)
    gui = DMM_GUI()

    gui.show()
    
    sys.exit(app.exec())
    app.exec_()
