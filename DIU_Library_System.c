#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define Books_FILE "Books.txt"
#define Borrow_FILE "Borrow_Records.txt"
#define Max_Books 10
#define Max_Stack 100
#define Max_Queue 5

// Predefined Book Codes:
// 222 - Chemistry
// 223 - Biology  
// 224 - Physics
// 225 - Mathematics
// 226 - Computer Science

typedef struct {
    int id;
    char name[50];
    char author[50];
    char genre[30];
    char date[15];
} Book;

typedef struct {
    int book_id;
    char operation[20];
    char date[15];
} Transaction;

typedef struct {
    int book_id;
    char user_name[20];
    char request_date[15];
} Reservation;

struct Node {
    int book_id;
    char user_name[20];
    char borrow_date[15];
    char return_date[15];
    int days;
    struct Node *next;
};

Book books[Max_Books];
Transaction stack[Max_Stack];
Reservation queue[Max_Queue];
int book_count = 0, stack_top = -1, queue_front = 0, queue_rear = -1, queue_size = 0;
struct Node *head = NULL;
int logged_in = 0;
int user_logged = 0;
char current_user[20];

int isBooksFull() { return book_count >= Max_Books; }
int isStackFull() { return stack_top >= Max_Stack - 1; }
int isQueueFull() { return queue_size >= Max_Queue; }

void clear_screen() {
    system("cls");
}

void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void get_return_date(char *return_date) {
    time_t t = time(NULL);
    t += (14 * 24 * 60 * 60); // Add 14 days
    struct tm tm = *localtime(&t);
    sprintf(return_date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void push_transaction(int book_id, char *operation, char *date) {
    if (!isStackFull()) {
        stack[++stack_top].book_id = book_id;
        strcpy(stack[stack_top].operation, operation);
        strcpy(stack[stack_top].date, date);
    }
}

void enqueue_reservation(int book_id, char *user_name, char *date) {
    if (!isQueueFull()) {
        queue[queue_rear = (queue_rear + 1) % Max_Queue].book_id = book_id;
        strcpy(queue[queue_rear].user_name, user_name);
        strcpy(queue[queue_rear].request_date, date);
        queue_size++;
    }
}

int admin_login() {
    char username[20], password[20];
    printf("Username: "); scanf("%s", username);
    printf("Password: "); scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        logged_in = 1;
        printf("Login successful\n");
        return 1;
    }
    printf("Invalid credentials\n");
    return 0;
}

int user_login() {
    // Valid Student IDs: 242-35-407, 242-35-408, 242-35-409, 242-35-410
    // Password: 123
    char user_id[20], password[10];
    printf("Student ID: "); scanf("%s", user_id);
    printf("Password: "); scanf("%s", password);
    
    if ((strcmp(user_id, "242-35-407") == 0 || 
         strcmp(user_id, "242-35-408") == 0 || 
         strcmp(user_id, "242-35-409") == 0 || 
         strcmp(user_id, "242-35-410") == 0) && 
        strcmp(password, "123") == 0) {
        user_logged = 1;
        strcpy(current_user, user_id);
        printf("Student login successful! Welcome %s\n", user_id);
        return 1;
    }
    printf("Invalid student credentials\n");
    return 0;
}

void load_books() {
    FILE *file = fopen(Books_FILE, "r");
    if (!file) return;
    book_count = 0;
    while (fscanf(file, "%d %s %s %s %s", &books[book_count].id, books[book_count].name, books[book_count].author, books[book_count].genre, books[book_count].date) == 5 && book_count < Max_Books) book_count++;
    fclose(file);
}

void save_books() {
    FILE *file = fopen(Books_FILE, "w");
    if (!file) return;
    for (int i = 0; i < book_count; i++) fprintf(file, "%d %s %s %s %s\n", books[i].id, books[i].name, books[i].author, books[i].genre, books[i].date);
    fclose(file);
}

void add_book() {
    if (!logged_in) { printf("Access denied\n"); return; }
    if (isBooksFull()) { printf("Inventory full\n"); return; }
    printf("Book ID: "); scanf("%d", &books[book_count].id);
    printf("Name: "); scanf("%s", books[book_count].name);
    printf("Author: "); scanf("%s", books[book_count].author);
    printf("Genre: "); scanf("%s", books[book_count].genre);
    printf("Date: "); scanf("%s", books[book_count].date);
    book_count++; save_books();
    push_transaction(books[book_count-1].id, "ADD", books[book_count-1].date);
    printf("Book added\n");
}

void delete_book() {
    if (!logged_in) { printf("Access denied\n"); return; }
    int id;
    printf("Book ID to delete: "); scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            push_transaction(id, "DELETE", books[i].date);
            for (int j = i; j < book_count - 1; j++) books[j] = books[j + 1];
            book_count--; save_books(); printf("Book deleted\n"); return;
        }
    }
    printf("Book not found\n");
}

void update_book() {
    if (!logged_in) { printf("Access denied\n"); return; }
    int id;
    printf("Book ID to update: "); scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            printf("New Name: "); scanf("%s", books[i].name);
            printf("New Author: "); scanf("%s", books[i].author);
            printf("New Genre: "); scanf("%s", books[i].genre);
            save_books(); push_transaction(id, "UPDATE", books[i].date);
            printf("Book updated\n"); return;
        }
    }
    printf("Book not found\n");
}

void display_inventory() {
    if (!logged_in) { printf("Access denied\n"); return; }
    printf("INVENTORY:\n");
    for (int i = 0; i < book_count; i++) printf("ID: %d, Name: %s, Author: %s, Genre: %s\n", books[i].id, books[i].name, books[i].author, books[i].genre);
}

void search_book() {
    int choice, id, found = 0;
    char search[50];
    printf("Search by: 1.ID 2.Author 3.Genre: "); scanf("%d", &choice);
    if (choice == 1) {
        printf("Book ID: "); scanf("%d", &id);
        for (int i = 0; i < book_count; i++) {
            if (books[i].id == id) {
                printf("Found: ID: %d, Name: %s, Author: %s, Genre: %s\n", books[i].id, books[i].name, books[i].author, books[i].genre);
                found = 1;
            }
        }
    } else if (choice == 2) {
        printf("Author: "); scanf("%s", search);
        for (int i = 0; i < book_count; i++) {
            if (strcmp(books[i].author, search) == 0) {
                printf("Found: ID: %d, Name: %s, Author: %s, Genre: %s\n", books[i].id, books[i].name, books[i].author, books[i].genre);
                found = 1;
            }
        }
    } else if (choice == 3) {
        printf("Genre: "); scanf("%s", search);
        for (int i = 0; i < book_count; i++) {
            if (strcmp(books[i].genre, search) == 0) {
                printf("Found: ID: %d, Name: %s, Author: %s, Genre: %s\n", books[i].id, books[i].name, books[i].author, books[i].genre);
                found = 1;
            }
        }
    }
    if (!found) printf("No books found\n");
}

void search_predefined_books() {
    printf("\nAVAILABLE BOOKS:\n");
    printf("222 - Chemistry\n");
    printf("223 - Biology\n");
    printf("224 - Physics\n");
    printf("225 - Mathematics\n");
    printf("226 - Computer Science\n");
}

void load_borrow_records() {
    FILE *file = fopen(Borrow_FILE, "r");
    if (!file) return;
    struct Node *temp;
    int book_id, days;
    char user_name[20], borrow_date[15], return_date[15];
    while (fscanf(file, "%d %s %s %s %d", &book_id, user_name, borrow_date, return_date, &days) == 5) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->book_id = book_id; strcpy(temp->user_name, user_name); strcpy(temp->borrow_date, borrow_date);
        strcpy(temp->return_date, return_date); temp->days = days; temp->next = head; head = temp;
    }
    fclose(file);
}

void save_borrow_records() {
    FILE *file = fopen(Borrow_FILE, "w");
    if (!file) return;
    struct Node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%d %s %s %s %d\n", temp->book_id, temp->user_name, temp->borrow_date, temp->return_date, temp->days);
        temp = temp->next;
    }
    fclose(file);
}

void borrow_book() {
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    char borrow_date[15], return_date[15];
    
    search_predefined_books();
    printf("Enter Book Code to borrow: "); 
    scanf("%d", &newnode->book_id);
    clear_screen();
    
    // Validate book code
    if (newnode->book_id < 222 || newnode->book_id > 226) {
        printf("Invalid book code! Please select from 222-226\n");
        free(newnode);
        return;
    }
    
    strcpy(newnode->user_name, current_user);
    get_current_date(borrow_date);
    get_return_date(return_date);
    strcpy(newnode->borrow_date, borrow_date);
    strcpy(newnode->return_date, return_date);
    newnode->days = 14;
    
    newnode->next = head; 
    head = newnode; 
    save_borrow_records();
    
    printf("\nBook borrowed successfully!\n");
    printf("Book Code: %d\n", newnode->book_id);
    printf("Student: %s\n", current_user);
    printf("Borrow Date: %s\n", borrow_date);
    printf("Return Date: %s (14 days from today)\n", return_date);
}

void return_book() {
    int book_code;
    search_predefined_books();
    printf("Enter Book Code to return: ");
    scanf("%d", &book_code);
    clear_screen();
    
    struct Node *temp = head;
    struct Node *prev = NULL;
    
    while (temp != NULL) {
        if (temp->book_id == book_code && strcmp(temp->user_name, current_user) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            printf("Book %d returned successfully by %s\n", book_code, current_user);
            free(temp);
            save_borrow_records();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("No record found for this book or it's not borrowed by you\n");
}

void view_return_dates() {
    if (!logged_in) { printf("Access denied\n"); return; }
    struct Node *temp = head;
    printf("RETURN DATES:\n");
    while (temp != NULL) {
        printf("Book ID: %d, User: %s, Return: %s, Days: %d\n", temp->book_id, temp->user_name, temp->return_date, temp->days);
        temp = temp->next;
    }
}

void track_history() {
    if (!logged_in) { printf("Access denied\n"); return; }
    char filter_date[15];
    printf("Date filter (or 'all'): "); scanf("%s", filter_date);
    struct Node *temp = head;
    printf("HISTORY:\n");
    while (temp != NULL) {
        if (strcmp(filter_date, "all") == 0 || strcmp(temp->borrow_date, filter_date) == 0)
            printf("Book ID: %d, User: %s, Borrow: %s, Return: %s\n", temp->book_id, temp->user_name, temp->borrow_date, temp->return_date);
        temp = temp->next;
    }
}

void view_transactions() {
    if (!logged_in) { printf("Access denied\n"); return; }
    printf("TRANSACTION HISTORY:\n");
    for (int i = stack_top; i >= 0; i--)
        printf("Book ID: %d, Operation: %s, Date: %s\n", stack[i].book_id, stack[i].operation, stack[i].date);
}

void view_reservations() {
    if (!logged_in) { printf("Access denied\n"); return; }
    printf("RESERVATION QUEUE:\n");
    for (int i = 0; i < queue_size; i++) {
        int index = (queue_front + i) % Max_Queue;
        printf("Book ID: %d, User: %s, Request Date: %s\n", queue[index].book_id, queue[index].user_name, queue[index].request_date);
    }
}

void make_reservation() {
    int book_id;
    char user_name[20], date[15];
    printf("Book ID for reservation: "); scanf("%d", &book_id);
    printf("Your name: "); scanf("%s", user_name);
    printf("Request date: "); scanf("%s", date);
    enqueue_reservation(book_id, user_name, date);
    printf("Reservation added\n");
}

void admin_panel() {
    int choice;
    do {
        printf("ADMIN PANEL:\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Inventory\n5. View Reservation History\n0. Logout\nChoice: ");
        scanf("%d", &choice);
        clear_screen();
        switch (choice) {
            case 1: add_book(); break; case 2: delete_book(); break; case 3: update_book(); break; case 4: display_inventory(); break;
            case 5: view_reservations(); break;
            case 0: logged_in = 0; printf("Logged out\n"); break;
        }
    } while (choice != 0 && logged_in);
}

void student_panel() {
    int choice;
    do {
        printf("STUDENT PANEL:\n1. Search Books\n2. Borrow Book\n3. Make Reservation\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: search_book(); break; case 2: borrow_book(); break; case 3: make_reservation(); break; case 0: printf("Exiting\n"); break;
        }
    } while (choice != 0);
}

void user_panel() {
    int choice;
    do {
        printf("\nSTUDENT PANEL - %s:\n", current_user);
        printf("1. Borrow Books\n");
        printf("2. Return Books\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clear_screen();
        
        switch (choice) {
            case 1: borrow_book(); break;
            case 2: return_book(); break;
            case 0: 
                user_logged = 0; 
                printf("Student logged out\n"); 
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 0 && user_logged);
}

int main() {
    int choice;
    load_books(); load_borrow_records();
    do {
        printf("DIU LIBRARY SYSTEM:\n1. Admin/Librarian Login\n2. Student Access\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        clear_screen();
        switch (choice) {
            case 1: if (admin_login()) admin_panel(); break; 
            case 2: if (user_login()) user_panel(); break;
            case 0: printf("Exiting system\n"); break;
        }
    } while (choice != 0);
    return 0;
}
