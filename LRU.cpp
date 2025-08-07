#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Node{
    public:
    string url;
    Node* next;
    Node* back;

    Node(string url1, Node* next1, Node* back1){
        url=url1;
        next=next1;
        back=back1;
    }

    Node(string url1){
        url=url1;
        next=NULL;
        back=NULL;
    }

};

class LRU{

public:
    int max_sz=4;

    Node* head=nullptr;
    Node* tail=nullptr;
    unordered_map<std::string, Node*> cache;
    //int ca_sz=cache.size();
    void print(){
        for(auto it: cache){
            cout<<it.first<<endl;
        }
        cout<<"head: "<<head->url<<endl;
        cout<<"------"<<endl;
    }

    void movetoHead(Node* node){
        if(node == head) return;

        // detach node
        if(node == tail){
            tail=node->back;
            tail->next=nullptr;
        }
        else{
            node->back->next=node->next;
            node->next->back=node->back;
        }

        node->next=head;
        node->back=nullptr;
        head->back=node;
        head=node;
    }
    
    void put_url(string url1){
        auto it=cache.find(url1);

        //if cache exists in the hashmap, means it just needs to be brought to the head position
        if(it!=cache.end()){
            movetoHead(it->second);
            return;
        }

        //if cache[url] dosent exist int the hashmap, then there are 3 cases:
        //i)either there is no element in the dll at all and this is the 1st element
        //ii)there is space in cache to add new url as head without deleting
        //iii)the cache space is full and the tail url must be deleted
        Node* new_node = new Node(url1);
        cache[url1]=new_node;
        if(head==nullptr){
            head=new_node;
            tail=new_node;
        }
        else{
            new_node->next=head;
            head->back=new_node;
            head=new_node;
        }
        if(cache.size()>max_sz){
            cache.erase(tail->url);
            Node* temp=tail;
            tail=temp->back;
            tail->next=nullptr;
            delete temp;
        }
        print();    
    }


    string get_url(string url1){
        auto it=cache.find(url1);
        if(it==cache.end()) return "error!!!the url dosen't exist ";
        movetoHead(it->second);

        if(head->url==url1) return "yayy!!!";
    }
};

int main(){
std::string u = "google";
std::string u1 = "googl";
std::string u2 = "goog";
std::string u3 = "goo";
std::string u4 = "goog";
std::string u5 = "youtube";
LRU obj1;
obj1.put_url(u);  // Works fine
obj1.put_url(u1);  // Works fine
obj1.put_url(u2);  // Works fine
obj1.put_url(u3);  // Works fine
obj1.put_url(u4);  // Works fine
obj1.put_url(u5);  // Works fine
// cout<<"enter ur url"<<endl;
// cin>>url1;
cout<<"input res: "<<obj1.get_url(u)<<endl;
cout<<"input res: "<<obj1.get_url(u4);


return 0;
}