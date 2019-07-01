<?php
include('functions.php');
try
{
	$resultset=getSQLResultSet("SELECT * FROM `Dispositivos`");
	while ($row = $resultset->fetch_array(MYSQLI_NUM)){
		echo $row [2];
	}
}
catch(Exceptio $e)
{
	echo "Error en consulta: $e";
}
