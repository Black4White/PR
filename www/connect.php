<!DOCTYPE html>
    <html>
<?php 
session_start();
if (isset($_POST['name']) && $_POST['name']) {
	$_SESSION["username"]=$_POST['name'];
}elseif(!isset($_SESSION["username"]) || !$_SESSION["username"]){
	$_SESSION["username"]="Anon".date('dhns');
}
?>
  <frameset rows="*,80" cols="*">
    <frame src="top.php" border="1" name="top">
    <frame src="bottom.php" border="1" name="bottom">
  </frameset>
 </html>
