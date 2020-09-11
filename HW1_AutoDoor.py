# from gpio import *
# from time import *
# from tcp import *

# client = TCPClient()
# g1 = 0

# pinMode(0, IN)
# g1 = digitalRead(0)

# serverIP = "209.165.201.2"
# serverPort = 81

# def onTCPConnection(data):
#     print("Received from: "+ str(data))
#     client.send(data)

# def main():
#     client.onConnectionChange(onTCPConnection)
#     client.onRecieve(onTCPReceive)

#     print(client.connect(serverIP,serverPort))
#     while True:
#         g1 = customRead(0)
#         client.send(g1)
#         print("Door Status: " + g1)
#         delay(1000)

# if __name__ == "__main__":
#     main()

from gpio import *
from time import *

def main():
	pinMode(1, OUT)
	print("Flipping the door closed and open.")
	while True:
		customWrite(0, "1");
		delay(1000)
		customWrite(0, "0");
		delay(1000)

if __name__ == "__main__":
	main()
