# This is Tetris game clone
# Author: Jan Bodnar
# https://zetcode.com/gui/pyqt5/tetris/
# modify: 2025-04-10  K.OHWADA
# You can change game speed (interval)

# Operation
# Key_Left: move left
# Key_Right: move right
# Key_Up: rotateLeft
# Key_Down: rotateRight
# Key_Space: dropDown
# Key_D: oneLineDown
# Key_P: pause, restart if pause


import random
import sys
from PyQt5.QtCore import Qt, QBasicTimer, pyqtSignal
from PyQt5.QtGui import QPainter, QColor
from PyQt5.QtWidgets import QMainWindow, QFrame, QDesktopWidget, QApplication


# Window
WIN_TITLE="PyQt5 Tetris"
PX=100
PY=100
WIDTH= 200
HEIGHT= 400

# Board
BOARD_WIDTH = 10
BOARD_HEIGHT = 22

INTERVAL = 300 # msec

# Color
COLOR_TABLE = [0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
                      0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00]

COORDS_TABLE = (
        ((0, 0), (0, 0), (0, 0), (0, 0)),
        ((0, -1), (0, 0), (-1, 0), (-1, 1)),
        ((0, -1), (0, 0), (1, 0), (1, 1)),
        ((0, -1), (0, 0), (0, 1), (0, 2)),
        ((-1, 0), (0, 0), (1, 0), (0, 1)),
        ((0, 0), (1, 0), (0, 1), (1, 1)),
        ((-1, -1), (0, -1), (0, 0), (0, 1)),
        ((1, -1), (0, -1), (0, 0), (0, 1))
    )


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        """initiates application UI"""
        self.setWindowTitle(WIN_TITLE) 

        # self.resize(180, 380)
        # self.center()
        self.setGeometry(PX, PY, WIDTH,HEIGHT)
# end

    def set_interval(self, interval):
        self.tboard = Board(self)
        self.tboard. set_interval(interval)
        self.setCentralWidget(self.tboard)
        self.statusbar = self.statusBar()
        self.tboard.msg2Statusbar[str].connect(self.statusbar.showMessage)
        self.tboard.start()
# end

    def center(self):
        """centers the window on the screen"""
        screen = QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move(int((screen.width() - size.width()) / 2),
                  int((screen.height() - size.height()) / 2))
# end


class Board(QFrame):
    msg2Statusbar = pyqtSignal(str)

    def __init__(self, parent):
        super().__init__(parent)
        self.initBoard()
# end

    def initBoard(self):
        """initiates board"""
        self.timer = QBasicTimer()
        self.interval = 0
        self.isWaitingAfterLine = False
        self.curX = 0
        self.curY = 0
        self.numLinesRemoved = 0
        self.board = []
        self.setFocusPolicy(Qt.StrongFocus)
        self.isStarted = False
        self.isPaused = False
        self.clearBoard()
# end

    def set_interval(self, interval):
        self.interval = interval
# end

    def shapeAt(self, x, y):
        """determines shape at the board position"""
        return self.board[(y * BOARD_WIDTH) + x]
# end

    def setShapeAt(self, x, y, shape):
        """sets a shape at the board"""
        self.board[(y * BOARD_WIDTH) + x] = shape
# end

    def squareWidth(self):
        """returns the width of one square"""
        return self.contentsRect().width() // BOARD_WIDTH
# end

    def squareHeight(self):
        """returns the height of one square"""
        return self.contentsRect().height() // BOARD_HEIGHT
# end

    def start(self):
        """starts game"""
        if self.isPaused:
            return
# end
        self.isStarted = True
        self.isWaitingAfterLine = False
        self.numLinesRemoved = 0
        self.clearBoard()
        self.msg2Statusbar.emit(str(self.numLinesRemoved))
        self.newPiece()
        print('timer.start: ', self.interval)
        self.timer.start(self.interval, self)
# end

    def pause(self):
        """pauses game"""
        if not self.isStarted:
            return
# end
        self.isPaused = not self.isPaused
        if self.isPaused:
            self.timer.stop()
            self.msg2Statusbar.emit("paused")
        else:
            self.timer.start(self.interval, self)
            self.msg2Statusbar.emit(str(self.numLinesRemoved))
# end
        self.update()
# end

    def paintEvent(self, event):
        """paints all shapes of the game"""
        painter = QPainter(self)
        rect = self.contentsRect()
        boardTop = rect.bottom() - BOARD_HEIGHT * self.squareHeight()
        for i in range(BOARD_HEIGHT):
            for j in range(BOARD_WIDTH):
                shape = self.shapeAt(j, BOARD_HEIGHT - i - 1)
                if shape != Tetrominoe.NoShape:
                    self.drawSquare(painter,
                                    rect.left() + j * self.squareWidth(),
                                    boardTop + i * self.squareHeight(), shape)
# end
        if self.curPiece.shape() != Tetrominoe.NoShape:
            for i in range(4):
                x = self.curX + self.curPiece.x(i)
                y = self.curY - self.curPiece.y(i)
                self.drawSquare(painter, rect.left() + x * self.squareWidth(),
                                boardTop + (BOARD_HEIGHT - y - 1) * self.squareHeight(),
                                self.curPiece.shape())
# end

    def keyPressEvent(self, event):
        """processes key press events"""
        if not self.isStarted or self.curPiece.shape() == Tetrominoe.NoShape:
            super(Board, self).keyPressEvent(event)
            return
# end
        key = event.key()
        if key == Qt.Key_P:
            self.pause()
            return
# end
        if self.isPaused:
            return
        elif key == Qt.Key_Left:
            self.tryMove(self.curPiece, self.curX - 1, self.curY)
        elif key == Qt.Key_Right:
            self.tryMove(self.curPiece, self.curX + 1, self.curY)
        elif key == Qt.Key_Down:
            self.tryMove(self.curPiece.rotateRight(), self.curX, self.curY)
        elif key == Qt.Key_Up:
            self.tryMove(self.curPiece.rotateLeft(), self.curX, self.curY)
        elif key == Qt.Key_Space:
            self.dropDown()
        elif key == Qt.Key_D:
            self.oneLineDown()
        else:
            super(Board, self).keyPressEvent(event)
# end

    def timerEvent(self, event):
        """handles timer event"""
        if event.timerId() == self.timer.timerId():
            if self.isWaitingAfterLine:
                self.isWaitingAfterLine = False
                self.newPiece()
            else:
                self.oneLineDown()
        else:
            super(Board, self).timerEvent(event)
# end

    def clearBoard(self):
        """clears shapes from the board"""
        for i in range(BOARD_HEIGHT * BOARD_WIDTH):
            self.board.append(Tetrominoe.NoShape)
# end

    def dropDown(self):
        """drops down a shape"""
        newY = self.curY
        while newY > 0:
            if not self.tryMove(self.curPiece, self.curX, newY - 1):
                break
            newY -= 1
# end
        self.pieceDropped()
# end

    def oneLineDown(self):
        """goes one line down with a shape"""
        if not self.tryMove(self.curPiece, self.curX, self.curY - 1):
            self.pieceDropped()
# end

    def pieceDropped(self):
        """after dropping shape, remove full lines and create new shape"""
        for i in range(4):
            x = self.curX + self.curPiece.x(i)
            y = self.curY - self.curPiece.y(i)
            self.setShapeAt(x, y, self.curPiece.shape())
# end
        self.removeFullLines()
        if not self.isWaitingAfterLine:
            self.newPiece()
# end

    def removeFullLines(self):
        """removes all full lines from the board"""
        numFullLines = 0
        rowsToRemove = []
        for i in range(BOARD_HEIGHT):
            n = 0
            for j in range(BOARD_WIDTH):
                if not self.shapeAt(j, i) == Tetrominoe.NoShape:
                    n = n + 1
            if n == 10:
                rowsToRemove.append(i)
# end
        rowsToRemove.reverse()
# end
        for m in rowsToRemove:
            for k in range(m, BOARD_HEIGHT):
                for l in range(BOARD_WIDTH):
                    self.setShapeAt(l, k, self.shapeAt(l, k + 1))
# end
        numFullLines = numFullLines + len(rowsToRemove)
        if numFullLines > 0:
            self.numLinesRemoved = self.numLinesRemoved + numFullLines
            self.msg2Statusbar.emit(str(self.numLinesRemoved))
            self.isWaitingAfterLine = True
            self.curPiece.setShape(Tetrominoe.NoShape)
            self.update()
# end

    def newPiece(self):
        """creates a new shape"""
        self.curPiece = Shape()
        self.curPiece.setRandomShape()
        self.curX = BOARD_WIDTH // 2 + 1
        self.curY = BOARD_HEIGHT - 1 + self.curPiece.minY()
        if not self.tryMove(self.curPiece, self.curX, self.curY):
            self.curPiece.setShape(Tetrominoe.NoShape)
            self.timer.stop()
            self.isStarted = False
            self.msg2Statusbar.emit("Game over")
# end

    def tryMove(self, newPiece, newX, newY):
        """tries to move a shape"""
        for i in range(4):
            x = newX + newPiece.x(i)
            y = newY - newPiece.y(i)
            if x < 0 or x >= BOARD_WIDTH or y < 0 or y >= BOARD_HEIGHT:
                return False
            if self.shapeAt(x, y) != Tetrominoe.NoShape:
                return False
# end
        self.curPiece = newPiece
        self.curX = newX
        self.curY = newY
        self.update()
        return True
# end

    def drawSquare(self, painter, x, y, shape):
        """draws a square of a shape"""
        color = QColor(COLOR_TABLE[shape])
        painter.fillRect(x + 1, y + 1, self.squareWidth() - 2,
                         self.squareHeight() - 2, color)
        painter.setPen(color.lighter())
        painter.drawLine(x, y + self.squareHeight() - 1, x, y)
        painter.drawLine(x, y, x + self.squareWidth() - 1, y)
        painter.setPen(color.darker())
        painter.drawLine(x + 1, y + self.squareHeight() - 1,
                         x + self.squareWidth() - 1, y + self.squareHeight() - 1)
        painter.drawLine(x + self.squareWidth() - 1,
                         y + self.squareHeight() - 1, x + self.squareWidth() - 1, y + 1)
# end


class Tetrominoe(object):
    NoShape = 0
    ZShape = 1
    SShape = 2
    LineShape = 3
    TShape = 4
    SquareShape = 5
    LShape = 6
    MirroredLShape = 7
# end


class Shape(object):

    def __init__(self):
        self.coords = [[0, 0] for i in range(4)]
        self.pieceShape = Tetrominoe.NoShape
        self.setShape(Tetrominoe.NoShape)
# end

    def shape(self):
        """returns shape"""
        return self.pieceShape
# end

    def setShape(self, shape):
        """sets a shape"""
        table =  COORDS_TABLE[shape]
        for i in range(4):
            for j in range(2):
                self.coords[i][j] = table[i][j]
# end
        self.pieceShape = shape
# end

    def setRandomShape(self):
        """chooses a random shape"""
        self.setShape(random.randint(1, 7))
# end

    def x(self, index):
        """returns x coordinate"""
        return self.coords[index][0]
# end

    def y(self, index):
        """returns y coordinate"""
        return self.coords[index][1]
# end

    def setX(self, index, x):
        """sets x coordinate"""
        self.coords[index][0] = x
# end

    def setY(self, index, y):
        """sets y coordinate"""
        self.coords[index][1] = y
# end

    def minX(self):
        """returns min x value"""
        m = self.coords[0][0]
        for i in range(4):
            m = min(m, self.coords[i][0])
# end
        return m
# end

    def maxX(self):
        """returns max x value"""
        m = self.coords[0][0]
        for i in range(4):
            m = max(m, self.coords[i][0])
# end
        return m
# end

    def minY(self):
        """returns min y value"""
        m = self.coords[0][1]
        for i in range(4):
            m = min(m, self.coords[i][1])
# end
        return m
# end

    def maxY(self):
        """returns max y value"""
        m = self.coords[0][1]
        for i in range(4):
            m = max(m, self.coords[i][1])
# end
        return m
# end

    def rotateLeft(self):
        """rotates shape to the left"""
        if self.pieceShape == Tetrominoe.SquareShape:
            return self
# end
        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, self.y(i))
            result.setY(i, -self.x(i))
# end
        return result
# end

    def rotateRight(self):
        """rotates shape to the right"""
        if self.pieceShape == Tetrominoe.SquareShape:
            return self
# end
        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, -self.y(i))
            result.setY(i, self.x(i))
# end
        return result
# end


def main(interval):
    app = QApplication([])
    win = Window()
    win.set_interval(interval)
    win.show()
    sys.exit(app.exec_())
# end

# main
args = sys.argv
argc = len(args)
script = args[0]
interval = INTERVAL

if argc < 2:
	print("Usage: python %s  <interval>" % script)
elif argc >= 2:
    interval = int(args[1])
# end

main(interval)

