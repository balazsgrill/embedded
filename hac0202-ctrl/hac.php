<?php
switch($_GET["actionid"]){
  case "0":
    exec("/home/cubie/hac0202ctrl 1 0");
  break;
  case "1":
    exec("/home/cubie/hac0202ctrl 1 64");
  break;
  case "2":
    exec("/home/cubie/hac0202ctrl 1 128");
  break;
  case "3":
    exec("/home/cubie/hac0202ctrl 1 255");
  break;
  case "4":
    exec("/home/cubie/hac0202ctrl 0 8");
  break;
  case "5":
    exec("/home/cubie/hac0202ctrl 0 4");
  break;  
}
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>HAC controller</title>
<style>
table{
  position: absolute;
  width: 90%;
  height: 90%;
}
a.button{
  background-color : #aaa;
  display: table;
  position: relative;
  width: 100%;
  height: 100%;
}
</style>
</head>
<body>
<table>
<tr>
<td><a class="button" href="?actionid=0"> 0% </a></td>
<td><a class="button" href="?actionid=1"> 25% </a></td>
</tr>
<tr>
<td><a class="button" href="?actionid=2"> 50% </a></td>
<td><a class="button" href="?actionid=3"> 100% </a></td>
</tr><tr>
<td><a class="button" href="?actionid=4"> ON </a></td>
<td><a class="button" href="?actionid=5"> OFF </a></td>
</tr>
</table>


</body>
</html>
