# Python: "Analog Clock using pyqtgraph
# 2025-04-10  K.OHWADA

# https://github.com/ddside/analog_clock_python/blob/main/analog_clock.py

from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import numpy as np
import datetime
import sys

WIN_TITLE= "Analog Clock"
WIN_SIZE = 500

BOTTOM = 'bottom'
LEFT =  'left'

RESIZE_INTERVAL = 200 # msec
UPDATE_INTERVAL = 100 # msec

NUM_CIRCLE =1000


# time for the hand to rotate one lap
# ONE_LAP_HOUR = 12 # 12 houurs
# ONE_LAP_MIN = 60 # 60 minutess = one hour
# ONE_LAP_SEC = 60 # 60 secinds = one minute

# angle per unit time
SEC_DEG = 6 # 360/ONE_LAP_HOUR
MIN_DEG = 6 # 360/ONE_LAP_MIN
HOUR_DEG = 30 # 360/ONE_LAP_HOUR

# unit conversion
ONE_HOUR_MIN = 60 # one hour = 60minutes
ONE_MIN_SEC = 60 # one minute = 60 srconds

# second hand scale placed every 5 seconds on the outer circle
MAX_SEC = 60 # same  ONE_LAP_SEC
SEC_INTERVAL = 5

MIN_HOUR = 1
MAX_HOUR = 13 # MIN_HOUR + ONE_LAP_HOUR

DATE_FORMAT = '%Y-%m-%d %a'
TIME_FORMAT = '%H:%M:%S'
TIME_TEXT= '00:00:00'

RADIUS = 1

LINE_LENGTH_SEC_SCALE = 0.05
LINE_LENGTH_5SEC_SCALE = 0.1

PEN_WIDTH_SEC_SCALE= 2
PEN_WIDTH_5SEC_SCALE = 4

RATIO_HOUR_TEXT = 0.8
RATIO_SECOND_HAND = 0.85
RATIO_MINUTE_HAND = 0.8
RATIO_HOUR_HAND = 0.5

POS_HOUR_TEXT =  RADIUS * RATIO_HOUR_TEXT
LINE_LENGTH_SECOND_HAND =  RADIUS * RATIO_SECOND_HAND
LINE_LENGTH_MINUTE_HAND = RADIUS * RATIO_MINUTE_HAND
LINE_LENGTH_HOUR_HAND = RADIUS * RATIO_HOUR_HAND

FONT_SIZE_HOUR_TEXT = 48
FONT_SIZE_DATETIME = 32

PEN_WIDTH_CIRCLE = 4
PEN_WIDTH_HOUR_HAND =12
PEN_WIDTH_MINUTE_HAND =6
PEN_WIDTH_SECOND_HAND =2
 
win = pg.GraphicsLayoutWidget(show=True, title=WIN_TITLE)
win.resize(WIN_SIZE, WIN_SIZE)
pg.setConfigOptions(antialias=True)
graph = win.addPlot()
graph.showAxis(BOTTOM, False)
graph.showAxis(LEFT, False)
graph.setAspectLocked(lock=True)
graph.setMouseEnabled(x=False, y=False)

# draw outer circle
inspace_circle  = np.linspace(0, 2 * np.pi, NUM_CIRCLE)
x = RADIUS * np.cos(inspace_circle)
y =  RADIUS * np.sin(inspace_circle)
graph.plot(x, y, pen=pg.mkPen(width=PEN_WIDTH_CIRCLE) )


# drew sec scale
for second in range(MAX_SEC):
    line_length =   LINE_LENGTH_5SEC_SCALE if second % SEC_INTERVAL == 0 else  LINE_LENGTH_SEC_SCALE
    pen_width = PEN_WIDTH_5SEC_SCALE if second % SEC_INTERVAL == 0  else   PEN_WIDTH_SEC_SCALE
    rad_sec_scale = np.radians(360 * (second / 60))
    x1 = np.sin(rad_sec_scale) *  RADIUS
    x2 = np.sin(rad_sec_scale) * ( RADIUS - line_length)
    y1 = np.cos( rad_sec_scale) *  RADIUS
    y2 = np.cos(rad_sec_scale) * ( RADIUS - line_length)
    pen_sec_scale = pg.mkPen(width=pen_width)
    pen_sec_scale.setCapStyle(QtCore.Qt.RoundCap)
    graph.plot([x1, x2], [y1, y2], pen=pen_sec_scale )
# end

hour_texts = []

ONE_LAP_HOUR = 12

# append hour_texts
for hour in range( MIN_HOUR,  MAX_HOUR, 1):
    rad_hours = np.radians( hour * HOUR_DEG )
    px = np.sin(rad_hours) * POS_HOUR_TEXT
    py = np.cos(rad_hours) * POS_HOUR_TEXT
    hour_text = pg.TextItem(text=str(hour), anchor=(0.5, 0.5))
    hour_text.setPos(px, py)
    font = QtGui.QFont()
    font.setPixelSize(FONT_SIZE_HOUR_TEXT )
    hour_text.setFont(font)
    graph.addItem(hour_text)
    hour_texts.append(hour_text)
# end

dt_now = datetime.datetime.now()
# date_str = '{}/{}/{} {}'.format(dt_now.year, dt_now.month, dt_now.day, dt_now.strftime('%a'))
date_str = dt_now.strftime(DATE_FORMAT)
date_text = pg.TextItem(text=date_str, anchor=(0.5, 0.5))
yo = - RADIUS / 3.5
date_text.setPos(0, yo)
font = QtGui.QFont()
font.setPixelSize( FONT_SIZE_DATETIME )
date_text.setFont(font)
graph.addItem(date_text)
time_text = pg.TextItem(text=TIME_TEXT, anchor=(0.5, 0.5))
y1 = yo - (RADIUS * 0.2)
time_text.setPos(0, y1)
time_text.setFont(font)
graph.addItem(time_text)
pen_hour = pg.mkPen(width=PEN_WIDTH_HOUR_HAND)
pen_hour.setCapStyle(QtCore.Qt.RoundCap)
hour_hand_plot = graph.plot(pen=pen_hour)
pen_minute = pg.mkPen(width=PEN_WIDTH_MINUTE_HAND)
pen_minute.setCapStyle(QtCore.Qt.RoundCap)
minute_hand_plot = graph.plot(pen=pen_minute)
pen_second = pg.mkPen(width=PEN_WIDTH_SECOND_HAND)
pen_second.setCapStyle(QtCore.Qt.RoundCap)
second_hand_plot = graph.plot(pen=pen_second)


def set_time(dt_now):
    hour= dt_now.hour
    minute = dt_now.minute
    second = dt_now.second
    deg_second = second * SEC_DEG
    deg_minute = int( (minute + float( float(second) / ONE_MIN_SEC) ) * MIN_DEG)
    deg_hour = int( (hour  + float( float(minute) / ONE_HOUR_MIN) ) * HOUR_DEG )
    rad_second = np.radians(deg_second)
    rad_minute = np.radians(deg_minute)
    rad_hour = np.radians(deg_hour)
    x_second = np.sin(rad_second) * LINE_LENGTH_SECOND_HAND
    y_second = np.cos(rad_second)  * LINE_LENGTH_SECOND_HAND
    second_hand_plot.setData([0, x_second], [0, y_second])
    x_minute = np.sin(rad_minute) *  LINE_LENGTH_MINUTE_HAND
    y_minute = np.cos(rad_minute) *  LINE_LENGTH_MINUTE_HAND
    minute_hand_plot.setData([0, x_minute], [0, y_minute])
    x_hour = np.sin(rad_hour) *  LINE_LENGTH_HOUR_HAND
    y_hour = np.cos(rad_hour) *  LINE_LENGTH_HOUR_HAND
    hour_hand_plot.setData([0, x_hour], [0, y_hour])
    # time_str = '{:02d}:{:02d}:{:02d}'.format(hour, minute, second)
    time_str = dt_now.strftime(TIME_FORMAT)
    time_text.setText(time_str)
# end

def resize_text():
    size = win.size()
    height = size.height()
    width = size.width()
    new_font_size = int( FONT_SIZE_DATETIME * (min(height, width) / WIN_SIZE) )
    font = QtGui.QFont()
    font.setPixelSize(new_font_size )
    date_text.setFont(font)
    time_text.setFont(font)
# end

    for hour_text in hour_texts:
        font = QtGui.QFont()
        font.setPixelSize(new_font_size)
        hour_text.setFont(font)
# end

resize_timer = QtCore.QTimer()
resize_timer.timeout.connect(resize_text)
resize_timer.start(RESIZE_INTERVAL)

def update_clock():
    dt_now = datetime.datetime.now()
    set_time(dt_now )
# end

update_timer = QtCore.QTimer()
update_timer.timeout.connect(update_clock)
update_timer.start(UPDATE_INTERVAL)

if __name__ == '__main__':
# app = QtGui.QApplication([])
    app = pg.mkQApp()
    win.show()
    sys.exit(app.exec_())
# end
  
