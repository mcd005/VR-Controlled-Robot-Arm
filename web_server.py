from flask import Flask, render_template, request

app = Flask(__name__)

test = ''

print("script was run")

# receiving a post request
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

# test if we send data
@app.route('/test')
def getRequest():
    print ("helllllooooo")
    return "hello"


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = 5000, debug=True)