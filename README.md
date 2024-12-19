# Kharazyan Bank

**Kharazyan Bank** is a console-based banking system implemented in C. It simulates basic banking operations in a text-based environment. Users can register accounts, log in, deposit and withdraw funds, transfer money, and view account information. Administrators have additional privileges allowing them to manage the system more broadly.

## Overview

This application emulates a simplified banking environment. Regular users can maintain their accounts, while administrators can manage multiple accounts, block or unblock them, reset the database, and more. The interface is console-driven, ensuring that the system can run on most Unix-like environments without additional GUI libraries.

## Features

### User Operations

- **Register a New Account:**  
  Create an account with a username (owner name) and a password (both must be at least 8 characters long).
  
- **Login to an Existing Account:**  
  Access your account using your username and password. Three incorrect password attempts result in automatic account blocking.
  
- **View Account Balance:**  
  Check your account’s current balance at any time.

- **Deposit Funds (Minimum 1000):**  
  Add money to your account balance. The minimum deposit amount is 1000 units (e.g., 1000 AMD).
  
- **Withdraw Funds (1% Commission):**  
  Remove funds from your account. The withdrawal incurs a 1% commission, which is deducted along with the requested amount.
  
- **Transfer Money (1% Commission):**  
  Transfer funds from your account to another user’s account. A 1% commission is applied to the transferred amount.
  
- **Block Your Own Account:**  
  If needed, a user can block their own account. Once blocked, the user must contact an administrator to unblock it.

### Administrative Operations

- **View All Users:**  
  List all registered accounts including their IDs, owners, and statuses.
  
- **View Blocked Accounts:**  
  Quickly see which accounts are currently blocked.
  
- **Change Account Status:**  
  Administrators can block, activate, or grant admin privileges to other accounts.
  
- **Change Account Password:**  
  Reset or change the password of any user’s account.
  
- **Reset the Database:**  
  Clear all data, including user accounts and metadata. This action is irreversible and requires the admin password.

### Security and Constraints

- **Admin Password:**  
  There is a fixed admin password (`papayutyun`) known to the administrator.
  
- **Blocking Mechanism:**  
  After 3 incorrect login attempts, the account is automatically blocked.
  
- **Data Persistence:**  
  User accounts and system metadata are stored in `passwd.txt` and `metainfo.txt`, ensuring persistence across runs.

## Project Structure

```
project/
├── include/
│   ├── bank.h        // Type definitions, constants, and extern globals
│   ├── functions.h   // Prototypes for all functions
├── src/
│   ├── main.c        // Entry point of the application
│   ├── accounts.c    // User-related operations (login, deposit, withdraw, transfer)
│   ├── admin.c       // Administrative functionalities (block accounts, change status, etc.)
│   ├── metainfo.c    // Metadata handling (reading/writing system info, registration)
│   ├── utils.c       // Utility functions (parsing, cleaning input, synchronization)
├── Makefile
├── passwd.txt        // Stores account data
└── metainfo.txt      // Stores system metadata (number of accounts, total money, etc.)
```

**Key Files:**

- **`passwd.txt`**: Stores user account information in a formatted text form.
- **`metainfo.txt`**: Holds system-wide info such as total accounts, blocked accounts, and cumulative transaction statistics.

## Building the Project

Before you start, ensure that you have:

- A C compiler (e.g., `gcc`)
- `make` utility

**Build Steps:**

1. Navigate to the project’s root directory.
2. Run:
   ```bash
   make
   ```
   
If everything is set up correctly, the compilation will produce an executable named `bank_app` (or the name specified in the Makefile).

## Running the Application

To run the program after building:

```bash
./bank_app
```

Upon starting, you will see the main menu:

1. **Register a new user**  
   Allows you to create a new user account.

2. **View registered users**  
   Prints a list of all accounts (for admins or just browsing).

3. **Login as a user**  
   Once logged in, you can access account-specific functions.

4. **Exit**  
   Quit the program gracefully.

**Admin Access:**  
To access admin functionalities, you either need to log in to an admin account or convert a user account to admin privileges by providing the admin password.

## Example Workflows

### Registering a New User

1. Run the program and select "1. Register a new user."
2. Enter a username (at least 8 characters).
3. Enter a password (at least 8 characters).
4. After successful registration, you can log in and start using the account.

### Depositing Money

1. Log in to your account.
2. From the account menu, choose "Deposit funds."
3. Enter an amount (>= 1000).
4. The account balance updates accordingly.

### Withdrawing Money

1. Log in to your account.
2. Choose "Withdraw funds."
3. Enter the amount you wish to withdraw.
4. The system deducts the amount plus a 1% commission.

### Admin Tasks

1. Log in as an admin user or gain admin privileges by entering the admin password.
2. Access the "Admin Menu" to view all accounts, block accounts, or reset the entire database.
3. Use "Change account password" or "Change account status" options to manage users.

## Tips

- Always remember the admin password (`papayutyun`) to unlock administrative tasks.
- If you forget your password, an admin can reset it for you.
- Make sure to have at least 1000 units before making a deposit (or it will be rejected).
- Review your account status frequently if you encounter login issues.
