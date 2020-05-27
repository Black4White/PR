<!DOCTYPE html>
    <html>
    <head>
        <title>top</title>
		<meta charset="UTF-8"/>
    </head>
<? 
$filename = "chat.txt";
$fh = fopen($filename, "w");
fwrite($fh,"\n");
fclose($fh);
?>	
    <body>
	<center>	
    Message board is clean
<script type="text/javascript">
window.open("connect.php","_parent");
</script>
	</center>
    </body>
    </html>