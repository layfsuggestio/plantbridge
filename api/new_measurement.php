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
$tm =  $_GET['temp'];

$response = file_get_contents('https://financialmodelingprep.com/api/v3/majors-indexes');
$response = json_decode($response);

$stk = $response->{'majorIndexesList'}[0]->{'price'};



$sql = "INSERT INTO sensor_data (humidity, light, stock, temp)
VALUES ($hum,$lig,$stk,$tm)";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>

