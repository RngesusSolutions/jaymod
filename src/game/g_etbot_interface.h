/*
 * Jaymod
 * Copyright (C) 2025 Jaymod Team
 *
 * Adapted from ET: Legacy Omnibot integration
 * ET: Legacy Copyright (C) 2012-2024 ET:Legacy team <mail@etlegacy.com>
 *
 * This file is part of Jaymod
 *
 * Jaymod is free software: you can redistribute it and/or modify
 * it under the terms of the Apache License as published by
 * the Apache Software Foundation, either version 2.0 of the License, or
 * (at your option) any later version.
 *
 * Jaymod is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * @file g_etbot_interface.h
 * @brief Jaymod <-> Omni-Bot interface header file.
 */

#ifndef INCLUDE_G_JAYBOT_INTERFACE_H
#define INCLUDE_G_JAYBOT_INTERFACE_H

#include "../bgame/q_shared.h"

#ifdef FEATURE_OMNIBOT

#define OMNIBOT_MODNAME    "jaymod"
#define OMNIBOT_MODVERSION "2.2.0"

//////////////////////////////////////////////////////////////////////////
/**
 * @enum BotFlagOptions
 * @brief g_OmniBotFlags bits
 */
typedef enum
{
	OBF_DONT_XPSAVE        = (1 << 0),
	OBF_DONT_MOUNT_TANKS   = (1 << 1),
	OBF_DONT_MOUNT_GUNS    = (1 << 2),
	OBF_DONT_SHOW_BOTCOUNT = (1 << 3),
	OBF_GIBBING            = (1 << 4),
	OBF_TRIGGER_MINES      = (1 << 5),
	OBF_SHOVING            = (1 << 6),
	OBF_NEXT_FLAG          = (1 << 16),
} BotFlagOptions;

//////////////////////////////////////////////////////////////////////////
// Bot Interface Functions
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// Initialization and shutdown
int Bot_Interface_Init(void);
void Bot_Interface_InitHandles(void);
int Bot_Interface_Shutdown(void);
void Bot_Interface_Update(void);
void Bot_Interface_ConsoleCommand(void);

// Utility functions
qboolean Bot_Util_AllowPush(int weaponId);
qboolean Bot_Util_CheckForSuicide(struct gentity_s *ent);
const char *_GetEntityName(struct gentity_s *_ent);
void Bot_Util_SendTrigger(struct gentity_s *_ent, struct gentity_s *_activator, const char *_tagname, const char *_action);

// Conversion functions
int Bot_WeaponGameToBot(int weapon);
int Bot_TeamGameToBot(int team);
int Bot_PlayerClassGameToBot(int playerClass);

// Entity events
void Bot_Queue_EntityCreated(struct gentity_s *pEnt);
void Bot_Event_EntityDeleted(struct gentity_s *pEnt);

// Client events
void Bot_Event_ClientConnected(int _client, qboolean _isbot);
void Bot_Event_ClientDisConnected(int _client);

// Weapon events
void Bot_Event_ResetWeapons(int _client);
void Bot_Event_AddWeapon(int _client, int _weaponId);
void Bot_Event_RemoveWeapon(int _client, int _weaponId);

// Combat events
void Bot_Event_TakeDamage(int _client, struct gentity_s *_ent);
void Bot_Event_Death(int _client, struct gentity_s *_killer, const char *_meansofdeath);
void Bot_Event_KilledSomeone(int _client, struct gentity_s *_victim, const char *_meansofdeath);
void Bot_Event_Revived(int _client, struct gentity_s *_whodoneit);
void Bot_Event_Healed(int _client, struct gentity_s *_whodoneit);
void Bot_Event_ReceivedAmmo(int _client, struct gentity_s *_whodoneit);

// Weapon fire events
void Bot_Event_FireWeapon(int _client, int _weaponId, struct gentity_s *_projectile);
void Bot_Event_PreTriggerMine(int _client, struct gentity_s *_mine);
void Bot_Event_PostTriggerMine(int _client, struct gentity_s *_mine);
void Bot_Event_MortarImpact(int _client, vec3_t _pos);

// Spectator events
void Bot_Event_Spectated(int _client, int _who);

// Communication events
void Bot_Event_ChatMessage(int _client, struct gentity_s *_source, int _type, const char *_message);
void Bot_Event_VoiceMacro(int _client, struct gentity_s *_source, int _type, const char *_message);

// Sound events
void Bot_Event_Sound(struct gentity_s *_source, int _sndtype, const char *_name);

// Fireteam events
void Bot_Event_FireTeamCreated(int _client, int _fireteamnum);
void Bot_Event_FireTeamDestroyed(int _client);
void Bot_Event_JoinedFireTeam(int _client, struct gentity_s *leader);
void Bot_Event_LeftFireTeam(int _client);
void Bot_Event_InviteFireTeam(int _inviter, int _invitee);
void Bot_Event_FireTeam_Proposal(int _client, int _proposed);
void Bot_Event_FireTeam_Warn(int _client, int _warned);

// Goal management
void Bot_AddDynamiteGoal(struct gentity_s *_ent, int _team, const char *_tag);
void Bot_AddFallenTeammateGoals(struct gentity_s *_teammate, int _team);
void AddDeferredGoal(struct gentity_s *ent);
void UpdateGoalEntity(struct gentity_s *oldent, struct gentity_s *newent);
void GetEntityCenter(struct gentity_s *ent, vec3_t pos);

#ifdef __cplusplus
}
#endif

#endif // FEATURE_OMNIBOT

#endif // INCLUDE_G_JAYBOT_INTERFACE_H
