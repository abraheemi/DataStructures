package edu.uic.cs342.airhee2;

/* ################################## Node Class ################################## */
public class Node {
	private Vehicle data;
	private Node next = null;
	
	public Node(){
		next = null;
	}
	
	public Node(Vehicle newData){
		data = newData;
		next = null;
	}
	
	public Vehicle getData(){
		return data;
	}
	
	public Node getNext(){
		return next;
	}
	
	public void setData(Vehicle newData){
		data = newData;
	}
	
	public void setNext(Node newNext){
		next = newNext;
	}

}
