/*
** get_next_line.h for get_next_line in /home/wery_p/rendu/CPE_2015_getnextline
**
** Made by paul wery
** Login   <wery_p@epitech.net>
**
** Started on  Tue Jan  5 01:26:12 2016 paul wery
<<<<<<< HEAD
** Last update Sun Jun  5 04:21:17 2016 Nicolas Chevalier
=======
** Last update Sun Jun  5 07:19:29 2016 Paul Wery
>>>>>>> master
*/

#ifndef MINS
# define MINS

# ifndef READ_SIZE
#  define READ_SIZE (5)

#endif /* !READ_SIZE */

#    define UNUSED __attribute__((unused))

# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include "shrc.h"

typedef struct dirent t_dir;
typedef struct	stat t_stat;

char	*get_next_line(void);

typedef struct	s_set
{
  char		*var;
  char		*elem;
  int		n;
}		t_set;

typedef struct	s_limit
{
  int		start;
  int		end;
}		t_limit;

typedef struct	s_var
{
  char		*name;
  char		*value;
  struct s_var	*next;
  struct s_var	*prev;
}		t_var;

typedef struct		s_order
{
  char			*name;
  struct s_order	*next;
  struct s_order	*prev;
}			t_order;

typedef struct		s_elems
{
  char			*path;
  char			*one;
  char			*two;
  char			*ref;
  struct s_limit	l;
}			t_elems;

typedef struct	s_glob_error
{
  int		one;
  int		two;
  int		three;
  int		four;
}		t_glob_error;

typedef struct	s_exec
{
  char		**tab;
  int		error;
  struct s_exec	*next;
  struct s_exec	*prev;
}		t_exec;

typedef struct	s_line
{
  char		*line;
  int		val_ret;
  int		end;
  int		nb;
}		t_line;

typedef struct	s_free
{
  char		*buffer;
  char		**pars;
  struct s_exec	*list;
  struct s_var	*list_v;
}		t_free;

typedef struct	s_env
{
  char		**env;
  char		*oldpwd;
  int		pipe_t[2];
  int		state_p;
  int		result;
  int		stdin;
  int		stdout;
  int		val_exit;
  struct s_free	free;
}		t_env;

char	*get_exec(char *str);
char	**exec_line(char **opts, t_env *ev, pid_t my_pid, int status);
int	find_exec(char *exec, char **opts, t_env *ev, int ret);
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
void	my_exit(t_env *ev, char **opts);
int	my_cd(char *exec, char **opts);
int	comp_words(char *word1, char *word2);
char	**create_my_env(char **str, int n, int i, t_env *ev);
void	free_opts(char **opts);
int	my_builtins(char *exec);
int	comp_builtins(char *word1, char *word2);
void	*my_realloc(char *str, int new_size);
int	nb_env(char **str);
char	**unset_env(char *exec, char **opts, char **env, int state);
char	**set_env(char *exec, char **opts, t_env *ev);
int	find_set_unset(char **env, char *opt);
char	**realloc_env2(char **env, int size, int n, char **opts);
void	add_env(char **cop, char **opts, int n);
int	valid_line(char *buffer);
char	**swap_env(char *exec, char **opts, t_env *ev);
char	**clear_env(char **env, int n, int size, int i);
char	**moove_old_directory(t_env *ev);
char	*ini_elem(void);
char	*get_elem_env(char **env, char *opt, int n, int i);
char	**swap_elems(char *pwd, t_env *ev);
char	**moove_home(t_env *ev);
char	**concat_tab(char **src, int start, int end);
char	*alloc_buffer(char *file, int fd);
char	*build_path(char *path, char *exec);
char	*conv_str(char *str);
char	*conv_strs(char *one, char *two, char *three);
char	**final_env(char **str, t_env *ev);
void	aff_error(char *exec);
int	my_env(t_env *ev, char **opts, char *exec);
void	get_status(int status, t_env *ev);

t_exec	*create_list(void);
int	add_elem_prev(t_exec *, char **, t_glob_error *error);
int	add_elem_pipe(t_exec *, char **);
void	delete_list(t_exec **root);

t_order	*create_order(void);
int	add_order_prev(t_order *elem, char *name);
void	delete_order(t_order **root);

t_var	*create_var(void);
int	add_var_prev(t_var *var, char *name, char *value);
void	delete_var(t_var **root);
void	delete_var_elem(t_var *elem);

char	**pars_elems(char *buffer);
int	full_list(t_exec *list, char **pars, t_env *ev);
char	**get_opts(char *str, int n, int z);
char	**exec_list(t_exec *list, t_env *ev, int in, int out);
int	change_output(t_exec *list, t_exec *elem, int stdout, t_env *ev);
int	change_input(t_exec *list, t_exec *elem, int num, t_env *ev);
int	elem_redirection(char *elem, char *ref);
int	default_io(int stdin, int stdout, int state);
int	open_files(t_exec *list, t_exec *it, int num, t_env *ev);
int	wait_lef(t_exec *list, t_exec *it, int num);
int	update_std(t_env *ev, int state);
int	valid_command(t_exec *list);
t_exec	*jump(t_exec *list, t_exec *it);
int	equal_w_space(char *one, char *two);
int	echo_built(char *buffer, int n, t_env *ev);
void	aff_echo(char *echo, int new_line, int s_one, int s_two);
int	and_or(t_env *ev, t_exec *it);
int	pair(char *buffer, int n, int s_one, int s_two);
int	inhib(char *buffer, int n, int state);
int	not_inhib(char *buffer, int n, int state);
void	aff_cd_error(char *exec, t_env *ev);
int	valid_name(char *name, t_env *ev);
char	*echo_star(char *buffer, int *error);
char	*echo_quest(char *buffer, int *error);
char	*replace_seg(char *buffer, char *replace, int *error);
char	*replace_seg_q(char *buffer, char *replace, int *error, int start);
char	*replace_seg_b(char *buffer, char *replace, int *error, int start);
int	valid_star(char *buffer);
int	notm(t_exec *it, t_env *ev);
void	files_error(char *file, t_env *ev, int state);
t_exec	*next_command(t_exec *list, t_exec *it);
int	elem_redirection(char *elem, char *ref);
char	*echo_var(char *buffer, int *error, t_env *ev);
char	*replace_seg_v(char *buffer, char *replace);
int	end_elem(char *buffer, char c);
int	start_elem(char *buffer, char c);
int	match_elem(char *name, char *ref);
int	match_elem_brak(char *name, char *one, char *two, char *ref);
int	size_result(char *buffer, char *replace, char c);
int	glob_two(char *buffer, int start);
int	glob_three(char *buffer, t_limit *l);
int	create_replace_q_next(char *path, char *name, int n, char *replace);
char	*get_elem_path(char *buffer, int start, int end);
char	*replace_seg_q_next(char *buffer, char *replace, int start);
char	*echo_bracket(char *buffer, int *error);
char	*get_val_ret(int val, char *buffer);
int	check_loc(char *buffer);
int	parsing_error(t_exec *list);
t_order	*order_names(DIR *directory);
char	*added_elem(char *str);
char	*added_same(char *str);
char	*added_value(char *str);
int	unsetable(char *name, char *str, t_var *elem);
int	set_unset_var(t_var *list_v, char **opts, t_env *ev);
void	aff_set(t_var *list_v);
void	unset(t_var *list_v, char **opts);

#endif /* !MINS */
