#include "game_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "space.h"
#include "character.h"

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

            while (strlen(line) < 14)
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
  char line[WORD_SIZE] = "", name[WORD_SIZE] = "", desc[40] = "";
  char *toks = NULL;
  Id id, space_id;
  Object *obj = NULL;

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

      obj = object_create(id);
      if (obj != NULL)
      {
        object_set_name(obj, name);
        object_set_desc(obj, desc);
        game_add_object(game, obj);
        space_add_object(game_get_space(game, space_id), id);
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
  int health, friendly;
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
      /* id */
      toks = strtok(line + 3, "|");
      if (!toks)
        continue;
      id = atol(toks);

      /* nome */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(name, toks);

      /* gdesc */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      strcpy(gdesc, toks);

      /* location*/
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      loc = atol(toks);

      /* health */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      health = atoi(toks);

      /* B friend */
      toks = strtok(NULL, "|");
      if (!toks)
        continue;
      friendly = atoi(toks);

      /* chat */
      toks = strtok(NULL, "\r\n"); 
      if (!toks) continue;
      strcpy(msg, toks);

      ch = character_create(id);
      if (ch)
      {
        character_set_name(ch, name);
        character_set_gdesc(ch, gdesc);
        character_set_health(ch, health);
        character_set_friendly(ch, (Bool)friendly);
        character_set_message(ch, msg);

        character_set_location(ch, loc);
        game_add_character(game, ch);

        s = game_get_space(game, loc);
        if (s)
        {
          space_set_character(s, id);
        }
      }
    }
  }
  fclose(file);
  return OK;
}

Status game_reader_load_player(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE], name[WORD_SIZE], gdesc[WORD_SIZE];
  char *toks = NULL;
  Id space_id;
  int health;
  Player *p = game_get_player(game);

  file = fopen(filename, "r");
  if (!file)
    return ERROR;

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      strtok(line + 3, "|");

      toks = strtok(NULL, "|");
      if (toks)
        strcpy(name, toks);

      toks = strtok(NULL, "|");
      if (toks)
        strcpy(gdesc, toks);

      toks = strtok(NULL, "|");
      if (toks)
        space_id = atol(toks);

      toks = strtok(NULL, "|");
      if (toks)
        health = atoi(toks);

      player_set_name(p, name);
      player_set_gdesc(p, gdesc);
      player_set_health(p, health);
      game_set_player_location(game, space_id);
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
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      dest = atol(toks);
      toks = strtok(NULL, "|");
      dir = atoi(toks);
      toks = strtok(NULL, "|");
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
Status game_create_from_file(Game *game, char *filename)
{
  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_objects(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_characters(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_player(game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_links(game, filename) == ERROR)
    return ERROR;
  return OK;
}