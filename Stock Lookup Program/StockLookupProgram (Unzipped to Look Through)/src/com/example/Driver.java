package com.example;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonSyntaxException;

import java.util.Arrays;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;

import org.apache.commons.text.WordUtils;
import java.time.*;
import java.time.format.DateTimeParseException;
import java.util.Collections;
import java.util.InputMismatchException;



public class Driver {
	public static void main(String []args) throws FileNotFoundException{
		Gson gson = new Gson();
		Scanner s = null;
		Scanner bean = null;
		String filler = "";
		boolean going = true;
		StockData sd = null;
		File file = null;
		boolean chon = true;
		String filename = "";
		boolean checker = true;
		while(chon) {
			checker = true;
			filler = "";
			try {
				bean = new Scanner(System.in);
				System.out.print("What is the name of the company file? ");
				filename = bean.nextLine();
				file = new File(filename);
								
				s = new Scanner(file);

				while(s.hasNext()) {
					filler += s.nextLine();
				}
				
				sd = gson.fromJson(filler, StockData.class);

				s.close();
				//bean.close();
			}catch(FileNotFoundException e) {
				System.out.println("\nThe file " + filename + " not found.\n");
				continue;
				//checker = false;
			}catch(JsonSyntaxException ex) {
				//if(checker = true) {
					System.out.println("\nThe file " + filename + " is not formatted properly.\n");
					continue;
				//}
				//checker = false;
			}

			if(sd == null) {
				System.out.print("");
				System.out.println("\nThis file does not contain any companies!\n");
				continue;
			}
			
			for(int i = 0; i < sd.getData().size(); i++) {
				if(sd.getData().get(i).getName() == null || sd.getData().get(i).getTicker() == null || sd.getData().get(i).getExchangeCode() == null) {
					System.out.println("\nThis file has imporant entries (Name, Ticker, Exchange Code) that are null or missing, please choose another or fix and reselect.\n");
					checker = false;
				}
			}
			if(checker) {
				chon = false;
			}
			
			
			
		}
		
		System.out.println("\nThe file has been properly read.");

		s = new Scanner(System.in);
		//s.nextLine();

		while (going) {
			int n = 0;
			
			try {
				System.out.print("\n\t\t1) Display all public companies\n\t\t2) Search for a stock (by ticker)\n\t\t3) Search for all stocks on an exchange\n\t\t"
						+ "4) Add a new company/stocks\n\t\t5) Remove a company\n\t\t6) Sort Companies\n\t\t7) Exit\nWhat would you like to do? ");
				n = s.nextInt();
				s.nextLine();
			}catch(Exception e) {
					s.nextLine();
			}
			
			
			switch(n) {
			case 1: 
				for(int i = 0; i < sd.getData().size(); i++){
					if(i == 0) {
						System.out.println();
					}
					System.out.print(sd.getData().get(i).getName() + ", symbol " + sd.getData().get(i).getTicker() + ", started on " + 
							sd.getData().get(i).getStartDate() + ", listed on " + sd.getData().get(i).getExchangeCode() + ",\n\t");
					System.out.println(WordUtils.wrap(sd.getData().get(i).getDescription(), 60, "\n\t", false));
				}
				break;
			case 2:
				boolean run = true;
				while(run) {
					System.out.print("\nWhat is the ticker of the company you would like to search for? ");
					String t = s.nextLine();
					System.out.print("");
					boolean found = false;
					for(int i = 0; i < sd.getData().size(); i++) {
						if(sd.getData().get(i).getTicker().equalsIgnoreCase(t)){
							System.out.print("\n" + sd.getData().get(i).getName() + ", symbol " + sd.getData().get(i).getTicker() + ", started on " + 
									sd.getData().get(i).getStartDate() + ", listed on " + sd.getData().get(i).getExchangeCode() + "\n");
							found = true;
							run = false;
						}
					}
					if(!found) {
						System.out.println("\n"+ t + " could not be found.");
					}
				}
				break;
			case 3:
				boolean run3 = true;
				while(run3) {
					boolean found = false;
					int amount = 0;
					boolean word = false;
					boolean comma = false;
					System.out.print("\nWhat Stock Exchange would you like to search for? ");
					String se = s.nextLine();
					System.out.println("");
					for(int i = 0; i < sd.getData().size(); i++) {
						if(sd.getData().get(i).getExchangeCode().equalsIgnoreCase(se)){
							found = true;
							amount++;
							if(amount > 1) {
								word = true;
							}
							if(amount > 3) {
								comma = true;
							}
						}
					}
					if(found){
						for(int i = 0; i < sd.getData().size(); i++) {
							if(sd.getData().get(i).getExchangeCode().equalsIgnoreCase(se)){
								if(amount >= 1) {
									if(word && amount == 1) {
										System.out.print("and " + sd.getData().get(i).getTicker().toUpperCase() + " found on the " + se.toUpperCase() + " exchange.\n");
										run3 = false;
										amount--;
									}
									else if(amount == 1) {
										System.out.print(sd.getData().get(i).getTicker().toUpperCase() + " found on the " + se.toUpperCase() + " exchange.\n");
										run3 = false;
										amount--;
									}
									else if(amount >= 3){
										System.out.print(sd.getData().get(i).getTicker().toUpperCase() + ", ");
										amount--;
									}
									else{
										System.out.print(sd.getData().get(i).getTicker().toUpperCase() + " ");
										amount--;
									}
								}
							}
						}
					}
					else {
						System.out.println("No exchange named " + se.toUpperCase() + " found.");
					}
					
				}
				break;
			case 4:
				boolean run4 = true;
				while(run4) {
					boolean success = false;
					System.out.print("\nWhat is the name of the company you would like to add? ");
					String se = s.nextLine();
					System.out.println("");
					for(int i = 0; i < sd.getData().size(); i++) {
						if(sd.getData().get(i).getName().equalsIgnoreCase(se)) {
							System.out.println("There is already an entry for " + sd.getData().get(i).getName() + ".");
							success = true;
						}
					}
					Datum temp = new Datum();
					while(!success) {
						temp.setName(se);
						boolean tickerOK = true;
						boolean found = false;
						while(tickerOK) {
							System.out.print("What is the stock symbol of " + temp.getName() + "? ");
							se = s.nextLine();
							System.out.println("");
							for(int i = 0; i < sd.getData().size(); i++) {
								if(sd.getData().get(i).getTicker().equalsIgnoreCase(se)) {
									System.out.println("There is already an entry for symbol " + sd.getData().get(i).getTicker() + ".\n");
									found = true;
								}
							}
							if(!found) {
								tickerOK = false;
							}
							found = false;
						}
						temp.setTicker(se.toUpperCase());
						boolean dateOK = true;
						while(dateOK) {
							System.out.print("What is the start date of " + temp.getName() + "? ");
							se = s.nextLine();
							System.out.println("");
							try {
								LocalDate date = null;
								date = LocalDate.parse(se);
								temp.setStartDate(se);
								dateOK = false;
							}catch(DateTimeParseException e) {
								System.out.println("This date is invalid. Please use format YYYY-MM-DD.\n");
							}
						}
						boolean exchange = true;
						while(exchange) {
							System.out.print("What is the exchange where " + temp.getName() + " is listed? ");
							se = s.nextLine();
							System.out.println("");
							for(int i = 0; i < sd.getData().size(); i++) {
								if(sd.getData().get(i).getExchangeCode().equalsIgnoreCase(se)) {
									temp.setExchangeCode(sd.getData().get(i).getExchangeCode());
									exchange = false;
								}
							}
							if(exchange) {
								System.out.println("This exchange does not exist. Please enter a valid exchange.\n");
							}
							
						}
						boolean descrip = true;
						while(descrip) {
							System.out.print("What is the description of " + temp.getName() + "? ");
							se = s.nextLine();
							System.out.println("");
							temp.setDescription(se);
							descrip = false;
						}
						success = true;
						sd.getData().add(temp);
						run4 = false;
					}
				}
				System.out.println("There is a new entry for:");
				System.out.print("\n" + sd.getData().get(sd.getData().size() - 1).getName() + ", symbol " + sd.getData().get(sd.getData().size() - 1).getTicker() + ", started on " + 
						sd.getData().get(sd.getData().size() - 1).getStartDate() + ", listed on " + sd.getData().get(sd.getData().size() - 1).getExchangeCode() + "\n\t");
				System.out.println(WordUtils.wrap(sd.getData().get(sd.getData().size() - 1).getDescription(), 60, "\n\t", false));
				break;
			case 5: 
				boolean run5 = true;
				while(run5) {
					for(int i = 0; i < sd.getData().size(); i++) {
						if(i == 0) {
							System.out.println();
						}
						System.out.println("\t" + (i+1) + ") " + sd.getData().get(i).getName());
					}
					int num = 0;
					try {
						System.out.print("Which company would you like to remove? ");
						num = s.nextInt();
						s.nextLine();
					}catch(Exception e) {
						System.out.println("\nThat is not a valid input. Please enter a valid input (1 - " + sd.getData().size() + ").");
						s.nextLine();
						continue;
					}
					for(int i = 0; i < sd.getData().size(); i++) {
						if(i+1 == num) {
							run5 = false;
							System.out.println("\n" + sd.getData().get(i).getName() + " is now removed.");
							sd.getData().remove(i);
						}
					}
					if(run5) {
						System.out.println("\nThat is not a valid input. Please enter a valid input (1 - " + sd.getData().size() + ").");
					}
				}
				break;
			case 6:
				boolean run6 = true;
				while(run6) {
					String [] names = new String[sd.getData().size()];
					for(int i = 0; i < sd.getData().size(); i++) {
						names[i] = sd.getData().get(i).getName().toLowerCase();
					}
					Arrays.sort(names);
					Datum tempDat = new Datum();
					for(int i = 0; i < sd.getData().size(); i++) {
						for(int j = 0; j < sd.getData().size(); j++) {
							if(names[i].equalsIgnoreCase(sd.getData().get(j).getName())) {
								tempDat = sd.getData().get(i);
								sd.getData().set(i, sd.getData().get(j));
								sd.getData().set(j, tempDat);
							}
						}	
					}
					
					boolean cont = true;
					while(cont) {
						int decision;
						try {
							System.out.print("\t1) A to Z\n\t2) Z to A\nHow would you like to sort by? ");
							decision = s.nextInt();
							s.nextLine();
						}catch(InputMismatchException e) {
							System.out.println("\nThat input is invalid. Please enter a valid input (1 or 2).\n");
							s.nextLine();
							continue;
						}
						if(decision == 1) {
							cont = false;
							System.out.println("\nYour companies are now sorted in alphabetical order (A-Z).");
							run6 = false;
						}
						else if(decision == 2) {
							cont = false;
							Collections.reverse(sd.getData());
							System.out.println("\nYour companies are now sorted in reverse alphabetical order (Z-A).");
							run6 = false;
						}
						else {
							System.out.println("\nThat input is invalid. Please enter a valid input (1 or 2).\n");
						}
					}
				
				}
				
				break;
			case 7:
				going = false;
				boolean run7 = true;
				int choice;
				while(run7) {
					try {
						System.out.print("\n\t1) Yes\n\t2) No\nWould you like to save your edits? ");
						choice = s.nextInt();
						s.nextLine();
					}catch(InputMismatchException e) {
						System.out.println("\nThat input is invalid. Please enter a valid input (1 or 2).\n");
						s.nextLine();
						continue;
					}
					if(choice == 1) {
						run7 = false;
						try {
							FileWriter writer = new FileWriter(file);
						    Gson gson1 = new GsonBuilder().setPrettyPrinting().disableHtmlEscaping().create();
						    gson1.toJson(sd, writer);
						    writer.flush();
						    writer.close();
							System.out.println("\nYour edits have been saved to " + file.toString() + "\nThank you for using my program!");
						}catch(Exception e) {
							System.out.println("Failed to save edits! (Is the file still available?)\nThanks for using my program!");
						}
						
					}
					else if(choice == 2) {
						run7 = false;
						System.out.println("\nYour edits were not saved.\nThank you for using my program!");
					}
					else {
						System.out.println("That input is invalid. Please enter a valid input (1 or 2).\n");
					}
				}
				break;
			default:
				System.out.println("\nThat is not a valid option.");
				break;
			}
		}
		
		s.close();
		bean.close();
	}
}
