# throttleCPU
Set max CPU clock speed on laptops depending on their charging status.

Buying very cheap batteries can result in voltage drops on full CPU load.
So I had the problem that compiling, updating,
or just starting a browser made my laptop turn off instantly.
Throttling CPU clock speed prevents that problem.

`throttleCPU` reads `/etc/throttleCPU.conf` and needs those parameters:

> **All values must be integers.**

Parameter   | Description                                            | Unit
---         | ---                                                    | ---
`DISCHARGE` | CPU clock speed when the battery is discharging        | `Hz`
`CHARGE`    | CPU clock speed when the battery is charging           | `Hz`
`REPEAT`    | The charging status is checked every `REPEAT` seconds. | `s`

(The example config)[throttleCPU.conf] (included with the source) contains this:

```
DISCHARGE 1000000
CHARGE 3400000
REPEAT 5
```

> Use `lscpu` to get basic information about you CPU.

## Build
```bash
git clone https://github.com/k4lipso/throttleCPU
cd throttleCPU
mkdir build; cd build
cmake ..
make
sudo make install
```

## Usage
### Setup
`throttleCPU` can be used like any other `systemd` service using `systemctl`.

```bash
systemctl daemon-reload
systemctl start/enable throttleCPU.service
```

### Monitoring
To see the latest action of `throttleCPU` use the `systemctl status` command:

```
systemctl status throttleCPU.service
```

Made on Archlinux, shoud work on other Distos too.

## Github
Find this project on [Github](https://github.com/k4lipso/throttleCPU)
