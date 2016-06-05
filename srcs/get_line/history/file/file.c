/*
** file.c for 42sh in /home/gerard_v/Documents/42sh/srcs/file
**
** Made by Valentin GERARD
** Login   <gerard_v@epitech.net>
**
** Started on  Tue Dec 29 21:18:49 2015 Valentin GERARD
** Last update Sun Jun  5 06:24:54 2016 Nicolas Chevalier
*/

#include "history.h"

int	close_error(char *file_name)
{
  my_putstr(file_name, 2);
  my_putstr(" : Can't close !\n", 2);
  return (1);
}

int	close_file(int fd)
{
  int	close_fd;

  close_fd = close(fd);
  return (close_fd);
}

int	open_error(char *file_name)
{
  my_putstr(file_name, 2);
  my_putstr(" : Can't open !\n", 2);
  return (1);
}

int	open_file(char *file_name, int mode)
{
  int	fd;

  if (mode == 0)
    fd = open(file_name, O_CREAT | O_RDONLY | O_TRUNC,
	      S_IWUSR | S_IRUSR | S_IRGRP);
  if (mode == 1)
    fd = open(file_name, O_CREAT | O_WRONLY , S_IRUSR | S_IWUSR);
  return (fd);
}
