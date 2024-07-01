
# Drink Mixing Machine main python script
# Erik Magnusson July 2024
#
# 
#

from gui import *
from hwio import *

import sys
import os 
import signal

def signal_handler(signal, frame):
        print('You pressed Ctrl+C!')
        sys.exit(0)
        QApplication.quit()

if __name__ == "__main__":
    print("Hello world - main.py")

    signal.signal(signal.SIGINT, signal_handler)
    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(True)

    dmm_gui = DMM_GUI()

    dmm_gui.setFixedHeight(540)
    dmm_gui.setFixedWidth(1024)
    

    #widget.showFullScreen()
    dmm_gui.show()
    
    sys.exit(app.exec())
    app.exec_()

