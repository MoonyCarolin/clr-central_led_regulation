import tkinter as tk
import paho.mqtt.client as mqtt
import tkcolorpicker





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
  #  print(hexa)
   # print(hexa[1:])
  #  (rc, mid) = client.publish('LED/' + str(identifier), payload=str(color[1]), qos=1)
    (rc, mid) = client.publish('LED/' + str(identifier), payload=str(hexa[1:]), qos=1)
    coloring(identifier, hexa)


def coloring(identifier, hexa):
    if identifier == 101:
        button101.configure(background=hexa, selectcolor=hexa)
    if identifier == 201:
        button201.configure(background=hexa, selectcolor=hexa)
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


    if identifier == 102:
        button102.configure(background=hexa, selectcolor=hexa)
    if identifier == 103:
        button103.configure(background=hexa, selectcolor=hexa)
    if identifier == 104:
        button104.configure(background=hexa, selectcolor=hexa)
    if identifier == 105:
        button105.configure(background=hexa, selectcolor=hexa)
    if identifier == 106:
        button106.configure(background=hexa, selectcolor=hexa)
    if identifier == 107:
        button107.configure(background=hexa, selectcolor=hexa)
    if identifier == 108:
        button108.configure(background=hexa, selectcolor=hexa)

    if identifier == 1202:
        button1202.configure(background=hexa, selectcolor=hexa)
    if identifier == 1203:
        button1203.configure(background=hexa, selectcolor=hexa)
    if identifier == 1204:
        button1204.configure(background=hexa, selectcolor=hexa)
    if identifier == 1205:
        button1205.configure(background=hexa, selectcolor=hexa)
    if identifier == 1206:
        button1206.configure(background=hexa, selectcolor=hexa)
    if identifier == 1207:
        button1207.configure(background=hexa, selectcolor=hexa)
    if identifier == 1208:
        button1208.configure(background=hexa, selectcolor=hexa)


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
    global button101
    button101 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 101, height=1, width=10, indicatoron=0, command = function)
    button101.grid(column=1, row=1)

    global button201
    button201 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 201, height=1, width=10, indicatoron=0, command = function)
    button201.grid(column=2, row=1)

    global button301
    button301 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 301, height=1, width=10, indicatoron=0, command = function)
    button301.grid(column=3, row=1)

    global button401
    button401 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 401, height=1, width=10, indicatoron=0, command = function)
    button401.grid(column=4, row=1)

    global button501
    button501 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 501, height=1, width=10, indicatoron=0, command = function)
    button501.grid(column=5, row=1)

    global button601
    button601 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 601, height=1, width=10, indicatoron=0, command = function)
    button601.grid(column=6, row=1)

    global button701
    button701 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 701, height=1, width=10, indicatoron=0, command = function)
    button701.grid(column=7, row=1)

    global button801
    button801 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 801, height=1, width=10, indicatoron=0, command = function)
    button801.grid(column=8, row=1)

    global button901
    button901 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 901, height=1, width=10, indicatoron=0, command = function)
    button901.grid(column=9, row=1)

    global button1001
    button1001 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1001, height=1, width=10, indicatoron=0, command = function)
    button1001.grid(column=10, row=1)

    global button1101
    button1101 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1101, height=1, width=10, indicatoron=0, command = function)
    button1101.grid(column=11, row=1)

    global button1201
    button1201 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1201, height=1, width=10, indicatoron=0, command = function)
    button1201.grid(column=12, row=1)


    global button102
    button102 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 102, height=4, width=2, indicatoron=0, command = function)
    button102.grid(column=1, row=2, sticky=tk.W)

    global button103
    button103 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 103, height=4, width=2, indicatoron=0, command = function)
    button103.grid(column=1, row=3, sticky=tk.W)

    global button104
    button104 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 104, height=4, width=2, indicatoron=0, command = function)
    button104.grid(column=1, row=4, sticky=tk.W)

    global button105
    button105 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 105, height=4, width=2, indicatoron=0, command = function)
    button105.grid(column=1, row=5, sticky=tk.W)

    global button106
    button106 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 106, height=4, width=2, indicatoron=0, command = function)
    button106.grid(column=1, row=6, sticky=tk.W)

    global button107
    button107 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 107, height=4, width=2, indicatoron=0, command = function)
    button107.grid(column=1, row=7, sticky=tk.W)

    global button108
    button108 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 108, height=4, width=2, indicatoron=0, command = function)
    button108.grid(column=1, row=8, sticky=tk.W)


    global button1202
    button1202 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1202, height=4, width=2, indicatoron=0, command = function)
    button1202.grid(column=12, row=2, sticky=tk.E)

    global button1203
    button1203 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1203, height=4, width=2, indicatoron=0, command = function)
    button1203.grid(column=12, row=3, sticky=tk.E)

    global button1204
    button1204 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1204, height=4, width=2, indicatoron=0, command = function)
    button1204.grid(column=12, row=4, sticky=tk.E)

    global button1205
    button1205 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1205, height=4, width=2, indicatoron=0, command = function)
    button1205.grid(column=12, row=5, sticky=tk.E)

    global button1206
    button1206 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1206, height=4, width=2, indicatoron=0, command = function)
    button1206.grid(column=12, row=6, sticky=tk.E)

    global button1207
    button1207 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1207, height=4, width=2, indicatoron=0, command = function)
    button1207.grid(column=12, row=7, sticky=tk.E)

    global button1208
    button1208 = tk.Radiobutton(root, background=bcolor, selectcolor=bcolor, variable = var, value = 1208, height=4, width=2, indicatoron=0, command = function)
    button1208.grid(column=12, row=8, sticky=tk.E)



bcolor = {}

root = tk.Tk()
var = tk.IntVar()
root.title('CLR - Central LED Regulation')

client = mqtt.Client(client_id='gui', clean_session=True, userdata=None, protocol=mqtt.MQTTv311, transport="tcp")
client.username_pw_set('$username', '$password')
client.connect('$serveradress', 1883, 60)

gui_buttons()

client.on_connect = on_connect
client.on_message = on_message
client.loop_start()
tk.mainloop()
