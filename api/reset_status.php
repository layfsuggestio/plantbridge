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


$sql = "UPDATE `requested_status` SET `value` = '0' WHERE `requested_status`.`id` = 1;";

if ($conn->query($sql) === TRUE) {
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>

