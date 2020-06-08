# backlight
`backlight` is a simple CLI program to control screen brightness. Because [xbacklight](https://linux.die.net/man/1/xbacklight) never seems to work.

### Installation
The executable is installed in `/usr/local/` by default.
```
make
sudo make install
```

### Usage
```
$ backlight -h
Usage: backlight [-h] [-s percent | -i percent | -d percent]
    -h Print this help
    -s Set current brightness percentage
    -i Increment brightness percentage
    -d Decrement brightness percentage
```
