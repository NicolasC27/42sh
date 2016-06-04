/*
** match_brak.c for match_brak in /home/wery_p/rendu/PSU_2015_42sh/srcs/global/glob_three
**
** Made by Paul Wery
** Login   <wery_p@epitech.net>
**
** Started on  Sat Jun  4 00:36:13 2016 Paul Wery
** Last update Sat Jun  4 01:18:46 2016 Paul Wery
*/

int	first_part(char *one, char *name, int pos)
{
  int	n;

  n = 0;
  while (one[n] == name[pos] && one[n] != '\0' && name[pos] != '\0')
    {
      n += 1;
      pos += 1;
    }
  if (one[n] == '\0' && name[pos] != '\0')
    return (pos);
  return (-1);
}

int	second_part(char *ref, char *name, int pos)
{
  int	n;

  n = 1;
  while (ref[n] != '\0' && ref[n + 1] != '\0')
    {
      if (ref[n] == name[pos])
	return (pos + 1);
      n += 1;
    }
  return (-1);
}

int	third_part(char *two, char *name, int pos)
{
  int	n;

  n = 0;
  while (two[n] == name[pos] && two[n] != '\0' && name[pos] != '\0')
    {
      n += 1;
      pos += 1;
    }
  if (two[n] == '\0' && name[pos] == '\0')
    return (pos);
  return (-1);
}

int	match_elem_brak(char *name, char *one, char *two, char *ref)
{
  int	pos;

  pos = 0;
  if (name[0] == '.')
    return (0);
  if ((pos = first_part(one, name, pos)) == -1
      || (pos = second_part(ref, name, pos)) == -1
      || (pos = third_part(two, name, pos)) == -1)
    return (-1);
  return (1);
}
