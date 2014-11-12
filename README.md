### How to get source code
```
mkdir cs540 (any name you like)
cd cs540
git clone git@github.com:njurn/cs540.git .
```

### Requirements
자세한 사항은 http://ndnsim.net/getting-started.html 참고 
```
$ apt-get aptitude
$ aptitude install libboost1.48-all-dev (for ubuntu 12.04)
$ aptitude install libboost-all-dev (12.10, 13.04, and newer versions)
$ apt-get install python-dev python-pygraphviz python-kiwi
$ apt-get install python-pygoocanvas python-gnome2
$ apt-get install python-gnomedesktop python-rsvg ipython
```
### How to build
```
$ cd ns-3
$ ./waf configure --enable-examples
$ ./waf
```
### How to run samples
```
$ ./waf --run=ndn-simple
```

