/* Questão 4 - Crie uma função chamada celsiusParaFahrenheit que 
receba uma temperatura em graus Celsius e
retorne o valor convertido para Fahrenheit. 
Utilize a fórmula F = (9 × C) / 5 + 32. O programa principal deverá
solicitar a temperatura ao usuário e apresentar o resultado com duas 
casas decimais.*/

#include <stdio.h>

float celsiusParaFahrenheit(float celsius) {
    return (9 * celsius) / 5 + 32;
}

int main() {
    float c, f;

    printf("Digite a temperatura em graus Celsius: ");
    scanf("%f", &c);

    f = celsiusParaFahrenheit(c);

    printf("%.2f °C equivale a %.2f °F\n", c, f);

    return 0;
}