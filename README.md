# Lifi 1.0 (Arduino Project)
[https://blog.echo35.com/lifi_1.0](https://blog.echo35.com/lifi_1.0)

Requires PySerial: `# pip2 install pyserial`

`funcs.py` must be executed from a python2 console with access to the Arduino device (serial):
```
$ sudo python2
Python 2.7.13 (default, Dec 21 2016, 07:16:46)
Type "help", "copyright", "credits" or "license" for more information.
>>> execfile("lifi_funcs.py")
>>> ser = serial.Serial("/dev/ttyACM0", 4800)
>>> send("notes", 64)
Sending 64 bytes... total: 64/223 bytes.
Sending 64 bytes... total: 128/223 bytes.
Sending 64 bytes... total: 192/223 bytes.
Sending 64 bytes... total: 223/223 bytes.
>>>
```
