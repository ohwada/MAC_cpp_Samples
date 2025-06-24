# https://github.com/baoboa/pyqt5/blob/master/examples/multimediawidgets/videowidget.py
# Copyright (C) 2013 Riverbank Computing Limited.
# Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
# PyQt5 Video Player
# choice audio file using QFileDialog
 # load audio file using QMediaPlayer
 # show video using QVideoWidget
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtCore import *
from PyQt5.QtMultimedia import *
from PyQt5.QtMultimediaWidgets import *
from PyQt5.QtWidgets import *
import sys, os


# Window
WIN_TITLE ="pyQt5 Video Player"
PX=50
PY=50
WIDTH = 640
HEIGHT = 480

OPEN = "Open..."
OPEN_MOVIE =  "Open Movie"

EMPTY = ''

ERROR_LABEL_STYLE ="QLabel { color : red;}"

ERROR_FORMAT  = "Error: {:s} : {:s}" 

NOT_AVAILABLE_FORMAT = "Video Not Available: {:s}"

class Window(QMainWindow):
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.initPlayer()
        self.initUI()
# end

    def initPlayer(self):
        self.videoWidget = QVideoWidget()
        self.player = QMediaPlayer(None, QMediaPlayer.VideoSurface)
        self.player.setVideoOutput(self.videoWidget)
        self.player.stateChanged.connect(self.mediaStateChanged)
        self.player.positionChanged.connect(self.positionChanged)
        self.player.durationChanged.connect(self.durationChanged)
        self.player.error.connect(self.handleError)
# end

    def initUI(self):
# Btton Slider Label
        openButton = QPushButton(OPEN)
        openButton.clicked.connect(self.openFile)
        self.playButton = QPushButton()
        self.playButton.setEnabled(False)
        self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))
        self.playButton.clicked.connect(self.play)
        self.positionSlider = QSlider(Qt.Horizontal)
        self.positionSlider.setRange(0, 0)
        self.positionSlider.sliderMoved.connect(self.setPosition)
        self.errorLabel = QLabel()
        self.errorLabel.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        self.errorLabel.setStyleSheet(ERROR_LABEL_STYLE)

# HBoxLayout
        controlLayout = QHBoxLayout()
        controlLayout.setContentsMargins(0, 0, 0, 0)
        controlLayout.addWidget(openButton)
        controlLayout.addWidget(self.playButton)
        controlLayout.addWidget(self.positionSlider)

# VBoxLayout
        layout = QVBoxLayout()
        layout.addWidget(self.videoWidget)
        layout.addLayout(controlLayout)
        layout.addWidget(self.errorLabel)

# CentralWidget
        widet = QWidget(self)
        widet.setLayout(layout)
        self.setCentralWidget(widet)
# end

    def openFile(self):
        self.errorLabel.setText(EMPTY)
        fileName, selectedFilter = QFileDialog.getOpenFileName(self, OPEN_MOVIE, QDir.homePath())
        if fileName != EMPTY:
            print('fileName: ', fileName)
            print('selectedFilter: ', selectedFilter)
            media = QMediaContent(QUrl.fromLocalFile(fileName))
            self.player.setMedia(media)
            self.playButton.setEnabled(True)
            self.basename= os.path.basename(fileName)
            self.setWindowTitle(self.basename)
# end

    def play(self):
        if not self.player.isVideoAvailable():
            text = NOT_AVAILABLE_FORMAT.format(  self.basename )
            print(text)
            self.errorLabel.setText(text)
            return
# end
        if self.player.state() == QMediaPlayer.PlayingState:
            self.player.pause()
        else:
            self.player.play()
# end

    def mediaStateChanged(self, state):
        if self.player.state() == QMediaPlayer.PlayingState:
            self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPause))
        else:
            self.playButton.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))
# end

    def positionChanged(self, position):
        self.positionSlider.setValue(position)
# end

    def durationChanged(self, duration):
        sec =  float(duration)/1000
        print('duration: ', sec ,' sec')
        self.positionSlider.setRange(0, duration)
# end

    def setPosition(self, position):
        self.player.setPosition(position)
# end

    def handleError(self):
        self.playButton.setEnabled(False)
        text = ERROR_FORMAT.format(self.player.errorString(), self.basename)
        print(text)
        self.errorLabel.setText(text)
# end


def main():
    app = QApplication(sys.argv)
    win =  Window()
    win.show()
    sys.exit(app.exec_())
# end


if __name__ == '__main__':
    main()
# end