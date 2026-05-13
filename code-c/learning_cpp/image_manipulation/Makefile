# O código-fonte foi movido para cpp/learning/image_manipulation.
# Este Makefile só redireciona chamadas (ex.: alias mkimg) para lá.
REAL := ../../../cpp/learning/image_manipulation
LEGACY_TARGET := ../../../code-c/learning_cpp/image_manipulation/ImageProcessing.exe

.PHONY: all run clean
all:
	$(MAKE) -C "$(REAL)" all TARGET="$(LEGACY_TARGET)"

run:
	$(MAKE) -C "$(REAL)" run TARGET="$(LEGACY_TARGET)"

clean:
	$(MAKE) -C "$(REAL)" clean TARGET="$(LEGACY_TARGET)"
