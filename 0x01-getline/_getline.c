#include "_getline.h"

static size_t numfd;
static listfiled *fdhead;

/**
 * linknd - node linker
 * @head: pointer to head node of linked list
 * @n: node to link
 * @sort: sorter
 */

void linknd(void *head, void *n, size_t sort)
{
	listc **curate;
	listfiled **fdc;

	if (!sort)
	{
		curate = (listc **) head;
		while (*curate)
			curate = &(*curate)->next;
		((listc *) n)->next = *curate;
		*curate = n;
	}
	else
	{
		fdc = (listfiled **) head;
		while (*fdc && ((listfiled *) n)->fd > (*fdc)->fd)
			fdc = &(*fdc)->next;
		((listfiled *) n)->next = *fdc;
		*fdc = n;
	}
}

/**
 * creatend - creates linked list node
 * @src: str
 * @end: to copy
 * @nl: line number incrementer
 * @lstfd: create node
 * @fd: file descriptor
 *
 * Return: node of new linked list
 */

void *creatend(char *src, size_t end, int nl, size_t lstfd, int fd)
{
	void *n;

	if (!lstfd)
	{
		static size_t line = 1;

		n = (listc *) malloc(sizeof(listc));

		if (!n)
			return (NULL);

		((listc *) n)->line = line;

		if (nl)
			++line;

		((listc *) n)->s = malloc((end + 1));

		if (!n)
			return (NULL);

		memcpy(((listc *) n)->s, src, end);
		((listc *) n)->s[end] = '\0';
		((listc *) n)->size = end + 1;
		((listc *) n)->next = NULL;
	}

	else
	{
		n = (listfiled *) malloc(sizeof(listfiled));

		if (!n)
			return (NULL);

		((listfiled *) n)->fd = fd;
		((listfiled *) n)->rd = 0;
		((listfiled *) n)->head = NULL;
		((listfiled *) n)->next = NULL;
	}
	return (n);
}

/**
 * parse_reall - changes the size of the memory
 * @ptr: pointer to memory
 * @old_size: old size
 * @n_size: new size
 * @parseline: parser
 * @file: string to file
 * @head: pointer to node of linked list
 *
 * Return: pointer to allocated memory
 */

void *parse_reall(void *ptr, size_t old_size, size_t n_size,
		size_t parseline, char *file, listc **head)
{
	void *nptr;
	size_t a, st;
	listc *n = NULL;

	if (parseline)
	{
		for (st = a = 0; file[a]; ++a)
			if (file[a] == '\n')
			{
				n = creatend(&file[st], a - st, 1, 0, 0);
				linknd(head, n, 0);
				st = a + 1;
			}
		if (file[st])
		{
			n = creatend(&file[st], a - st, 0, 0, 0);
			linknd(head, n, 0);
		}
		if (!n)
			return ((char *) NULL);
	}
	else
	{
		if (n_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		if (!ptr)
			return (malloc(n_size));
		if (n_size <= old_size)
			return (ptr);
		nptr = malloc(n_size);
		if (nptr)
		{
			memcpy(nptr, ptr, old_size);
			free(ptr);
		}
	}
	return (nptr);
}

/**
 * _strncat - string concatenator
 * @dest: string to concatenate
 * @src: string to copy
 * @n: amount of bytes to copy
 *
 * Return: pointer to new string
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t d_len;
	size_t i;

	for (i = 0; dest[i]; ++i)
	;

	d_len = i;

	for (i = 0; i < n && src[i]; ++i)
		dest[d_len + i] = src[i];
	dest[d_len + i] = '\0';

	return (dest);
}

/**
 * parse_fd - parser
 * @fdhead: pointer to head node
 * @fd: file descriptor
 * @file:freer
 *
 * Return: created list
 */
listfiled *parse_fd(listfiled **fdhead, const int fd, char *file)
{
	listfiled *fdc;
	listc *curate, *temp;

	if (fd == -1)
	{
		while (*fdhead)
		{
			curate = (*fdhead)->head;
			while (curate)
			{
				temp = curate;
				curate = curate->next;
				free(temp->s);
				free(temp);
			}
			fdc = *fdhead;
			*fdhead = (*fdhead)->next;
			free(fdc);
		}
		free(file);
		return (NULL);
	}
	fdc = *fdhead;
	while (fdc)
	{
		if (fd == fdc->fd)
			break;
		fdc = fdc->next;
	}
	if (!fdc)
	{
		fdc = creatend('\0', 0, 0, 1, fd);
		if (!fdc)
			return (NULL);
		linknd(fdhead, fdc, 1);
		++numfd;
	}
	return (fdc);
}

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: string excluding nline character or NULL
 */

char *_getline(const int fd)
{
	size_t linsiz = READ_SIZE + 1;
	char *line, buf[READ_SIZE] = {0}, *file = malloc(linsiz);
	ssize_t byte;
	listfiled *fdc;
	listc *temp;

	if (!file)
		return (NULL);
	memset(file, 0, linsiz);
	fdc = parse_fd(&fdhead, fd, file);
	if (!fdc)
		return (NULL);
	if (!fdc->rd)
		for (; (byte = read(fd, buf, READ_SIZE)) > 0; fdc->rd = 1)
		{
			_strncat(file, buf, READ_SIZE);
			linsiz += READ_SIZE;
			file = parse_reall(file, linsiz - READ_SIZE, linsiz, 0, NULL, NULL);
			if (!file)
				return (NULL);
			memset(buf, 0, READ_SIZE);
		}
	if (fdc->rd)
		line = parse_reall(NULL, 0, 0, 1, file, &fdc->head);
	free(file);
	if (!fdc->head)
	{
		if (numfd == 1)
			free(fdc);
		return (NULL);
	}
	temp = fdc->head;
	fdc->head = fdc->head->next;
	line = malloc(temp->size);
	if (!line)
		return (NULL);
	memcpy(line, temp->s, temp->size);
	free(temp->s);
	free(temp);
	return (line);
}
