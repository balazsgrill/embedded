LWIP_OUT = $(OUT_DIR)/lwip
LWIP_OBJ = $(LWIP_OUT)/obj
LWIP_LIB = $(LWIP_OUT)/liblwip.a	
	
$(LWIP_OUT) : $(OUT_DIR)
	mkdir -p $(LWIP_OUT)

$(LWIP_OBJ) : $(LWIP_OUT)
	mkdir -p $(LWIP_OBJ)
	
LWIP_INCLUDE = $(LWIP_SRC)/src/include
LWIP_CC_OPTS = $(CFLAGS) -I$(LWIP_INCLUDE) -I$(LWIP_INCLUDE)/ipv4 -Isrc-app -Isrc-app/$(TARGET) -I$(STELLARIS_WARE)
LWIP_CC_OPTS += -I$(ENC28J60_DRIVER)/stellaris/enchw -I$(ENC28J60_DRIVER)/enc28j60driver -I$(ENC28J60_DRIVER)/lwip

LWIP_SOURCES += $(wildcard $(LWIP_SRC)/src/api/*.c)
LWIP_SOURCES += $(wildcard $(LWIP_SRC)/src/core/*.c)
LWIP_SOURCES += $(wildcard $(LWIP_SRC)/src/core/ipv4/*.c)
LWIP_SOURCES += $(wildcard $(LWIP_SRC)/src/netif/*.c)
LWIP_SOURCES += $(wildcard $(LWIP_SRC)/src/netif/ppp/*.c)
LWIP_SOURCES += $(wildcard $(ENC28J60_DRIVER)/stellaris/enchw/*.c)
LWIP_SOURCES += $(wildcard $(ENC28J60_DRIVER)/enc28j60driver/*.c)
LWIP_SOURCES += $(wildcard $(ENC28J60_DRIVER)/lwip/netif/*.c)

define LWIP_CC_template
$$(LWIP_OBJ)/$(basename $(notdir $(1))).o : $(1) $$(LWIP_OBJ)
LWIP_OBJS += $$(LWIP_OBJ)/$(basename $(notdir $(1))).o
endef

$(foreach srcfile,$(LWIP_SOURCES),$(eval $(call LWIP_CC_template,$(srcfile))))

$(LWIP_OBJS) : $(LWIP_OBJ)
	@echo CC $@
	@$(CC) $(LWIP_CC_OPTS) -o $@ $(filter %.c,$+)

$(LWIP_LIB) : $(LWIP_OUT) $(LWIP_OBJS)
	@echo AR $@
	@$(AR) cr $@ $(filter %.o,$+)
