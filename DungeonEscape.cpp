//Zeke Morton
//Escape

#include<iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class User              //Modularization class
{
public:
    void add_armor (string armor_found, int defense);
    void add_weapon(string weapon_found, int attack);
    int damage_taken (int damage);
    void restore_health();
    int get_attack();
    int get_defense();
    int get_health();
    void check_user_death();
    bool check_defeated(string name);
    void add_defeat(string name);
    void show_enemies();

private:
    int health = 100;
    int attack_power = 5;
    int defense_power = 5;
    vector <string> armor_list;           //structure1: vector
    vector <string> weapon_list;
    string enemies_defeated [15] = {};    //structure2: array

};

int User::get_attack()
{
    return attack_power;
}
int User::get_defense()
{
    return defense_power;
}

int User::get_health()
{
    return health;
}

bool User::check_defeated( string name)
{
    bool defeated = false;
    for (int i = 0; i < 15;i++)
    {
        if (enemies_defeated[i] == name)
        {
            defeated = true;
        }
    }
    return defeated;
}

void User::show_enemies()
{
    cout<<"You have defeated these enemies: ";
    int counter =0;
    for (int i = 0; i < 15;i++)
    {
        if (enemies_defeated[i] != "")
        {
            cout<<enemies_defeated[i]<<endl;
            counter++;
        }
    }
    if (counter >0)
    {
        cout<<endl<<"You've defeated "<<counter<<" enemies, Good Job!"<<endl;
    }


}

void User::add_defeat(string name)
{
    for (int i = 0;i<15;i++)
    {
        if (enemies_defeated[i] == "")
        {
            enemies_defeated[i] = name;
            break;
        }
    }

}


void User::add_armor (string armor_found, int defense)
{
    bool new_item = true;
    for (int i = 0;i < armor_list.size();i++)
    {
        if (armor_list.at(i) == armor_found)
        {
            new_item = false;
        }
    }
    if (new_item)
    {
        defense_power += defense;
        armor_list.push_back(armor_found);
        cout<<armor_found<<" has been added to inventory."<<endl;
        cin.get();
        cout<<"Defense has been raised by "<<defense<<" points."<<endl;
        cin.get();
    }
    else
    {
        cout<<"You already have that armor, so you put it back."<<endl;
        cin.get();
    }
}

void User::add_weapon (string weapon_found, int attack)
{
    bool new_item = true;
    for (int i = 0;i < weapon_list.size();i++)
    {
        if (weapon_list.at(i) == weapon_found)
        {
            new_item = false;
        }
    }
    if (new_item)
    {
        attack_power += attack;
        weapon_list.push_back(weapon_found);
        cout<<weapon_found<<" has been added to inventory."<<endl;
        cin.get();
        cout<<"Attack has been raised by "<<attack<<" points."<<endl;
        cin.get();
    }
    else
    {
        cout<<"You already have that weapon, so you put it back."<<endl;
        cin.get();
    }

}

int User::damage_taken (int damage)
{
    health -= damage;
    return health;
}

void User::restore_health()
{
    health = 100;
}

class Monster
{
public:
    int get_attack();
    int get_defense();
    int get_health();
    int damage_taken(int damage);
    void set_stats(int hp, int ap,int dp,string n, string weak);
    bool check_monster_death();
    string get_name();
    string get_weakness();

private:
    int health;
    int attack;
    int defense;
    string weakness;
    string name;


};
int Monster::get_health()
{
    return health;
}
string Monster::get_weakness()
{
    return weakness;
}

string Monster::get_name()
{
    return name;
}

int Monster::damage_taken (int damage)
{
    health -= damage;
    return health;
}
int Monster::get_attack()
{
    return attack;
}
int Monster:: get_defense()
{
    return defense;
}

void Monster::set_stats(int hp, int ap,int dp, string n, string weak)
{
    health = hp;
    attack = ap;
    defense = dp;
    name = n;
    weakness = weak;
}

void room1 (User* user);
int main()
{
    cout<<"     Dungeon Escape      "<<endl;
    cout<<"The game is played by using keys 1-4"<<endl;
    cout<<"The console is held with cin.get(), so just press enter to continue."<<endl;
    cin.get();
    User user;
    User* user_ptr = &user;        //effective use of pointers through out program
    srand(time(0));
    room1(user_ptr);
}

void User::check_user_death()
{
    if (health <= 0 )
    {
        string temp;
        cout<<"You have died"<<endl;
        cin.get();
        show_enemies();
        cin.get();
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        main();
    }
}

bool Monster::check_monster_death()
{
    if (health <= 0 )
    {
        return true;
    }
    else
    {
        return false;
    }

}

void battle(User* user, Monster monster)             //Modularization: function
{

    bool dead = user->check_defeated(monster.get_name());
    if (dead)
    {
        cout<<"You have already defeated "<<monster.get_name()<<endl;
    }
    int chance, damage;
    int choice;
    string hit;
    while (!dead)
    {
        cout<<"Where would you like to attack the "<<monster.get_name()<<"?"<<endl;
        cout<<"1) Head"<<endl;
        cout<<"2) Torso"<<endl;
        cout<<"3) Legs"<<endl;
        cout<<"4) Arms"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            hit = "Head";
            break;
        case 2:
            hit = "Torso";
            break;
        case 3:
            hit = "Legs";
            break;
        case 4:
            hit = "Arms";
            break;

        }

        chance  = rand () % 4+2;
        if (hit == monster.get_weakness())
        {
            chance *= 2;
        }
        damage = user->get_attack() *chance - monster.get_defense() ;
        if (damage < 0)
            {
                damage = 18;
            }
        cout<<"You strike monster and deal "<<damage<<" points of damage."<<endl;
        if (hit == monster.get_weakness())
        {
            cout<<"It's super effective!"<<endl;
        }
        cin.get();

        monster.damage_taken(damage);
        dead = monster.check_monster_death();
        if (dead)
        {
            cout<<"You have defeated "<<monster.get_name()<<endl;
            user->add_defeat(monster.get_name());
        }
        if (!monster.check_monster_death())
        {
            chance  = rand () % 4+2;
            damage = monster.get_attack() * chance - user->get_defense();
            if (damage < 1)
            {
                damage = 13;
            }
            cout<<"The monster strikes you and deals "<<damage<<" points of damage."<<endl;
            cin.get();
            user->damage_taken(damage);
            user->check_user_death();

        }

    }
    user->restore_health();



}

void escape(User* user)
{
    cout<<"You find yourself outside with lush fields of green."<<endl;
    cout<<"This is the happiest you have ever been, you have escaped."<<endl;
    cin.get();
    user->show_enemies();
    cout<<"Play agin?"<<endl;
    cin.get();
    main();
}
void room2 (User* user);

void room1 (User* user)
{
    int choice;
    cout<<"You awake in a dark room"<<endl;
    while (true)
    {
        cout<<"What do you want to do?"<<endl;
        cout<<"1) Walk towards the door."<<endl;
        cout<<"2) Look around the room."<<endl;
        cout<<"3) Turn on the lights."<<endl;
        cout<<"4) Check the window."<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                cout<<"You exit the room."<<endl;
                room2(user);
                break;
            }
            case 2:
            {
                cout<<"You find leather gloves on the floor."<<endl;
                user->add_armor("leather gloves", 4);
                break;
            }
            case 3:
            {
                cout<<"After turning on the lights, you relize that you have awoken several bats"<<endl;
                cout<<"They begin to attack!"<<endl;
                Monster bats;
                bats.set_stats(50, 5, 4, "Venemous Bats", "Head");
                battle(user, bats);
                cout<<"You find a large bat fang on the ground."<<endl;
                cin.get();
                user->add_weapon("Bat Fang", 4);
                cout<<"You decide to get out of the room before more bats wake up."<<endl;
                room2(user);
                break;
            }
            case 4:
            {
                cout<<"You check the window and its locked, dang"<<endl;
                cin.get();
                break;
            }
        }
    }
}

void room4 (User* user);

void room3 (User* user)
{
    int choice;
    Monster skeleton;
    skeleton.set_stats(250, 20, 10, "Skeleton King", "Torso");
    cout<<"You find yoursel in a large open room."<<endl;
    cin.get();
    cout<<"There is a large throne with a giant skeleton sitting in it."<<endl;
    cin.get();

    while (true)
    {
        cout<<"What would you like to do?"<<endl;
        cout<<"1) Approach Skeleton."<<endl;
        cout<<"2) Go back to way you came."<<endl;
        cout<<"3) Go through the door on the side of the room."<<endl;
        cout<<"4) Look around."<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                int opt;
                cout<<"As you approch the Skeleton, he begins to move."<<endl;
                cin.get();
                cout<<"He states: 'Come closer and you will surely perish'"<<endl;
                cout<<"Continue? (1 to continue)"<<endl;
                cin>>opt;
                if (opt ==1)
                {
                    battle(user, skeleton);
                    cout<<"The Skeleton King screams out in pain and sudenly vanishes into thin air."<<endl;
                    cin.get();
                    cout<<"You hear an unlocking sound come from the door on the other side of the room."<<endl;
                }

                break;
            }
            case 2:
            {
                room2(user);

                break;
            }
            case 3:
            {
                if (user->check_defeated("Skeleton King"))
                {
                    room4(user);
                }
                else
                {
                    cout<<"The door is locked, you cannot go that way."<<endl;
                }
                break;
            }
            case 4:
            {
                cout<<"You look behind the throne and see a golden helmet."<<endl;
                cin.get();
                user->add_armor("Golden Helemt", 20);
                break;
            }
        }
    }

}

void room4 (User* user)
{
    int choice;
    Monster spider;
    spider.set_stats(300, 15, 30, "Arachnais", "Head");
    cout<<"You find yoursel in a large open room."<<endl;
    cin.get();
    cout<<"There is an ominous feeling about the room...."<<endl;
    cin.get();
    cout<<"You Notice two doors beside the one you came in."<<endl;

    while (true)
    {
        cout<<"What would you like to do?"<<endl;
        cout<<"1) Head towards the large door to the outside."<<endl;
        cout<<"2) Go towards the other set of large doors."<<endl;
        cout<<"3) Go through the smaller set of stairs."<<endl;
        cout<<"4) Look around."<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                int opt;
                cout<<"As you approch the Exit, you hear a loud rumbling sound."<<endl;
                cin.get();
                cout<<"A giant spider descends from the ceiling."<<endl;
                cout<<"There is no time to escape, you must fight!"<<endl;
                if (!user->check_defeated(spider.get_name()))
                {
                    battle(user, spider);
                    cout<<"The withers away into dust."<<endl;
                    cin.get();
                    cout<<"You find a the spiders venoumous fangs."<<endl;
                    user->add_weapon("Arachnais Fang", 12);
                }
                cout<<"You are now able to reach the exit."<<endl;
                escape(user);
                break;
            }
            case 2:
            {
                room2(user);

                break;
            }
            case 3:
            {
                room3(user);
                break;
            }
            case 4:
            {
                cout<<"You find Mighty Boots"<<endl;
                cin.get();
                user->add_armor("Mighty Boots", 18);
                break;
            }
        }
    }

}

void room2 (User* user)
{
    int choice;
    Monster statue;
    statue.set_stats(150, 10, 30, "Statue King", "Legs");
    cout<<"You find yoursel in a large hallway"<<endl;
    cin.get();
    cout<<"There is a large statue at the center of the hallway, \na large door at the other side."<<endl;
    cout<<"There is also a smaller door on the side of the hallway."<<endl;
    cin.get();

    while (true)
    {
        cout<<"What would you like to do?"<<endl;
        cout<<"1) Examine the statue."<<endl;
        cout<<"2) Run down the hallway towards the large door as quickly as possible"<<endl;
        cout<<"3) Go through the smaller door on the side of the hall."<<endl;
        cout<<"4) Look around."<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                int pull;
                cout<<"You look more closely at the statue and see that there is a large lever."<<endl;
                cout<<"Pull it? (Press 1 to pull)"<<endl;
                cin>>pull;
                if (pull == 1)
                {
                    cout<< "You Pull the lever ans a secret compartment opens up"<<endl;
                    cout<< "You cannot help but look inside....."<<endl;
                    cout<<"You found the mythical sword Excaliber!"<<endl;
                    user->add_weapon("Excaliber", 25);
                }
                break;
            }
            case 2:
            {
                int chance, run;
                chance = rand() % 50;
                cout<<"As you pass the large statue, it begins to move towards you."<<endl;
                cin.get();
                cout<<"Would you like to turn and fight, or continue running? (1 to keep running)"<<endl;
                cin>>run;
                if (run != 1)
                {
                    chance = 0;
                }
                if (chance > 25)
                {
                    cout<<"You barely managed to reach the door and slip through"<<endl;
                    cin.get();
                    cout<<"You hear a large thud right as the door closes from the statues weapon."<<endl;
                    room4(user);
                }
                else
                {
                    cout<<"The statue cuts you off from the door, you have no choice but to fight."<<endl;
                    cin.get();
                    battle(user, statue);
                    cout<<"You managed to survive a gruling battle"<<endl;
                    cin.get();
                    cout<<"You make your way to the door"<<endl;
                    room4(user);

                }

                break;
            }
            case 3:
            {
                room3(user);
                break;
            }
            case 4:
            {
                cout<<"You look under the rug and find a trap door."<<endl;
                cin.get();
                cout<<"You lift the latch and find Precious Armor"<<endl;
                cin.get();
                user->add_armor("Precious Armor", 25);
                break;
            }
        }
    }
}



