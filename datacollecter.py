import serial
import time
ser = serial.Serial('/dev/ttyACM0', 9600)
while 1:
	temp=ser.readline()
	
	if(temp):
		fob=open('/var/www/html/date.html', 'w')
		fob.write('<html><head><meta http-equiv="content-type" content="text/html; charset=utf-8" /><link rel="stylesheet" type="text/css" href="css/styled.css" /><meta http-equiv="refresh" content="1;url=date.html"></head><body><center><h3>Temperatura Umiditate Lumina Coordonate x;y<br>' +temp+ '<br> at'+ time	.strftime(' %S %l:%M%p on %b %d, %Y') + '</h3></center></body></html>')	
                fob.close()
