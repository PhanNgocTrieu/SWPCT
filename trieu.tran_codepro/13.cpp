	if(sr >= er || sc >= ec) return;
	int a = Mat[sr][sc];
	
	for(int r =  sr + 1; r <=  er; r++) SWAP(Mat[r][sc], a);
	for(int c =  sc + 1; c <=  ec; c++) SWAP(Mat[er][c], a);
	for(int r =  er - 1; r >=  sr; r--) SWAP(Mat[r][ec], a);
	for(int c =  ec - 1; c >=  sc; c--) SWAP(Mat[sr][c], a);