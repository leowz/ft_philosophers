/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:00:58 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 16:31:43 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	tenary(int value, int ret1, int ret2)
{
	if (value)
		return (ret1);
	else
		return (ret2);
}

int	ft_atoi(const char *str)
{
	int				ret;
	unsigned int	digit;
	int				sign;
	int				i;

	ret = 0;
	sign = 0;
	i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || *str
		== '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		sign = tenary(*str++ == '-', 1, 0);
	while (1 && i < 20)
	{
		digit = *str++ - '0';
		if (digit > 9)
			break ;
		ret = (10 * ret) + digit;
		i++;
	}
	if (sign)
		return (tenary(i < 20, -ret, 0));
	return (tenary(i < 20, ret, -1));
}
