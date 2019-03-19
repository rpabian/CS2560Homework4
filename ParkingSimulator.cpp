#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class PoliceOfficer;

class ParkedCar
{
private:
	string m_make, m_model, m_color;
	int m_licenseNum, m_minsParked;
public:
	ParkedCar(string make, string model, string color,
		int licenseNum, int minsParked)
	{
		m_make = make;
		m_model = model;
		m_color = color;
		m_licenseNum = licenseNum;
		m_minsParked = minsParked;
	}
	ParkedCar() { ParkedCar("", "", "", 0, 0); }
	void setMake(string make) { m_make = make; }
	void setModel(string model) { m_model = model; }
	void setColor(string color) { m_color = color; }
	void setLicenseNum(int licenseNum) { m_licenseNum = licenseNum; }
	void setMinsParked(int minsParked) { m_minsParked = minsParked; }
	string getMake() { return m_make; }
	string getModel() { return m_model; }
	string getColor() { return m_color; }
	int getLicenseNum() { return m_licenseNum; }
	int getMinsParked() const { return m_minsParked; }
};

class ParkingMeter
{
private:
	int m_minsPurchased;
public:
	ParkingMeter(int minsPurchased)
	{
		m_minsPurchased = minsPurchased;
	}
	ParkingMeter() { ParkingMeter(0); }
	void setMinsPurchased(int minsPurchased)
	{
		m_minsPurchased = minsPurchased;
	}
	int getMinsPurchased() const { return m_minsPurchased; }
};

class ParkingTicket
{
private:
	int m_fineTime;
	ParkedCar parkedCar;
public:
	ParkingTicket(int fineTime, const ParkedCar &parkedCarObject)
	{
		m_fineTime = fineTime;
		parkedCar = parkedCarObject;
	}

	ParkingTicket(int fineTime) { m_fineTime = fineTime; }
	ParkingTicket() { ParkingTicket(0); }
	~ParkingTicket() {}
	void setParkedCar(const ParkedCar &parkedCarObject)
	{
		parkedCar = parkedCarObject;
	}
	void reportParkedCar()
	{
		cout << "Parked Car details: \n"
			<< "Make: " << parkedCar.getMake() << "\n"
			<< "Model: " << parkedCar.getModel() << "\n"
			<< "Color: " << parkedCar.getColor() << "\n"
			<< "License Plate: " << parkedCar.getLicenseNum() << endl;
	}
	void reportPoliceOfficer(PoliceOfficer &policeOfficer);

	int getFineAmount()
	{
		int fineHours = m_fineTime / 60;
		if (m_fineTime % 60 != 0)
			fineHours += 1;
		int fineAmount = 25 + (10 * (fineHours - 1));
		return fineAmount;
	}
};

class PoliceOfficer
{
private:
	string m_name;
	int m_badgeNum;

public:
	PoliceOfficer(string name, int badgeNum)
	{
		m_name = name;
		m_badgeNum = badgeNum;
	}
	PoliceOfficer()
	{
		PoliceOfficer("", 0);
	}
	void setName(string name) { m_name = name; }
	void setBadgeNum(int badgeNum) { m_badgeNum = badgeNum; }
	string getName() const { return m_name; }
	int getBadgeNum() const { return m_badgeNum; }
	ParkingTicket* inspectCar(const ParkedCar & parkedCarObject,
		const ParkingMeter & parkingMeterObject)
	{
		int parkedTime = parkedCarObject.getMinsParked();
		if (parkedCarObject.getMinsParked() > parkingMeterObject.getMinsPurchased())
		{
			int fineTime = parkedCarObject.getMinsParked() - parkingMeterObject.getMinsPurchased();
			ParkingTicket *ticket = new ParkingTicket(fineTime, parkedCarObject);
			return ticket;
		}
		else return NULL;
	}
	~PoliceOfficer() {}
	friend void ParkingTicket::reportPoliceOfficer(PoliceOfficer &policeOfficer);
};

void ParkingTicket::reportPoliceOfficer(PoliceOfficer &policeOfficer)
{
	cout << "Police Officer: \n" << "Name: "
		<< policeOfficer.getName() << "\n"
		<< "Badge: " << policeOfficer.getBadgeNum()
		<< endl;
}

int main()
{
	ParkedCar mazda("Mazda", "Mazda 3", "Grey", 12345, 90);
	ParkingMeter meter1(60);
	PoliceOfficer joe("Joe", 6789);
	ParkingTicket* joeTicket;

	cout << "Parking Meter Minutes: " << meter1.getMinsPurchased()
		<< "\nPolice officer inspecting car parked in front of meter." 
		<< endl;

	joeTicket = joe.inspectCar(mazda, meter1);
	cout << "Minutes Parked: " 
		<< mazda.getMinsParked() << endl;
	(*joeTicket).reportParkedCar();
	int fineAmount = (*joeTicket).getFineAmount();
	cout << "Fine for the Mazda parked: "
		<< fineAmount << endl;
	(*joeTicket).reportPoliceOfficer(joe);

	cout << "\n\n" << endl;

	ParkedCar toyota("Toyota", "Celica", "Black", 6789, 150);
	ParkingTicket* joeTicket2;

	cout << "Parking Meter Minutes: " << meter1.getMinsPurchased()
		<< "\nPolice officer inspecting car parked in front of meter."
		<< endl;

	joeTicket2 = joe.inspectCar(toyota, meter1);
	cout << "Minutes Parked: "
		<< toyota.getMinsParked() << endl;
	(*joeTicket2).reportParkedCar();
	int fineAmount2 = (*joeTicket2).getFineAmount();
	cout << "Fine for the toyota parked: "
		<< fineAmount2 << endl;
	(*joeTicket2).reportPoliceOfficer(joe);

	delete joeTicket;
	delete joeTicket2;

	return 0;
}