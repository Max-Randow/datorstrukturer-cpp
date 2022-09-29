QT += widgets
# Used to turn off warnings on qt m_headers.
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_M_HEADERS]

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
QMAKE_CXXFLAGS_RELEASE += -D NDEBUG -O3 -march=native -flto -s

QMAKE_LFLAGS += -m64
#QMAKE_LFLAGS_DEBUG += -fsanitize=address -fsanitize=undefined
#QMAKE_LFLAGS_RELEASE +=

SOURCES = $$PWD/src/*.cpp
#SOURCES += $$PWD/lib/*.cpp
m_headERS = $$PWD/src/*.h
#m_headERS += $$PWD/lib/*.h

INCLUDEPATH += $$PWD/lib/

# Copies the given files to the destination directory
defineTest(copyToDestdir) {
	files = $$1

	for(FILE, files) {
		DDIR = $$OUT_PWD

		# Replace slashes in paths with backslashes for Windows
		win32:FILE ~= s,/,\\,g
		win32:DDIR ~= s,/,\\,g

		!win32 {
			QMAKE_POST_LINK += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
		}
		win32 {
			QMAKE_POST_LINK += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
		}
	}

	export(QMAKE_POST_LINK)
}
!win32 {
	copyToDestdir($$files($$PWD/res/*))
}
win32 {
	copyToDestdir($$PWD/res)
}
macx {
	cache()
}
