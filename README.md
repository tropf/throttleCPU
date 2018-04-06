# throttleCPU
Set Max CPU Clock Speed on Laptops Depending on their charging status.

Buying very cheap Batterys can result in voltage drops on full CPU load. So I had the problem that Compiling, Updating, or just starting a browser made my laptop turn of instantly. Throttling CPU Clock Speed prevents that problem.

throttleCPU reads /etc/throttleCPU.conf and needs those parameters:<br>
DISCHARGE [VALUE]<br>
CHARGE [VALUE]<br>
REPEAT [VALUE]<br>
Where DISCHARGE and CHARGE are Integer values presenting Hz.<br>
REPEAT is an Integer value representing seconds.
throttleCPU will check charging status every REPEAT-Seconds

# BUILD
```git clone https://github.com/k4lipso/throttleCPU```<br>
```cd throttleCPU```<br>
```mkdir build; cd build```<br>
```cmake ..```<br>
```make```<br>
```make install```<br>

# USAGE
```systemctl daemon-reload```<br>
```systemctl start/enable throttleCPU```

Made on Archlinux, shoud work on other Distos too.
