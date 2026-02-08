# Secure Linux Sign-up/Login program

This is a simple sign-up/login program for Linux. In the folder 'Simple-Vulnerable' there is a very simple and vulnerable sign-up/login program. The goal is to show how a simple program can have multiple vulnerabilities and how to fix them. 

In the folder 'Secure' there is a more secure version of the sign-up/login program. The implemented security improvements are the following:
- The password input is hidden when the user types it in, preventing shoulder surfing attacks.
- The program handles SIGINT (Ctrl+C) to ensure that the terminal settings are restored if the user interrupts the program while entering a password.
- The password input is handled with read() system call instead of cin, which is more secure as it does not use hidden buffers. Boundary checks are implemented to prevent buffer overflow attacks.
- The password is stored in the database file in a hashed format using SHA-256, instead of plain text.
- The password before hashing is salted with a unique random salt for each user, which is stored alongside the hashed password in the database file. This adds an extra layer of security against rainbow table attacks.
- Added security hardening flags to the Makefile to improve the security of the compiled binary.

To further improve the security of the program things that could be added are:
- Implementing rate limiting and account lockout after a certain number of failed login attempts to prevent brute-force attacks.
- Use a more secure hashing algorithm such as PBKDF2 or Argon2 instead of SHA-256, which is designed to be computationally expensive and resistant to brute-force attacks from GPUs.
- Have an encrypted database file or use a secure database management system to store user credentials, instead of a plain text file. This was not implemented in the secure version to keep things simple and focused on the password handling improvements.
- In fuction loginUser there is a vulnerability in the time taken to compare the entered password with the stored hashed password, which can be exploited in a timing attack. To mitigate this vulnerability, a constant-time comparison function should be used to compare the hashed passwords, which takes the same amount of time regardless of the input. There are other places in the code where this vulnerability is present.




