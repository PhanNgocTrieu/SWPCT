int CalLargestBlock(int id_ignore){
	int max_block_size = 0;
	int cur_size = 1;
	int last = -1;
	for (int i = 0; i < N; i++){
		if(ID[i] == id_ignore) continue;
		if (ID[i] == last) cur_size++;
		else cur_size = 1;
		last = ID[i];
		if (max_block_size < cur_size) {
			max_block_size = cur_size;
		}
	}
	return max_block_size;
}