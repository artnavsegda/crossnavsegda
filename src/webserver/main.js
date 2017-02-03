console.log("hello javascript");
var xhttp = new XMLHttpRequest();
//xhttp.open("LOL", "getopt", false);
//xhttp.setRequestHeader("Content-type", "text/plain");
//xhttp.send("hello my name is jack");
//console.log(xhttp.responseText);

function fillform()
{
        var something = ["ip","mac","sll","cdl","cel","zdl","ztl","prg","tdl","tml","edl","eml","rcl","cal","pcl"];
        for (var i = 0; i < something.length; i++)
        {
                xhttp.open("LOL", "getopt", false);
                xhttp.send(something[i]);
                document.forms["settings"][something[i]].value = xhttp.responseText;
        }



        //xhttp.send("ip");
        //document.forms["settings"]["ip"].value = xhttp.responseText;
        //xhttp.open("LOL", "getopt", false);
        //xhttp.send("mac");
        //document.forms["settings"]["mac"].value = xhttp.responseText;
        return false;
}
