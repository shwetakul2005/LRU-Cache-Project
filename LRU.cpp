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
    unordered_map<std::string, Node*> cache;
    //int ca_sz=cache.size();
    
    void put_url(string url1){

        //if cache exists in the hashmap, means it just needs to be brought to the head position
        if(cache.find(url1) != cache.end()){
            get_url(url1);
        }

        //if cache[url] dosent exist int the hashmap, then there are 3 cases:
        //i)either there is no element in the dll at all and this is the 1st element
        //ii)there is space in cache to add new url as head without deleting
        //iii)the cache space is full and the tail url must be deleted
        else{
            //
            if(cache.size()==0){
                head= new Node(url1);
                cache[url1]=head;
            }

            else if(cache.size()>0 && cache.size()<max_sz){
                Node* new_node=new Node(url1);

                //error#1: You never allocated memory for new_node, so it causes undefined behavior when accessing url.
                //new_node->url=url1;

                cache[url1]=new_node;
                head->back=new_node;
                new_node->back=nullptr;
                new_node->next=head;
                head=new_node;

                //delete new_node;

            }

            else if(cache.size()==max_sz){
                Node* new_node=new Node(url1);
                Node* mover=head;

                //deleting the tail
                while(mover->next){
                    mover=mover->next;
                }
                //removes the tail from the hashmap
                cache.erase(mover->url);

                //removes the tail from the dll
                Node* temp=mover->back;
                temp->next=nullptr;
                mover->back=nullptr;

                //adding new url as head
                //new_node= new Node(url1);
                cache[url1]=new_node;
                head->back=new_node;
                new_node->back=nullptr;
                new_node->next=head;
                head=new_node;

                //  delete new_node;
                  delete mover;
                //  delete temp;
            }
        }

        for(auto it: cache){
            cout<<it.first<<endl;
        }
        cout<<"head: "<<head->url<<endl;
        cout<<"------"<<endl;
    }


    string get_url(string url1){

        if(cache.find(url1) != cache.end()){
            if(cache[url1]!=head){
                Node* mover=cache[url1];
                Node* temp1=mover->back;
                Node* temp2=mover->next;
                head->back=mover;
                mover->back=nullptr;
                mover->next=head;
                head=mover;
                temp1->next=temp2;
                if(temp2) temp2->back=temp1;
                return "yayyy!!";

                  delete mover;
                //  delete temp1;
                //  delete temp2;

            }
            else if(cache[url1]==head){
                return "already_head";
            }
        }

        return "error!!";
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
cout<<obj1.get_url(u);


return 0;
}