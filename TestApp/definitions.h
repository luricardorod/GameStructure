#pragma once

#define ARRIVALMARGINERROR 1
#define GARRISONRADIUSENTRANCE 1

enum ENUMWEAPONS
{
	WEAPONS_SIZE
};
enum ENUMTYPES
{
	TYPES_SIZE
};
enum ENUMFACTION
{
	FACTIONS_SIZE
};
enum STATES
{
	STATEIDLE,//
	STATEMOVETO,//
	STATEATTACK,
	STATEDEAD,//
	STATEROTING,//
	STATERECOLLECT,
	STATEBUILD,
	STATEGARRISON,//
	COUNTSTATES
};