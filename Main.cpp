#include "LinkedList.cpp"
int main()
{
    LinkedList l;
    int num_of_players;
    cin>>num_of_players;
    for(int i = 0; i<num_of_players ; i++ )
    {
        int t;
        cin>>t;
        l.addLast(new Node(i+1,t));
    }


    int time = 0;
    int last_changed_time = 0;       //The time when the pillow was passed
    Node* cur = l.head();            //The game starting with the 1st person
    int rot = 1;                     // 1 means forward and 0 means backward
    int game_status = 0;             // 1 means game is already done

    while(1)
    {
        int cmdT;
        cin>>cmdT;

        char cmd;
        cin>>cmd;

        if(game_status == 1)
        {
            if(cmd == 'F')break;
            if(cmd == 'I')
            {
                int r;
                cin>>r;      //Useless information as no new player can't be inserted due to finished game
            }
            continue;
        }

        //determine currently which player has the pillow
        while((last_changed_time + cur->getRefT()) < cmdT)
        {
            last_changed_time += cur->getRefT();
            if(rot)cur = cur->next_Node();
            else   cur = cur->prev_Node();
        }




        // 'M' means Music stopped
        if(cmd == 'M')
        {
            printf("Player %d has been eliminated at t=%d\n", cur->getPersonNo(), cmdT);
            Node* temp = (rot)? cur->next_Node() : cur->prev_Node();                    //passing the pillow according the rotation
            Node* temp2 = cur;
            l.remove(temp2);
            cur = temp;
            if(cur->next_Node() == cur)
            {
                printf("Game over : Player %d wins!!\n", cur->getPersonNo());
                game_status = 1;
            }
            last_changed_time = cmdT;
        }

        //'R' means change Rotation
        else if(cmd == 'R')
        {
            rot = (++rot)%2;
        }

        //'P' means change Print current player
        else if(cmd == 'P')
        {
            printf("Player %d is holding the pillow at t=%d\n", cur->getPersonNo(), cmdT);
        }

        //'I' means insert new Player
        else if(cmd == 'I')
        {
            int ref_time ;
            cin>>ref_time;
            Node* in = new Node(++num_of_players, ref_time);
            (rot)? l.insertBefore(cur->getPersonNo(),in) : l.insertAfter(cur->getPersonNo(), in);   //Inserting reverse of current rotation
        }

        //Finishing the game and printing the sequence
        else if(cmd == 'F')
        {
            printf("Game over : Player %d is holding the pillow at t=%d, pillow passing sequence = player ",cur->getPersonNo(), cmdT);
            Node* temp = cur;
            (rot)? l.printForwardFrom(cur) : l.printBackwardFrom(cur);
            break;
        }

    }
    return 0;
}
