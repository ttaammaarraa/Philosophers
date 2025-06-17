#include"philo.h"
#include<limits.h>
int ft_atoi(const char *str)
{
    //int         sign;
    int         i;
    long int    result;

    //sign = 1;
    i = 0;
    result = 0;
    while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
        i++;
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            //sign *=-1;
            return (-1);
        i++;
    }
    while (str[i] != '/0' && str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0' || (result > INT_MAX))
			return (-1);
    return (result);
}

int main(int argc, char **argv)
{
    t_data  data;

}