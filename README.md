# bank-management-system
bank management system project in c++

The program first asks for the password which is set to "abcde". It gives you 3 tries for correct password.

If you fail to enter the correct password the system gets locked and the password can be reset only by entering the security code which is fixed to "1234". If you enter the security code correctly, the system asks you to reset the password else the system access is locked.

Once you get into the system, there are 3 options given: 
-->administration which for managing the account information, searching of a particular account, closing an account
-->transaction which has 3 options: deposit, withdraw and generating the passbook i.e. the list of all the transactions made by the account
-->quit

There are 2 files: 
-->master.dat which stores the information about all the customers and their account details
-->transaction.dat which stores the details of all the transactions
