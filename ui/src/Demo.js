import React, { Component } from "react";
import Chessboard from "chessboardjsx";
const io = require('socket.io-client/dist/socket.io');
// const socket = io("http://0.0.0.0:5000", {
//   transports: ['websocket']
// });
const socket = io("http://0.0.0.0:5000");

class Demo extends Component {

  state = {
    position: "3B4/2b2pn1/P3p3/7p/1P1k3P/R4K1b/3P2r1/1N6"
  };

  componentDidMount() {
    // Called when the board loads first
    console.log("DID MOUNT");
    socket.on("connection", () => console.log("al"));
    socket.on("o", pos => console.log(pos));//this.haveNewPosition(pos));
  }

  render() {
    const { position } = this.state;
    return (
      <div style={boardsContainer}>
          <Chessboard
            id="board1"
            position={position}
            width={ window.innerWidth * 0.5}
            onDrop={() => {}}
            boardStyle={boardStyle}
            orientation="black"
          />
      </div>
    );
  }

  haveNewPosition(position) {
    console.log(position);
    this.setState({ position: position.fen });
  }
}

export default Demo;

const boardsContainer = {
  display: "flex",
  justifyContent: "space-around",
  alignItems: "center"
};
const boardStyle = {
  borderRadius: "5px",
  boxShadow: `0 5px 15px rgba(0, 0, 0, 0.5)`
};
