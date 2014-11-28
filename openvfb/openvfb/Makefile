OPENVFB := $(dir $(lastword $(MAKEFILE_LIST)))
OUT = $(MODULE)/out
TMP = $(out)/tmp 

MODULENAME = $(basename $(MODULE))

$(MODULE)/$(MODULENAME).a : $(TMP)/Makefile
	make -f $(TMP)/Makefile
	
$(TMP)/Makefile : $(MODULE)/module.yml
	$(XSLT) -o $@ $(OPENVFB)/makefile.xsl $+
