TEMPLATE = app
CONFIG += c++17
CONFIG += qt
QT += widgets

# Used to turn off warnings for qt headers.
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

QMAKE_CXXFLAGS += -std=c++17 -m64 -pipe -fstack-clash-protection -fstack-protector-strong

# Warnings
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wunused -Wold-style-cast -Woverloaded-virtual -Wnull-dereference
QMAKE_CXXFLAGS += -Wconversion -Wdouble-promotion -Wmismatched-new-delete
# GCC specific
QMAKE_CXXFLAGS += -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wunsafe-loop-optimizations

# Errors
QMAKE_CXXFLAGS += -Werror=implicit-fallthrough -Werror=return-type -Werror=narrowing -Werror=uninitialized


QMAKE_CXXFLAGS_DEBUG += -Og -g -ggdb -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fasynchronous-unwind-tables
#QMAKE_CXXFLAGS_DEBUG += -fsanitize=address -fsanitize=undefined
QMAKE_CXXFLAGS_RELEASE += -D NDEBUG -O3 -march=native -flto

QMAKE_LFLAGS += -m64
#QMAKE_LFLAGS_DEBUG += -fsanitize=address -fsanitize=undefined
#QMAKE_LFLAGS_RELEASE +=


HEADERS += mainwindow.h \
	utilities.h \
	constants.h \
	Unit.h \
	Junk.h \
	Hero.h \
	Robot.h \
	GameState.h \
	qgameoverwindow.h \
	qresetbutton.h
SOURCES += mainwindow.cpp \
	robotsmain.cpp \
	utilities.cpp \
	Unit.cpp \
	Junk.cpp \
	Hero.cpp \
	Robot.cpp \
	GameState.cpp \
	qgameoverwindow.cpp \
	qresetbutton.cpp
QMAKE_CXXFLAGS += -std=c++11
macx {
	cache()
}
