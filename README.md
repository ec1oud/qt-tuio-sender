# Qt TUIO Sender

This is intended as a way for QtQuick applications to send a
[TUIO 2.0](http://www.tuio.org/?tuio20) event stream, for example
for remote-controlling another touch-based application, perhaps
on another screen.

Requires Qt 5.9 or later.

Depends on [the reference TUIO 2.0 implementation](https://github.com/mkalten/TUIO20_CPP)
as a git submodule.

To build and test:
```
git submodule update --init --recursive
qmake
make install
examples/simulator.qml
```

As with most TUIO servers, it sends UDP packets on port 3333.
You can monitor the output with the Tuio2Dump utility, which can be built as follows:

```
cd TUIO20_CPP/demos
make
```

Qt includes a plugin supporting TUIO 1.0, whereas the reference implementation
which this depends on uses the TUIO 2.0 specification, and the two are incompatible.
So you can try this

```
QT_TUIOTOUCH_DELIVER_WITHOUT_FOCUS=1 qml -plugin TuioTouch path/to/qt59/qtdeclarative/tests/manual/touch/mpta-crosshairs.qml
```

but it won't work, yet, whereas the
[Java-based TUIO 1.1 simulator](https://github.com/mkalten/TUIO11_Simulator)
should work with Qt 5.9 applications.

[QTBUG-51862](https://bugreports.qt.io/browse/QTBUG-51862) will track the
progress of getting TUIO 2.0 support into Qt.  It was a chicken/egg problem
that TUIO 2.0 is still too uncommon to test with, which is one reason for
this project.

The QML API here is unfinished... it's intended to be less stupid and more
declarative eventually.

