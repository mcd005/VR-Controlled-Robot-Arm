from flask import Flask, render_template, request

app = Flask(__name__)

json = ''

ser = serial.Serial(port = "/dev/ttyACM0", baudrate = 9600, timeout = 1.0)

print("script was run")

# receiving a post request
@app.route('/', methods=['POST', 'GET'])
def changeIndex():
    if request.method == 'POST':
        global json
        json = request.get_json()
        print ("received POST request")
        print ("test: ", json)
        ser.write(json)
    else :
        print ("nothing was sent")
        return json
    return json

# test if we send data
@app.route('/test')
def getRequest():
    print ("helllllooooo")
    return "hello"


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = 5000, debug=True)
