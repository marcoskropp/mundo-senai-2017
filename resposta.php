<?php
   header('Access-Control-Allow-Origin: *');
?>
<?php

$dados = filter_input_array(INPUT_GET, FILTER_DEFAULT);
sleep(1);
echo "Comando: ".$dados['function'];
return;
 ?>
