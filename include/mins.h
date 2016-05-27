/*
** get_next_line.h for get_next_line in /home/wery_p/rendu/CPE_2015_getnextline
**
** Made by paul wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan  5 01:26:12 2016 paul wery
** Last update Fri May 27 02:08:19 2016 Paul Wery
*/

#ifndef MINS
# define MINS

# ifndef READ_SIZE
#  define READ_SIZE (5)

#endif /* !READ_SIZE */

#    define UNUSED __attribute__((unused))

# include <sys/stat.h>

typedef struct	stat t_stat;

char	*get_next_line(void);

typedef struct	s_line
{
  char		*line;
  int		val_ret;
  int		end;
  int		nb;
}		t_line;

typedef struct	s_exec
{
  char		**tab;
  struct s_exec	*next;
  struct s_exec	*prev;
}		t_exec;

typedef struct	s_env
{
  char		**env;
  char		*oldpwd;
  int		pipe_t[2];
  int		state_p;
  int		result;
  int		stdin;
  int		stdout;
}		t_env;

char	*get_exec(char *str);
char	**exec_line(char *exec, char **opts, t_env *ev, pid_t my_pid);
int	find_exec(char *exec, char **opts, char **env, int ret);
char	*get_exec(char *str);
int	find_path(char **env);
char	*get_path(int n, int nb_t, char **env, int i);
int	nb_path(int n, char **env);
int	my_strlen(char *str);
char	*final_path(char *path, char *exec);
void	my_putstr(char *str);
void	my_put_error(char *error);
void	path_exec(char *exec, char **opts, char **env);
int	where_exec(char *exec);
void	my_exit(char *w1, char *word2, char *buffer, t_env *ev);
int	my_cd(char *exec, char **opts);
int	comp_words(char *word1, char *word2);
char	**create_my_env(char **str, int n, int i);
void	free_opts(char **opts);
int	my_builtins(char *exec, char **opts, char **env);
int	comp_builtins(char *word1, char *word2);
void	*my_realloc(char *str, int new_size);
int	nb_env(char **str);
char	**unset_env(char *exec, char **opts, char **env, int state);
char	**set_env(char *exec, char **opts, char **env);
int	find_set_unset(char **env, char *opt);
char	**realloc_env2(char **env, int size, int n, char **opts);
void	add_env(char **cop, char **opts, int n);
int	valid_line(char *buffer);
char	**swap_env(char *exec, char **opts, t_env *ev);
char	**clear_env(char **env, int n, int size, int i);
char	**moove_old_directory(t_env *ev);
char	*ini_elem(void);
char	*get_elem_env(char **env, char *opt, int n, int i);
char	**swap_elems(char *pwd, char **env);
char	**moove_home(t_env *ev);
char	**concat_tab(char **src, int start, int end);
char	*alloc_buffer(char *file, int fd);
char	*build_path(char *path, char *exec);
char	*conv_str(char *str);
char	*conv_strs(char *one, char *two, char *three);
char	**final_env(char **str, char **env);

t_exec	*create_list(void);
int	add_elem_prev(t_exec *elem, char **tab);
int	add_elem_pipe(t_exec *elem, char **tab);
void	delete_list(t_exec **root);

char	**pars_elems(char *buffer);
int	full_list(t_exec *list, char **pars);
char	**get_opts(char *str, int n, int z);
char	**exec_list(t_exec *list, t_env *ev);
int	change_output(t_exec *list, t_exec *elem, int stdout, int num);
int	change_input(t_exec *list, t_exec *elem, int num);
int	elem_redirection(char *elem, char *ref);
int	default_io(int stdin, int stdout, int state);
int	open_files(t_exec *list, t_exec *it, int num, int fd);
int	wait_lef(t_exec *list, t_exec *it, int num);
int	update_std(t_env *ev, int state);
int	valid_command(t_exec *list);
t_exec	*jump(t_exec *list, t_exec *it);

#endif /* !MINS */
