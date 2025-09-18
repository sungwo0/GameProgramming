#include <stdio.h>
#include <stdarg.h>

double sum(int count, ...);
int main(void)
{
    printf("합계 = %lf\n", sum(2, 10.5, 20.23));
    printf("합계 = %lf\n", sum(5, 10.3, 245.67, 0.51, 198345.764));
    return 0;
}
double sum(int count, ...)
{
    double total = 0, number;
    int i = 0;
    va_list ap;
    va_start(ap, count);
    while (i < count)
    {
        number = va_arg(ap, double); // 인수의 데이터 형은 double
        total += number;
        i++;
    }
    va_end(ap);
    return total;
}