BIN = bin
OBJ = obj
SRC = src
DOC = doc
CFLAGS=-std=c99 -Wall -Wextra -g -lm
LATEXMK = pdflatex -output-directory $(OBJ)
RAPPORT = rapport
TARGET_FILES = rapport.pdf 
FILES = $(addprefix $(RAPPORT)/,$(TARGET_FILES))
all : $(BIN)/computePatchOpt doc 

dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)
$(OBJ)/computePatchOpt.o: $(SRC)/computePatchOpt.c dirs
	gcc -c -o $@ $< $(CFLAGS)

$(BIN)/computePatchOpt: $(OBJ)/computePatchOpt.o $(OBJ)/algo_1.o $(OBJ)/outils.o
		gcc -o $@ $^ $(CFLAGS)

$(OBJ)/algo_1.o: $(SRC)/algo_1.c
	gcc -c -o $@ $< $(CFLAGS)

$(OBJ)/outils.o: $(SRC)/outils.c
	gcc -c -o $@ $< $(CFLAGS)

rapport: $(FILES)

%.aux: %.tex
	$(LATEXMK) $<

%.pdf: dirs
	$(LATEXMK) $(@:.pdf=.tex)
	cp -f $(OBJ)/$(basename $(@F)).pdf $@
doc:
	doxygen Doxyfile

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)
	rm -rf $(DOC)

.Phony: clean all dirs doc rapport
