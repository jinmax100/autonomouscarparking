<?php   

$db_name = "mcparking";
$user = "root";
$password = "";
$host = "localhost";

$con = mysqli_connect($host,$user,$password,$db_name);

// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$result = mysqli_query($con,"SELECT value FROM users WHERE id='1'");

while($row = mysqli_fetch_array($result)) {
  echo $row['value'];
  echo "<br>"; 
}

?>
