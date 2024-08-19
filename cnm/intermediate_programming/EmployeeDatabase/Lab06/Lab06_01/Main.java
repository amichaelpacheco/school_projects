/*
Programming Assignment Lab 06 part 1
======================================
School of Business and Information Technology
Central New Mexico Community College
Course: CSCI-2251-R01, Spring 2021
Author: Michael Pacheco
email: mpacheco121@cnm.edu 
Date: 04/15/2021
*/
import java.util.*;
import java.io.*;
import java.io.IOException; 
import java.util.Scanner;
import java.util.Arrays;
import java.util.*;
import java.nio.file.*;
import java.lang.*;
import java.sql.*;
public class Main{

	public static void main(String[] args) throws IOException{
		Scanner in = new Scanner(System.in);
		String choice ="";
		while(true){

			System.out.print("Would you like to start/continue? (y/n): ");
			choice=in.next();
			if(choice.equals("n")){
				System.out.println("Goodbye!");
				System.exit(1);
			}
			else if (choice.equals("y")){
				addEmployee();
			}
			else{
				System.out.println("enter y or n then hit ENTER");
			}
		}
	}
	public static void addEmployee(){
		//get useful objects
		Scanner input = new Scanner(System.in);
		Random random =new Random();
		//declare and initialize variables
		String ssn="";
		String first_name="";
		String last_name="";
		String birthday="";
		String employeeType="";
		String departmentName="";
		String[] employeeTypeArr ={"salariedEmployee","comissionEmployee"};
		String[] departmentNameArr ={"Sales","R&D","HR"};
		float weeklySalary=0;
		float bonus=0;
		int gross_sales=0;
		float commission_rate=0;
		//used for boolean
		String verify ="";		
		//gather info
		//
		System.out.println("Enter Social Security No. in format \"111-11-1111\"");
		System.out.print("SSN: ");
		ssn=input.next();
		while(true){
			System.out.print("Verify your Social Security No.: ");
			verify=input.next();
			if(ssn.equals(verify)){
				break;
			}
			else{
				System.out.println("SSN does not match");
			}
		}			
		System.out.print("Enter first name: ");
		first_name=input.next();
		System.out.print("Enter last name: ");
		last_name=input.next();
		System.out.println("Enter your birthday in the format \"yyyy-mm-dd\"");
		System.out.print("Birthday: ");
		birthday=input.next();
		while(true){
			System.out.print("Verify your birthday: ");
			verify=input.next();
			if(birthday.equals(verify)){
				break;
			}
			else{
				System.out.println("Birthday does not match");
			}
		}
		int random_choice =random.nextInt(employeeTypeArr.length);
		employeeType=employeeTypeArr[random_choice];
		random_choice=random.nextInt(departmentNameArr.length);
		departmentName=departmentNameArr[random_choice];
		
		//run database stuff
		//set path, username, password as constants
		final String Database_url = "jdbc:derby:employees";
		final String user = "michael";
		final String password = "michael";
		
		//insert info into database
		try(Connection conn = DriverManager.getConnection(Database_url,user,password)){
			
			//enter info into employees table
			PreparedStatement pstmt = conn.prepareStatement("INSERT INTO employees (ssn,first_name,last_name,birthday,employeeType,departmentName) VALUES (?,?,?,?,?,?)");
			pstmt.setString(1, ssn);
			pstmt.setString(2, first_name);
			pstmt.setString(3, last_name);
			pstmt.setDate(4, java.sql.Date.valueOf(birthday));
			pstmt.setString(5,employeeType);
			pstmt.setString(6, departmentName);
			pstmt.executeUpdate();
		}
		catch(Exception sqlException){
			sqlException.printStackTrace();
		}
			//enter into salariedEmployees table if applicable
		if(employeeType=="salariedEmployee"){
			try(Connection conn = DriverManager.getConnection(Database_url,user,password)){
				PreparedStatement pstmt = conn.prepareStatement("INSERT INTO salariedEmployees (ssn,weeklySalary,bonus) VALUES (?,?,?)");
				pstmt.setString(1, ssn);
				pstmt.setFloat(2, weeklySalary);
				pstmt.setFloat(3, bonus);
				pstmt.executeUpdate();
			}
			catch(SQLException sqlException){
				sqlException.printStackTrace();
			}		
		}
		//enter into commissionEmployees table if applicable
		else{
			try(Connection conn = DriverManager.getConnection(Database_url,user,password)){
				
				PreparedStatement pstmt = conn.prepareStatement("INSERT INTO commissionEmployees (ssn,gross_sales,commission_rate,bonus) VALUES (?,?,?,?)");
				pstmt.setString(1, ssn);
				pstmt.setInt(2, gross_sales);
				pstmt.setFloat(3, commission_rate);
				pstmt.setFloat(4, bonus);				
				pstmt.executeUpdate();
			}
			catch(SQLException sqlException){
				sqlException.printStackTrace();
			}
		}
	}
}

/*
Credits:
=======
https://stackoverflow.com/a/26700322/14470832
random choice object

https://www.codegrepper.com/code-examples/java/picking+a+random+string+from+string+array+java
assign random choice to variable

https://stackoverflow.com/questions/18438587/string-to-java-sql-date
date format for sql database

https://stackoverflow.com/questions/18614836/using-setdate-in-preparedstatement
preparedstatement date fill in from string
*/