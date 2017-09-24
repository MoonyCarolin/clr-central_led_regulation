import tkinter as tk
import tkFontChooser as tkfont
import tkcolorpicker
from IPAdresses import *


#  ____     ____     ____     ____     ____     ____     ____     ____     ____     ____     ____     ____
# |____|   |____|   |____|   |____|   |____|   |____|   |____|   |____|   |____|   |____|   |____|   |____|
#   101      201      301      401      501      601      701      801      901      100      111      121
#  _                                                                                                     _
# | | 102                                                                                          1201 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 202                                                                                          1202 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 302                                                                                          1203 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 402                                                                                          1204 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 502                                                                                          1205 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 602                                                                                          1206 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 702                                                                                          1207 | |
# |_|                                                                                                   |_|
#  _                                                                                                     _
# | | 802                                                                                          1208 | |
# |_|                                                                                                   |_|


def function():
    selection = var.get()

    if selection == 101:
        color = tkcolorpicker.askcolor()
        # L101()
        rgbcolor = color[1]
        print(color)

    if selection == 201:
        color = tkcolorpicker.askcolor()
        print(color)

root = tk.Tk()
var = tk.IntVar()
root.title('CLR - Central LED Regulation')


tk.Radiobutton(root, variable = var, value = 101, height=1, width=10, indicatoron=0, command = function).grid(column=1, row=1)
tk.Radiobutton(root, variable = var, value = 201, height=1, width=10, indicatoron=0, command = function).grid(column=2, row=1)
tk.Radiobutton(root, variable = var, value = 301, height=1, width=10, indicatoron=0, command = function).grid(column=3, row=1)
tk.Radiobutton(root, variable = var, value = 401, height=1, width=10, indicatoron=0, command = function).grid(column=4, row=1)
tk.Radiobutton(root, variable = var, value = 501, height=1, width=10, indicatoron=0, command = function).grid(column=5, row=1)
tk.Radiobutton(root, variable = var, value = 601, height=1, width=10, indicatoron=0, command = function).grid(column=6, row=1)
tk.Radiobutton(root, variable = var, value = 701, height=1, width=10, indicatoron=0, command = function).grid(column=7, row=1)
tk.Radiobutton(root, variable = var, value = 801, height=1, width=10, indicatoron=0, command = function).grid(column=8, row=1)
tk.Radiobutton(root, variable = var, value = 901, height=1, width=10, indicatoron=0, command = function).grid(column=9, row=1)
tk.Radiobutton(root, variable = var, value = 1001, height=1, width=10, indicatoron=0, command = function).grid(column=10, row=1)
tk.Radiobutton(root, variable = var, value = 1101, height=1, width=10, indicatoron=0, command = function).grid(column=11, row=1)
tk.Radiobutton(root, variable = var, value = 1201, height=1, width=10, indicatoron=0, command = function).grid(column=12, row=1)


tk.Radiobutton(root, variable = var, value = 102, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=2, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 103, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=3, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 104, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=4, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 105, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=5, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 106, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=6, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 107, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=7, sticky=tk.W)
tk.Radiobutton(root, variable = var, value = 108, height=4, width=2, indicatoron=0, command = function).grid(column=1, row=8, sticky=tk.W)

tk.Radiobutton(root, variable = var, value = 1202, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=2, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1203, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=3, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1204, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=4, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1205, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=5, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1206, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=6, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1207, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=7, sticky=tk.E)
tk.Radiobutton(root, variable = var, value = 1208, height=4, width=2, indicatoron=0, command = function).grid(column=12, row=8, sticky=tk.E)

tk.mainloop()
