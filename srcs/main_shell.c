#include "../includes/minishell.h"

int         len_env(char *env[])
{
    int     len;

    len = 0;
    while (env[len])
        len++;
    return (len);
}

shell_t     *init_save_env(int argc, char *argv[], char *env[])
{
    shell_t *shell;
    int     size;
    int     i;

    (void)argc;
    (void)argv;
    if (!(shell = (shell_t*)malloc(sizeof(shell_t) * 1)))
        return (NULL);
    size = len_env(env);
    if (!(shell->env = (char**)malloc(sizeof(char*) * (size + 1))))
        return (NULL);
    shell->env[size] = NULL;
    i = -1;
    while (env[++i])
        if (!(shell->env[i] = ft_strdup(env[i])))
            return (NULL);
    return (shell);
}

int         main(int argc, char *argv[], char *env[])
{
    char    *line;
    int     status;
    shell_t *shell;

    if (!(shell = init_save_env(argc, argv, env)))
        return (ft_error("Failed allocate memory"));
    status = 1;
    while (status)
    {
        display_prompt(shell);
        get_next_line(STDIN_FILENO, &line);
        shell->commands = ft_split(line, ';');
        free(line);
        status = parse_commands(shell);
        free(shell->commands);
    }
    return (0);
}