
def ratio(val: int):
    a:int = val
    b:int = 255
    percentage:int = 100
    sum:float = a / b * percentage
    return sum

print("value is: {0:.2f}%".format(ratio(0)))

print(0/100)