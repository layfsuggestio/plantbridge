from flask import Flask
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET KEY'] = 'very_secret'

socketio = SocketIO(app, cors_allowed_origins="*")

position = {
	"o": "start"
}

@socketio.on('connection')
def client_connection():
    print("Client connected")
    # emit('position', position)

@socketio.on('disconnect')
def client_disconnect():
    print("Client disconnected")

@socketio.on("position")
def position(data):    
    emit('position', position, broadcast=True	)

if __name__ == '__main__':
    app.debug = True
    socketio.run(app, port=5000)