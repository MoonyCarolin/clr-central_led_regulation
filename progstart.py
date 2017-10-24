import tkinter as tk

import paho.mqtt.client as mqtt
import tkcolorpicker





def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe('LED')
    client.subscribe('LED/#')

def on_message(client, userdata, msg):
    print(msg.topic+' '+str(msg.payload))

def on_publish(client, userdata, mid):
    print('mid: '+str(mid))


def datageneration(identifier):
    color = tkcolorpicker.askcolor()
    print(identifier, color, 'LED/' + str(identifier))
    (rc, mid) = client.publish('LED/' + str(identifier), payload=str(color[1]), qos=1)

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


def gui_buttons():
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


root = tk.Tk()
var = tk.IntVar()
root.title('CLR - Central LED Regulation')


client = mqtt.Client(client_id='gui', clean_session=True, userdata=None, protocol=mqtt.MQTTv311, transport="tcp")
client.username_pw_set('$username', '$password')

client.on_connect = on_connect

client.connect('$serveradresse', 1883, 60)

gui_buttons()

client.on_message = on_message
client.loop_start()
tk.mainloop()
