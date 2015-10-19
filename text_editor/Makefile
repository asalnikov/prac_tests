#
# Собственно для использования можно сделать
# символичискую ссылку на файл исполняемый файл
# в том каталоге, где он лежит в этот каталог, где 
# лежат тесты.
#
# ls -s /xxxxxxx/repos/task_text_editor/editor ./testing_editor
#

PROGRAM=./testing_editor

#
# Раскомментировать, если есть утечки памяти 
#
VALGRIND_OPTIONS=  #--leak-check=full 

TESTS=$(wildcard *.conf)
RESULTS=$(patsubst %.conf, %.out, $(TESTS) )
ERRS=$(patsubst %.conf, %.err, $(TESTS) )
ADV_OUT=$(patsubst %.conf, file_%.err.out, $(TESTS) )



test:  $(RESULTS)
	@echo "Tests finished"

valgrind_check: $(ERRS)
	@echo "Valgrind checks finished"

$(TESTS) : $(PROGRAM)

%.out: %.conf
	$(PROGRAM) < $<
	$(PROGRAM) < $< > $@ #выводим результат в файл

%.err: %.conf
	valgrind $(VALGRIND_OPTIONS) $(PROGRAM) < $< 1>file_$@.out 2>$@
	valgrind $(VALGRIND_OPTIONS) $(PROGRAM) < $< 2>$@
	valgrind $(VALGRIND_OPTIONS) $(PROGRAM) < $< > file_$@.out 2>>$@

clean:
	rm -rf $(RESULTS)
	rm -rf $(ERRS)
	rm -rf $(ADV_OUT)
