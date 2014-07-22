
OBJ_DIR = $(OUT_DIR)/release-$(CC)-$(TARGET)
RELEASE = $(OBJ_DIR)/release.$(TARGET).$(RELEASE_EXT)

SOURCES = $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.c))
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.$(OBJ_EXT)))
INCLUDES = $(addprefix -I,$(SOURCE_DIRS))

