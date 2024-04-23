#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include<fstream>
using namespace std;

// variables for prime numbers used in RSA encryption
int p = 11, q = 13;

// variables for RSA encryption parameters and file paths
int n, e, d;
// variables for files paths
const string allUsersFilePath = "allUsers.txt";
const string allMessagesFilePath = "allMessages.txt";

// string variable to store the currently logged-in user
string loginUser = "";
// struct to represent user information
struct UserInfo{
	string name;
	string secureNumber;
	string password;
};

// vector  (linked list) to store information about all users
vector <UserInfo> allUsers;

// struct to represent message information
struct MessageInfo{
	string sender;
	string reciever;
	string message;
};

// vector (linked list) to store information about all messages
vector <MessageInfo> allMessages;

/**
 * Computes the greatest common divisor (GCD) of two numbers using Euclid's algorithm.
 * 
 * @param a The first number.
 * @param b The second number.
 * @return The GCD of the two numbers.
 */
int gcd(int a, int b) {
	// If b is zero, a is the GCD
	if (b == 0)
		return a;
	// Otherwise, recursively call gcd with b and a % b
	return gcd(b, a % b);
}

/**
 * Generates private and public keys for encryption and decryption.
 * 
 * This function calculates the private (d) and public (e) keys based on given prime numbers (p and q).
 * It also calculates the modulus (n) used in encryption and decryption.
 */
void createPrivateAndPublicKeys() {
	// Calculate n by multiplying the prime numbers p and q
	n = p * q;
	// Calculate Euler's totient function (phi(n)) for n
	int h = (p - 1) * (q - 1);
	// Initialize e to 2
	e = 2;
	// try to find a suitable public exponent e such that 1 < e < h and gcd(e, h) = 1
	while (e < h && (gcd(e, h) != 1)) {
		// Increment e until a suitable value is found
		e++;
	}
	// Initialize d to 2
	d = 2;
	// try to find the corresponding private exponent d such that (d * e) % h = 1
	while(d < h && (((d * e) % h) != 1)) {
		// Increment d until a suitable value is found
		d++;
	}
}

/**
 * Computes modular exponentiation (b^e mod m).
 * 
 * @param b The base.
 * @param e The exponent.
 * @param m The modulus.
 * @return The result of b^e mod m.
 */
long long int computeModulus(long long int b, long long int e, long long int m) {
	// Initialize the result to 1
	long long int r = 1;
	// Take b modulo m to handle large values of b
	b = b % m;
	// Repeat until exponent e is greater than 0
	for (;e > 0;) {
		// If the current bit of e is 1
		// Update result: r = (r * b) mod m
		if (e % 2 == 1)
			r = (r * b) % m;
		// Right shift e to divide it by 2
		e = e >> 1;
		// Square b: b = (b * b) mod m
		b = (b * b) % m;
	}
	// Return the final result
	return r;
}


long long int computeModulus(long long int base, long long int exponent, long long int modulus);

/**
 * Encrypts a text using RSA encryption.
 * 
 * @param text The text to be encrypted.
 * @param encryptedText Reference to a string where the encrypted test will be stored.
 *                      his string will be modified by the function ( call by reference).
 * @return void
 */
void encrypt(const string& text, string &encryptedText){
	// Initialize encrypted text string
    encryptedText = "";
	// Iterate through each character of the text
    for (size_t i = 0; i < text.length(); i++) {
		 // Convert the character to its ASCII value (typecast to long long int)
        long long int ch = computeModulus(static_cast<long long int>(text[i]), e, n);
		// Append the encrypted character (represented as a string) to the encrypted text
        encryptedText += to_string(ch) + " ";
    }
}

/**
 * Decrypts an encrypted text using RSA decryption.
 * 
 * @param encryptedText The encrypted text.
 * @param text A reference to store the decrypted text.
 */
void decrypt(const string& encryptedText, string &text) {
	// Initialize decrypted text string
	text = "";
	 // Initialize index for iterating through encrypted text
	int i = 0;
	// Iterate through each character of the encrypted text
	while(i < encryptedText.length()) {
		// Temporary string to store each encrypted character
		string temp = "";
		// Extract characters until a space is encountered or end of string
		while (encryptedText[i] != ' ' && i < encryptedText.length()) {
			// Append character to temporary string
			temp += encryptedText[i];
			// Move to next character
			i++;
		}
		// Convert the temporary string to a long long integer
		long long int c = stoll(temp);
		// Decrypt the encrypted character using RSA decryption
		long long int ch = computeModulus(c, d, n);
		// Append the decrypted character to the decrypted text
		text += char(ch);
		// Move to next character in encrypted text
		i++;
	}
}


/**
 * Checks if a user exists in the list of all users or not.
 * 
 * @param name The name of the user to check.
 * @param password The password of the user to check.
 * @param secureNumber The secure number associated with the user to check.
 * @return True if the user exists with the provided credentials, otherwise false.
 */
bool isUserExist(string name, string password, string secureNumber) {
	// Iterate through each user in the list
    for (int i = 0; i < allUsers.size(); ++i) {  
        // Check if the user's name, password, and secure number match the given info
        if (allUsers[i].name == name && allUsers[i].password == password && allUsers[i].secureNumber == secureNumber) {
            // Return true if user exists
			return true;  
        }
    }
	// Return false if user does not exist
    return false;  
}


/**
 * Loads user data from file into the list of all users.
 * 
 * @return void
 */
void loadAllUsersFile() {
	// Open the file for reading
    ifstream file(allUsersFilePath);  
	// Check if the file opened successfully
    if (!(file.is_open())) {          
		// Return if file cannot be opened
        return;                       
    }
	// Display message indicating loading process
    cout << "Loading All Users from DataBase ...\n"; 
	// Variable to store each line read from the file
    string line; 
	// Variable to store user information
    UserInfo userInfo;         
	// Read each line from the file
    while (getline(file, line)) {  
		// Create a stringstream to parse the line
        stringstream ss(line);     
        // Extract user information from the comma-separated line
        getline(ss, userInfo.name, ',');
        getline(ss, userInfo.password, ',');
        getline(ss, userInfo.secureNumber, ',');
		// Add the user information to the list of all users
        allUsers.push_back(userInfo);  
    }
	// Close the file
    file.close();  
}


/**
 * Loads message data from file into the list of all messages.
 * @return void
 */
void loadAllMessagesFile() {
	// Open the file for reading
    ifstream file(allMessagesFilePath);  
	// Check if the file opened successfully
    if (!(file.is_open())) {             
		// Return if file cannot be opened
        return;                          
    }
	// Display message indicating loading process
    cout << "Loading Messages from DataBase ...\n";  
	// Variable to store each line read from the file
    string line;                 
	// Variable to store message information
    MessageInfo messageInfo;   
	// Read each line from the file
    while (getline(file, line)) {  
		// Create a stringstream to parse the line
        stringstream ss(line);     
        // Extract message information from the comma-separated line
        getline(ss, messageInfo.sender, ',');
		getline(ss, messageInfo.reciever, ',');
        getline(ss, messageInfo.message, ',');
		// Add the message information to the list of all messages
        allMessages.push_back(messageInfo);  
    }
	// Close the file
    file.close();  
}

/**
 * Sends a new message from the currently logged-in user to another user.
 * 
 * ask the user to enter the receiver's name and the message content, encrypts the message,
 * and stores it in the list of all messages. If a conversation already exists between the logged-in
 * user and the receiver, the new message is appended to the existing conversation; otherwise, a new
 * conversation entry is created.
 * 
 * @return void
 */
void sendNewMessage() {
	// Variables to store receiver's name and message content
    string receiver, message;  
	 // ask user to enter receiver's name
    cout << "Enter Friend name: ";
    getline(cin, receiver);    
	// ask user to enter message content
    cout << "Enter Your message: ";
    getline(cin, message);      
    // Variable to store message information
    MessageInfo messageInfo;   
	// append sender's name to the message
    message = "\n" + loginUser + ": " + message;  
    // Variable to store encrypted message
    string encryptedMessage;    
	// Encrypt the message
    encrypt(message, encryptedMessage);  
    
    // Check if there is an existing conversation between the sender and receiver
    for (int index = 0; index < allMessages.size(); index++) {
        if (allMessages[index].sender == loginUser && allMessages[index].reciever == receiver) {
            // Append the encrypted message to the existing conversation
            allMessages[index].message += encryptedMessage;
            cout << "Message sent successfully to " << receiver << "\n";
			// Exit the function
            return;  
        }
    }
    
    // If there is no existing conversation, create a new conversation entry
    messageInfo.sender = loginUser;
	messageInfo.reciever = receiver;
    messageInfo.message = encryptedMessage;
    // Add the new conversation to the list of all messages
    allMessages.push_back(messageInfo);  
    cout << "Message sent successfully to " << receiver << "\n";
}

/**
 * Displays messages received by the currently logged-in user.
 * 
 * Retrieves messages from the list of all messages where the logged-in user is the receiver.
 * Decrypts the messages and displays them to the user. If there are no messages, 
 * a corresponding message is displayed.
 * 
 * @return void
 */
void showMyMessages() {
	// Variable to store encrypted messages received by the user
    string message = "";  
    // Iterate through all messages to find messages intended for the logged-in user
    for (int index = 0; index < allMessages.size(); index++) {
		// Check if the currentlly logged-in user is the receiver of the message
		if (allMessages[index].reciever == loginUser) {  
			// Store the encrypted message
            message = allMessages[index].message;    
			// Exit the loop after finding the first message
            break;  
        }
    }
	// If no messages are found
    if (message == "") {  
		// Display corresponding message
        cout << "You did not have any messages yet !!!\n";  
		// Exit the function
        return;  
    }
	// Display header for the user's messages
    cout << "Your messages are\n";
	// Variable to store decrypted messages
    string decryptedMessages;  
	// Decrypt the encrypted messages
    decrypt(message, decryptedMessages);
	// Display the decrypted messages
    cout << decryptedMessages << endl;  
}

/**
 * Displays the second chat menu and handles user input.
 * 
 * The menu options include sending a message, viewing received messages,
 * and logging out. The function repeatedly asks the user for input
 * until the user chooses to exit by selecting the logout option.
 * 
 * @return void
 */
void secondMenu() {
	// Variable to store user's menu choice
    string choice;  
	 // Variable to control the loop
    bool exit = false;
	// Continue until the user chooses to exit
    while (!exit) {  
        cout << "****  Second Chat Menu  ****\n";
        cout << "1. Send Message\n";
        cout << "2. Received Messages\n";
        cout << "3. LogOut\n";
        cout << "Enter your choice [1-3]: ";
		// Read user's choice
        getline(cin, choice);  
		// Call function to send a new message
        if (choice == "1")
            sendNewMessage();  
		// Call function to display received messages
        else if (choice == "2")
            showMyMessages();  
		// Set exit flag to true to exit the loop
        else if (choice == "3")
            exit = true;  
		 // Display error message for invalid input
        else
            cout << "Invalid choice. Please try again [1-3] only.\n"; 
    }
}

/**
 * Allows a user to sign up by providing personal information.
 * 
 * asks the user to enter their name, password, re-enter password, and secure number.
 * Encrypts the password and secure number before storing them. 
 * Checks if the user already exists
 * If the user does not exist, adds the user to the list of all users.
 * 
 * @return void
 */
void userSignUp() {
    string name, secureNumber, password, rePassword, encryptedPassword, encryptedSecureNumber;
    // ask user to enter their name
	cout << "Enter Your Name: ";
    getline(cin, name);  
	// ask user to enter their password
    cout << "Enter Password: ";
    getline(cin, password);  
	// ask user to re-enter their password
    cout << "Enter Re-Password: ";
    getline(cin, rePassword);  
	// Check if the passwords match
	// // Exit the function if not match
    if (rePassword != password) {  
        cout << "Password mismatch. Failed to sign up.\n";
        return;  
    }
    cout << "Enter Secure Number: ";
	// ask user to enter their secure number
    getline(cin, secureNumber);  
    // Encrypt the password and secure number
    encrypt(password, encryptedPassword);
    encrypt(secureNumber, encryptedSecureNumber);
    
    // Check if the user already exists based on the provided info
    if (isUserExist(name, encryptedPassword, encryptedSecureNumber)) {
        cout << "Invalid signup data. This username already exists.\n";
    } else {
        // Create a new user and add them to the list of all users
        UserInfo userInfo;
        userInfo.name = name;
        userInfo.password = encryptedPassword;
        userInfo.secureNumber = encryptedSecureNumber;
        allUsers.push_back(userInfo);
        cout << "You have successfully signed up.\n";
    }
}

/**
 * Allows a user to log in by providing their info.
 * 
 * asks the user to enter their name, password, and secure number.
 * Encrypts the password and secure number before verifying the login info.
 * If the provided info match an existing user, the user is logged in and
 * directed to the second chat menu.
 * 
 * @return void
 */
void userLogIn() {
    string name, secureNumber, password, encryptedPassword, encryptedSecureNumber;
    cout << "Enter Your Name: ";
	// ask user to enter their name
    getline(cin, name);  
    cout << "Enter Password: ";
	// ask user to enter their password
    getline(cin, password);  
    cout << "Enter Secure Number: ";
	// ask user to enter their secure number
    getline(cin, secureNumber);  
    
    // Encrypt the password and secure number
    encrypt(password, encryptedPassword);
    encrypt(secureNumber, encryptedSecureNumber);
    
    // Check if the user exists based on the provided info
    if (isUserExist(name, encryptedPassword, encryptedSecureNumber)) {
		 // Set the logged-in user to name
        loginUser = name; 
        cout << "You are logged in as " << name << ".\n";
		 // show second chat menu
        secondMenu(); 
    } else {
		// Display message for invalid login info
        cout << "Invalid login data.\n";  
    }
}

/**
 * Saves all user data to a file.
 * 
 * Writes user data to file
 * Each user's data is written in the format: name,password,secureNumber.
 * 
 * @return void
 */
void saveAllUsersToFile() {
	// Open the file for writing
    ofstream file(allUsersFilePath);  
	// Check if the file opened successfully
    if (!(file.is_open())) {          
		// Return if file cannot be opened
        return;                       
    }
    // Write user data to the file
    for (int index = 0; index < allUsers.size(); index++) {
        file << allUsers[index].name << "," << allUsers[index].password << "," << allUsers[index].secureNumber << "\n";
    }
	 // Close the file
    file.close(); 
	// Display success message
    cout << "User data successfully written to " << allUsersFilePath << ".\n";  
}

/**
 * Saves all message data to a file.
 * 
 * Writes message data to the file
 * Each message's data is written in the format: sender,receiver,message.
 * 
 * @return void
 */
void saveAllMessagesToFile() {
	// Open the file for writing
    ofstream file(allMessagesFilePath); 
	 // Check if the file opened successfully
    if (!(file.is_open())) {            
		 // Return if file cannot be opened
        return;                         
    }
    // Write message data to the file
    for (int index = 0; index < allMessages.size(); index++) {
        file << allMessages[index].sender << "," << allMessages[index].reciever << "," << allMessages[index].message << "\n";
    }
	// Close the file
    file.close();  
	 // Display success message
    cout << "Message data successfully written to " << allMessagesFilePath << ".\n"; 
}


/**
 * The main function of the program.
 * 
 * entry point of the application. It performs the following tasks:
 * - Generates private and public keys for RSA encryption.
 * - Clears the vectors containing user and message data.
 * - Loads user data from a file into list of all users.
 * - Loads message data from a file into list of all messages.
 * - Displays a welcome message.
 * - Displays a main chat menu for user.
 * - Processes user input and calls appropriate functions based on the input.
 * - Exits the application if the user chooses to exit.
 * - Saves all users and all messages data to files.
 * 
 * @return 0 upon successful execution of the program.
 */
int main() {
	 // Generate private and public keys for RSA encryption
    createPrivateAndPublicKeys();  
	// Clear the list that containing all users data
    allUsers.clear();               
	// Clear the list that containing all messages data
    allMessages.clear();            
	// Load user data from file into all users list
    loadAllUsersFile();             
	// Load message data from file into all messages list
    loadAllMessagesFile();          
	 // Variable to store user's menu choice
    string choice;                 
	// Variable to control the loop
    bool exit = false;              
	 // Display welcome message
    cout << "Welcome in Our Application that implements a secure Chat\n\n"; 
	 // Continue until the user chooses to exit
    while (!exit) {                
        cout << "****  Secure Chat Menu  ****\n";
        cout << "1. Sign-up\n";
        cout << "2. Log-in\n";
        cout << "0. Exit\n";
        cout << "Enter your choice [0-2]: ";
		 // Read user's choice
        getline(cin, choice);      
		// sign up a new user
        if (choice == "1")
            userSignUp();      
		// log in an existing user
        else if (choice == "2")
            userLogIn();            
		// Set exit flag to true to exit the loop
        else if (choice == "0") {   
            exit = true;            
			// Display exit message
            cout << "Exiting Our Application Thanks...\n";  
			// Save user data to file
            saveAllUsersToFile();   
			// Save message data to file
            saveAllMessagesToFile();
        } else {
			// Display error message for invalid input
            cout << "Invalid choice. Please try again [0-2] only.\n";  
        }
    }
    system("pause");                
    return 0;
}
