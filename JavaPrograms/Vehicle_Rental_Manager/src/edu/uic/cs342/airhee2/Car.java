package edu.uic.cs342.airhee2;

public class Car extends Vehicle {
	private String bodyType;
	
	public Car() {
	}
	
	// Calls Super class Vehicle to initialize fields
	public Car(String Kind, String Make, String Model, int Year, 
			String Status, int Id, double Cost, String BodyType){
		super(Kind, Make, Model, Year, Status, Id, Cost);
		bodyType = BodyType;
	}
	
	// The following is information specific to this class
	public String getBodyType(){
		return bodyType;
	}
	
}
