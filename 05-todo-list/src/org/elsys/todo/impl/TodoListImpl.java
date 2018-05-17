package org.elsys.todo.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.elsys.todo.Criteria;
import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;
import org.elsys.todo.TodoList;

public class TodoListImpl implements TodoList{

	List<Task> tasks;
	
	public TodoListImpl(String input){
		tasks = new ArrayList<Task>();
		String[] fields = input.split("\\||\\r?\\n");
		for(int i = 0; i < fields.length; i += 4) {
			tasks.add(new TaskImpl(
				Status.valueOf(fields[i].trim().toUpperCase()),
				fields[i + 1],
				Priority.valueOf(fields[i + 2].trim().toUpperCase()),
				fields[i + 3].trim().split("\\s*,\\s*")));
		}
	}
	
	public TodoListImpl(List<Task> tasks) {
		this.tasks = tasks;
	}
	
	@Override
	public Boolean isCompleted() {
		return tasks.stream().allMatch(t -> t.getStatus() == Status.DONE);
	}

	@Override
	public Double percentageCompleted() {
		return (double)tasks.stream().filter(t -> t.getStatus() == Status.DONE).count() / tasks.size() * 100;
	}

	@Override
	public List<Task> getTasks() {
		return tasks;
	}

	@Override
	public TodoList filter(Criteria criteria) {
		return new TodoListImpl(tasks.stream().filter(criteria.getPredicate()).collect(Collectors.toList()));
	}

	@Override
	public TodoList join(TodoList other) {
		return new TodoListImpl(Stream.concat(tasks.stream(), other.getTasks().stream())
                             	.distinct()
								.collect(Collectors.toList()));
	}
	
}
