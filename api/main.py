from flask import Flask, request, jsonify
import db
from db import create_tables

app = Flask(__name__)
app.config["DEBUG"] = True

@app.route('/', methods=['GET'])
def home():
    return "<h1>Temperture reading api</h1><p>This page is a test api and is not ment for public use.</p>"

@app.route('/temperture', methods=['GET'])
def get_device():
    device = db.get_devices()
    return jsonify(device)

@app.route('/temperture', methods=['POST'])
def insert_device():
    location = request.form["location"]
    reading = request.form["reading"]
    isEmpty = request.form["isEmpty"]
    result = db.insert_device(location, reading, isEmpty)
    return jsonify(result)

@app.errorhandler(404)
def page_not_found(e):
    return "<h1>404</h1><p>The page could not be found.</p>", 404

if __name__ == "__main__":
    db.create_tables()

    app.run()