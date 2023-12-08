#include <stdio.h>

float absolutOf(float N)
{
    if ( N < 0 )
        return -N;
    
    return N;
}
float squareRoot(float x)
{
    float guess = 1.0; 
    const float eps = 0.00001;
    while ( absolutOf(guess*guess - x) >= eps)
    {
        guess = ( x / guess + guess) / 2; 
    }
    return guess;
}
int main(void)
{
    printf("%.2f ",squareRoot(53));
}
