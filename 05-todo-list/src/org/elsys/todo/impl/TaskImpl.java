package org.elsys.todo.impl;

import java.util.Arrays;

import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.Task;

public class TaskImpl implements Task{

	Status status; 
	String description;
	Priority priority;
	String[] tags;
	
	public TaskImpl(Status status, String description, Priority priority, String[] tags) {
		this.status = status;
		this.description = description;
		this.priority = priority;
		this.tags = tags;
	}
	
	@Override
	public Status getStatus() {
		return status;
	}

	@Override
	public String getDescription() {
		return description;
	}

	@Override
	public Priority getPriority() {
		return priority;
	}

	@Override
	public String[] getTags() {
		return tags;
	}

	@Override
	public boolean equals(Object o) {
		if (o == null) {
	        return false;
	    }
	    if (!Task.class.isAssignableFrom(o.getClass())) {
	        return false;
	    }
	    final Task other = (Task) o;
	    if ((this.status == null) ? (other.getStatus() != null) : !(this.status == other.getStatus())) {
	        return false;
	    }
	    if ((this.priority == null) ? (other.getPriority() != null) : !(this.priority == other.getPriority())) {
	        return false;
	    }
	    if(!this.description.equals(other.getDescription())) {
	    	return false;
	    }
	    if(!Arrays.equals(this.tags, other.getTags())) {
	    	return false;
	    }
	    return true;
	}
	
	@Override
	public int hashCode() {
		int hash = 3;
		hash = 17 * hash + (status != null ? status.hashCode() : 0);
		hash = 17 * hash + (description != null ? description.hashCode() : 0);
		hash = 17 * hash + (description != null ? priority.hashCode() : 0);
		hash = 17 * hash + Arrays.deepHashCode(tags);
		return hash;
	}
	
}
