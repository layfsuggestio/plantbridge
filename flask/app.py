import flask
from flask import Flask, request, jsonify, after_this_request

app = Flask(__name__)

@app.route('/hello', methods=['GET'])
def hello():
    @after_this_request
    def add_header(response):
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    jsonResp = {'fen': "6N1/P3R3/3B1p1P/2P3P1/p3K2k/1q6/B1P5/2N2n2"}
    print(jsonResp)
    return jsonify(jsonResp)


if __name__ == '__main__':
	app.debug=True
	app.run(port=5000)