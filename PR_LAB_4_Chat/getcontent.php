<?php 
$offset = (!isset($_GET['offset']) || !$_GET['offset']) ? 0: $_GET['offset'];
$filename = "chat.txt";
$content = file_get_contents($filename, FALSE, NULL, $offset);
echo $content;
?>