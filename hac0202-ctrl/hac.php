<?php
switch($_GET["actionid"]){
  case "0":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 1 0");
  break;
  case "1":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 1 64");
  break;
  case "2":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 1 128");
  break;
  case "3":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 1 255");
  break;
  case "4":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 0 8");
  break;
  case "5":
    exec("/home/cubie/git/embedded/hac0202-ctrl/bin/hac0202ctrl 0 4");
  break;  
}
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>HAC controller</title>
<style>
a.button{
  background-color : #aaa;
  width: 70px;
  height: 70px;
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



{{button label=" 0% " action="hac0202ctrl 1 0"}}
{{button label=" 25% " action="hac0202ctrl 1 64"}}
{{button label=" 50% " action="hac0202ctrl 1 128"}}
{{button label=" 100% " action="hac0202ctrl 1 255"}}
<br>
{{button label=" ON " action="hac0202ctrl 0 8"}}
{{button label=" OFF " action="hac0202ctrl 0 4"}}

</body>
</html>
