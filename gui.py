import tkinter as tk
import tkFontChooser as tkfont
import tkcolorpicker


#maintitle = tk.Font(family='Arial', size=16, weight='bold')
#def ccolorchooser():

 #   return 0

# class lamp:
#     def __init__(self, location, color):
#         self.location = location
#         self.color = None

 #   def color(self):



buttonbackground = None

root = tk.Tk()


root.title('CLR - Central LED Regulation')


def getColor():
    color = tkcolorpicker.askcolor()
  #  print(color)
    rgbcolor = color[1]
    return rgbcolor



def horizontalbutton(location, background='#fffff'):
   # background = getColor()
    return tk.Radiobutton(location, background=background, height=1, width=10, indicatoron=0, command=getColor)


def verticalbutton(location, background='#ffffff'):
    return tk.Button(location, background=background, height=4, width=2, command=getColor)


#root.maxsize(1000, 400)
#root.geometry()
root.minsize(500,200)
#root.configure()
root.columnconfigure(1, weight=0)
root.rowconfigure(1, weight=0)

# w = verticalbutton(root, background=buttonbackground)
# y = horizontalbutton(root, background='#0ff')
# v = horizontalbutton(root, background='#0f0')


horizontalbutton(root, background=buttonbackground).grid(row=0, column=0)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=1)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=2)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=3)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=4)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=5)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=6)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=7)
horizontalbutton(root, background=buttonbackground).grid(row=0, column=8)

verticalbutton(root, background=buttonbackground).grid(row=1, column=0, sticky=tk.W)
verticalbutton(root, background=buttonbackground).grid(row=2, column=0, sticky=tk.W)
verticalbutton(root, background=buttonbackground).grid(row=3, column=0, sticky=tk.W)
verticalbutton(root, background=buttonbackground).grid(row=4, column=0, sticky=tk.W)

verticalbutton(root, background=buttonbackground).grid(row=1, column=8, sticky=tk.E)
verticalbutton(root, background=buttonbackground).grid(row=2, column=8, sticky=tk.E)
verticalbutton(root, background=buttonbackground).grid(row=3, column=8, sticky=tk.E)
verticalbutton(root, background=buttonbackground).grid(row=4, column=8, sticky=tk.E)


root.mainloop()

