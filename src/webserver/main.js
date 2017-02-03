console.log("hello javascript");
var xhttp = new XMLHttpRequest();
xhttp.open("LOL", "special", false);
xhttp.setRequestHeader("Content-type", "text/plain");
xhttp.send("hello my name is jack");
console.log(xhttp.responseText);

function fillform()
{
        xhttp.send("ip");
        document.forms["settings"]["ip"].value = xhttp.responseText;
        return false;
}
