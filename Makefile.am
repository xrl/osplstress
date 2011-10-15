# -pedantic
AM_CXXFLAGS = -g -O0 -Wall -Werror

bin_PROGRAMS = userqot

# /home/ospl/HDE/x86_64.linux2.6/include/sys/
# /home/ospl/HDE/x86_64.linux2.6/include/dcps/C++/SACPP
pidfiles = src/ccpp_PID.h src/PID.cpp src/PID.h src/PIDDcps.cpp src/PIDDcps.h src/PIDDcps_impl.cpp src/PIDDcps_impl.h src/PIDSplDcps.cpp src/PIDSplDcps.h
CLEANFILES = $(pidfiles)
$(pidfiles) : src/idl/PID.idl
	idlpp -S -l c++ -Isrc/idl -d built/idl/ $<

userqot_LDFLAGS = -L$(OSPL_HOME)/lib -lddsdatabase -ldcpsgapi -ldcpssacpp -lddsos
userqot_CPPFLAGS = -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include/ -I$(OSPL_HOME)/include/sys
userqot_DEPENDENCIES = $(pidfiles)
userqot_SOURCES = src/userqos.cpp
