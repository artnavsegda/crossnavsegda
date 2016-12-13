#/bin/bash
(stty raw; cat > record.txt) < /dev/ttyACM0 

