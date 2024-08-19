/*
Programming Assignment Lab 06 part 2
======================================
School of Business and Information Technology
Central New Mexico Community College
Course: CSCI-2251-R01, Spring 2021
Author: Michael Pacheco
email: mpacheco121@cnm.edu 
Date: 04/22/2021
*/
import javax.swing.JFrame;

public class Test
{
	public static void main(String[] args)
	{
		//FrameNullLayout testFrame = new FrameNullLayout();
		//FrameFlowLayout testFrame = new FrameFlowLayout();
		FrameBoxLayout testFrame = new FrameBoxLayout();

		testFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		testFrame.setSize(500, 700);
		testFrame.setVisible(true);
	}
}