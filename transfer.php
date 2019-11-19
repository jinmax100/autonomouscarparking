<?php

$db_name = "mcparking";
$user = "root";
$password = "";
$host = "localhost";

$con = mysqli_connect($host,$user,$password);
$dbselect = mysqli_select_db($con, "mcparking");

$slotnumber = $_GET['slotnumber'];

if ($slotnumber == '1') {
    $q1 = "INSERT INTO users (slotnumber) 
            VALUES ('1')";
}

else if ($slotnumber == '5') {
    $q1 = "DELETE FROM users WHERE slotnumber='1'";
}



if ($slotnumber == '2') {
    $q1 = "INSERT INTO users (slotnumber) 
            VALUES ('2')";
}

else if ($slotnumber == '6') {
    $q1 = "DELETE FROM users WHERE slotnumber='2'";
}



if ($slotnumber == '3') {
    $q1 = "INSERT INTO users (slotnumber) 
            VALUES ('3')";
}

else if ($slotnumber == '7') {
    $q1 = "DELETE FROM users WHERE slotnumber='3'";
}



if ($slotnumber == '4') {
    $q1 = "INSERT INTO users (slotnumber) 
            VALUES ('4')";
}

else if ($slotnumber == '8') {
    $q1 = "DELETE FROM users WHERE slotnumber='4'";
}

mysqli_query($con, $q1);

?>
