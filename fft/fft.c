#include <complex.h>
#include <math.h>
#include <stdio.h>

// 交换两个复数
#define SWAP(a, b, T) do { T temp = a; a = b; b = temp; } while(0)

// FFT函数
void fft(complex double *a, int n, int inv) {
    int i, j, k, m, p, q;
    complex double u, v, temp;
    double pi = 3.14159265358979323846;
    double angle = 2 * pi / n * (inv ? -1 : 1);

    // 位反转
    for (i = 1, j = n - 1; i < j; i++, j--) {
        SWAP(a[i], a[j], complex double);
    }

    // 蝶形运算
    for (k = 1; k <= n; k = k + k) {
        for (m = 0; m < k; m++) {
            u = 1;
            for (p = m; p < n; p += k + k) {
                q = p + k;
                v = (inv ? conj(u) : u) * a[q];
                SWAP(a[q], a[p], complex double);
                u *= angle;
            }
        }
        angle *= 0.5;
    }
}

// 打印复数数组
void print_array(complex double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("(%f, %f) ", creal(a[i]), cimag(a[i]));
    }
    printf("\n");
}

int main() {
    int N = 8; // 必须为2的幂
    complex double a[N];

    // 初始化复数数组
    for (int i = 0; i < N; i++) {
        a[i] = i * I; // 这里使用I来表示虚数单位
    }

    printf("原始数据: ");
    print_array(a, N);

    // 执行FFT
    fft(a, N, 0);

    printf("FFT结果: ");
    printf("N: %d\n", N);
    print_array(a, N);

    // 执行逆FFT
    fft(a, N, 1);

    printf("逆FFT结果: ");
    print_array(a, N);

    return 0;
}
