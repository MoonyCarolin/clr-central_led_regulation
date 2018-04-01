try:
    # Python2
    import Tkinter as tk
except ImportError:
    # Python3
    import tkinter as tk
import paho.mqtt.client as mqtt
import tkcolorpicker
import os


roomsize = [1250, 650]  #[1250, 650] #in cm
sizefactor = 0.1 * 7.7
ledbandwidth_hori = 10
ledbandheight_hori = ledbandwidth_hori / 10
ledbandwidth_verti = 2
ledbandheight_verti = ledbandwidth_verti * 2
xpositionfactor = 8
xpositionshift = -79
ypositionfactor = 75
ypositionshift = -65


def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe('LED')
    client.subscribe('LED/#')


def on_publish(client, userdata, mid):
    print('mid: '+str(mid))


def on_message(client, userdata, msg):
    print(msg.topic+' '+str(msg.payload))


def datageneration(identifier):
    color = tkcolorpicker.askcolor()
  #  print(identifier, color, 'LED/' + str(identifier))
   # print(color[1])
    hexa = str(color[1])
    print(hexa)
   # print(hexa[1:])
  #  (rc, mid) = client.publish('LED/' + str(identifier), payload=str(color[1]), qos=1)
    (rc, mid) = client.publish('LED/' + str(identifier), payload=str(hexa[1:]), qos=1)
    try:
        coloring(identifier, hexa)
    except:
        coloring(identifier, '#FFFFFF')


def coloring(identifier, hexa):
    # if identifier == 101:
    #     button101.configure(background=hexa, selectcolor=hexa)
    # if identifier == 201:
    #     button201.configure(background=hexa, selectcolor=hexa)
    if identifier == 301:
        button301.configure(background=hexa, selectcolor=hexa)
    if identifier == 401:
        button401.configure(background=hexa, selectcolor=hexa)
    if identifier == 501:
        button501.configure(background=hexa, selectcolor=hexa)
    if identifier == 601:
        button601.configure(background=hexa, selectcolor=hexa)
    if identifier == 701:
        button701.configure(background=hexa, selectcolor=hexa)
    if identifier == 801:
        button801.configure(background=hexa, selectcolor=hexa)
    if identifier == 901:
        button901.configure(background=hexa, selectcolor=hexa)
    if identifier == 1001:
        button1001.configure(background=hexa, selectcolor=hexa)
    if identifier == 1101:
        button1101.configure(background=hexa, selectcolor=hexa)
    if identifier == 1201:
        button1201.configure(background=hexa, selectcolor=hexa)

    # if identifier == 102:
    #     button102.configure(background=hexa, selectcolor=hexa)
    # if identifier == 103:
    #     button103.configure(background=hexa, selectcolor=hexa)
    # if identifier == 104:
    #     button104.configure(background=hexa, selectcolor=hexa)
    # if identifier == 105:
    #     button105.configure(background=hexa, selectcolor=hexa)
    # if identifier == 106:
    #     button106.configure(background=hexa, selectcolor=hexa)
    # if identifier == 107:
    #     button107.configure(background=hexa, selectcolor=hexa)
    # if identifier == 108:
    #     button108.configure(background=hexa, selectcolor=hexa)
    #
    # if identifier == 1202:
    #     button1202.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1203:
    #     button1203.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1204:
    #     button1204.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1205:
    #     button1205.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1206:
    #     button1206.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1207:
    #     button1207.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1208:
    #     button1208.configure(background=hexa, selectcolor=hexa)


    if identifier == 1006:
        button1006.configure(background=hexa, selectcolor=hexa)

    # if identifier == 107:
    #     button107.configure(background=hexa, selectcolor=hexa)
    if identifier == 207:
        button207.configure(background=hexa, selectcolor=hexa)
    if identifier == 307:
        button307.configure(background=hexa, selectcolor=hexa)
    if identifier == 407:
        button407.configure(background=hexa, selectcolor=hexa)
    if identifier == 507:
        button507.configure(background=hexa, selectcolor=hexa)
    if identifier == 607:
        button607.configure(background=hexa, selectcolor=hexa)
    if identifier == 707:
        button707.configure(background=hexa, selectcolor=hexa)
    if identifier == 807:
        button807.configure(background=hexa, selectcolor=hexa)
    if identifier == 907:
        button907.configure(background=hexa, selectcolor=hexa)
    if identifier == 1007:
        button1007.configure(background=hexa, selectcolor=hexa)
    if identifier == 1107:
        button1107.configure(background=hexa, selectcolor=hexa)
    # if identifier == 1207:
    #     button1207.configure(background=hexa, selectcolor=hexa)





def function():
    selection = var.get()
    datageneration(selection)
    # if selection == 101:
    #     datageneration(selection)
    #
    # if selection == 201:
    #     datageneration(selection)
    #
    # if selection == 301:
    #     datageneration(selection)
    #
    # if selection == 401:
    #     datageneration(selection)
    #
    # if selection == 501:
    #     datageneration(selection)
    #
    # if selection == 601:
    #     datageneration(selection)
    #
    # if selection == 701:
    #     datageneration(selection)
    #
    # if selection == 801:
    #     datageneration(selection)
    #
    # if selection == 901:
    #     datageneration(selection)
    #
    # if selection == 1001:
    #     datageneration(selection)
    #
    # if selection == 1101:
    #     datageneration(selection)
    #
    # if selection == 1201:
    #     datageneration(selection)
    #
    #
    # if selection == 102:
    #     datageneration(selection)
    #
    # if selection == 103:
    #     datageneration(selection)
    #
    # if selection == 104:
    #     datageneration(selection)
    #
    # if selection == 105:
    #     datageneration(selection)
    #
    # if selection == 106:
    #     datageneration(selection)
    #
    # if selection == 107:
    #     datageneration(selection)
    #
    # if selection == 108:
    #     datageneration(selection)
    #
    #
    # if selection == 1202:
    #     datageneration(selection)
    #
    # if selection == 1203:
    #     datageneration(selection)
    #
    # if selection == 1204:
    #     datageneration(selection)
    #
    # if selection == 1205:
    #     datageneration(selection)
    #
    # if selection == 1206:
    #     datageneration(selection)
    #
    # if selection == 1207:
    #     datageneration(selection)
    #
    # if selection == 1208:
    #     datageneration(selection)



def gui_buttons(bcolor=None):
    # global button101
    # button101 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 101, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    # button101.place(x=1*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)
    #
    # global button201
    # button201 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 201, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    # button201.place(x=2*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button301
    button301 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 301, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button301.place(x=3*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button401
    button401 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 401, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button401.place(x=4*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button501
    button501 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 501, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button501.place(x=5*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button601
    button601 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 601, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button601.place(x=6*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button701
    button701 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 701, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button701.place(x=7*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button801
    button801 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 801, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button801.place(x=8*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button901
    button901 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 901, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button901.place(x=9*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button1001
    button1001 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1001, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button1001.place(x=10*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button1101
    button1101 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1101, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button1101.place(x=11*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button1201
    button1201 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1201, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button1201.place(x=12*ledbandwidth_hori*xpositionfactor+xpositionshift, y=1*ledbandheight_hori*ypositionfactor+ypositionshift)


    # global button102
    # button102 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 102, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button102.place(x=1*ledbandwidth_verti, y=2*ledbandheight_verti)
    #
    # global button103
    # button103 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 103, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button103.grid(column=1, row=3, sticky=tk.W)
    #
    # global button104
    # button104 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 104, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button104.grid(column=1, row=4, sticky=tk.W)
    #
    # global button105
    # button105 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 105, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button105.grid(column=1, row=5, sticky=tk.W)
    #
    # global button106
    # button106 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 106, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button106.grid(column=1, row=6, sticky=tk.W)
    #
    # global button107
    # button107 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 107, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button107.grid(column=1, row=7, sticky=tk.W)
    #
    # global button108
    # button108 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 108, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button108.grid(column=1, row=8, sticky=tk.W)
    #
    #
    # global button1202
    # button1202 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1202, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1202.grid(column=12, row=2, sticky=tk.E)
    #
    # global button1203
    # button1203 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1203, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1203.grid(column=12, row=3, sticky=tk.E)
    #
    # global button1204
    # button1204 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1204, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1204.grid(column=12, row=4, sticky=tk.E)
    #
    # global button1205
    # button1205 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1205, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1205.grid(column=12, row=5, sticky=tk.E)
    #
    # global button1206
    # button1206 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1206, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1206.grid(column=12, row=6, sticky=tk.E)
    #
    # global button1207
    # button1207 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1207, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1207.grid(column=12, row=7, sticky=tk.E)
    #
    # global button1208
    # button1208 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1208, height=int(ledbandheight_verti), width=int(ledbandwidth_verti), indicatoron=0, command = function)
    # button1208.grid(column=12, row=8, sticky=tk.E)

    global button1006
    button1006 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1006, height=int((ledbandheight_hori+ledbandwidth_hori)/4), width=int((ledbandheight_hori+ledbandwidth_hori)/2), indicatoron=0, command = function)
    button1006.place(x=10*ledbandwidth_hori*xpositionfactor+xpositionshift+30, y=6*ledbandheight_hori*ypositionfactor+ypositionshift+30)


    # global button107
    # button107 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 107, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    # button107.place(x=1*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button207
    button207 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 207, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button207.place(x=2*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button307
    button307 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 307, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button307.place(x=3*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button407
    button407 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 407, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button407.place(x=4*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button507
    button507 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 507, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button507.place(x=5*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button607
    button607 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 607, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button607.place(x=6*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button707
    button707 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 707, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button707.place(x=7*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button807
    button807 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 807, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button807.place(x=8*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button907
    button907 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 907, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button907.place(x=9*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button1007
    button1007 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1007, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button1007.place(x=10*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    global button1107
    button1107 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1107, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    button1107.place(x=11*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)

    # global button1207
    # button1207 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1207, height=int(ledbandheight_hori), width=int(ledbandwidth_hori), indicatoron=0, command = function)
    # button1207.place(x=12*ledbandwidth_hori*xpositionfactor+xpositionshift, y=7*ledbandheight_hori*ypositionfactor+ypositionshift)



bcolor = {}

root = tk.Tk()
var = tk.IntVar()
root.title('CLR - Central LED Regulation')
root.geometry(str(int(roomsize[0] * sizefactor)) + 'x' + str(int(roomsize[1] * sizefactor)))

client = mqtt.Client(client_id='gui', clean_session=True, userdata=None, protocol=mqtt.MQTTv311, transport="tcp")
client.username_pw_set('$username', '$password')
client.connect('$serveradresse', 1883, 60)

gui_buttons()

client.on_connect = on_connect
client.on_message = on_message


client.loop_start()
tk.mainloop()

# cxfreeze ../../../Python_to_exe_stuff/start.py --target-dir ../../../Python_to_exe_stuff/dist