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

$stocknorm = 29348.1;
$stockhalf = 0.6;
$st = $st/$stocknorm;
$st = $st-$stockhalf;
$d = ($hu + 1024 - $li - abs($tm-800))/3/1024;

echo($d . "\r\n" .  $st);

$conn->close();
?>

