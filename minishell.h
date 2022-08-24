/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:16:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/24 10:45:04 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

// Global variable declaration
extern t_list	*g_m;

// for saving local variable
typedef struct var
{
	char		*key;
	char		*value;
	int			err_flag;
	struct var	*next;
	struct var	*prev;
}	t_var;

// for saving commands
typedef struct list
{
	char		*token;
	int			flag;
	t_list		*lst;
	char		*es;
	int			d_flag;
	int			l_flag;
	int			l2_flag;
	int			r_flag;
	int			r2_flag;
	int			p_flag;
	int			err_flag;
	int			s_flag;
	int			dq_flag;
	struct list	*next;
	struct list	*prev;
}	t_new;

// for saving required information
typedef struct info
{
	int	flag;
	int	w_flag;
	int	e_flag;
	int	q_flag;
	int	dq_flag;
	int	err_flag;
}				t_info;

//---------------------------------------------//
//--------------Parsing Functions--------------//
//---------------------------------------------//
// return 1 if space tab or newline 
int		ft_isspace(char c);
// return 0 if double or single quote is found.
int		is_quote(char c);
// Used to clear the screen
void	ft_clearscreen(void);
// Display a prompt and wait for input 
char	*ft_readline(void);
// --------handling quote----------------------
// find length of word until quote.
int		ft_strlen_ch(char *line, char c);
/*count the number single and double quotes saperately
if there is odd number return false*/
void	quote_counter(char *line, t_info *info);
//get the quoted word without quotes
char	*quoted_word(char *line, char ch);
// move pointer after the closing quote
char	*go_past_quotes(char *s, char ch, int *flag);
// ----------handling normal-------------------
//find the word length for normal part in a string
int		get_word_len(char *line);
//get the normal word
char	*normal_word(char *line);
//normal part
void	normal_lexer(t_new **pars, t_info *info, char *str);
char	*get_word(t_info *info, char *line);
int		check_word_for_parsing(char *line);
// ---------List operations for words--------------------
// adds new node to the pars structure
void	lst_add_new(t_new **pars, char *str, t_info *info);
// adds new node at back side of pars structure
void	lst_add_back(t_new **pars, char *str, t_info *info, int flag);
//prints contents of structure var
void	lst_print(t_new *pars);
void	lst_rev_print(t_new *pars);
//----------List operations for variable assignment-----
// adds new node to the var structure
void	lst_add_newvar(t_var **var, char *line);
// adds new node at back side of var structure
void	lst_add_backvar(t_var **var, char *line);
// print structure var
void	lst_print_vars(t_var *vars);
//----------variable assignment-------------------------
int		check_var(char *line, t_info *info);
int		get_vars(char *line);
int		get_len(char *line);
char	*get_key(char *line);
char	*get_value(char *line);
void	var_lexer(t_var **var, char *line);
////////////////////////////////////////////
void	lst_add_front(t_new **cmd, t_list *lst);
void	lst_big_new(t_new **cmd, t_list *lst);
void	lst_add(t_new **cmd, t_list *lst);
void	lst_skip_node(t_new **cmd);
void	make_big_list(t_new **cmd);
void	ft_lst_join(t_new *cmd);
////////////////////////////////////////////
// ----------------Handling dollar----------------------
// utility for find redirection presence
void	make_all_zero(t_new *cmd);
// handle the flags for redirection >>, >, <<, <
void	find_redirection_presence(t_new *cmd);
// Find the presence of dollar
void	find_dollar_presence(t_new *cmd);
// check if the character meta or not returns one if true.
int		is_meta(char c);
int		is_meta_pipe(char c);
// contains |, <, >
int		is_no_dollar_meta(char c);
// space, tab, new line, &, ;, ()
int		is_no_dollar_meta1(char c);
// contatins space, tab, new line, |&;()<>:?+-=!@#$^{}[]|%*,.~
int		is_meta_special(char c);
// contatins space, tab, new line, |&;()<>:?+-=!@#$^{}[]|%*,.~1234567890
int		is_meta_special2(char c);
// get string length for dollar expansion
int		get_strlen(char *str);
//string join mehdy version
int		ft_strjoin_ps(char **prestr, char *sufstr, int8_t freesuf);
//  if success returns the matching env variable part after the equal sign.
char	*get_dollar_path(char *str, char **env);
// It returns normal string until dollar sign.
char	*get_str(char *str);
// It returns entire string with expansion
char	*get_expanded_string(char *str, char **env);
//loop through cmd and do dollar expansion.
void	dollar_expansion(t_new *cmd, char **env);
//It returns a list of expanded string
t_list	*get_expanded_list(char *str, char **env);
int		syntax_error(t_new *cmd);
t_list	*get_expanded_string2(char *str, char **env);
int		ft_expand1(t_list **lst, t_list *temp, char c);
int		ft_expand2(t_list **lst, t_list *temp, char c);
int		ft_expand3(t_list **lst, t_list *temp, char *str, char **env);
int		ft_expand4(t_list **lst, t_list *temp, char *str);
int		ft_expand5(t_list **lst, t_list *temp, char *str);
int		ft_expand6(t_list **lst, t_list *temp, char *str);
int		ft_expand7(t_list **lst, t_list *temp, char *str);
int		ft_move_string(char *str, int i, int flag);
char	*get_meta_pipe(char *str);
char	*get_meta1(char *str);
char	*get_meta(char *str);
int		normal_lexer_help(t_new **pars, t_info *info, char *str, int wc);
void	big_list_help(t_new **cmd);
void	lst_skip_node2(t_new *cmd);
void	lst_add(t_new **cmd, t_list *lst);
int		ft_putstr_fd1(char *s, int fd);
//---------------------------------------------//
//--------------Parsing Functions--------------//
//---------------------------------------------//

// builtins.c

int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_env(char **env, char **args);
char	*get_home(char **env);

// builtins1.c

int		ft_chdir(char **args, char **env);

//child.c

char	**args_array(t_new *lst);
int		buitin_switch(t_new *lst, char **env, char *file_name, int append);
int		child_execute(t_new *lst, char **path, char **env);

// enviroment.c

int		cpynewenv(char **new_env, char **env);
int		setnewenv(char **env);
int		valid_varible(char *var);
int		ft_unset(char **args, char **env);

//enviroment1

int		append_env(char **env, char *args, int j);
int		ft_export(char **args, char **env, char *file_name, int append);

//enviroment2

int		update_shlvl(char **env, char *var);
int		varlen(char *var);
int		append_env1(char **env, char *args, int j);

//here_doc.c

int		here_doc_input(t_new *lst);

//pipex_utils.c

t_new	*nxt_cmd(t_new *lst);
int		number_of_pipes(t_new *lst);
int		list_has_pipes(t_new *lst);
void	close_pipes(int (*fd)[2], int no_of_pipes);
int		print_error(char *problem, char *msg, int errrorno);

//pipex_utils1.c

void	clear_str_sep(char **str_sep);
int		ft_strjoin_ms(char **prestr, char *sufstr);
int		ft_strncmp_p(const char *s1, const char *s2, size_t n);
int		ft_strncmp_pc(const char *s1, const char *s2, size_t n);
void	ft_tolower_str(char *str);

//pipex_utils2.c

int		ft_lstadd_backhelper(t_list **head, void *content);
void	cleanexit(char **path, int (*fd)[2], int status, int *open_fds);
int		builtins(t_new *lst, char **env);
void	find_cmd(t_new **lst);
int		has_parentbuiltins(t_new *lst);

// pipex.c

int		excute(t_new *lst, char **env);

//redirection.c

int		redirect_input(t_new **lst, int *skpflag, int *inflag, char **filestr);
int		redirect_output(t_new **lst, int *skpflag,
			int *appendflag, char **filename);

//redirection2.c
int		hijack_stdin(int in_file, char *in_file_name);
int		hijack_stdout(int out_file, char *out_file_name,
			int append_flag, int flag);
int		redirect_loop(t_new **lst, char **in_file_name,
			char **out_file_name, int *append_flag);
int		adopted_child(int in_file, char *here_doc);
int		set_pipes2(t_new **lst, char **ifile_name,
			char **ofile_name, int *flag);

//signals.c
int		signals(void);
int		ft_exit(char **args, int child);

#endif