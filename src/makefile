CC=inform

ODIR=../build/modules
BDIR=../build

MAIN = main.inf
TARGET = $(BDIR)/heist.z5

DEPS = disguise_amulet.inf destruction_disk.inf
_OBJ = disguise_amulet.m5 destruction_disk.m5
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.m5: %.inf
	$(CC) -M $^ $@

make: $(OBJ)
	$(CC) +module_path=$(ODIR) $(MAIN) $(TARGET)

clean:
	rm -f $(ODIR)/*.m5 *~ $(TARGET)

run: make
	frotz $(TARGET)
