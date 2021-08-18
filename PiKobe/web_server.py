from flask import Flask, render_template, request
import serial
import time
import json

app = Flask(__name__)

jsonData = ''

ser = serial.Serial(port = "/dev/ttyS0", baudrate = 9600, timeout = 1.0)

print("Server is running")

# receiving a post request
@app.route('/', methods=['POST', 'GET'])
def changeIndex():
    if request.method == 'POST':
        jsonData = json.dumps(request.get_json())
        print ("JSON string from Unity: ", jsonData)
        ser.write(jsonData.encode("utf-8"))
    else :
        print ("nothing was sent")
        return jsonData
    return jsonData

# test if we send data
@app.route('/test')
def getRequest():
    print ("helllllooooo")
    return "hello"


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = 5000, debug=True)
