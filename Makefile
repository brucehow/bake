# Make file for Bake

PROGNAME = bake
C99 = cc -std=c99 -Werror -Wall -pedantic
DEPENDENCIES = append.c bake.c curl.c expandvar.c filedate.c main.c process.c readfile.c targets.c variables.c

Bake : $(DEPENDENCIES)
	@$(C99) -o $(PROGNAME) $(DEPENDENCIES)
	@echo "make: 'Bake' successfully built."
clean :
	@rm -f $(PROGNAME)
	@echo "make: 'Bake' has been removed."
