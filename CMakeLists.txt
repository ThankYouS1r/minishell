cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-ltermcap")
find_library(minishell minishell_library includes)
add_executable(minishell srcs/main/minishell.c libs/libft/ft_crash.c libs/libft/ft_malloc.c libs/libft/ft_realloc.c)
target_link_libraries(minishell LINK_PUBLIC $(minishell_library))