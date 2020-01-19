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

$sql = "SELECT * FROM sensor_data ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);
$row = mysqli_fetch_assoc($result);
$hu = $row["humidity"];
$li = $row["light"];
$st = $row["stock"];
$tm = $row["temp"];


echo($hu  . "\r\n" . $li . "\r\n" . $st  . "\r\n" . $tm);

$conn->close();
?>

