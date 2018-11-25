all:
	g++ test_lzw.cpp LZW.cpp -o test
	#g++ test_huf.cpp AdaptiveHuffman.cpp -o test