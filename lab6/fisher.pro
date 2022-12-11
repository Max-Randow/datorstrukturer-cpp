TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# Used to turn off warnings for qt headers.
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

QMAKE_CXXFLAGS += -std=c++11 -m64 -pipe -fstack-clash-protection -fstack-protector-strong

# Warnings
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wunused -Wold-style-cast -Woverloaded-virtual -Wnull-dereference
QMAKE_CXXFLAGS += -Wconversion -Wdouble-promotion
# GCC specific
QMAKE_CXXFLAGS += -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wunsafe-loop-optimizations

# Errors
QMAKE_CXXFLAGS += -Werror=implicit-fallthrough -Werror=return-type -Werror=narrowing -Werror=uninitialized


QMAKE_CXXFLAGS_DEBUG += -Og -g -ggdb -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fasynchronous-unwind-tables
QMAKE_CXXFLAGS_RELEASE += -D NDEBUG -O3 -march=native -flto

QMAKE_LFLAGS += -m64

SOURCES = Event.cpp Fish.cpp main.cpp Simulation.cpp

HEADERS = $$files(*.h,true)
