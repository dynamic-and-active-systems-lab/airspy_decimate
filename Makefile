all:
	rm -f airspy_decimate
	rm -f *.o
	rm -f codegen/exe/airspy_decimate/*.o
	make -f matlab-coder-utils/Makefile PRODUCT_NAME=airspy_decimate -j4
