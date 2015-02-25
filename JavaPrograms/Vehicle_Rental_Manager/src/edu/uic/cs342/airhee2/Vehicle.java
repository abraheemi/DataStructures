package edu.uic.cs342.airhee2;

/* ################################## Vehicle Super Class ################################## */
public abstract class Vehicle {
	// The following fields are shared by all subclasses
	private String kind;
	private String make;
	private String model;
	private int year;
	private String status;
	private int id;
	private double cost;
	//private String bodyType;
	
	public Vehicle() {
	}
	
	public Vehicle(String Kind, String Make, String Model, 
			int Year, String Status, int Id, double Cost) {
		kind = Kind;
		make = Make;
		model = Model;
		year = Year;
		status = Status;
		id = Id;
		cost = Cost;
	}
	
	public String getKind(){
		return kind;
	}
	
	public String getMake(){
		return make;
	}

	public String getModel(){
		return model;
	}
	
	public int getYear(){
		return year;
	}
	
	public String getStatus(){
		return status;
	}
	
	public int getId(){
		return id;
	}
	
	public double getCost(){
		return cost;
	}
	
	public void setStatus(String newStat){
		status = newStat;
	}
	
}
