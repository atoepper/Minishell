/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_in_directory.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:14:02 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 10:14:13 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int search_file_in_directory(const char *directory, const char *filename) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            closedir(dp);
            return 1;  // Datei gefunden
        }
    }

    closedir(dp);
    return 0;  // Datei nicht gefunden
}


int	main(void)
{
	char *path;
	char **lst_path;
	int i;
	// const char *directory = "/bin";
    // const char *filename = "echo";

	path = getenv("PATH");
	if (path != NULL) {
        // Ausgabe des PATH-Werts
        printf("PATH: %s\n", path);
    } else {
        // Fehlerbehandlung, falls PATH nicht gesetzt ist
        printf("The PATH environment variable is not set.\n");
    }
	lst_path = ft_split(path, ':');
	i = 0;
	while (lst_path[i] != NULL)
	{
		printf("%s\n", lst_path[i]);
		i++;
	}


    while (search_file_in_directory(directory, filename) != 0);

    // if (result == 1) {
    //     printf("File '%s' found in directory '%s'.\n", filename, directory);
    // } else if (result == 0) {
    //     printf("File '%s' not found in directory '%s'.\n", filename, directory);
    // } else {
    //     printf("An error occurred while searching the directory.\n");
    // }


	return (0);
}