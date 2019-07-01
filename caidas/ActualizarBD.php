<?php include ('functions.php');

$ESTADO=$_GET['Estado'];


$x=ejecutarSQLCommand("UPDATE `Dispositivos` SET `Estado` = '$ESTADO' WHERE `Dispositivos`.`ID` = 1;" );
echo "$x";
 ?>