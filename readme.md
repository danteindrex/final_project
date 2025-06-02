# SACCO Management System - Complete Beginner's Guide

## Table of Contents
1. [Introduction](#introduction)
2. [What is a SACCO?](#what-is-a-sacco)
3. [Understanding Data Structures](#understanding-data-structures)
4. [Code Structure Overview](#code-structure-overview)
5. [Header Files and Libraries](#header-files-and-libraries)
6. [Constants and Definitions](#constants-and-definitions)
7. [Data Structures Explained](#data-structures-explained)
8. [Global Variables](#global-variables)
9. [Function Explanations](#function-explanations)
10. [Main Program Flow](#main-program-flow)
11. [How Each Feature Works](#how-each-feature-works)
12. [Memory Management](#memory-management)
13. [Why We Use These Data Structures](#why-we-use-these-data-structures)
14. [Common Beginner Questions](#common-beginner-questions)

---

## Introduction

Welcome to the complete guide for understanding the SACCO Management System! This document will explain every single part of the code in simple terms, as if you're learning programming for the first time.

**Don't worry if you feel overwhelmed at first** - programming is like learning a new language. We'll break everything down into small, easy-to-understand pieces.

---

## What is a SACCO?

A **SACCO** stands for "Savings and Credit Cooperative Organization." Think of it like a small bank that serves a community, especially farmers. People can:
- **Deposit money** (put money into their account)
- **Withdraw money** (take money out of their account)
- **Check their balance** (see how much money they have)
- **Transfer money** to other people
- **Get statements** (see their transaction history)

Our program simulates this bank system using a computer program written in C.

---

## Understanding Data Structures

Before we look at the code, let's understand what **data structures** are:

### What is a Data Structure?
A data structure is like a **container** or **organizer** for storing information in your computer's memory. Just like you might organize your clothes in different ways:
- **Closet** = stores clothes in order
- **Drawer** = stores clothes in categories
- **Laundry basket** = stores clothes temporarily

In programming, we have different "containers" for storing data:

### 1. **Array** 
```c
int numbers[5] = {1, 2, 3, 4, 5};
```
- Like a **row of boxes** numbered 0, 1, 2, 3, 4
- Each box can hold one piece of data
- You access data by saying "give me what's in box number 2"

### 2. **Linked List**
```c
struct Node {
    int data;
    struct Node* next;
};
```
- Like a **chain of boxes** where each box points to the next box
- You can add or remove boxes anywhere in the chain
- Like a train where each car is connected to the next car

### 3. **Stack**
```c
struct Stack {
    int items[100];
    int top;
};
```
- Like a **stack of plates** - you can only add or remove from the top
- "Last In, First Out" (LIFO) - the last plate you put on is the first one you take off

### 4. **Queue**
```c
struct Queue {
    int items[100];
    int front, rear;
};
```
- Like a **line at the bank** - first person in line is first to be served
- "First In, First Out" (FIFO)

### 5. **Hash Table**
```c
struct HashEntry* table[101];
```
- Like a **phone book** - you can quickly find someone's number by their name
- Very fast for looking up information

---

## Code Structure Overview

Our SACCO program is organized into several parts:

```
1. Header files and libraries (what tools we're using)
2. Constants (fixed numbers we use throughout)
3. Data structure definitions (our containers)
4. Global variables (data everyone can access)
5. Function declarations (list of what our program can do)
6. Main function (where the program starts)
7. All the other functions (the actual work)
```

Think of it like a recipe book:
- **Header files** = the kitchen tools you need
- **Constants** = measurements that never change
- **Data structures** = your containers and bowls
- **Functions** = individual recipe steps
- **Main function** = the order you follow the recipes

---

## Header Files and Libraries

```c
#include <stdio.h>      // For input/output (printf, scanf)
#include <string.h>     // For text manipulation (strcmp, strcpy)
#include <stdlib.h>     // For memory management (malloc, free)
#include <time.h>       // For date and time functions
#include <stdbool.h>    // For true/false values
```

**Think of these like importing tools into your workshop:**
- `stdio.h` = your printer and scanner
- `string.h` = your text editing tools
- `stdlib.h` = your memory management tools
- `time.h` = your clock and calendar
- `stdbool.h` = your yes/no decision maker

---

## Constants and Definitions

```c
#define MAX_FARMERS 100
#define MAX_TRANSACTIONS 1000
#define PASSWORD_LENGTH 4
#define HASH_TABLE_SIZE 101
```

**Constants are like rules that never change:**
- `MAX_FARMERS 100` means "our bank can have at most 100 customers"
- `MAX_TRANSACTIONS 1000` means "we can remember at most 1000 transactions"
- `PASSWORD_LENGTH 4` means "passwords must be 4 numbers long"
- `HASH_TABLE_SIZE 101` means "our lookup table has 101 slots"

**Why do we use constants?**
- If we want to change the maximum number of farmers later, we only change it in one place
- It makes our code easier to read and understand
- It prevents mistakes (like accidentally typing 99 instead of 100)

---

## Data Structures Explained

Let's look at each data structure in detail:

### 1. Transaction Structure
```c
typedef struct {
    int farmer_id;          // Which farmer made this transaction
    int amount;             // How much money
    time_t timestamp;       // When it happened
    char type;              // 'D' for deposit, 'W' for withdrawal
    char description[100];  // What the transaction was for
} Transaction;
```

**Think of this like a receipt from the bank:**
- `farmer_id` = customer number
- `amount` = how much money
- `timestamp` = date and time
- `type` = deposit or withdrawal
- `description` = notes about the transaction

### 2. Transaction Node (for Linked List)
```c
typedef struct TransactionNode {
    Transaction data;               // The actual transaction information
    struct TransactionNode* next;   // Pointer to the next transaction
} TransactionNode;
```

**This is like a train car:**
- `data` = the cargo (transaction information)
- `next` = the connection to the next car

**Why use a linked list for transactions?**
- We don't know how many transactions each farmer will have
- We can easily add new transactions to the beginning
- We can go through all transactions in order

### 3. Transaction Stack
```c
typedef struct {
    Transaction items[MAX_TRANSACTIONS];  // Array to store transactions
    int top;                             // Index of the top item
} TransactionStack;
```

**This is like a stack of papers on your desk:**
- `items[]` = the stack of papers
- `top` = which paper is on top (and how many papers total)

**Why use a stack?**
- We want to see the most recent transactions first
- It's very fast to add new transactions (just put on top)
- It's very fast to see recent transactions (just look at the top)

### 4. Transaction Queue
```c
typedef struct {
    Transaction items[MAX_TRANSACTIONS];  // Array to store transactions
    int front;                           // Index of first item
    int rear;                            // Index of last item
    int size;                            // How many items we have
} TransactionQueue;
```

**This is like a line at the bank:**
- `items[]` = the people in line
- `front` = the first person in line
- `rear` = the last person in line
- `size` = how many people are in line

**Why use a queue?**
- For processing transactions in the order they happened
- Fair processing (first come, first served)

### 5. Hash Table Entry
```c
typedef struct HashEntry {
    int farmer_id;              // The farmer's ID number
    int index;                  // Where to find this farmer in our array
    struct HashEntry* next;     // Next entry (in case of collision)
} HashEntry;
```

**This is like an index in a book:**
- `farmer_id` = the topic you're looking for
- `index` = what page it's on
- `next` = other topics that might be on the same page

**Why use a hash table?**
- Finding a farmer by ID is VERY fast (like using an index instead of reading the whole book)
- Instead of checking 100 farmers one by one, we can jump directly to the right one

### 6. Farmer Structure
```c
typedef struct {
    int farmer_id;                    // Unique ID number
    char username[50];                // Farmer's name
    int password;                     // 4-digit password
    double balance;                   // How much money they have
    TransactionNode* transactions;    // Pointer to their transaction history
    int transaction_count;            // How many transactions they've made
} Farmer;
```

**This is like a complete customer file:**
- `farmer_id` = customer number
- `username` = customer name
- `password` = secret code to access account
- `balance` = current money in account
- `transactions` = history of all their transactions (linked list)
- `transaction_count` = total number of transactions

---

## Global Variables

```c
Farmer farmers[MAX_FARMERS];              // Array of all farmers
int num_farmers = 5;                      // How many farmers we have
TransactionStack recent_transactions;     // Stack of recent transactions
TransactionQueue transaction_queue;       // Queue for processing
HashEntry* farmer_hash_table[HASH_TABLE_SIZE]; // Hash table for quick lookup
```

**Global variables are like the bank's main records:**
- `farmers[]` = filing cabinet with all customer files
- `num_farmers` = how many customers we have
- `recent_transactions` = recent activity log
- `transaction_queue` = transactions waiting to be processed
- `farmer_hash_table[]` = quick lookup directory

**Why are these global?**
- All functions need access to customer information
- It's like having the bank's main database available everywhere

---

## Function Explanations

Let's go through each function and understand what it does:

### Main Function - The Program's Starting Point
```c
int main() {
    initialize_system();        // Set up the bank with sample data
    
    while (1) {                // Keep running forever (until user exits)
        clear_screen();        // Clear the screen
        display_welcome_banner(); // Show welcome message
        
        int farmer_id = authenticate(); // Ask user to log in
        if (farmer_id == -1) continue; // If login failed, try again
        
        // Show menu and handle user choices
        char choice[10];
        do {
            // Display menu and get user choice
            // Call appropriate function based on choice
        } while (1);
    }
    
    free_memory();  // Clean up before ending
    return 0;       // Program ended successfully
}
```

**Think of main() like the bank manager who:**
1. Opens the bank in the morning (initialize_system)
2. Greets each customer (display_welcome_banner)
3. Checks their ID (authenticate)
4. Helps them with their banking needs (menu options)
5. Closes the bank at the end (free_memory)

### Initialize System Function
```c
void initialize_system() {
    // Set up hash table (make it empty)
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        farmer_hash_table[i] = NULL;
    }
    
    // Create sample farmers
    char* usernames[] = {"trevor", "arnold", "shafiq", "jeremiah", "dorris"};
    int passwords[] = {1539, 2247, 1426, 1123, 3241};
    double balances[] = {5000.00, 7500.50, 3000.25, 6000.75, 9000.00};
    
    // Set up each farmer's account
    for (int i = 0; i < num_farmers; i++) {
        farmers[i].farmer_id = i + 1;
        strcpy(farmers[i].username, usernames[i]);
        farmers[i].password = passwords[i];
        farmers[i].balance = balances[i];
        farmers[i].transactions = NULL;
        farmers[i].transaction_count = 0;
        
        insert_farmer_hash(farmers[i].farmer_id, i);
        add_transaction(i+1, balances[i], 'D', "Initial deposit - Account opening");
    }
    
    // Set up empty stack and queue
    recent_transactions.top = -1;
    transaction_queue.front = 0;
    transaction_queue.rear = -1;
    transaction_queue.size = 0;
}
```

**This function is like setting up a new bank:**
1. **Prepare the filing system** (hash table)
2. **Create customer accounts** with sample data
3. **Give each customer an initial deposit**
4. **Set up record-keeping systems** (stack and queue)

**Why do we need sample data?**
- So you can test the program immediately
- Real banks would load this data from a database
- For learning purposes, we create it in the code

### Authentication Function
```c
int authenticate() {
    char username[50];
    int password;
    
    printf("\n👤 Enter username (or 'exit' to quit): ");
    scanf("%s", username);
    
    if (strcmp(username, "exit") == 0) {
        free_memory();
        exit(0);
    }
    
    printf("🔑 Enter password: ");
    scanf("%d", &password);
    
    // Check if username and password match any farmer
    for (int i = 0; i < num_farmers; i++) {
        if (strcmp(username, farmers[i].username) == 0 && 
            password == farmers[i].password) {
            printf("\n✅ Authentication successful! Welcome, %s.\n", username);
            return farmers[i].farmer_id;
        }
    }
    
    printf("Authentication failed. Invalid username or password.\n");
    return -1;  // -1 means login failed
}
```

**This function is like a security guard:**
1. **Ask for ID** (username)
2. **Ask for password**
3. **Check the records** to see if they match
4. **Let them in** if correct, or **deny access** if wrong

**How it works step by step:**
1. User types their username
2. If they type "exit", the program ends
3. User types their password (number)
4. Program checks all farmers to find a match
5. If found: return the farmer's ID number
6. If not found: return -1 (which means "failed")

### Hash Table Functions

#### Hash Function
```c
int hash_function(int farmer_id) {
    return farmer_id % HASH_TABLE_SIZE;
}
```

**This is like a filing system rule:**
- Take the farmer's ID number
- Divide it by 101 and take the remainder
- That remainder tells us which "slot" to use

**Example:**
- Farmer ID 1: 1 % 101 = 1 (goes in slot 1)
- Farmer ID 102: 102 % 101 = 1 (also goes in slot 1)
- Farmer ID 205: 205 % 101 = 3 (goes in slot 3)

#### Insert into Hash Table
```c
void insert_farmer_hash(int farmer_id, int index) {
    int hash_index = hash_function(farmer_id);          // Find which slot
    HashEntry* new_entry = malloc(sizeof(HashEntry));   // Create new entry
    new_entry->farmer_id = farmer_id;
    new_entry->index = index;
    new_entry->next = farmer_hash_table[hash_index];    // Link to existing entries
    farmer_hash_table[hash_index] = new_entry;          // Put at front of list
}
```

**This is like adding a card to a filing system:**
1. **Calculate which drawer** to use (hash_function)
2. **Create a new index card** (malloc)
3. **Write the information** on the card
4. **Put it at the front** of that drawer

#### Lookup in Hash Table
```c
int lookup_farmer_hash(int farmer_id) {
    int hash_index = hash_function(farmer_id);      // Find which slot
    HashEntry* current = farmer_hash_table[hash_index]; // Start looking in that slot
    
    while (current != NULL) {                       // Look through the chain
        if (current->farmer_id == farmer_id) {      // Found it!
            return current->index;
        }
        current = current->next;                    // Try next entry
    }
    return -1;  // Not found
}
```

**This is like looking up a phone number:**
1. **Open the right section** of the phone book (hash_index)
2. **Look through that section** until you find the name
3. **Return the information** when found
4. **Return "not found"** if you reach the end

### Deposit Function
```c
void deposit(int farmer_id) {
    clear_screen();
    // Show deposit screen
    
    double amount;
    char description[100];
    
    printf("\n💵 Enter amount to deposit: $");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("\n❌ Invalid amount! Please enter a positive value.\n");
        return;
    }
    
    // Get optional description
    printf("📝 Enter description (optional): ");
    getchar(); // consume newline
    fgets(description, sizeof(description), stdin);
    
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    // Update balance
    farmers[index].balance += amount;
    
    // Record transaction
    add_transaction(farmer_id, amount, 'D', description);
    
    // Show success message with receipt
    printf("\n✅ DEPOSIT SUCCESSFUL ✅\n");
    printf("Amount Deposited: $%.2f\n", amount);
    printf("New Balance: $%.2f\n", farmers[index].balance);
}
```

**This function is like a bank teller handling a deposit:**
1. **Ask how much** money to deposit
2. **Check if the amount is valid** (positive number)
3. **Ask for a description** (optional note)
4. **Find the customer's account**
5. **Add money to their balance**
6. **Record the transaction** in their history
7. **Print a receipt**

**Step-by-step process:**
- Customer says "I want to deposit $100"
- Teller checks: "Is $100 a valid amount?" (Yes)
- Teller asks: "What is this deposit for?" (Customer explains)
- Teller finds customer's account in the system
- Teller adds $100 to the account balance
- Teller writes down the transaction in the records
- Teller gives customer a receipt

### Withdraw Function
```c
void withdraw(int farmer_id) {
    // Similar to deposit, but:
    // 1. Check if they have enough money first
    // 2. Subtract money instead of adding
    // 3. Record as withdrawal ('W') instead of deposit ('D')
    
    if (amount > farmers[index].balance) {
        printf("\n❌ Insufficient funds!\n");
        printf("Requested: $%.2f\n", amount);
        printf("Available: $%.2f\n", farmers[index].balance);
        return;
    }
    
    farmers[index].balance -= amount;  // Subtract money
    add_transaction(farmer_id, amount, 'W', description);
}
```

**The key difference from deposit:**
- **Check balance first** - make sure they have enough money
- **Subtract money** instead of adding it
- **Mark as withdrawal** ('W') instead of deposit ('D')

### Add Transaction Function
```c
void add_transaction(int farmer_id, double amount, char type, const char* description) {
    time_t now = time(NULL);  // Get current time
    
    // Create new transaction record
    Transaction t;
    t.farmer_id = farmer_id;
    t.amount = amount;
    t.timestamp = now;
    t.type = type;
    strcpy(t.description, description);
    
    int index = find_farmer_index(farmer_id);
    if (index == -1) return;
    
    // Add to farmer's linked list (at the beginning)
    TransactionNode* new_node = malloc(sizeof(TransactionNode));
    new_node->data = t;
    new_node->next = farmers[index].transactions;
    farmers[index].transactions = new_node;
    farmers[index].transaction_count++;
    
    // Also add to stack and queue
    push_to_stack(t);
    enqueue_transaction(t);
}
```

**This function is like a record keeper:**
1. **Get the current time** (timestamp)
2. **Create a transaction record** with all the details
3. **Find the customer's file**
4. **Add the record to their history** (linked list)
5. **Update their transaction count**
6. **Also add to recent activity** (stack and queue)

**Why add to multiple places?**
- **Linked list**: Customer's personal history
- **Stack**: System's recent activity log
- **Queue**: For processing in order

### Display Functions

The display functions create the beautiful ASCII art interface:

```c
void display_welcome_banner() {
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ███████╗ █████╗  ██████╗ ██████╗ ██████╗     ███████╗██╗   ██╗███████╗  ║\n");
    printf("║    SACCO Management System                                                   ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}
```

**These functions are like the bank's interior decorators:**
- They make the program look professional and easy to use
- They organize information in neat tables and boxes
- They use symbols and colors to make things clear

---

## Main Program Flow

Here's how the program works from start to finish:

```
1. Program starts (main function)
   ↓
2. Initialize system (create sample accounts)
   ↓
3. Show welcome screen
   ↓
4. Ask user to log in
   ↓
5. Check username and password
   ↓
6. If login fails → go back to step 3
   If login succeeds → continue
   ↓
7. Show main menu with options
   ↓
8. User chooses an option:
   - Deposit money
   - Withdraw money
   - Check balance
   - View statements
   - Transfer money
   - View statistics
   - Logout
   ↓
9. Perform the chosen action
   ↓
10. Show results to user
    ↓
11. Go back to step 7 (show menu again)
    ↓
12. If user chooses logout → go back to step 3
    If user exits program → clean up memory and end
```

---

## How Each Feature Works

### 1. **User Authentication (Login)**
```
User enters username → Program searches all farmers → 
If found, ask for password → Check if password matches → 
If yes: login successful → If no: login failed
```

**Why it's secure:**
- Passwords are required
- Wrong password = access denied
- Each farmer can only access their own account

### 2. **Money Deposit**
```
User chooses deposit → Enter amount → Check if amount > 0 → 
Enter description → Find user's account → Add money to balance → 
Record transaction → Show receipt
```

**What happens in memory:**
- Balance number increases
- New transaction added to linked list
- Transaction added to stack (recent activity)
- Transaction count increases

### 3. **Money Withdrawal**
```
User chooses withdraw → Show current balance → Enter amount → 
Check if amount ≤ balance → If yes: subtract from balance → 
Record transaction → Show receipt
If no: show "insufficient funds" error
```

**Safety checks:**
- Can't withdraw more than you have
- Can't withdraw negative amounts
- Balance is updated immediately

### 4. **Balance Check**
```
User chooses balance → Find user's account → 
Display current balance + account information
```

**Information shown:**
- Current balance
- Account holder name
- Total number of transactions
- Last update time

### 5. **Account Statement**
```
User chooses statement → Choose type:
- Last N transactions → Show N most recent
- Date range → Show transactions between two dates
- All transactions → Show complete history
```

**How it works:**
- Goes through linked list of transactions
- Filters based on user's choice
- Displays in neat table format

### 6. **Money Transfer**
```
User chooses transfer → Enter recipient ID → Check if recipient exists → 
Enter amount → Check if sender has enough money → 
Subtract from sender → Add to recipient → 
Record transactions for both → Show confirmation
```

**What happens:**
- Two transactions created (one withdrawal, one deposit)
- Both accounts updated
- Both transaction histories updated

---

## Memory Management

### Why Memory Management Matters
In C, when you use `malloc()` to create memory, you must use `free()` to release it. It's like:
- `malloc()` = renting a storage unit
- `free()` = returning the keys when you're done

### Where We Use Dynamic Memory
```c
// Creating new transaction node
TransactionNode* new_node = malloc(sizeof(TransactionNode));

// Creating hash table entry  
HashEntry* new_entry = malloc(sizeof(HashEntry));
```

### How We Clean Up
```c
void free_memory() {
    // Free all transaction linked lists
    for (int i = 0; i < num_farmers; i++) {
        TransactionNode* current = farmers[i].transactions;
        while (current != NULL) {
            TransactionNode* temp = current;
            current = current->next;
            free(temp);  // Release this node
        }
    }
    
    // Free hash table entries
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashEntry* current = farmer_hash_table[i];
        while (current != NULL) {
            HashEntry* temp = current;
            current = current->next;
            free(temp);  // Release this entry
        }
    }
}
```

**Why this is important:**
- Prevents memory leaks (wasted memory)
- Makes program run efficiently
- Good programming practice

---

## Why We Use These Data Structures

### 1. **Array for Farmers**
```c
Farmer farmers[MAX_FARMERS];
```
**Pros:**
- Very fast access by index: `farmers[0]`, `farmers[1]`
- Simple to understand and use
- Memory efficient

**Cons:**
- Fixed size (can't grow)
- Need to know maximum number ahead of time

**Why we chose it:** Perfect for a fixed number of bank customers

### 2. **Linked List for Transactions**
```c
TransactionNode* transactions;
```
**Pros:**
- Can grow and shrink as needed
- Very fast to add new transactions (O(1))
- Don't need to know how many transactions ahead of time

**Cons:**
- Uses more memory (each node needs a pointer)
- Can't jump directly to transaction #50 (must follow chain)

**Why we chose it:** Each farmer might have different numbers of transactions

### 3. **Hash Table for Farmer Lookup**
```c
HashEntry* farmer_hash_table[HASH_TABLE_SIZE];
```
**Pros:**
- VERY fast lookup (usually O(1))
- Much faster than searching through array

**Cons:**
- Uses extra memory
- More complex to implement

**Why we chose it:** Finding farmers by ID needs to be fast

### 4. **Stack for Recent Transactions**
```c
TransactionStack recent_transactions;
```
**Pros:**
- Perfect for "most recent first" order
- Very fast to add/remove (O(1))

**Cons:**
- Can only access the top item easily

**Why we chose it:** Users usually want to see recent activity first

### 5. **Queue for Transaction Processing**
```c
TransactionQueue transaction_queue;
```
**Pros:**
- Fair processing (first come, first served)
- Good for batch processing

**Cons:**
- More complex than simple array

**Why we chose it:** Transactions should be processed in order

### Performance Comparison

| Operation | Array | Linked List | Hash Table | Stack | Queue |
|-----------|-------|-------------|------------|-------|-------|
| Add item | O(1) | O(1) | O(1) | O(1) | O(1) |
| Find item | O(n) | O(n) | O(1) | O(n) | O(n) |
| Remove item | O(n) | O(1)* | O(1) | O(1) | O(1) |
| Access by position | O(1) | O(n) | N/A | O(n) | O(n) |

*O(1) if you know which node to remove

**What O(1) and O(n) mean:**
- **O(1)**: Always takes the same time, no matter how much data you have
- **O(n)**: Takes longer as you have more data

---

## Common Beginner Questions

### Q1: "What does `typedef struct` mean?"
**Answer:** It's like creating a blueprint for a new type of container.

```c
typedef struct {
    int farmer_id;
    char username[50];
    double balance;
} Farmer;
```

This says: "From now on, when I say 'Farmer', I mean a container that holds a farmer_id, username, and balance."

### Q2: "What is a pointer and why do we use `*`?"
**Answer:** A pointer is like an address or GPS coordinate.

```c
TransactionNode* next;
```

Instead of storing the actual data, we store the **address** where the data is located. It's like saying "the next transaction is stored at location 12345 in memory."

### Q3: "Why do we use `malloc()` and `free()`?"
**Answer:** 
- `malloc()` = "Computer, please give me some memory to store something"
- `free()` = "Computer, I'm done with this memory, you can use it for something else"

It's like renting and returning a storage unit.

### Q4: "What does `NULL` mean?"
**Answer:** `NULL` means "nothing" or "empty."

```c
if (farmers[i].transactions == NULL) {
    // This farmer has no transactions yet
}
```

It's like an empty box - there's nothing inside.

### Q5: "How does the hash table actually work?"
**Answer:** Imagine a filing cabinet with 101 drawers numbered 0-100.

```c
int hash_function(int farmer_id) {
    return farmer_id % 101;
}
```

- Farmer ID 1 → 1 % 101 = 1 → goes in drawer 1
- Farmer ID 102 → 102 % 101 = 1 → also goes in drawer 1 (collision!)
- Farmer ID 205 → 205 % 101 = 3 → goes in drawer 3

When multiple items go in the same drawer, we chain them together like a linked list.

### Q6: "Why is the linked list better than an array for transactions?"
**Answer:** 

**Array:**
```c
Transaction transactions