from flask import Flask, render_template, request

app = Flask(__name__)

test = ''

print("hi")

@app.route('/', methods=['POST']) 
def changeIndex():
    if request.method == 'POST':
        global test 
        test = request.get_json()
        print ("received POST request")
        print ("test: ", test)
        return test
    else :
        print 
        return render_template('registration.html')

@app.route('/')
def getRequest():
    print ("helllllooooo")
    return test


if __name__ == '__main__':
    app.run(debug=True)