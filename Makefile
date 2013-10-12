all:
clean:
	rm -f *.bmk *.brk *.RES *.user.dic *.c.ini *.h.ini \
	      *.asm *.emcl *.cp *.mil *.dbg *.dct *.dlt \
	      *.log *_callertable.txt
distclean: clean
	rm -f *.hex *.lst
