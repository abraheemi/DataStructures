package edu.uic.cs342.airhee2;

public class Truck extends Vehicle {
	private double cargoWeight;
	
	public Truck() {	
	}
	
	// Calls Super class Vehicle to initialize fields
	public Truck(String Kind, String Make, String Model, int Year, 
			String Status, int Id, double Cost, double CargoWeight){
		super(Kind, Make, Model, Year, Status, Id, Cost);
		cargoWeight = CargoWeight;
	}
	
	// The following is information specific to this class
	public double getWeight(){
		return cargoWeight;
	}

}
