/*
** get_val_ret.c for get_val_ret in /home/wery_p/rendu/PSU_2015_42sh/srcs/var_env
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 04:51:04 2016 Paul Wery
** Last update Sat Jun  4 05:00:15 2016 Paul Wery
*/

#include <stdlib.h>
#include <unistd.h>

int	size_ret(int val)
{
  int	n;

  n = 0;
  while (val > 0)
    {
      val /= 10;
      n += 1;
    }
  if (n == 0)
    n = 1;
  return (n);
}

char	*get_val_ret(int val)
{
  char	*val_exit;
  int	size;

  if ((val_exit = malloc(size_ret(val) + 1)) == NULL)
    return (NULL);
  size = size_ret(val);
  val_exit[size--] = '\0';
  while (size >= 0)
    {
      val_exit[size] = val % 10 + 48;
      val /= 10;
      size -= 1;
    }
  return (val_exit);
}
