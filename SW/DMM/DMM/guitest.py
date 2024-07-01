import sys
import os 
import signal

def signal_handler(signal, frame):
        print('You pressed Ctrl+C!')
        sys.exit(0)
        QApplication.quit()

from PySide6.QtWidgets import QApplication, QDialog
from PySide6.QtCore import QFile, QIODevice, QTimer,QDateTime
from PySide6 import QtWidgets
from PySide6 import QtCore, QtGui, QtUiTools
from pyside_dynamic import *


class Screen1(QDialog):
    def __init__(self):
        super(Screen1, self).__init__()
        print(os.path.dirname(os.path.realpath(__file__)))
        loadUi("./../../../GUI/UI/screen1.ui", self)

        self.pushButton.clicked.connect(self.gotoscreen2)

        self.timer=QTimer()
        self.timer.timeout.connect(self.testloop)
        self.timer.start(1000)
    
    def gotoscreen2(self):
        widget.setCurrentIndex(widget.currentIndex() + 1)
    
    def testloop(self):
        print("Hello wolrd 1")
        
class Screen2(QDialog):
    def __init__(self):
        super(Screen2, self).__init__()
        loadUi("./../../../GUI/UI/screen2.ui", self)

        self.pushButton.clicked.connect(self.gotoscreen1)
    
    def gotoscreen1(self):
        widget.setCurrentIndex(widget.currentIndex() - 1)
        #widget.setCurrentWidget(Screen1Obj) # <------


if __name__ == "__main__":
    # ---- load ui file -----
    #app = QApplication(sys.argv)
    #print(os.path.dirname(os.path.realpath(__file__)))
    #ui_file_name = "../../GUI/UI/screen1.ui"
    #ui_file = QFile(ui_file_name)
    #if not ui_file.open(QIODevice.ReadOnly):
    #    print(f"Cannot open {ui_file_name}: {ui_file.errorString()}")
    #    sys.exit(-1)
    #loader = QUiLoader()
    #window = loader.load(ui_file)
    #ui_file.close()
    #if not window:
    #    print(loader.errorString())
    #    sys.exit(-1)
    #window.show()
    #sys.exit(app.exec())
    
    from HX711 import *

    # create a SimpleHX711 object using GPIO pin 2 as the data pin,
    # GPIO pin 3 as the clock pin, -370 as the reference unit, and
    # -367471 as the offset
    clock_pin = 17
    dt_pin = 18
    with SimpleHX711(dt_pin, clock_pin, -370, -367471) as hx:

      # set the scale to output weights in ounces
      hx.setUnit(Mass.Unit.OZ)

      # zero the scale
      hx.zero()

      # constantly output weights using the median of 35 samples
      while True:
        print(hx.weight(35)) #eg. 1.08 oz
    
    signal.signal(signal.SIGINT, signal_handler)
    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(True)
    
    widget = QtWidgets.QStackedWidget() # a stack of widgets

    widget.setFixedWidth(800)
    widget.setFixedHeight(600)

    Screen1Obj = Screen1()
    Screen2Obj = Screen2()

    widget.addWidget(Screen1Obj)
    widget.addWidget(Screen2Obj)

    widget.setFixedHeight(300)
    widget.setFixedWidth(400)

    print("index of 2nd widget is=", widget.indexOf(Screen1Obj))

    #widget.showFullScreen()
    widget.show()
    
    sys.exit(app.exec())
    app.exec_()



    #{your QPushButton}.clicked.connect(lambda: {your QStackedWidget}.setCurrentIndex({another page}))