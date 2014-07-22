all: $(RELEASE)

$(RELEASE): $(OBJECTS)
	$(CC) $(LD_OPTS) -o$@ $(OBJECTS)

.SECONDEXPANSION:
$(OBJECTS): %.$(OBJ_EXT): $$(subst $(OBJ_DIR)/,,%.c)
	mkdir -p $(dir $@)
	$(CC) -c $(INCLUDES) $(CC_OPTS) -o$@ $< 

clean:
	rm -f -R $(OBJ_DIR)

