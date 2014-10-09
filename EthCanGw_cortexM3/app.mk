
APP_LIB = $(OBJ_DIR)/app.a
SOURCES += $(wildcard src-app/*.c)
SOURCES += $(wildcard src-app/clock/*.c)
SOURCES += $(wildcard src-app/utils/*.c)
SOURCES += $(wildcard $(BOARD_DRIVERS)/*.c)

define CC_template
$$(OBJ_DIR)/$(basename $(notdir $(1))).o : $(1) $$(OBJ_DIR)
APP_OBJS += $$(OBJ_DIR)/$(basename $(notdir $(1))).o
endef

$(foreach srcfile,$(SOURCES),$(eval $(call CC_template,$(srcfile))))

$(APP_OBJS) : $(OBJ_DIR)
	@echo CC $@
	@$(CC) $(CFLAGS) -I$(STELLARIS_WARE) -I$(STELLARIS_WARE)/boards/ek-lm3s3748 -I$(LWIP_INCLUDE) -I$(LWIP_INCLUDE)/ipv4 -Isrc-app -Isrc-app/$(PART) -I$(ENC28J60_DRIVER)/stellaris/enchw -I$(ENC28J60_DRIVER)/enc28j60driver -I$(ENC28J60_DRIVER)/lwip -o $@ $(filter %.c,$+)
	
$(APP_LIB) : $(OUT_DIR) $(APP_OBJS)
	@echo AR $@
	@$(AR) cr $@ $(filter %.o,$+)