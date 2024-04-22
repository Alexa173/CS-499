/* Alexa Szlykowicz
 * March 28
 * CS 499 
 * Text Baseed Game
 * Version 2
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class planets {
    String direction;
    String name;
}


public class TextBasedGame {
    public static void printInstructions(){
        System.out.println("Instructions:");
        System.out.println("Collect all six artifacts before entering Dark Morrows to defeat Naruko.  \n" + //
                    "If you do not have all the artifacts, you will be defeated.");
        System.out.println("Move commands: go South, go North, go East, go West");
        System.out.println("Add to Inventory: get Artifact [number]");
        System.out.println();
    }
    public static void main(String[] args) throws Exception {
        String currentPlanet;
        
        // Print "Planetary Text Base Game"
        System.out.println("Planetary Text Base Game");
        System.out.println("");

        /* Must visit all the planets and collect the artifacts
        * before heading to the Boss in Dark Morrows
        * User Controls: go South, go North, go East, go West
        *               get Artifact 1, get Artifact 2, Artifact 3, Artifact 4, Artifact 5, Artifact 6
        */  
        
        Scanner scan = new Scanner(System.in);
        
        /* Instantiate data structure. Populate 
        * with the planets along with the 
        * directions of the closest planets 
        */
        
        HashMap<String, String> HeliQ = new HashMap<>(); 
        HashMap<String, String> Sandara = new HashMap<>(); 
        HashMap<String, String> Petrius = new HashMap<>(); 
        HashMap<String, String> Iris = new HashMap<>(); 
        HashMap<String, String> Helios = new HashMap<>(); 
        HashMap<String, String> Fateim = new HashMap<>(); 
        HashMap<String, String> Lotacus = new HashMap<>();
        HashMap<String, String> item = new HashMap<>();
        HashMap<String, HashMap<String, String>> map = new HashMap<>();

        // Populating HeliQ Space Station map
        HeliQ.put("North", "Sandara");
        HeliQ.put("South", "Helios");
        HeliQ.put("East", "Iris");
        HeliQ.put("West", "Lotacus");

        // Populating Sandara map
        Sandara.put("West", "Petrius");
        Sandara.put("South", "HeliQ Space Station");

        // Populating Petrius map
        Petrius.put("East", "Sandara");

        // Populating Iris map
        Iris.put("West", "HeliQ Space Station");

        // Populating Helios map
        Helios.put("North", "HeliQ Space Station");
        Helios.put("West", "Fateim");

        // Populating Fateim map
        Fateim.put("East", "Helios");

        // Populating Lotacus map
        Lotacus.put("North", "Dark Morrows");
        Lotacus.put("East", "HeliQ Space Station");

        // Master Map - Linking planets together
        map.put("HeliQ Space Station", HeliQ);
        map.put("Sandara", Sandara);
        map.put("Petrius", Petrius);
        map.put("Lotacus", Lotacus);
        map.put("Iris", Iris);
        map.put("Helios", Helios);
        map.put("Fateim", Fateim);
         
        /* Create another hashmap to hold 
        * the "treasures" and their corresponding 
        * planets 
        */
        item.put("Sandara", "Artifact 1");
        item.put("Helios", "Artifact 2");
        item.put("Fateim", "Artifact 3");
        item.put("Iris", "Artifact 4");
        item.put("Petrius", "Artifact 5");
        item.put("Lotacus", "Artifact 6");
        

        // Start the player on the airship
        currentPlanet = "HeliQ Space Station";
        
        // Instantiate Inventory data structure
        ArrayList<String> inventory = new ArrayList<String>();
        
        
        
        //print instructions 
        printInstructions();

        // Create a loop that plays the game
        while (true) {
            // print planet
            System.out.println("You are on " + currentPlanet );
            // print item that is on planet  
            if (currentPlanet.equals("HeliQ Space Station")){
                System.out.println("No items to collect");
            } else {
                System.out.println("You see " + item.get(currentPlanet));
            }       
            
            // print inventory 
            System.out.println("Inventory " + inventory);
           
            System.out.println("------------------");
            System.out.println("Enter Your Move");

            // take in player input
            String userInput = scan.nextLine();
            String[] command = userInput.split(" ",2);
            if (command.length < 2 || command.length > 3) {
                System.out.println();
                System.out.println("*Invalid Command*");
                continue;
            }
            String action = command[0];
            String direction = command[1];
            String artifact;
        
            System.out.println("");
            
            // if player enters "go" as first input
            if (action.equals("go")){
                // if direction is not in hashmap
                if (!map.get(currentPlanet).containsKey(direction)) {
                    System.out.println("*Invalid Direction*");
                } else {                    
                    // update current planet  
                    currentPlanet = map.get(currentPlanet).get(direction);
                    // if planet is "Boss" planet 
                    if (currentPlanet.equals("Dark Morrows")) {
                        // if inventory count is 6
                        if (inventory.size() != 6){
                            System.out.println("You are defeated!");    
                            break;                                             
                        } else {
                            System.out.println("You defeated Naruko!"); 
                            break;
                        }                            
                    }                                      
                }                              
            } 
                   
            // Implement logic to acquire items
            // if player enters 'get'
            if(action.equals("get")) {               
                artifact = item.get(currentPlanet);                
                // if player does not enter correct artifact
                if (!direction.equals(artifact)){
                    // print error
                    System.out.println("*Invalid Item*");
                } else if (inventory.contains(artifact)){
                    // if item is in inventory 
                    // print "Item is already in inventory"
                    System.out.println("*Item is already in inventory*");                
                } else {
                    // else add item to inventory 
                    inventory.add(artifact);
                }                                                                       
            }             
        }
    }
}


