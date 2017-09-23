import tkinter as tk
import tkFontChooser as tkfont


#maintitle = tk.Font(family='Arial', size=16, weight='bold')
def colorchooser():
    return 0

class lamp:
    def __init__(self, location, color):
        self.location = location
        self.color = None

 #   def color(self):




root = tk.Tk()


root.title('CLR - Central LED Regulation')



def horizontalbutton(location, background='#fff'):
    return tk.Button(location, background=background, height=1, width=10, command=colorchooser)


def verticalbutton(location, background='#fff'):
    return tk.Button(location, background=background, height=4, width=2, command=colorchooser)



#root.maxsize(1000, 400)
#root.geometry()
root.minsize(500,200)
#root.configure()
root.columnconfigure(1, weight=0)
root.rowconfigure(1, weight=0)

w = verticalbutton(root, background='#00f')
y = horizontalbutton(root, background='#0ff')
v = horizontalbutton(root, background='#0f0')


horizontalbutton(root, background='#00f').grid(row=0, column=0)
horizontalbutton(root, background='#00f').grid(row=0, column=1)
horizontalbutton(root, background='#00f').grid(row=0, column=2)
horizontalbutton(root, background='#00f').grid(row=0, column=3)
horizontalbutton(root, background='#00f').grid(row=0, column=4)
horizontalbutton(root, background='#00f').grid(row=0, column=5)
horizontalbutton(root, background='#00f').grid(row=0, column=6)
horizontalbutton(root, background='#00f').grid(row=0, column=7)
horizontalbutton(root, background='#00f').grid(row=0, column=8)

verticalbutton(root, background='#00f').grid(row=1, column=0, sticky=tk.W)
verticalbutton(root, background='#00f').grid(row=2, column=0, sticky=tk.W)
verticalbutton(root, background='#00f').grid(row=3, column=0, sticky=tk.W)
verticalbutton(root, background='#00f').grid(row=4, column=0, sticky=tk.W)

verticalbutton(root, background='#00f').grid(row=1, column=8, sticky=tk.E)
verticalbutton(root, background='#00f').grid(row=2, column=8, sticky=tk.E)
verticalbutton(root, background='#00f').grid(row=3, column=8, sticky=tk.E)
verticalbutton(root, background='#00f').grid(row=4, column=8, sticky=tk.E)


root.mainloop()

