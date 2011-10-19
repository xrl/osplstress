Let's break opensplice.

First, build the code:

  libtoolize -c || glibtoolize -c
  autoreconf -fv --install
  ./configure
  make

Recreate UserQosPolicy is empty error
  In one terminal you will run a publisher, a short-lived process
    ./userqos p
  In another terminal you will run a subscriber, a long-lived process
    ./userqos s
