CXX      = g++
CXXFLAGS += -Wall -pedantic
CC       = $(CXX) $(CXXFLAGS)
CPPFLAGS += -std=c++11

AR      = ar
ARFLAGS += rvs

MKDIR  = mkdir -p
RM     = rm -f
RMDIR  = rm -rf
COPY   = cp
MOVE   = mv -f
RENAME = mv -f
NULL_DEVICE = /dev/null
