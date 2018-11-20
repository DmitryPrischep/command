char* LZW::compress(const char* data, int size) {
	std::string str_data(data, size);
	std::vector<int> encoded;
	std::vector<char> result;
	int dict_size = 256;
	encode(str_data, std::back_inserter(encoded), dict_size);

	/*
	int fill = 0; // количество записанных бит в байте
	for (int i = 0; i < size; i++) {
		int value = encoded[i];
		int bits_count = log(value) / log(2); // количество значащих бит в числе
		for (int j = 0; j < bits_count; j++) { // не уверен, что учел выход за 8 бит !!!!!!
			if (fill == 0) {
				result.push_back(0);
			}
			result.back() |= ( (value >> j) & 1u ) << (7 - fill); // "конкатенируем" значащие биты
			fill = (fill + 1) % 8;
		}
	}
	*/

	//return result;

}