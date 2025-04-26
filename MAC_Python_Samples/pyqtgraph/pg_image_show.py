# Python: draw gpaph using pyqtgraph
# 2025-04-10  K.OHWADA

# https://www.swelec.tech/blog/blog/2021/05/14/pyqtgraph%E3%82%92%E7%94%A8%E3%81%84%E3%81%9F%E3%82%A2%E3%83%97%E3%83%AA%E3%82%B1%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3%E9%96%8B%E7%99%BA%EF%BC%88%E3%81%AF%E3%81%98%E3%82%81%E3%81%AE%E4%B8%80%E6%AD%A9/

import pyqtgraph as pg
from PIL import Image
import numpy as np
import sys

def Setup_Window():
    #win = pg.LayoutWidget()  # main Window
    win = pg.GraphicsLayoutWidget() # Layout manager
    imv = pg.ImageView()
    data = np.array(Image.open("sample.png"))
    imv.setImage(data)    
    # win.addWidget(imv, row = 0, col = 0)  
    image = pg.ImageItem()
    image.setImage(data)
    vbox = pg.ViewBox()
    vbox.addItem(image)
    win.addItem(image)  
    return win

if __name__ == '__main__':
    app = pg.mkQApp()
    win = Setup_Window()
    win.show()
    sys.exit(app.exec_())
# end
