# -pedantic
# CXX=clang++
AM_CXXFLAGS = -g -O0 -Wall -Werror

bin_PROGRAMS = userqot

EXTRA_DIST = src/idl
CLEANFILES = $(pidfiles)
$(pidfiles) : src/idl/PID.idl
	idlpp -S -l c++ -Isrc/idl/ -d built/idl/ $<

pidfiles = built/idl/ccpp_PID.h built/idl/PID.cpp built/idl/PID.h built/idl/PIDDcps.cpp built/idl/PIDDcps.h built/idl/PIDDcps_impl.cpp built/idl/PIDDcps_impl.h built/idl/PIDSplDcps.cpp built/idl/PIDSplDcps.h
BUILT_SOURCES = $(pidfiles)

userqot_LDFLAGS = -L$(OSPL_HOME)/lib -lddsdatabase -ldcpsgapi -ldcpssacpp -lddsos
userqot_CPPFLAGS = -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include/ -I$(OSPL_HOME)/include/sys -Ibuilt
userqot_SOURCES = src/userqos.cpp
