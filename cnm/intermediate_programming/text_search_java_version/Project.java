/*
Programming Assignment Project
======================================
School of Business and Information Technology
Central New Mexico Community College
Course: CSCI-1152-R01, Spring 2021
Author: Michael Pacheco
email: mpacheco121@cnm.edu 
Date: 04/11/2021
*/

import java.util.*;
import java.io.*;
import java.io.IOException; 
import java.util.Scanner;
import java.util.Arrays;
import java.util.*;
import java.nio.file.*;
import java.lang.*;

public class Project{
	public static void main(String[] args)throws IOException{
		
		//get file
		Path txt = Paths.get(args[0]);
		
		//create and read in arraylist for sorting
		//count number of words
		ArrayList<String> sortList = new ArrayList<String>();
		Scanner file_in = new Scanner(txt);
		int numWords = 0;
		String word = "";
		while(file_in.hasNext()){
			word = file_in.next();
			word = word.replaceAll("\\p{Punct}|\\d","");
			sortList.add(word);
			numWords++;
		}
		file_in.close();
		//count unique words with second arraylist
		int unique_numWords =0;
		ArrayList<String> unique_sortList = new ArrayList<String>();
		int j=0;
		for(int i=0;i<numWords;i++){
			for(j=i+1;j<numWords;j++){
				if(sortList.get(i).equals(sortList.get(j))){
					break;
				}
			}
			if(j == numWords){
				unique_sortList.add(sortList.get(i));
				unique_numWords++;
			}
		}

		//print out numWords and unique_numWords
		System.out.println("The total number of word in the file is: "+numWords);
		System.out.println("The total number of different words in the file is: "+unique_numWords);
		System.out.println("Words of the input file in ascending order without duplication: ");
		System.out.println("// here is the output of all the words in ascending order without duplication");
		System.out.println("// (this content is subject to the input text file)");
		
		//sort unqiue_sortlist list
		sort(unique_sortList);

		//read in file as string to searchList		
		String file_content = "";
		file_content = new String(Files.readAllBytes(txt));
		//split string to search terms
		ArrayList<String> searchList = new ArrayList<String>(Arrays.asList(file_content.split("")));
		
		//begin search method
		search(searchList);
		
	}
	public static void sort(ArrayList<String> unique_sortList){
		String temp ="";
		boolean sorted = false;
		while (!sorted) {
			sorted = true;
			for (int i = 0; i < unique_sortList.size() - 1; i++) {
				if(unique_sortList.get(i).compareTo(unique_sortList.get(i+1))>0){
					temp = unique_sortList.get(i);
					unique_sortList.set(i, unique_sortList.get(i+1));
					unique_sortList.set(i+1, temp);
					sorted = false;
				}
			}
		}

		//print sorted list in ascending order
		for(String words:unique_sortList){
			System.out.println(words);
		}		
	}
	public static void search(ArrayList<String> searchList){
		//get search key
		Scanner user_input = new Scanner(System.in);
		while(true){
			//all these values need to be reset before looping through
			boolean match_found=false;
			int i=0;
			int j=0;
			int cursor=0;
			int line_start=0;
			int line_number = 1;
			System.out.println();
			System.out.print("Enter Word to be searched, \"EINPUT\" to exit: ");
			String key = user_input.next();
			if(key.equals("EINPUT")){
				System.out.println("Bye");
				System.exit(1);
			}
			else{
				//convert string to arraylist
				ArrayList<String> keyList = new ArrayList<String>(Arrays.asList(key.split("")));
				int keyList_size = keyList.size()-1;
				//loop through all content characters
				for(i=0;i<searchList.size();i++){
					//count \n as line number
					if(searchList.get(i).equals("\n")){
						line_number++;
					}
					//if match for first char begin loop to look for rest
					if(searchList.get(i).equals(keyList.get(0))){
						//System.out.println("looping through possible match");
						for(j=0;j<keyList.size();j++){
							//if there is a mismatch found before the loop is done, break
							if(!keyList.get(j).equals(searchList.get(i+j))){
								//System.out.println("match failed");
								break;
							}
							//
							//continues if there is a complete match
							else if(keyList.get(keyList.size()-1).equals(searchList.get(i+keyList_size))){
								//since there was a match we set boolean value to true for "no match found" statement
								match_found=true;
								//print line number
								System.out.println("Line Number "+line_number);
								//cursor starts at match location then moves back with two possibilities match on first line 
								//or match everywhere else 
								cursor=i;
								//first line match
								if(line_number==1){
									//we move back to index 0
									while(cursor>=0){
										if(cursor==0){
											break;
										}
										if(cursor<0){
											cursor=0;
											break;
										}
										cursor--;
									}
									//print first line until \n
									while(!searchList.get(cursor).equals("\n")){
										System.out.print(searchList.get(cursor));
										cursor++;
									}
									//print out pointer to first index of keyList
									System.out.println();
									for(int m=0;m<i;m++){
										System.out.print(" ");
									}
									System.out.print("^");
									System.out.println();
									break;
								}
								//match everywhere else
								else if(line_number>1){
									while(!searchList.get(cursor).equals("\n")){
										cursor--;
									}
									//move cursor one past the \n then print the first char of the line
									cursor++;
									//save current cursor position to new variable for use on line 144 to find position in arraylist
									line_start=cursor;
									//print out arraylist characters until we reach the next \n
									while(!searchList.get(cursor).equals("\n")){
										System.out.print(searchList.get(cursor));
										cursor++;
									}
									//print cursor pointing to match
									cursor=(i-line_start);
									System.out.println();
									for(int m=0;m<cursor;m++){
										System.out.print(" ");
									}
									System.out.print("^");
									System.out.println();
									break;
								}	
							}
						}
					}
				}
				//conditional no match found statement
				if(match_found==false){
					System.out.println("No match was found in the file");
				}
			}
		}	
	}
}

/*
Credits
=======
https://www.geeksforgeeks.org/different-ways-reading-text-file-java/
reading in text file as string to keep \n

https://stackoverflow.com/a/7488676/14470832
how to split string by spaces

https://stackoverflow.com/a/37419929/14470832
remove punctuation with regex or something

https://stackabuse.com/bubble-sort-in-java/
simple bubble sort, I adjusted the code to work for my arraylist
*/