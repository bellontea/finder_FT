#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int finder(char *dir_name)
{
	// Добавление '/' в конец к названию пути, если нет изначально
	if (dir_name[strlen(dir_name) - 1] != '/')
	{
		dir_name = realloc(dir_name, strlen(dir_name) + 2);
		dir_name = strcat(dir_name, "/");
	}
	// Инициализация dir и проверка, открылась ли директория
	DIR *dir = opendir(dir_name);
	if (!dir)
	{
		perror("Error");
		free(dir_name);
		return (1);
	}
	struct dirent *entry;
	// Считывание данных из директории циклом
	while ((entry = readdir(dir)) != NULL)
	{
		// Пропуск '.' и '..'
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		printf("%s%s\n", dir_name, entry->d_name);
		// Рекурсивный обход дочерних каталогов
		if (entry->d_type == DT_DIR)
		{
			char *subdir_name = strdup(dir_name);
			subdir_name = realloc(subdir_name, strlen(subdir_name) + strlen(entry->d_name) + 1);
			finder(strcat(subdir_name, entry->d_name));
		}
	}
	closedir(dir);
	free(dir_name);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: bad arguments\n");
		return (1);
	}
	return finder(strdup(argv[1]));
}