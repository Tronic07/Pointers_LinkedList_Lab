#include "Inventory.h"
#include <iostream>

// Constructor
Inventory::Inventory() : head(nullptr) {
    // Vector is automatically initialized as empty
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    Node* curr = head;
	while (curr) {
		Node* next = curr->next;
		delete curr->data; // Free the Book object
		delete curr;       // Free the Node itself
		curr = next;
    }
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book* bookPtr) {
    if (!bookPtr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    Node* newNode = new Node(bookPtr);

    // Insert at head if list empty OR title comes before head
    if (!head || bookPtr->getTitle() < head->data->getTitle()) {
        newNode->next = head;
        head = newNode;
        std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
        return;
    }

    // Find insertion point
    Node* curr = head;
    while (curr->next && curr->next->data->getTitle() < bookPtr->getTitle()) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;

    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
}

// Display all books
void Inventory::displayAll() const {
    if (!head) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";

    size_t index = 1;
    Node* curr = head;
    while (curr) {
        std::cout << "Book #" << index++ << ":\n";
        curr->data->displayInfo();
        curr = curr->next;
    }

    std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    if (!head) {
        std::cout << "Book '" << title << "' not found in inventory.\n";
        return;
    }

    // Remove head
    if (head->data->getTitle() == title) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        std::cout << "Removing book: " << title << "\n";
        return;
    }

    // Find node BEFORE the one to delete
    Node* curr = head;
    while (curr->next && curr->next->data->getTitle() != title) {
        curr = curr->next;
    }

    if (curr->next) {
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp->data;
        delete temp;
        std::cout << "Removing book: " << title << "\n";
    }
    else {
        std::cout << "Book '" << title << "' not found in inventory.\n";
    }
}

// Count books
size_t Inventory::getBookCount() const {
    size_t count = 0;
    Node* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

// Find a book by title
Book* Inventory::findBook(const std::string& title) const {
    Node* curr = head;
    while (curr) {
        if (curr->data->getTitle() == title) {
            return curr->data;
        }
        curr = curr->next;
    }
    return nullptr;
}

// Check if empty
bool Inventory::isEmpty() const {
    return head == nullptr;
}