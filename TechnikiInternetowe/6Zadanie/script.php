<?php
	$f=fopen('dowcipy.txt','r');
	while(!feof($f)){
		$linia = fgets($f);
		echo $linia;
		echo '<br>';
	}
	fclose($f);
?>
