bool solution(string inputString) {
    int left = 0;
    int right = inputString.length() - 1;
    do {
        if (inputString[left] != inputString[right]) {
            return false;
        }
        left++;
        right--;
    } while (left < right);
    return true;
}
