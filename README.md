# GeorgeBeeWell
Basic surveillance of an beehive

Fetch data with an Sparkfun Openscale and Arduino MKRWAN1300 and send it via LoRaWAN through The Things Network (TTN) to an Raspberry Pi.

To gather data from TTN we use MQTT. On the Raspberry are running two Python scripts to access a Textdocument.
One script to write data and the other one is an Telegram-Bot to view current temperature in your favorite chat app.
