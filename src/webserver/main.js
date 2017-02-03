console.log("hello javascript");
var xhttp = new XMLHttpRequest();
xhttp.open("LOL", "getopt", false);
xhttp.setRequestHeader("Content-type", "text/plain");
//xhttp.send("hello my name is jack");
//console.log(xhttp.responseText);

function fillform()
{
        xhttp.send("ip");
        document.forms["settings"]["ip"].value = xhttp.responseText;
        xhttp.open("LOL", "getopt", false);
        xhttp.send("mac");
        document.forms["settings"]["mac"].value = xhttp.responseText;
        return false;
}
