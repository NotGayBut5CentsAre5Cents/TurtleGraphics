package org.elsys.todo.impl;


import java.util.Arrays;
import java.util.function.Predicate;

import org.elsys.todo.Criteria;
import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;

public class CriteriaImpl implements Criteria{

	Predicate<Task> predicate;
	
	public CriteriaImpl(Status status) {
		predicate = (t) -> t.getStatus() == status;
	}
	
	public CriteriaImpl(Priority priority) {
		predicate = (t) -> t.getPriority() == priority;
	}
	
	public CriteriaImpl(String[] tags) {
		predicate = (t) -> Arrays.asList(t.getTags())
						.containsAll(Arrays.asList(tags));
	}
	
	public CriteriaImpl(Predicate<Task> predicate) {
		this.predicate = predicate;
	}
	
	public Predicate<Task> getPredicate() {
		return predicate;
	}
	
	@Override
	public Criteria and(Criteria other) {
		return new CriteriaImpl(predicate.and(other.getPredicate()));
	}

	@Override
	public Criteria or(Criteria other) {
		return new CriteriaImpl(predicate.or(other.getPredicate()));
	}

	@Override
	public Criteria not() {
		return new CriteriaImpl(predicate.negate());
	}
	
}
