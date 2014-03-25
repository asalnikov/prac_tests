#
# Собственно для использования можно сделать
# символичискую ссылку на файл исполняемый файл
# в том каталоге, где он лежит в этот каталог.
#

PROGRAM=./testing_shell

#
# Раскомментировать, если есть утечки памяти 
#
VALGRIND_OPTIONS=  #--leak-check=full 

TESTS=$(wildcard *.sh)
RESULTS=$(patsubst %.sh, %.out, $(TESTS) )
ERRS=$(patsubst %.sh, %.err, $(TESTS) )



test:  $(RESULTS)
	@echo "Tests finished"

valgrind_check: $(ERRS)
	@echo "Valgrind checks finished"

$(TESTS) : $(PROGRAM)

%.out: %.sh  
	$(PROGRAM) < $< > $@

%.err: %.sh
	valgrind $(VALGRIND_OPTIONS) $(PROGRAM) < $< 2>$@

clean:
	rm -rf $(RESULTS)
	rm -rf $(ERRS)
