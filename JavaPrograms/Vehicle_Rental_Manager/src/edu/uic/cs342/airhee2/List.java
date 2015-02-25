package edu.uic.cs342.airhee2;

import java.io.*;
import java.util.*;

/* ################################## Linked List Class ################################## */
// This class stores, prints, sorts vehicle objects
public class List {
	protected Node head = null;
	protected Node tail = null;
	private static int tally = 0; // This acts as the vehicle ID
	
	public List(){
		head = null;
		tail = null;
		tally = 0;
	}
	
	public List(Vehicle data){
		head = tail = new Node(data);
		tally++;
	}
	
	// This acts as the vehicle ID
	public static int tally(){
		return tally;
	}
	
	public boolean isEmpty(){
		if(head == null)
			return true;
		else
			return false;
	}
	
	public List insert(Vehicle data){
		Node p = new Node(data);
		
		if(isEmpty())
			head = tail = p;
		else{
			tail.setNext(p);
			tail = p;
		}
		tally++;
		return this;
	}
	
	// This is called when user enters 's' to sort
	public void sortLinkedList(){
		//Convert linked list into an array of nodes
		Node arr[] = toArr(); 
		bubble(arr);
		int i;
		head = null; 
		// Now change the previous unsorted linked list into a sorted list
		for(i=0; i<arr.length; i++){
			insert(arr[i].getData());
		}
			
	}
	
	// NOT USED (didn't work)
	public List copy(List l){
		Node p = l.head;
		Node tmp = head;
		String s1, s2;
		
		while(p != null){
			if(head == null){
				Node newNode = new Node(p.getData());
				head = tail = newNode;
			}
			else{
				s1 = p.getData().getMake();
				s2 = head.getData().getMake();
				if(s1.compareToIgnoreCase(s2) < 0){
					Node newNode = new Node(p.getData());
					newNode.setNext(head);
					head.setNext(newNode);
				}
				else{
					tmp = head;
					s2 = tmp.getNext().getData().getMake();
					while(s1.compareToIgnoreCase(s2) > 0 && tmp.getNext() != null){
						tmp = tmp.getNext();
					}
					Node pNext = tmp.getNext();
					//Node pTemp = new Node(p.getData());
					tmp.setNext(new Node(p.getData()));
					tmp = tmp.getNext();
					tmp.setNext(pNext);
				}
			}
			
			p = p.getNext();
		}
		
		return this;
	}
	
	// Changes vehicle availability
	public void setNewStat(String newStat, int vId){
		Node p = head;
		
		if(isEmpty()){
			System.out.println("List is empty");
			return;
		}
		
		while(p != null){
			if(p.getData().getId() == vId){
				p.getData().setStatus(newStat);
				return;
			}
			p = p.getNext();
		}
		System.out.println("ID " + vId + " does not exist in list");
	}
	
	// Used with sortLinkedList()
	private int compString(String str1, String str2){
		
		if(str1.compareTo(str2) == 0){
			return 0;
		}
		char[] arr1 = str1.toCharArray();
		char[] arr2 = str2.toCharArray();
		int i;
		for(i=0; i<str1.length(); i++){
			if((arr1[i] - arr2[i]) < 0){
				return -1;
			}
			else if((arr1[i] - arr2[i]) > 0){
				return 1;
			}
		}
		return 1;
	}
	
	// Used with sortLinkedList()
	private Node[] toArr(){
		Node temp = head;
		Node nodeArr[] = new Node[tally];
		int i;
		
		for(i=0; i<tally; i++){
			nodeArr[i] = temp;
			temp = temp.getNext();
		}
		return nodeArr;
		
	}
	
	public void display(){
		Node p = head;
		
		if(isEmpty()){
			System.out.println("List is empty");
			return;
		}
		
		System.out.println("Displaying all vehicles: ");
		
		System.out.println("ID\tMake\tModel\tYear\tAvailability\tDailyCost\t\tOther");
		
		while(p != null){
			System.out.print(p.getData().getId() + ". \t"); 
			System.out.print(p.getData().getMake());
			System.out.print("\t" + p.getData().getModel());
			System.out.print("\t" + p.getData().getYear());
			System.out.print("\t" + p.getData().getStatus());
			System.out.print("\t\t" + p.getData().getCost());
			
			if( (p.getData().getKind()).equals("Car"))
				System.out.println("\t\tBodyType" + ( (Car)(p.getData()) ).getBodyType() );
			else if( (p.getData().getKind()).equals("Truck"))
				System.out.println("\tCargoWeight: " + ( (Truck)(p.getData()) ).getWeight() );
			else if( (p.getData().getKind()).equals("Minivan")){
				System.out.print("\t\tLength: " + ( (Minivan)(p.getData()) ).getLength() );
				System.out.println("; Width: " + ( (Minivan)(p.getData()) ).getWidth() );
			}
			
			p = p.getNext();
		}
		
	}
	
	public void displayIfAvailable(){
		Node p = head;
		
		if(isEmpty()){
			System.out.println("List is empty");
			return;
		}
		
		System.out.println("Displaying Available vehicles only: ");
		
		System.out.println("ID\tMake\tModel\tYear\tAvailability\tDailyCost\t\tOther");
		
		while(p != null){
			if( (p.getData().getStatus()).equals("available")){
				System.out.print(p.getData().getId() + ". \t"); 
				System.out.print(p.getData().getMake());
				System.out.print("\t" + p.getData().getModel());
				System.out.print("\t" + p.getData().getYear());
				System.out.print("\t" + p.getData().getStatus());
				System.out.print("\t\t" + p.getData().getCost());
				
				if( (p.getData().getKind()).equals("Car"))
					System.out.println("\t\tBodyType" + ( (Car)(p.getData()) ).getBodyType() );
				else if( (p.getData().getKind()).equals("Truck"))
					System.out.println("\tCargoWeight: " + ( (Truck)(p.getData()) ).getWeight() );
				else if( (p.getData().getKind()).equals("Minivan")){
					System.out.print("\tLength: " + ( (Minivan)(p.getData()) ).getLength() );
					System.out.println("; Width: " + ( (Minivan)(p.getData()) ).getWidth() );
				}
			}
			p = p.getNext();
		}
		
	}
	
	// Implements bubble sort
	// Used to sort the array of nodes
	// Used with sortLinkedList()
	private void bubble(Node[] arr){
		boolean check = true;
		String s1Make, s1Model, s2Make, s2Model;

		while(check){
			check = false; // Will evaluate to false once sorting if finished
			int i;
			
			for(i=0; i<(arr.length)-1; i++){
				Node temp;
				// Assign Make to strings to make it easy to compare them
				s1Make = arr[i].getData().getMake();
				s1Model = arr[i].getData().getModel();
				s2Make = arr[i+1].getData().getMake();
				s2Model = arr[i+1].getData().getModel();
				
				if(compString(s1Make, s2Make) == 0){
					if(compString(s1Model, s2Model) == 1){
						//swap two nodes
						temp = arr[i];
	                    arr[i] = arr[i+1];
	                    arr[i+1] = temp; 
	                    check = true;
					}
				}
				else if(compString(s1Make, s2Make) == 1){
					//swap two nodes
					temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp; 
                    check = true;
				}		
			}
		}
	}
	
}
