# -pedantic
CXX=clang++
AM_CXXFLAGS = -g -Wall -Werror

bin_PROGRAMS = userqos

EXTRA_DIST = src/idl
CLEANFILES = $(pidfiles)
$(pidfiles) : src/idl/PID.idl
	idlpp -S -l c++ -Isrc/idl/ -d built/idl/ $<

pidfiles = built/idl/ccpp_PID.h built/idl/PID.cpp built/idl/PID.h built/idl/PIDDcps.cpp built/idl/PIDDcps.h built/idl/PIDDcps_impl.cpp built/idl/PIDDcps_impl.h built/idl/PIDSplDcps.cpp built/idl/PIDSplDcps.h
BUILT_SOURCES = $(pidfiles)

userqos_LDFLAGS = -L$(OSPL_HOME)/lib -lddsdatabase -ldcpsgapi -ldcpssacpp -lddsos
userqos_CPPFLAGS = -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include/ -I$(OSPL_HOME)/include/sys -Ibuilt
userqos_SOURCES = $(pidfiles) src/userqos.cpp src/userqos/reader.cpp src/userqos/writer.cpp
