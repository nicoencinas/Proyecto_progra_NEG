/**
 * @brief It implements the space module
 *
 * @file game_rules.c
 * @author MAR
 */
#include "game_rules.h"
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

Status game_rules_run(Game *game)
{
    int random_rule;

    if (!game)
        return ERROR;

    /* 15% de probabilidad de que ocurra un evento */
    if ((rand() % 100) < 15)
    {
        game_set_event(game, TRUE);
        /* Ahora tenemos 10 reglas (0 a 9) */
        random_rule = rand() % 10; 

        switch (random_rule)
        {
        case 0: rule_enemy_ambush(game); break;
        case 1: rule_fog_teleport(game); break;
        case 2: rule_ghost_steals_item(game); break;
        case 3: rule_earthquake_kill_ch(game); break;
        case 4: rule_healing_rain(game); break;
        case 5: rule_strength_buff(game); break;   /* +1 ATK */
        case 6: rule_vitality_buff(game); break;   /* +1 MAX HP */
        case 7: rule_strength_debuff(game); break; /* -1 ATK */
        case 8: vitality_debuff(game); break;      /* -1 MAX HP */
        case 9: rule_enemy_ambush(game); break;    /*esta esta repetida, meter otra si quereis*/
        }
    }
    return OK;
}

/*Ataque sorpresa*/
void rule_enemy_ambush(Game *game)
{
    Player *p = game_get_player(game);
    player_set_health(p, player_get_health(p) - 1);
    game_set_e(game, "EVENT:  An enemy attacked you from the shadows! (-1 HP)");
}

/*Tp al inicio*/
void rule_fog_teleport(Game *game)
{
    Id random_space_id = 11;
    game_set_player_location(game, random_space_id);
    game_set_e(game, "EVENT:  A thick fog surrounds you... You are lost.");
}

void rule_ghost_steals_item(Game *game)
{
    Player *p = NULL;
    Object *obj = NULL;
    Id obj_id = NO_ID;
    int i, n_objs = 0;
    Id inv_objects[MAX_OBJECTS];
    char msg[WORD_SIZE];

    if (!game)
        return;
    p = game_get_player(game);

    for (i = 0; i < game_get_n_obj(game); i++)
    {
        obj = game_get_object_at(game, i);
        if (obj != NULL)
        {
            obj_id = object_get_id(obj);
            if (player_has_object(p, obj_id))
            {
                inv_objects[n_objs] = obj_id;
                n_objs++;
            }
        }
    } 

    if (n_objs > 0)
    {
        int target_index = rand() % n_objs;
        Id stolen_id = inv_objects[target_index];
        obj = game_get_object_from_id(game, stolen_id);

        player_remove_object(p, stolen_id);
        sprintf(msg, "EVENT: A ghost appeared and stole your %s!", object_get_name(obj));
        game_set_e(game, msg);
    }
    else
    {
        game_set_e(game, "EVENT: A ghost tried to steal from you, but your pockets are empty!");
    }
}

/* Terremoto que mata a un ch que te sigue */
void rule_earthquake_kill_ch(Game *game)
{
    Player *p = NULL;
    Character *ch = NULL;
    Id player_id = NO_ID;
    int i=0, r=0, count=0, j = 0;

    if (!game)
    {
        return;
    }
    p = game_get_player(game);

    for (i = 0; i < game_get_n_characters(game); i++)
    {
        ch = game_get_character_at(game, i);
        if (ch && character_get_following(ch) == player_id)
        {
            count++;
        }
    }

    if (count > 0)
    {
        r = rand() % count;

        for (i = 0; i < game_get_n_characters(game); i++)
        {
            ch = game_get_character_at(game, i);
            if (ch && character_get_following(ch) == player_id)
            {
                if (j == r)
                {
                    /* El personaje muere */
                    character_set_health(ch, 0);
                    character_set_following(ch, NO_ID);
                    character_set_location(ch, NO_ID);

                    game_set_e(game, "EVENT: EARTHQUAKE! Some rocks fell and killed one of your allies!");
                    return;
                }
                j++;
            }
        }
    }
    /*si no te sigue nadie menos 5  de vida al player*/
    else
    {
        player_set_health(p, player_get_health(p)-5);
        if (player_get_health(p)<=0)
        {
            game_get_finished(game);
        }
        
        game_set_e(game, "EVENT:  EARTHQUAKE! The ground shakes!.");
    }
}
void rule_healing_rain(Game *game)
{
    Player *p = game_get_player(game);
    player_set_health(p, player_get_health(p) + 2);
    game_set_e(game, "EVENT: A mystical rain falls. You feel stronger (+2 HP).");
}


void rule_strength_buff(Game *game) {
  Player *p = game_get_player(game);
  if (!p) return;

  player_set_damage(p, player_get_damage(p) + 1);
  game_set_e(game, "EVENT: A priestess blesses you, you feel stronger(+1 ATK)");
}

void rule_vitality_buff(Game *game) {
  Player *p = game_get_player(game);
  if (!p) return;
  player_set_max_health(p, player_get_max_health(p) + 1);
  game_set_e(game, "EVENT: A priestess blesses you, you feel more resilient (MAX HP +1)");
}

void rule_strength_debuff(Game *game) {
  Player *p = game_get_player(game);
  int current_dmg;
  if (!p) return;

  current_dmg = player_get_damage(p);
  if (current_dmg > 1) {
    player_set_damage(p, current_dmg - 1);
    game_set_e(game, "EVENT: A dark sorcerer curses you, you feel weaker (-1 ATK)");
  }
}

void vitality_debuff(Game *game) {
  Player *p = game_get_player(game);
  int current_max;
  if (!p) return;

  current_max = player_get_max_health(p);
  /* Evitamos que la vida máxima baje de 5 para no hacer el juego imposible */
  if (current_max > 5) {
    player_set_max_health(p, current_max - 1);
    if (player_get_health(p) > current_max - 1) {
      player_set_health(p, current_max - 1);
    }
    game_set_e(game, "EVENT: A dark sorcerer curses you, you feel less resistent (-1 MAX HP)");
  }
}
