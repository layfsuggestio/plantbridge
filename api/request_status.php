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

$sql = "SELECT lastplay, takenfigure FROM game_state";
$result = $conn->query($sql);
$row = mysqli_fetch_assoc($result);
$lp = $row["lastplay"];
$tf = $row["takenfigure"];

$sql = "SELECT value FROM requested_status";
$result = $conn->query($sql);
$row = mysqli_fetch_assoc($result);
$v1 = $row["value"];

echo($v1 . $lp . $tf);

$conn->close();
?>

