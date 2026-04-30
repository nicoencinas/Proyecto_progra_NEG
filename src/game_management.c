/**
 * @brief It implements the command interpreter
 *
 * @file game_management.c
 */
#include "game_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "space.h"
#include "character.h"
#include <errno.h>
#include "player.h"

Status game_create_from_file(Game *game, char *filename)
{
  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_objects(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_characters(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_players(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_links(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_followers(game, filename) == ERROR)
    return ERROR;

  return OK;
}

Status game_reader_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "", name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id;
  Space *space = NULL;
  int i;

  if (!game || !filename)
    return ERROR;

  file = fopen(filename, "r");
  if (file == NULL)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);
      toks = strtok(NULL, "| \n\r");
      if (!toks)
        continue;
      strcpy(name, toks);

      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);

        for (i = 0; i < 5; i++)
        {
          if (fgets(line, WORD_SIZE, file))
          {
            line[strcspn(line, "\r\n")] = '\0';

            while ((int)strlen(line) < 14)
            {
              strcat(line, " ");
            }
            line[14] = '\0';
            space_set_gdesc_at(space, i, line);
          }
        }
        game_add_space(game, space);
      }
    }
  }

  fclose(file);
  return OK;
}

Status game_reader_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "", name[WORD_SIZE] = "", desc[WORD_SIZE] = "";
  char *toks = NULL;
  Id id, space_id, open, dependency;
  Object *obj = NULL;
  Bool movable;
  int health;

  if (!game || !filename)
    return ERROR;

  file = fopen(filename, "r");
  if (file == NULL)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);

      toks = strtok(NULL, "|");
      if (toks)
        strcpy(name, toks);

      toks = strtok(NULL, "|");
      if (toks)
        space_id = atol(toks);

      toks = strtok(NULL, "|");
      if (toks)
        strcpy(desc, toks);

      toks = strtok(NULL, "|");
      if (toks)
        health = atoi(toks);

      toks = strtok(NULL, "|");
      if (toks)
        movable = atoi(toks);

      toks = strtok(NULL, "|");
      if (toks)
        open = atol(toks);

      toks = strtok(NULL, "|\r\n");
      if (toks)
        dependency = atol(toks);

      obj = object_create(id);
      if (obj != NULL)
      {
        object_set_name(obj, name);
        object_set_desc(obj, desc);
        object_set_health(obj, health);
        object_set_movable(obj, movable);
        object_set_open(obj, open);
        object_set_dependency(obj, dependency);

        game_add_object(game, obj);

        if (space_id != NO_ID)
        {
          space_add_object(game_get_space(game, space_id), id);
        }
      }
    }
  }

  fclose(file);
  return OK;
}

Status game_reader_load_characters(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  char name[WORD_SIZE], msg[WORD_SIZE], gdesc[WORD_SIZE];
  Id id, loc;
  int health, friendly, damage;
  Character *ch = NULL;
  Space *s = NULL;

  if (!game || !filename)
    return ERROR;
  file = fopen(filename, "r");
  if (file == NULL)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#c:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(gdesc, toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      loc = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      health = atoi(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      friendly = atoi(toks);

      toks = strtok(NULL, "\r\n");
      if (!toks)
        continue;
      strcpy(msg, toks);

      toks = strtok(NULL, "|\r\n");
      if (toks)
        damage = atoi(toks);

      ch = character_create(id);
      if (ch)
      {
        character_set_name(ch, name);
        character_set_gdesc(ch, gdesc);
        character_set_health(ch, health);
        character_set_friendly(ch, (Bool)friendly);
        character_set_message(ch, msg);
        character_set_location(ch, loc);
        character_set_damage(ch, damage);
        game_add_character(game, ch);

        s = game_get_space(game, loc);
        if (s)
        {
          space_add_character(s, id);
        }
      }
    }
  }
  fclose(file);
  return OK;
}

Status game_reader_load_players(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE], name[WORD_SIZE], gdesc[WORD_SIZE];
  char *toks = NULL;
  Id id, space_id;
  int health;
  Player *p = NULL;

  if (!game || !filename)
    return ERROR;

  file = fopen(filename, "r");
  if (!file)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      /* id */
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);

      /* name */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(name, toks);

      /* gdesc */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(gdesc, toks);

      /* location */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      space_id = atol(toks);

      /* health */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      health = atoi(toks);

      toks = strtok(NULL, "|\r\n");

      /* Create and configure the player */
      p = player_create(id);
      if (!p)
        continue;

      player_set_name(p, name);
      player_set_gdesc(p, gdesc);
      player_set_health(p, health);
      player_set_location(p, space_id);

      game_add_player(game, p);
    }
  }

  fclose(file);
  return OK;
}

Status game_reader_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "", name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id, origin, dest;
  int dir, open;
  Link *link = NULL;

  if (!game || !filename)
    return ERROR;
  file = fopen(filename, "r");
  if (!file)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      origin = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      dest = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      dir = atoi(toks);

      toks = strtok(NULL, "| \t\r\n");
      if (!toks)
        continue;
      open = atoi(toks);

      link = link_create(id);
      if (link)
      {
        link_set_name(link, name);
        link_set_origin(link, origin);
        link_set_destination(link, dest);
        link_set_direction(link, (Direction)dir);
        link_set_open(link, (Bool)open);
        game_add_link(game, link);
      }
    }
  }
  fclose(file);
  return OK;
}

Status game_reader_load_followers(Game *game, char *filename)
{
  FILE *file = NULL;
  Id ch_id, pl_id;
  char *toks = NULL;
  char line[WORD_SIZE];
  Character *ch = NULL;

  if (!game || !filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (!file)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#f:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      ch_id = atol(toks);

      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      pl_id = atol(toks);

      ch = game_get_character(game, ch_id);
      if (!ch)
        continue;

      character_set_following(ch, pl_id);
    }
  }

  fclose(file);

  return OK;
}

Status game_management_save(Game *game, char *filename)
{
  FILE *file = NULL;
  int i, j;
  Space *s = NULL;
  Object *obj = NULL;
  Character *ch = NULL;
  Player *p = NULL;
  Link *l = NULL;
  Id pl_id;

  if (!game || !filename)
    return ERROR;

  /* Creamos la carpeta save donde vamos a guardar las partidas */
  system("mkdir -p save");

  file = fopen(filename, "w");
  if (!file)
    return ERROR;

  /* SPACES */
  for (i = 0; i < game_get_n_spaces(game); i++)
  {
    s = game_get_space_at(game, i);

    fprintf(file, "#s:%ld|%s\n", space_get_id(s), space_get_name(s));

    for (j = 0; j < GDESC_LINES; j++)
    {
      fprintf(file, "%s\n", space_get_gdesc_at(s, j));
    }
  }

  /* OBJECTS */
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    obj = game_get_object_at(game, i);

    fprintf(file, "#o:%ld|%s|%ld|%s|%d|%d|%ld|%ld\n",
            object_get_id(obj),
            object_get_name(obj),
            game_get_object_location(game, object_get_id(obj)),
            object_get_desc(obj),
            object_get_health(obj),
            object_get_movable(obj),
            object_get_open(obj),
            object_get_dependency(obj));
  }

  /* CHARACTERS */
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);

    fprintf(file, "#c:%ld|%s|%s|%ld|%d|%d|%s|%d\n",
            character_get_id(ch),
            character_get_name(ch),
            character_get_gdesc(ch),
            character_get_location(ch),
            character_get_health(ch),
            character_get_friendly(ch),
            character_get_message(ch),
            character_get_damage(ch));
  }

  /* PLAYERS */
  for (i = 0; i < game_get_n_players(game); i++)
  {
    p = game_get_player_at(game, i);

    fprintf(file, "#p:%ld|%s|%s|%ld|%d\n",
            player_get_id(p),
            player_get_name(p),
            player_get_gdesc(p),
            player_get_location(p),
            player_get_health(p));
  }

  /* LINKS */
  for (i = 0; i < game_get_n_links(game); i++)
  {
    l = game_get_link_at(game, i);

    fprintf(file, "#l:%ld|%s|%ld|%ld|%d|%d\n",
            link_get_id(l),
            link_get_name(l),
            link_get_origin(l),
            link_get_destination(l),
            link_get_direction(l),
            link_get_open(l));
  }

  /* FOLLOWERS */
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);

    pl_id = character_get_following(ch);

    if (pl_id != NO_ID)
    {
      fprintf(file, "#f:%ld|%ld\n", character_get_id(ch), pl_id);
    }
  }

  fclose(file);

  return OK;
}

Status game_management_load(Game *game, char *filename)
{
  if (!game || !filename)
    return ERROR;

  if (game_create_from_file(game, filename) == ERROR)
    return ERROR;

  return OK;
}