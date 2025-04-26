# Python: Dejital Clock with Tk using threading
# 2025-04-10  K.OHWADA

# https://office54.net/python/tkinter/after-method-schedule


import tkinter as tk
import threading
import time
import datetime

#Window
TITLE='Digital Clock'
WIN_SIZE='300x100'

# Label
FONT_FAMILY='times'
FONT_SIZE=50
FONT_STYLE='bold'

# Color
GRAY ='gray'
BLACK ='black'
BLUE='blue'
YELLOW='yellow' 

# after 1sec
DELAY =1000

### 時刻取得関数
def get_time():
 
    ### 無限ループ
    while True:
 
        ### 現在時刻取得
        now = datetime.datetime.now()
 
        ### 時刻設定
        tm = "{:02}:{:02}:{:02}".format(now.hour, now.minute, now.second)
 
        ### キャンバス初期化
        canvas.delete("all")
 
        ### キャンバスに時刻表示
        canvas.create_text(100, 50, text=tm, font=(None,36))
 
        #### 待ち時間
        time.sleep(1)
 # end

# main

### キャンバス作成
canvas = tk.Canvas(master=None, width=200, height=100)
 
### キャンバス表示
canvas.pack()
 

### スレッド作成
thread = threading.Thread(target=get_time, daemon=True)
 
### スレッド開始
thread.start()
 
### イベントループ
canvas.mainloop()




