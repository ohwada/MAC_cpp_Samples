 # Python: automatically change Image Size when CustomWindow is resized
# 2025-04-10  K.OHWADA

# https://forum.qt.io/topic/150700/how-to-resize-images-so-they-always-fit-to-the-scene


from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys, os


# Window
WIN_TITLE = "Image Viewer"
PX = 50
PY = 50
WIDTH = 400
HEIGHT = 400

BG_COLOR = QColor(3, 5, 15) # black
        
     
class CustomWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
# end

    def initUI(self):
        self.setWindowTitle(  WIN_TITLE)
        self.setGeometry(PX, PY, WIDTH, HEIGHT)   
        # Create a central widget and set it as the main window's central widget
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        # Create a QGraphicsView and set it as the central widget
        layout = QVBoxLayout(central_widget)
        layout.setContentsMargins(0, 0, 0, 0)
        #layout.setSpacing(0)
        self.view = QGraphicsView(self)
        self.view.setBackgroundBrush(   BG_COLOR)
        layout.addWidget(self.view)
        # Create a QGraphicsScene
        self.scene = QGraphicsScene(self)
        self.view.setScene(self.scene)
        # Create a QAction to open an image
        open_action = QAction("Open Image", self)
        open_action.triggered.connect(self.openImage)
        self.menuBar().addAction(open_action)
        self.grouped_images = {}  # Dictionary to store images in groups
        self.group_names = []  # List to store group names
        self.current_group_index = 0  # Index of the currently selected group
        self.current_image_index = 0  # Index of the currently displayed image within the group
        text_item = QGraphicsTextItem("Alice")
        font = text_item.font()
        font.setPointSize(150)  # Adjust the font size as needed
        text_item.setFont(font)
        text_item.setDefaultTextColor(Qt.red)
        text_item.setPos(100, 100)
        self.scene.addItem(text_item)
        self.setShortcuts()
# end
    
    def setShortcuts(self):
        QShortcut(QKeySequence(Qt.Key_F11), self, self.toggleFullScreen)
        QShortcut(QKeySequence(Qt.Key_Right), self, self.nextImage)
        QShortcut(QKeySequence(Qt.Key_Left), self, self.previousImage)
        QShortcut(QKeySequence(Qt.Key_Up), self, self.switchGroupUp)
        QShortcut(QKeySequence(Qt.Key_Down), self, self.switchGroupDown)
# end

    def openImage(self):
        folder_dialog = QFileDialog.getExistingDirectory(self, "Open Directory")
        if folder_dialog:
            self.grouped_images, self.group_names = self.collectGroupedImages(folder_dialog)
            self.current_group_index = 0  # Reset the current group index
            self.current_image_index = 0  # Reset the current image index within the group   
            if self.group_names:
                self.displayImage()
# if def end

    def collectGroupedImages(self, directory):
        grouped_images = {}
        group_names = []
        for root, _, files in os.walk(directory):
            # Determine the group name (folder name)
            group_name = os.path.basename(root)
            if group_name not in grouped_images:
                grouped_images[group_name] = []
                group_names.append(group_name)
#
            for filename in files:
                if filename.lower().endswith(('.jpg', '.jpeg', '.png', '.gif', '.bmp', '.tiff', '.tif')):
                    image_path = os.path.join(root, filename)
                    grouped_images[group_name].append(image_path)
# if for end
        return grouped_images, group_names
# def end

    def switchGroupUp(self):
        if self.group_names:
            self.current_group_index = (self.current_group_index - 1) % len(self.group_names)
            self.current_image_index = 0  # Reset the current image index within the new group
            self.displayImage()
# if def end

    def switchGroupDown(self):
        if self.group_names:
            self.current_group_index = (self.current_group_index + 1) % len(self.group_names)
            self.current_image_index = 0  # Reset the current image index within the new group
            self.displayImage()
# end

    def nextImage(self):
        if self.group_names:
            current_group_name = self.group_names[self.current_group_index]
            current_group = self.grouped_images.get(current_group_name, [])
            if current_group:
                self.current_image_index = (self.current_image_index + 1) % len(current_group)
                self.displayImage()
       # if def end

    def previousImage(self):
        if self.group_names:
            current_group_name = self.group_names[self.current_group_index]
            current_group = self.grouped_images.get(current_group_name, [])
            if current_group:
                self.current_image_index = (self.current_image_index - 1) % len(current_group)
                self.displayImage()
# end

    def displayImage(self):
        #self.timer.start(self.new_delay * 1000)
        if self.group_names:
            current_group_name = self.group_names[self.current_group_index]
            current_group = self.grouped_images.get(current_group_name, [])
            if current_group:
                image_path = current_group[self.current_image_index]
                image = QImage(image_path)
                pixmap = QPixmap(image)
                pixmap_item = QGraphicsPixmapItem(pixmap)
                self.scene.clear()
                self.scene.addItem(pixmap_item)
                self.scene.setSceneRect(0, 0, pixmap.width(), pixmap.height())
                self.view.setScene(self.scene)
                self.view.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)
# if def end

    def resizeEvent(self, event):
        self.view.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)
# end

    def toggleFullScreen(self):
        if self.isFullScreen():
            self.showNormal()
            self.menuBar().show()
        else:
            self.showFullScreen()
            self.menuBar().hide()
# end

def main():
    app = QApplication(sys.argv)
    win = CustomWindow()
    win.show()
    sys.exit(app.exec())
# end

if __name__ == '__main__':
    main()
# end

