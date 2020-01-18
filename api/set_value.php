<?php 
   function display() {
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

	$test = $_POST["studentname"];
	$sql = "UPDATE `requested_status` SET `value` = '$test' WHERE `requested_status`.`id` = 1;";

	if ($conn->query($sql) === TRUE) {
	} else {
	    echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();
   }
?>
<html>
    <body>
        <form method="post">
            <input type="text" name="studentname">
            <input type="submit" value="click">
        </form>
        <?php
           display();
        ?>
    </body>
</html>
