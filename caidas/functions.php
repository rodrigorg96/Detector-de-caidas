<?php 
header( 'Content-Type: text/html;charset=utf-8' );
  

function ejecutarSQLCommand($commando){
  $user="2847813_seisai";
  $pass="22830rodrigo69229";
  $server="fdb23.runhosting.com";
  $db="2847813_seisai";
  $con=new mysqli($server,$user,$pass,$db);
  if ($con->connect_error) {
    die("Connection failed: " . $con->connect_error);
} 
/* check connection */
else if ( $con->query($commando)===TRUE) {
  return "Actualizado";  
}
else {
    return "Error: ". $sql . "<br>" . $con->error;
}

$con->close();
}

function getSQLResultSet($commando){
  $user="2847813_seisai";
  $pass="22830rodrigo69229";
  $server="fdb23.runhosting.com";
  $db="2847813_seisai";
 $mysqli = new mysqli($server,$user,$pass,$db);
/* check connection */
if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}

if ( $mysqli->multi_query($commando)) {
	return $mysqli->store_result();   
}
$mysqli->close();
}
?>
