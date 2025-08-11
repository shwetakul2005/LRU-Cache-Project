    #include <iostream>
    #include <map>
    #include <unordered_map>
    #include <string>
    #include <fstream>
    #include<vector>
    
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
        int max_sz=10;

        Node* head=nullptr;
        Node* tail=nullptr;
        unordered_map<std::string, Node*> cache;
        
        void del_node(Node* node){
            if(!node) return;
            if(node==head && node==tail){
                head=tail=nullptr;
            }
            else if(node==head){
                node->next->back=nullptr;
                head=node->next;
                node->next=nullptr;
            }
            else if(node==tail){
                node->back->next=nullptr;
                tail=node->back;
                node->back=nullptr;
            }
            else{
                Node* temp = node;
                temp=node->back;
                temp->next=node->next;
                node->next->back=temp;
                node->next=nullptr;
                node->back=nullptr;
            }
            delete node;
            node=nullptr;
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
            // print();    
        }


        string get_url(string url1){
            auto it=cache.find(url1);
            if(it==cache.end()) return "error!!!the url dosen't exist ";
            movetoHead(it->second);

            if(head->url==url1) return "yayy!!!";
        }

        void print_reccomendations(vector<string>& store){
        store.clear(); // Clear the old contents of the vector
        Node* current = head;
        int i=1;
        while(current != nullptr){
            store.push_back(current->url);
            cout << i << ". " << current->url << endl;
            i++;
            current = current->next;
        }
    }
    };


    void saveRecent(const LRU& obj, const string& filename) {
        ofstream out(filename, ios::trunc);
        for (Node* cur = obj.head; cur; cur = cur->next) {
            out << cur->url << '\n';
        }
        out.close();
    }


int main(){

    LRU obj1;
    
    ifstream inputFile("recent.txt");
    string line;
    
    vector<string> store;
    if(inputFile.is_open()){
        while(getline(inputFile, line)){
            if(line==""){
                break;
            }
            store.push_back(line);    
        }
        int i=store.size()-1;
        while(i>=0){
            obj1.put_url(store[i]);
            i--;
        }
        inputFile.close();
    }
    else{
        cerr<<"ERROR: Unable to open file!"<<endl;
    }

    obj1.print_reccomendations(store);
    
    cout<<"Enter 'l' to launch or enter 'n' to type a new command or enter 'd' to delete a node: or 'q' to quit: ";
    char c;
    cin>>c;
    string path_open;
    string path_del;

    if(c=='l'){
        cout<<"enter number from the list: ";
        int num;
        cin>>num;
        if(num>0 && num<=store.size()){
            path_open=store[num-1];
            obj1.get_url(path_open);
        }
            #if defined(_WIN32)
            string command = "start \"\" \"" + path_open + "\"";
            #elif defined(__APPLE__)
            string command = "open \"" + path_open + "\"";
            #elif defined(__linux__)
            string command = "xdg-open \"" + path_open + "\"";
            #endif
            system(command.c_str());
        saveRecent(obj1, "recent.txt");
    }
    else if(c=='n'){
        // new command
        cout<<"enter new path below: "<<endl;
        cin>>path_open;
        
        obj1.put_url(path_open);
        obj1.get_url(path_open);
        obj1.print_reccomendations(store);
            #if defined(_WIN32)
            string command = "start \"\" \"" + path_open + "\"";
            #elif defined(__APPLE__)
            string command = "open \"" + path_open + "\"";
            #elif defined(__linux__)
            string command = "xdg-open \"" + path_open + "\"";
            #endif
            system(command.c_str());
        saveRecent(obj1, "recent.txt");  
    }
    else if(c=='d'){
        cout<<"enter number from the list to delete: ";
        int del;
        cin>>del;

        if(del>0 && del<=store.size()){
            path_del=store[del-1];
            obj1.del_node(obj1.cache[path_del]);
            obj1.cache.erase(path_del);
            store.erase(store.begin()+(del-1));    
        }

        obj1.print_reccomendations(store);
        saveRecent(obj1, "recent.txt");
    }

    else{
        cout<<"Error!! enter valid letter: ";
        cin>>c;
    }

return 0;
}
