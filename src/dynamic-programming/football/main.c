#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    int salary, id;
    char name[30];
} player;

typedef struct
{
    player **players;
    char name[30];
} team;

typedef struct
{
    team **teams;
    char name[30];
} championship;

void print_player(player P)
{
    printf("Jucatorul: %s are salaryl: %d si id: %d\n", P.name, P.salary, P.id);
}

void print_team(team T)
{
    int i = 0;
    printf("====TEAM: %s====\n", T.name);
    player **players = T.players;
    while (*(players + i) != NULL)
    {
        print_player(**(players + i));
        i++;
    }
    printf("====TEAM: %s====\n", T.name);
    printf("\n");
}
void print_championship(championship C)
{
    printf("====LEAGUE: %s====\n", C.name);
    printf("\n");

    team **teams = C.teams;
    int i = 0;
    while (*(teams + i) != NULL)
    {
        print_team(**(teams + i));
        i++;
    }

    printf("====LEAGUE: %s====\n", C.name);
    printf("\n");
}

int check_player_in_team(player P, team T)
{
    int i = 0;
    player **players = T.players;

    if (players == NULL)
        return 0;

    while (*(players + i) != NULL)
    {
        if (strcmp((*(players + i))->name, P.name) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}
int check_team_in_championship(team T, championship C)
{
    int i = 0;
    team **teams = C.teams;
    if (teams == NULL)
        return 0;

    while (*(teams + i) != NULL)
    {
        if (strcmp((*(teams + i))->name, T.name) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void add_player_in_team(player *pointer_to_new_player, team *T)
{
    if (T->players == NULL)
    {
        T->players = realloc(T->players, (2) * sizeof(player *));

        T->players[0] = pointer_to_new_player;
        T->players[1] = NULL;
    }

    if (check_player_in_team(*pointer_to_new_player, *T) == 0)
    {
        int i = 0;
        while (T->players[i] != NULL)
            i++;
        T->players = realloc(T->players, (i + 2) * sizeof(player *));

        T->players[i] = pointer_to_new_player;
        T->players[i + 1] = NULL;
    }
    else
        printf("Player %s is already in team %s\n", pointer_to_new_player->name, T->name);
}
void remove_player_from_team(player *pointer_to_player, team *T)
{
    if (T->players == NULL)
        return;

    if (check_player_in_team(*pointer_to_player, *T) == 1)
    {
        int i = 0;
        while (T->players[i] != NULL)
        {
            if (strcmp(T->players[i]->name, pointer_to_player->name) == 0)
                break;

            i++;
        }

        while (T->players[i] != NULL)
        {
            if (T->players[i + 1] == NULL)
                T->players[i] = NULL;
            else
                T->players[i] = T->players[i + 1];

            i++;
        }
    }
    else
        printf("Player %s is not in team %s\n", pointer_to_player->name, T->name);
}
void add_team_in_championship(team *pointer_to_new_team, championship *C)
{
    if (C->teams == NULL)
    {
        C->teams = realloc(C->teams, sizeof(team *) * 2);
        C->teams[0] = pointer_to_new_team;
        C->teams[1] = NULL;
    }

    if (check_team_in_championship(*pointer_to_new_team, *C) == 0)
    {
        int i = 0;
        while (C->teams[i] != NULL)
            i++;

        C->teams = realloc(C->teams, sizeof(team *) * (i + 2));
        C->teams[i] = pointer_to_new_team;
        C->teams[i + 1] = NULL;
    }
    else
        printf("Teams %s is already in championship %s\n", pointer_to_new_team->name, C->name);
}
// void elimina_team_in_championship(team a, championship *championship)
// {

//     if (check_team_in_championship(a, *championship) == 1)
//     {
//         int i = 0;
//         team *team = championship->teams;
//         while (i < M && strlen(team->name)) // NU ASA
//         {
//             if (strcmp(team->name, a.name) == 0)
//             {
//                 int j = 0;
//                 for (j = i; j + 1 < M; j++)
//                 {
//                     (team + j) = (team + j + 1);
//                 }
//                 i = j;
//             }
//             i++;
//         }
//     }
//     else
//         printf("Nu este in championship");
// }
int main(void)
{
    player Andrei = {10000, 1, "Andrei"};
    player Mihai = {20000, 2, "Mihai"};

    team team_alpha = {NULL, "Alhpa"};
    add_player_in_team(&Andrei, &team_alpha);

    team team_beta = {NULL, "Beta"};
    add_player_in_team(&Mihai, &team_beta);

    championship championship = {NULL, "Liga 1"};
    add_team_in_championship(&team_alpha, &championship);
    add_team_in_championship(&team_beta, &championship);

    print_team(team_alpha);

    printf("\n");

    add_player_in_team(&Mihai, &team_alpha);
    print_team(team_alpha);
    remove_player_from_team(&Andrei, &team_alpha);
    print_team(team_alpha);

    printf("\n");

    add_player_in_team(&Andrei, &team_beta);
    print_team(team_beta);

    printf("\n");

    print_championship(championship);

    return 0;
}