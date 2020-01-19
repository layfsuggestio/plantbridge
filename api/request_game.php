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

$sql = "SELECT resetgame FROM requested_restart";
$result = $conn->query($sql);
$row = mysqli_fetch_assoc($result);
$lp = $row["resetgame"];
echo($lp);

$conn->close();
?>

