#include <pthread.h>
#include "list.h"
#include "multithreading.h"

/**
 * create_task - creates the task
 * @entry: pointer to the entry function of the task
 * @param: parameter that will later be passed to the entry function
 * Return: pointer to the created task structure
*/

task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task;

	task = calloc(1, sizeof(*task));

	if (!task)
		return (NULL);

	task->entry = entry;
	task->param = param;
	task->status = PENDING;

	if (pthread_mutex_init(&task->lock, NULL))
	{
		free(task);
		return (NULL);
	}

	return (task);
}

/**
 * destroy_task - frees task
 * @task: pointer to the task to destroy
*/

void destroy_task(task_t *task)
{
	list_destroy(task->result, free);
	free(task->result);
	pthread_mutex_destroy(&task->lock);
	free(task);
}

/**
 * exec_tasks - assigns a thread to a task
 * @tasks: pointer to the list of tasks to be executed
 * Return: struct
*/

void *exec_tasks(list_t const *tasks)
{
	node_t *root;
	task_t *task;
	size_t holder = 0;

	root = tasks->head;

	while (root)
	{
		task = root->content;
		if (pthread_mutex_trylock(&task->lock) == 0)
		{
			if (task->status == PENDING)
			{
				task->status = STARTED;
				tprintf("[%02lu] Started\n", holder);
				task->result = task->entry(task->param);
				tprintf("[%02lu] Success\n", holder);
				task->status = SUCCESS;
			}
			pthread_mutex_unlock(&task->lock);
		}

		root = root->next;
		++holder;
	}
	return (NULL);
}
