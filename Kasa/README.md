### API [Document](https://python-kasa.readthedocs.io/en/latest/index.html)
```shell
pip install pyinstaller
pip install python-kasa --pre
```
### bulb.py
```python3
import asyncio, kasa
bulb = kasa.SmartBulb("192.168.1.120")
asyncio.run(bulb.update())
if bulb.is_on:
    asyncio.run(bulb.turn_off())
else:
    asyncio.run(bulb.turn_on())
#asyncio.run(bulb.set_brightness(100, transition=10000))
```
### plug.py
```python3
import asyncio, kasa
plug = kasa.SmartPlug("192.168.1.105")
asyncio.run(plug.update())
if plug.is_on:
    asyncio.run(plug.turn_off())
else:
    asyncio.run(plug.turn_on())
```
### Generate a standalone exe on windows
1. [Install](https://github.com/xg590/tutorials/blob/master/Windows.md#python-and-pip) python and pip
2. Modify \_\_init\_\_.py of kasa package. 
    * %LOCALAPPDATA%\Programs\Python\Python39\Lib\site-packages\kasa\\\_\_init\_\_.py
    * Line 25: __version__ = version("python-kasa") => __version__ = '0.0.0'
3. Build
```
pyinstaller --onefile bulb.py
```
4. Test dist\bulb.exe 
