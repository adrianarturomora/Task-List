//CSC 134 - C++ Programming
//Adrian Arturo Mora
//17APR2022

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Task
{
    std::string task;
public:
    
    Task(string s)
    {
        task = s;
    }
    
    friend ostream &operator << (ostream &output, const Task &p);
};


ostream &operator << (ostream &output, const Task &p)
{
   
    output << p.task;
   
    return output;
}

class TaskList
{
    vector<Task> tasklist;
public:
    TaskList operator+= (Task task)
    {
        tasklist.push_back(task);
        
        return *this;
    }
    
    Task operator[](int i)
    {
        return tasklist[i];
    }
    
    int size() const
    {
        return tasklist.size();
    }
    
    void erase(int i)
    {
        tasklist.erase(tasklist.begin() + i);
    }
    
    friend ostream &operator << (ostream &output, const TaskList &p);
};

ostream &operator << (ostream &output, const TaskList &p)
{
    for(int i = 0; i < p.size(); i++)
    {
        output << i + 1<< ". " << p.tasklist[i] << endl;
    }
    return output;
}

class TaskIO
{
public:
    static TaskList read(string filename)
    {
        ifstream input_file(filename);
        
        TaskList list;
        string s;
        while(getline(input_file, s))
        {
            list += Task(s);
        }
        return list;
    }
    
    static void write(string filename, TaskList list)
    {
        ofstream output_file(filename);
        
        for(int i = 0; i < list.size(); i++)
        {
            output_file << list[i] << endl;
        }
    }
};

void print_commands()
{
    std::cout << "Task List" << std::endl << std::endl;
    
    std::cout << "COMMANDS" << std::endl;
    std::cout << "v - View pending tasks" << std::endl;
    std::cout << "a - Add a task" << std::endl;
    std::cout << "c - Complete a task" << std::endl;
    std::cout << "h - History of completed tasks" << std::endl;
    std::cout << "x - Exit" << std::endl;
    std::cout << "? - Menu Options" << std::endl << std::endl;
}

int main()
{
    const string filename = "tasklist";
    TaskList completedTasks = TaskIO::read(filename);
    TaskList activeTasks;
    
    
    print_commands();
    
    while(true)
    {
        string command;
        cout << "COMMAND: " << endl;
        cin >> command;
     
        if(command == "x" || command == "X")
        {
            break;
        }
        else if(command == "?")
        {
            print_commands();
        }
        
        else if(command == "v" || command == "V")
        {
            cout << activeTasks;
            
        }
        else if(command == "a" || command == "A")
        {
            
            string user_input;
           
            cout << "Description: ";
            cin.ignore();
            getline(cin, user_input);
            
            activeTasks += user_input;
            
            
        }
        else if(command == "c" || command == "C")
        {
            int number;
            cout << "Number: ";
            cin >> number;
            number--;
            if(number < 0 || number >= activeTasks.size())
            {
                cout << "Number is out of bounds.";
                continue;
            }
            completedTasks += activeTasks[number];
            activeTasks.erase(number);
            
            
        }
        else if(command == "h" || command == "H")
        {
            cout << completedTasks;
        }
        else
            cout << "Not a letter in the menu." << endl;
    }
    cout << "Bye!";
    
    TaskIO::write(filename, completedTasks);
    
    return 0;
    
}


