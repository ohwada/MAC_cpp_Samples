# Python: Qt QStyle Icons
# 2025-04-10  K.OHWADA

# https://unpyside.com/blog/2017/10/16/maya_pyside_standardicon/

from PyQt5.QtGui import*
from PyQt5.QtCore import*
from PyQt5.QtWidgets import*
import sys

# Window
WIN_TITLE = "PyQt5 QStyle Icons"
PX = 50
PY = 50
WIDTH = 640
HEIGHT = 480


STYLES = [ QStyle.SP_TitleBarMinButton, QStyle.SP_TitleBarMenuButton,
QStyle.SP_TitleBarMaxButton, QStyle.SP_TitleBarCloseButton, 
QStyle.SP_TitleBarNormalButton, QStyle.SP_TitleBarShadeButton, 
QStyle.SP_TitleBarUnshadeButton, QStyle.SP_TitleBarContextHelpButton,
QStyle.SP_MessageBoxInformation, QStyle.SP_MessageBoxWarning,
QStyle.SP_MessageBoxCritical, QStyle.SP_MessageBoxQuestion,
QStyle.SP_DesktopIcon, QStyle.SP_TrashIcon, QStyle.SP_ComputerIcon, 
QStyle.SP_DriveFDIcon, QStyle.SP_DriveHDIcon, QStyle.SP_DriveCDIcon,
QStyle.SP_DriveDVDIcon, QStyle.SP_DriveNetIcon, QStyle.SP_DirHomeIcon,
QStyle.SP_DirOpenIcon, QStyle.SP_DirClosedIcon, QStyle.SP_DirIcon,
QStyle.SP_DirLinkIcon, QStyle.SP_FileIcon, QStyle.SP_FileLinkIcon,
QStyle.SP_FileDialogStart, QStyle.SP_FileDialogEnd,
QStyle.SP_FileDialogToParent, QStyle.SP_FileDialogNewFolder,
QStyle.SP_FileDialogDetailedView, QStyle.SP_FileDialogInfoView,
QStyle.SP_FileDialogContentsView, QStyle.SP_FileDialogListView,
QStyle.SP_FileDialogBack, QStyle.SP_DockWidgetCloseButton,
QStyle.SP_ToolBarHorizontalExtensionButton,
QStyle.SP_ToolBarVerticalExtensionButton,
QStyle.SP_DialogOkButton, QStyle.SP_DialogCancelButton,
QStyle.SP_DialogHelpButton, QStyle.SP_DialogOpenButton,
QStyle.SP_DialogSaveButton, QStyle.SP_DialogCloseButton,
QStyle.SP_DialogApplyButton, QStyle.SP_DialogResetButton,
QStyle.SP_DialogDiscardButton, QStyle.SP_DialogYesButton,
QStyle.SP_DialogNoButton, QStyle.SP_ArrowUp, QStyle.SP_ArrowDown,
QStyle.SP_ArrowLeft, QStyle.SP_ArrowRight, QStyle.SP_ArrowBack,
QStyle.SP_ArrowForward, QStyle.SP_CommandLink, QStyle.SP_VistaShield,
QStyle.SP_BrowserReload, QStyle.SP_BrowserStop, QStyle.SP_MediaPlay,
QStyle.SP_MediaStop, QStyle.SP_MediaPause, QStyle.SP_MediaSkipForward,
QStyle.SP_MediaSkipBackward, QStyle.SP_MediaSeekForward,
QStyle.SP_MediaSeekBackward, QStyle.SP_MediaVolume, QStyle.SP_MediaVolumeMuted ]

STYLES_TEXT = [ "SP_TitleBarMinButton", "SP_TitleBarMenuButton",
"SP_TitleBarMaxButton", "SP_TitleBarCloseButton",
"SP_TitleBarNormalButton", "SP_TitleBarShadeButton",
"SP_TitleBarUnshadeButton", "SP_TitleBarContextHelpButton",
"SP_MessageBoxInformation", "SP_MessageBoxWarning",
"SP_MessageBoxCritical", "SP_MessageBoxQuestion",
"SP_DesktopIcon", "SP_TrashIcon", "SP_ComputerIcon",
"SP_DriveFDIcon", "SP_DriveHDIcon",
"SP_DriveCDIcon", "SP_DriveDVDIcon", "SP_DriveNetIcon",
"SP_DirHomeIcon", "SP_DirOpenIcon",
"SP_DirClosedIcon", "SP_DirIcon", "SP_DirLinkIcon",
"SP_FileIcon", "SP_FileLinkIcon", 
"SP_FileDialogStart", "SP_FileDialogEnd",
"SP_FileDialogToParent", "SP_FileDialogNewFolder",
"SP_FileDialogDetailedView", "SP_FileDialogInfoView",
"SP_FileDialogContentsView",
"SP_FileDialogListView", "SP_FileDialogBack",
"SP_DockWidgetCloseButton",
"SP_ToolBarHorizontalExtensionButton", "SP_ToolBarVerticalExtensionButton",
"SP_DialogOkButton", "SP_DialogCancelButton", "SP_DialogHelpButton",
"SP_DialogOpenButton", "SP_DialogSaveButton", "SP_DialogCloseButton",
"SP_DialogApplyButton", "SP_DialogResetButton", "SP_DialogDiscardButton",
"SP_DialogYesButton", "SP_DialogNoButton",
"SP_ArrowUp", "SP_ArrowDown", "SP_ArrowLeft", "SP_ArrowRight",
"SP_ArrowBack", "SP_ArrowForward",
"SP_CommandLink", "SP_VistaShield", "SP_BrowserReload", "SP_BrowserStop",
"SP_MediaPlay", "SP_MediaStop", "SP_MediaPause", "SP_MediaSkipForward",
"SP_MediaSkipBackward", "SP_MediaSeekForward", "SP_MediaSeekBackward",
"SP_MediaVolume", "SP_MediaVolumeMuted" ]


class Window(QWidget):
    def __init__(self):
        super(Window, self).__init__()
        self.initUI()
        self.initButtons()
# end

    def initUI(self):
        style = self.style()
        icon = style.standardIcon(QStyle.SP_TitleBarMenuButton)
        tray = QSystemTrayIcon()
        tray.setIcon(QIcon(icon))
        tray.setVisible(True)
        self.setWindowIcon(QIcon(icon))
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
# end

    def initButtons(self):
        len_styles = len(STYLES)
        btns = [QToolButton(self) for i in range(len_styles)]
        layout = QGridLayout()
        j = 0
        k = 0
        style = self.style()
        for i in range(len_styles):
            btns[i].setText("%s" % (STYLES_TEXT[i]))
            btns[i].setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
            icon = style.standardIcon(STYLES[i])
            btns[i].setIcon(QIcon(icon))
            layout.addWidget(btns[i], j, k)
            if i == 0:
                pass
            elif 0 == i % 5:
                j += 1
                k = 0
            else:
                k += 1
# for end
        self.setLayout(layout)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    app.exec_()
# end

if __name__ == '__main__':
    main()
# end

