#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

class Node {
public:
    string url;
    Node* next;
    Node* prev;

    Node(string url1, Node* next1, Node* prev1) {
        url = url1;
        next = next1;
        prev = prev1;
    }

    Node(string url1) {
        url = url1;
        next = nullptr;
        prev = nullptr;
    }
};

class LRU {
public:
    int max_sz = 4;
    Node* head = nullptr;
    Node* tail = nullptr;
    unordered_map<string, Node*> cache;

    void insert_url(string url1) {
        // If cache exists in the hashmap, move it to the head position
        if (cache.find(url1) != cache.end()) {
            cout << "URL " << url1 << " is already in cache, moving it to front."<<endl;
            Node* node1 = cache[url1];
            move_to_front(node1);
        }
        // If cache[url] doesn't exist in the hashmap, handle 3 cases:
        else {
            cout << "Inserting new URL: " << url1 << endl;
            if (cache.size() == 0) {
                head = new Node(url1);
                tail = head;
                cache[url1] = head;
            } 
            else if (cache.size() < max_sz) {
                Node* new_node = new Node(url1);
                cache[url1] = new_node;
                head->prev = new_node;
                new_node->prev = nullptr;
                new_node->next = head;
                head = new_node;
            } 
            else if (cache.size() == max_sz) {
                Node* new_node = new Node(url1);
                cache.erase(tail->url);

                // Remove the tail from the doubly linked list
                Node* temp = tail;
                tail = tail->prev;
                temp->prev = nullptr;
                if (tail) tail->next = nullptr;

                // Add new URL as head
                cache[url1] = new_node;
                head->prev = new_node;
                new_node->prev = nullptr;
                new_node->next = head;
                head = new_node;

                delete temp;
            }
        }

        print_cache();

    }

    void move_to_front(Node* node) {
        if (node->url == head->url) return; // Already at the front

        // If the node is the tail, update tail
        if (node->url == tail->url) {
            tail = tail->prev;
            tail->next = nullptr;
        } 
        else {
            Node* mover = node;
            Node* temp1 = mover->prev;
            Node* temp2 = mover->next;

            temp1->next = temp2;
            temp2->prev = temp1;
        }

        // Move node to head
        node->next = head;
        node->prev = nullptr;
        if(head) head->prev = node;
        head = node;
    }

    string access_url(string url1) {
        if (cache.find(url1) != cache.end()) {
            cout << "Accessing URL: " << url1 << " (moved to front)" << endl;
            if (cache[url1] != head) {
                Node* mover = cache[url1];
                Node* temp1 = mover->prev;
                Node* temp2 = mover->next;
                head->prev = mover;
                mover->prev = nullptr;
                mover->next = head;
                head = mover;
                temp1->next = temp2;
                if (temp2) temp2->prev = temp1;
                tail = tail->prev;
                print_cache();
                return "Access successful";
            } 
            else if (cache[url1] == head) {
                return "Access successful";
            }
        }

        cout << "Error! URL " << url1 << " not found in cache." << endl;
    return "Error!";
    }

    void print_cache() {
        Node* temp = head;
        cout << "Cache state (Most Recent to Least Recent): ";
        while (temp) {
            cout << temp->url << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~LRU() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void handleUserInput(LRU &cache) {
        int num;
        cout << "How many URLs do you want to insert? ";
        cin >> num;
    
        for (int i = 0; i < num; i++) {
            string url;
            int choice;
            cout << "\nEnter URL: ";
            cin >> url;
            cout << "Choose an option:\n";
            cout << "1 - Access URL\n";
            cout << "2 - Insert URL\n";
            cout << "Enter your choice: ";
            cin >> choice;
    
            if (choice == 1) {
                cout << "Result: " << cache.access_url(url) << "\n";
            } else if (choice == 2) {
                cache.insert_url(url);
            } else {
                cout << "Invalid choice! Please enter 1 or 2.\n";
            }
        }
    }
};

int main() {
    LRU cache;
    cache.handleUserInput(cache);
    return 0;
}
