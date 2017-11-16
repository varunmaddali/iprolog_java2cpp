package setest1;

import java.io.*;


public class test1 {
        public static void main(String args[]) throws IOException
        {
            
            String fileName = "Downloads\\palindrome.txt";//name of the string

            
            String line = null;

            try {
                
                FileReader fileReader =
                        new FileReader(fileName);

               
                BufferedReader bufferedReader =
                        new BufferedReader(fileReader);

                while((line = bufferedReader.readLine()) != null) {
                    String original, reverse = "";

                    original = line;
                    System.out.print(line);
                    System.out.print("----**---");
                    int length = original.length();

                    for ( int i = length - 1; i >= 0; i-- )
                        reverse = reverse + original.charAt(i);//checking here

                    if (original.equals(reverse))
                        System.out.println(" YES it is palindrome");
                    else
                        System.out.println("NO it not palindrome");

                }
                bufferedReader.close();
                }
            catch(FileNotFoundException ex) {
                System.out.println(
                        "Unable to open file '" +
                                fileName + "'");
            }

                }

                // Always close files.

            }




