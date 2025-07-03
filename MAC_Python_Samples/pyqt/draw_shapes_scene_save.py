# Python: draw Shape using QGraphicsScene
# save file using QImage
# 2025-04-10  K.OHWADA


from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from pos import *
import sys

# Window
WIN_TITLE =  "draw Shapes"
PX=50
PY=50
WIDTH = 480
HEIGHT = 360

TEXT = "Hello Python"
FONT = 'Arial'
FONT_SIZE = 20

FPATH_IMG = "python_qt_logo.png"

OUTFILE = "qt_draw_shapes_scene.png"

class Window(QGraphicsView):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)
        self.draw_shapes()
# end

    def save_scene(self, scene):
        w = int(scene.width())
        h = int(scene.height())
        print('scene: ', w, h)
        img = QImage(w, h, QImage.Format_RGB32)
        img.fill(Qt.white)
        painter = QPainter(img)
        scene.render(painter)
        painter.end()
        img.save(OUTFILE)
# end

    def draw_shapes(self):
        scene = QGraphicsScene()
        scene.setSceneRect(0, 0, WIDTH, HEIGHT)
        pen_black = QPen(QColor(Qt.black), 2)
        pen_red = QPen(QColor(Qt.red))
        pen_green = QPen(QColor(Qt.green), 2)
        pen_blue = QPen(QColor(Qt.blue), 2)
        brush_cyan = QBrush(QColor(Qt.cyan))
        font = QFont(FONT, FONT_SIZE)
        text = scene.addText(TEXT, font)
        text.setPos(20, 30)
        text.setDefaultTextColor(Qt.red)
        scene.addLine( 20,100,150,100, pen_blue)
        scene.addRect(20,150,150,100, pen_green)
        rect_item = QGraphicsRectItem(30,170,120,60)
        rect_item.setBrush(QBrush(Qt.SolidPattern))
        scene.addItem(rect_item)
        ellipse_item = QGraphicsEllipseItem(200,50,70,100)
        ellipse_item.setPen(pen_black)
        ellipse_item.setBrush( brush_cyan)
        scene.addItem(ellipse_item)
        pixmap_item = QGraphicsPixmapItem(QPixmap(FPATH_IMG))
        pixmap_item.setPos(300,50)
        scene.addItem(pixmap_item)
        self.save_scene(scene)
        self.setScene(scene)
# end


def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end
