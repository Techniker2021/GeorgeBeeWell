from ttn import MQTTClient as ttn_mqtt
import paho.mqtt.client as paho_mqtt
import time
import datetime
from random import randint
import json
import collections
import ttn
import os

###########################################################
#Ab hier Global gueltiger Shit
###########################################################

messwert = 999
msgTime = 0
filename = 'temperature.txt' #Dateiname fuer Daten

ttn_app_id         = "george_beewell"
ttn_access_key     = "ttn-account-v2.5qJ877-eemTyjsub2GmKLzfWeJeNB0ja-96Oqq9KSKI"

###########################################################
#Ab hier ttn 2 mqtt 2 file
###########################################################

def uplink_callback(msg, client):
  #print(msg)
  messwert = msg.payload_fields.weight
  messwert = messwert.split(",")
  messwert = messwert[2]
  messwert = messwert
  msgTime = msg.metadata.time
  msgTime = msgTime.replace("T", " ")
  msgTime = msgTime.replace("Z", "")
  msgTime = msgTime[:msgTime.rfind(".")]
  msgTimeConv = datetime.datetime.strptime(msgTime, "%Y-%m-%d %H:%M:%S")
  msgTime = msgTime.split(" ")
  #timex = msgTime[1].split(":")
  #print(type(timex[0]))
  #timex[0] = timex[0]+2
  #msgTime[1]=timex[0]+":"+timex[1]+":"+timex[2]
  #print(msgTime)
  f=open(filename,"a")
  f.write(str(msgTime[0])+"; "+str(msgTime[1])+"; "+str(messwert)+"\n")
  print("\nNachricht von Geraet: "+msg.dev_id+"\nTTN-Application: GeorgeBeeWell\n\nTemperature: "+messwert+"\nam: "+msgTime[0]+"\num: "+msgTime[1]+" Uhr\n")
  f.close()

while True:
    handler = ttn.HandlerClient(ttn_app_id, ttn_access_key)
    mqtt_client = handler.data()
    mqtt_client.set_uplink_callback(uplink_callback)
    mqtt_client.connect()
    time.sleep(60)
    mqtt_client.close()
    time.sleep(3)
