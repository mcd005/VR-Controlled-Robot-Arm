from flask import Flask, render_template, request

app = Flask(__name__)

<<<<<<< HEAD
json = ''

ser = serial.Serial(port = "/dev/ttyACM0", baudrate = 9600, timeout = 1.0)
=======
test = ''
>>>>>>> Kobe-68_ChansisBaseBranch

print("script was run")

# receiving a post request
<<<<<<< HEAD
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
=======
@app.route('/', methods=['POST', 'GET']) 
def changeIndex():
    if request.method == 'POST':
        global test 
        test = request.get_json()
        print ("received POST request")
        print ("test: ", test)
    else :
        print ("nothing was sent")
        return test
    return test
>>>>>>> Kobe-68_ChansisBaseBranch

# test if we send data
@app.route('/test')
def getRequest():
    print ("helllllooooo")
    return "hello"


if __name__ == '__main__':
<<<<<<< HEAD
    app.run(host = '0.0.0.0', port = 5000, debug=True)
=======
    app.run(host = '0.0.0.0', port = 5000, debug=True)
>>>>>>> Kobe-68_ChansisBaseBranch
