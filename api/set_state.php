<?php
$servername = "localhost";
$username = "root";
$password = "abcd1234";
$dbname = "plant_measurements";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$player =  $_GET['player'];
$looser =  $_GET['lost'];
$entry = 1;

if ($player == 0){
    if ($looser == 1){
	$entry = 2;
    }
}
if ($player == 1){
    if ($looser == 1){
	$entry = 0;
    }
}




$sql = "UPDATE `game_state` SET `lastplay` = '$player', `takenfigure` = '$entry' WHERE `game_state`.`id` = 1;";

if ($conn->query($sql) === TRUE) {
    echo "Record updated successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
