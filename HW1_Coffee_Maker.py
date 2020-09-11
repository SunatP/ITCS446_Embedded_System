from gpio import *
from time import *


def main():
    while True:
        motion_sensor = digitalRead(9)
        if motion_sensor == HIGH:
            print("something is moving")
            print("Turn-on")
            customWrite(1,1);
            customWrite(2,2);
            delay(3000)
            print("Turn-off")
            customWrite(1,0);
            customWrite(2,0);
        delay(500)


if __name__ == "__main__":
    main()
