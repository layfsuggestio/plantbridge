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

$sql = "SELECT value FROM requested_status";
$result = $conn->query($sql);


if (mysqli_num_rows($result) > 0) {
    // output data of each row
    while($row = mysqli_fetch_assoc($result)) {
	echo($row["value"]);
    }
} else {
    echo "0 results";
}

$conn->close();
?>

