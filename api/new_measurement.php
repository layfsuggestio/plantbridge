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

$hum =  $_GET['humidity'];
$lig =  $_GET['light'];

$sql = "INSERT INTO sensor_data (humidity, light)
VALUES ($hum,$lig)";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>

