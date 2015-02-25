package edu.uic.cs342.airhee2;

import java.io.*;
import java.util.*;

/* ################################## Driver Class ################################## */
public class VRM {
	public VRM(){
	}
	
	public static void displayCommandInfo(){
		System.out.println("Beginning Vehicle Rental Manager program...\n");
		System.out.println("Command list: ");
		System.out.println("v: add a new vehicle");
		System.out.println("c: Change vehicle status");
		System.out.println("d: reset database");
		System.out.println("l: list all vehicles in the database");
		System.out.println("a: list all vehicles that are available for rental");
		System.out.println("s: sort database by vehicle make and model");
		System.out.println("q: quit VRM\n");
	}
	
	public static void main(String[] args) {
		List l = new List();        // Linked list for storing Vehicle instances
		Vehicle v;                  // Vehicle instance
		
		String kind;
		String mk;        // Make
		String mdl;       // Model
		int yr;              // Year
		String stat;  // Status
		int id;             // ID
		double cst;       // Daily cost
		String type;      // Body type (for Car)
		double cgW;         // Cargo Weight (for Truck)
		double len;         // Length (for Minivan)
		double wid;         // Width (for Minivan)
		
		displayCommandInfo();
		
		Scanner s = new Scanner(System.in);
		System.out.print("Enter command: ");
		
		while(true){
			//Scanner s = new Scanner(System.in);
			String command = s.next(); 
			char ch = command.charAt(0); // Extracts first input character which will be the command
			
			// Quit the VRM
			if (ch == 'q'){
				s.close();
				System.out.println("Exiting Vehicle Rental Manager...");
				return;
			}
			// Add a new vehicle
			// Item information can be entered in a single line or multiple lines
			else if (ch == 'v'){
				System.out.print("Enter vehicle kind (Car, Truck, or Minivan): ");
				kind = s.next();  System.out.println();
				
				System.out.print("Enter vehicle make: ");
				mk = s.next();  System.out.println();
				
				System.out.print("Enter vehicle model: ");
				mdl = s.next();  System.out.println();
				
				System.out.print("Enter vehicle year: ");
				yr = s.nextInt();  System.out.println();
				
				System.out.print("Enter vehicle status (available, unavailable, or repair): ");
				stat = s.next();  System.out.println();
				
				System.out.print("Enter vehicle daily cost: ");
				cst = s.nextDouble();  System.out.println();
				
				id = l.tally();
				// Prompts for additional information depending on kind of vehicle
				if( kind.equals("Car") ){
					System.out.print("Please enter the body type: ");
					type = s.next();  System.out.println();
					v = new Car(kind, mk, mdl, yr, stat, id, cst, type);
					l.insert(v);
				}
				else if ( kind.equals("Truck") ){
					System.out.print("Please enter the cargo weight: ");
					cgW = s.nextDouble();  System.out.println();
					v = new Truck(kind, mk, mdl, yr, stat, id, cst, cgW);
					l.insert(v);
				}
				else if ( kind.equals("Minivan") ){
					System.out.print("Please enter the Minivan length: ");
					len = s.nextDouble();  System.out.println();
					System.out.print("Please enter the Minivan width: ");
					wid = s.nextDouble();  System.out.println();
					v = new Minivan(kind, mk, mdl, yr, stat, id, cst, len, wid);
					l.insert(v);
				}
				else{
					System.out.println("Invalid vehicle kind");
					continue;
					//s.nextLine(); // Clean up the rest of the line
				}
				
			}
			// Change vehicle status
			else if (ch == 'c'){
				System.out.print("Please enter a vehicle ID: ");
				id = s.nextInt();  System.out.println();
				System.out.print("Please enter a new status (available, unavailable, repair): ");
				stat = s.next();  System.out.println();
				l.setNewStat(stat, id); // Sets new status for given vehicle ID
			}
			// Empty list of vehicles
			else if (ch == 'd'){
				l = new List(); // Resets head and tail to null
				System.out.println("Linked list has been reset");
			}
			// List all vehicles
			else if (ch == 'l'){
				l.display();
			}
			// List vehicles only if status is available for rental
			else if (ch == 'a'){
				l.displayIfAvailable();
			}
			// Sort linked list by make and model of vehicle
			else if (ch == 's'){
				l.sortLinkedList();
				System.out.println("List is now sorted");
			}
			else{
				System.out.println("Invalid command. Please re-enter command");
				s.nextLine(); // Clean up the rest of the line
			}
			System.out.print("Enter command: ");
		}
		
	}
	
}
