console.log("hello javascript");
var xhttp = new XMLHttpRequest();
xhttp.open("LOL", "special", false);
xhttp.setRequestHeader("Content-type", "text/plain");
xhttp.send("hello my name is jack");
console.log(xhttp.responseText);

function fillform()
{
        document.forms["settings"]["data"].value = "bullshit";
        return false;
}
