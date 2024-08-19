/*
https://docs.oracle.com/javase/7/docs/api/javax/swing/BoxLayout.html

https://www.geeksforgeeks.org/java-awt-boxlayout-class/

https://stackoverflow.com/questions/761341/error-upon-assigning-layout-boxlayout-cant-be-shared

https://www.codota.com/code/java/methods/javax.swing.JTextField/setEditable
seteditable for text area

https://www.w3schools.com/sql/sql_where.asp
select from table where

https://www.w3schools.com/sql/sql_ref_order_by.asp
select all from in order of column

https://www.zentut.com/sql-tutorial/sql-update/
update table 

https://stackoverflow.com/questions/7375827/how-to-print-text-to-a-text-area
print to text table replacing previous text
*/
import java.awt.Font;
import java.awt.Color;

import javax.swing.BoxLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JOptionPane;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public class FrameBoxLayout extends JFrame 
{
	private final JButton button1;
	private final JButton button2;
	private final JButton button3;
	private final JButton button4;
	private final JButton button5;
	private final JButton button6;

	private final JTextField textField; //input
	private final JTextArea textArea; //output

	private final String DATABASE_URL = "jdbc:derby:employees";
	private final String SELECT_QUERY = "SELECT * FROM employees WHERE departmentName = 'SALES'"; //works
	private final String SELECT_TWO = "SELECT * FROM employees WHERE hours > 30"; //doesn't, hours is from a different table, will need to get all ssn from 
	private final String SELECT_THREE = "SELECT * FROM commissionEmployees ORDER BY commissionRate DESC"; //works
	private final String SET_ONE = "UPDATE basePlusCommissionEmployees SET baseSalary = baseSalary * 1.10"; //works
	private final String SET_TWO = "UPDATE  SET bonus = bonus + 100 WHERE MONTH(birthday) = MONTH(CURRENT_TIMESTAMP)"; //doesn't, table set is unknown
	private final String SET_THREE = "UPDATE commissionEmployees SET bonus = bonus + 100 WHERE grossSales > 10000"; //works
	private final String SET_THREE_O= "UPDATE basePlusCommissionEmployees SET bonus = bonus + 100 WHERE grossSales > 10000";
	private Connection connection = null;
	private Statement statement = null;

	public FrameBoxLayout()
	{
		super("Testing Layouts");

		//Initialize my database variables
		try {
			connection = DriverManager.getConnection(DATABASE_URL, "deitel", "deitel");
			statement = connection.createStatement();
		}
		catch (SQLException sqlException) {
			sqlException.printStackTrace();
		}
		
		//With BoxLayout, the buttons and text can be aligned along an axis
		BoxLayout boxlayout = new BoxLayout(getContentPane(),
										BoxLayout.PAGE_AXIS);
		getContentPane().setLayout(boxlayout);

		
		button1 = new JButton("Button 1");
		add(button1); // add button to JFrame

		button2 = new JButton("Button 2");
		add(button2); // add button to JFrame

		button3 = new JButton("Button 3");
		add(button3); // add button to JFrame

		button4 = new JButton("Button 4");
		add(button4); // add button to JFrame
		
		button5 = new JButton("Button 5");
		add(button5);
		
		button6 = new JButton("Button 6");
		add(button6);
		// create new ButtonHandler for button event handling 
		ButtonHandler handler = new ButtonHandler();
		button1.addActionListener(handler);
		button2.addActionListener(handler);
		button3.addActionListener(handler);
		button4.addActionListener(handler);
		button5.addActionListener(handler);
		button6.addActionListener(handler);


		textField = new JTextField("Enter Sql Statement Here");
		add(textField); // add textField1 to JFrame

		textArea = new JTextArea("Output");
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		//textArea.setFont(new Font("Serif", Font.PLAIN, 20));
		//textArea.setBackground(Color.black);
		//textArea.setForeground(Color.yellow);
		add(textArea); // add textField1 to JFrame

		TextHandler text_handler = new TextHandler();
		textField.addActionListener(text_handler);
	}

	// inner class for button event handling
	private class ButtonHandler implements ActionListener 
	{
		// handle button event
		@Override
		public void actionPerformed(ActionEvent event)
		{
			String which_button = event.getActionCommand();
			if(which_button.equals("Button 1"))
			{
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "Select all employees in Sales");
				runSelect();
				
			}
			else if(which_button.equals("Button 2")){
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "Select all employees over 30 hours");
				button_2();
			}
			else if(which_button.equals("Button 3")){
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "Select all commission employees in descending order of the comission rate");
				button_3();
			}
			else if(which_button.equals("Button 4")){
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "Increase base salary by 10% for all base-plus-commission employees");
				button_4();
			}
			else if(which_button.equals("Button 5")){
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "100$ bonus to employees whose birthday is this month");
				button_5();
			}
			else if(which_button.equals("Button 6")){
				JOptionPane.showMessageDialog(FrameBoxLayout.this, "100$ bonus for all commission employees with gross sales over 10,000");
				button_6();
			}
		}
		
		public void runSelect()
		{
			try (ResultSet resultSet = statement.executeQuery(SELECT_QUERY))
			{
				// get ResultSet's meta data
				ResultSetMetaData metaData = resultSet.getMetaData();
				int numberOfColumns = metaData.getColumnCount();

				String to_display = "";

				// display the names of the columns in the ResultSet
				for (int i = 1; i <= numberOfColumns; i++) {
					//System.out.printf("%-8s\t", metaData.getColumnName(i));
					to_display += metaData.getColumnName(i)+"\t";
				}
				//System.out.println();
				to_display += "\n";
				
				// display query results
				while (resultSet.next()) {
					for (int i = 1; i <= numberOfColumns; i++) {
						//System.out.printf("%-8s\t", resultSet.getObject(i));
						to_display += resultSet.getObject(i)+"\t";
					}
					//System.out.println();
					to_display += "\n";
				}
				
				textArea.setText(to_display);
			}
			catch (SQLException sqlException) {
				sqlException.printStackTrace();
			}
		}
		//select all employees over 30 hours
		public void button_2(){
			try(ResultSet resultSet = statement.executeQuery(SELECT_TWO)){
				// get ResultSet's meta data
				ResultSetMetaData metaData = resultSet.getMetaData();
				int numberOfColumns = metaData.getColumnCount();

				String to_display = "";

				// display the names of the columns in the ResultSet
				for (int i = 1; i <= numberOfColumns; i++) {
					//System.out.printf("%-8s\t", metaData.getColumnName(i));
					to_display += metaData.getColumnName(i)+"\t";
				}
				//System.out.println();
				to_display += "\n";
				
				// display query results
				while (resultSet.next()) {
					for (int i = 1; i <= numberOfColumns; i++) {
						//System.out.printf("%-8s\t", resultSet.getObject(i));
						to_display += resultSet.getObject(i)+"\t";
					}
					//System.out.println();
					to_display += "\n";
				}
				
				textArea.setText(to_display);				
			}
			catch (SQLException sqlException) {
				sqlException.printStackTrace();
			}
		}
		//Select all commission employees in descending order of the comission rate
		public void button_3(){
			try(ResultSet resultSet = statement.executeQuery(SELECT_THREE)){
				// get ResultSet's meta data
				ResultSetMetaData metaData = resultSet.getMetaData();
				int numberOfColumns = metaData.getColumnCount();

				String to_display = "";

				// display the names of the columns in the ResultSet
				for (int i = 1; i <= numberOfColumns; i++) {
					//System.out.printf("%-8s\t", metaData.getColumnName(i));
					to_display += metaData.getColumnName(i)+"\t";
				}
				//System.out.println();
				to_display += "\n";
				
				// display query results
				while (resultSet.next()) {
					for (int i = 1; i <= numberOfColumns; i++) {
						//System.out.printf("%-8s\t", resultSet.getObject(i));
						to_display += resultSet.getObject(i)+"\t";
					}
					//System.out.println();
					to_display += "\n";
				}
				
				textArea.setText(to_display);				
			}
			catch (SQLException sqlException) {
				sqlException.printStackTrace();
			}		
		}
		//Increase base salary by 10% for all base-plus-commission employees
		public void button_4(){
			try{				
				statement.executeUpdate(SET_ONE);
				textArea.setText("Done");
			}
			catch (SQLException sqlException) {
				sqlException.printStackTrace();
			}		
		}
		//100$ bonus to employees whose birthday is this month
		public void button_5(){
			try{				
				statement.executeUpdate(SET_TWO);
				textArea.setText("Done");				
			}
			catch (SQLException sqlException) {
				sqlException.printStackTrace();
			}			
		}
		//100$ bonus for all commission employees with gross sales over 10,000
		public void button_6(){
			try{
				statement.executeUpdate(SET_THREE);
				statement.executeUpdate(SET_THREE_O);
				textArea.setText("Done");
			}
			catch (SQLException sqlException) {
				textArea.setText("Failed");
				sqlException.printStackTrace();
			}			
		}
	}
	
	
	// inner class for text event handling
	private class TextHandler implements ActionListener 
	{
		@Override
		public void actionPerformed(ActionEvent event)
		{
			String text_from_textfield = event.getActionCommand();
			
			if(text_from_textfield.startsWith("SELECT")){
				try{
					statement.executeQuery(text_from_textfield);
				}
				catch (SQLException sqlException) {
					sqlException.printStackTrace();
				}			
			}
			else if(text_from_textfield.startsWith("UPDATE")){
				try{
					statement.executeUpdate(text_from_textfield);
				}
				catch (SQLException sqlException) {
					sqlException.printStackTrace();
				}					
			}
		}
	}
}

