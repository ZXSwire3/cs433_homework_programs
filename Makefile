SUBDIRS := assign1 assign2 assign3 assign4 assign5

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

build_assign1:
	$(MAKE) -C assign1 all
run_assign1:
	$(MAKE) -C assign1 clean run

build_assign2:
	$(MAKE) -C assign2 all
run_assign2:
	$(MAKE) -C assign2 clean run

build_assign3:
	$(MAKE) -C assign3 all
run_assign3:
	$(MAKE) -C assign3 clean run

build_assign4:
	$(MAKE) -C assign4 all
run_assign4:
	$(MAKE) -C assign4 clean run

build_assign5:
	$(MAKE) -C assign5 all
run_assign5:
	$(MAKE) -C assign5 clean run