<!DOCTYPE HTML>
    <html>
    <head>
        <title>top</title>
		<meta charset="UTF-8">
    </head>
    <body>
	<center>	
    Message board<hr>
<textarea name="chat" id="chat"  rows="20" cols="80"></textarea>
<script type="text/javascript">
var size = 0;
let timerId = setTimeout(function getmess()
{
	var chat = document.getElementById("chat");
	var x = new XMLHttpRequest();
	x.open("GET", "getcontent.php?offset="+size, true);
	x.onload = function ()
	{
		if (x.responseText)
		{
			chat.value += x.responseText;
			size += x.responseText.length;
		}
	}
	x.send(null);
  timerId = setTimeout(getmess, 1000); // (*)
},
1000);
</script>
	</center>
    </body>
    </html>
