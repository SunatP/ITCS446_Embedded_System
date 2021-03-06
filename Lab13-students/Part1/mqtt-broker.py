import paho.mqtt.client as mqtt
from pymongo import MongoClient 
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("esp32/temperature")
    client.subscribe("esp32/humidity")


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload,'utf-8'))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.43.65", 1883, 60)

client.loop_forever()