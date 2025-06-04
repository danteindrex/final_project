#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define MAX_FARMERS 100
#define MAX_TRANSACTIONS 1000
#define PASSWORD_LENGTH 4
#define HASH_TABLE_SIZE 101

// Transaction structure
typedef struct {
    int farmer_id;
    int amount;
    time_t timestamp;
    char type; // 'D' for deposit, 'W' for withdrawal
    char description[100];
} Transaction;

// Node for linked list of transactions
typedef struct TransactionNode {
    Transaction data;
    struct TransactionNode* next;
} TransactionNode;

// Stack for recent transactions
typedef struct {
    Transaction items[MAX_TRANSACTIONS];
    int top;
} TransactionStack;

// Queue for processing transactions
typedef struct {
    Transaction items[MAX_TRANSACTIONS];
    int front;
    int rear;
    int size;
} TransactionQueue;

// Hash table entry for farmer lookup
typedef struct HashEntry {
    int farmer_id;
    int index;
    struct HashEntry* next;
} HashEntry;

// Farmer account structure
typedef struct {
    int farmer_id;
    char username[50];
    int password;
    double balance;
    TransactionNode* transactions; // Linked list of transactions
    int transaction_count;
} Farmer;

// Global data structures
Farmer farmers[MAX_FARMERS];
int num_farmers = 5;
TransactionStack recent_transactions;
TransactionQueue transaction_queue;
HashEntry* farmer_hash_table[HASH_TABLE_SIZE];

// Function prototypes
void initialize_system();
void display_welcome_banner();
void display_main_menu();
void display_farmer_menu(int farmer_id);
int authenticate();
void deposit(int farmer_id);
void withdraw(int farmer_id);
void check_balance(int farmer_id);
void account_statement(int farmer_id);
void transfer_money(int farmer_id);
void add_transaction(int farmer_id, double amount, char type, const char* description);
void display_recent_transactions(int farmer_id, int n);
void display_transactions_by_date(int farmer_id, time_t start, time_t end);
void push_to_stack(Transaction t);
void enqueue_transaction(Transaction t);
Transaction dequeue_transaction();
void print_transaction(Transaction t);
void print_separator();
void print_box(const char* text);
void free_memory();
int find_farmer_index(int farmer_id);
int hash_function(int farmer_id);
void insert_farmer_hash(int farmer_id, int index);
int lookup_farmer_hash(int farmer_id);
void display_system_statistics();
void clear_screen();

int main() {
    initialize_system();
    
    while (1) {
        clear_screen();
        display_welcome_banner();
        
        int farmer_id = authenticate();
        if (farmer_id == -1) {
            printf("\n❌ Authentication failed! Press Enter to try again...");
            getchar();
            continue;
        }
        
        char choice[10];
        do {
            clear_screen();
            display_farmer_menu(farmer_id);
            printf("\n🔹 Enter your choice: ");
            scanf("%s", choice);
            
            if (strcmp(choice, "1") == 0) {
                deposit(farmer_id);
            } 
            else if (strcmp(choice, "2") == 0) {
                withdraw(farmer_id);
            } 
            else if (strcmp(choice, "3") == 0) {
                check_balance(farmer_id);
            } 
            else if (strcmp(choice, "4") == 0) {
                account_statement(farmer_id);
            }
            else if (strcmp(choice, "5") == 0) {
                transfer_money(farmer_id);
            }
            else if (strcmp(choice, "6") == 0) {
                display_system_statistics();
            }
            else if (strcmp(choice, "7") == 0) {
                printf("\n👋 Logging out... Thank you for using our services!\n");
                printf("Press Enter to continue...");
                getchar();
                getchar();
                break;
            } 
            else {
                printf("\n❌ Invalid option! Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
                getchar();
            }
            
            if (strcmp(choice, "7") != 0) {
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
            }
        } while (1);
    }
    
    free_memory();
    return 0;
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void display_welcome_banner() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                              ║\n");
    printf("║    ███████╗ █████╗  ██████╗ ██████╗ ██████╗     ███████╗██╗   ██╗███████╗  ║\n");
    printf("║    ██╔════╝██╔══██╗██╔════╝██╔════╝██╔═══██╗    ██╔════╝╚██╗ ██╔╝██╔════╝  ║\n");
    printf("║    ███████╗███████║██║     ██║     ██║   ██║    ███████╗ ╚████╔╝ ███████╗  ║\n");
    printf("║    ╚════██║██╔══██║██║     ██║     ██║   ██║    ╚════██║  ╚██╔╝  ╚════██║  ║\n");
    printf("║    ███████║██║  ██║╚██████╗╚██████╗╚██████╔╝    ███████║   ██║   ███████║  ║\n");
    printf("║    ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═════╝     ╚══════╝   ╚═╝   ╚══════╝  ║\n");
    printf("║                                                                              ║\n");
    printf("║                    🌾 RURAL FARMERS MANAGEMENT SYSTEM 🌾                    ║\n");
    printf("║                          Savings & Credit Cooperative                       ║\n");
    printf("║                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void display_farmer_menu(int farmer_id) {
    int index = find_farmer_index(farmer_id);
    if (index == -1) return;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                              ║\n");
    printf("║                          🧑‍🌾 FARMER DASHBOARD 🧑‍🌾                           ║\n");
    printf("║                                                                              ║\n");
    printf("║    Welcome: %-20s                   Balance: $%.2f          ║\n", 
           farmers[index].username, farmers[index].balance);
    printf("║    Farmer ID: %-5d                            Transactions: %-5d        ║\n", 
           farmer_id, farmers[index].transaction_count);
    printf("║                                                                              ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                              ║\n");
    printf("║                              📋 SERVICES MENU 📋                            ║\n");
    printf("║                                                                              ║\n");
    printf("║    [1] 💰 Deposit Money          [2] 💸 Withdraw Money                      ║\n");
    printf("║    [3] 💳 Check Balance          [4] 📄 Account Statement                   ║\n");
    printf("║    [5] 🔄 Transfer Money         [6] 📊 System Statistics                   ║\n");
    printf("║    [7] 🚪 Logout                                                            ║\n");
    printf("║                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}

void initialize_system() {
    // Initialize hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        farmer_hash_table[i] = NULL;
    }
    
    // Dan_Trevor_Matovu dcs/day/2024/ 1539, "Mubwiine_Arnold: dcs/day/2024/ 0246", "Sebirungi_Shafiq:dcs/day/2024/0191g",
    //"Kamogo_David:dcs/day/2024/1006g", "Twesimire_Dorris:dcs/day/2024/0902g"
    char* usernames[] = {"Dan_Trevor_Matovu", "Mubwiine_Arnold", "Sebirungi_Shafiq", "Kamogo_David", "Twesimire_Dorris"};
    int passwords[] = {1539, 0246, 01910, 10060, 09020};
    double balances[] = {5000.00, 7500.50, 3000.25, 6000.75, 9000.00};
    
    for (int i = 0; i < num_farmers; i++) {
        farmers[i].farmer_id = i + 1;
        strcpy(farmers[i].username, usernames[i]);
        farmers[i].password = passwords[i];
        farmers[i].balance = balances[i];
        farmers[i].transactions = NULL;
        farmers[i].transaction_count = 0;
        
        // Insert into hash table
        insert_farmer_hash(farmers[i].farmer_id, i);
        
        // Add initial deposit transaction
        char desc[100];
        sprintf(desc, "Initial deposit - Account opening");
        add_transaction(i+1, balances[i], 'D', desc);
    }
    
    // Initialize transaction stack and queue
    recent_transactions.top = -1;
    transaction_queue.front = 0;
    transaction_queue.rear = -1;
    transaction_queue.size = 0;
}

int hash_function(int farmer_id) {
    return farmer_id % HASH_TABLE_SIZE;
}

void insert_farmer_hash(int farmer_id, int index) {
    int hash_index = hash_function(farmer_id);
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    new_entry->farmer_id = farmer_id;
    new_entry->index = index;
    new_entry->next = farmer_hash_table[hash_index];
    farmer_hash_table[hash_index] = new_entry;
}

int lookup_farmer_hash(int farmer_id) {
    int hash_index = hash_function(farmer_id);
    HashEntry* current = farmer_hash_table[hash_index];
    
    while (current != NULL) {
        if (current->farmer_id == farmer_id) {
            return current->index;
        }
        current = current->next;
    }
    return -1;
}

int find_farmer_index(int farmer_id) {
    return lookup_farmer_hash(farmer_id);
}

int authenticate() {
    char username[50];
    int password;
    
    printf("\n┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                              🔐 USER LOGIN 🔐                              │\n");
    printf("└────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n👤 Enter username (or 'exit' to quit): ");
    scanf("%s", username);
    
    if (strcmp(username, "exit") == 0) {
        printf("\n👋 Thank you for using SACCO Management System!\n");
        free_memory();
        exit(0);
    }
    
    printf("🔑 Enter password: ");
    scanf("%d", &password);
    
    // Use hash table for efficient lookup
    for (int i = 0; i < num_farmers; i++) {
        if (strcmp(username, farmers[i].username) == 0 && password == farmers[i].password) {
            printf("\n✅ Authentication successful! Welcome, %s.\n", username);
            return farmers[i].farmer_id;
        }
    }
    
    return -1;
}

void deposit(int farmer_id) {
    clear_screen();
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              💰 DEPOSIT MONEY 💰                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    double amount;
    char description[100];
    
    printf("\n💵 Enter amount to deposit: $");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("\n❌ Invalid amount! Please enter a positive value.\n");
        return;
    }
    
    printf("📝 Enter description (optional): ");
    getchar(); // consume newline
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0; // remove newline
    
    if (strlen(description) == 0) {
        strcpy(description, "Cash deposit");
    }
    
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    // Update balance
    farmers[index].balance += amount;
    
    // Record transaction
    add_transaction(farmer_id, amount, 'D', description);
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                           ✅ DEPOSIT SUCCESSFUL ✅                          │\n");
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Amount Deposited: $%-15.2f                                       │\n", amount);
    printf("│ New Balance:      $%-15.2f                                       │\n", farmers[index].balance);
    printf("│ Description:      %-45s      │\n", description);
    printf("└────────────────────────────────────────────────────────────────────────────┘\n");
}

void withdraw(int farmer_id) {
    clear_screen();
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             💸 WITHDRAW MONEY 💸                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    double amount;
    char description[100];
    
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    printf("\n💳 Current Balance: $%.2f\n", farmers[index].balance);
    printf("💵 Enter amount to withdraw: $");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("\n❌ Invalid amount! Please enter a positive value.\n");
        return;
    }
    
    // Check balance
    if (amount > farmers[index].balance) {
        printf("\n❌ Insufficient funds!\n");
        printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ Requested Amount: $%-15.2f                                       │\n", amount);
        printf("│ Available Balance: $%-15.2f                                      │\n", farmers[index].balance);
        printf("│ Shortage: $%-15.2f                                               │\n", amount - farmers[index].balance);
        printf("└────────────────────────────────────────────────────────────────────────────┘\n");
        return;
    }
    
    printf("📝 Enter description (optional): ");
    getchar(); // consume newline
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0; // remove newline
    
    if (strlen(description) == 0) {
        strcpy(description, "Cash withdrawal");
    }
    
    // Update balance
    farmers[index].balance -= amount;
    
    // Record transaction
    add_transaction(farmer_id, amount, 'W', description);
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                          ✅ WITHDRAWAL SUCCESSFUL ✅                        │\n");
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Amount Withdrawn: $%-15.2f                                       │\n", amount);
    printf("│ New Balance:      $%-15.2f                                       │\n", farmers[index].balance);
    printf("│ Description:      %-45s      │\n", description);
    printf("└────────────────────────────────────────────────────────────────────────────┘\n");
}

void check_balance(int farmer_id) {
    clear_screen();
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    time_t now = time(NULL);
    char time_str[30];
    strftime(time_str, 30, "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             💳 ACCOUNT BALANCE 💳                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                              ║\n");
    printf("║    Account Holder: %-30s                             ║\n", farmers[index].username);
    printf("║    Farmer ID:      %-5d                                                   ║\n", farmer_id);
    printf("║    Current Balance: $%-15.2f                                       ║\n", farmers[index].balance);
    printf("║    Total Transactions: %-5d                                             ║\n", farmers[index].transaction_count);
    printf("║    Last Updated:   %-30s                             ║\n", time_str);
    printf("║                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}

void transfer_money(int farmer_id) {
    clear_screen();
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             🔄 TRANSFER MONEY 🔄                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    int recipient_id;
    double amount;
    char description[100];
    
    int sender_index = find_farmer_index(farmer_id);
    if (sender_index == -1) {
        printf("\n❌ Error: Sender account not found!\n");
        return;
    }
    
    printf("\n💳 Your Balance: $%.2f\n", farmers[sender_index].balance);
    printf("👤 Enter recipient Farmer ID: ");
    scanf("%d", &recipient_id);
    
    if (recipient_id == farmer_id) {
        printf("\n❌ Cannot transfer to yourself!\n");
        return;
    }
    
    int recipient_index = find_farmer_index(recipient_id);
    if (recipient_index == -1) {
        printf("\n❌ Recipient account not found!\n");
        return;
    }
    
    printf("💵 Enter amount to transfer: $");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("\n❌ Invalid amount! Please enter a positive value.\n");
        return;
    }
    
    if (amount > farmers[sender_index].balance) {
        printf("\n❌ Insufficient funds for transfer!\n");
        return;
    }
    
    printf("📝 Enter description: ");
    getchar();
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;
    
    if (strlen(description) == 0) {
        sprintf(description, "Transfer to %s", farmers[recipient_index].username);
    }
    
    // Process transfer
    farmers[sender_index].balance -= amount;
    farmers[recipient_index].balance += amount;
    
    // Record transactions
    char sender_desc[150], recipient_desc[150];
    sprintf(sender_desc, "Transfer to %s: %s", farmers[recipient_index].username, description);
    sprintf(recipient_desc, "Transfer from %s: %s", farmers[sender_index].username, description);
    
    add_transaction(farmer_id, amount, 'W', sender_desc);
    add_transaction(recipient_id, amount, 'D', recipient_desc);
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                          ✅ TRANSFER SUCCESSFUL ✅                          │\n");
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ From:             %-30s                             │\n", farmers[sender_index].username);
    printf("│ To:               %-30s                             │\n", farmers[recipient_index].username);
    printf("│ Amount:           $%-15.2f                                       │\n", amount);
    printf("│ Your New Balance: $%-15.2f                                       │\n", farmers[sender_index].balance);
    printf("└────────────────────────────────────────────────────────────────────────────┘\n");
}

void account_statement(int farmer_id) {
    clear_screen();
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           📄 ACCOUNT STATEMENT 📄                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    int option;
    printf("\n📋 Statement Options:\n");
    printf("  [1] Last N transactions\n");
    printf("  [2] Transactions between dates\n");
    printf("  [3] All transactions\n");
    printf("\n🔹 Enter your choice: ");
    scanf("%d", &option);
    
    if (option == 1) {
        int n;
        printf("📊 Enter number of recent transactions: ");
        scanf("%d", &n);
        display_recent_transactions(farmer_id, n);
    } 
    else if (option == 2) {
        int start_day, end_day;
        printf("📅 Enter start day offset (e.g., 7 for one week ago): ");
        scanf("%d", &start_day);
        printf("📅 Enter end day offset (e.g., 0 for today): ");
        scanf("%d", &end_day);
        
        time_t now = time(NULL);
        time_t start_date = now - start_day * 24 * 60 * 60;
        time_t end_date = now - end_day * 24 * 60 * 60;
        
        if (start_date > end_date) {
            printf("\n❌ Error: Start date must be before end date.\n");
            return;
        }
        
        display_transactions_by_date(farmer_id, start_date, end_date);
    }
    else if (option == 3) {
        display_recent_transactions(farmer_id, farmers[index].transaction_count);
    }
    else {
        printf("\n❌ Invalid option.\n");
    }
}

void display_system_statistics() {
    clear_screen();
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           📊 SYSTEM STATISTICS 📊                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    double total_balance = 0;
    int total_transactions = 0;
    int total_deposits = 0;
    int total_withdrawals = 0;
    
    for (int i = 0; i < num_farmers; i++) {
        total_balance += farmers[i].balance;
        total_transactions += farmers[i].transaction_count;
        
        // Count transaction types
        TransactionNode* current = farmers[i].transactions;
        while (current != NULL) {
            if (current->data.type == 'D') total_deposits++;
            else total_withdrawals++;
            current = current->next;
        }
    }
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                            SYSTEM OVERVIEW                                 │\n");
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Total Farmers:        %-10d                                        │\n", num_farmers);
    printf("│ Total Balance:        $%-15.2f                                    │\n", total_balance);
    printf("│ Total Transactions:   %-10d                                        │\n", total_transactions);
    printf("│ Total Deposits:       %-10d                                        │\n", total_deposits);
    printf("│ Total Withdrawals:    %-10d                                        │\n", total_withdrawals);
    printf("│ Average Balance:      $%-15.2f                                    │\n", total_balance / num_farmers);
    printf("└────────────────────────────────────────────────────────────────────────────┘\n");
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                           FARMER DETAILS                                  │\n");
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ ID │ Username          │ Balance        │ Transactions                    │\n");
    printf("├────┼───────────────────┼────────────────┼─────────────────────────────────┤\n");
    
    for (int i = 0; i < num_farmers; i++) {
        printf("│ %-2d │ %-17s │ $%-13.2f │ %-10d                      │\n", 
               farmers[i].farmer_id, 
               farmers[i].username, 
               farmers[i].balance, 
               farmers[i].transaction_count);
    }
    
    printf("└────┴───────────────────┴────────────────┴─────────────────────────────────┘\n");
}

void add_transaction(int farmer_id, double amount, char type, const char* description) {
    time_t now = time(NULL);
    
    // Create new transaction
    Transaction t;
    t.farmer_id = farmer_id;
    t.amount = amount;
    t.timestamp = now;
    t.type = type;
    strcpy(t.description, description);
    
    int index = find_farmer_index(farmer_id);
    if (index == -1) return;
    
    // Add to farmer's linked list (insert at head)
    TransactionNode* new_node = (TransactionNode*)malloc(sizeof(TransactionNode));
    new_node->data = t;
    new_node->next = farmers[index].transactions;
    farmers[index].transactions = new_node;
    farmers[index].transaction_count++;
    
    // Push to stack for recent transactions
    push_to_stack(t);
    
    // Enqueue for processing
    enqueue_transaction(t);
}

void display_recent_transactions(int farmer_id, int n) {
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                    RECENT TRANSACTIONS - %s                           │\n", farmers[index].username);
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Date/Time           │ Type     │ Amount      │ Description              │\n");
    printf("├─────────────────────┼──────────┼─────────────┼──────────────────────────┤\n");
    
    TransactionNode* current = farmers[index].transactions;
    int count = 0;
    
    while (current != NULL && count < n) {
        print_transaction(current->data);
        current = current->next;
        count++;
    }
    
    if (count == 0) {
        printf("│                         No transactions found                             │\n");
    }
    
    printf("└─────────────────────┴──────────┴─────────────┴──────────────────────────┘\n");
    printf("\nTotal transactions shown: %d\n", count);
}

void display_transactions_by_date(int farmer_id, time_t start, time_t end) {
    int index = find_farmer_index(farmer_id);
    if (index == -1) {
        printf("\n❌ Error: Farmer account not found!\n");
        return;
    }
    
    char start_str[20], end_str[20];
    strftime(start_str, 20, "%Y-%m-%d", localtime(&start));
    strftime(end_str, 20, "%Y-%m-%d", localtime(&end));
    
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│              TRANSACTIONS FROM %s TO %s                     │\n", start_str, end_str);
    printf("├────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Date/Time           │ Type     │ Amount      │ Description              │\n");
    printf("├─────────────────────┼──────────┼─────────────┼──────────────────────────┤\n");
    
    TransactionNode* current = farmers[index].transactions;
    int count = 0;
    
    while (current != NULL) {
        if (current->data.timestamp >= start && current->data.timestamp <= end) {
            print_transaction(current->data);
            count++;
        }
        current = current->next;
    }
    
    if (count == 0) {
        printf("│                    No transactions found in date range                    │\n");
    }
    
    printf("└─────────────────────┴──────────┴─────────────┴──────────────────────────┘\n");
    printf("\nTotal transactions in range: %d\n", count);
}

void push_to_stack(Transaction t) {
    if (recent_transactions.top >= MAX_TRANSACTIONS - 1) {
        // Stack overflow, shift elements
        for (int i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            recent_transactions.items[i] = recent_transactions.items[i + 1];
        }
        recent_transactions.top--;
    }
    recent_transactions.items[++recent_transactions.top] = t;
}

void enqueue_transaction(Transaction t) {
    if (transaction_queue.size >= MAX_TRANSACTIONS) {
        // Queue is full, dequeue oldest
        dequeue_transaction();
    }
    
    transaction_queue.rear = (transaction_queue.rear + 1) % MAX_TRANSACTIONS;
    transaction_queue.items[transaction_queue.rear] = t;
    transaction_queue.size++;
}

Transaction dequeue_transaction() {
    Transaction t = {0};
    if (transaction_queue.size <= 0) {
        return t; // Empty queue
    }
    
    t = transaction_queue.items[transaction_queue.front];
    transaction_queue.front = (transaction_queue.front + 1) % MAX_TRANSACTIONS;
    transaction_queue.size--;
    return t;
}

void print_transaction(Transaction t) {
    char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M", localtime(&t.timestamp));
    
    char type_str[10];
    if (t.type == 'D') {
        strcpy(type_str, "Deposit");
    } else {
        strcpy(type_str, "Withdraw");
    }
    
    // Truncate description if too long
    char desc[25];
    if (strlen(t.description) > 24) {
        strncpy(desc, t.description, 21);
        desc[21] = '.';
        desc[22] = '.';
        desc[23] = '.';
        desc[24] = '\0';
    } else {
        strcpy(desc, t.description);
    }
    
    printf("│ %-19s │ %-8s │ $%-10.2f │ %-24s │\n", 
           time_str, type_str, t.amount, desc);
}

void print_separator() {
    printf("════════════════════════════════════════════════════════════════════════════════\n");
}

void print_box(const char* text) {
    int len = strlen(text);
    int padding = (76 - len) / 2;
    
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║%*s%s%*s║\n", padding, "", text, 76 - len - padding, "");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}

void free_memory() {
    // Free transaction linked lists for all farmers
    for (int i = 0; i < num_farmers; i++) {
        TransactionNode* current = farmers[i].transactions;
        while (current != NULL) {
            TransactionNode* temp = current;
            current = current->next;
            free(temp);
        }
        farmers[i].transactions = NULL;
    }
    
    // Free hash table entries
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashEntry* current = farmer_hash_table[i];
        while (current != NULL) {
            HashEntry* temp = current;
            current = current->next;
            free(temp);
        }
        farmer_hash_table[i] = NULL;
    }
    
    printf("\n🧹 Memory cleaned up successfully!\n");
}
