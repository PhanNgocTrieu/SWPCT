def calcLessThanX(a, x):
    n = len(a)
    s = sum(a)
    j = 0
    ans = 0

    for i in range(n-1, -1, -1):
        while j < n and s - a[i] - a[j] >= x:
            j += 1
        ans += (n - j)

    for i in range(n):
        if s - a[i] - a[i] < x:
            ans -= 1

    return ans // 2

def main():
    for _ in range(int(input())):
        n, x, y = map(int, input().split())
        a = list(map(int, input().split()))
        a = sorted(a)
    print(calcLessThanX(a, y+1) - calcLessThanX(a, x))
    print('end case')

main()