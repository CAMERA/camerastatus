AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = ${CURL_CFLAGS} ${CPPUNIT_CFLAGS}

bin_PROGRAMS = camerastatus

camerastatus_LDADD = ${CURL_LIBS} ${CURSES_LIB}

camerastatus_SOURCES = src/camerastatus.cpp \
                       src/CursesView.cpp \
                       src/Box.cpp \
                       src/CursesColors.cpp \
                       src/NightRiderSlider.cpp \
                       src/News.cpp \
                       src/JobPanel.cpp \
                       src/FakeStatusModel.cpp \
                       src/HorizontalJobBar.cpp \
                       src/ClusterPanel.cpp \
                       src/StringUtil.cpp \
                       src/LoggedInUsersBar.cpp \
                       src/WorkflowsRunBar.cpp \
                       src/URLStatusModel.cpp

camerastatustest_SOURCES = test/camerastatustest.cpp \
                           test/StringUtilTest.cpp \
                           src/CursesView.cpp \
                           src/Box.cpp \
                           src/CursesColors.cpp \
                           src/NightRiderSlider.cpp \
                           src/News.cpp \
                           src/JobPanel.cpp \
                           src/FakeStatusModel.cpp \
                           src/HorizontalJobBar.cpp \
                           src/ClusterPanel.cpp \
                           src/StringUtil.cpp \
                           src/LoggedInUsersBar.cpp \
                           src/WorkflowsRunBar.cpp \
                           src/URLStatusModel.cpp

man_MANS = doc/camerastatus.1

dist_noinst_SCRIPTS = autogen.sh

EXTRA_DIST = doc/camerastatus.1

check_PROGRAMS = camerastatustest

camerastatustest_CXXFLAGS = ${CPPUNIT_CFLAGS} 

camerastatustest_LDADD = ${CPPUNIT_LIBS} ${CURL_LIBS} ${CURSES_LIB}

.PHONY: test

TESTS = camerastatustest



all-local:
	@echo "This target all-local is part of all: target"
	
clean-local:
	@echo "This clean-local target is called during clean target"
	rm -f test/*.o
	rm -f camerastatustest
	

test: check
