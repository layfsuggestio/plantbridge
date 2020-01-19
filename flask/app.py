import flask
from flask import Flask, request, jsonify, after_this_request
import requests
import chess
from pystockfish import *

BOARDFEN = "state"

app = Flask(__name__)

@app.route('/position', methods=['GET'])
def position():
    @after_this_request
    def add_header(response):
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    global BOARDFEN
    jsonResp = {'fen': BOARDFEN}
    print(jsonResp)
    return jsonify(jsonResp)

@app.route('/new_game')
def new_game():
    @after_this_request
    def add_header(response):
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    def _create_match():
	    engines = {
	        # TODO depth 2 only for debugging
	        'player1': Engine(depth=2, rand=False),
	        'player2': Engine(depth=2, rand=False)
	    }
	    m = Match(engines=engines)
	    return m
	
	# request: to endpoint: game start
    requests.get("http://104.198.192.55/api/reset_game.php")
    m = _create_match()
    board = chess.Board()
    gameover = False
    global BOARDFEN

    # TODO update GUI: game starts
    while not gameover:
        # request: from endpoint: skill levels for both players
        plant_skill, stock_skill = requests.get("http://104.198.192.55/api/request_difficulty.php").content.split(b'\r')
        plant_skill, stock_skill = float(plant_skill), float(stock_skill)
        # update skill level
        m.white_engine.setoption("Skill Level", 20 * plant_skill)
        m.black_engine.setoption("Skill Level", 20 * stock_skill)
        
        # make a move
        if not m.move():
            # game ended
            gameover = True
        
        # generate fen, prepare for GUI: sensors & game state
        board.push(chess.Move.from_uci(m.moves[-1]))
        fen = board.fen()
        print(fen, BOARDFEN)
        BOARDFEN = fen
        
        # request: to endpoint: game state   TODO suffix
        requests.get("http://104.198.192.55/api/set_state.php?player=1&lost=1")

        # IF newgame: break
        if 1 == int(requests.get("http://104.198.192.55/api/request_game.php").content):
            break
    return

if __name__ == '__main__':
	app.debug=True
	app.run(port=5000, threaded=True)