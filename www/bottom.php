<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
    <head>
        <title>bottom</title>
		<meta charset="UTF-8">
    </head>
<?php 
session_start();


if (isset($_POST['mess']) && $_POST['mess']) {
	$mess=$_SESSION['username'].":\n".$_POST['mess']."\n\n";
	$filename = "chat.txt";
	$fh = fopen($filename, "a");
	$fwrite = fwrite($fh, $mess);
	fclose($fh);	
}
?>	
<body>
	<center>	
<?=$_SESSION['username']?>:<br>
	<form action="bottom.php" method="post">
		<textarea rows="2" cols="120" name="mess" id="mess"></textarea>
		<input type="submit">
		<input type="button" value="Clear" OnClick="window.open('new.php','_self');">
		<form name="form1" action="chernovik.php" enctype="multipart/form-data" method="post">
		<input type="file" name="path" title="Выберите файл"/> </br>
</br>
<input type="submit" name="button" /> </br>
	</form>
<script type="text/javascript">
document.getElementById("mess").focus();
</script>
</center>
</body>
</html>
