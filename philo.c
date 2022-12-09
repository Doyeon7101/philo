/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:13 by dpark             #+#    #+#             */
/*   Updated: 2022/12/09 18:17:26 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int terminate(t_vaild status, t_data *data, char *msg)
{
    if (status == INVAILD)
    {
        // mutex들 free
        printf("%s\n", msg);
        return(1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;

    if (argc != 5 && argc != 6)
        return(terminate(INVAILD, &data, "argc error"));
    if (!init_parse(&data, philo, argv))
        return(terminate(INVAILD, &data, "parsing error"));
}
