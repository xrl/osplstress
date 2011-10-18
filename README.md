Let's break opensplice.

First, build the code:

  libtoolize -c || glibtoolize -c
  autoreconf -fv --install
  ./configure
  make

Existing test tools

  userqot: causes denial of service, crashing the ospl daemon and locking the DDS application. Must hard-kill application, ospl stop && ospl start
  in one terminal: ./userqot p
  in another:      for i in {1..10000}; do ./userqos s; done

  After a while it will fall over, always less than 2 minutes.
