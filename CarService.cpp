#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

class ServiceType{
    public:
    string serviceTypeID;
    string serviceName;
    string serviceDuration;
    string serviceCost;

    ServiceType(string id="", string name="", string duration="", string cost=""){
        serviceTypeID=id;
        serviceName=name;
        serviceDuration=duration;
        serviceCost=cost;
    }

    void printServiceTypeInfo(){
        cout << "Service Type ID: " << serviceTypeID << endl;
        cout << "Service Name: " << serviceName << endl;
        cout << "Service Duration: " << serviceDuration << endl;
        cout << "Service Cost: " << serviceCost << endl;
    }
};

class ServiceHistory {
public:
    ServiceType serviceType;
    string date;

    ServiceHistory(ServiceType st=ServiceType(), string d="") {
        serviceType = st;
        date = d;
    }

    void printServiceHistory() {
        serviceType.printServiceTypeInfo();
        cout << "Service Date: " << date << endl << endl;
    }
};

class Customer{
   public:
   string customerID;
   string name;
   string contactNumber;
   string licensePlate;
   ServiceHistory history[50];
   int currentIndex;

    Customer(string id="",string n="",string contact="", string plate=""){
        customerID=id;
        name= n;
        contactNumber=contact;
        licensePlate=plate;
        for (int i = 0; i < 50; i++) {
            history[i] = ServiceHistory();
        }
        currentIndex = 0;
    }

    void printCustomerInfo(){
        cout << "Customer Information" << endl;
        cout << "Customer ID: " << customerID << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Contact Number: " << contactNumber << endl;
        cout << "License Plate: " << licensePlate << endl;
    }

     void addServiceRecord(ServiceType st, string d) {
        history[currentIndex]= ServiceHistory(st, d);
        currentIndex++;
    }

    void printHistoryList() {
            int i=0;
            while(history[i].date != ""){
                history[i].printServiceHistory();
                i++;
            }
        }
    
};

class Node{
    public:
    Customer car;
    ServiceType service;
    Node * next;

    Node(Customer c, ServiceType s){
        car=c;
        service=s;
        next=NULL;
    }

    Node(Customer c){
        car=c;
        next=NULL;
    }
};

class CustomerLL{
    public:
    Node * head;
    Node * current;
    int index;

    CustomerLL(){
        head=nullptr;
        current=nullptr;
        index=0;
    }

    void push(Customer c){
        Node * newNode = new Node(c);
        if(head==NULL){
            head=current=newNode;
            index++;
            return;
        }
        else{
            current=head;
            while(current->next!=nullptr){
                current=current->next;
            }
            current->next=newNode;
            current=newNode;
            index++;
        }
    }

    string getNextID(){
        return "C00"+to_string(index+1);
    }

    bool check(string id){
        current=head;
        while(current!=nullptr){
            if(current->car.customerID==id){
                return true; 
            }
            else{
                current=current->next;
            }
        }
        return false;
    }

    Customer accessCustomer(string id){
        current=head;
        while(current!=nullptr){
            if(current->car.customerID==id){
                return current->car;
            }
            else{
                current=current->next;
            }
        }
        return Customer();
    }
};

class ServiceQueue{
    public:
    Node *backPtr, *frontPtr;
    
    ServiceQueue(){
        backPtr=NULL;
        frontPtr=NULL;
    }

    void destroyQue(){
        Node * temp= frontPtr;
        while(temp){
            frontPtr = temp->next;
            delete temp;
            temp=frontPtr;
        }
    }

    bool isEmpty(){
        return (backPtr==NULL && frontPtr==NULL);
    }

    void enque(Customer c, ServiceType s){
        Node * newNode = new Node(c,s);
        newNode->car=c;
        newNode->next=NULL;

        if(isEmpty()){
            frontPtr=newNode;
        }else{
            backPtr->next=newNode;
        }
        backPtr=newNode;
    }

    void deque(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
        }else{
            Node * temp=frontPtr;
            frontPtr=frontPtr->next;
            delete temp;
        }
    }

    bool stillQue(Customer c){
        Node *current=frontPtr;
        while(current!=NULL){
            if(current->car.customerID==c.customerID){
                return true;
            }
            current=current->next;
        }
        return false;
    }

    int queLength(Customer c){
        int count=0;
        Node * current=frontPtr;
        while(current->car.customerID != c.customerID){
            count++;
            current=current->next;
        }
        return count;
    }

    void printQue(){
        Node * current=frontPtr;
        while(current!=NULL){
            current->car.printCustomerInfo();
            cout << endl;
            current=current->next;
        }
    }
};

class ServiceTechnician{
    public:
    string technicianId;
    string name;
    string expertise;

    ServiceTechnician(string id="", string n="", string exp=""){
        technicianId=id;
        name=n;
        expertise=exp;
    }

    void printTechnicianInfo(){
        cout << "Technician Information" << endl;
        cout << "Technician ID: " << technicianId << endl;
        cout << "Technician Name: " << name << endl;
        cout << "Expertise: " << expertise << endl;
    }
};

class ServiceBay{
    public:
    string bayID;
    ServiceTechnician * technician;
    Customer *car;

    ServiceBay(string id=""){
        bayID=id;
        technician=NULL;
        car=NULL;
    }

    bool isBayAvailable(){
        return (technician!=NULL && car!=NULL);
    }

    void assignTechnician(ServiceTechnician *tech){
        technician=tech;
    }

    void assignCar(Customer *c){
        car=c;
    }

    void printServiceBayInfo(){
        cout << "Bay ID: " << bayID << endl;
        if(technician!=NULL){
            technician->printTechnicianInfo();
        }
        else{
            cout << "Technician Not Assigned" << endl;
        }
        if(car!=NULL){
            car->printCustomerInfo();
        }
        else{
            cout << "Car Not Assigned" << endl;
        }
        cout << endl << endl;
    }
};

void mainMenu(CustomerLL &, ServiceType[], ServiceQueue &, ServiceBay[], ServiceTechnician[]);
void existCustomerMenu(CustomerLL &, ServiceType[], ServiceQueue &, ServiceBay[], ServiceTechnician[]);
void newCustomerMenu(CustomerLL &, ServiceType[], ServiceQueue &, ServiceBay[], ServiceTechnician[]);
void technicianMenu(CustomerLL &, ServiceType[], ServiceQueue &, ServiceBay[], ServiceTechnician[]);

ServiceTechnician& findTechnician(ServiceTechnician technician[], string id){
    for(int i=0;i<5;i++){
        if(technician[i].technicianId==id){
            return technician[i];
        }
    }
    throw runtime_error("Technician Not Found");
}

void questionAfterFunctionforTechnicianManu(CustomerLL & list, ServiceType service[], ServiceQueue & q, ServiceBay bay[], ServiceTechnician technician[]){
    int choice =0;
        cout << endl << endl;
        cout << "1. Back to Technician Menu" << endl;
        cout << "2. Exit System" << endl;
        cout << "\nPlese Enter Your Choice: ";
        cin >> choice;
    do{
        if(choice == 1)
            technicianMenu(list, service, q, bay, technician);
        else if (choice == 2){
            cout << "Thank You For Using Car Service System" << endl;
            system("pause");
            exit(0);
        }
        else
            cout << "Invalid Choice" << endl;

    }while(choice != 1 || choice != 2);
}

void questionAfterFunctionforCustomerManu(CustomerLL & list, ServiceType service[], ServiceQueue & q, ServiceBay bay[], ServiceTechnician technician[]){
    int choice =0;
        cout << endl << endl;
        cout << "1. Back to Customer Menu" << endl;
        cout << "2. Exit System" << endl;
        cout << "\nPlese Enter Your Choice: ";
        cin >> choice;
    do{
        if(choice == 1)
            existCustomerMenu(list, service, q, bay, technician);
        else if (choice == 2){
            cout << "Thank You For Using Car Service System" << endl;
            system("pause");
            exit(0);
        }
        else
            cout << "Invalid Choice" << endl;

    }while(choice != 1 || choice != 2);
}

void newCustomerMenu(CustomerLL &list,ServiceType service[], ServiceQueue &q, ServiceBay bay[], ServiceTechnician technician[]){
    int choice=0;
    string id, name, contact, plate;

    do{
        system("cls");
        cout << "=============================================" << endl;
        cout << setw(25) << "Customer Menu" << endl;
        cout << "=============================================" << endl;
        cout << "1. Register Customer Information" << endl;
        cout << "2. Back to Main Menu" << endl;
        cout << "3. Exit System" << endl;
        cout << "\nPlese Enter Your Choice: ";
        cin >> choice;

        switch(choice){
            case 1:{   
                // Register Information
                system("cls");
                cout << "\n\n=============================================" << endl;
                cout  << "              Register Car Service          " << endl;
                cout << "=============================================" << endl;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Contact Number: ";
                cin >> contact;
                cout << "Enter License Plate: ";
                cin >> plate;
                Customer c1(list.getNextID(),name,contact,plate);
                list.push(c1);
                cout << "\nCustomer Information Registered Successfully" << endl;
                c1.printCustomerInfo();
                do{
                    cout << endl;
                    cout << "1. Register Car Service" << endl;
                    cout << "2. Exit System" << endl;
                    cout << "\nPlese Enter Your Choice: ";
                    cin >> choice;
                    if (choice == 1)
                        existCustomerMenu(list, service, q, bay, technician);

                    else if (choice == 2)
                        exit(0);
                    else
                        cout << "Please Enter Valid Choice" << endl;
                }while(choice != 1 || choice != 2);
                break;
            }

            case 2:{
                // Back to Main Menu
                cout << "\nRedireccting back to Main Menu" << endl;
                std::this_thread::sleep_for(2s);
                mainMenu(list, service, q, bay, technician);
            }
                break;
            case 3:
                // Exit System
                cout << "Thank You For Using Car Service System" << endl;
                system("pause");
                exit(0);
            default:
                cout << "Invalid Choice" << endl<< endl;
        }
    }while(choice!=1 || choice!=2 || choice!=3); 
}

void existCustomerMenu(CustomerLL &list, ServiceType service[], ServiceQueue &q, ServiceBay bay[], ServiceTechnician technician[]){
    int choice=0,serviceID=0;
    string customerID, date;
    system("cls");
    cout << "Please Enter CustomerID: ";
    cin >> customerID;
    if(list.check(customerID)){
        Customer c=list.accessCustomer(customerID);
        cout << "=============================================" << endl;
        cout << setw(25) << "Customer Menu" << endl;
        cout << "=============================================" << endl;
        cout << "1. Register Car Service" << endl;
        cout << "2. View Service Status" << endl;
        cout << "3. Car Service History" << endl;
        cout << "4. View Register Information" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "6. Exit System" << endl;
        cout << "\nPlese Enter Your Choice: ";
        cin >> choice;

        switch(choice){
            case 1:{   
                // Register Car Service Information
                for(int i=0;i<10;i++){
                    if(service[i].serviceTypeID!=""){
                        cout << i+1 << ". " << service[i].serviceName << endl;
                    }
                }
                cout << "\nEnter Service Type ID: ";
                cin >> serviceID;
                cout << "Enter Service Date: ";
                cin >> date;
                c.addServiceRecord(service[serviceID-1],date);
                if (bay[0].isBayAvailable()){
                    bay[0].assignCar(&c);
                    bay[0].printServiceBayInfo();
                }
                else if (bay[1].isBayAvailable()){
                    bay[1].assignCar(&c);
                    bay[1].printServiceBayInfo();
                }
                else if (bay[2].isBayAvailable()){
                    bay[2].assignCar(&c);
                    bay[2].printServiceBayInfo();
                }
                else
                    q.enque(c,service[serviceID-1]);
               
                cout << "Service Registered Successfully" << endl;
                std::this_thread::sleep_for(3s);
                questionAfterFunctionforCustomerManu(list, service, q, bay, technician);
                break;
            }

            case 2:{
                // View Service Status
                if(q.stillQue(c)){
                    cout << "Your Car is in Queue" << endl;
                    cout << "Your Position in Queue: " << q.queLength(c) << endl;
                }
                else if(bay[0].car->customerID==c.customerID){
                    cout << "Your Car is in Service Bay 1" << endl;
                    cout << "Service by: " << endl;
                    bay[0].technician->printTechnicianInfo();
                }
                else if(bay[1].car->customerID==c.customerID){
                    cout << "Your Car is in Service Bay 2" << endl;
                    cout << "Service by: " << endl;
                    bay[1].technician->printTechnicianInfo();
                }
                else if(bay[2].car->customerID==c.customerID){
                    cout << "Your Car is in Service Bay 3" << endl;
                    cout << "Service by: " << endl;
                    bay[2].technician->printTechnicianInfo();
                }
                else{
                    cout << "Your Car is not in Queue or Service Bay" << endl;
                }
                questionAfterFunctionforCustomerManu(list, service, q, bay, technician);
                break;
            }

            case 3:{
                system("cls");
                if(c.history[0].date != ""){
                    c.printHistoryList();
                }
                else{
                    cout << "No Service History Found" << endl;
                }
                questionAfterFunctionforCustomerManu(list, service, q, bay, technician);
                break;
            }

            case 4:{
                system("cls");
                c.printCustomerInfo();
                break;
            }

            case 5:{
                cout << "\nRedireccting back to Main Menu" << endl;
                std::this_thread::sleep_for(2s);
                mainMenu(list, service, q, bay, technician);
                break;
            }
            
            case 6:{
                cout << "Thank You For Using Car Service System" << endl;
                system("pause");
                exit(0);
                break;
            }
            default:
                cout << "Invalid Choice" << endl;
        }
    }
    else{
        cout << "Customer Not Found" << endl;
        cout << "Please Register at New Customer Menu" << endl;
        std::this_thread::sleep_for(3s);
        newCustomerMenu(list, service, q, bay, technician);
    }
}

void technicianMenu(CustomerLL &list, ServiceType service[], ServiceQueue &q, ServiceBay bay[], ServiceTechnician technician[]){
    int choice=0;
    string id, name, expertise;
        system("cls");
        cout << "=============================================" << endl;
        cout << "              Technician Menu                " << endl;
        cout << "=============================================" << endl;
        cout << "1. Assign Technician to Service Bay" << endl;
        cout << "2. Technician List" << endl;
        cout << "3. Updated Technician Information" << endl;
        cout << "4. View Queue Information" << endl;
        cout << "5. Update Service Bay Status" << endl;
        cout << "6. Customer List" << endl;
        cout << "7. Back to Main Menu" << endl;
        cout << "8. Exit System" << endl;
        cout << "\nPlese Enter Your Choice: ";
        cin >> choice;

        switch(choice){
            case 1:{   // View Service Bay Information
                system("cls");
                cout << "=====================================================" << endl;
                cout << "        Assign Technician to Service Bay             " << endl;
                cout << "=====================================================" << endl;
                cout << "Service Bay 1" << endl;
                bay[0].printServiceBayInfo();
                cout << "Service Bay 2" << endl;
                bay[1].printServiceBayInfo();
                cout << "Service Bay 3" << endl;
                bay[2].printServiceBayInfo();
                system("pause");
                int i=0;;
                try{
                    if (bay[0].technician==NULL){
                        cout << "Bay 1 don't have Technician" << endl;
                        cout << "Enter Technician ID: ";
                        cin >> id;
                        bay[0].assignTechnician(&findTechnician(technician,id));
                    }
                    else{
                        cout << "Bay 1 already have Technician" << endl;
                    }
                    if(bay[1].technician==NULL){
                        cout << "Bay 2 don't have Technician" << endl;
                        cout << "Enter Technician ID: ";
                        cin >> id;
                        bay[1].assignTechnician(&findTechnician(technician,id));
                    }
                    else{
                        cout << "Bay 2 already have Technician" << endl;
                    }
                    if (bay[2].technician==NULL){
                        cout << "Bay 3 don't have Technician" << endl;
                        cout << "Enter Technician ID: ";
                        cin >> id;
                        bay[2].assignTechnician(&findTechnician(technician,id));
                    }
                    else{
                        cout << "Bay 3 already have Technician" << endl;
                    }
                }
                catch(const runtime_error& e) {
                    cout << e.what() << endl;
                }

                questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                break;
            }

            case 2:{
                // Technician List
                system("cls");
                cout << "=====================================================" << endl;
                cout << "                   Technician List                    " << endl;
                cout << "=====================================================" << endl;
                technician[0].printTechnicianInfo();
                cout << endl;
                technician[1].printTechnicianInfo();
                cout << endl;
                technician[2].printTechnicianInfo();

                questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                break;
            }

            case 3:{
                // Updated Technician Information
                system("cls");
                cout << "=====================================================" << endl;
                cout << "              Updated Technician Information         " << endl;
                cout << "=====================================================" << endl;
                cout << "Enter Technician ID you like to update: ";
                cin >> id;
                try{
                    ServiceTechnician &t=findTechnician(technician,id);
                    cout << "Enter Technician Name: ";
                    cin >> name;
                    cout << "Enter Technician Expertise: ";
                    cin >> expertise;
                    t.name=name;
                    t.expertise=expertise;
                    cout << "Technician Information Updated Successfully" << endl;
                    t.printTechnicianInfo();
                }
                catch(const runtime_error& e) {
                    cout << e.what() << endl;
                }

                questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                break;
            }

            case 4:{
                // Assign Customer to Bay
                    system("cls");
                    cout << "=====================================================" << endl;
                    cout << "                   Queue Situation                     " << endl;
                    cout << "=====================================================" << endl;
                        if(!q.isEmpty()){
                            cout << "Customer in Queue: " << endl;
                            q.printQue();
                        }
                        else{
                            cout << "No Customer in Queue" << endl;
                        }

                    questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                    break;
            }
            
            case 5:{
                // Update Service Bay Status
                system("cls");
                cout << "=====================================================" << endl;
                cout << "                  Service Bay Status                 " << endl;
                cout << "=====================================================" << endl;
                cout << "Service Bay 1" << endl;
                bay[0].printServiceBayInfo();
                cout << "Service Bay 2" << endl;
                bay[1].printServiceBayInfo();
                cout << "Service Bay 3" << endl;
                bay[2].printServiceBayInfo();
                system("pause");

                cout << "Enter the Service Bay ID you like to update: ";
                cin >> id;
                if(id=="B001"){
                    bay[0].car->printCustomerInfo();
                    cout << "Car Service Completed" << endl << endl;
                    cout << "Next Service Customer Information " << endl;
                    if(!q.isEmpty()){
                        Customer next=q.frontPtr->car;
                        bay[0].assignCar(&next);
                        q.deque();
                        bay[0].car->printCustomerInfo();
                        cout << "New Car Assigned to Service Bay 1" << endl;
                    }
                    else
                        cout << "There is no car in the queue" << endl;
                
                }
                else if(id=="B002"){
                    bay[1].car->printCustomerInfo();
                    cout << "Car Service Completed" << endl << endl;
                    cout << "Next Service Customer Information " << endl;
                    if(!q.isEmpty()){
                        Customer next=q.frontPtr->car;
                        bay[1].assignCar(&next);
                        q.deque();
                        bay[1].car->printCustomerInfo();
                        cout << "New Car Assigned to Service Bay 2" << endl;
                    }
                    else
                        cout << "There is no car in the queue" << endl;
                }
                else if(id=="B003"){
                    bay[2].car->printCustomerInfo();
                    cout << "Car Service Completed" << endl << endl;                 
                    cout << "Next Service Customer Information " << endl;
                    if(!q.isEmpty()){
                        Customer next=q.frontPtr->car;
                        bay[2].assignCar(&next);
                        q.deque();
                        bay[2].car->printCustomerInfo();
                        cout << "New Car Assigned to Service Bay 3" << endl;
                    }
                    else
                        cout << "There is no car in the queue" << endl;
                }
                else{
                    cout << "Service Bay Not Found" << endl;
                    std::this_thread::sleep_for(3s);
                    technicianMenu(list, service, q, bay, technician);
                }
                questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                break;
            }
                
            case 6:{
                // Customer List
                system("cls");
                cout << "=====================================================" << endl;
                cout << "                   Customer List                     " << endl;
                cout << "=====================================================" << endl;
                Node * current=list.head;
                while(current!=nullptr){
                    current->car.printCustomerInfo();
                    cout << endl;
                    current=current->next;
                }
                questionAfterFunctionforTechnicianManu(list, service, q, bay, technician);
                break;
            }

            case 7:
                // Back to Main Menu
                cout << "\nRedireccting back to Main Menu" << endl;
                std::this_thread::sleep_for(2s);
                mainMenu(list, service, q, bay, technician);
                break;
            case 8:
                // Exit System
                cout << "Thank You For Using Car Service System" << endl;
                system("pause");
                exit(0);
                break;
            default:
                cout << "Invalid Choice" << endl;
    }
}

void mainMenu(CustomerLL &list, ServiceType service[], ServiceQueue &q, ServiceBay bay[], ServiceTechnician technician[]){
    system("cls");
    int choice=0;
    cout << "=============================================" << endl;
    cout << "       Welcome To Car Service System         " << endl;
    cout << "=============================================" << endl;
    cout << "User Type: " << endl;
    cout << "1. Customer " << endl;
    cout << "2. Service Technician " << endl;
    cout << "3. Exit System" << endl;
    do {
        cout << "\nPlease Enter Your Choice: ";
        cin >> choice;

        if (choice == 1){
            cout << "\n=============================================" << endl;
            cout << "1. New Customer " << endl;
            cout << "2. Exist Customer " << endl;
            cout << "3. Back to Main Menu " << endl;
            cout << "\nEnter Your Choice: ";
            cin >> choice;
            if (choice == 1)
                newCustomerMenu(list, service, q, bay, technician);          
            else if (choice == 2)
                existCustomerMenu(list, service, q, bay, technician);
            else if (choice == 3){
                cout << "\nRedireccting back to Main Menu" << endl;
                std::this_thread::sleep_for(2s);
                system("cls");
                mainMenu(list, service, q, bay, technician);
            }
            else
                cout << "Please Enter Valid Choice" << endl;
            break;
        }
            
        else if (choice == 2){
            technicianMenu(list, service, q, bay, technician);
            break;
        }

        else if (choice == 3){
            cout << "Thank You For Using Car Service System" << endl;
            system("pause");
            exit(0);
        }
        else{
            cout << "Invalid Choice" << endl;
        }
    } while (choice != 1 || choice != 2 || choice != 3);
}

int main(){
    ServiceType serviceList[10];
    ServiceBay bay[5];
    ServiceTechnician technicianList[5];
    serviceList[0]=ServiceType("S001","Engine Oil Change","30 minutes","$50");
    serviceList[1]=ServiceType("S002","Brake Service","45 minutes","$100");
    serviceList[2]=ServiceType("S003","Suspension Service","60 minutes","$150");

    CustomerLL customerList;
    Customer c1("C001","Ali","123456789","ABC123");
    Customer c2("C002","Kumar","987654321","XYZ987");
    Customer c3("C003","Asad","456123789","JKL456");
    Customer c4("C004","Shalize","789456123","MNO789");
    Customer c5("C005","Zafri","321654987","PQR321");
    Customer c6("C006","Lee","654987321","STU654");

    c1.addServiceRecord(serviceList[0],"12/12/2021");
    c1.addServiceRecord(serviceList[1],"02/01/2022");
    c1.addServiceRecord(serviceList[2],"20/03/2022");
    c1.addServiceRecord(serviceList[0],"09/08/2022");
    c2.addServiceRecord(serviceList[2],"12/01/2023");
    c2.addServiceRecord(serviceList[1],"24/07/2023");
    c2.addServiceRecord(serviceList[2],"20/11/2023");
    c2.addServiceRecord(serviceList[0],"11/01/2024");


    ServiceTechnician t1("T001","John","Engine");
    ServiceTechnician t2("T002","Smith","Brakes");
    ServiceTechnician t3("T003","David","Suspension");

    ServiceBay b1("B001");
    ServiceBay b2("B002");
    ServiceBay b3("B003");

    ServiceQueue q;
    q.enque(c4,serviceList[2]);
    q.enque(c5,serviceList[0]);
    q.enque(c6,serviceList[1]);

    b1.assignTechnician(&t1);
    b1.assignCar(&c1);
    b2.assignTechnician(&t2);
    b2.assignCar(&c2);
    //b3.assignTechnician(&t3);
    b3.assignCar(&c3);

    bay[0]=b1;
    bay[1]=b2;
    bay[2]=b3;

    customerList.push(c1);
    customerList.push(c2);  
    customerList.push(c3);
    customerList.push(c4);
    customerList.push(c5);
    customerList.push(c6);
    technicianList[0]=t1;
    technicianList[1]=t2;
    technicianList[2]=t3;

    mainMenu(customerList, serviceList, q, bay, technicianList);

    return 0;
}