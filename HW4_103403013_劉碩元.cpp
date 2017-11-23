#include <iostream>
#include <vector>
#include <fstream>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
/*using dynamic array in struct method*/
typedef struct myset
{
    vector<int> var;
    int elementNum;
    myset()
    {

    }
    bool sameTeam(int num)
    {
        bool flag = (find(var.begin(), var.end(), num) != var.end());
        return flag;
    }
};
int space = 0;
typedef struct linking_list *link_pointer;
typedef struct linking_list
{
  int team;
  int value;
  link_pointer link_before;
  link_pointer link_after;

};
link_pointer front_ptr, current_ptr, rear_ptr;
void add(int tim, int number)
{
    link_pointer temp = (link_pointer) malloc(sizeof(linking_list));
    temp->team = tim;
    temp->value = number;
    temp->link_before = NULL;
    temp->link_after = NULL;
    //queue is empty
    if(space==0)
    {
        front_ptr = temp;
        current_ptr = temp;
        rear_ptr = temp;
        space++;
    }
    else // queue has at least one element
    {
        link_pointer save_ptr;
        for(int i=0; i<space;i++) // find same team member in the queue
        {
            if(tim == current_ptr->team)
                break;
            else
                current_ptr = current_ptr->link_before;
        }

        if(current_ptr != NULL) //means that same team is found in queue
        {
            save_ptr = current_ptr->link_after; //save the current->link_after before insertion
            current_ptr->link_after = temp;
            temp->link_before = current_ptr;
            temp->link_after = save_ptr;
            if(save_ptr != NULL)
                save_ptr->link_before = temp;
            else
                rear_ptr = temp; // when there is only one element in the queue, or the insertion is after the last element
            current_ptr = rear_ptr;
            //cout << current_ptr->value << endl;

        }
        else{
            // can't find any same team in the queue
            save_ptr = rear_ptr;
            rear_ptr->link_after = temp;
            rear_ptr = temp;
            rear_ptr->link_before = save_ptr;
            current_ptr = rear_ptr;
            rear_ptr->link_after = NULL;
        }
        space++;

    }
    //temp = NULL;

    //cout << rear_ptr->value << endl;
}

void deletion()
{
    int value;
    link_pointer save_ptr;

    if(space == 0)
    {
        cout << "the queue is empty" << endl;
    }
    else if(space == 1)
    {
        value = front_ptr->value;
        space--;
        front_ptr = NULL;
        current_ptr = NULL;
        rear_ptr = NULL;
        cout << value << endl;

    }
    else{
        save_ptr = front_ptr->link_after;
        save_ptr->link_before = NULL;
        value = front_ptr->value;
        front_ptr = save_ptr;
        space--;
        cout << value << endl;
    }



}

int main()
{
    int flag_while = 1,k=0;
    char file_name[20]= {};

    cout << "Please enter file's name(remember to enter file's format): ";
    cin >> file_name;

    ifstream ifs(file_name,ios::in);
    while(flag_while)
    {
        vector<myset> mylist;

        int teamNum,num;

        ifs >> teamNum;
        if(teamNum==0)
			break;

        for(int i=0; i<teamNum; i++)
        {
            mylist.push_back(myset());
        }

        for(int k=0; k < teamNum; k++)
        {
            ifs >> mylist.at(k).elementNum;
            for(int j=0; j < mylist.at(k).elementNum; j++)
            {
                ifs >> num;
                mylist.at(k).var.push_back(num);
            }
        }
        //enqueue or dequeue
        string next;
        string str_enqueue = "ENQUEUE";
        string str_dequeue = "DEQUEUE";
        string str_stop = "STOP";
        string jump_loop = "0";
        bool flag_enqueue;
        cout<<"Scenario #"<<++k<<endl;
        while(ifs >> next)
        {
            if(next.compare(jump_loop)==0)
            {
                flag_while = 0;
                break;
            }
            else if(next.compare(str_stop)==0)
            {
                //all the variables that need for the next round should go back to the initial condition
                space = 0;
                front_ptr = NULL;
                current_ptr = NULL;
                rear_ptr = NULL;
                break;
            }
            else if(next.compare(str_enqueue)==0)
            {
                int enqueueNum,s, team;
                ifs >> enqueueNum;
                for( s=0; s<teamNum; s++)
                {
                    flag_enqueue = mylist.at(s).sameTeam(enqueueNum);
                    if(flag_enqueue)
                        break; // means that the element belongs to this team
                }
                team = s;
                add(team,enqueueNum);
            }
            else if(next.compare(str_dequeue)==0)
            {
                deletion();
            }
        }

    }
    return 0;
}
