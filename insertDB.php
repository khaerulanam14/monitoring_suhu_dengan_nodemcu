<?php
error_reporting(E_ALL ^ (E_NOTICE | E_WARNING));
//Connect to database
    $hostname = "localhost";      
    $username = "root";     
    $password = ""; 

    // Create connection
    $conn = mysqli_connect($hostname, $username, $password)or die("Could not connect");
    $db = mysqli_select_db( $conn,"data_sensor")or die("Could not select database");
    // Check connection
    if (mysqli_connect_errno())
    {
        echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }

    //Get current date and time
    
    $date= date("Y-m-d");
    $time = time("H:i:s");

    $humid = $_POST['humidity'];
        $temp = $_POST['temperature'];
    $sql = "INSERT INTO dht11 (humidity, temperature, time, date) VALUES ('$humid', '$temp', '$time', '$date')"; //nodemcu_ldr_table = Youre_table_name
        $result = mysqli_query( $conn,$sql) or die("Query failed");

         if ($result)
         echo " OK";        

        else
         echo "Problem occured !";

    mysqli_close($conn);
?>