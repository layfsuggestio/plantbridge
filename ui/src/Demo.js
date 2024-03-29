import React, {Component} from "react";
import Chessboard from "chessboardjsx";
import bB from "./imgs/bB.png";
import bK from "./imgs/bK.png";
import bN from "./imgs/bN.png";
import bP from "./imgs/bP.png";
import bQ from "./imgs/bQ.png";
import bR from "./imgs/bR.png";

import wB from "./imgs/wB.png";
import wK from "./imgs/wK.png";
import wN from "./imgs/wN.png";
import wP from "./imgs/wP.png";
import wQ from "./imgs/wQ.png";
import wR from "./imgs/wR.png";

class Demo extends Component {

    state = {
        position: "start"
    };

    componentDidMount() {
        // Called when the board loads first
    }

    componentWillMount() {
        this.getData()
    }

    getData() {
        // create a new XMLHttpRequest
        var xhr = new XMLHttpRequest();

        // get a callback when the server responds
        xhr.addEventListener('load', () => {
            this.haveNewPosition(JSON.parse(xhr.responseText));
        });
        // open the request with the verb and the url
        xhr.open('GET', 'http://localhost:5000/position');
        // send the request
        xhr.send()
    }

    render() {
        setTimeout(this.getData.bind(this), 1000);
        const {position} = this.state;
        return (
            <div>
            <div style={boardsContainer}>
                <Chessboard
                    id="board1"
                    position={position}
                    width={window.innerWidth * 0.5}
                    onDrop={() => {
                    }}
                    boardStyle={boardStyle}
                    orientation="black"
                    pieces={{
                        wB: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wB}
                                alt={"wB"}
                            />
                        ),
                        wK: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wK}
                                alt={"wK"}
                            />
                        ),
                        wN: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wN}
                                alt={"wN"}
                            />
                        ),
                        wP: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wP}
                                alt={"wP"}
                            />
                        ),
                        wQ: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wQ}
                                alt={"wQ"}
                            />
                        ),
                        wR: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={wR}
                                alt={"wR"}
                            />
                        ),
                        bB: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bB}
                                alt={"bB"}
                            />
                        ),
                        bK: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bK}
                                alt={"bK"}
                            />
                        ),
                        bN: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bN}
                                alt={"bN"}
                            />
                        ),
                        bP: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bP}
                                alt={"bP"}
                            />
                        ),
                        bQ: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bQ}
                                alt={"bQ"}
                            />
                        ),
                        bR: ({squareWidth, isDragging}) => (
                            <img
                                style={{
                                    width: isDragging ? squareWidth * 1.75 : squareWidth,
                                    height: isDragging ? squareWidth * 1.75 : squareWidth
                                }}
                                src={bR}
                                alt={"bR"}
                            />
                        )
                    }}
                />
            </div>
                <button style={buttonStyle} onClick={()=>{
                    // create a new XMLHttpRequest
                    var xhr = new XMLHttpRequest();
                    // // get a callback when the server responds
                    xhr.addEventListener('load', () => {
                        console.log(JSON.parse(xhr.responseText));
                    });
                    // open the request with the verb and the url
                    xhr.open('GET', 'http://localhost:5000/new_game');
                    // send the request
                    xhr.send()
                }}>Start Game</button>
        </div>
        );
    }

    haveNewPosition(position) {
        // console.log(position);
        this.setState({position: position.fen});
    }
}

export default Demo;

const buttonStyle = {
    alignItems: "center",
};

const boardsContainer = {
    display: "flex",
    justifyContent: "space-around",
    alignItems: "center",
};
const boardStyle = {
    borderRadius: "5px",
    boxShadow: `0 5px 15px rgba(0, 0, 0, 0.5)`
};
