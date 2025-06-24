# https://github.com/arvind-4/Audio-Player-with-PyQt5/blob/main/main.py
# PyQt5 Audio Player
# choice audio file using QFileDialog
 # load audio file using QMediaPlayer
 # play music using QMediaPlayer
# support mp3
# modify: 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtMultimedia import *
import sys, os, random

# from qtwidgets import EqualizerBar
from equalizer_bar import *

# Window
WIN_TITLE = "Audio Player --Arvind"
PX = 50
PY = 50
WIDTH = 480
HEIGHT = 360

APP_STYLE = "Fusion"

EMPTY = ''

INTERVAL = 100 # msc

MENU_FILE = "&File"
MENU_PREF = "&Preference"

OPEN = "Open"
OPEN_TEXT =  "Open..."
QUIT = "Quit"
QUIT_TEXT =  "Quit..."
PLAY = "Play"
PAUSE ="Pause"
STOP = "Stop"

FPATH_ICON_WIN = "icons/Icon.png"
FPATH_ICON_OPEN = "icons/Open.png"
FPATH_ICON_CLOSE ="icons/Close.png"
FPATH_ICON_PLAY = "icons/Play.png"
FPATH_ICON_PAUSE = "icons/Pause.png"
FPATH_ICON_STOP = "icons/Stop.png"

# Volume
VOL_MIN =1
VOL_MAX = 100
VOL_INIT = 70

 # QFileDialog.getOpenFileName
FILE_FILTER = "Files (*.wav *.mp3)"

ERROR_LABEL_STYLE = "QLabel { color : red;}"

ERROR_FORMAT  = "Error: {:s} : {:s}" 

NOT_AVAILABLE_FORMAT = "Audio Not Available: {:s}"

EQUALIZERBAR_COLORS = [
'#0C0786', '#40039C', '#6A00A7', '#8F0DA3', '#B02A8F', '#CA4678', '#E06461',
'#F1824C', '#FCA635', '#FCCC25', '#EFF821']


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setWindowIcon(QIcon(FPATH_ICON_WIN))
        self.setWindowFilePath(FPATH_ICON_WIN) # for Mac
        self.setGeometry( PX, PY, WIDTH, HEIGHT)
        self.initPlayer()
        self.initUI()
# end

    def initPlayer(self):
        self.player = QMediaPlayer()
        # print('supportedMimeTypes: ', self.player.supportedMimeTypes() )
        self.player.stateChanged.connect(self.Logo_Changed)
        self.player.positionChanged.connect(self.position_Changed)
        self.player.durationChanged.connect(self.duration_Changed)
        self.player.error.connect(self.handleError)
# end

    def initUI(self):
        self.equalizer = EqualizerBar(5,  EQUALIZERBAR_COLORS)

     # Menu 
        menubar = self.menuBar()
        menubar.setNativeMenuBar(False) # for Mac

# Menu File
        FileMenu = menubar.addMenu(MENU_FILE)

# Menu Open
        OpenFileAction = QAction(QIcon(FPATH_ICON_OPEN), OPEN_TEXT, self)
        OpenFileAction.setStatusTip(OPEN)
        OpenFileAction.setShortcut(QKeySequence.Open)
        OpenFileAction.triggered.connect(self.Open_File)
        FileMenu.addAction(OpenFileAction)
        FileMenu.addSeparator()

# Menu Quit
        QuitFileAction = QAction(QIcon(FPATH_ICON_CLOSE),   QUIT_TEXT, self)
        QuitFileAction.setStatusTip(QUIT)
        QuitFileAction.setShortcut(QKeySequence.Close)
        QuitFileAction.triggered.connect(self.Quit_Function)
        FileMenu.addAction(QuitFileAction)
        PreferenceMenu = self.menuBar().addMenu(MENU_PREF)

# Menu Start (Play)
        StartPreferenceAction = QAction(QIcon(FPATH_ICON_PLAY), PLAY, self)
        StartPreferenceAction.setStatusTip(PLAY)
        StartPreferenceAction.triggered.connect(self.Play_Music)

        PreferenceMenu.addAction(StartPreferenceAction)

# Menu Pause
        PausePreferenceAction = QAction(QIcon(FPATH_ICON_PAUSE), PAUSE, self)
        PausePreferenceAction.setStatusTip(PAUSE)
        PausePreferenceAction.triggered.connect(self.Pause_Music)
        PreferenceMenu.addAction(PausePreferenceAction)

# Menu Stop
        StopPreferenceAction = QAction(QIcon(FPATH_ICON_STOP), STOP, self)
        StopPreferenceAction.setStatusTip(STOP)
        StopPreferenceAction.triggered.connect(lambda: self.player.stop())
        PreferenceMenu.addAction(StopPreferenceAction)

# Play Button
        self.Play_Button = QPushButton()
        self.Play_Button.setEnabled(False)
        self.Play_Button.setIcon(self.style().standardIcon(QStyle.SP_MediaPlay))
        self.Play_Button.clicked.connect(self.Play_Music)

# Stop Button
        self.Stop_Button = QPushButton()
        self.Stop_Button.setEnabled(False)
        self.Stop_Button.setIcon(self.style().standardIcon(QStyle.SP_MediaStop))
        self.Stop_Button.clicked.connect(self.Stop_Function)

# Audio Slider
        self.slider = QSlider(Qt.Horizontal)
        self.slider.setRange(0, 0)
        self.slider.sliderMoved.connect(self.set_Position)

# Volume Slider
        self.Volume_slider = QSlider(Qt.Horizontal)
        self.Volume_slider.setMinimum(VOL_MIN)
        self.Volume_slider.setMaximum(VOL_MAX)
        self.Volume_slider.setValue(VOL_INIT)
        self.Volume_slider.setEnabled(False)
        self.Volume_slider.sliderMoved.connect(self.player.setVolume)
        self.Volume_slider.valueChanged.connect(self.Volume_Changed)

# Volume Display Label
        self.Volume_label = QLabel()
        self.Volume_label.setText( str(VOL_INIT) )

# Check Box
        self.Muted_CheckBox = QCheckBox()
        self.Muted_CheckBox.setEnabled(False)
        self.Muted_CheckBox.setIcon(self.style().standardIcon(QStyle.SP_MediaVolumeMuted))
        self.Muted_CheckBox.toggled.connect(self.Muted_Checking)

# Control Layout
        controlLayout = QHBoxLayout()
        controlLayout.setContentsMargins(0, 0, 0, 0)
        controlLayout.addWidget(self.Play_Button)
        controlLayout.addWidget(self.Stop_Button)
        controlLayout.addWidget(self.slider)
        controlLayout.addWidget(self.Volume_label)
        controlLayout.addWidget(self.Volume_slider)
        controlLayout.addWidget(self.Muted_CheckBox)

# Error Label
        self.errorLabel = QLabel()
        self.errorLabel.setStyleSheet(ERROR_LABEL_STYLE)

# VBoxLayout
        layout = QVBoxLayout()
        layout.addWidget(self.equalizer)
        layout.addLayout(controlLayout)
        layout.addWidget(self.errorLabel)
       
# CentralWidget
        widet = QWidget(self)
        widet.setLayout(layout)
        self.setCentralWidget( widet)
# end


    def Open_File(self):
        self.errorLabel.setText(EMPTY)
        fileName, selectedFilter = QFileDialog.getOpenFileName(self, 
            OPEN, QDir.homePath(), FILE_FILTER)
        if fileName != EMPTY:
            print('fileName: ', fileName)
            print('selectedFilter: ', selectedFilter)
            self.basename= os.path.basename(fileName)
            self.setWindowTitle(self.basename)
            media = QMediaContent(QUrl.fromLocalFile(fileName))
            self.player.setMedia(media)
            self.Play_Button.setEnabled(True)
            self.Stop_Button.setEnabled(True)
            self.Muted_CheckBox.setEnabled(True)
            self.Volume_slider.setEnabled(True)
            self.timer = QTimer()
            self.timer.setInterval(INTERVAL)
            self.timer.timeout.connect(self.update_values)
# end

    def Play_Music(self):
        if not self.player.isAudioAvailable():
            text = NOT_AVAILABLE_FORMAT.format(self.basename)
            print(text)
            self.errorLabel.setText(text)
            return
# end
        if self.player.state() == QMediaPlayer.PlayingState:
            self.player.pause()
            self.timer.stop()
        else:
            self.player.play()
            self.timer.start()
# end

    def Logo_Changed(self, state):
        if self.player.state() == QMediaPlayer.PlayingState:
            self.Play_Button.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPause))
        else:
            self.Play_Button.setIcon(
                self.style().standardIcon(QStyle.SP_MediaPlay))
# end

    def Pause_Music(self):
        self.player.pause()
        self.timer.stop()
# end

    def Volume_Changed(self):
        self.value = self.Volume_slider.value()
        self.Volume_label.setText(str(self.value))
# end

    def Muted_Checking(self):
        if self.Muted_CheckBox.isChecked():
            self.player.setMuted(True)
        else:
            self.player.setMuted(False)
# end

    def Stop_Function(self):
        self.player.stop()
        self.timer.stop()
# end

    def Quit_Function(self):
        sys.exit()
# end

    def position_Changed(self, position):
        self.slider.setValue(position)
# end

    def duration_Changed(self, duration):
        sec =  float(duration)/1000
        print('duration: ', sec ,' sec')
        self.slider.setRange(0, duration)
# end

    def set_Position(self, position):
        self.player.setPosition(position)
# end

    def update_values(self):
        self.equalizer.setValues([
            min(100, v + random.randint(0, 50)
            if random.randint(0, 5) > 2 else v)
            for v in self.equalizer.values()])
# end

    def handleError(self):
        self.Play_Button.setEnabled(False)
        basename = os.path.basename(self.fileName)
        text = ERROR_FORMAT.format(self.player.errorString(), basename)
        print(text)
        self.errorLabel.setText(text)
# end


def main():
    app = QApplication(sys.argv)
    print(QStyleFactory.keys())
    app.setStyle(APP_STYLE)
    win = Window()
    win.show()
    sys.exit(app.exec_())
# end


if __name__ == '__main__':
    main()
# end