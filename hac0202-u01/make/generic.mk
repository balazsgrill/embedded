

$(OBJ_DIR)%.$(OBJ_EXT): %.c
	$(CC) -c $(CC_OPTS) -o $@ $< 