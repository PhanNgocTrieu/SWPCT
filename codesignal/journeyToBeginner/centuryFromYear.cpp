int solution(int year) {
    int century = year / 100;
    year = year % 100;
    if (year > 0) {
        return century + 1;
    }
    return century;
}
