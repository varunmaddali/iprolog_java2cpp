import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.io.*;
 
class Palindrome
{
   public static void main(String args[])
   {
      String original, reverse = "";
	int palindrome=0,notpalindrome=0;
	
  BufferedReader br = new BufferedReader(new FileReader("common_words.txt"));
    String line;
    while ((line = br.readLine()) != null) {

        original = line;
 
      int length = original.length();
 
      for ( int i = length - 1; i >= 0; i-- )
         reverse = reverse + original.charAt(i);
 
      if (original.equals(reverse))
	{
	palindrome++;
         System.out.println("The string -----"+original+"-----is a palindrome.");
	}
      else
	{
         //System.out.println("The string -----"+original+"-----is not a palindrome.");
	notpalindrome++;
	}
    }  
	System.out.println("The count of palindromes inn the list is :"+palindrome);
	System.out.println("The count of palindromes inn the list is :"+notpalindrome);   
 
   }
}
