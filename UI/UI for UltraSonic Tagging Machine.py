import sys
import os
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow

from UI_MainWindow import Ui_MainWindow

root= r'C:\Users\DELL\Projects\GRBL\UI\Designs'
dirlist = [ item for item in os.listdir(root) if os.path.isdir(os.path.join(root, item)) ]
print (dirlist)


class MainWindow:
    def __init__(self):
        self.main_win = QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.main_win)
        self.ui.pushButton.clicked.connect(self.buttonPressed)
    def show(self):
        self.main_win.show()
    def ChangeText(self, text):
        self.ui.label_2.setText(text)
    def AdditemtoComboBox(self,item):
        self.ui.comboBox.addItem(item)
    def buttonPressed(self):
        self.ChangeText("Button Pressed") ##Dummy thing I added
        #this Function is CAlled when the Button is Pressed

if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()

    ##Functions You can Use on the UI
        ##Change the Text Box
    main_win.ChangeText("Changed the Text")

        ##Add item to ComboBox/// Here I have added all the folders
    for items in dirlist:
        main_win.AdditemtoComboBox(items)

        ##What happens when We press the Run Button
                ## TO Change this Change the ButtonPressed Function in the Main_Window class above


    sys.exit(app.exec())
