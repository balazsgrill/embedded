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
html, body{
    height: 100%;  
}

a.button{
  background-color : #aaa;
  display: inline-block;
  width: 45%;
  height: 30%;
  margin: 5px;
}
</style>
</head>
<body>
<a class="button" href="?actionid=0"> 0% </a>
<a class="button" href="?actionid=1"> 25% </a>
<br>
<a class="button" href="?actionid=2"> 50% </a>
<a class="button" href="?actionid=3"> 100% </a>
<br>
<a class="button" href="?actionid=4"> ON </a>
<a class="button" href="?actionid=5"> OFF </a>

</body>
</html>
