/*
 * Jaymod - Omnibot Integration Stub
 * This is a minimal stub implementation to allow compilation.
 * Full implementation to be added from ET: Legacy.
 */

#ifdef FEATURE_OMNIBOT

#include "g_etbot_interface.h"

// Stub implementations for all bot interface functions

extern "C" {

int Bot_Interface_Init(void) {
	// TODO: Load Omnibot library and initialize
	return 0;
}

void Bot_Interface_InitHandles(void) {
	// TODO: Initialize entity handles
}

int Bot_Interface_Shutdown(void) {
	// TODO: Shutdown Omnibot
	return 0;
}

void Bot_Interface_Update(void) {
	// TODO: Update bot AI each frame
}

void Bot_Interface_ConsoleCommand(void) {
	// TODO: Handle console commands
}

qboolean Bot_Util_AllowPush(int weaponId) {
	return qfalse;
}

qboolean Bot_Util_CheckForSuicide(struct gentity_s *ent) {
	return qfalse;
}

const char *_GetEntityName(struct gentity_s *_ent) {
	return "";
}

void Bot_Util_SendTrigger(struct gentity_s *_ent, struct gentity_s *_activator,
                          const char *_tagname, const char *_action) {
}

int Bot_WeaponGameToBot(int weapon) {
	return 0;
}

int Bot_TeamGameToBot(int team) {
	return 0;
}

int Bot_PlayerClassGameToBot(int playerClass) {
	return 0;
}

void Bot_Queue_EntityCreated(struct gentity_s *pEnt) {
}

void Bot_Event_EntityDeleted(struct gentity_s *pEnt) {
}

void Bot_Event_ClientConnected(int _client, qboolean _isbot) {
}

void Bot_Event_ClientDisConnected(int _client) {
}

void Bot_Event_ResetWeapons(int _client) {
}

void Bot_Event_AddWeapon(int _client, int _weaponId) {
}

void Bot_Event_RemoveWeapon(int _client, int _weaponId) {
}

void Bot_Event_TakeDamage(int _client, struct gentity_s *_ent) {
}

void Bot_Event_Death(int _client, struct gentity_s *_killer, const char *_meansofdeath) {
}

void Bot_Event_KilledSomeone(int _client, struct gentity_s *_victim, const char *_meansofdeath) {
}

void Bot_Event_Revived(int _client, struct gentity_s *_whodoneit) {
}

void Bot_Event_Healed(int _client, struct gentity_s *_whodoneit) {
}

void Bot_Event_ReceivedAmmo(int _client, struct gentity_s *_whodoneit) {
}

void Bot_Event_FireWeapon(int _client, int _weaponId, struct gentity_s *_projectile) {
}

void Bot_Event_PreTriggerMine(int _client, struct gentity_s *_mine) {
}

void Bot_Event_PostTriggerMine(int _client, struct gentity_s *_mine) {
}

void Bot_Event_MortarImpact(int _client, vec3_t _pos) {
}

void Bot_Event_Spectated(int _client, int _who) {
}

void Bot_Event_ChatMessage(int _client, struct gentity_s *_source, int _type, const char *_message) {
}

void Bot_Event_VoiceMacro(int _client, struct gentity_s *_source, int _type, const char *_message) {
}

void Bot_Event_Sound(struct gentity_s *_source, int _sndtype, const char *_name) {
}

void Bot_Event_FireTeamCreated(int _client, int _fireteamnum) {
}

void Bot_Event_FireTeamDestroyed(int _client) {
}

void Bot_Event_JoinedFireTeam(int _client, struct gentity_s *leader) {
}

void Bot_Event_LeftFireTeam(int _client) {
}

void Bot_Event_InviteFireTeam(int _inviter, int _invitee) {
}

void Bot_Event_FireTeam_Proposal(int _client, int _proposed) {
}

void Bot_Event_FireTeam_Warn(int _client, int _warned) {
}

void Bot_AddDynamiteGoal(struct gentity_s *_ent, int _team, const char *_tag) {
}

void Bot_AddFallenTeammateGoals(struct gentity_s *_teammate, int _team) {
}

void AddDeferredGoal(struct gentity_s *ent) {
}

void UpdateGoalEntity(struct gentity_s *oldent, struct gentity_s *newent) {
}

void GetEntityCenter(struct gentity_s *ent, vec3_t pos) {
	if (pos) {
		pos[0] = pos[1] = pos[2] = 0.0f;
	}
}

} // extern "C"

#endif // FEATURE_OMNIBOT
