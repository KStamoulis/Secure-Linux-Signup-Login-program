# Secure Linux Sign-up/Login program

This is a simple sign-up/login program for Linux. In the folder 'Simple-Vulnerable' there is a very simple and vulnerable sign-up/login program. 

In the folder 'Secure' there is a more secure version of the sign-up/login program. The improvements are the following:
- The password input is hidden when the user types it in.
- The password input is handled with read() system call instead of cin, which is more secure. Boundary checks are implemented to prevent buffer overflow.
- The program handles SIGINT (Ctrl+C) to ensure that the terminal settings are restored if the user interrupts the program while entering a password.
- The program uses termios to disable echoing of the password input, enhancing security by preventing shoulder surfing attacks. ??
- The password is stored in the database file in a hashed format using SHA-256, instead of plain text.
- The password before hashing is salted with a unique salt for each user, which is stored alongside the hashed password in the database file. This adds an extra layer of security against rainbow table attacks.
- The program uses a more secure method for comparing the entered password with the stored hashed password, which is resistant to timing attacks.??

