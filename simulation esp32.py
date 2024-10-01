from flask import Flask, jsonify, request

app = Flask(__name__)

# Define a basic route
@app.route('/')
def home():
    return "Hello, Flask!"

# Define a simple API endpoint
@app.route('/trigger', methods=['POST'])
def api():
    return "success",200

if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port=80)
