int solution(vector<int> inputArray) {
    int res = inputArray[0] * inputArray[1];
    if (inputArray.size() == 2) {
        return res;
    }
    int left = 1;
    while (left < inputArray.size() - 1) {
        int right = left + 1;
        int tmp = inputArray[left++] * inputArray[right];
        if (res < tmp) res = tmp;
    }
    return res;
}
