# cw2-
Read me

The Secure Chat Application is a robust platform built using C++, designed to facilitate encrypted communication through text between users. It exemplifies a practical application of cryptographic principles, specifically RSA encryption, to ensure that all messages exchanged within the system are kept confidential and secure from unauthorized access.

What Does the Chat Application Do? 
This application enables users to sign up with their credentials, log in, and engage in secure conversations with other users. The core functionality revolves around text-based messaging where every message sent and received within the system is encrypted using RSA encryption. This ensures that even if the data is intercepted, the actual content remains inaccessible without the appropriate decryption keys. The system stores all user credentials and message histories in files, allowing for persistence of data across different sessions of the application. Users can view their message history, which is decrypted upon access, providing a seamless user experience while maintaining security.

Overview of the Code The codebase of the Secure Chat Application is comprehensive, incorporating various aspects necessary for running a secure messaging service. Key components include: RSA Encryption: At the heart of the application’s security measures is the RSA algorithm, which is used to encrypt and decrypt messages. The system generates private and public keys based on prime numbers, allowing secure communication between users.

User Management: The application handles user data through functions that allow users to sign up, log in, and log out. All user information, including encrypted passwords and secure numbers (a unique identifier for additional security), is stored in a file named allUsers.txt. Message Handling: Messages are managed through a series of functions that facilitate sending and receiving encrypted messages. These messages are stored in another file, allMessages.txt, ensuring that the conversation history is retained.

File Handling: The application reads from and writes to files to load and store user data and messages. This aspect is crucial for data persistence, allowing the system to maintain state between sessions.

How to Use the Application
 To get started with the Secure Chat Application: Installation: Clone the repository from GitHub and compile the C++ files using a C++11 compatible compiler by running commands such as g++ -o SecureChat main.cpp in your terminal. Running the Application: Execute the compiled application by entering ./SecureChat. The program will greet you with a main menu offering options to sign up, log in, or exit.

Navigating the Menu: Use the menu to create an account or log in to an existing one. Once logged in, you can send encrypted messages to other users and view messages you have received. Exiting: To exit the application, select the exit option from the main menu. This action will save all recent data to the respective files, ensuring that your messages and user information are updated for the next session.

This chat application is a fantastic tool for those interested in understanding how encryption can be applied in real-world software applications to enhance privacy and security in digital communications.
