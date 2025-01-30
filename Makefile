makedirs = fileman palm-rejection qt-resource-rebuilder random-suspend-screen
qmakedirs = qt-command-executor
alldirs = $(qmakedirs) $(makedirs)

.PHONY	: all $(alldirs) clean clean-%

all	: $(makedirs) $(qmakedirs)
clean	: $(addprefix clean-,$(alldirs))

$(makedirs)	:
	cd $@ && $(MAKE)

$(qmakedirs)	:
	cd $@ && qmake . && $(MAKE)

clean-%	:
	cd $* && $(MAKE) clean
