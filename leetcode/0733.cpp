class Solution {
#ifdef USING_RECURSIVE
    void helper(vector<vector<int>>& image, int sr, int sc, int color, int tar) {
        if (sr >= image.size() || sc >= image[0].size()) {
            return;
        }
        if (image[sr][sc] == color || image[sr][sc] != tar) {
            return;
        }
        image[sr][sc] = color;
        helper(image, sr + 1, sc, color, tar);
        helper(image, sr - 1, sc, color, tar);
        helper(image, sr, sc + 1, color, tar);
        helper(image, sr, sc - 1, color, tar);
    }
#endif
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int val = image[sr][sc];
#ifdef USING_RECURSIVE
        helper(image, sr, sc, color, val);
#endif
        return image;
    }
};
