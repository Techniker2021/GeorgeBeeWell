import logging
import os
#import telegram
from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram.ext import MessageHandler, Filters

filename = "/home/pi/GeorgeBeeWell/temperature.txt" #Dateiname fuer Daten
#2019-06-11; 17:56:53; 22.12

print("Bot started")
updater = Updater(token="YOUR-TELEGRAM-BOT-TOKEN", use_context=True)
dispatcher = updater.dispatcher

logging.basicConfig(format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",level=logging.INFO)

def start(update, context):
    print("Bot-registration from: " + str(update.message.chat.first_name)+"\n")
    context.bot.send_message(chat_id=update.message.chat_id, text="Hi! Ich bin George BeeWell. Du kannst nach der aktuellen Temperatur fragen. Schreib einfach /temperature")

def temperature(update, context):
    print("Anfrage von: " + str(update.message.chat.first_name))
    f = open(filename,"r")
    lineList = f.readlines()
    print(lineList[-1])
    fString = lineList[-1]
    f.close()
    fString = fString.split(";")
    message = "Aktuelle Temperatur:\t\t" + fString[2] + "am:\t\t" + fString[0] + "\num:" +fString[1] + " Uhr"
    context.bot.send_message(chat_id=update.message.chat_id, text=message)
    
temperature_handler = CommandHandler("temperature", temperature)
dispatcher.add_handler(temperature_handler)

start_handler = CommandHandler("start", start)
dispatcher.add_handler(start_handler)

updater.start_polling()
