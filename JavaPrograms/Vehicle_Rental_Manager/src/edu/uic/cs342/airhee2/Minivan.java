package edu.uic.cs342.airhee2;

public class Minivan extends Vehicle {
	private double length;
	private double width;
	
	public Minivan() {
	}

	// Calls Super class Vehicle to initialize fields
	public Minivan(String Kind, String Make, String Model, int Year, 
			String Status, int Id, double Cost, double len, double wid){
		super(Kind, Make, Model, Year, Status, Id, Cost);
		length = len;
		width = wid;
	}
	
	// The following is information specific to this class
	public double getLength(){
		return length;
	}
	
	public double getWidth(){
		return width;
	}
}
