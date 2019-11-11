#include "stdafx.h"
#include "Functions.h"

void TheEnforcerMenu();
int ThenEnforcerTimer();
#define hookFunctionStart(Address, SaveStubAddress, Destination) Tools::hookFunctionStartEx(Address, SaveStubAddress, Destination);

#pragma region VM Execute Hooking
__declspec(naked) UINT64 VM_ExecuteStub(UINT64 r3)
{
	__asm
	{
		li r3, 1
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}
UINT64 VM_ExecuteHook(UINT64 r3)
{
	ThenEnforcerTimer();
	return VM_ExecuteStub(r3);
}
int frame_cache;
int ThenEnforcerTimer()
{
	if (frame_cache < GAMEPLAY::GET_FRAME_COUNT())
	{
		frame_cache = GAMEPLAY::GET_FRAME_COUNT();
		TheEnforcerMenu();
	}
	return frame_cache;
}
int __declspec(naked) VM_ExecuteStubFast(...)
{
	__asm
	{
		li r3, 3
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}
__int64 VM_ExecuteHookFast(__int64 r3, int r4, __int64 r5, __int64 r6)
{
	//Fast Loops
	return VM_ExecuteStubFast(r3, r4, r5, r6);
}
#pragma endregion
void Hook()
{

	otherLoop();
	monitorButtons();
	optionCount = 0;
	switch (submenu)
	{
#pragma region Main Menu
	case Main_Menu:
		addTitle("AMEngine: V3.3");
		addSubmenuOption("Player Options", Quick_Options);
		addSubmenuOption("Teleport Menu", Teleport_Options);
		addSubmenuOption("Online Players", Players_List);
		addSubmenuOption("All Players", All_Players);
		addSubmenuOption("Weapon Options", Weapon_Options);
		addSubmenuOption("Vehicle Spawner", Vehicle_Spawner);
		addSubmenuOption("Vehicle Menu", Vehicle_Options);
		addSubmenuOption("Creator Menu", Object_Spawner);
		addSubmenuOption("Ped Spawner", Ped_Options); //5
		addSubmenuOption("Ride Menu", Ride_Menu); //5
		addSubmenuOption("Model Changer", ModelOptions);
		addSubmenuOption("Misc Options", Misc_Options);
		break;
#pragma endregion
#pragma region All Players
	case All_Players:

		addTitle("All Players");
		addSubmenuOption("Particle Effect At All Players", ParticleEffectAtAllPlayers, "Particle Effect At All Players | Version 2.3");
		addSubmenuOption("Spawn Vehicles At All Players", SpawnVehiclesAtAllPlayers, "Spawn Vehicles At All Players | Version 2.3");
		addOption("Kill All Players");
		addBoolOption("Freeze All Players", Freeze_AllPlayers);
		addBoolOption("Freeze All Players Cars", Freeze_AllPlayersCars);
		addOption("Give All Players Weapons");
		addOption("Take All Players Weapons");
		addBoolOption("Player Name ESP", Toggle_featureNameESP);
		addBoolOption("Line ESP", Line_ESP);
		addBoolOption("Cash Drop All", neverwantedonlineall);
		addIntOption("Money Amount", &amount, 0, 999999999, true, true);
		addIntOption("Money Radius", &MoneyRange_, 0, 200, true, true);
		addFloatOption("Money Z Coord", &moneyzcoord, -255.0f, 255.0f, true);
		addOption("All Sesion Down");
		addBoolOption("Dragon Mode All Players", DragonMode3);
		addOption("Pole Dance All");
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
		{
			int i = 0;
			int Handle;
			Vector3 coords;
			for (i = 0; i<16; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle = PLAYER::GET_PLAYER_PED(i);
				coords = ENTITY::GET_ENTITY_COORDS(i, 1);
				if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
				FIRE::ADD_OWNED_EXPLOSION(i, coords.x, coords.y, coords.z, BLIMP, FLT_MAX, false, true, 1.0f);
			}
		} break;
		case 4: Freeze_AllPlayers = !Freeze_AllPlayers; break;
		case 5: Freeze_AllPlayersCars = !Freeze_AllPlayersCars; break;
		case 6:
		{
			int i = 0;
			int Handle2;
			for (i = 0; i<16; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle2 = PLAYER::GET_PLAYER_PED(i);
				if (!ENTITY::DOES_ENTITY_EXIST(Handle2)) continue;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x3656C8C1, 9999, 1); // stun gun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x99B507EA, 9999, 1); // knife
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x678B81B1, 9999, 1); // night stick
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x4E875F73, 9999, 1); // hammer
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x958A4A8F, 9999, 1); // bat
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x440E4788, 9999, 1); // golf club
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x84BD7BFD, 9999, 1); // crowbar
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x1B06D571, 9999, 5); // pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x5EF9FEC4, 9999, 1); // combat pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x22D8FE39, 9999, 1); // ap pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x99AEEB3B, 9999, 1); // pistol 50.
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x13532244, 9999, 1); // micro smg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x2BE6766B, 9999, 1); // smg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xEFE7E2DF, 9999, 1); // assault smg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xBFEFFF6D, 9999, 1); // assault rifle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x83BF0278, 9999, 1); // carbine rifle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xAF113F99, 9999, 1); // advanced rifle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x9D07F764, 9999, 1); // MG
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x7FD62962, 9999, 1); // combat mg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x1D073A89, 9999, 1); // pump shotgun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x7846A318, 9999, 1); // sawnoff shotgun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xE284C527, 9999, 1); // assault shotgun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x9D61E50F, 9999, 1); // bullpupshotgun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x05FC3C11, 9999, 1); // sniper
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x0C472FE2, 9999, 1); // heavy sniper
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xA284510B, 9999, 1); // grenade launcher
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xB1CA77B1, 9999, 1); // rpg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x42BF8A85, 9999, 1); // minigun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x93E220BD, 9999, 1); // grenades
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x2C3731D9, 9999, 1); // sticky bomb
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xFDBC8A50, 9999, 1); // smoke grenade
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x34A67B97, 9999, 1); // petrol can
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x060EC506, 9999, 1); // fire extinguisher
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x24B17070, 9999, 1); // moltovs
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x497FACC3, 9999, 1); // flare
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xFDBADCED, 9999, 1); // digiscanner
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x687652CE, 9999, 1); // stinger
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 600439132, 9999, 1); // ball
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xF9E6AA4B, 9999, 1); // bottle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x61012683, 9999, 1); // gusenerg
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xC0A3098D, 9999, 1); // special carbine
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xD205520E, 9999, 1); // heavy pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xBFD21232, 9999, 1); // sns pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x7F229F94, 9999, 1); // bullpup rifle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x92A27487, 9999, 1); // dagger
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x083839C4, 9999, 1); // vintage pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x7F7497E5, 9999, 1); // firework launcher
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xA89CB99E, 9999, 1); // musket
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x63AB0442, 9999, 1); // homing launcher
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xAB564B93, 9999, 1); // proxmine
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x787F0BB, 9999, 1); // snowball
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xC734385A, 9999, 1); // marksman rifle
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x47757124, 9999, 1); // flare gun
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xE232C28C, 9999, 1); // trash bag
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xDC4DB296, 9999, 1); // Marksman Pistol
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0xD8DF3C3C, 9999, 1); // Knuckle Duster
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(i), 0x0A3D4D34, 9999, 1);
			}
		} break;
		case 7:
		{
			int i = 0;
			int Handle3;
			for (i = 0; i<16; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle3 = PLAYER::GET_PLAYER_PED(i);
				if (!ENTITY::DOES_ENTITY_EXIST(Handle3)) continue;
				WEAPON::REMOVE_ALL_PED_WEAPONS(i, true);
			}
		} break;
		case 8: Toggle_featureNameESP = !Toggle_featureNameESP; break;
		case 9: Line_ESP = !Line_ESP; break;
		case 10: neverwantedonlineall = !neverwantedonlineall; break;
		case 13:
		{
			int i = 0;
			int Handle;
			for (i = 0; i < 18; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle = PLAYER::GET_PLAYER_PED(i);
				Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 pcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), 1);
				int hash;
				hash = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(mycoords.x, mycoords.y, mycoords.z, pcoords.x, pcoords.y, pcoords.z, 0, 0, hash, PLAYER::PLAYER_PED_ID(), 0, 0, 998);
			}
		} drawNotification("All Sesion Downed Success!"); break;
		case 14: DragonMode3 = !DragonMode3; break;
		case 15: AddAnimationOnline2("mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		}
		break;
#pragma endregion
#pragma region Spawn Vehicles At All Players
	case SpawnVehiclesAtAllPlayers:
		VehicleSpawner_Sprite();
		addTitle("Spawn Vehicles At All Players");
		addSubmenuOption("Favorites", Vehicle_FavoritesAll);
		addSubmenuOption("Super", Vehicle_SuperAll);
		addSubmenuOption("Sports", Vehicle_SportsAll);
		addSubmenuOption("Coupes", Vehicle_CoupesAll);
		addSubmenuOption("Sedans", Vehicle_SedansAll);
		addSubmenuOption("Emergency", Vehicle_EmergencyAll);
		addSubmenuOption("Off Road", Vehicle_OffRoadAll);
		addSubmenuOption("Muscle", Vehicle_MuscleAll);
		addSubmenuOption("SUVs", Vehicle_SUVsAll);
		addSubmenuOption("Motorcycles", Vehicle_MotorcyclesAll);
		addSubmenuOption("Helicopters", Vehicle_HelicoptersAll);
		addSubmenuOption("Planes", Vehicle_PlanesAll);
		addSubmenuOption("Commercial", Vehicle_CommercialAll);
		addSubmenuOption("Bicycles", Vehicle_BicyclesAll);
		addSubmenuOption("Boats", Vehicle_BoatsAll);
		addSubmenuOption("Industrial", Vehicle_IndustrialAll);
		addSubmenuOption("Utility", Vehicle_UtilityAll);
		addSubmenuOption("Trailers", Vehicle_TrailersAll);
		addSubmenuOption("Compacts", Vehicle_CompactsAll);
		addSubmenuOption("Military", Vehicle_MilitaryAll);
		addSubmenuOption("Service", Vehicle_ServiceAll);
		addSubmenuOption("Sports Classics", Vehicle_SportsClassicsAll);
		addSubmenuOption("Vans", Vehicle_VansAll);
		addSubmenuOption("Trains", Vehicle_TrainAll);
		break;
#pragma endregion
#pragma region Trains
	case Vehicle_TrainAll:
		VehicleSpawner_Sprite();
		addTitle("Trains");
		SpawnVehiclesAtAll("Freight Train", 0x3D6AAA9B);
		SpawnVehiclesAtAll("Train Well Car", 0x0AFD22A6);
		SpawnVehiclesAtAll("Train Container", 0x36DCFF98);
		SpawnVehiclesAtAll("Train Container Livery", 0x0E512E79);
		SpawnVehiclesAtAll("Train Boxcar", 0x264D9262);
		SpawnVehiclesAtAll("Freight Train Flatbed", 0xD1ABB666);
		SpawnVehiclesAtAll("Metro Train", 0x33C9E158);
		break;
#pragma endregion
#pragma region Favorites
	case Vehicle_FavoritesAll:
		VehicleSpawner_Sprite();
		addTitle("Favorites");
		SpawnVehiclesAtAll("Hydra", 0x39D6E83F);
		SpawnVehiclesAtAll("Lazer", 0xB39B0AE6);
		SpawnVehiclesAtAll("Hakuchou", 0x4B6C568A);
		SpawnVehiclesAtAll("Buzzard", 0x2F03547B);
		SpawnVehiclesAtAll("Tank", 0x2EA68690);
		SpawnVehiclesAtAll("FIB", 0x432EA949);
		SpawnVehiclesAtAll("FIB2", 0x9DC66994);
		SpawnVehiclesAtAll("Police", 0x71FA16EA);
		SpawnVehiclesAtAll("Police Buffalo", 0x9F05F101);
		SpawnVehiclesAtAll("Unmarked", 0x8A63C7B9);
		SpawnVehiclesAtAll("Jester2", 0xBE0E6126);
		SpawnVehiclesAtAll("Dubsta 6x6", 0xB6410173);
		SpawnVehiclesAtAll("Monster", 0xCD93A7DB);
		SpawnVehiclesAtAll("Mesa(Mercs)", 0x84F42E51);
		SpawnVehiclesAtAll("Phantom", 0x809AA4CB);
		SpawnVehiclesAtAll("Bus", 0xD577C962);
		SpawnVehiclesAtAll("Speeder", 0x0DC60D2B);
		SpawnVehiclesAtAll("Blimp", 0xF7004C86);
		SpawnVehiclesAtAll("Jumbo Jet", 0x3F119114);
		SpawnVehiclesAtAll("Insurgent", 0x9114EADA);
		SpawnVehiclesAtAll("Technical", 0x83051506);
		SpawnVehiclesAtAll("Cargo Plane", 0x15F27762);
		SpawnVehiclesAtAll("Dozer", 0x7074F39D);
		break;
#pragma endregion
#pragma region Super
	case Vehicle_SuperAll:
		VehicleSpawner_Sprite();
		addTitle("Super");
		SpawnVehiclesAtAll("Adder", 0xB779A091);
		SpawnVehiclesAtAll("Bullet", 0x9AE6DDA1);
		SpawnVehiclesAtAll("Cheetah", 0xB1D95DA0);
		SpawnVehiclesAtAll("EntityXF", 0xB2FE5CF9);
		SpawnVehiclesAtAll("Infernus", 0x18F25AC7);
		SpawnVehiclesAtAll("TurismoR", 0x185484E1);
		SpawnVehiclesAtAll("Vacca", 0x142E0DC3);
		SpawnVehiclesAtAll("Voltic", 0x9F4B77BE);
		SpawnVehiclesAtAll("Zentorno", 0xAC5DF515);
		SpawnVehiclesAtAll("Osiris", 0x767164D6);
		SpawnVehiclesAtAll("T20", 0x6322B39A);
		break;
#pragma endregion
#pragma region Sports
	case Vehicle_SportsAll:
		VehicleSpawner_Sprite();
		addTitle("Sports");
		SpawnVehiclesAtAll("9F", 0x3D8FA25C);
		SpawnVehiclesAtAll("9F Convertible", 0xA8E38B01);
		SpawnVehiclesAtAll("Alpha", 0x2DB8D1AA);
		SpawnVehiclesAtAll("Banshee", 0xC1E908D2);
		SpawnVehiclesAtAll("Buffalo", 0xEDD516C6);
		SpawnVehiclesAtAll("Franklins Buffalo", 0x2BEC3CBE);
		SpawnVehiclesAtAll("Carbonizzare", 0x7B8AB45F);
		SpawnVehiclesAtAll("Comet", 0xC1AE4D16);
		SpawnVehiclesAtAll("Coquette", 0x067BC037);
		SpawnVehiclesAtAll("Elegy", 0xDE3D9D22);
		SpawnVehiclesAtAll("Feltzer", 0x8911B9F5);
		SpawnVehiclesAtAll("FuroreGT", 0xBF1691E0);
		SpawnVehiclesAtAll("Fusilade", 0x1DC0BA53);
		SpawnVehiclesAtAll("Kumura", 0xAE2BFE94);
		SpawnVehiclesAtAll("Kumura2", 0x187D938D);
		SpawnVehiclesAtAll("Futo", 0x7836CE2F);
		SpawnVehiclesAtAll("Jester", 0xB2A716A3);
		SpawnVehiclesAtAll("Jester2", 0xBE0E6126);
		SpawnVehiclesAtAll("Khamelion", 0x206D1B68);
		SpawnVehiclesAtAll("Massacro", 0xF77ADE32);
		SpawnVehiclesAtAll("Massacro2", 0xDA5819A3);
		SpawnVehiclesAtAll("Penumbra", 0xE9805550);
		SpawnVehiclesAtAll("Rapid GT", 0x8CB29A14);
		SpawnVehiclesAtAll("Rapid GT Convertible", 0x679450AF);
		SpawnVehiclesAtAll("Schwartzer", 0xD37B7976);
		SpawnVehiclesAtAll("Sultan", 0x39DA2754);
		SpawnVehiclesAtAll("Surano", 0x16E478C1);
		break;
#pragma endregion
#pragma region Coupes
	case Vehicle_CoupesAll:
		VehicleSpawner_Sprite();
		addTitle("Coupes");
		SpawnVehiclesAtAll("Cognoscenti", 0x13B57D8A);
		SpawnVehiclesAtAll("Exemplar", 0xFFB15B5E);
		SpawnVehiclesAtAll("F620", 0xDCBCBE48);
		SpawnVehiclesAtAll("Felon", 0xE8A8BDA8);
		SpawnVehiclesAtAll("Felon2", 0xFAAD85EE);
		SpawnVehiclesAtAll("Jackal", 0xDAC67112);
		SpawnVehiclesAtAll("Oracle", 0x506434F6);
		SpawnVehiclesAtAll("Oracle2", 0xE18195B2);
		SpawnVehiclesAtAll("Sentinel", 0x50732C82);
		SpawnVehiclesAtAll("Sentinel2", 0x3412AE2D);
		SpawnVehiclesAtAll("Zion", 0xBD1B39C3);
		SpawnVehiclesAtAll("Zion2", 0xB8E2AE18);
		SpawnVehiclesAtAll("Windsor", 0x5E4327C8);
		break;
#pragma endregion
#pragma region Sedans
	case Vehicle_SedansAll:
		VehicleSpawner_Sprite();
		addTitle("Sedans");
		SpawnVehiclesAtAll("Asea", 0x94204D89);
		SpawnVehiclesAtAll("Snow Asea", 0x9441D8D5);
		SpawnVehiclesAtAll("Asterope", 0x8E9254FB);
		SpawnVehiclesAtAll("Emperor", 0xD7278283);
		SpawnVehiclesAtAll("Rusty Emperor", 0x8FC3AADC);
		SpawnVehiclesAtAll("Snow Emperor", 0xB5FCF74E);
		SpawnVehiclesAtAll("Fugitive", 0x71CB2FFB);
		SpawnVehiclesAtAll("Glendale", 0x047A6BC1);
		SpawnVehiclesAtAll("Ingot", 0xB3206692);
		SpawnVehiclesAtAll("Intruder", 0x34DD8AA1);
		SpawnVehiclesAtAll("Premier", 0x8FB66F9B);
		SpawnVehiclesAtAll("Primo", 0xBB6B404F);
		SpawnVehiclesAtAll("Regina", 0xFF22D208);
		SpawnVehiclesAtAll("Romero Hearse", 0x2560B2FC);
		SpawnVehiclesAtAll("Schafter", 0xB52B5113);
		SpawnVehiclesAtAll("Stanier", 0xA7EDE74D);
		SpawnVehiclesAtAll("Stratum", 0x66B4FC45);
		SpawnVehiclesAtAll("Stretch", 0x8B13F083);
		SpawnVehiclesAtAll("Super Diamond", 0x42F2ED16);
		SpawnVehiclesAtAll("Surge", 0x8F0E3594);
		SpawnVehiclesAtAll("Tailgater", 0xC3DDFDCE);
		SpawnVehiclesAtAll("Warrener", 0x51D83328);
		SpawnVehiclesAtAll("Washington", 0x69F06B57);
		break;
#pragma endregion
#pragma region Emergency
	case Vehicle_EmergencyAll:
		VehicleSpawner_Sprite();
		addTitle("Emergency");
		SpawnVehiclesAtAll("Ambulance", 0x45D56ADA);
		SpawnVehiclesAtAll("FIB", 0x432EA949);
		SpawnVehiclesAtAll("FIB2", 0x9DC66994);
		SpawnVehiclesAtAll("Fire Truck", 0x73920F8E);
		SpawnVehiclesAtAll("Life Guard", 0x1BF8D381);
		SpawnVehiclesAtAll("Park Ranger", 0x2C33B46E);
		SpawnVehiclesAtAll("Police Bike", 0xFDEFAEC3);
		SpawnVehiclesAtAll("Police Cruiser", 0x79FBB0C5);
		SpawnVehiclesAtAll("Police", 0x71FA16EA);
		SpawnVehiclesAtAll("Police Buffalo", 0x9F05F101);
		SpawnVehiclesAtAll("Prison Bus", 0x885F3671);
		SpawnVehiclesAtAll("Riot", 0xB822A1AA);
		SpawnVehiclesAtAll("Police Van", 0x1B38E955);
		SpawnVehiclesAtAll("Sheriff Cruiser", 0x9BAA707C);
		SpawnVehiclesAtAll("Sheriff SUV", 0x72935408);
		SpawnVehiclesAtAll("Snow Police Rancher", 0xA46462F7);
		SpawnVehiclesAtAll("Snow Police Esperanto", 0x95F4C618);
		SpawnVehiclesAtAll("Unmarked", 0x8A63C7B9);
		break;
#pragma endregion
#pragma region OffRoad
	case Vehicle_OffRoadAll:
		VehicleSpawner_Sprite();
		addTitle("Off Road");
		SpawnVehiclesAtAll("Brawler", 0xA7CE1BC5);
		SpawnVehiclesAtAll("Bifta", 0xEB298297);
		SpawnVehiclesAtAll("Blazer", 0x8125BCF9);
		SpawnVehiclesAtAll("Lifeguard Blazer", 0xFD231729);
		SpawnVehiclesAtAll("Trevors Blazer", 0xFD231729);
		SpawnVehiclesAtAll("Bodhi", 0xAA699BB6);
		SpawnVehiclesAtAll("Dubsta 6x6", 0xB6410173);
		SpawnVehiclesAtAll("Dune", 0x9CF21E0F);
		SpawnVehiclesAtAll("Duneloader", 0x698521E3);
		SpawnVehiclesAtAll("Injection", 0x432AA566);
		SpawnVehiclesAtAll("Kalahari", 0x05852838);
		SpawnVehiclesAtAll("Monster", 0xCD93A7DB);
		SpawnVehiclesAtAll("Mesa(Mercs)", 0x84F42E51);
		SpawnVehiclesAtAll("RancherXL", 0x6210CBB0);
		SpawnVehiclesAtAll("Rusty Rebel", 0xB802DD46);
		SpawnVehiclesAtAll("Clean Rebel", 0x8612B64B);
		SpawnVehiclesAtAll("SandkingSWB", 0x3AF8C345);
		SpawnVehiclesAtAll("SandkingXL", 0xB9210FD0);
		SpawnVehiclesAtAll("Snow Rancher", 0x7341576B);
		SpawnVehiclesAtAll("Space Docker", 0x1FD824AF);
		SpawnVehiclesAtAll("Insurgent", 0x9114EADA);
		SpawnVehiclesAtAll("Insurgent2", 0x7B7E56F0);
		break;
#pragma endregion
#pragma region Muscle
	case Vehicle_MuscleAll:
		VehicleSpawner_Sprite();
		addTitle("Muscle");
		SpawnVehiclesAtAll("Chino", 0x14D69010);
		SpawnVehiclesAtAll("Blackfin", 0x2EC385FE);
		SpawnVehiclesAtAll("Blade", 0xB820ED5E);
		SpawnVehiclesAtAll("Buccaneer", 0xD756460C);
		SpawnVehiclesAtAll("Dominator", 0x04CE68AC);
		SpawnVehiclesAtAll("Gauntlet", 0x94B395C5);
		SpawnVehiclesAtAll("Hotknife", 0x0239E390);
		SpawnVehiclesAtAll("Phoenix", 0x831A21D5);
		SpawnVehiclesAtAll("Picador", 0x59E0FBF3);
		SpawnVehiclesAtAll("Rat Loader", 0xD83C13CE);
		SpawnVehiclesAtAll("Rat Loader2", 0xDCE1D9F7);
		SpawnVehiclesAtAll("Ruiner", 0xF26CEFF9);
		SpawnVehiclesAtAll("SabreGT", 0x9B909C94);
		SpawnVehiclesAtAll("SlamVan", 0x2B7F9DE3);
		SpawnVehiclesAtAll("Vigero", 0xCEC6B9B7);
		SpawnVehiclesAtAll("Voodoo", 0x1F3766E3);
		SpawnVehiclesAtAll("Slamvan2", 0x31ADBBFC);
		SpawnVehiclesAtAll("Virgo", 0xE2504942);
		break;
#pragma endregion
#pragma region SUVs
	case Vehicle_SUVsAll:
		VehicleSpawner_Sprite();
		addTitle("SUVs");
		SpawnVehiclesAtAll("Baller", 0xCFCA3668);
		SpawnVehiclesAtAll("Baller2", 0x08852855);
		SpawnVehiclesAtAll("BeeJayXL", 0x32B29A4B);
		SpawnVehiclesAtAll("Old Cavalcade", 0x779F23AA);
		SpawnVehiclesAtAll("New Cavalcade", 0xD0EB2BE5);
		SpawnVehiclesAtAll("Dubsta", 0x462FE277);
		SpawnVehiclesAtAll("Dubsta2", 0xE882E5F6);
		SpawnVehiclesAtAll("FQ2", 0xBC32A33B);
		SpawnVehiclesAtAll("Granger", 0x9628879C);
		SpawnVehiclesAtAll("Gresley", 0xA3FC0F4D);
		SpawnVehiclesAtAll("Habanero", 0x34B7390F);
		SpawnVehiclesAtAll("HuntleyS", 0x1D06D681);
		SpawnVehiclesAtAll("Landstalker", 0x4BA4E8DC);
		SpawnVehiclesAtAll("Mesa", 0x36848602);
		SpawnVehiclesAtAll("Snow Mesa", 0xD36A4B44);
		SpawnVehiclesAtAll("Patriot", 0xCFCFEB3B);
		SpawnVehiclesAtAll("Radius", 0x9D96B45B);
		SpawnVehiclesAtAll("Rocoto", 0x7F5C91F1);
		SpawnVehiclesAtAll("Seminole", 0x48CECED3);
		SpawnVehiclesAtAll("Serrano", 0x4FB1A214);
		break;
#pragma endregion
#pragma region Motorcycles
	case Vehicle_MotorcyclesAll:
		VehicleSpawner_Sprite();
		addTitle("Motorcycles");
		SpawnVehiclesAtAll("Vindicator", 0xAF599F01);
		SpawnVehiclesAtAll("Akuma", 0x63ABADE7);
		SpawnVehiclesAtAll("Bagger", 0x806B9CC3);
		SpawnVehiclesAtAll("Bati801", 0xF9300CC5);
		SpawnVehiclesAtAll("Bati801RR", 0xCADD5D2D);
		SpawnVehiclesAtAll("Carbon RS", 0x00ABB0C0);
		SpawnVehiclesAtAll("Daemon", 0x77934CEE);
		SpawnVehiclesAtAll("DoubleT", 0x9C669788);
		SpawnVehiclesAtAll("Faggio", 0x0350D1AB);
		SpawnVehiclesAtAll("Hakuchou", 0x4B6C568A);
		SpawnVehiclesAtAll("Hexer", 0x11F76C14);
		SpawnVehiclesAtAll("Lectro", 0x26321E67);
		SpawnVehiclesAtAll("Enduro", 0x6882FA73);
		SpawnVehiclesAtAll("Innovation", 0x44C4E977);
		SpawnVehiclesAtAll("Nemesis", 0xDA288376);
		SpawnVehiclesAtAll("PCJ600", 0xC9CEAF06);
		SpawnVehiclesAtAll("Ruffian", 0xCABD11E8);
		SpawnVehiclesAtAll("Sanchez", 0x2EF89E46);
		SpawnVehiclesAtAll("Sanchez2", 0xA960B13E);
		SpawnVehiclesAtAll("Sovereign", 0x2C509634);
		SpawnVehiclesAtAll("Thrust", 0x6D6F8F43);
		SpawnVehiclesAtAll("Vader", 0xF79A00F7);
		break;
#pragma endregion
#pragma region Helicopters
	case Vehicle_HelicoptersAll:
		VehicleSpawner_Sprite();
		addTitle("Helicopters");
		SpawnVehiclesAtAll("Annihilator", 0x31F0B376);
		SpawnVehiclesAtAll("Buzzard(No Guns)", 0x2C75F0DD);
		SpawnVehiclesAtAll("Buzzard", 0x2F03547B);
		SpawnVehiclesAtAll("Cargobob", 0xFCFCB68B);
		SpawnVehiclesAtAll("Medic Cargobob", 0x60A7EA10);
		SpawnVehiclesAtAll("Trevors CargoBob", 0x53174EEF);
		SpawnVehiclesAtAll("Frogger", 0x2C634FBD);
		SpawnVehiclesAtAll("FIB/Trevors Frogger", 0x742E9AC0);
		SpawnVehiclesAtAll("Maverick", 0x9D0450CA);
		SpawnVehiclesAtAll("Police Maverick", 0x1517D4D9);
		SpawnVehiclesAtAll("Skylift", 0x3E48BF23);
		SpawnVehiclesAtAll("Swift", 0xEBC24DF2);
		SpawnVehiclesAtAll("Valkyrie", 0xA09E15FD);
		SpawnVehiclesAtAll("Swift(Gold)", 0x4019CB4C);
		SpawnVehiclesAtAll("Savage", 0xFB133A17);
		break;
#pragma endregion
#pragma region Planes
	case Vehicle_PlanesAll:
		VehicleSpawner_Sprite();
		//Planes_Sprite();
		addTitle("Planes");
		SpawnVehiclesAtAll("Blimp", 0xF7004C86);
		SpawnVehiclesAtAll("Besra", 0x6CBD1D6D);
		SpawnVehiclesAtAll("Cargo Plane", 0x15F27762);
		SpawnVehiclesAtAll("Cuban 800", 0xD9927FE3);
		SpawnVehiclesAtAll("Duster", 0x39D6779E);
		SpawnVehiclesAtAll("Jumbo Jet", 0x3F119114);
		SpawnVehiclesAtAll("Luxor", 0x250B0C5E);
		SpawnVehiclesAtAll("Luxor(Gold)", 0xB79F589E);
		SpawnVehiclesAtAll("Mallard", 0x81794C70);
		SpawnVehiclesAtAll("Mammatus", 0x97E55D11);
		SpawnVehiclesAtAll("MilJet", 0x09D80F93);
		SpawnVehiclesAtAll("Lazer", 0xB39B0AE6);
		SpawnVehiclesAtAll("Shamal", 0xB79C1BF5);
		SpawnVehiclesAtAll("Titan", 0x761E2AD3);
		SpawnVehiclesAtAll("Velum", 0x9C429B6A);
		SpawnVehiclesAtAll("Velum2", 0x403820E8);
		SpawnVehiclesAtAll("Vestra", 0x4FF77E37);
		break;
#pragma endregion
#pragma region Commercial
	case Vehicle_CommercialAll:
		VehicleSpawner_Sprite();
		addTitle("Commercial");
		SpawnVehiclesAtAll("Benson", 0x7A61B330);
		SpawnVehiclesAtAll("Biff", 0x32B91AE8);
		SpawnVehiclesAtAll("Hauler", 0x5A82F9AE);
		SpawnVehiclesAtAll("Mule", 0x35ED670B);
		SpawnVehiclesAtAll("Mule2", 0x85A5B471);
		SpawnVehiclesAtAll("Packer", 0x21EEE87D);
		SpawnVehiclesAtAll("Phantom", 0x809AA4CB);
		SpawnVehiclesAtAll("Pounder", 0x7DE35E7D);
		SpawnVehiclesAtAll("Stockade", 0x6827CF72);
		SpawnVehiclesAtAll("Snow Stockade", 0xF337AB36);
		break;
#pragma endregion
#pragma region Bicycles
	case Vehicle_BicyclesAll:
		VehicleSpawner_Sprite();
		//Bike_Sprite();
		addTitle("Bicycles");
		SpawnVehiclesAtAll("BMX", 0x43779C54);
		SpawnVehiclesAtAll("Scorcher", 0xF4E1AA15);
		SpawnVehiclesAtAll("Cruiser", 0x1ABA13B5);
		SpawnVehiclesAtAll("Fixter", 0xCE23D3BF);
		SpawnVehiclesAtAll("TriCycles", 0xE823FB48);
		SpawnVehiclesAtAll("Whippet", 0x4339CD69);
		SpawnVehiclesAtAll("Endurex", 0xB67597EC);
		break;
#pragma endregion
#pragma region Boats
	case Vehicle_BoatsAll:
		VehicleSpawner_Sprite();
		addTitle("Boats");
		SpawnVehiclesAtAll("Dinghy", 0x3D961290);
		SpawnVehiclesAtAll("Dinghy3", 0x1E5E54EA);
		SpawnVehiclesAtAll("Jetmax", 0x33581161);
		SpawnVehiclesAtAll("Marquis", 0xC1CE1183);
		SpawnVehiclesAtAll("Seashark", 0xC2974024);
		SpawnVehiclesAtAll("Lifeguard Seashark", 0xDB4388E4);
		SpawnVehiclesAtAll("Squalo", 0x17DF5EC2);
		SpawnVehiclesAtAll("Suntrap", 0xEF2295C9);
		SpawnVehiclesAtAll("Tropic", 0x1149422F);
		SpawnVehiclesAtAll("Speeder", 0x0DC60D2B);
		SpawnVehiclesAtAll("Police Boat", 0xE2E7D4AB);
		SpawnVehiclesAtAll("Submersible", 0x2DFF622F);
		SpawnVehiclesAtAll("Toro", 0x3FD5AA2F);
		break;
#pragma endregion
#pragma region Industrial
	case Vehicle_IndustrialAll:
		VehicleSpawner_Sprite();
		addTitle("Industrial");
		SpawnVehiclesAtAll("Dock Handler", 0x1A7FCEFA);
		SpawnVehiclesAtAll("Dozer", 0x7074F39D);
		SpawnVehiclesAtAll("Dump", 0x810369E2);
		SpawnVehiclesAtAll("Flatbed", 0x50B0215A);
		SpawnVehiclesAtAll("Mixer", 0xD138A6BB);
		SpawnVehiclesAtAll("Mixer2", 0x1C534995);
		SpawnVehiclesAtAll("Rubble", 0x9A5B1DCC);
		SpawnVehiclesAtAll("Tipper", 0x02E19879);
		SpawnVehiclesAtAll("Tipper2", 0xC7824E5E);
		SpawnVehiclesAtAll("Guardian", 0x825A9F4C);
		break;
#pragma endregion
#pragma region Utility
	case Vehicle_UtilityAll:
		VehicleSpawner_Sprite();
		addTitle("Utility");
		SpawnVehiclesAtAll("Airtug", 0x5D0AAC8F);
		SpawnVehiclesAtAll("Bison", 0xFEFD644F);
		SpawnVehiclesAtAll("Bison2", 0x7B8297C5);
		SpawnVehiclesAtAll("Bison3", 0x67B3F020);
		SpawnVehiclesAtAll("BobcatXL", 0x3FC5D440);
		SpawnVehiclesAtAll("Caddy", 0x44623884);
		SpawnVehiclesAtAll("Caddy2", 0xDFF0594C);
		SpawnVehiclesAtAll("Cutter", 0xC3FBA120);
		SpawnVehiclesAtAll("Docktug", 0xCB44B1CA);
		SpawnVehiclesAtAll("Fieldmaster", 0x843B73DE);
		SpawnVehiclesAtAll("Forklift", 0x58E49664);
		SpawnVehiclesAtAll("Lawn Mower", 0x6A4BD8F6);
		SpawnVehiclesAtAll("Ripley", 0xCD935EF9);
		SpawnVehiclesAtAll("Sadler", 0xDC434E51);
		SpawnVehiclesAtAll("Snow Sadler", 0x2BC345D1);
		SpawnVehiclesAtAll("Scrap Truck", 0x9A9FD3DF);
		SpawnVehiclesAtAll("Small Tow Truck", 0xE5A2D6C6);
		SpawnVehiclesAtAll("Big Tow Truck", 0xB12314E0);
		SpawnVehiclesAtAll("Tractor", 0x61D6BA8C);
		SpawnVehiclesAtAll("Snow Tractor", 0x562A97BD);
		SpawnVehiclesAtAll("Utility Truck", 0x1ED0A534);
		SpawnVehiclesAtAll("Utility Truck2", 0x34E6BF6B);
		SpawnVehiclesAtAll("Utility Truck3", 0x7F2153DF);
		break;
#pragma endregion
#pragma region Trailers
	case Vehicle_TrailersAll:
		VehicleSpawner_Sprite();
		addTitle("Trailers");
		SpawnVehiclesAtAll("Car Carrier", 0x7BE032C6);
		SpawnVehiclesAtAll("Marquis Trailer", 0x6A59902D);
		SpawnVehiclesAtAll("Super Car Carrier", 0x7CAB34D0);
		SpawnVehiclesAtAll("Log Trailer", 0x782A236D);
		SpawnVehiclesAtAll("Metal Trailer", 0xCBB2BE0E);
		SpawnVehiclesAtAll("Random Ad Trailer", 0xA1DA3C91);
		SpawnVehiclesAtAll("Big Goods Trailer", 0x8548036D);
		SpawnVehiclesAtAll("Flatbed Trailer", 0xAF62F6B2);
		SpawnVehiclesAtAll("Fame Or Shame Trailer", 0x967620BE);
		SpawnVehiclesAtAll("Army Trailer", 0xA7FF33F5);
		SpawnVehiclesAtAll("Army Trailer2", 0x9E6B14D6);
		SpawnVehiclesAtAll("Army Trailer3", 0xB8081009);
		SpawnVehiclesAtAll("Boat Trailer", 0x1F3D44B5);
		SpawnVehiclesAtAll("Dock Trailer", 0x806EFBEE);
		SpawnVehiclesAtAll("Freight Trailer", 0xD1ABB666);
		SpawnVehiclesAtAll("Construction Trailer", 0x2A72BEAB);
		SpawnVehiclesAtAll("Tanker Trailer", 0xD46F4737);
		SpawnVehiclesAtAll("Tanker Trailer2", 0x74998082);
		break;
#pragma endregion
#pragma region Compacts
	case Vehicle_CompactsAll:
		VehicleSpawner_Sprite();
		addTitle("Compacts");
		SpawnVehiclesAtAll("Blista", 0xEB70965F);
		SpawnVehiclesAtAll("Dilettante", 0xBC993509);
		SpawnVehiclesAtAll("Issi", 0xB9CB3B69);
		SpawnVehiclesAtAll("Panto", 0xE644E480);
		SpawnVehiclesAtAll("Prairie", 0xA988D3A2);
		SpawnVehiclesAtAll("Rhapsody", 0x322CF98F);
		break;
#pragma endregion
#pragma region Military
	case Vehicle_MilitaryAll:
		VehicleSpawner_Sprite();
		addTitle("Military");
		SpawnVehiclesAtAll("Barracks", 0xCEEA3F4B);
		SpawnVehiclesAtAll("Barracks Semi", 0x4008EABB);
		SpawnVehiclesAtAll("Barracks3", 0x2592B5CF);
		SpawnVehiclesAtAll("Crusader", 0x132D5A1A);
		SpawnVehiclesAtAll("Tank", 0x2EA68690);
		break;
#pragma endregion
#pragma region Service
	case Vehicle_ServiceAll:
		VehicleSpawner_Sprite();
		addTitle("Service");
		SpawnVehiclesAtAll("Airport Bus", 0x4C80EB0E);
		SpawnVehiclesAtAll("Bus", 0xD577C962);
		SpawnVehiclesAtAll("Dashound", 0x84718D34);
		SpawnVehiclesAtAll("Shuttle", 0xBE819C63);
		SpawnVehiclesAtAll("Taxi", 0xC703DB5F);
		SpawnVehiclesAtAll("Tourbus", 0x73B1C3CB);
		SpawnVehiclesAtAll("Trashmaster", 0x72435A19);
		SpawnVehiclesAtAll("Trash2", 0x72435A19);
		break;
#pragma endregion
#pragma region SportsClassics
	case Vehicle_SportsClassicsAll:
		VehicleSpawner_Sprite();
		addTitle("Sports Classics");
		SpawnVehiclesAtAll("Coquette Classic", 0x3C4E2113);
		SpawnVehiclesAtAll("JB700", 0x3EAB5555);
		SpawnVehiclesAtAll("Manana", 0x81634188);
		SpawnVehiclesAtAll("Monroe", 0xE62B361B);
		SpawnVehiclesAtAll("Peyote", 0x6D19CCBC);
		SpawnVehiclesAtAll("Pigalle", 0x404B6381);
		SpawnVehiclesAtAll("Roosevelt", 0x06FF6914);
		SpawnVehiclesAtAll("Stinger", 0x5C23AF9B);
		SpawnVehiclesAtAll("StingerGT", 0x82E499FA);
		SpawnVehiclesAtAll("Tornado", 0x1BB290BC);
		SpawnVehiclesAtAll("Tornado2", 0x5B42A5C4);
		SpawnVehiclesAtAll("Tornado3", 0x690A4153);
		SpawnVehiclesAtAll("Tornado4", 0x86CF7CDD);
		SpawnVehiclesAtAll("ZType", 0x2D3BD401);
		SpawnVehiclesAtAll("Stirling GT", 0xA29D6D10);
		SpawnVehiclesAtAll("Casco", 0x3822BDFE);
		break;
#pragma endregion
#pragma region Vans
	case Vehicle_VansAll:
		VehicleSpawner_Sprite();
		addTitle("Vans");
		SpawnVehiclesAtAll("Boxville", 0x898ECCEA);
		SpawnVehiclesAtAll("Boxville2", 0xF21B33BE);
		SpawnVehiclesAtAll("Boxville3", 0x07405E08);
		SpawnVehiclesAtAll("Boxville4", 0x1A79847A);
		SpawnVehiclesAtAll("Burrito", 0xAFBB2CA4);
		SpawnVehiclesAtAll("Burrito2", 0xC9E8FF76);
		SpawnVehiclesAtAll("Burrito3", 0x98171BD3);
		SpawnVehiclesAtAll("Burrito4", 0x353B561D);
		SpawnVehiclesAtAll("Snow Burrito", 0x437CF2A0);
		SpawnVehiclesAtAll("Gang Burrito", 0x97FA4F36);
		SpawnVehiclesAtAll("Gang Burrito2", 0x11AA0E14);
		SpawnVehiclesAtAll("Camper", 0x6FD95F68);
		SpawnVehiclesAtAll("Journey", 0xF8D48E7A);
		SpawnVehiclesAtAll("Minivan", 0xED7EADA4);
		SpawnVehiclesAtAll("Paradise", 0x58B3979C);
		SpawnVehiclesAtAll("Pony", 0xF8DE29A8);
		SpawnVehiclesAtAll("Weed Van", 0x38408341);
		SpawnVehiclesAtAll("Weazel News", 0x4543B74D);
		SpawnVehiclesAtAll("Deludamol", 0x961AFEF7);
		SpawnVehiclesAtAll("Speedo", 0xCFB3870C);
		SpawnVehiclesAtAll("Clown Van", 0x2B6DC64A);
		SpawnVehiclesAtAll("Surfer", 0x29B0DA97);
		SpawnVehiclesAtAll("Surfer2", 0xB1D80E06);
		SpawnVehiclesAtAll("Taco Van", 0x744CA80D);
		SpawnVehiclesAtAll("Youga", 0x03E5F6B8);
		break;
#pragma endregion
#pragma region Particle Effect At All Players
	case ParticleEffectAtAllPlayers:

		addTitle("Particle Effect At All Players");
		addSubmenuOption("Ghost Rider Menu", Ghost_Rider_Menu);
		addParticleEffectAllOption("Boosh", "scr_trevor1", "scr_trev1_trailer_boosh"); //2
		addParticleEffectAllOption("Splash", "scr_trevor1", "scr_trev1_trailer_splash"); //3
		addParticleEffectAllOption("Spiked", "scr_trevor1", "scr_bigscore_tyre_spiked"); //4
		addParticleEffectAllOption("Pink Smoke", "scr_familyscenem", "scr_meth_pipe_smoke"); //5
		addParticleEffectAllOption("Clown Appears", "scr_rcbarry2", "scr_clown_appears"); //6
		addParticleEffectAllOption("Clown Death", "scr_rcbarry2", "scr_clown_death"); //7
		addParticleEffectAllOption("Blood Impact", "scr_solomon3", "scr_trev4_747_blood_impact"); //8
		addParticleEffectAllOption("Engine Debris", "scr_solomon3", "scr_trev4_747_engine_debris"); //9
		addParticleEffectAllOption("Firework Fountain", "scr_indep_fireworks", "scr_indep_firework_fountain"); //10
		addParticleEffectAllOption("Firework Shotburst", "scr_indep_fireworks", "scr_indep_firework_shotburst"); //11
		addParticleEffectAllOption("Firework Starburst", "scr_indep_fireworks", "scr_indep_firework_starburst"); //12
		addParticleEffectAllOption("Firework Trailburst", "scr_indep_fireworks", "scr_indep_firework_trailburst"); //13
		addParticleEffectAllOption("Alien Disintegrate", "scr_rcbarry1", "scr_alien_disintegrate"); //14
		addParticleEffectAllOption("Alien Teleport", "scr_rcbarry1", "scr_alien_teleport"); //15
		addParticleEffectAllOption("Trailer Sparks", "scr_family4", "scr_fam4_trailer_sparks"); //16
		addParticleEffectAllOption("Car Impact", "scr_exile2", "scr_ex2_car_impact"); //17
		addParticleEffectAllOption("Water Dinghy Wash", "scr_exile3", "scr_ex3_water_dinghy_wash"); //18
		addParticleEffectAllOption("Bank Notes", "scr_paletoscore", "scr_paleto_banknotes"); //19
		addParticleEffectAllOption("Blow Torch", "scr_paletoscore", "cs_paleto_blowtorch"); //20
		addParticleEffectAllOption("Bike Burnout", "scr_jewelheist", "scr_jew_biKe_burnout"); //21
		addParticleEffectAllOption("Cab Smash", "scr_jewelheist", "scr_jewel_cab_smash"); //22
		addParticleEffectAllOption("Tyre Spiked", "scr_carsteal4", "scr_carsteal5_tyre_spiked"); //23
		addParticleEffectAllOption("Muzzle Flash", "scr_carsteal4", "scr_carsteal5_car_muzzle_flash"); //24
		addParticleEffectAllOption("Wheel Burnout", "scr_carsteal4", "scr_carsteal4_wheel_burnout"); //25
		addParticleEffectAllOption("Tyre Spiked", "scr_carsteal3", "scr_carsteal4_tyre_spiked"); //26
		addParticleEffectAllOption("Hotbox Trail", "scr_oddjobtaxi", "scr_ojtaxi_hotbox_trail"); //27
		addParticleEffectAllOption("Train Sparks", "scr_oddjobtowtruck", "scr_ojtt_train_sparks"); //28
		addParticleEffectAllOption("Cig Smoke Car", "scr_mp_cig", "ent_anim_cig_smoke_car"); //29
		addParticleEffectAllOption("Truck Crash", "scr_fbi4", "scr_fbi4_trucks_crash"); //30
		break;
#pragma endregion
#pragma region Ride Menu
	case Ride_Menu:

		addTitle("Ride Menu");
		addSubmenuOption("Deer Menu", Deer_Menu);
		addSubmenuOption("Pig Menu", Pig_Menu);
		addSubmenuOption("Boar Menu", Boar_Menu);
		addSubmenuOption("Cow Menu", Cow_Menu);
		addSubmenuOption("Shark Menu", Shark_Menu);
		break;
#pragma endregion
#pragma region Deer Menu
	case Deer_Menu:

		addTitle("Deer Menu");
		AddOptionDeerSpawner("Spawn Deer", -664053099);
		addOption("Attach To Deer");
		addBoolOption("Control Deer", ControllDeer);
		addOption("Detach From Deer");
		//addOption("Delete Deer");
		switch (getOption())
		{
		case 1: break;
		case 2:
			int spine;
			spine = rideDeer_pedBone(DeerID, 24816);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), DeerID, spine, -0.3f, 0.0f, +0.3f, 0.0f, 0.0f, 90.0f, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 3: ControllDeer = !ControllDeer;
			break;
		case 4: ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			break;
		}
		break;
#pragma endregion
#pragma region Pig Menu
	case Pig_Menu:

		addTitle("Pig Menu");
		AddOptionPigSpawner("Spawn Pig", -1323586730);
		addOption("Attach To Pig");
		addBoolOption("Control Pig", ControllPig);
		addOption("Detach From Pig");
		switch (getOption())
		{
		case 1: break;
		case 2:
			int spine;
			spine = rideDeer_pedBone(PigID, 24816);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PigID, spine, -0.3f, 0.0f, +0.3f, 0.0f, 0.0f, 90.0f, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 3: ControllPig = !ControllPig;
			break;
		case 4: ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			break;
		}
		break;
#pragma endregion
#pragma region Boar Menu
	case Boar_Menu:

		addTitle("Boar Menu");
		AddOptionBoarSpawner("Spawn Boar", -832573324);
		addOption("Attach To Boar");
		addBoolOption("Control Boar", ControllBoar);
		addOption("Detach From Boar");
		switch (getOption())
		{
		case 1: break;
		case 2:
			int spine;
			spine = rideDeer_pedBone(BoarID, 24816);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), BoarID, spine, -0.3f, 0.0f, +0.3f, 0.0f, 0.0f, 90.0f, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 3: ControllBoar = !ControllBoar;
			break;
		case 4: ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			break;
		}
		break;
#pragma endregion
#pragma region Cow Menu
	case Cow_Menu:

		addTitle("Cow Menu");
		AddOptionCowSpawner("Spawn Cow", -50684386);
		addOption("Attach To Cow");
		addBoolOption("Control Cow", ControllCow);
		addOption("Detach From Cow");
		switch (getOption())
		{
		case 1: break;
		case 2:
			int spine;
			spine = rideDeer_pedBone(CowID, 24816);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), CowID, spine, -0.3f, 0.0f, +0.3f, 0.0f, 0.0f, 90.0f, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 3: ControllCow = !ControllCow;
			break;
		case 4: ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			break;
		}
		break;
#pragma endregion
#pragma region Shark Menu
	case Shark_Menu:

		addTitle("Shark Menu");
		AddOptionSharkSpawner("Spawn Shark", 113504370);
		addOption("Attach To Shark");
		addBoolOption("Control Shark", ControllShark);
		addOption("Detach From Shark");
		switch (getOption())
		{
		case 1: break;
		case 2:
			int spine;
			spine = rideDeer_pedBone(SharkID, 24816);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), SharkID, spine, -0.3f, 0.0f, +0.3f, 0.0f, 0.0f, 90.0f, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 3: ControllShark = !ControllShark;
			break;
		case 4: ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			break;
		}
		break;
#pragma endregion
#pragma region Quick Options
	case Quick_Options:

		addTitle("Player Options");
		addSubmenuOption("Vision Options", Vision_Options); //1
		addSubmenuOption("Animation Menu", Animations_Menu); //2
		addSubmenuOption("Scenario Menu", Scenario_Menu); //3
		addBoolOption("Recovery", advRecovery);
		addOption("Normal Male Mode"); //10
		addOption("Normal Female"); //11
		addOption("Drunk Mode"); //12
		addOption("Remove Attached Objects");
		addBoolOption("Malicious Protection", ProtectionTest6); //16
		addBoolOption("Godmode Loop", PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID())); //1
		addOption("Give All Weapons"); //2
		addBoolOption("Never Wanted", neverwanted); //3
		addBoolOption("Invisibility", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); //4
		addBoolOption("Super Jump", superjump); //5
		addBoolOption("Super Run", superrun); //6
		addBoolOption("Swim Fast", SwimFast); //7
		addBoolOption("Super Punch", SuperPunch); //8
		addIntOption("Set Alpha", &Set_AlphaTo, 0, 255, true); //9
		addBoolOption("Heat Vision", ToggleHeatVision); //10
		addBoolOption("Night Vision", ToggleNightVision); //11
		addBoolOption("Slow Motion", Slow_Motion); //13
		addBoolOption("Ragdoll", Toggle_Ragdoll); //14
		addBoolOption("Radio On Foot", Toggle_Radio); //15
		addOption("Clear Blood"); //16
		addBoolOption("Dragon Mode", DragonMode);
		addOption("Fix & Clean Car");
		addBoolOption("Quick Fix & Clean Car", Quick_Fix);
		addFloatOption("Protection Range", &Range2, -255.0f, 255.0f, true);
		addBoolOption("No Targeted", targetted); //1
		switch (getOption())
		{
		case 4:
		{
			advRecovery = !advRecovery;
			if (advRecovery)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("2much4u_Recov"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("2much4u_Recov");
					SCRIPT::REQUEST_SCRIPT("2much4u_Recov");
					if (SCRIPT::HAS_SCRIPT_LOADED("2much4u_Recov"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("2much4u_Recov", StackSize);
						drawNotification("OPEN RECOVERY ~g~RB + A\nLSC ~g~LB + DOWN");
					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("2much4u_Recov");
					}
				}
				else
				{
					NotifyAboveMap("~r~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/apiirockvtrainer1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("2much4u_Recov"))
				{
					drawNotification("Terminated Recovery");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("2much4u_Recov");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("2much4u_Recov");
				}
			}
		}
		break;
		case 5: PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_m@generic", 1048576000); break;
		case 6: PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_f@generic", 1048576000); break;
		case 7:
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_f@drunk@verydrunk", 1048576000);
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_m@drunk@verydrunk", 1048576000); break;
		case 8: RemoveAllPropsFromPlayer(PLAYER::PLAYER_PED_ID()); break;
		case 9:
			ProtectionTest6 = !ProtectionTest6;
			ProtectionTest3 = !ProtectionTest3;
			FreezeCarProtection = !FreezeCarProtection;
			NotifyAboveMap("~g~Malicious Protection"); break;
		case 10:
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), !PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID()));
			NotifyAboveMap("~g~Godmode Toggled");
			break;
		case 11: WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x3656C8C1, 9999, 1); // stun gun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x99B507EA, 9999, 1); // knife
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x678B81B1, 9999, 1); // night stick
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x4E875F73, 9999, 1); // hammer
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x958A4A8F, 9999, 1); // bat
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x440E4788, 9999, 1); // golf club
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x84BD7BFD, 9999, 1); // crowbar
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x1B06D571, 9999, 5); // pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x5EF9FEC4, 9999, 1); // combat pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x22D8FE39, 9999, 1); // ap pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x99AEEB3B, 9999, 1); // pistol 50.
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x13532244, 9999, 1); // micro smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x2BE6766B, 9999, 1); // smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xEFE7E2DF, 9999, 1); // assault smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBFEFFF6D, 9999, 1); // assault rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x83BF0278, 9999, 1); // carbine rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xAF113F99, 9999, 1); // advanced rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x9D07F764, 9999, 1); // MG
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7FD62962, 9999, 1); // combat mg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x1D073A89, 9999, 1); // pump shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7846A318, 9999, 1); // sawnoff shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xE284C527, 9999, 1); // assault shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x9D61E50F, 9999, 1); // bullpupshotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x05FC3C11, 9999, 1); // sniper
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x0C472FE2, 9999, 1); // heavy sniper
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA284510B, 9999, 1); // grenade launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xB1CA77B1, 9999, 1); // rpg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x42BF8A85, 9999, 1); // minigun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x93E220BD, 9999, 1); // grenades
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x2C3731D9, 9999, 1); // sticky bomb
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFDBC8A50, 9999, 1); // smoke grenade
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x34A67B97, 9999, 1); // petrol can
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x060EC506, 9999, 1); // fire extinguisher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x24B17070, 9999, 1); // moltovs
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x497FACC3, 9999, 1); // flare
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFDBADCED, 9999, 1); // digiscanner
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x687652CE, 9999, 1); // stinger
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 600439132, 9999, 1); // ball
																							 //DLC Weapons
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xF9E6AA4B, 9999, 1); // bottle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x61012683, 9999, 1); // gusenerg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC0A3098D, 9999, 1); // special carbine
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xD205520E, 9999, 1); // heavy pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBFD21232, 9999, 1); // sns pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7F229F94, 9999, 1); // bullpup rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x92A27487, 9999, 1); // dagger
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x083839C4, 9999, 1); // vintage pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7F7497E5, 9999, 1); // firework launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA89CB99E, 9999, 1); // musket
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x63AB0442, 9999, 1); // homing launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xAB564B93, 9999, 1); // proxmine
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x787F0BB, 9999, 1); // snowball
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC734385A, 9999, 1); // marksman rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x47757124, 9999, 1); // flare gun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xE232C28C, 9999, 1); // trash bag
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xDC4DB296, 9999, 1); // Marksman Pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xD8DF3C3C, 9999, 1); // Knuckle Duster
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x0A3D4D34, 9999, 1); // new gun
			NotifyAboveMap("~g~All Weapons Given");

			break;
		case 12:
			neverwanted = !neverwanted;
			NotifyAboveMap("~g~Never Wanted Toggled"); break;
		case 13:
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()));
			NotifyAboveMap("~g~Invisibility Toggled"); break;
		case 14: superjump = !superjump;
			NotifyAboveMap("~g~Super Jump Toggled"); break;
		case 15:
			if (!superrun)
				PLAYER::_SET_MOVE_SPEED_MULTIPLIER(PLAYER::PLAYER_ID(), 1.49);
			else
				PLAYER::_SET_MOVE_SPEED_MULTIPLIER(PLAYER::PLAYER_ID(), 1);
			superrun = !superrun;
			NotifyAboveMap("~g~Super Run Toggled"); break;
		case 16:
			if (!SwimFast)
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.49f);
			else
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.0f);
			SwimFast = !SwimFast;
			NotifyAboveMap("~g~Super Swim Toggled");  break;
		case 17: SuperPunch = !SuperPunch;
			NotifyAboveMap("~g~Super Punch Toggled");  break;
		case 18:
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PLAYER::PLAYER_PED_ID());
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PLAYER::PLAYER_PED_ID()))
			{
				ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), Set_AlphaTo, false);
			}
			NotifyAboveMap("~g~Alpha Set"); break;
		case 19:
			if (ToggleHeatVision)
			{
				GRAPHICS::SET_SEETHROUGH(true);
			}
			else if (!ToggleHeatVision)
			{
				GRAPHICS::SET_SEETHROUGH(false);
			}
			ToggleHeatVision = !ToggleHeatVision;
			NotifyAboveMap("~g~Heat Vision Toggled"); break;
		case 20:
			if (ToggleNightVision)
			{
				GRAPHICS::SET_NIGHTVISION(true);
			}
			else if (!ToggleNightVision)
			{
				GRAPHICS::SET_NIGHTVISION(false);
			}
			ToggleNightVision = !ToggleNightVision;
			NotifyAboveMap("~g~Night Vision Toggled"); break;
		case 21:
			if (Slow_Motion)
				GAMEPLAY::SET_TIME_SCALE(1.0f);
			else
				GAMEPLAY::SET_TIME_SCALE(0.3f);
			Slow_Motion = !Slow_Motion;
			NotifyAboveMap("~g~Slow Motion Toggled"); break;
		case 22:
			if (Toggle_Ragdoll)
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
			else
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
			Toggle_Ragdoll = !Toggle_Ragdoll;
			NotifyAboveMap("~g~Ragdoll Toggled"); break;
		case 23:
			Toggle_Radio = !Toggle_Radio;
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(Toggle_Radio);
			NotifyAboveMap("~g~Radio Toggled"); break;
		case 24:
			PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
			PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID());
			NotifyAboveMap("~g~Player Cleaned"); break;
		case 25: DragonMode = !DragonMode; break;
		case 26:
			int myvehicle;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0))
			{
				myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					VEHICLE::SET_VEHICLE_FIXED(myvehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(myvehicle, 0.0f);
				}
			} break;
		case 27: Quick_Fix = !Quick_Fix;
			NotifyAboveMap("Quick Fixed Toggled Use RB To Use"); break;
		case 29:
			targetted = !targetted;
			if (targetted)
			{
				PED::SET_PED_CAN_BE_TARGETTED(PLAYER::PLAYER_PED_ID(), true);

			}
			else if (!targetted)
			{
				PED::SET_PED_CAN_BE_TARGETTED(PLAYER::PLAYER_PED_ID(), false);
			} break;
		}
		break;
#pragma endregion
#pragma region Model Changer
	case ModelOptions:
		addTitle("Advanced Model Options");
		addSubmenuOption("Component Editor", Component_Options); //4
		addSubmenuOption("Outfit Options", Outfit_Options); //3
		addSubmenuOption("Model Changer", Model_Changer); //3
		break;
#pragma endregion
#pragma region Model Changer
	case Model_Changer:
		addTitle("Model Changer");
		addOption("Set Model Black");
		addModelOption("Beach Girl", 808859815);
		addModelOption("Alien", 0x64611296);
		addModelOption("Beach Bae", 0x9CF26183);
		addModelOption("Stripper", 0x2970A494);
		addModelOption("Pilot", -163714847);
		addModelOption("Pissed Guy", 0x9194CE03);
		addModelOption("Gunman", 0xB881AEE);
		addModelOption("Prisoner", 0xB1BB9B59);
		addModelOption("SWAT", 0x8D8F1B10);
		addModelOption("Clown", 0x4498DDE);
		addModelOption("Bugstars", 0x48114518);
		addModelOption("Dildo Dipper", 0x5442C66B);
		addModelOption("Fat Lady", 0xB5CF80E4);
		addModelOption("Hobo", 0x55446010);
		addModelOption("Astronaut", 0xE7B31432);
		addModelOption("Firefighter", -1229853272);
		addModelOption("Johhny", 0x87CA80AE);
		addModelOption("FBI Suit", 0x3AE4A33B);
		addModelOption("Zombie", 0xAC4B4506);
		addModelOption("Buff Dude", 0xDA116E7E);
		addModelOption("Impotenet Rage", 880829941);
		addModelOption("Franklin", 0x9B22DBAF);
		addModelOption("Trevor", 0x9B810FA2);
		addModelOption("Micheal", 0xD7114C9);
		addModelOption("Dude With Pants Down", 2109968527);
		addModelOption("Hoe With Skirt Up", 602513566);
		addModelOption("Slenderman", 0x92991b72);
		addModelOption("Bigfoot", 1641334641);
		addModelOption("The Guy Who Isnt Real", 3459037009);
		addModelOption("Space Ranger", 1011059922);
		addModelOption("Drunk Mexican", 3367706194);
		addModelOption("Classy Stripper", -2126242959);
		addModelOption("Gang Member", -1031795266);
		addModelOption("Space Monkey", -598109171);
		addModelOption("Hunter", -837606178);
		addModelOption("Lester", 1302784073);
		addModelOption("Mark", -304305299);
		addModelOption("Wade", -1835459726);
		addModelOption("Porn Dudes", 793443893);
		addModelOption("Jimmy", 1459905209);
		addModelOption("Lamar", 1706635382);
		addModelOption("Mrs Phillips", 946007720);
		addModelOption("Muscl Beach Dude", -920443780);
		addModelOption("Dirt Bike Guy", 1694362237);
		addModelOption("Dirt Bike Guy 2", 1694362237);
		addModelOption("Dirt Bike Guy 3", 2007797722);
		addModelOption("Priest", 1681385341);
		addModelOption("Mime", 1021093698);
		addModelOption("Ron", -1124046095);
		addModelOption("Office Lady", -1106743555);
		addModelOption("Tonya", -892841148);
		addModelOption("Maude", 1005070462);
		addModelOption("Marnie", 411185872);
		addModelOption("Old Lady / Black Lady", -1606864033);
		addModelOption("Nice Chick With Tits", -96953009);
		addModelOption("Nigel", -927525251);
		addModelOption("Tanisha", 226559113);
		addModelOption("Russian Drunk", 1024089777);
		addModelOption("Bartender", 2014052797);
		addModelOption("Migrant Female", -715445259);
		addModelOption("Migrant Male", -317922106);
		addModelOption("Bouncer", -1613485779);
		addModelOption("Hair Dresser", 1099825042);
		addModelOption("Scientist", 1092080539);
		addModelOption("Misty", -785842275);
		addModelOption("Female Fatbla ", -88831029);
		addModelOption("Female Fatcult", -1244692252);
		addModelOption("Female Fatwhite", 951767867);
		addModelOption("Female Ktown", 1388848350);
		addModelOption("Female Ktown 2", 1090617681);
		addModelOption("Female Prol Host", 379310561);
		addModelOption("Female Salton", -569505431);
		addModelOption("Female Skidrow", -1332260293);
		addModelOption("Female Soucent MC", -840346158);
		addModelOption("Female Soucent", 1951946145);
		addModelOption("Female Soucent 2", -215821512);
		addModelOption("Female Tourist", 1347814329);
		addModelOption("Female Tramp Beach", -1935621530);
		addModelOption("Female Tramp", 1224306523);
		addModelOption("Female Genstreet", 1640504453);
		addModelOption("Female Indian", -1160266880);
		addModelOption("Female Ktown", 1204772502);
		addModelOption("Female Salton", -855671414);
		addModelOption("Female Soucent", 1039800368);
		addModelOption("Female Soucent 2", -1519524074);
		addModelOption("Female Beach", -945854168);
		addModelOption("Female Bevhills", 1146800212);
		addModelOption("Female Bevhills 2", 1546450936);
		addModelOption("Female Bevhills 3", 549978415);
		addModelOption("Female Bevhills 4", 920595805);
		addModelOption("Female Business", 664399832);
		addModelOption("Female Business 2", 826475330);
		addModelOption("Female Business 3", -1366884940);
		addModelOption("Female Business 4", -1211756494);
		addModelOption("Female Eastsa", -173013091);
		addModelOption("Female Eastsa 2", 70821038);
		addModelOption("Female Eastsa 3", 1371553700);
		addModelOption("Female Epsilon", 1755064960);
		addModelOption("Female Fitness", 1165780219);
		addModelOption("Female Fitness 2", 331645324);
		addModelOption("Female Genhot", 793439294);
		addModelOption("Female Golfer", 2111372120);
		addModelOption("Female Hiker", 813893651);
		addModelOption("Female Hippie", 343259175);
		addModelOption("Female Hipster", -21092220985);
		addModelOption("Female Hipster 2", -1745486195);
		addModelOption("Female Hipster 3", -1514497514);
		addModelOption("Female Hipster 4", 429425116);
		addModelOption("Female Indian", 153984193);
		addModelOption("Female Juggalo", -619494093);
		addModelOption("Female Runner", -951490775);
		addModelOption("Female Rur Meth", 1064866854);
		addModelOption("Female Scdressy", -614546432);
		addModelOption("Female Skater", 1767892582);
		addModelOption("Female Soucent", 744758650);
		addModelOption("Female Soucent 2", 1519319503);
		addModelOption("Female Soucent 3", -2018356203);
		addModelOption("Female Tennis", 1426880966);
		addModelOption("Female Topless", -1661836925);
		addModelOption("Female Tourist", 1446741360);
		addModelOption("Female Tourist", -1859912896);
		addModelOption("Female Vinewood", 435429221);
		addModelOption("Female Vinewood 2", -625565461);
		addModelOption("Female Vinewood 3", 933092024);
		addModelOption("Female Vinewood 4", -85696186);
		addModelOption("Female Yoga 1", -1004861906);
		addModelOption("Male Acult ", 1413662315);
		addModelOption("Male Afriamer", -781039234);
		addModelOption("Male Beach", 1077785853);
		addModelOption("Male Beach 2", 2021631368);
		addModelOption("Male Bevhills", 1423699487);
		addModelOption("Male Bevhills 2", 1068876755);
		addModelOption("Male Business", 2120901815);
		addModelOption("Male Eastsa", -106498753);
		addModelOption("Male Eastsa 2", 131961260);
		addModelOption("Male Farmer", -1806291497);
		addModelOption("Male Fatlatin", 1641152947);
		addModelOption("Male Genfat", 115168927);
		addModelOption("Male Genfat 2", 330231874);
		addModelOption("Male Golfer", -1444213182);
		addModelOption("Male Has Jew", 1809430156);
		addModelOption("Male Hillbilly", 1822107721);
		addModelOption("Male Hillbilly 2", 2064532783);
		addModelOption("Male Indian", -573920724);
		addModelOption("Male Ktown", -782401935);
		addModelOption("Male Malibu", 803106487);
		addModelOption("Male Mexcntry", -578715987);
		addModelOption("Male Mexican Labor", -1302522190);
		addModelOption("Male Og Boss", 1746653202);
		addModelOption("Male Papa Razzi", -322270187);
		addModelOption("Male Polynesian", -1445349730);
		addModelOption("Male Prol Host", -1760377969);
		addModelOption("Male Rur meth", 1001210244);
		addModelOption("Male Salton", 1328415626);
		addModelOption("Male Salton 2", 1626646295);
		addModelOption("Male Salton 3", -1299428795);
		addModelOption("Male Salton 4", -1773858377);
		addModelOption("Male Skater", -640198516);
		addModelOption("Male Skidrow", 32417469);
		addModelOption("Male Socenlat", 193817059);
		addModelOption("Male Soucent", 1750583735);
		addModelOption("Male Soucent 2", -1620232223);
		addModelOption("Male Soucent 3", -1948675910);
		addModelOption("Male Soucent 4", -1023672578);
		addModelOption("Male Stlat 2", -1029146878);
		addModelOption("Male Tennis", 1416254276);
		addModelOption("Male Tourist", -929103484);
		addModelOption("Male Tramp beach", 1404403376);
		addModelOption("Male Tramp", 516505552);
		addModelOption("Male Tranvest", -521758348);
		addModelOption("Male Tranvest 2", -150026812);
		addModelOption("Male Acult", 1430544400);
		addModelOption("Male Acult 2", 1268862154);
		addModelOption("Male Beach", -2077764712);
		addModelOption("Male Genstreet", -1386944600);
		addModelOption("Male Ktown", 355916122);
		addModelOption("Male Salton", 539004493);
		addModelOption("Male Soucent", 718836251);
		addModelOption("Male Soucent 2", 1082572151);
		addModelOption("Male Soucent 3", 238213328);
		addModelOption("Male Tramp", 390939205);
		addModelOption("Male Acult", -1251702741);
		addModelOption("Male Acult 2", -2132435154);
		addModelOption("Male Beachvesp", 2114544056);
		addModelOption("Male Beachvesp 2", -900269486);
		addModelOption("Male Beach", -771835772);
		addModelOption("Male Beach 2", 600300561);
		addModelOption("Male Beach 3", -408329255);
		addModelOption("Male Bevhills", 1982350912);
		addModelOption("Male Bevhills 2", 1720428295);
		addModelOption("Male Break dancer ", 933205398);
		addModelOption("Male Busicas", -1697435671);
		addModelOption("Male Business", -912318012);
		addModelOption("Male Business 2", -1280051738);
		addModelOption("Male Business 3", -1589423867);
		addModelOption("Male Cyclist", -37334073);
		addModelOption("Male Dhill", -12678997);
		addModelOption("Male Downtown", 766375082);
		addModelOption("Male Eastsa", -1538846349);
		addModelOption("Male Eastsa 2", 377976310);
		addModelOption("Male Epsilon", 2010389054);
		addModelOption("Male Epsilon 2", -1434255461);
		addModelOption("Male Gay", -775102410);
		addModelOption("Male Gay 2", -1519253631);
		addModelOption("Male Genstreet", -1736970383);
		addModelOption("Male Genstreet 2", 891398354);
		addModelOption("Male Golfer", -685776591);
		addModelOption("Male Has Jew", -512913663);
		addModelOption("Male Hiker", 1358380044);
		addModelOption("Male Hippy", 2097407511);
		addModelOption("Male Hipster", 587703123);
		addModelOption("Male Hipster 2", 349505262);
		addModelOption("Male Hipster 3", 1312913862);
		addModelOption("Male Indian", 706935758);
		addModelOption("Male Jetski", 767028979);
		addModelOption("Male Juggalo", -1849016788);
		addModelOption("Male Ktown", 452351020);
		addModelOption("Male Ktown 2", 696250687);
		addModelOption("Male Latino", 321657486);
		addModelOption("Male Meth Head", 1768677545);
		addModelOption("Male Mexican Thug", 810804565);
		addModelOption("Male Musclbeach", 1264920838);
		addModelOption("Male Musclbeach 2", -920443780);
		addModelOption("Male Polynesian", -2088436577);
		addModelOption("Male Roadcyc", -178150202);
		addModelOption("Male Runner", 623927022);
		addModelOption("Male Runner 2", -2076336881);
		addModelOption("Male Salton", -681546704);
		addModelOption("Male Skater", -1044093321);
		addModelOption("Male Skater 2", -1342520604);
		addModelOption("Male Soucent", -417940021);
		addModelOption("Male Soucent 2", -1398552374);
		addModelOption("Male Soucent 3", -1007618204);
		addModelOption("Male Soucent 4", -1976105999);
		addModelOption("Male Stbla", -812470807);
		addModelOption("Male Stbla 2", -1731772337);
		addModelOption("Male Stlat", -2039163396);
		addModelOption("Male Stwhi", 605602864);
		addModelOption("Male Stwhi 2", 919005580);
		addModelOption("Male Sunbathe", -1222037748);
		addModelOption("Male Surfer", -356333586);
		addModelOption("Male Vindouche", -1047300121);
		addModelOption("Male Vinewood", 1264851357);
		addModelOption("Male Vinewood 2", 1561705728);
		addModelOption("Male Vinewood 3", 534725268);
		addModelOption("Male Vinewood 4", 835315305);
		addModelOption("Male Yoga", -1425378987);
		addModelOption("Abigail", -1988720319);
		addModelOption("Anita", 117698822);
		addModelOption("Anton", -1513650250);
		addModelOption("Ballas Og", -1410400252);
		addModelOption("Bride", -2101379423);
		addModelOption("Burger Drug", -1931689897);
		addModelOption("Chines Goon", -1463670378);
		addModelOption("Cletus", -890640939);
		addModelOption("Cop", -1699520669);
		addModelOption("Customer", -1538297973);
		addModelOption("Denise Friend", -1249041111);
		addModelOption("Janitor", -1040164288);
		addModelOption("Maude", -1127975477);
		addModelOption("Merry Weather", 1631478380);
		addModelOption("Ortega", -1059388209);
		addModelOption("Oscar", -199280229);
		addModelOption("Prologue Driver", -267695653);
		addModelOption("Prolsec", 2141384740);
		addModelOption("Hipster", 569740212);
		addModelOption("Marine", 1634506681);
		addModelOption("Mexican", -162605104);
		addModelOption("Reporter", 776079908);
		addModelOption("Roccopelosi", -1436281204);
		addModelOption("Stripper", -1360365899);
		addModelOption("Traffic Warden", -567724045);
		addModelOption("Female Ballas", 361513884);
		addModelOption("Female Families", 1309468115);
		addModelOption("Female Lost", -44746786);
		addModelOption("Female Vagos", 1520708641);
		addModelOption("Male Arm Boss", -236444766);
		addModelOption("Male Arm Goon", -39239064);
		addModelOption("Male Arm Lieut", -412008429);
		addModelOption("Male Chem Work", -166363761);
		addModelOption("Male Chines Boss", -1176698112);
		addModelOption("Male Chines Cold", 275618457);
		addModelOption("Male Chines Goon", 2119136831);
		addModelOption("Male Chines Goon 2", -9308122);
		addModelOption("Male Korean Boss", 891945583);
		addModelOption("Male Mexican Boss", 1466037421);
		addModelOption("Male Mexican Boss 2", 1226102803);
		addModelOption("Male Arm Goon 2", -984709238);
		addModelOption("Male Azteca", 1752208920);
		addModelOption("Male Balla East", -198252413);
		addModelOption("Male Balla Orig", 588969535);
		addModelOption("Male Ballas Out", 599294057);
		addModelOption("Male Famca", -398748745);
		addModelOption("Male Famdnf", -613248456);
		addModelOption("Male Famfor", -2077218039);
		addModelOption("Male Korean", 611648169);
		addModelOption("Male Korean 2", -1880237687);
		addModelOption("Male Korean Lieut", 2093736314);
		addModelOption("Male Lost", 1330042375);
		addModelOption("Male Lost 2", 1032073858);
		addModelOption("Male Lost 3", 850468060);
		addModelOption("Male Mexican Gang", -1109568186);
		addModelOption("Male Mexicangoon", 653210662);
		addModelOption("Male Mexicangoon 2", 832784782);
		addModelOption("Male Mexicangoon 3", -1773333796);
		addModelOption("Male Pologoon", 1329576454);
		addModelOption("Male Pologoon 2", -1561829034);
		addModelOption("Male Salvaboss", -1872961334);
		addModelOption("Male Salvagoon", 663522487);
		addModelOption("Male Salvagoon 2", 846439045);
		addModelOption("Male Salvagoon 3", 62440720);
		addModelOption("Male Stream Punk", -48477765);
		addModelOption("Male Stream Punk 2", 228715206);
		addModelOption("Abigail", 1074457665);
		addModelOption("Ashley", 2129936603);
		addModelOption("Bank Man", -1868718465);
		addModelOption("Barry", 797459875);
		addModelOption("Best Men", 1464257942);
		addModelOption("Beverly", -1113448868);
		addModelOption("Bride", 1633872967);
		addModelOption("Car Guy", -2063996617);
		addModelOption("Car Guy 2", 1975732938);
		addModelOption("Casey", -520477356);
		addModelOption("Chef", 1240128502);
		addModelOption("Chengsr", -1427838341);
		addModelOption("Chris Formage", 678319271);
		addModelOption("Clay", 1825562762);
		addModelOption("Clay Pain", -1660909656);
		addModelOption("Cletus", -429715051);
		addModelOption("Dale", 1182012905);
		addModelOption("Dreyfuss", -628553422);
		addModelOption("Janet", 225287241);
		addModelOption("Jewelass", 257763003);
		addModelOption("Jimmy Boston", -308279251);
		addModelOption("Joe Minuteman", -1105179493);
		addModelOption("Josef", -518348876);
		addModelOption("Josh", 2040438510);
		addModelOption("Kerry Mcintosh", 1530648845);
		addModelOption("Lifeinvad", 1401530684);
		addModelOption("Lifeinvad 2", 666718676);
		addModelOption("Magenta", -52653814);
		addModelOption("Manuel", -46035440);
		addModelOption("Maryann", -1552967674);
		addModelOption("Natalia", -568861381);
		addModelOption("Old Man", 1906124788);
		addModelOption("Old Man 2", -283816889);
		addModelOption("Oneil", 768005095);
		addModelOption("Ortega", 648372919);
		addModelOption("Paper", -1717894970);
		addModelOption("Prolsec", 666086773);
		addModelOption("Hic", 1165307954);
		addModelOption("Hipster", -554721426);
		addModelOption("Mexican", -424905564);
		addModelOption("Roccopelosi", -709209345);
		addModelOption("Screen writer", -1689993);
		addModelOption("Talina", -409745176);
		addModelOption("Terry", 1728056212);
		addModelOption("Tom Epsilon", -847807830);
		addModelOption("Traffic Warden", 1461287021);
		addModelOption("Tyler Dix", 1382414087);
		addModelOption("Zimbor", 188012277);
		addModelOption("Female Barber", 373000027);
		addModelOption("Female Maid", -527186490);
		addModelOption("Female Shop High", -1371020112);
		addModelOption("Female Sweat Shop", 824925120);
		addModelOption("Female Air Hostess", 1567728751);
		addModelOption("Female Bay Watch", 1250841910);
		addModelOption("Female Cop", 368603149);
		addModelOption("Female Factory", 1777626099);
		addModelOption("Female Hooker", 42647445);
		addModelOption("Female Hooker 2", 348382215);
		addModelOption("Female Hooker 3", 51789996);
		addModelOption("Female Movie Prem", 587253782);
		addModelOption("Female Ranger", -1614285257);
		addModelOption("Female Scrubs", -1420211530);
		addModelOption("Female Sheriff", 1096929346);
		addModelOption("Female Shop Low", -1452399100);
		addModelOption("Female Shop Mid", 1055701597);
		addModelOption("Female Stripper Lite", 1544875514);
		addModelOption("Female Stripper", 1381498905);
		addModelOption("Female Stripper 2", 1846523796);
		addModelOption("Female Sweat Shop", -2063419726);
		addModelOption("Male Ammucountry", 233415434);
		addModelOption("Male Armoured", -1782092083);
		addModelOption("Male Armoured 2", 1669696074);
		addModelOption("Male Autoshop", 68070371);
		addModelOption("Male Autoshop", -261389155);
		addModelOption("Male Chemsec", 788443093);
		addModelOption("Male Ciasec", 1650288984);
		addModelOption("Male Cntrybar", 436345731);
		addModelOption("Male Dock Work", 349680864);
		addModelOption("Male Doctor", -730659924);
		addModelOption("Male Fib Office", -306416314);
		addModelOption("Male Fib Office 2", 653289389);
		addModelOption("Male Gaffer", -1453933154);
		addModelOption("Male Gardener", 1240094341);
		addModelOption("Male Gentransport", 411102470);
		addModelOption("Male High Sec", -245247470);
		addModelOption("Male High Sec 2", 691061163);
		addModelOption("Male Janitor", -1452549652);
		addModelOption("Male Lathandy", -1635724594);
		addModelOption("Male Lifeinvad", -570394627);
		addModelOption("Male Linecook", -610530921);
		addModelOption("Male Lsmetro", 1985653476);
		addModelOption("Male Mariachi", 2124742566);
		addModelOption("Male Marine", -220552467);
		addModelOption("Male Marine 2", -265970301);
		addModelOption("Male Movie Prem", -664900312);
		addModelOption("Male Movies Pace", -407694286);
		addModelOption("Male Paramedic", -1286380898);
		addModelOption("Male Pilot", -413447396);
		addModelOption("Male Postal", 1650036788);
		addModelOption("Male Postal 2", 1936142927);
		addModelOption("Male Prison Guard", 1456041926);
		addModelOption("Male Security", -681004504);
		addModelOption("Male Snow Cop", 451459928);
		addModelOption("Male Strperf", 2035992488);
		addModelOption("Male Strpreach", 469792763);
		addModelOption("Male Strvend", -829353047);
		addModelOption("Male Trucker", 1498487404);
		addModelOption("Male Ups", -1614577886);
		addModelOption("Male Ups 2", -792862442);
		addModelOption("Male Busker", -1382092357);
		addModelOption("Male Airworker", 1644266841);
		addModelOption("Male Ammucity", -1643617475);
		addModelOption("Male Armymech", 1657546978);
		addModelOption("Male Autopsy", -1306051250);
		addModelOption("Male Barman", -442429178);
		addModelOption("Male Bay Watch", 189425762);
		addModelOption("Male Black Ops", -1275859404);
		addModelOption("Male Black Ops 2", 2047212121);
		addModelOption("Male Busboy", -654717625);
		addModelOption("Male Chef", 261586155);
		addModelOption("Male Construck", -673538407);
		addModelOption("Male Construck 2", -973145378);
		addModelOption("Male Cop", 1581098148);
		addModelOption("Male Dealer", -459818001);
		addModelOption("Male Devin Sec", -1688898956);
		addModelOption("Male Dock Work", -2039072303);
		addModelOption("Male Door Man", 579932932);
		addModelOption("Male Dw Service", 1976765073);
		addModelOption("Male Dw Service 2", -175076858);
		addModelOption("Male Factory", 1097048408);
		addModelOption("Male Garbage", -294281201);
		addModelOption("Male Grip", 815693290);
		addModelOption("Male Hway Cop", 1939545845);
		addModelOption("Male Marine", 1702441027);
		addModelOption("Male Marine 2", 1490458366);
		addModelOption("Male Marine 3", 1925237458);
		addModelOption("Male Pestcont", 1209091352);
		addModelOption("Male Pilot", -1422914553);
		addModelOption("Male Prismuscl", 1596003233);
		addModelOption("Male Ranger", -277793362);
		addModelOption("Male Robber", -1067576423);
		addModelOption("Male Sheriff", -1320879687);
		addModelOption("Male Shop Mask", 1846684678);
		addModelOption("Male Strvend", -1837161693);
		addModelOption("Male Uscg", -905948951);
		addModelOption("Male Valet", 999748158);
		addModelOption("Male Waiter", -1387498932);
		addModelOption("Male Winclean", 1426951581);
		addModelOption("Male Xmech", 1142162924);
		addModelOption("Male Xmech 2", -1105135100);
		addModelOption("Female Corpse", 773063444);
		addModelOption("Female Miranda", 1095737979);
		addModelOption("Female Promourn", -1576494617);
		addModelOption("Female Moviestar", 894928436);
		addModelOption("Female Prolhost", -988619485);
		addModelOption("Female Comjane", -1230338610);
		addModelOption("Female Corpse", -1670377315);
		addModelOption("Female Corpse 2", 228356856);
		addModelOption("Female Hotposh", -1768198658);
		addModelOption("Female Jewelass", -254493138);
		addModelOption("Female Mistress", 1573528872);
		addModelOption("Female Princess", -756833660);
		addModelOption("Female Spyactress", 1535236204);
		addModelOption("Male Aldinapoli", -252946718);
		addModelOption("Male Bank Man", -1022961931);
		addModelOption("Male Bike Mire", 1984382277);
		addModelOption("Male Fibar Chitect", 874722259);
		addModelOption("Male Filmdirector", 728636342);
		addModelOption("Male Glen Stank", 1169888870);
		addModelOption("Male Griff", -1001079621);
		addModelOption("Male Jewelsec", -1395868234);
		addModelOption("Male Jewelthief", -422822692);
		addModelOption("Male Mark Fost", 479578891);
		addModelOption("Male Party Target", -2114499097);
		addModelOption("Male Prolsec", 1888624839);
		addModelOption("Male Promourn", -829029621);
		addModelOption("Male Rivalpap", 1624626906);
		addModelOption("Male Spyactor", -1408326184);
		addModelOption("Male Willyfist", -1871275377);
		addModelOption("Male Finguru", 1189322339);
		addModelOption("Male Taphill Billy", -1709285806);
		addModelOption("Male Tramp", 1787764635);
		addModelOption("Male Abner", -257153498);
		addModelOption("Male Antonb", -815646164);
		addModelOption("Male Babyd", -636391810);
		addModelOption("Male Baygor", 1380197501);
		addModelOption("Male Cyclist", 755956971);
		addModelOption("Male Fibmugger", -2051422616);
		addModelOption("Male Guido", -961242577);
		addModelOption("Male Gunvend", -1289578670);
		addModelOption("Male Hippie", -264140789);
		addModelOption("Male Mani", -927261102);
		addModelOption("Male Military Bum", 1191548746);
		addModelOption("Male Paparazzi", 1346941736);
		addModelOption("Male Party", 921110016);
		addModelOption("Male Proldriver", -2057423197);
		addModelOption("Male Sbike", 1794381917);
		addModelOption("Male Staggrm", -1852518909);
		addModelOption("Male Tattoo", -1800524916);
		addModelOption("Driver", 994527967);
		addModelOption("Hacker", -1715797768);
		addModelOption("Amanda Townley", 1830688247);
		addModelOption("Andreas", 1206185632);
		addModelOption("Ballasog", -1492432238);
		addModelOption("Brad", -1111799518);
		addModelOption("Davenorton", 365775923);
		addModelOption("Denise", -2113195075);
		addModelOption("Devin", 1952555184);
		addModelOption("Dom", -1674727288);
		addModelOption("Dr Fried Lander", -872673803);
		addModelOption("Fabien", -795819184);
		addModelOption("Floyd", -1313761614);
		addModelOption("Jay Norris", 2050158196);
		addModelOption("Lazlow", -538688539);
		addModelOption("Milton", -886023758);
		addModelOption("Molly", -1358701087);
		addModelOption("Omega", 1625728984);
		addModelOption("Patricia", -982642292);
		addModelOption("Siemonyetarian", 1283141381);
		addModelOption("Solomon", -2034368986);
		addModelOption("Stevehains", 941695432);
		addModelOption("Stretch", 915948376);
		addModelOption("Taocheng", -597926235);
		addModelOption("Taostranslator", 2089096292);
		addModelOption("Tennis Coach", -1573167273);
		addModelOption("Tracy Disanto", -566941131);
		addModelOption("Dead Hooker", 1943971979);
		addModelOption("Stripper Lite", 695248020);
		addModelOption("Headtargets", 1173958009);
		addModelOption("Claude", -1057787465);
		addModelOption("Famdd", 866411749);
		addModelOption("Fibsec", 1558115333);
		addModelOption("Marston", 943915367);
		addModelOption("Niko", -287649847);
		addModelOption("Shop Keeper", 416176080);
		switch (getOption())
		{
		case 1:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 12, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 13, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 14, 0, 5, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 15, 0, 5, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Players List
	case Players_List:
		pinfo = false;
		PlayerInfo(PLAYER_PLAYING_INF_SELC);
		addTitle("Online Players");
		for (int i = 0; i < 18; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			xInstruction = true;
			if (optionPress)
			{
				selectedPlayer = currentOption - 1;
				changeSubmenu(Player_Options);
			}
		}

		break;
#pragma endregion
#pragma region Blame Players List
	case Blame_Players_List:

		addTitle("Blame Player List");
		//addSubmenuOption("All Players", NULL);
		for (int i = 0; i < 18; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			xInstruction = true;
			if (optionPress)
			{
				selectedPlayer2 = currentOption - 1;
				Vector3 Playerscoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer2), true);
				FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED(selectedPlayer), Playerscoords.x, Playerscoords.y, Playerscoords.z, BLIMP, FLT_MAX, false, true, 1.0f); break;
			}
		}
		break;
#pragma endregion
#pragma region Player Options
	case Player_Options:
		pinfo = true;
		addTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
		addSubmenuOption("Player Options", Player_Options_Online);
		addSubmenuOption("RP Options", onlinetest);
		addSubmenuOption("Player Animations", Animations_Menu2);
		addSubmenuOption("Spawn Bad Peds", AnimacionesOnline);
		addSubmenuOption("Vehicle Menu", Vehicle_MenuOnline);
		addSubmenuOption("Teleport Options", Teleport_Options_Online);
		addSubmenuOption("Nice Stuff", Nice_Stuff_Online);
		addSubmenuOption("Cash Drop Options", cashdrop_options);
		addSubmenuOption("Mean Stuff", Mean_Stuff_Online);
		addKeyboardOption("Send Custom Text", 1, "", 250);
		addSubmenuOption("Attachement Menu", Attachement_Menu_Online);
		addSubmenuOption("Set Stuff On Ped Options", SetStuffOnPlayerOptions);
		addSubmenuOption("Shoot Bullet At Player", ShootBulletAtPlayer);
		addSubmenuOption("Explode Options", Explode_Options_Online);
		addSubmenuOption("Blame Player List", Blame_Players_List);
		break;
#pragma endregion
#pragma region Animation Menu
	case Animations_Menu2:

		addTitle("Animations Menu");
		addSubmenuOption("Sport Options", Sport_Options2); //1
		addSubmenuOption("Sex Options", Sex_Options2); //2
		addSubmenuOption("Dance Options", Dance_Options2); //3
		addSubmenuOption("SuperHero Options", SuperHero_Options2); //4
		addSubmenuOption("Misc Options", Misc_OptionsAnims2); //5
		addSubmenuOption("Police Options", Police_OptionsAnims2); //6
		addSubmenuOption("Paparazzi Options", Paparazzi_OptionsAnims2); //7
		addSubmenuOption("Cower Options", Cower_OptionsAnims2); //8
		addOption("Stop Tasks"); //9
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
		break;
#pragma endregion
#pragma region Sport Options
	case Sport_Options2:

		addTitle("Sport Options");
		addOption("Situps");
		addOption("Pushups");
		addOption("Bench Press");
		addOption("Chin Ups");
		addOption("Free Weights");
		addOption("Flex Side");
		addOption("Flex Front");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb@world_human_sit_ups@male@base", "base"); break;
		case 2:
			AddAnimationOnline("amb@world_human_push_ups@male@base", "base"); break;
		case 3:
			AddAnimationOnline("amb@prop_human_seat_muscle_bench_press@base", "base"); break;
		case 4:
			AddAnimationOnline("amb@prop_human_muscle_chin_ups@male@base", "base"); break;
		case 5:
			AddAnimationOnline("amb@world_human_muscle_free_weights@male@barbell@base", "base"); break;
		case 6:
			AddAnimationOnline("amb@world_human_muscle_flex@arms_at_side@base", "base"); break;
		case 7:
			AddAnimationOnline("amb@world_human_muscle_flex@arms_in_front@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Wank Options
	case Wank_OptionsAnims2:
		addTitle("Wank Options");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb", "base");
			break;
		case 2:
			AddAnimationOnline("amb", "base");
			break;
		case 3:
			AddAnimationOnline("amb", "base");
			break;
		case 4:
			AddAnimationOnline("amb", "base");
			break;
		case 5:
			AddAnimationOnline("amb", "base");
			break;
		case 6:
			AddAnimationOnline("amb", "base");
			break;
		case 7:
			AddAnimationOnline("amb", "base");
			break;
		case 8:
			AddAnimationOnline("amb", "base");
			break;
		case 9:
			AddAnimationOnline("amb", "base");
			break;

		}
		break;
#pragma endregion
#pragma region Cower Options
	case Cower_OptionsAnims2:

		addTitle("Cower Options");
		addOption("Cower Female Base");
		addOption("Cower Female Enter");
		addOption("Cower Female Exit");
		addOption("Cower Female Idle A");
		addOption("Cower Female React Cowering");
		addOption("Cower Male Base");
		addOption("Cower Male Enter");
		addOption("Cower Male Exit");
		addOption("Cower Male Idle A");
		addOption("Cower Male Idle B");
		addOption("Cower Male React Cowering");
		addOption("Cower Female Stand Base");
		addOption("Cower Female Stand Enter");
		addOption("Cower Female Stand Exit");
		addOption("Cower Female Stand Idle A");
		addOption("Cower Male Stand React Cowering");
		addOption("Cower Male Stand Base");
		addOption("Cower Male Stand Enter");
		addOption("Cower Male Stand Exit");
		addOption("Cower Male Stand Idle A");
		addOption("Cower Male Stand React Cowering");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb@code_human_cower@female@base", "base");
			break;
		case 2:
			AddAnimationOnline("amb@code_human_cower@female@enter", "enter");
			break;
		case 3:
			AddAnimationOnline("amb@code_human_cower@female@exit", "exit_flee");
			break;
		case 4:
			AddAnimationOnline("amb@code_human_cower@female@idle_a", "idle_c");
			break;
		case 5:
			AddAnimationOnline("amb@code_human_cower@female@react_cowering", "base_back_left");
			break;
		case 6:
			AddAnimationOnline("amb@code_human_cower@male@base", "base");
			break;
		case 7:
			AddAnimationOnline("amb@code_human_cower@male@enter", "enter");
			break;
		case 8:
			AddAnimationOnline("amb@code_human_cower@male@exit", "exit_flee");
			break;
		case 9:
			AddAnimationOnline("amb@code_human_cower@male@idle_a ", "idle_b");
			break;
		case 10:
			AddAnimationOnline("amb@code_human_cower@male@idle_b", "idle_d");
			break;
		case 11:
			AddAnimationOnline("amb@code_human_cower@male@react_cowering", "base_back_left");
			break;
		case 12:
			AddAnimationOnline("amb@code_human_cower_stand@female@base", "base");
			break;
		case 13:
			AddAnimationOnline("amb@code_human_cower_stand@female@enter", "enter");
			break;
		case 14:
			AddAnimationOnline("amb@code_human_cower_stand@female@exit", "exit_flee");
			break;
		case 15:
			AddAnimationOnline("amb@code_human_cower_stand@female@idle_a", "idle_c");
			break;
		case 16:
			AddAnimationOnline("amb@code_human_cower_stand@female@react_cowering", "base_back_left_exit");
			break;
		case 17:
			AddAnimationOnline("amb@code_human_cower_stand@male@base", "base");
			break;
		case 18:
			AddAnimationOnline("amb@code_human_cower_stand@male@enter", "enter");
			break;
		case 19:
			AddAnimationOnline("amb@code_human_cower_stand@male@exit", "exit_flee");
			break;
		case 20:
			AddAnimationOnline("amb@code_human_cower_stand@male@idle_a", "idle_b");
			break;
		case 21:
			AddAnimationOnline("amb@code_human_cower_stand@male@react_cowering ", "base_right");
			break;
		}
		break;
#pragma endregion
#pragma region Police Options
	case Police_OptionsAnims2:

		addTitle("Police Options");
		addOption("Police Crowd Control Base");
		addOption("Police Crowd Control Intro");
		addOption("Police Crowd Control A");
		addOption("Police Crowd Control B");
		addOption("Police Investigate Base");
		addOption("Police Investigate Intro");
		addOption("Police Investigate A");
		addOption("Police Investigate B");
		addOption("Police Vehicle Car Base");
		addOption("Police Vehicle Car Idle A");
		addOption("Police Vehicle Car Idle B");
		addOption("Police Bike Front Base");
		addOption("Police Down Town");
		addOption("Police Paleto Bay");
		addOption("Police Rockford");
		addOption("Police Sandy Shores");
		addOption("Police South Central");
		addOption("Police Vespucci");
		addOption("Police Vinewood");
		addOption("Police Bike Front Base");
		addOption("Police Bike Front Ds");
		addOption("Police Bike Front Ds 2");
		addOption("Police Bike Front Ps");
		addOption("Police Bike Front Ps 2");
		addOption("Police Bike Rear Base");
		addOption("Police Bike Rear Ds");
		addOption("Police Bike Rear Ds 2");
		addOption("Police Bike Rear Ps");
		addOption("Police Bike Rear Ps 2");
		addOption("Police Bike Busted");
		addOption("Police Drive By Bike Front 1H");
		addOption("Police Drive By Bike Front Grenade");
		addOption("Police Drive By Bike Front Grenade 2");
		addOption("Police Drive By Bike Front Unarmed");
		addOption("Police Drive By Bike Rear 1H");
		addOption("Police Drive By Bike Rear Grenade");
		addOption("Police Drive By Bike Rear Grenade 2");
		addOption("Police Drive By Bike Rear Unarmed");
		addOption("Police Van Exit To Aim");
		addOption("Police Van Exit To Aim 2");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb@code_human_police_crowd_control@base", "base");
			break;
		case 2:
			AddAnimationOnline("amb@code_human_police_crowd_control@idle_intro", "idle_intro");
			break;
		case 3:
			AddAnimationOnline("amb@code_human_police_crowd_control@idle_a", "idle_a");
			break;
		case 4:
			AddAnimationOnline("amb@code_human_police_crowd_control@idle_b", "idle_d");
			break;
		case 5:
			AddAnimationOnline("amb@code_human_police_investigate@base", "base");
			break;
		case 6:
			AddAnimationOnline("amb@code_human_police_investigate@idle_intro", "idle_intro");
			break;
		case 7:
			AddAnimationOnline("amb@code_human_police_investigate@idle_a", "idle_a");
			break;
		case 8:
			AddAnimationOnline("amb@code_human_police_investigate@idle_b", "idle_f");
			break;
		case 9:
			AddAnimationOnline("amb@world_vehicle_police_carbase", "base");
			break;
		case 10:
			AddAnimationOnline("amb@world_vehicle_police_caridle_a", "idle_b");
			break;
		case 11:
			AddAnimationOnline("amb@world_vehicle_police_caridle_b", "idle_e");
			break;
		case 12:
			AddAnimationOnline("anim@veh@bike@police@front@base", "horn_intro");
			break;
		case 13:
			AddAnimationOnline("respawn@police@down_town", "down_town_cam");
			break;
		case 14:
			AddAnimationOnline("respawn@police@paleto_bay", "paleto_bay_cam");
			break;
		case 15:
			AddAnimationOnline("respawn@police@rockford", "rockford_cam");
			break;
		case 16:
			AddAnimationOnline("respawn@police@sandy_shores", "sandy_shores_cam");
			break;
		case 17:
			AddAnimationOnline("respawn@police@south_central_a", "south_central_a_cam");
			break;
		case 18:
			AddAnimationOnline("respawn@police@vespucci", "vespucci_cam");
			break;
		case 19:
			AddAnimationOnline("respawn@police@vinewood", "vinewood_cam");
			break;
		case 20:
			AddAnimationOnline("veh@bike@police@front@base", "shunt_from_right");
			break;
		case 21:
			AddAnimationOnline("veh@bike@police@front@ds", "dead_fall_out");
			break;
		case 22:
			AddAnimationOnline("veh@bike@police@front@ds", "jack_dead_victim");
			break;
		case 23:
			AddAnimationOnline("veh@bike@police@front@ps", "jack_dead_victim");
			break;
		case 24:
			AddAnimationOnline("veh@bike@police@front@ps", "get_on_quick");
			break;
		case 25:
			AddAnimationOnline("veh@bike@police@rear@base", "shunt_from_back");
			break;
		case 26:
			AddAnimationOnline("veh@bike@police@rear@ds", "get_out");
			break;
		case 27:
			AddAnimationOnline("veh@bike@police@rear@ds", "jack_base_perp");
			break;
		case 28:
			AddAnimationOnline("veh@bike@police@rear@ps", "jack_base_perp");
			break;
		case 29:
			AddAnimationOnline("veh@bike@police@rear@ps", "get_in");
			break;
		case 30:
			AddAnimationOnline("veh@busted_bike@police@", "busted");
			break;
		case 31:
			AddAnimationOnline("veh@drivebybike@police@front@1h", "intro_0");
			break;
		case 32:
			AddAnimationOnline("veh@drivebybike@police@front@grenade", "intro_0");
			break;
		case 33:
			AddAnimationOnline("veh@drivebybike@police@front@grenade", "sweep_blocked");
			break;
		case 34:
			AddAnimationOnline("veh@drivebybike@police@front@unarmed", "intro_180l");
			break;
		case 35:
			AddAnimationOnline("veh@drivebybike@police@rear@1h ", "intro_0");
			break;
		case 36:
			AddAnimationOnline("veh@drivebybike@police@rear@grenade", "intro_180l");
			break;
		case 37:
			AddAnimationOnline("veh@drivebybike@police@rear@grenade", "outro_180l");
			break;
		case 38:
			AddAnimationOnline("veh@drivebybike@police@rear@unarmed", "outro_180l");
			break;
		case 39:
			AddAnimationOnline("veh@van@policet@ds@exit_to_aim", "get_out_east_ccw");
			break;
		case 40:
			AddAnimationOnline("veh@van@policet@ps@exit_to_aim", "get_out_east");
			break;
		}
		break;
#pragma endregion
#pragma region Paparazzi Options
	case Paparazzi_OptionsAnims2:

		addTitle("Paparazzi Options");
		addOption("Paparazzi Male Base");
		addOption("Paparazzi Male Enter");
		addOption("Paparazzi Male Exit");
		addOption("Paparazzi Male Idle A");
		addOption("Paparazzi Escape In A Car");
		addOption("Paparazzi Escape On Foot");
		addOption("Paparazzi Pap Anims");
		addOption("Paparazzi Peek");
		addOption("Paparazzi Trans");
		addOption("Paparazzi Wait");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb@world_human_paparazzi@male@base", "base");
			break;
		case 2:
			AddAnimationOnline("amb@world_human_paparazzi@male@enter", "enter");
			break;
		case 3:
			AddAnimationOnline("amb@world_human_paparazzi@male@exit", "exit");
			break;
		case 4:
			AddAnimationOnline("amb@world_human_paparazzi@male@idle_a", "idle_a");
			break;
		case 5:
			AddAnimationOnline("random@escape_paparazzi@incar@", "idle_d");
			break;
		case 6:
			AddAnimationOnline("random@escape_paparazzi@standing@", "idle_d");
			break;
		case 7:
			AddAnimationOnline("random@paparazzi@pap_anims", "sweep_low");
			break;
		case 8:
			AddAnimationOnline("random@paparazzi@peek", "right_come_here");
			break;
		case 9:
			AddAnimationOnline("random@paparazzi@trans", "trans_right_to_wait");
			break;
		case 10:
			AddAnimationOnline("random@paparazzi@wait", "wait_a");
			break;
		}
		break;
#pragma endregion
#pragma region Dance Options
	case Dance_Options2:

		addTitle("Dance Options");
		addOption("Pole Dance");
		addOption("Pole Dance 2");
		addOption("Pole Dance 3");
		addOption("Private Dance");
		addOption("Tap Dancing Heaven");
		addOption("Buttwag Dance");
		addOption("Verse Dance");
		addOption("Heaven Dance");
		addOption("Pole Dance On Stage Enter");
		addOption("Pole Dance On Stage Exit");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 2:
			AddAnimationOnline("mini@strip_club@pole_dance@pole_dance2", "pd_dance_02"); break;
		case 3:
			AddAnimationOnline("mini@strip_club@pole_dance@pole_dance3", "pd_dance_03"); break;
		case 4:
			AddAnimationOnline("mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		case 5:
			AddAnimationOnline("special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel"); break;
		case 6:
			AddAnimationOnline("special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag"); break;
		case 7:
			AddAnimationOnline("special_ped@mountain_dancer@monologue_1@monologue_1a", "mnt_dnc_verse"); break;
		case 8:
			AddAnimationOnline("special_ped@mountain_dancer@monologue_4@monologue_4a", "mtn_dnc_if_you_want_to_get_to_heaven"); break;
		case 9:
			AddAnimationOnline("mini@strip_club@pole_dance@stage_enter ", "stage_enter"); break;

		}
		break;
#pragma endregion
#pragma region Sex Options
	case Sex_Options2:

		addTitle("Sex Options");
		addOption("Fuck");
		addOption("Fuck 2");
		addOption("Car Sex (Male)");
		addOption("Car Sex (Female)");
		addOption("Drunk Car Sex (Male)");
		addOption("Drunk Car Sex (Female)");
		addOption("Prostitue Male Sex");
		addOption("Prostitue Female Sex");
		addOption("Prostitue Male BJ");
		addOption("Prostitue Female BJ");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("rcmpaparazzo_2", "shag_loop_a"); break;
		case 2:
			AddAnimationOnline("rcmpaparazzo_2", "shag_loop_poppy"); break;
		case 3:
			AddAnimationOnline("ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_m"); break;
		case 4:
			AddAnimationOnline("ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_f"); break;
		case 5:
			AddAnimationOnline("random@drunk_driver_2", "cardrunksex_loop_m"); break;
		case 6:
			AddAnimationOnline("random@drunk_driver_2", "cardrunksex_loop_f"); break;
		case 7:
			AddAnimationOnline("mini@prostitutes@sexnorm_veh", "sex_loop_male"); break;
		case 8:
			AddAnimationOnline("mini@prostitutes@sexnorm_veh", "sex_loop_prostitute"); break;
		case 9:
			AddAnimationOnline("mini@prostitutes@sexnorm_veh", "bj_loop_male"); break;
		case 10:
			AddAnimationOnline("mini@prostitutes@sexnorm_veh", "bj_loop_prostitute"); break;

		}
		break;
#pragma endregion
#pragma region SuperHero Options
	case SuperHero_Options2:

		addTitle("SuperHero Options");
		addOption("Space Pistol");
		addOption("Space Rifle");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("amb@world_human_superhero@male@space_pistol@base", "base"); break;
		case 2:
			AddAnimationOnline("amb@world_human_superhero@male@space_rifle@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Misc Options
	case Misc_OptionsAnims2:

		addTitle("Misc Options");
		addOption("Tazer");
		addOption("Stun Fire");
		addOption("Electrocute");
		addOption("Wave Yo Arms");
		addOption("Cop Kneeling Arrest");
		addOption("Cop Hands Up");
		addOption("Trevor Smoking Meth");
		switch (getOption())
		{
		case 1:
			AddAnimationOnline("ragdoll@human", "electrocute"); break;
		case 2:
			AddAnimationOnline("ragdoll@human", "on_fire"); break;
		case 3:
			AddAnimationOnline("stungun@standing", "damage"); break;
		case 4:
			AddAnimationOnline("random@car_thief@victimpoints_ig_3", "arms_waving"); break;
		case 5:
			AddAnimationOnline("random@arrests", "kneeling_arrest_idle"); break;
		case 6:
			AddAnimationOnline("creatures@rottweiler@move", "dump_enter"); break;
		case 7:
			AddAnimationOnline("timetable@trevor@smoking_meth@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Explode Options
	case AnimacionesOnline:
		addTitle("Spawn Bad Peds");
		addOption("Stripper with Bat");
		addOption("Clown with Bat");
		addOption("Angry Chop");
		addOption("Mountain Lion");
		addOption("SWAT with Flaregun");
		addOption("SWAT with RPG");
		addOption("Cop with Flaregun");
		addOption("Cop with Machine Gun");
		addOption("Hostile Insurgent");
		addOption("Hostile Hydra");
		addOption("Hostile Savage");
		addOption("Hostile Tank");

		if (getOption() == 1)
		{
			doStripper = true;
			if (spawnStripper())
			{

			}
		}
		else if (getOption() == 2)
		{

			doClown = true;
			if (spawnClown())
			{

			}
		}
		else if (getOption() == 3)
		{
			doChop = true;
			if (spawnChop())
			{

			}
		}
		else if (getOption() == 4)
		{

			doLion = true;
			if (spawnLion())
			{

			}
		}
		else if (getOption() == 5)
		{
			doSwatTazer = true;
			if (spawnSwatTazer())
			{

			}
		}
		else if (getOption() == 6)
		{
			doSwatRPG = true;
			if (spawnSwatRPG())
			{

			}
		}
		else if (getOption() == 7)
		{
			doCopTazer = true;
			if (spawnCopTazer())
			{

			}
		}
		else if (getOption() == 8)
		{
			doCopMG = true;
			if (spawnCopMG())
			{

			}
		}
		else if (getOption() == 9)
		{
			hostileinsurgent = true;
			vehspawncheck = true;
			if (HostileInsurgent())
			{

			}
		}
		else if (getOption() == 10)
		{
			hostilehydra = true;
			vehspawncheck = true;
			if (HostileHydra())
			{

			}
		}
		else if (getOption() == 11)
		{
			hostilesavage = true;
			vehspawncheck = true;
			if (HostileSavage())
			{

			}
		}
		else if (getOption() == 12)
		{
			hostiletank = true;
			vehspawncheck = true;
			if (HostileTank())
			{

			}
		}
		break;
#pragma endregion 
#pragma region Explode Options
	case onlinetest:

		addTitle("RP Options");
		addSubmenuOption("Take RP", Take_RP);
		addSubmenuOption("Give RP", Give_RP);
		break;
#pragma endregion 

	case Take_RP:
		addTitle("Player RP Options");
		addOption("Lower Players Rank By 50");
		addOption("Lower Players Rank By 100");
		addOption("Lower Players Rank By 150");
		addOption("Lower Players Rank By 200");
		addOption("Lower Players Rank By 250");
		addOption("Lower Players Rank By 300");
		addOption("Reset Players Rank To 1");
		switch (getOption())
		{
		case 1: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 448800;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);
		} break;
		case 2: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 1584350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 3: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 3075600;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 4: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 4691850;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 5: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 6433100;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 6: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 8299350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 7: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = 8299350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		}
		break;
	case Give_RP:
		addTitle("Give RP");
		addOption("Increase Players Rank By 50");
		addOption("Increase Players Rank By 100");
		addOption("Increase Players Rank By 150");
		addOption("Increase Players Rank By 200");
		addOption("Increase Players Rank By 250");
		addOption("Increase Players Rank By 300");
		switch (getOption())
		{
		case 1: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -448800;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);
		} break;
		case 2: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -1584350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 3: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -3075600;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 4: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -4691850;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 5: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -6433100;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 6: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -8299350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		case 7: {
			int Args[5];
			Args[0] = 0xD8;
			Args[1] = selectedPlayer;
			Args[2] = -8299350;
			Args[3] = 0;
			Args[4] = 0;
			TriggerScriptEvent(Args, 5, selectedPlayer);

		}break;
		}
		break;
#pragma region Ghost Rider Menu
	case Ghost_Rider_Menu2:

		addTitle("Ghost Rider Menu");
		addBoolOption("Ghost Rider", Ghost_RiderOnline); //3
		switch (getOption())
		{
		case 1:
			Ghost_RiderOnline = !Ghost_RiderOnline;
			Ghost_RiderOnline2 = !Ghost_RiderOnline2;
			Ghost_RiderOnline3 = !Ghost_RiderOnline3; break;
		}
		break;
#pragma endregion
#pragma region Explode Options
	case Explode_Options_Online:

		addTitle("Explode Options");
		//addOption("Attach to Player"); //case 1
		addOption("Grenade");
		addOption("Grenade Launcher");
		addOption("Stick Bomb");
		addOption("Molotov");
		addOption("Rocket");
		addOption("Tank Shell");
		addOption("Octane");
		addOption("Car");
		addOption("Plane");
		addOption("Petrol Pump");
		addOption("Bike");
		addOption("Dir Steam");
		addOption("Dir Flame");
		addOption("Dir Water Hydrant");
		addOption("Dir Gas Canister");
		addOption("Boat");
		addOption("Ship Destroy");
		addOption("Truck");
		addOption("Bullet");
		addOption("Smoke Grenade Launcher");
		addOption("Smoke Grenade");
		addOption("Bzgas");
		addOption("Flare");
		addOption("Gas Canister");
		addOption("Extinguisher");
		addOption("Pogrammablear");
		addOption("Train");
		addOption("Barrel");
		addOption("Propane");
		addOption("Blimp");
		addOption("Dir Flame Explode");
		addOption("Tanker");
		addOption("Plane Rocket");
		addOption("Vehicle Bullet");
		addOption("Gas Tank");
		switch (getOption())
		{
		case 1:
			ExplosionType = GRENADE;
			Explosions = true;
			break;
		case 2:
			ExplosionType = GRENADELAUNCHER;
			Explosions = true;
			break;
		case 3:
			ExplosionType = STICKYBOMB;
			Explosions = true;
			break;
		case 4:
			ExplosionType = MOLOTOV;
			Explosions = true;
			break;
		case 5:
			ExplosionType = ROCKET;
			Explosions = true;
		case 6:
			ExplosionType = TANKSHELL;
			Explosions = true;
			break;
		case 7:
			ExplosionType = HI_OCTANE;
			Explosions = true;
			break;
		case 8:
			ExplosionType = CAR;
			Explosions = true;
			break;
		case 9:
			ExplosionType = PLANE;
			Explosions = true;
			break;
		case 10:
			ExplosionType = PETROL_PUMP;
			Explosions = true;
			break;
		case 11:
			ExplosionType = BIKE;
			Explosions = true;
			break;
		case 12:
			ExplosionType = DIR_STEAM;
			Explosions = true;
			break;
		case 13:
			ExplosionType = DIR_FLAME;
			Explosions = true;
			break;
		case 14:
			ExplosionType = DIR_WATER_HYDRANT;
			Explosions = true;
			break;
		case 15:
			ExplosionType = DIR_GAS_CANISTER;
			Explosions = true;
			break;
		case 16:
			ExplosionType = BOAT;
			Explosions = true;
			break;
		case 17:
			ExplosionType = SHIP_DESTROY;
			Explosions = true;
			break;
		case 18:
			ExplosionType = TRUCK;
			Explosions = true;
			break;
		case 19:
			ExplosionType = BULLET;
			Explosions = true;
			break;
		case 20:
			ExplosionType = SMOKEGRENADELAUNCHER;
			Explosions = true;
			break;
		case 21:
			ExplosionType = SMOKEGRENADE;
			Explosions = true;
			break;
		case 22:
			ExplosionType = BZGAS;
			Explosions = true;
			break;
		case 23:
			ExplosionType = FLARE;
			Explosions = true;
			break;
		case 24:
			ExplosionType = GAS_CANISTER;
			Explosions = true;
			break;
		case 25:
			ExplosionType = EXTINGUISHER;
			Explosions = true;
			break;
		case 26:
			ExplosionType = PROGRAMMABLEAR;
			Explosions = true;
			break;
		case 27:
			ExplosionType = TRAIN;
			Explosions = true;
			break;
		case 28:
			ExplosionType = BARREL;
			Explosions = true;
			break;
		case 29:
			ExplosionType = PROPANE;
			Explosions = true;
			break;
		case 30:
			ExplosionType = BLIMP;
			Explosions = true;
			break;
		case 31:
			ExplosionType = DIR_FLAME_EXPLODE;
			Explosions = true;
			break;
		case 32:
			ExplosionType = TANKER;
			Explosions = true;
			break;
		case 33:
			ExplosionType = PLANE_ROCKET;
			Explosions = true;
			break;
		case 34:
			ExplosionType = VEHICLE_BULLET;
			Explosions = true;
			break;
		case 35:
			ExplosionType = GAS_TANK;
			Explosions = true;
			break;
		}
		break;
#pragma endregion
#pragma region Mean Stuff
	case Mean_Stuff_Online:

		addTitle("Mean Stuff");
		addOption("Cage Player"); //1
		addOption("Trap Player In Cage"); //2
		addOption("Kick Player"); //3
		addOption("Remove Weapons"); //4
		addBoolOption("Freeze Player", Freeze_Player); //5
		addTeleportOption("Freeze Console", 23.400757, 7640.037109, 17.566275);
		addTeleportOption("Freeze Console V2", 23.400757, 7640.037109, 17.566275);
		addIntOption("Enter Vehicle Model", &vehToSpawnHash, -99999999999999999, 99999999999999999, true); //5
		switch (getOption())
		{
		case 1:
		{
			float Position[3];
			int cage1;
			int cage2;
			ENTITY::GET_ENTITY_COORDS3(PLAYER::GET_PLAYER_PED(selectedPlayer), Position);
			cage1 = OBJECT::CREATE_OBJECT(2063962179, Position[0], Position[1], Position[2], 1, 1, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(cage1, PLAYER::GET_PLAYER_PED(selectedPlayer), -1, Position[0], Position[1], Position[2] - 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0);// end
			cage2 = OBJECT::CREATE_OBJECT(2063962179, Position[0], Position[1], Position[2], 1, 1, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(cage2, PLAYER::GET_PLAYER_PED(selectedPlayer), -1, Position[0], Position[1], Position[2] - 1.1, 0, 0, 90, 0, 0, 0, 0, 0, 0);// end
			ENTITY::FREEZE_ENTITY_POSITION(cage1, true);
			ENTITY::FREEZE_ENTITY_POSITION(cage2, true);
			ENTITY::DETACH_ENTITY(cage1, 0, 0);
			ENTITY::DETACH_ENTITY(cage2, 0, 0);
		} break;
		case 2:
		{
			int hash;
			hash = GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01");
			Vector3 coords;
			coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
			OBJECT::CREATE_OBJECT(hash, coords.x, coords.y, coords.z, 1, 1, 0);
		} break;
		case 3: {
			int NetworkOptions = selectedPlayer;
			int Args[3];
			Args[0] = 2;
			Args[1] = NetworkOptions;
			Args[2] = 0x35;
			TriggerScriptEvent(Args, 3, NetworkOptions);
		}break;
		case 4: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(selectedPlayer), true); break;
		case 5: Freeze_Player = !Freeze_Player; break;
		case 6: crashtest2 = !crashtest2;
			NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED(selectedPlayer));
			drawNotification("~g~Go to the player list to start the attack"); break;
		case 7: crashtest = !crashtest;
			NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED(selectedPlayer));
			drawNotification("~g~Go to the player list to start the attack"); break;
		}
		break;
#pragma endregion
#pragma region Shoot Bullet At Player
	case ShootBulletAtPlayer:

		addTitle("Shoot Bullet At Player");
		addOption("Tank Bullets"); //1
		addOption("Red Laser"); //2
		addOption("Green Laser"); //3
		addOption("Hunter"); //4
		addOption("Snowballs"); //5
		addOption("Stungun"); //6
		addOption("Combat MG"); //7
		addOption("Firework"); //8
		addOption("Gusenberg"); //9
		addOption("Special Carbine"); //10
		addOption("Heavy Pistol"); //11
		addOption("SNS Pistol"); //12
		addOption("Minigun"); //13
		addOption("Heavy Sniper"); //14
		addOption("RPG"); //15
		addOption("Assault Rifle"); //16
		switch (getOption())
		{
		case 1:
			BulletAtPlayerString = "VEHICLE_WEAPON_TANK";
			ShootBulletAPlayer = true;
			break;
		case 2:
			BulletAtPlayerString = "VEHICLE_WEAPON_ENEMY_LASER";
			ShootBulletAPlayer = true;
			break;
		case 3:
			BulletAtPlayerString = "VEHICLE_WEAPON_PLAYER_LASER";
			ShootBulletAPlayer = true;
			break;
		case 4:
			BulletAtPlayerString = "VEHICLE_WEAPON_PLAYER_HUNTER";
			ShootBulletAPlayer = true;
			break;
		case 5:
			BulletAtPlayerString = "WEAPON_SNOWBALL";
			ShootBulletAPlayer = true;
			break;
		case 6:
			BulletAtPlayerString = "WEAPON_STUNGUN";
			ShootBulletAPlayer = true;
			break;
		case 7:
			BulletAtPlayerString = "WEAPON_COMBATMG";
			ShootBulletAPlayer = true;
			break;
		case 8:
			BulletAtPlayerString = "WEAPON_FIREWORK";
			ShootBulletAPlayer = true;
			break;
		case 9:
			BulletAtPlayerString = "WEAPON_GUSENBERG";
			ShootBulletAPlayer = true;
			break;
		case 10:
			BulletAtPlayerString = "WEAPON_SPECIALCARBINE";
			ShootBulletAPlayer = true;
			break;
		case 11:
			BulletAtPlayerString = "WEAPON_HEAVYPISTOL";
			ShootBulletAPlayer = true;
			break;
		case 12:
			BulletAtPlayerString = "WEAPON_SNSPISTOL";
			ShootBulletAPlayer = true;
			break;
		case 13:
			BulletAtPlayerString = "WEAPON_MINIGUN";
			ShootBulletAPlayer = true;
			break;
		case 14:
			BulletAtPlayerString = "WEAPON_HEAVYSNIPER";
			ShootBulletAPlayer = true;
			break;
		case 15:
			BulletAtPlayerString = "WEAPON_RPG";
			ShootBulletAPlayer = true;
			break;
		case 16:
			BulletAtPlayerString = "WEAPON_ASSAULTRIFLE";
			ShootBulletAPlayer = true;
			break;
		}
		break;
#pragma endregion
#pragma region Attach Object Menu
	case Attachement_Menu_Online:

		addTitle("Attach Objects");
		addOption("Attach to Player"); //case 1
		addOption("Attach to Player's Head"); //case 2
		addOption("Detach from Player"); //case 3
		addOption("Attach Mercs"); //case 5
		addAttachmentOption("Attach Alien Egg", 1803116220, 31086, 0.2, 0, 0, 0, 90.0, 0); //case 6
		addAttachmentOption("Attach Cone", -1587301201, 31086, 0.1, 0.02, 0, 0, 90.0, 0); //case 7
		addAttachmentOption("Attach Innertube", 1677315747, 11816, 0.0, 0, 0, 0, -90.0, 0); //case 8
		addAttachmentOption("Attach Beach Ball", 1017479830, 31086, 0.05, 0, 0, 0, 90.0, 0); //case 9
		addAttachmentOption("Attach Beach Umbrella", -2108662770, 57597, -0.54, 0, 0, 0, 90.0, 0); //case 10
		addAttachmentOption("Attach Campfire", -1065766299, 31086, 0.21, 0.02, 0, 0, 90.0, 0); //case 11
		addAttachmentOption("Attach Sprinkler", 946782395, 31086, 0.1, 0.02, 0, 0, 90.0, 0); //case 12
		addAttachmentOption("Attach Porta-Potty", 682074297, 57597, -1.0, 0, 0, 0, -90.0, 180.0); //case 13
		addAttachmentOption("Attach Chandelier", -1720704599, 57597, 0, 0, 0, 0, -90.0, 0); //case 14
		addAttachmentOption("Attach Light", -1874162628, 57597, 0.0, 0.5, 0, 0, -90.0, 180.0); //case 15
		addAttachmentOption("Attach Artifact", -956377380, 31086, 0.05, 0, 0, 0, 90.0, 0); //case 16
		addAttachmentOption("Attach Riot Shield", -547381377, 28422, 0.35, 0, -0.1, 0, 90.0, 90.0); //case 17
		addAttachmentOption("Attach Space Pistol", -1114972153, 28422, 0.273, 0.05, 0.0, -90.0, 0.0, 0.0); //case 18
		addOption("Attach Minigun Cannons"); //case 19
		addAttachmentOption("Attach Katana to back", -491126417, 24817, 0.54, -0.15, -0.08, 5.5, -75.0, 0.0); //case 20
		addAttachmentOption("Attach Creator Object", objecthandle, -1, 0, 0, 0, 0, 0, 0); //case 22
		switch (getOption())
		{
		case 1:
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(selectedPlayer), -1, 0.0, -0.3, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmjosh2", "josh_sitting_loop");
			break;
		case 2:
			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(selectedPlayer), -1, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			break;
		case 3:
			ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			break;
		case 4:
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(0xB881AEE))
			{
				if (STREAMING::IS_MODEL_VALID(0xB881AEE))
				{
					STREAMING::REQUEST_MODEL(0xB881AEE);
					if (STREAMING::HAS_MODEL_LOADED(0xB881AEE))
					{
						int ped1 = PED::CREATE_PED(0x1A, 0xB881AEE, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped1, 0xB1CA77B1, 9999, 1);
						ENTITY::SET_ENTITY_INVINCIBLE(ped1, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(ped1, PLAYER::GET_PLAYER_PED(selectedPlayer), -1, 0.0, -0.6, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
					}
				}
			}
		}break;
		case 19: {
			int model = -929681224;
			STREAMING::REQUEST_MODEL(model);
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Attachcoords2;
			Attachcoords2 = ENTITY::GET_ENTITY_COORDS(ped, 1);
			int Bone = PED::GET_PED_BONE_INDEX(ped, 24817);
			if (STREAMING::HAS_MODEL_LOADED(model)) {
				int attachobj1 = OBJECT::CREATE_OBJECT(model, Attachcoords2.x, Attachcoords2.y, Attachcoords2.z, 0, 0, 0);
				int attachobj2 = OBJECT::CREATE_OBJECT(model, Attachcoords2.x, Attachcoords2.y, Attachcoords2.z, 0, 0, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(attachobj1, ped, Bone, 0.4, 0.115, 0.2, -90.0, -90.0, 0.0, 0, 0, 0, 0, 0, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(attachobj2, ped, Bone, 0.4, 0.115, -0.2, -90.0, -90.0, 0.0, 0, 0, 0, 0, 0, 0);
			}}
				 break;

		}
		break;
#pragma endregion
#pragma region Set Stuff On Player Options
	case SetStuffOnPlayerOptions:

		addTitle("Set Stuff On Ped Options");
		addOption("Send Army After Player");
		/*addSubmenuOption("Tanks On Player Option", SetTanksOnPlayer); //1
		addSubmenuOption("Hydras On Player Options",SetHydrasOnPlayer); //2
		addSubmenuOption("Jets On Player Options", SetJetsOnPlayer); //3
		addSubmenuOption("Cops On Player Options", SetCopsOnPlayer); //4
		addSubmenuOption("Swat On Player Options", SetSwatOnPlayer); //5
		addSubmenuOption("FIB On Player Options", SetFIBOnPlayer); //5
		addSubmenuOption("Insurgents On Player Options", SetInsurgentsOnPlayer); //6
		addSubmenuOption("Savages On Player Options", SetSavagesOnPlayer); //7
		addSubmenuOption("Clowns On Player Options", SetKillerClownsOnPlayer); //8
		*/
		switch (getOption())
		{
		case 1:
			sendArmyAttackers();
			break;
		}
		break;
#pragma endregion
#pragma region Tanks On Player Option
	case SetTanksOnPlayer:

		addTitle("Tanks On Player Option");
		AddOptionPedSpawner("Spawn Tank Driver", 1634506681); //1
		addVehicleOption("Spawn Tank", -163714847); //2
		addOption("Set Tank Driver In Tank"); //3
		addOption("Send Tanks After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Hydras On Player Options
	case SetHydrasOnPlayer:

		addTitle("Hydras On Player Options");
		AddOptionPedSpawner("Spawn Hydra Driver", 0x39D6E83F); //1
		addVehicleOption("Spawn Hydra", -163714847); //2
		addOption("Set Hydra Driver In Hydra"); //3
		addOption("Send Hydra After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Jets On Player Options
	case SetJetsOnPlayer:

		addTitle("Jets On Player Options");
		AddOptionPedSpawner("Spawn Jets Driver", 0x39D6E83F); //1
		addVehicleOption("Spawn Jet", 0xB39B0AE6); //2
		addOption("Set Jet Driver In Jet"); //3
		addOption("Send Jet After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Cops On Player Options
	case SetCopsOnPlayer:

		addTitle("Cops On Player Options");
		AddOptionPedSpawner("Spawn Cop Driver", 1581098148); //1
		addVehicleOption("Spawn Cop Car", 0x71FA16EA); //2
		addOption("Set Cop Driver In Cop Car"); //3
		addOption("Send Cops After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PedID, 0x1D073A89, 9999, 1); // pump shotgun
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Swat On Player Options
	case SetSwatOnPlayer:

		addTitle("Swat On Player Options");
		AddOptionPedSpawner("Spawn Swat Driver", 1581098148); //1
		addVehicleOption("Spawn Swat Van", 0xB822A1AA); //2
		addOption("Set Swat Driver In Swat Van"); //3
		addOption("Send Swat After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PedID, 0x83BF0278, 9999, 1); // carbine rifle
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region FIB On Player Options
	case SetFIBOnPlayer:

		addTitle("FIB On Player Options");
		AddOptionPedSpawner("Spawn FIB Driver", 0x8D8F1B10); //1
		addVehicleOption("Spawn FIB Car", 0x432EA949); //2
		addOption("Set FIB Driver In FIB Car"); //3
		addOption("Send FIB After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PedID, 0x83BF0278, 9999, 1); // carbine rifle
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Insurgents On Player Options
	case SetInsurgentsOnPlayer:

		addTitle("Insurgents On Player Options");
		AddOptionPedSpawner("Spawn Insurgent Driver", 0xB3F3EE34); //1
		addVehicleOption("Spawn Insurgent", 0x9114EADA); //2
		addOption("Set Insurgents Driver In Insurgents"); //3
		addOption("Send Insurgents After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Savages On Player Options
	case SetSavagesOnPlayer:

		addTitle("Savages On Player Options");
		AddOptionPedSpawner("Spawn Savage Driver", 0xB3F3EE34); //1
		addVehicleOption("Spawn Savage", 0xFB133A17); //2
		addOption("Set Savage Driver In Savage"); //3
		addOption("Send Savage After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion
#pragma region Clowns On Player Options
	case SetKillerClownsOnPlayer:

		addTitle("Clowns On Player Options");
		AddOptionPedSpawner("Spawn Clowns Driver", 0x4498DDE); //1
		addVehicleOption("Spawn Clown Van", 0x2B6DC64A); //2
		addOption("Set Clown Driver In Clown Van"); //3
		addOption("Send Clown After Player"); //4
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3:
			//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PedID, 0x42BF8A85, 9999, 1); // minigun
			PED::SET_PED_INTO_VEHICLE(PedID, VehicleID, -1);  break;
		case 4:
			AI::TASK_VEHICLE_CHASE(PedID, PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		}
		break;
#pragma endregion 
#pragma region Vehicle Menu Online
	case Vehicle_MenuOnline:

		addTitle("Vehicle Menu");
		addSubmenuOption("Vehicle Options", Vehicle_Options_Online);
		addSubmenuOption("Vehicle Spawner", OnlineCarSpawner);
		addSubmenuOption("Acrobatics", Vehicle_Acrobatics);
		break;
#pragma endregion



#pragma region Player Options
	case Player_Options_Online:

		addTitle("Player Options");
		addOption("Clone Player");//1
		addBoolOption("Show Player Info", pinfo); //3
		addBoolOption("Spectate Player", SPECTATE);
		switch (getOption())
		{
		case 1:
			Vector3 coords2;
			coords2 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
			PED::CLONE_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), coords2.x, coords2.y, coords2.z); break;
		case 2:
			onlinePlayerinfo = PLAYER::GET_PLAYER_PED(selectedPlayer);
			onlinePlayerinfo1 = selectedPlayer;
			if (!pinfo)
			{
				PrintHeadset = true;
				pinfo = true;
			}
			else if (pinfo)
			{
				pinfo = false;
				PrintHeadset = false;
			} break;
		case 3: SPECTATE = !SPECTATE; break;
		}
		//various player options here
		//use PLAYER::GET_PLAYER_PED(selectedPlayer) to get the ped rather than player.
		break;
#pragma endregion
#pragma region Nice Stuff
	case Nice_Stuff_Online:

		addTitle("Nice Stuff");
		addOption("Give All Weapons"); //1
		addBoolOption("Weapon Drop", Weapon_Drop); //2
		addBoolOption("Ammo Drop", Ammo_Drop); //3
		addBoolOption("Never Wanted", neverwantedonline); //4
		addBoolOption("Give Health", Give_Health); //5
		addBoolOption("Give Player Money", Cash_Drop); //6
		addBoolOption("40K Cash Drop", Cash_Drop40K); //7
		addBoolOption("Insane Cash Drop", Cash_DropInsane); //8
		addBoolOption("Snack Drop", Snack_Drop); //9
		addBoolOption("Armour Drop", Armour_Drop); //10
		addBoolOption("Protect against crashes", ProtectionTest4); //10
		switch (getOption())
		{
		case 1:
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x3656C8C1, 9999, 1); // stun gun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x99B507EA, 9999, 1); // knife
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x678B81B1, 9999, 1); // night stick
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x4E875F73, 9999, 1); // hammer
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x958A4A8F, 9999, 1); // bat
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x440E4788, 9999, 1); // golf club
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x84BD7BFD, 9999, 1); // crowbar
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1B06D571, 9999, 5); // pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x5EF9FEC4, 9999, 1); // combat pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x22D8FE39, 9999, 1); // ap pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x99AEEB3B, 9999, 1); // pistol 50.
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x13532244, 9999, 1); // micro smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x2BE6766B, 9999, 1); // smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xEFE7E2DF, 9999, 1); // assault smg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xBFEFFF6D, 9999, 1); // assault rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x83BF0278, 9999, 1); // carbine rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xAF113F99, 9999, 1); // advanced rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x9D07F764, 9999, 1); // MG
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x7FD62962, 9999, 1); // combat mg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1D073A89, 9999, 1); // pump shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x7846A318, 9999, 1); // sawnoff shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xE284C527, 9999, 1); // assault shotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x9D61E50F, 9999, 1); // bullpupshotgun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x05FC3C11, 9999, 1); // sniper
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x0C472FE2, 9999, 1); // heavy sniper
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xA284510B, 9999, 1); // grenade launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xB1CA77B1, 9999, 1); // rpg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x42BF8A85, 9999, 1); // minigun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x93E220BD, 9999, 1); // grenades
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x2C3731D9, 9999, 1); // sticky bomb
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xFDBC8A50, 9999, 1); // smoke grenade
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x34A67B97, 9999, 1); // petrol can
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x060EC506, 9999, 1); // fire extinguisher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x24B17070, 9999, 1); // moltovs
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x497FACC3, 9999, 1); // flare
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xFDBADCED, 9999, 1); // digiscanner
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x687652CE, 9999, 1); // stinger
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 600439132, 9999, 1); // ball
																											//DLC Weapons
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xF9E6AA4B, 9999, 1); // bottle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x61012683, 9999, 1); // gusenerg
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xC0A3098D, 9999, 1); // special carbine
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xD205520E, 9999, 1); // heavy pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xBFD21232, 9999, 1); // sns pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x7F229F94, 9999, 1); // bullpup rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x92A27487, 9999, 1); // dagger
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x083839C4, 9999, 1); // vintage pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x7F7497E5, 9999, 1); // firework launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xA89CB99E, 9999, 1); // musket
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x63AB0442, 9999, 1); // homing launcher
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xAB564B93, 9999, 1); // proxmine
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x787F0BB, 9999, 1); // snowball
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xC734385A, 9999, 1); // marksman rifle
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x47757124, 9999, 1); // flare gun
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xE232C28C, 9999, 1); // trash bag
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xDC4DB296, 9999, 1); // Marksman Pistol
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0xD8DF3C3C, 9999, 1); // Knuckle Duster
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x0A3D4D34, 9999, 1);  break;
		case 2: Weapon_Drop = !Weapon_Drop; break;
		case 3: Ammo_Drop = !Ammo_Drop; break;
		case 4: neverwantedonline = !neverwantedonline; break;
		case 5: Give_Health = !Give_Health; break;
		case 6: Cash_Drop = !Cash_Drop; break;
		case 7: Cash_Drop40K = !Cash_Drop40K; break;
		case 8: Cash_DropInsane = !Cash_DropInsane; break;
		case 9: Snack_Drop = !Snack_Drop; break;
		case 10: Armour_Drop = !Armour_Drop; break;
		case 11: ProtectionTest4 = !ProtectionTest4; break;
		}
		break;
#pragma endregion
#pragma region Nice Stuff
	case cashdrop_options:
		addTitle("Cash Drop Options");
		addSubmenuOption("Money Object Bypass", cashdrop_options2);
		addBoolOption("Start Cash Drop [~g~Normal~s~]", Cashdropadv); //7
		addBoolOption("Start Cash Drop [~g~Object~s~]", Cashdropadv2); //7
		addIntOption("Money Amount", &amount, 0, 999999999, true, true);
		addIntOption("Money Radius", &MoneyRange_, 0, 200, true, true);
		addFloatOption("Money Z Coord", &moneyzcoord, -255.0f, 255.0f, true);
		switch (getOption())
		{
		case 2: Cashdropadv = !Cashdropadv; break;
		case 3: Cashdropadv2 = !Cashdropadv2; break;
		}
		break;
#pragma endregion
#pragma region FullAttacList
	case cashdrop_options2:
		addTitle("Object List");
		for (llvar = 0; llvar < 3415; llvar++)
		{
			addCashption(AllPROPS[llvar]);
		}
		break;
#pragma endregion

	case Vehicle_Acrobatics:

		addTitle("Acrobatics");
		addOption("Flip Upright");
		addOption("Front Flip");
		addOption("Back Flip");
		addOption("Kick Flip");
		addOption("Heel Flip");
		addOption("Bunny Hop");
		addOption("Launch Up");
		addOption("Crush Vehicle");
		switch (getOption())
		{
		case 1:
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
				}
			}
		}
		break;
		case 2://front flip
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
				}
			}
		}
		break;
		case 3://back flip
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
				}
			}
		}
		break;
		case 4://kick flip
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
				}
			}
		}
		break;
		case 5://heel flip
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 5.0f, -2.0f, 0, 0, true, true, true, true, false, true);
				}
			}
		}
		break;

		case 6://bunny hop
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
				}
			}
		}
		break;

		case 7://launch up
		{

			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, 40.0f, 0, 0, 0, true, true, true, true, false, true);
				}
			}
		}
		break;

		case 8://crush
		{
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, true, 0, 0, -40.0f, 0, 0, 0, true, true, true, true, false, true);
				}
			}}
		break;
		}
		break;
#pragma region Vehicle Options
	case Vehicle_Options_Online:

		addTitle("Vehicle Options");
		addOption("Vehicle Miniguns"); //case 1
		addOption("Toggle Freeze Vehicle"); //case 2
		addOption("Vehicle God Mode Off"); //case 3
		addOption("Vehicle Invisibility Off"); //case 4
		addOption("Paint Random"); //case 5
		addOption("Paint Chrome"); //case 6
		addOption("Paint Pink");  //case 7
		addOption("Paint Blue Angels"); //case 8
		addOption("Stall And Light On Fire"); //case 9
		addOption("Launch Players Vehicle In Sky"); //case 10
		addOption("Boost Player Vehicle"); //case 11
		addOption("Flip 180 Vehicle"); //case 12
		addOption("Tow Truck"); //case 13
		addOption("Remote Control Car"); //case 14
		addOption("Detach Towtruck / RC"); //case 15
		addOption("Lock Player Doors"); //case 16
		addOption("Unlock Player Doors"); //case 17
		addOption("Delete Vehicle"); //case 18
		switch (getOption())
		{
		case 1: break;
		case 2: {
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, true);
					//VehFrozen = true;
				}
				else if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && ENTITY::IS_ENTITY_STATIC(vehicle)) {
					ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);
					//VehFrozen = false;
				}
			}}
				break;
		case 3: {
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0)) {
					if (ENTITY::DOES_ENTITY_EXIST(vehicle) && ENTITY::IS_ENTITY_A_VEHICLE(vehicle)) {
						printf("ENTITY::IS_ENTITY_A_VEHICLE == true, ");
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, true);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicle, true);
						ENTITY::SET_ENTITY_INVINCIBLE(vehicle, false);
						ENTITY::SET_ENTITY_PROOFS(vehicle, false, false, false, false, false, false, false, false);
						VEHICLE::SET_VEHICLE_STRONG(vehicle, false);
					}
					else {
					}
				}
			}}
				break;
		case 4: {
			int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (RequestNetworkControl(player, vehicle)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(player, 0)) {
					if (ENTITY::DOES_ENTITY_EXIST(vehicle) && ENTITY::IS_ENTITY_A_VEHICLE(vehicle)) {
						printf("ENTITY::IS_ENTITY_A_VEHICLE == true, ");
						ENTITY::SET_ENTITY_VISIBLE(vehicle, true);
					}
					else {
					}
				}
			}}
				break;
		case 5: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0.0f);
				VEHICLE::SET_VEHICLE_COLOURS(Vehicle, irand(0, 255, 1), irand(0, 255, 2));
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Vehicle, irand(0, 255, 3), irand(0, 255, 4));
			}}
				break;
		case 6: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0.0f);
				VEHICLE::SET_VEHICLE_COLOURS(Vehicle, 120, 120);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Vehicle, 120, 120);
			}}
				break;
		case 7: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0.0f);
				VEHICLE::SET_VEHICLE_COLOURS(Vehicle, 135, 135);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Vehicle, 135, 135);
			}}
				break;
		case 8: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0.0f);
				VEHICLE::SET_VEHICLE_COLOURS(Vehicle, 64, 89);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Vehicle, 64, 0);
			}}
				break;
		case 9: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle, -1);
				VEHICLE::SET_VEHICLE_UNDRIVEABLE(Vehicle, 1);
			}}
				break;
		case 10: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, true, 0, 0, 150, 0, 0, 0, true, true, true, true, false, true);
			}}
				 break;
		case 11: {
			int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);
			if (RequestNetworkControl(Player, Vehicle)) {
				ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, true, 0, 30, 0, 0, 0, 0, true, true, true, true, false, true);
			}}
				 break;
		case 12: break;
		case 13: break;
		case 14: break;
		case 15: break;
		}
		break;
#pragma endregion
#pragma region Favorites
	case funny_cars:
		addTitle("Funny Cars");
		addOption("Trolley Bike");
		addOption("Wheelbarrow Bike");
		addOption("Bumpercar");
		addOption("Wheelchair Quad");
		addOption("Couch Car");
		addOption("Toilet Quad");

		if (getOption() == 1)
		{
			doTrolley = true;
		}
		if (getOption() == 2)
		{
			doWheelbarrow = true;
		}
		if (getOption() == 3)
		{
			doBumpercar = true;
		}
		if (getOption() == 4)
		{
			doWheelchair = true;
		}
		if (getOption() == 5)
		{
			doCouch = true;
		}
		if (getOption() == 6)
		{
			spawnToilet();
		}
		break;
#pragma endregion
#pragma region Vehicle Spawner
	case OnlineCarSpawner:
		VehicleSpawner_Sprite();
		addTitle("Vehicle Spawner");
		addKeyboardOption("Custom Input", 3, "", 150);
		addSubmenuOption("Favorites", Vehicle_Online_Favorites);
		addSubmenuOption("Super", Vehicle_Online_Super);
		addSubmenuOption("Sports", Vehicle_Online_Sports);
		addSubmenuOption("Coupes", Vehicle_Online_Coupes);
		addSubmenuOption("Sedans", Vehicle_Online_Sedans);
		addSubmenuOption("Emergency", Vehicle_Online_Emergency);
		addSubmenuOption("Off Road", Vehicle_Online_OffRoad);
		addSubmenuOption("Muscle", Vehicle_Online_Muscle);
		addSubmenuOption("SUVs", Vehicle_Online_SUVs);
		addSubmenuOption("Motorcycles", Vehicle_Online_Motorcycles);
		addSubmenuOption("Helicopters", Vehicle_Online_Helicopters);
		addSubmenuOption("Planes", Vehicle_Online_Planes);
		addSubmenuOption("Commercial", Vehicle_Online_Commercial);
		addSubmenuOption("Bicycles", Vehicle_Online_Bicycles);
		addSubmenuOption("Boats", Vehicle_Online_Boats);
		addSubmenuOption("Industrial", Vehicle_Online_Industrial);
		addSubmenuOption("Utility", Vehicle_Online_Utility);
		addSubmenuOption("Trailers", Vehicle_Online_Trailers);
		addSubmenuOption("Compacts", Vehicle_Online_Compacts);
		addSubmenuOption("Military", Vehicle_Online_Military);
		addSubmenuOption("Service", Vehicle_Online_Service);
		addSubmenuOption("Sports Classics", Vehicle_Online_SportsClassics);
		addSubmenuOption("Vans", Vehicle_Online_Vans);
		break;
#pragma endregion
#pragma region Favorites
	case Vehicle_Online_Favorites:
		VehicleSpawner_Sprite();
		addTitle("Favorites");
		addOnlineVehicleOption("Hydra", 0x39D6E83F);
		addOnlineVehicleOption("Lazer", 0xB39B0AE6);
		addOnlineVehicleOption("Hakuchou", 0x4B6C568A);
		addOnlineVehicleOption("Buzzard", 0x2F03547B);
		addOnlineVehicleOption("Tank", 0x2EA68690);
		addOnlineVehicleOption("FIB", 0x432EA949);
		addOnlineVehicleOption("FIB2", 0x9DC66994);
		addOnlineVehicleOption("Police", 0x71FA16EA);
		addOnlineVehicleOption("Police Buffalo", 0x9F05F101);
		addOnlineVehicleOption("Unmarked", 0x8A63C7B9);
		addOnlineVehicleOption("Jester2", 0xBE0E6126);
		addOnlineVehicleOption("Dubsta 6x6", 0xB6410173);
		addOnlineVehicleOption("Monster", 0xCD93A7DB);
		addOnlineVehicleOption("Mesa(Mercs)", 0x84F42E51);
		addOnlineVehicleOption("Phantom", 0x809AA4CB);
		addOnlineVehicleOption("Bus", 0xD577C962);
		addOnlineVehicleOption("Speeder", 0x0DC60D2B);
		addOnlineVehicleOption("Blimp", 0xF7004C86);
		addOnlineVehicleOption("Jumbo Jet", 0x3F119114);
		addOnlineVehicleOption("Insurgent", 0x9114EADA);
		addOnlineVehicleOption("Technical", 0x83051506);
		addOnlineVehicleOption("Cargo Plane", 0x15F27762);
		addOnlineVehicleOption("Dozer", 0x7074F39D);
		break;
#pragma endregion
#pragma region Super
	case Vehicle_Online_Super:
		VehicleSpawner_Sprite();
		addTitle("Super");
		addOnlineVehicleOption("Adder", 0xB779A091);
		addOnlineVehicleOption("Bullet", 0x9AE6DDA1);
		addOnlineVehicleOption("Cheetah", 0xB1D95DA0);
		addOnlineVehicleOption("EntityXF", 0xB2FE5CF9);
		addOnlineVehicleOption("Infernus", 0x18F25AC7);
		addOnlineVehicleOption("TurismoR", 0x185484E1);
		addOnlineVehicleOption("Vacca", 0x142E0DC3);
		addOnlineVehicleOption("Voltic", 0x9F4B77BE);
		addOnlineVehicleOption("Zentorno", 0xAC5DF515);
		addOnlineVehicleOption("Osiris", 0x767164D6);
		addOnlineVehicleOption("T20", 0x6322B39A);
		break;
#pragma endregion
#pragma region Sports
	case Vehicle_Online_Sports:
		VehicleSpawner_Sprite();
		addTitle("Sports");
		addOnlineVehicleOption("9F", 0x3D8FA25C);
		addOnlineVehicleOption("9F Convertible", 0xA8E38B01);
		addOnlineVehicleOption("Alpha", 0x2DB8D1AA);
		addOnlineVehicleOption("Banshee", 0xC1E908D2);
		addOnlineVehicleOption("Buffalo", 0xEDD516C6);
		addOnlineVehicleOption("Franklins Buffalo", 0x2BEC3CBE);
		addOnlineVehicleOption("Carbonizzare", 0x7B8AB45F);
		addOnlineVehicleOption("Comet", 0xC1AE4D16);
		addOnlineVehicleOption("Coquette", 0x067BC037);
		addOnlineVehicleOption("Elegy", 0xDE3D9D22);
		addOnlineVehicleOption("Feltzer", 0x8911B9F5);
		addOnlineVehicleOption("FuroreGT", 0xBF1691E0);
		addOnlineVehicleOption("Fusilade", 0x1DC0BA53);
		addOnlineVehicleOption("Kumura", 0xAE2BFE94);
		addOnlineVehicleOption("Kumura2", 0x187D938D);
		addOnlineVehicleOption("Futo", 0x7836CE2F);
		addOnlineVehicleOption("Jester", 0xB2A716A3);
		addOnlineVehicleOption("Jester2", 0xBE0E6126);
		addOnlineVehicleOption("Khamelion", 0x206D1B68);
		addOnlineVehicleOption("Massacro", 0xF77ADE32);
		addOnlineVehicleOption("Massacro2", 0xDA5819A3);
		addOnlineVehicleOption("Penumbra", 0xE9805550);
		addOnlineVehicleOption("Rapid GT", 0x8CB29A14);
		addOnlineVehicleOption("Rapid GT Convertible", 0x679450AF);
		addOnlineVehicleOption("Schwartzer", 0xD37B7976);
		addOnlineVehicleOption("Sultan", 0x39DA2754);
		addOnlineVehicleOption("Surano", 0x16E478C1);
		break;
#pragma endregion
#pragma region Coupes
	case Vehicle_Online_Coupes:
		VehicleSpawner_Sprite();
		addTitle("Coupes");
		addOnlineVehicleOption("Cognoscenti", 0x13B57D8A);
		addOnlineVehicleOption("Exemplar", 0xFFB15B5E);
		addOnlineVehicleOption("F620", 0xDCBCBE48);
		addOnlineVehicleOption("Felon", 0xE8A8BDA8);
		addOnlineVehicleOption("Felon2", 0xFAAD85EE);
		addOnlineVehicleOption("Jackal", 0xDAC67112);
		addOnlineVehicleOption("Oracle", 0x506434F6);
		addOnlineVehicleOption("Oracle2", 0xE18195B2);
		addOnlineVehicleOption("Sentinel", 0x50732C82);
		addOnlineVehicleOption("Sentinel2", 0x3412AE2D);
		addOnlineVehicleOption("Zion", 0xBD1B39C3);
		addOnlineVehicleOption("Zion2", 0xB8E2AE18);
		addOnlineVehicleOption("Windsor", 0x5E4327C8);
		break;
#pragma endregion
#pragma region Sedans
	case Vehicle_Online_Sedans:
		VehicleSpawner_Sprite();
		addTitle("Sedans");
		addOnlineVehicleOption("Asea", 0x94204D89);
		addOnlineVehicleOption("Snow Asea", 0x9441D8D5);
		addOnlineVehicleOption("Asterope", 0x8E9254FB);
		addOnlineVehicleOption("Emperor", 0xD7278283);
		addOnlineVehicleOption("Rusty Emperor", 0x8FC3AADC);
		addOnlineVehicleOption("Snow Emperor", 0xB5FCF74E);
		addOnlineVehicleOption("Fugitive", 0x71CB2FFB);
		addOnlineVehicleOption("Glendale", 0x047A6BC1);
		addOnlineVehicleOption("Ingot", 0xB3206692);
		addOnlineVehicleOption("Intruder", 0x34DD8AA1);
		addOnlineVehicleOption("Premier", 0x8FB66F9B);
		addOnlineVehicleOption("Primo", 0xBB6B404F);
		addOnlineVehicleOption("Regina", 0xFF22D208);
		addOnlineVehicleOption("Romero Hearse", 0x2560B2FC);
		addOnlineVehicleOption("Schafter", 0xB52B5113);
		addOnlineVehicleOption("Stanier", 0xA7EDE74D);
		addOnlineVehicleOption("Stratum", 0x66B4FC45);
		addOnlineVehicleOption("Stretch", 0x8B13F083);
		addOnlineVehicleOption("Super Diamond", 0x42F2ED16);
		addOnlineVehicleOption("Surge", 0x8F0E3594);
		addOnlineVehicleOption("Tailgater", 0xC3DDFDCE);
		addOnlineVehicleOption("Warrener", 0x51D83328);
		addOnlineVehicleOption("Washington", 0x69F06B57);
		break;
#pragma endregion
#pragma region Emergency
	case Vehicle_Online_Emergency:
		VehicleSpawner_Sprite();
		addTitle("Emergency");
		addOnlineVehicleOption("Ambulance", 0x45D56ADA);
		addOnlineVehicleOption("FIB", 0x432EA949);
		addOnlineVehicleOption("FIB2", 0x9DC66994);
		addOnlineVehicleOption("Fire Truck", 0x73920F8E);
		addOnlineVehicleOption("Life Guard", 0x1BF8D381);
		addOnlineVehicleOption("Park Ranger", 0x2C33B46E);
		addOnlineVehicleOption("Police Bike", 0xFDEFAEC3);
		addOnlineVehicleOption("Police Cruiser", 0x79FBB0C5);
		addOnlineVehicleOption("Police", 0x71FA16EA);
		addOnlineVehicleOption("Police Buffalo", 0x9F05F101);
		addOnlineVehicleOption("Prison Bus", 0x885F3671);
		addOnlineVehicleOption("Riot", 0xB822A1AA);
		addOnlineVehicleOption("Police Van", 0x1B38E955);
		addOnlineVehicleOption("Sheriff Cruiser", 0x9BAA707C);
		addOnlineVehicleOption("Sheriff SUV", 0x72935408);
		addOnlineVehicleOption("Snow Police Rancher", 0xA46462F7);
		addOnlineVehicleOption("Snow Police Esperanto", 0x95F4C618);
		addOnlineVehicleOption("Unmarked", 0x8A63C7B9);
		break;
#pragma endregion
#pragma region OffRoad
	case Vehicle_Online_OffRoad:
		VehicleSpawner_Sprite();
		addTitle("Off Road");
		addOnlineVehicleOption("Brawler", 0xA7CE1BC5);
		addOnlineVehicleOption("Bifta", 0xEB298297);
		addOnlineVehicleOption("Blazer", 0x8125BCF9);
		addOnlineVehicleOption("Lifeguard Blazer", 0xFD231729);
		addOnlineVehicleOption("Trevors Blazer", 0xB44F0582);
		addOnlineVehicleOption("Bodhi", 0xAA699BB6);
		addOnlineVehicleOption("Dubsta 6x6", 0xB6410173);
		addOnlineVehicleOption("Dune", 0x9CF21E0F);
		addOnlineVehicleOption("Duneloader", 0x698521E3);
		addOnlineVehicleOption("Injection", 0x432AA566);
		addOnlineVehicleOption("Kalahari", 0x05852838);
		addOnlineVehicleOption("Monster", 0xCD93A7DB);
		addOnlineVehicleOption("Mesa(Mercs)", 0x84F42E51);
		addOnlineVehicleOption("RancherXL", 0x6210CBB0);
		addOnlineVehicleOption("Rusty Rebel", 0xB802DD46);
		addOnlineVehicleOption("Clean Rebel", 0x8612B64B);
		addOnlineVehicleOption("SandkingSWB", 0x3AF8C345);
		addOnlineVehicleOption("SandkingXL", 0xB9210FD0);
		addOnlineVehicleOption("Snow Rancher", 0x7341576B);
		addOnlineVehicleOption("Space Docker", 0x1FD824AF);
		addOnlineVehicleOption("Insurgent", 0x9114EADA);
		addOnlineVehicleOption("Insurgent2", 0x7B7E56F0);
		break;
#pragma endregion
#pragma region Muscle
	case Vehicle_Online_Muscle:
		VehicleSpawner_Sprite();
		addTitle("Muscle");
		addOnlineVehicleOption("Chino", 0x14D69010);
		addOnlineVehicleOption("Blackfin", 0x2EC385FE);
		addOnlineVehicleOption("Blade", 0xB820ED5E);
		addOnlineVehicleOption("Buccaneer", 0xD756460C);
		addOnlineVehicleOption("Dominator", 0x04CE68AC);
		addOnlineVehicleOption("Gauntlet", 0x94B395C5);
		addOnlineVehicleOption("Hotknife", 0x0239E390);
		addOnlineVehicleOption("Phoenix", 0x831A21D5);
		addOnlineVehicleOption("Picador", 0x59E0FBF3);
		addOnlineVehicleOption("Rat Loader", 0xD83C13CE);
		addOnlineVehicleOption("Rat Loader2", 0xDCE1D9F7);
		addOnlineVehicleOption("Ruiner", 0xF26CEFF9);
		addOnlineVehicleOption("SabreGT", 0x9B909C94);
		addOnlineVehicleOption("SlamVan", 0x2B7F9DE3);
		addOnlineVehicleOption("Vigero", 0xCEC6B9B7);
		addOnlineVehicleOption("Voodoo", 0x1F3766E3);
		addOnlineVehicleOption("Slamvan2", 0x31ADBBFC);
		addOnlineVehicleOption("Virgo", 0xE2504942);
		break;
#pragma endregion
#pragma region SUVs
	case Vehicle_Online_SUVs:
		VehicleSpawner_Sprite();
		addTitle("SUVs");
		addOnlineVehicleOption("Baller", 0xCFCA3668);
		addOnlineVehicleOption("Baller2", 0x08852855);
		addOnlineVehicleOption("BeeJayXL", 0x32B29A4B);
		addOnlineVehicleOption("Old Cavalcade", 0x779F23AA);
		addOnlineVehicleOption("New Cavalcade", 0xD0EB2BE5);
		addOnlineVehicleOption("Dubsta", 0x462FE277);
		addOnlineVehicleOption("Dubsta2", 0xE882E5F6);
		addOnlineVehicleOption("FQ2", 0xBC32A33B);
		addOnlineVehicleOption("Granger", 0x9628879C);
		addOnlineVehicleOption("Gresley", 0xA3FC0F4D);
		addOnlineVehicleOption("Habanero", 0x34B7390F);
		addOnlineVehicleOption("HuntleyS", 0x1D06D681);
		addOnlineVehicleOption("Landstalker", 0x4BA4E8DC);
		addOnlineVehicleOption("Mesa", 0x36848602);
		addOnlineVehicleOption("Snow Mesa", 0xD36A4B44);
		addOnlineVehicleOption("Patriot", 0xCFCFEB3B);
		addOnlineVehicleOption("Radius", 0x9D96B45B);
		addOnlineVehicleOption("Rocoto", 0x7F5C91F1);
		addOnlineVehicleOption("Seminole", 0x48CECED3);
		addOnlineVehicleOption("Serrano", 0x4FB1A214);
		break;
#pragma endregion
#pragma region Motorcycles
	case Vehicle_Online_Motorcycles:
		VehicleSpawner_Sprite();
		addTitle("Motorcycles");
		addOnlineVehicleOption("Vindicator", 0xAF599F01);
		addOnlineVehicleOption("Akuma", 0x63ABADE7);
		addOnlineVehicleOption("Bagger", 0x806B9CC3);
		addOnlineVehicleOption("Bati801", 0xF9300CC5);
		addOnlineVehicleOption("Bati801RR", 0xCADD5D2D);
		addOnlineVehicleOption("Carbon RS", 0x00ABB0C0);
		addOnlineVehicleOption("Daemon", 0x77934CEE);
		addOnlineVehicleOption("DoubleT", 0x9C669788);
		addOnlineVehicleOption("Faggio", 0x0350D1AB);
		addOnlineVehicleOption("Hakuchou", 0x4B6C568A);
		addOnlineVehicleOption("Hexer", 0x11F76C14);
		addOnlineVehicleOption("Lectro", 0x26321E67);
		addOnlineVehicleOption("Enduro", 0x6882FA73);
		addOnlineVehicleOption("Innovation", 0x44C4E977);
		addOnlineVehicleOption("Nemesis", 0xDA288376);
		addOnlineVehicleOption("PCJ600", 0xC9CEAF06);
		addOnlineVehicleOption("Ruffian", 0xCABD11E8);
		addOnlineVehicleOption("Sanchez", 0x2EF89E46);
		addOnlineVehicleOption("Sanchez2", 0xA960B13E);
		addOnlineVehicleOption("Sovereign", 0x2C509634);
		addOnlineVehicleOption("Thrust", 0x6D6F8F43);
		addOnlineVehicleOption("Vader", 0xF79A00F7);
		break;
#pragma endregion
#pragma region Helicopters
	case Vehicle_Online_Helicopters:
		VehicleSpawner_Sprite();
		addTitle("Helicopters");
		addOnlineVehicleOption("Annihilator", 0x31F0B376);
		addOnlineVehicleOption("Buzzard(No Guns)", 0x2C75F0DD);
		addOnlineVehicleOption("Buzzard", 0x2F03547B);
		addOnlineVehicleOption("Cargobob", 0xFCFCB68B);
		addOnlineVehicleOption("Medic Cargobob", 0x60A7EA10);
		addOnlineVehicleOption("Trevors CargoBob", 0x53174EEF);
		addOnlineVehicleOption("Frogger", 0x2C634FBD);
		addOnlineVehicleOption("FIB/Trevors Frogger", 0x742E9AC0);
		addOnlineVehicleOption("Maverick", 0x9D0450CA);
		addOnlineVehicleOption("Police Maverick", 0x1517D4D9);
		addOnlineVehicleOption("Skylift", 0x3E48BF23);
		addOnlineVehicleOption("Swift", 0xEBC24DF2);
		addOnlineVehicleOption("Valkyrie", 0xA09E15FD);
		addOnlineVehicleOption("Swift(Gold)", 0x4019CB4C);
		addOnlineVehicleOption("Savage", 0xFB133A17);
		break;
#pragma endregion
#pragma region Planes
	case Vehicle_Online_Planes:
		VehicleSpawner_Sprite();
		addTitle("Planes");
		addOnlineVehicleOption("Blimp", 0xF7004C86);
		addOnlineVehicleOption("Besra", 0x6CBD1D6D);
		addOnlineVehicleOption("Cargo Plane", 0x15F27762);
		addOnlineVehicleOption("Cuban 800", 0xD9927FE3);
		addOnlineVehicleOption("Duster", 0x39D6779E);
		addOnlineVehicleOption("Jumbo Jet", 0x3F119114);
		addOnlineVehicleOption("Luxor", 0x250B0C5E);
		addOnlineVehicleOption("Luxor(Gold)", 0xB79F589E);
		addOnlineVehicleOption("Mallard", 0x81794C70);
		addOnlineVehicleOption("Mammatus", 0x97E55D11);
		addOnlineVehicleOption("MilJet", 0x09D80F93);
		addOnlineVehicleOption("Lazer", 0xB39B0AE6);
		addOnlineVehicleOption("Shamal", 0xB79C1BF5);
		addOnlineVehicleOption("Titan", 0x761E2AD3);
		addOnlineVehicleOption("Velum", 0x9C429B6A);
		addOnlineVehicleOption("Velum2", 0x403820E8);
		addOnlineVehicleOption("Vestra", 0x4FF77E37);
		break;
#pragma endregion
#pragma region Commercial
	case Vehicle_Online_Commercial:
		VehicleSpawner_Sprite();
		addTitle("Commercial");
		addOnlineVehicleOption("Benson", 0x7A61B330);
		addOnlineVehicleOption("Biff", 0x32B91AE8);
		addOnlineVehicleOption("Hauler", 0x5A82F9AE);
		addOnlineVehicleOption("Mule", 0x35ED670B);
		addOnlineVehicleOption("Mule2", 0x85A5B471);
		addOnlineVehicleOption("Packer", 0x21EEE87D);
		addOnlineVehicleOption("Phantom", 0x809AA4CB);
		addOnlineVehicleOption("Pounder", 0x7DE35E7D);
		addOnlineVehicleOption("Stockade", 0x6827CF72);
		addOnlineVehicleOption("Snow Stockade", 0xF337AB36);
		break;
#pragma endregion
#pragma region Bicycles
	case Vehicle_Online_Bicycles:
		VehicleSpawner_Sprite();
		addTitle("Bicycles");
		addOnlineVehicleOption("BMX", 0x43779C54);
		addOnlineVehicleOption("Scorcher", 0xF4E1AA15);
		addOnlineVehicleOption("Cruiser", 0x1ABA13B5);
		addOnlineVehicleOption("Fixter", 0xCE23D3BF);
		addOnlineVehicleOption("TriCycles", 0xE823FB48);
		addOnlineVehicleOption("Whippet", 0x4339CD69);
		addOnlineVehicleOption("Endurex", 0xB67597EC);
		break;
#pragma endregion
#pragma region Boats
	case Vehicle_Online_Boats:
		VehicleSpawner_Sprite();
		addTitle("Boats");
		addOnlineVehicleOption("Dinghy", 0x3D961290);
		addOnlineVehicleOption("Dinghy3", 0x1E5E54EA);
		addOnlineVehicleOption("Jetmax", 0x33581161);
		addOnlineVehicleOption("Marquis", 0xC1CE1183);
		addOnlineVehicleOption("Seashark", 0xC2974024);
		addOnlineVehicleOption("Lifeguard Seashark", 0xDB4388E4);
		addOnlineVehicleOption("Squalo", 0x17DF5EC2);
		addOnlineVehicleOption("Suntrap", 0xEF2295C9);
		addOnlineVehicleOption("Tropic", 0x1149422F);
		addOnlineVehicleOption("Speeder", 0x0DC60D2B);
		addOnlineVehicleOption("Police Boat", 0xE2E7D4AB);
		addOnlineVehicleOption("Submersible", 0x2DFF622F);
		addOnlineVehicleOption("Toro", 0x3FD5AA2F);
		break;
#pragma endregion
#pragma region Industrial
	case Vehicle_Online_Industrial:
		VehicleSpawner_Sprite();
		addTitle("Industrial");
		addOnlineVehicleOption("Dock Handler", 0x1A7FCEFA);
		addOnlineVehicleOption("Dozer", 0x7074F39D);
		addOnlineVehicleOption("Dump", 0x810369E2);
		addOnlineVehicleOption("Flatbed", 0x50B0215A);
		addOnlineVehicleOption("Mixer", 0xD138A6BB);
		addOnlineVehicleOption("Mixer2", 0x1C534995);
		addOnlineVehicleOption("Rubble", 0x9A5B1DCC);
		addOnlineVehicleOption("Tipper", 0x02E19879);
		addOnlineVehicleOption("Tipper2", 0xC7824E5E);
		addOnlineVehicleOption("Guardian", 0x825A9F4C);
		break;
#pragma endregion
#pragma region Utility
	case Vehicle_Online_Utility:
		VehicleSpawner_Sprite();
		addTitle("Utility");
		addOnlineVehicleOption("Airtug", 0x5D0AAC8F);
		addOnlineVehicleOption("Bison", 0xFEFD644F);
		addOnlineVehicleOption("Bison2", 0x7B8297C5);
		addOnlineVehicleOption("Bison3", 0x67B3F020);
		addOnlineVehicleOption("BobcatXL", 0x3FC5D440);
		addOnlineVehicleOption("Caddy", 0x44623884);
		addOnlineVehicleOption("Caddy2", 0xDFF0594C);
		addOnlineVehicleOption("Cutter", 0xC3FBA120);
		addOnlineVehicleOption("Docktug", 0xCB44B1CA);
		addOnlineVehicleOption("Fieldmaster", 0x843B73DE);
		addOnlineVehicleOption("Forklift", 0x58E49664);
		addOnlineVehicleOption("Lawn Mower", 0x6A4BD8F6);
		addOnlineVehicleOption("Ripley", 0xCD935EF9);
		addOnlineVehicleOption("Sadler", 0xDC434E51);
		addOnlineVehicleOption("Snow Sadler", 0x2BC345D1);
		addOnlineVehicleOption("Scrap Truck", 0x9A9FD3DF);
		addOnlineVehicleOption("Small Tow Truck", 0xE5A2D6C6);
		addOnlineVehicleOption("Big Tow Truck", 0xB12314E0);
		addOnlineVehicleOption("Tractor", 0x61D6BA8C);
		addOnlineVehicleOption("Snow Tractor", 0x562A97BD);
		addOnlineVehicleOption("Utility Truck", 0x1ED0A534);
		addOnlineVehicleOption("Utility Truck2", 0x34E6BF6B);
		addOnlineVehicleOption("Utility Truck3", 0x7F2153DF);
		break;
#pragma endregion
#pragma region Trailers
	case Vehicle_Online_Trailers:
		VehicleSpawner_Sprite();
		addTitle("Trailers");
		addOnlineVehicleOption("Car Carrier", 0x7BE032C6);
		addOnlineVehicleOption("Marquis Trailer", 0x6A59902D);
		addOnlineVehicleOption("Super Car Carrier", 0x7CAB34D0);
		addOnlineVehicleOption("Log Trailer", 0x782A236D);
		addOnlineVehicleOption("Metal Trailer", 0xCBB2BE0E);
		addOnlineVehicleOption("Random Ad Trailer", 0xA1DA3C91);
		addOnlineVehicleOption("Big Goods Trailer", 0x8548036D);
		addOnlineVehicleOption("Flatbed Trailer", 0xAF62F6B2);
		addOnlineVehicleOption("Fame Or Shame Trailer", 0x967620BE);
		addOnlineVehicleOption("Army Trailer", 0xA7FF33F5);
		addOnlineVehicleOption("Army Trailer2", 0x9E6B14D6);
		addOnlineVehicleOption("Army Trailer3", 0xB8081009);
		addOnlineVehicleOption("Boat Trailer", 0x1F3D44B5);
		addOnlineVehicleOption("Dock Trailer", 0x806EFBEE);
		addOnlineVehicleOption("Freight Trailer", 0xD1ABB666);
		addOnlineVehicleOption("Construction Trailer", 0x2A72BEAB);
		addOnlineVehicleOption("Tanker Trailer", 0xD46F4737);
		addOnlineVehicleOption("Tanker Trailer2", 0x74998082);
		break;
#pragma endregion
#pragma region Compacts
	case Vehicle_Online_Compacts:
		VehicleSpawner_Sprite();
		addTitle("Compacts");
		addOnlineVehicleOption("Blista", 0xEB70965F);
		addOnlineVehicleOption("Dilettante", 0xBC993509);
		addOnlineVehicleOption("Issi", 0xB9CB3B69);
		addOnlineVehicleOption("Panto", 0xE644E480);
		addOnlineVehicleOption("Prairie", 0xA988D3A2);
		addOnlineVehicleOption("Rhapsody", 0x322CF98F);
		break;
#pragma endregion
#pragma region Military
	case Vehicle_Online_Military:
		VehicleSpawner_Sprite();
		addTitle("Military");
		addOnlineVehicleOption("Barracks", 0xCEEA3F4B);
		addOnlineVehicleOption("Barracks Semi", 0x4008EABB);
		addOnlineVehicleOption("Barracks3", 0x2592B5CF);
		addOnlineVehicleOption("Crusader", 0x132D5A1A);
		addOnlineVehicleOption("Tank", 0x2EA68690);
		break;
#pragma endregion
#pragma region Service
	case Vehicle_Online_Service:
		VehicleSpawner_Sprite();
		addTitle("Service");
		addOnlineVehicleOption("Airport Bus", 0x4C80EB0E);
		addOnlineVehicleOption("Bus", 0xD577C962);
		addOnlineVehicleOption("Dashound", 0x84718D34);
		addOnlineVehicleOption("Shuttle", 0xBE819C63);
		addOnlineVehicleOption("Taxi", 0xC703DB5F);
		addOnlineVehicleOption("Tourbus", 0x73B1C3CB);
		addOnlineVehicleOption("Trashmaster", 0x72435A19);
		addOnlineVehicleOption("Trash2", 0x72435A19);
		break;
#pragma endregion
#pragma region SportsClassics
	case Vehicle_Online_SportsClassics:
		VehicleSpawner_Sprite();
		addTitle("Sports Classics");
		addOnlineVehicleOption("Coquette Classic", 0x3C4E2113);
		addOnlineVehicleOption("JB700", 0x3EAB5555);
		addOnlineVehicleOption("Manana", 0x81634188);
		addOnlineVehicleOption("Monroe", 0xE62B361B);
		addOnlineVehicleOption("Peyote", 0x6D19CCBC);
		addOnlineVehicleOption("Pigalle", 0x404B6381);
		addOnlineVehicleOption("Roosevelt", 0x06FF6914);
		addOnlineVehicleOption("Stinger", 0x5C23AF9B);
		addOnlineVehicleOption("StingerGT", 0x82E499FA);
		addOnlineVehicleOption("Tornado", 0x1BB290BC);
		addOnlineVehicleOption("Tornado2", 0x5B42A5C4);
		addOnlineVehicleOption("Tornado3", 0x690A4153);
		addOnlineVehicleOption("Tornado4", 0x86CF7CDD);
		addOnlineVehicleOption("ZType", 0x2D3BD401);
		addOnlineVehicleOption("Stirling GT", 0xA29D6D10);
		addOnlineVehicleOption("Casco", 0x3822BDFE);
		break;
#pragma endregion
#pragma region Vans
	case Vehicle_Online_Vans:
		VehicleSpawner_Sprite();
		addTitle("Vans");
		addOnlineVehicleOption("Boxville", 0x898ECCEA);
		addOnlineVehicleOption("Boxville2", 0xF21B33BE);
		addOnlineVehicleOption("Boxville3", 0x07405E08);
		addOnlineVehicleOption("Boxville4", 0x1A79847A);
		addOnlineVehicleOption("Burrito", 0xAFBB2CA4);
		addOnlineVehicleOption("Burrito2", 0xC9E8FF76);
		addOnlineVehicleOption("Burrito3", 0x98171BD3);
		addOnlineVehicleOption("Burrito4", 0x353B561D);
		addOnlineVehicleOption("Snow Burrito", 0x437CF2A0);
		addOnlineVehicleOption("Gang Burrito", 0x97FA4F36);
		addOnlineVehicleOption("Gang Burrito2", 0x11AA0E14);
		addOnlineVehicleOption("Camper", 0x6FD95F68);
		addOnlineVehicleOption("Journey", 0xF8D48E7A);
		addOnlineVehicleOption("Minivan", 0xED7EADA4);
		addOnlineVehicleOption("Paradise", 0x58B3979C);
		addOnlineVehicleOption("Pony", 0xF8DE29A8);
		addOnlineVehicleOption("Weed Van", 0x38408341);
		addOnlineVehicleOption("Weazel News", 0x4543B74D);
		addOnlineVehicleOption("Deludamol", 0x961AFEF7);
		addOnlineVehicleOption("Speedo", 0xCFB3870C);
		addOnlineVehicleOption("Clown Van", 0x2B6DC64A);
		addOnlineVehicleOption("Surfer", 0x29B0DA97);
		addOnlineVehicleOption("Surfer2", 0xB1D80E06);
		addOnlineVehicleOption("Taco Van", 0x744CA80D);
		addOnlineVehicleOption("Youga", 0x03E5F6B8);
		break;
#pragma endregion
#pragma region Teleport Options
	case Teleport_Options_Online:

		addTitle("Teleport Options");
		addOption("Teleport To Player"); //case 1
		addOption("Teleport Player To Me"); //case 2
		addOption("Teleport Into Players Vehicle"); //case 3
		addOption("Teleport Player Into Ocean"); //case 4
		switch (getOption())
		{
		case 1: {
			Ped ped = PLAYER::PLAYER_PED_ID();
			Vector3 coords1101;
			coords1101 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
			Entity entityToTele = ped;
			if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
				entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
			ENTITY::SET_ENTITY_COORDS(entityToTele, coords1101.x, coords1101.y, coords1101.z, false, false, false, true);
			Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");

			//GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1.0, 0, 0, 0);
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(128, 0, 128);
			STREAMING::LOAD_ALL_OBJECTS_NOW();
		}
				break;
		case 2: {
			Ped ped = PLAYER::PLAYER_PED_ID();
			Ped Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vehicle TheirVehicle = PED::GET_VEHICLE_PED_IS_USING(Player);
			Vector3 coords1102;
			if (RequestNetworkControl(Player, TheirVehicle)) {
				coords1102 = ENTITY::GET_ENTITY_COORDS(ped, 1);
				if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(Player))
					TheirVehicle = PED::GET_VEHICLE_PED_IS_USING(Player);
				ENTITY::SET_ENTITY_COORDS(TheirVehicle, coords1102.x, coords1102.y, coords1102.z + 12.0f, false, false, false, true);
				Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1.0, 0, 0, 0);
				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);
				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(128, 0, 128);

			}}
				break;
		case 3: {
			Ped ped = PLAYER::PLAYER_PED_ID();
			Ped Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vehicle TheirVehicle = PED::GET_VEHICLE_PED_IS_USING(Player);
			Vector3 coords1103;
			coords1103 = ENTITY::GET_ENTITY_COORDS(TheirVehicle, 1);
			ENTITY::SET_ENTITY_COORDS(ped, coords1103.x, coords1103.y, coords1103.z + 1.0, false, false, false, true);
			Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1.0, 0, 0, 0);
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_clown_appears", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(128, 0, 128);
			if (ENTITY::DOES_ENTITY_EXIST(TheirVehicle) && ENTITY::IS_ENTITY_A_VEHICLE(TheirVehicle)) {
				printf("Vehicle exists\n");
				int var4 = -1;
				int pasnmax;
				pasnmax = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(TheirVehicle);
				printf("Got max seats\n");
				while (var4 < pasnmax) {
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(TheirVehicle, var4)) {
						printf("Found seat\n");
						PED::SET_PED_INTO_VEHICLE(ped, TheirVehicle, var4);
						NotifyAboveMap("~b~ Teleported to free seat!");
						break;
					}
					else
					{
						var4++;
					}
				}
				if (var4 > pasnmax) {
					NotifyAboveMap("~b~ Failed, Player may not be in any vehicle or vehicle has no available seat");
				}
			}
		}
				break;
		case 4:
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), 0));
				int PedVehicle;
				PedVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), 0);
				Vector3 coords = { 103.4720, 7744.1870, -158.1106 };
				ENTITY::SET_ENTITY_COORDS(PedVehicle, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
		} break;
		}
		break;
#pragma endregion
#pragma region Money Settings
	case Money_Settings:

		addTitle("Money Settings");
		addIntOption("Set Money", &MoneySet, 0, 40000, true); //1
		addOption("Set Cash To Dildos"); //2
		addOption("Set Cash To XMas Trees"); //3
		addOption("Set Cash To Weed Plants"); //4
		addOption("Set Cash To Alien Eggs"); //5
		addOption("Set Cash To JukeBox"); //6
		addOption("Set Cash To Hesit Bags"); //7
		addOption("Set Cash To Hesit Bags 2"); //8
		addOption("Set Cash To 40K Bags"); //9
		addOption("Set Cash To Cash Creates"); //10
		addOption("Set Cash To Cable Cars"); //11
		addOption("Set Cash To Roller Coasters"); //12
		addOption("Set Cash To Lawn Mower"); //13
		switch (getOption())
		{
		case 1: break;
		case 2: CashDropItem = 0xE6CB661E; break;
		case 3: CashDropItem = 0x0E3BA450; break;
		case 4: CashDropItem = 0x1AFA6A0A; break;
		case 5: CashDropItem = 0x6B795EBC; break;
		case 6: CashDropItem = 0x73F55396; break;
		case 7: CashDropItem = 0xD593F420; break;
		case 8: CashDropItem = 0x60F90AD4; break;
		case 9: CashDropItem = 0x113FD533; break;
		case 10: CashDropItem = 0xE44D5CEC; break;
		case 11: CashDropItem = GAMEPLAY::GET_HASH_KEY("p_cablecar_s"); break;
		case 12: CashDropItem = 1543894721; break;
		case 13: CashDropItem = 447976993; break;
		}
		break;
#pragma endregion

#pragma region Misc Options
	case Misc_Options:

		addTitle("Misc Options");
		addSubmenuOption("Network Options", Network_Options);
		addSubmenuOption("Weather Options", Weather_Options);
		addSubmenuOption("Particle Effects", ParticleFX_Options); //6
		addSubmenuOption("Mini Games Menu", Main_MiniGames); //3
		addOption("join public Sessions"); //8
		addBoolOption("Water Powers", partWater); //9
		addBoolOption("First Person Mod", NULL); //13
		addBoolOption("GTA 2 Cam", loop_gta2cam); //13
		addBoolOption("Display Mini Map", DisplayMiniMap);
		addBoolOption("Display HUD", DISPLAYHUD);
		addBoolOption("Black Out", Black_Out);
		addBoolOption("Enable Restricted Zones", radarmod);
		addBoolOption("Masacre Mode", set_massacre_mode);
		switch (getOption())
		{
		case 5: 	allowonline(); break;
		case 6: partWater = !partWater; break;
		case 7: loop_gta2cam = !loop_gta2cam; break;
		case 9:
		{
			if (DisplayMiniMap)
				UI::DISPLAY_RADAR(false);
			else
				UI::DISPLAY_RADAR(true);
			DisplayMiniMap = !DisplayMiniMap;
		} break;
		case 10:
		{
			if (DISPLAYHUD)
				UI::DISPLAY_HUD(false);
			else
				UI::DISPLAY_HUD(true);
			DISPLAYHUD = !DISPLAYHUD;
		} break;
		case 11:
		{
			if (Black_Out)
				GRAPHICS::_SET_BLACKOUT(false);
			else
				GRAPHICS::_SET_BLACKOUT(true);
			Black_Out = !Black_Out;
		} break;
		case 12:
		{
			if (radarmod)
				EnableRestrictedZones(false);
			else
				EnableRestrictedZones(true);
			radarmod = !radarmod;
		} break;
		case 13: set_massacre_mode = !set_massacre_mode; break;
		}
		break;
#pragma endregion
#pragma region Create Escort Options
	case Create_Escort_Options:

		addTitle("Create Escort Options");
		createEscortOption("Adder Escort", 0x3AE4A33B, 0xB779A091); //1
		createEscortOption("Moto Escort", 0x3AE4A33B, 0xA960B13E); //1
		createEscortOption("Insurgent Escort", 0x3AE4A33B, 0x9114EADA); //1
		createEscortOption("Lazer Escort", 0x3AE4A33B, 0xB39B0AE6); //1
		createEscortOption("Cargobob Escort", 0x3AE4A33B, 0xFCFCB68B); //1
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region TV Options
	case TV_Options:

		addTitle("TV Options");
		addBoolOption("Draw TV", DrawTV, "Credits To i420 NZ"); //1
		addOption("Get TV Channel", "Credits To i420 NZ"); //2
		addIntOption("Set TV Channel", &SetTVChannel, 0, 10, true, "Credits To i420 NZ");
		addOption("Get TV Volume", "Credits To i420 NZ"); //2
		addIntOption("Set TV Volume", &SetTVVolume, 0, 100, true, "Credits To i420 NZ");
		switch (getOption())
		{
		case 1: DrawTV = !DrawTV; break;
		case 2: GRAPHICS::GET_TV_CHANNEL(); break;
		case 3: GRAPHICS::SET_TV_CHANNEL(SetTVChannel); break;
		case 4: GRAPHICS::GET_TV_VOLUME(); break;
		case 5: GRAPHICS::SET_TV_VOLUME(SetTVVolume); break;
		}
		break;
#pragma endregion
#pragma region Test Options
	case Test_Options:

		addTitle("Test Options");
		addBoolOption("Mod Shop 1", ModShop);
		addBoolOption("Mod Shop 1", ModShop2);
		switch (getOption())
		{
		case 1: ModShop = !ModShop; break;
		case 2: ModShop2 = !ModShop2; break;
		}
		break;
#pragma endregion
#pragma region Particle FX Options
	case ParticleFX_Options:

		addTitle("Particle Effects");
		addSubmenuOption("Ghost Rider Menu", Ghost_Rider_Menu);
		addSubmenuOption("Fire Storm Menu", Fire_Storm_Menu);
		addParticleEffectOption("Boosh", "scr_trevor1", "scr_trev1_trailer_boosh"); //2
		addParticleEffectOption("Splash", "scr_trevor1", "scr_trev1_trailer_splash"); //3
		addParticleEffectOption("Spiked", "scr_trevor1", "scr_bigscore_tyre_spiked"); //4
		addParticleEffectOption("Pink Smoke", "scr_familyscenem", "scr_meth_pipe_smoke"); //5
		addParticleEffectOption("Clown Appears", "scr_rcbarry2", "scr_clown_appears"); //6
		addParticleEffectOption("Clown Death", "scr_rcbarry2", "scr_clown_death"); //7
		addParticleEffectOption("Blood Impact", "scr_solomon3", "scr_trev4_747_blood_impact"); //8
		addParticleEffectOption("Engine Debris", "scr_solomon3", "scr_trev4_747_engine_debris"); //9
		addParticleEffectOption("Firework Fountain", "scr_indep_fireworks", "scr_indep_firework_fountain"); //10
		addParticleEffectOption("Firework Shotburst", "scr_indep_fireworks", "scr_indep_firework_shotburst"); //11
		addParticleEffectOption("Firework Starburst", "scr_indep_fireworks", "scr_indep_firework_starburst"); //12
		addParticleEffectOption("Firework Trailburst", "scr_indep_fireworks", "scr_indep_firework_trailburst"); //13
		addParticleEffectOption("Alien Disintegrate", "scr_rcbarry1", "scr_alien_disintegrate"); //14
		addParticleEffectOption("Alien Teleport", "scr_rcbarry1", "scr_alien_teleport"); //15
		addParticleEffectOption("Trailer Sparks", "scr_family4", "scr_fam4_trailer_sparks"); //16
		addParticleEffectOption("Car Impact", "scr_exile2", "scr_ex2_car_impact"); //17
		addParticleEffectOption("Water Dinghy Wash", "scr_exile3", "scr_ex3_water_dinghy_wash"); //18
		addParticleEffectOption("Bank Notes", "scr_paletoscore", "scr_paleto_banknotes"); //19
		addParticleEffectOption("Blow Torch", "scr_paletoscore", "cs_paleto_blowtorch"); //20
		addParticleEffectOption("Bike Burnout", "scr_jewelheist", "scr_jew_biKe_burnout"); //21
		addParticleEffectOption("Cab Smash", "scr_jewelheist", "scr_jewel_cab_smash"); //22
		addParticleEffectOption("Tyre Spiked", "scr_carsteal4", "scr_carsteal5_tyre_spiked"); //23
		addParticleEffectOption("Muzzle Flash", "scr_carsteal4", "scr_carsteal5_car_muzzle_flash"); //24
		addParticleEffectOption("Wheel Burnout", "scr_carsteal4", "scr_carsteal4_wheel_burnout"); //25
		addParticleEffectOption("Tyre Spiked", "scr_carsteal3", "scr_carsteal4_tyre_spiked"); //26
		addParticleEffectOption("Hotbox Trail", "scr_oddjobtaxi", "scr_ojtaxi_hotbox_trail"); //27
		addParticleEffectOption("Train Sparks", "scr_oddjobtowtruck", "scr_ojtt_train_sparks"); //28
		addParticleEffectOption("Cig Smoke Car", "scr_mp_cig", "ent_anim_cig_smoke_car"); //29
		addParticleEffectOption("Truck Crash", "scr_fbi4", "scr_fbi4_trucks_crash"); //30
		break;
#pragma endregion
#pragma region Ghost Rider Menu
	case Ghost_Rider_Menu:

		addTitle("Ghost Rider Menu");
		addSubmenuOption("Ghost Rider Head", GhostRiderHead); //1
		addBoolOption("Ghost Rider Arm", Ghost_Rider2); //3
		addBoolOption("Ghost Rider Arm 2", Ghost_Rider3); //4
		switch (getOption())
		{
		case 2:
			Ghost_Rider2 = !Ghost_Rider2; break;
		case 3:
			Ghost_Rider3 = !Ghost_Rider3; break;
		}
		break;
#pragma endregion
#pragma region Fire Storm Menu
	case Fire_Storm_Menu:

		addTitle("Fire Storm Menu");
		addBoolOption("Fire Storm Head", FireStormHead); //3
		addBoolOption("Fire Storm Arm", FireStormArm); //3
		addBoolOption("Fire Storm Arm 2", FireStormArm2); //4
		switch (getOption())
		{
		case 1:
			FireStormHead = !FireStormHead; break;
		case 2:
			FireStormArm = !FireStormArm; break;
		case 3:
			FireStormArm2 = !FireStormArm2; break;
		}
		break;
#pragma endregion
#pragma region Ghost Rider Head
	case GhostRiderHead:

		addTitle("Ghost Rider Head");
		addBoolOption("Ghost Rider Head", Ghost_Rider); //1
		addBoolOption("Ghost Rider Head 2", Ghost_Rider_Head2); //1
		switch (getOption())
		{
		case 1:
			Ghost_Rider = !Ghost_Rider; break;
		case 2:
			Ghost_Rider_Head2 = !Ghost_Rider_Head2; break;
		}
		break;
#pragma endregion
#pragma region Network Options
	case Network_Options:
		addTitle("Network Options");

		addSubmenuOption("Money Settings", Money_Settings); //1
		addSubmenuOption("Map Options", Map_Options); //2
		addSubmenuOption("Name Changer Menu", Name_Changer);
		addBoolOption("Show Whos Talking", Show_Info); //3
		addBoolOption("Show Whos Host", Show_Host); //4
		addBoolOption("Show Free Slots", AtlasOpenText); //6
		addBoolOption("Show FPS Counter", Show_FPS_Counter); //7
		switch (getOption())
		{
		case 4: Show_Info = !Show_Info; break;
		case 5: Show_Host = !Show_Host; break;
		case 6: AtlasOpenText = !AtlasOpenText; break;
		case 7: Show_FPS_Counter = !Show_FPS_Counter; break;
		}
		break;
#pragma endregion
#pragma region Gamertag Changer Options
	case Name_Changer:
		addTitle("Gamertag Changer");
		addOption("~y~AnTraX X MoDz");
		addOption("~f~AMEngine");
		addOption("~r~Rockstar Support");
		addOption("~g~You are fucked");
		addOption("~r~Anonimous");
		addOption("~o~Microsoft");
		addOption("~h~~p~Developer");
		addOption("~y~P~g~R~f~O~o~Y~w~E~p~C~f~T~g~360");
		addOption("~r~Fuck ~y~You");
		addOption("~h~You~r~Tube");
		addKeyboardOption("Custom Gamertag", 2, "Enter Your Gamertag", 15);
		switch (getOption())
		{
		case 1: GTChanger = "~y~AnTraX X MoDz"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : AnTraX X MoDz"); break;
		case 2: GTChanger = "~f~AMEngine"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : AMEngine"); break;
		case 3: GTChanger = "~r~Rockstar Support"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : Rockstar Support"); break;
		case 4: GTChanger = "~g~You are fucked"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : You are fucked"); break;
		case 5: GTChanger = "~r~Anonimous"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : Anonimous"); break;
		case 6: GTChanger = "~o~Microsoft"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : Microsoft"); break;
		case 7: GTChanger = "~h~~p~Developer"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : Developer"); break;
		case 8: GTChanger = "~y~P~g~R~f~O~o~Y~w~E~p~C~f~T~g~360"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : PROYECT360"); break;
		case 9: GTChanger = "~r~Fuck ~y~You"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : Fuck You"); break;
		case 10: GTChanger = "~h~You~r~Tube"; strcpy((char*)(0xDFBCC1AC), GTChanger); NotifyAboveMap("Gamertag Changed : YouTube"); break;
		}
		break;
#pragma endregion 
#pragma region Zenyle Mod Loader
	case Modloader2:
		addTitle("[~r~Requires TU Of Menu~s~]");

		addBoolOption("API Rock ~y~[RB + X]", apiirockvtrainer1); //1
		addBoolOption("API Spanish ~y~[RB + X]", APISpanish1); //2
		addBoolOption("Console Trainer ~y~[RB + Left]", ConsoleTrainer); //3
		addBoolOption("K & K Dark Horse ~y~[RB + LB]", Dark_Horse); //4
		addBoolOption("K & K Dark Horse 1.0 ~y~[RB + LB]", DarkHorse10); //5
		addBoolOption("Garage Editor ~y~[A + Right]", GarageEditor1); //6
		addBoolOption("Anti Cheater ~y~[LB + A]", AntiCheater); //7
		addBoolOption("Map Loader ~y~[LB + B]", MapLoader); //8
		addBoolOption("Custom Camera ~y~[LS + X]", Custom_Camera); //9
		addBoolOption("RayRod Menu V4 ~y~[LB + Right]", rayrod4); //10
		addBoolOption("Mafins Menyoo ~y~[RB + Down]", mafinsbeta01); //11
		addBoolOption("Mini Menyoo ~y~[RB + UP]", MiniMenyo); //12
		addBoolOption("Slinkys Animation ~y~[RB + Right]", slinky_animati); //13
		addBoolOption("Slinkys Menu ~y~[RB + A]", Slinkys1); //14
		addBoolOption("Slinkys Recovery ~y~[RB + Right]", Slinkys_R); //15
		addBoolOption("TDB Recovery ~y~[RB + A]", TheDnBroR); //16
		addBoolOption("TDB Menu ~y~[RB + X]", TheDonBro); //17
		addBoolOption("VCAHax Hairys ~y~[LT + RT]", VCAHairy); //18
		addBoolOption("VCAHax Venox V2 ~y~[LB + Down]", Venox_v2); //19
		addBoolOption("VCAHax Zero ~y~[LB + B]", VCAHaxZero); //20
		addBoolOption("VCAHax Norway ~y~[LB + Right]", VCANorway); //21
		addBoolOption("Rocket Car ~y~[LB + Left]", rocketcar); //22
		addBoolOption("Car Jump ~y~[A]", CarJump); //23
		addBoolOption("Bind Menu", bindmenu); //24
		addBoolOption("Hao Menu", hao1); //25
		addBoolOption("Freeze Protection", NULL); //26
		addBoolOption("XBL ToothPik", XBLTooth); //27
		addBoolOption("XYZH Coordinates", xyzhcoord); //28
		switch (getOption())
		{
		case 1:
		{
			apiirockvtrainer1 = !apiirockvtrainer1;
			if (apiirockvtrainer1)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("apiirockvtrainer1"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("apiirockvtrainer1");
					SCRIPT::REQUEST_SCRIPT("apiirockvtrainer1");
					if (SCRIPT::HAS_SCRIPT_LOADED("apiirockvtrainer1"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("apiirockvtrainer1", StackSize);
						NotifyAboveMap("~b~ Started script: apiirockvtrainer1");
					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("apiirockvtrainer1");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/apiirockvtrainer1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("apiirockvtrainer1"))
				{
					NotifyAboveMap("~b~ Terminated script: apiirockvtrainer1");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("apiirockvtrainer1");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("apiirockvtrainer1");
				}
			}
		}
		break;
		case 2:
		{
			APISpanish1 = !APISpanish1;
			if (APISpanish1)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("APISpanish1"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("APISpanish1");
					SCRIPT::REQUEST_SCRIPT("APISpanish1");
					if (SCRIPT::HAS_SCRIPT_LOADED("APISpanish1"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("APISpanish1", StackSize);
						NotifyAboveMap("~b~ Started script: APISpanish1");
					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("APISpanish1");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/APISpanish1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("APISpanish1"))
				{
					NotifyAboveMap("~b~ Terminated script: APISpanish1");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("APISpanish1");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("APISpanish1");
				}
			}
		}
		break;
		case 3:
		{
			ConsoleTrainer = !ConsoleTrainer;
			if (ConsoleTrainer)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("ConsoleTrainer"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("ConsoleTrainer");
					SCRIPT::REQUEST_SCRIPT("ConsoleTrainer");
					if (SCRIPT::HAS_SCRIPT_LOADED("ConsoleTrainer"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("ConsoleTrainer", StackSize);
						NotifyAboveMap("~b~ Started script: ConsoleTrainer");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("ConsoleTrainer");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/ConsoleTrainer Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("ConsoleTrainer"))
				{
					NotifyAboveMap("~b~ Terminated script: ConsoleTrainer");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("ConsoleTrainer");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("ConsoleTrainer");
				}
			}
		}
		break;
		case 4:
		{
			Dark_Horse = !Dark_Horse;
			if (Dark_Horse)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("Dark_Horse"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Dark_Horse");
					SCRIPT::REQUEST_SCRIPT("Dark_Horse");
					if (SCRIPT::HAS_SCRIPT_LOADED("Dark_Horse"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("Dark_Horse", StackSize);
						NotifyAboveMap("~b~ Started script: Dark_Horse");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Dark_Horse");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/Dark_Horse Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("Dark_Horse"))
				{
					NotifyAboveMap("~b~ Terminated script: Dark_Horse");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("Dark_Horse");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Dark_Horse");
				}
			}
		}
		break;
		case 5:
		{
			DarkHorse10 = !DarkHorse10;
			if (DarkHorse10)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("DarkHorse10"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("DarkHorse10");
					SCRIPT::REQUEST_SCRIPT("DarkHorse10");
					if (SCRIPT::HAS_SCRIPT_LOADED("DarkHorse10"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("DarkHorse10", StackSize);
						NotifyAboveMap("~b~ Started script: DarkHorse10");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("DarkHorse10");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/DarkHorse10 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("DarkHorse10"))
				{
					NotifyAboveMap("~b~ Terminated script: DarkHorse10");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("DarkHorse10");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("DarkHorse10");
				}
			}
		}
		break;
		case 6:
		{
			GarageEditor1 = !GarageEditor1;
			if (GarageEditor1)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("GarageEditor1"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("GarageEditor1");
					SCRIPT::REQUEST_SCRIPT("GarageEditor1");
					if (SCRIPT::HAS_SCRIPT_LOADED("GarageEditor1"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("GarageEditor1", StackSize);
						NotifyAboveMap("~b~ Started script: GarageEditor1");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("GarageEditor1");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/GarageEditor1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("GarageEditor1"))
				{
					NotifyAboveMap("~b~ Terminated script: GarageEditor1");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("GarageEditor1");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("GarageEditor1");
				}
			}
		}
		break;
		case 7:
		{
			AntiCheater = !AntiCheater;
			if (AntiCheater)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("AntiCheater"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("AntiCheater");
					SCRIPT::REQUEST_SCRIPT("AntiCheater");
					if (SCRIPT::HAS_SCRIPT_LOADED("AntiCheater"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("AntiCheater", StackSize);
						NotifyAboveMap("~b~ Started script: AntiCheater");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("AntiCheater");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/AntiCheater Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("AntiCheater"))
				{
					NotifyAboveMap("~b~ Terminated script: AntiCheater");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("AntiCheater");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("AntiCheater");
				}
			}
		}
		break;
		case 8:
		{
			MapLoader = !MapLoader;
			if (MapLoader)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("MapLoader"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MapLoader");
					SCRIPT::REQUEST_SCRIPT("MapLoader");
					if (SCRIPT::HAS_SCRIPT_LOADED("MapLoader"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("MapLoader", StackSize);
						NotifyAboveMap("~b~ Started script: MapLoader");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MapLoader");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/MapLoader Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("MapLoader"))
				{
					NotifyAboveMap("~b~ Terminated script: MapLoader");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("MapLoader");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MapLoader");
				}
			}
		}
		break;
		case 9:
		{
			Custom_Camera = !Custom_Camera;
			if (Custom_Camera)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("Custom_Camera"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Custom_Camera");
					SCRIPT::REQUEST_SCRIPT("Custom_Camera");
					if (SCRIPT::HAS_SCRIPT_LOADED("Custom_Camera"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("Custom_Camera", StackSize);
						NotifyAboveMap("~b~ Started script: Custom_Camera");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Custom_Camera");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/Custom_Camera Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("Custom_Camera"))
				{
					NotifyAboveMap("~b~ Terminated script: Custom_Camera");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("Custom_Camera");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Custom_Camera");
				}
			}
		}
		break;
		case 10:
		{
			rayrod4 = !rayrod4;
			if (rayrod4)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("rayrod4"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rayrod4");
					SCRIPT::REQUEST_SCRIPT("rayrod4");
					if (SCRIPT::HAS_SCRIPT_LOADED("rayrod4"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("rayrod4", StackSize);
						NotifyAboveMap("~b~ Started script: rayrod4");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rayrod4");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/rayrod4 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("rayrod4"))
				{
					NotifyAboveMap("~b~ Terminated script: rayrod4");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("rayrod4");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rayrod4");
				}
			}
		}
		break;
		case 11:
		{
			mafinsbeta01 = !mafinsbeta01;
			if (mafinsbeta01)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("mafinsbeta01"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mafinsbeta01");
					SCRIPT::REQUEST_SCRIPT("mafinsbeta01");
					if (SCRIPT::HAS_SCRIPT_LOADED("mafinsbeta01"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("mafinsbeta01", StackSize);
						NotifyAboveMap("~b~ Started script: mafinsbeta01");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mafinsbeta01");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/mafinsbeta01 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("mafinsbeta01"))
				{
					NotifyAboveMap("~b~ Terminated script: mafinsbeta01");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("mafinsbeta01");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mafinsbeta01");
				}
			}
		}
		break;
		case 12:
		{
			MiniMenyo = !MiniMenyo;
			if (MiniMenyo)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("MiniMenyo"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MiniMenyo");
					SCRIPT::REQUEST_SCRIPT("MiniMenyo");
					if (SCRIPT::HAS_SCRIPT_LOADED("MiniMenyo"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("MiniMenyo", StackSize);
						NotifyAboveMap("~b~ Started script: MiniMenyo");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MiniMenyo");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/MiniMenyo Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("MiniMenyo"))
				{
					NotifyAboveMap("~b~ Terminated script: MiniMenyo");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("MiniMenyo");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MiniMenyo");
				}
			}
		}
		break;
		case 13:
		{
			slinky_animati = !slinky_animati;
			if (slinky_animati)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("slinky_animati"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("slinky_animati");
					SCRIPT::REQUEST_SCRIPT("slinky_animati");
					if (SCRIPT::HAS_SCRIPT_LOADED("slinky_animati"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("slinky_animati", StackSize);
						NotifyAboveMap("~b~ Started script: slinky_animati");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("slinky_animati");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/slinky_animati Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("slinky_animati"))
				{
					NotifyAboveMap("~b~ Terminated script: slinky_animati");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("slinky_animati");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("slinky_animati");
				}
			}
		}
		break;
		case 14:
		{
			Slinkys1 = !Slinkys1;
			if (Slinkys1)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("Slinkys1"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys1");
					SCRIPT::REQUEST_SCRIPT("Slinkys1");
					if (SCRIPT::HAS_SCRIPT_LOADED("Slinkys1"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("Slinkys1", StackSize);
						NotifyAboveMap("~b~ Started script: Slinkys1");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys1");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/Slinkys1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("Slinkys1"))
				{
					NotifyAboveMap("~b~ Terminated script: Slinkys1");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("Slinkys1");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys1");
				}
			}
		}
		break;
		case 15:
		{
			Slinkys_R = !Slinkys_R;
			if (Slinkys_R)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("Slinkys_R"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys_R");
					SCRIPT::REQUEST_SCRIPT("Slinkys_R");
					if (SCRIPT::HAS_SCRIPT_LOADED("Slinkys_R"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("Slinkys_R", StackSize);
						NotifyAboveMap("~b~ Started script: Slinkys_R");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys_R");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/Slinkys_R Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("Slinkys_R"))
				{
					NotifyAboveMap("~b~ Terminated script: Slinkys_R");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("Slinkys_R");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Slinkys_R");
				}
			}
		}
		break;
		case 16:
		{
			TheDnBroR = !TheDnBroR;
			if (TheDnBroR)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("TheDnBroR"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDnBroR");
					SCRIPT::REQUEST_SCRIPT("TheDnBroR");
					if (SCRIPT::HAS_SCRIPT_LOADED("TheDnBroR"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("TheDnBroR", StackSize);
						NotifyAboveMap("~b~ Started script: TheDnBroR");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDnBroR");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/TheDnBroR Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("TheDnBroR"))
				{
					NotifyAboveMap("~b~ Terminated script: TheDnBroR");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("TheDnBroR");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDnBroR");
				}
			}
		}
		break;
		case 17:
		{
			TheDonBro = !TheDonBro;
			if (TheDonBro)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("TheDonBro"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDonBro");
					SCRIPT::REQUEST_SCRIPT("TheDonBro");
					if (SCRIPT::HAS_SCRIPT_LOADED("TheDonBro"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("TheDonBro", StackSize);
						NotifyAboveMap("~b~ Started script: TheDonBro");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDonBro");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/TheDonBro Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("TheDonBro"))
				{
					NotifyAboveMap("~b~ Terminated script: TheDonBro");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("TheDonBro");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("TheDonBro");
				}
			}
		}
		break;
		case 18:
		{
			VCAHairy = !VCAHairy;
			if (VCAHairy)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("VCAHairy"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHairy");
					SCRIPT::REQUEST_SCRIPT("VCAHairy");
					if (SCRIPT::HAS_SCRIPT_LOADED("VCAHairy"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("VCAHairy", StackSize);
						NotifyAboveMap("~b~ Started script: VCAHairy");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHairy");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/VCAHairy Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("VCAHairy"))
				{
					NotifyAboveMap("~b~ Terminated script: VCAHairy");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("VCAHairy");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHairy");
				}
			}
		}
		break;
		case 19:
		{
			Venox_v2 = !Venox_v2;
			if (Venox_v2)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("Venox_v2"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Venox_v2");
					SCRIPT::REQUEST_SCRIPT("Venox_v2");
					if (SCRIPT::HAS_SCRIPT_LOADED("Venox_v2"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("Venox_v2", StackSize);
						NotifyAboveMap("~b~ Started script: Venox_v2");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Venox_v2");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/Venox_v2 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("Venox_v2"))
				{
					NotifyAboveMap("~b~ Terminated script: Venox_v2");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("Venox_v2");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("Venox_v2");
				}
			}
		}
		break;
		case 20:
		{
			VCAHaxZero = !VCAHaxZero;
			if (VCAHaxZero)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("VCAHaxZero"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHaxZero");
					SCRIPT::REQUEST_SCRIPT("VCAHaxZero");
					if (SCRIPT::HAS_SCRIPT_LOADED("VCAHaxZero"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("VCAHaxZero", StackSize);
						NotifyAboveMap("~b~ Started script: VCAHaxZero");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHaxZero");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/VCAHaxZero Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("VCAHaxZero"))
				{
					NotifyAboveMap("~b~ Terminated script: VCAHaxZero");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("VCAHaxZero");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCAHaxZero");
				}
			}
		}
		break;
		case 21:
		{
			VCANorway = !VCANorway;
			if (VCANorway)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("VCANorway"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCANorway");
					SCRIPT::REQUEST_SCRIPT("VCANorway");
					if (SCRIPT::HAS_SCRIPT_LOADED("VCANorway"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("VCANorway", StackSize);
						NotifyAboveMap("~b~ Started script: VCANorway");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCANorway");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/VCANorway Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("VCANorway"))
				{
					NotifyAboveMap("~b~ Terminated script: VCANorway");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("VCANorway");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("VCANorway");
				}
			}
		}
		break;
		case 22:
		{
			rocketcar = !rocketcar;
			if (rocketcar)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("rocketcar"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rocketcar");
					SCRIPT::REQUEST_SCRIPT("rocketcar");
					if (SCRIPT::HAS_SCRIPT_LOADED("rocketcar"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("rocketcar", StackSize);
						NotifyAboveMap("~b~ Started script: rocketcar");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rocketcar");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/rocketcar Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("rocketcar"))
				{
					NotifyAboveMap("~b~ Terminated script: rocketcar");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("rocketcar");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("rocketcar");
				}
			}
		}
		break;
		case 23:
		{
			CarJump = !CarJump;
			if (CarJump)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("CarJump"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("CarJump");
					SCRIPT::REQUEST_SCRIPT("CarJump");
					if (SCRIPT::HAS_SCRIPT_LOADED("CarJump"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("CarJump", StackSize);
						NotifyAboveMap("~b~ Started script: CarJump");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("CarJump");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/CarJump Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("CarJump"))
				{
					NotifyAboveMap("~b~ Terminated script: CarJump");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("CarJump");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("CarJump");
				}
			}
		}
		break;
		case 24:
		{
			bindmenu = !bindmenu;
			if (bindmenu)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("bindmenu"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("bindmenu");
					SCRIPT::REQUEST_SCRIPT("bindmenu");
					if (SCRIPT::HAS_SCRIPT_LOADED("bindmenu"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("bindmenu", StackSize);
						NotifyAboveMap("~b~ Started script: bindmenu");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("bindmenu");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/bindmenu Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("bindmenu"))
				{
					NotifyAboveMap("~b~ Terminated script: bindmenu");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("bindmenu");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("bindmenu");
				}
			}
		}
		break;
		case 25:
		{
			hao1 = !hao1;
			if (hao1)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("hao1"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("hao1");
					SCRIPT::REQUEST_SCRIPT("hao1");
					if (SCRIPT::HAS_SCRIPT_LOADED("hao1"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("hao1", StackSize);
						NotifyAboveMap("~b~ Started script: hao1");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("hao1");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/hao1 Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("hao1"))
				{
					NotifyAboveMap("~b~ Terminated script: hao1");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("hao1");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("hao1");
				}
			}
		}
		break;
		case 26: break;
		case 27:
		{
			XBLTooth = !XBLTooth;
			if (XBLTooth)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("XBLTooth"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("XBLTooth");
					SCRIPT::REQUEST_SCRIPT("XBLTooth");
					if (SCRIPT::HAS_SCRIPT_LOADED("XBLTooth"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("XBLTooth", StackSize);
						NotifyAboveMap("~b~ Started script: XBLTooth");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("XBLTooth");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/XBLTooth Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("XBLTooth"))
				{
					NotifyAboveMap("~b~ Terminated script: XBLTooth");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("XBLTooth");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("XBLTooth");
				}
			}
		}
		break;
		case 28:
		{
			xyzhcoord = !xyzhcoord;
			if (xyzhcoord)
			{
				if (SCRIPT::DOES_SCRIPT_EXIST("xyzhcoord"))
				{
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xyzhcoord");
					SCRIPT::REQUEST_SCRIPT("xyzhcoord");
					if (SCRIPT::HAS_SCRIPT_LOADED("xyzhcoord"))
					{
						int StackSize;
						StackSize = GAMEPLAY::GET_ALLOCATED_STACK_SIZE();
						SYSTEM::START_NEW_SCRIPT("xyzhcoord", StackSize);
						NotifyAboveMap("~b~ Started script: xyzhcoord");

					}
					else
					{
						NotifyAboveMap("Error: failed to load");
						GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xyzhcoord");
					}
				}
				else
				{
					NotifyAboveMap("~b~ Error: tu00000009_00000000/update.rpf/xbox360/patch/levels/gta5/script.rpf/xyzhcoord Not Found");
				}
			}
			else
			{
				if (SCRIPT::HAS_SCRIPT_LOADED("xyzhcoord"))
				{
					NotifyAboveMap("~b~ Terminated script: xyzhcoord");
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("xyzhcoord");
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xyzhcoord");
				}
			}
		}
		}
		break;
#pragma endregion

#pragma region Scenario Options
	case Scenario_Menu:

		addTitle("Scenario Options");
		addOption("Coffee");
		addOption("Smoke");
		addOption("Binoculars");
		addOption("Freeway");
		addOption("Slumped");
		addOption("Standing");
		addOption("Wash");
		addOption("Car Park Attendant");
		addOption("Cheering");
		addOption("Clipboard");
		addOption("Drill");
		addOption("Cop Idles");
		addOption("Drinking");
		addOption("Drug Dealer");
		addOption("Drug Dealer Hard");
		addOption("Mobile Film Shocking");
		addOption("Gardener Leaf Blower");
		addOption("Gardener Plant");
		addOption("Golf Player");
		addOption("Guard Patrol");
		addOption("Guard Stand");
		addOption("Guard Stand Army");
		addOption("Hammering");
		addOption("Hang Out Street");
		addOption("Hiker Standing");
		addOption("Statue");
		addOption("Janitor");
		addOption("Jog Standing");
		addOption("Leaning");
		addOption("Maid Clean");
		addOption("Muscle Flex");
		addOption("Muscle Free Weights");
		addOption("Musician");
		addOption("Paparazzi");
		addOption("Partying");
		addOption("Picnic");
		addOption("Prostitute High Class");
		addOption("Prostitute Low Class");
		addOption("Push Ups");
		addOption("Seat Ledge");
		addOption("Seat Ledge Eating");
		addOption("Seat STEPS");
		addOption("Seat Wall");
		addOption("Seat Wall Eating");
		addOption("Seat Wall Tablet");
		addOption("Security Shine Torch");
		addOption("Sit Ups");
		addOption("Smoking");
		addOption("Smoking Pot");
		addOption("Stand Fire");
		addOption("Stand Fishing");
		addOption("Stand Impatient");
		addOption("Stand Impatient Upright");
		addOption("Stand Mobile");
		addOption("Stand Mobile Upright");
		addOption("Strip Watch Stand");
		addOption("Stupor");
		addOption("Sunbathe");
		addOption("Sunbathe Back");
		addOption("Superhero");
		addOption("Swimming");
		addOption("Tennis Player");
		addOption("Tourist Map");
		addOption("Tourist MOBILE");
		addOption("Car Mechanic");
		addOption("Welding");
		addOption("Shop Browse");
		addOption("Yoga");
		addOption("Boar Grazing");
		addOption("Cat Sleeping Ground");
		addOption("Cat Sleeping Ledge");
		addOption("Cow Grazing");
		addOption("Coyote Howl");
		addOption("Coyote Rest");
		addOption("Coyote Wander");
		addOption("Chicken hawk Feeding");
		addOption("Chicken hawk Standing");
		addOption("Cormorant Standing");
		addOption("Crow Feeding");
		addOption("Crow Standing");
		addOption("Deer Grazing");
		addOption("Dog Barking Rottweiler");
		addOption("Dog Barking Retriver");
		addOption("Dog Barking Shepherd");
		addOption("Dog Sitting Rottweiler");
		addOption("Dog Sitting Retriver");
		addOption("Dog Sitting Shepherd");
		addOption("Dog Barking Small");
		addOption("Dog Sitting Small");
		addOption("Fish Idle");
		addOption("Gull Feeding");
		addOption("Gull Standing");
		addOption("Hen Pecking");
		addOption("Hen Standing");
		addOption("Mountain Lion Rest");
		addOption("Mountain Lion Wander");
		addOption("Pig Grazing");
		addOption("Pigeon Feeding");
		addOption("Pigeon Standing");
		addOption("Rabbit Eating");
		addOption("Rats Eating");
		addOption("Shark Swim");
		addOption("Bird In Tree");
		addOption("Bird Telegraph Pole");
		addOption("ATM");
		addOption("BBQ");
		addOption("Bin");
		addOption("Shopping Cart");
		addOption("Chin Ups");
		addOption("Chin Ups Army");
		addOption("Chin Ups Prison");
		addOption("Parking Meter");
		addOption("Seat Armchair");
		addOption("Seat Bar");
		addOption("Seat Bench");
		addOption("Seat Bench Drink");
		addOption("Seat Bench Drink Beer");
		addOption("Seat Bench Food");
		addOption("Seat Bus Stop Wait");
		addOption("Seat Chair");
		addOption("Seat Chair Drink");
		addOption("Seat Chair Drink Beer");
		addOption("Seat Chair Food");
		addOption("Seat Chair Upright");
		addOption("Seat Chair MP Player");
		addOption("Seat Computer");
		addOption("Seat Deckchair");
		addOption("Seat Deckchair Drink");
		addOption("Seat Muscle Bench Press");
		addOption("Seat Muscle Bench Press Prison");
		addOption("Seat Sewing");
		addOption("Seat Strip Watch");
		addOption("Seat Sunlounger");
		addOption("Stand Impatient");
		addOption("Cower");
		addOption("Cross Road Wait");
		addOption("Park Car");
		addOption("Movie Bulb");
		addOption("Movie Studio Light");
		addOption("Medic KNEEL");
		addOption("Medic Tend To Dead");
		addOption("Medic Time Of Death");
		addOption("Police Crowd Control");
		addOption("Police Investigate");
		addOption("Stand Cower");
		addOption("Ear To Text");
		addOption("Ear To Text Fat");
		addOption("Musician 2");
		addOption("Stop Tasks");
		switch (getOption())
		{
		case 1:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, 1); break;
		case 2:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_SMOKE", 0, 1); break;
		case 3:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, 1); break;
		case 4:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_FREEWAY", 0, 1); break;
		case 5:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_SLUMPED", 0, 1); break;
		case 6:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_STANDING", 0, 1); break;
		case 7:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_WASH", 0, 1); break;
		case 8:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CAR_PARK_ATTENDANT", 0, 1); break;
		case 9:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CHEERING", 0, 1); break;
		case 10:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, 1); break;
		case 11:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, 1); break;
		case 12:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, 1); break;
		case 13:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, 1); break;
		case 14:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER", 0, 1); break;
		case 15:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, 1); break;
		case 16:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, 1); break;
		case 17:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, 1); break;
		case 18:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_PLANT", 0, 1); break;
		case 19:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, 1); break;
		case 20:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_PATROL", 0, 1); break;
		case 21:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_STAND", 0, 1); break;
		case 22:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_STAND_ARMY", 0, 1); break;
		case 23:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, 1); break;
		case 24:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HANG_OUT_STREET", 0, 1); break;
		case 25:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HIKER_STANDING", 0, 1); break;
		case 26:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HUMAN_STATUE", 0, 1); break;
		case 27:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JANITOR", 0, 1); break;
		case 28:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, 1); break;
		case 29:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_LEANING", 0, 1); break;
		case 30:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MAID_CLEAN", 0, 1); break;
		case 31:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, 1); break;
		case 32:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", 0, 1); break;
		case 33:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, 1); break;
		case 34:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, 1); break;
		case 35:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PARTYING", 0, 1); break;
		case 36:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PICNIC", 0, 1); break;
		case 37:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS", 0, 1); break;
		case 38:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PROSTITUTE_LOW_CLASS", 0, 1); break;
		case 39:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PUSH_UPS", 0, 1); break;
		case 40:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_LEDGE", 0, 1); break;
		case 41:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_LEDGE_EATING", 0, 1); break;
		case 42:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_STEPS", 0, 1); break;
		case 43:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL", 0, 1); break;
		case 44:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL_EATING", 0, 1); break;
		case 45:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL_TABLET", 0, 1); break;
		case 46:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, 1); break;
		case 47:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SIT_UPS", 0, 1); break;
		case 48:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING", 0, 1); break;
		case 49:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, 1); break;
		case 50:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FIRE", 0, 1); break;
		case 51:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, 1); break;
		case 52:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_IMPATIENT", 0, 1); break;
		case 53:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT", 0, 1); break;
		case 54:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_MOBILE", 0, 1); break;
		case 55:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_MOBILE_UPRIGHT", 0, 1); break;
		case 56:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STRIP_WATCH_STAND", 0, 1); break;
		case 57:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STUPOR", 0, 1); break;
		case 58:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUNBATHE", 0, 1); break;
		case 59:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUNBATHE_BACK", 0, 1); break;
		case 60:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, 1); break;
		case 61:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SWIMMING", 0, 1); break;
		case 62:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, 1); break;
		case 63:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TOURIST_MAP", 0, 1); break;
		case 64:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TOURIST_MOBILE", 0, 1); break;
		case 65:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_VEHICLE_MECHANIC", 0, 1); break;
		case 66:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, 1); break;
		case 67:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WINDOW_SHOP_BROWSE", 0, 1); break;
		case 68:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_YOGA", 0, 1); break;
		case 69:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_BOAR_GRAZING", 0, 1); break;
		case 70:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CAT_SLEEPING_GROUND", 0, 1); break;
		case 71:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CAT_SLEEPING_LEDGE", 0, 1); break;
		case 72:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COW_GRAZING", 0, 1); break;
		case 73:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_HOWL", 0, 1); break;
		case 74:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_REST", 0, 1); break;
		case 75:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_WANDER", 0, 1); break;
		case 76:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CHICKENHAWK_FEEDING", 0, 1); break;
		case 77:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CHICKENHAWK_STANDING", 0, 1); break;
		case 78:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CORMORANT_STANDING", 0, 1); break;
		case 79:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CROW_FEEDING", 0, 1); break;
		case 80:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CROW_STANDING", 0, 1); break;
		case 81:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DEER_GRAZING", 0, 1); break;
		case 82:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_ROTTWEILER", 0, 1); break;
		case 83:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_RETRIEVER", 0, 1); break;
		case 84:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_SHEPHERD", 0, 1); break;
		case 85:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_ROTTWEILER", 0, 1); break;
		case 86:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_RETRIEVER", 0, 1); break;
		case 87:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_SHEPHERD", 0, 1); break;
		case 88:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_SMALL", 0, 1); break;
		case 89:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_SMALL", 0, 1); break;
		case 90:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_FISH_IDLE", 0, 1); break;
		case 91:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_GULL_FEEDING", 0, 1); break;
		case 92:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_GULL_STANDING", 0, 1); break;
		case 93:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HEN_PECKING", 0, 1); break;
		case 94:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HEN_STANDING", 0, 1); break;
		case 95:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_MOUNTAIN_LION_REST", 0, 1); break;
		case 96:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_MOUNTAIN_LION_WANDER", 0, 1); break;
		case 97:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIG_GRAZING", 0, 1); break;
		case 98:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIGEON_FEEDING", 0, 1); break;
		case 99:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIGEON_STANDING", 0, 1); break;
		case 100:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_RABBIT_EATING", 0, 1); break;
		case 101:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_RATS_EATING", 0, 1); break;
		case 102:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_SHARK_SWIM", 0, 1); break;
		case 103:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_BIRD_IN_TREE", 0, 1); break;
		case 104:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_BIRD_TELEGRAPH_POLE", 0, 1); break;
		case 105:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_ATM", 0, 1); break;
		case 106:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, 1); break;
		case 107:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BUM_BIN", 0, 1); break;
		case 108:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BUM_SHOPPING_CART", 0, 1); break;
		case 109:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, 1); break;
		case 110:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY", 0, 1); break;
		case 111:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS_PRISON", 0, 1); break;
		case 112:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_PARKING_METER", 0, 1); break;
		case 113:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_ARMCHAIR", 0, 1); break;
		case 114:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BAR", 0, 1); break;
		case 115:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH", 0, 1); break;
		case 116:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_DRINK", 0, 1); break;
		case 117:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_DRINK_BEER", 0, 1); break;
		case 118:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_FOOD", 0, 1); break;
		case 119:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BUS_STOP_WAIT", 0, 1); break;
		case 120:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR", 0, 1); break;
		case 121:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_DRINK", 0, 1); break;
		case 122:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_DRINK_BEER", 0, 1); break;
		case 123:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_FOOD", 0, 1); break;
		case 124:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_UPRIGHT", 0, 1); break;
		case 125:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_MP_PLAYER", 0, 1); break;
		case 126:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_COMPUTER", 0, 1); break;
		case 127:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_DECKCHAIR", 0, 1); break;
		case 128:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_DECKCHAIR_DRINK", 0, 1); break;
		case 129:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, 1); break;
		case 130:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS_PRISON", 0, 1); break;
		case 131:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_SEWING", 0, 1); break;
		case 132:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_STRIP_WATCH", 0, 1); break;
		case 133:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_SUNLOUNGER", 0, 1); break;
		case 134:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_STAND_IMPATIENT", 0, 1); break;
		case 135:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_COWER", 0, 1); break;
		case 136:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_CROSS_ROAD_WAIT", 0, 1); break;
		case 137:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_PARK_CAR", 0, 1); break;
		case 138:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MOVIE_BULB", 0, 1); break;
		case 139:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MOVIE_STUDIO_LIGHT", 0, 1); break;
		case 140:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_KNEEL", 0, 1); break;
		case 141:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_TEND_TO_DEAD", 0, 1); break;
		case 142:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_TIME_OF_DEATH", 0, 1); break;
		case 143:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_POLICE_CROWD_CONTROL", 0, 1); break;
		case 144:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_POLICE_INVESTIGATE", 0, 1); break;
		case 145:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_STAND_COWER", 0, 1); break;
		case 146:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "EAR_TO_TEXT", 0, 1); break;
		case 147:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "EAR_TO_TEXT_FAT", 0, 1); break;
		case 148:
			AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, 2); break;
		case 149:
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); break;
		}
		break;
#pragma endregion
#pragma region Ped Options
	case Ped_Options:

		addTitle("Ped Options");
		addSubmenuOption("Ped Spawner", Ped_Spawner); //1
		addSubmenuOption("Ped Animations", Ped_Animations); //2
		addSubmenuOption("Ped Scenarios", Ped_Scenarios); //3
		addSubmenuOption("Ped Weapon Giver", Ped_WeaponGiver); //4
		addOption("Set As Bodyguard"); //6
		addOption("Clear Ped Tasks"); //7
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5:
			Entity ent;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);
					int my_group;
					my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
					PED::SET_PED_AS_GROUP_LEADER(PLAYER::PLAYER_PED_ID(), my_group);
					PED::SET_PED_AS_GROUP_MEMBER(ent, my_group);
					PED::SET_PED_NEVER_LEAVES_GROUP(ent, my_group);
					//ENTITY::SET_ENTITY_INVINCIBLE(ent, true);
					PED::SET_PED_COMBAT_ABILITY(ent, 100);
					AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(PLAYER::PLAYER_PED_ID(), 100, ent);
					PED::SET_PED_CAN_SWITCH_WEAPON(ent, true);
					PED::SET_GROUP_FORMATION(my_group, 3);
					int blip;
					blip = UI::ADD_BLIP_FOR_ENTITY(ent);
					UI::SET_BLIP_AS_FRIENDLY(blip, true);
					UI::SET_BLIP_SCALE(blip, 1.0);
					UI::SET_BLIP_COLOUR(blip, 3);
					Vector3 EntCoords;
					EntCoords = ENTITY::GET_ENTITY_COORDS(ent, true);
					STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
					GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", EntCoords.x, EntCoords.y, EntCoords.z, 0.0f, 0.0f, 0.0f, 1.0, 0, 0, 0);
				}
			} break;
		case 6:
			Entity ClearTasks;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ClearTasks))
			{
				if (ENTITY::IS_ENTITY_A_PED(ClearTasks))
				{
					AI::CLEAR_PED_TASKS_IMMEDIATELY(ClearTasks);
					Vector3 ClearTasksCoords;
					ClearTasksCoords = ENTITY::GET_ENTITY_COORDS(ClearTasks, true);
					STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
					GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
					GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", ClearTasksCoords.x, ClearTasksCoords.y, ClearTasksCoords.z, 0.0f, 0.0f, 0.0f, 1.0, 0, 0, 0);
				}
			} break;
		}
		break;
#pragma endregion
#pragma region Drive to Waypoint, With Chauffeur
	case PedDriveToWaypoint:

		addTitle("Drive to Waypoint, With Chauffeur");
		addBoolOption("Spawn Chauffer", spawnChauffer);
		addSubmenuOption("Set Driving Mode", Set_Driving_Mode);
		switch (getOption())
		{
		case 1: spawnChauffer = !spawnChauffer; break;
		}
		break;
#pragma endregion
#pragma region Set Driving Mode
	case Set_Driving_Mode:

		addTitle("Set Driving Mode");
		addOption("Rushed");
		addOption("Obey");
		addOption("Fast");
		addOption("Stop");
		addOption("Avoid");
		addOption("Overtake");
		addOption("Expert");
		switch (getOption())
		{
		case 1: DrivingModeSet = Rushed; break;
		case 2: DrivingModeSet = Obey; break;
		case 3: DrivingModeSet = Fast; break;
		case 4: DrivingModeSet = Stop; break;
		case 5: DrivingModeSet = Avoid; break;
		case 6: DrivingModeSet = Overtake; break;
		case 7: DrivingModeSet = Expert; break;
		}
		break;
#pragma endregion
#pragma region Ped Scenarios
	case Ped_Scenarios:

		addTitle("Ped Scenarios");
		addOption("Coffee");
		addOption("Smoke");
		addOption("Binoculars");
		addOption("Freeway");
		addOption("Slumped");
		addOption("Standing");
		addOption("Wash");
		addOption("Car Park Attendant");
		addOption("Cheering");
		addOption("Clipboard");
		addOption("Drill");
		addOption("Cop Idles");
		addOption("Drinking");
		addOption("Drug Dealer");
		addOption("Drug Dealer Hard");
		addOption("Mobile Film Shocking");
		addOption("Gardener Leaf Blower");
		addOption("Gardener Plant");
		addOption("Golf Player");
		addOption("Guard Patrol");
		addOption("Guard Stand");
		addOption("Guard Stand Army");
		addOption("Hammering");
		addOption("Hang Out Street");
		addOption("Hiker Standing");
		addOption("Statue");
		addOption("Janitor");
		addOption("Jog Standing");
		addOption("Leaning");
		addOption("Maid Clean");
		addOption("Muscle Flex");
		addOption("Muscle Free Weights");
		addOption("Musician");
		addOption("Paparazzi");
		addOption("Partying");
		addOption("Picnic");
		addOption("Prostitute High Class");
		addOption("Prostitute Low Class");
		addOption("Push Ups");
		addOption("Seat Ledge");
		addOption("Seat Ledge Eating");
		addOption("Seat Steps");
		addOption("Seat Wall");
		addOption("Seat Wall Eating");
		addOption("Seat Wall Tablet");
		addOption("Security Shine Torch");
		addOption("Sit Ups");
		addOption("Smoking");
		addOption("Smoking Pot");
		addOption("Stand Fire");
		addOption("Stand Fishing");
		addOption("Stand Impatient");
		addOption("Stand Impatient Upright");
		addOption("Stand Mobile");
		addOption("Stand Mobile Upright");
		addOption("Strip Watch Stand");
		addOption("Stupor");
		addOption("Sunbathe");
		addOption("Sunbathe Back");
		addOption("Superhero");
		addOption("Swimming");
		addOption("Tennis Player");
		addOption("Tourist Map");
		addOption("Tourist MOBILE");
		addOption("Car Mechanic");
		addOption("Welding");
		addOption("Shop Browse");
		addOption("Yoga");
		addOption("ATM");
		addOption("BBQ");
		addOption("Bin");
		addOption("Shopping Cart");
		addOption("Chin Ups");
		addOption("Chin Ups Army");
		addOption("Chin Ups Prison");
		addOption("Parking Meter");
		addOption("Seat Armchair");
		addOption("Seat Bar");
		addOption("Seat Bench");
		addOption("Seat Bench Drink");
		addOption("Seat Bench Drink Beer");
		addOption("Seat Bench Food");
		addOption("Seat Bus Stop Wait");
		addOption("Seat Chair");
		addOption("Seat Chair Drink");
		addOption("Seat Chair Drink Beer");
		addOption("Seat Chair Food");
		addOption("Seat Chair Upright");
		addOption("Seat Chair MP Player");
		addOption("Seat Computer");
		addOption("Seat Deckchair");
		addOption("Seat Deckchair Drink");
		addOption("Seat Muscle Bench Press");
		addOption("Seat Muscle Bench Press Prison");
		addOption("Seat Sewing");
		addOption("Seat Strip Watch");
		addOption("Seat Sunlounger");
		addOption("Stand Impatient");
		addOption("Cower");
		addOption("Cross Road Wait");
		addOption("Park Car");
		addOption("Movie Bulb");
		addOption("Movie Studio Light");
		addOption("Medic KNEEL");
		addOption("Medic Tend To Dead");
		addOption("Medic Time Of Death");
		addOption("Police Crowd Control");
		addOption("Police Investigate");
		addOption("Stand Cower");
		addOption("Ear To Text");
		addOption("Ear To Text Fat");
		addOption("Musician 2");
		switch (getOption())
		{
		case 1:
			Entity Scenarios1;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios1))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios1))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios1, "WORLD_HUMAN_AA_COFFEE", 0, 1);
				}
			} break;
		case 2:
			Entity Scenarios2;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios2))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios2))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios2, "WORLD_HUMAN_AA_SMOKE", 0, 1);
				}
			} break;
		case 3:
			Entity Scenarios3;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios3))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios3))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios3, "WORLD_HUMAN_BINOCULARS", 0, 1);
				}
			} break;
		case 4:
			Entity Scenarios4;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios4))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios4))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios4, "WORLD_HUMAN_BUM_FREEWAY", 0, 1);
				}
			}break;
		case 5:
			Entity Scenarios5;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios5))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios5))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios5, "WORLD_HUMAN_BUM_SLUMPED", 0, 1);
				}
			} break;
		case 6:
			Entity Scenarios6;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios6))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios6))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios6, "WORLD_HUMAN_BUM_STANDING", 0, 1);
				}
			} break;
		case 7:
			Entity Scenarios7;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios7))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios7))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios7, "WORLD_HUMAN_BUM_WASH", 0, 1);
				}
			} break;
		case 8:
			Entity Scenarios8;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios8))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios8))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios8, "WORLD_HUMAN_CAR_PARK_ATTENDANT", 0, 1);
				}
			} break;
		case 9:
			Entity Scenarios9;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios9))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios9))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios9, "WORLD_HUMAN_CHEERING", 0, 1);
				}
			} break;
		case 10:
			Entity Scenarios10;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios10))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios10))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios10, "WORLD_HUMAN_CLIPBOARD", 0, 1);
				}
			} break;
		case 11:
			Entity Scenarios11;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios11))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios11))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios11, "WORLD_HUMAN_CONST_DRILL", 0, 1);
				}
			} break;
		case 12:
			Entity Scenarios12;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios12))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios12))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios12, "WORLD_HUMAN_COP_IDLES", 0, 1);
				}
			} break;
		case 13:
			Entity Scenarios13;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios13))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios13))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios13, "WORLD_HUMAN_DRINKING", 0, 1);
				}
			} break;
		case 14:
			Entity Scenarios14;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios14))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios14))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios14, "WORLD_HUMAN_DRUG_DEALER", 0, 1);
				}
			} break;
		case 15:
			Entity Scenarios15;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios15))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios15))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios15, "WORLD_HUMAN_DRUG_DEALER_HARD", 0, 1);
				}
			} break;
		case 16:
			Entity Scenarios16;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios16))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios16))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios16, "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, 1);
				}
			} break;
		case 17:
			Entity Scenarios17;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios17))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios17))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios17, "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, 1);
				}
			} break;
		case 18:
			Entity Scenarios18;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios18))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios18))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios18, "WORLD_HUMAN_GARDENER_PLANT", 0, 1);
				}
			} break;
		case 19:
			Entity Scenarios19;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios19))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios19))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios19, "WORLD_HUMAN_GOLF_PLAYER", 0, 1);
				}
			} break;
		case 20:
			Entity Scenarios20;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios20))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios20))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios20, "WORLD_HUMAN_GUARD_PATROL", 0, 1);
				}
			} break;
		case 21:
			Entity Scenarios21;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios21))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios21))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios21, "WORLD_HUMAN_GUARD_STAND", 0, 1);
				}
			} break;
		case 22:
			Entity Scenarios22;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios22))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios22))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios22, "WORLD_HUMAN_GUARD_STAND_ARMY", 0, 1);
				}
			} break;
		case 23:
			Entity Scenarios23;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios23))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios23))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios23, "WORLD_HUMAN_HAMMERING", 0, 1);
				}
			} break;
		case 24:
			Entity Scenarios24;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios24))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios24))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios24, "WORLD_HUMAN_HANG_OUT_STREET", 0, 1);
				}
			} break;
		case 25:
			Entity Scenarios25;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios25))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios25))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios25, "WORLD_HUMAN_HIKER_STANDING", 0, 1);
				}
			} break;
		case 26:
			Entity Scenarios26;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios26))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios26))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios26, "WORLD_HUMAN_HUMAN_STATUE", 0, 1);
				}
			} break;
		case 27:
			Entity Scenarios27;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios27))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios27))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios27, "WORLD_HUMAN_JANITOR", 0, 1);
				}
			} break;
		case 28:
			Entity Scenarios28;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios28))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios28))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios28, "WORLD_HUMAN_JOG_STANDING", 0, 1);
				}
			} break;
		case 29:
			Entity Scenarios29;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios29))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios29))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios29, "WORLD_HUMAN_LEANING", 0, 1);
				}
			} break;
		case 30:
			Entity Scenarios30;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios30))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios30))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios30, "WORLD_HUMAN_MAID_CLEAN", 0, 1);
				}
			} break;
		case 31:
			Entity Scenarios31;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios31))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios31))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios31, "WORLD_HUMAN_MUSCLE_FLEX", 0, 1);
				}
			} break;
		case 32:
			Entity Scenarios32;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios32))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios32))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios32, "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", 0, 1);
				}
			} break;
		case 33:
			Entity Scenarios33;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios33))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios33))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios33, "WORLD_HUMAN_MUSICIAN", 0, 1);
				}
			} break;
		case 34:
			Entity Scenarios34;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios34))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios34))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios34, "WORLD_HUMAN_PAPARAZZI", 0, 1);
				}
			} break;
		case 35:
			Entity Scenarios35;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios35))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios35))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios35, "WORLD_HUMAN_PARTYING", 0, 1);
				}
			} break;
		case 36:
			Entity Scenarios36;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios36))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios36))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios36, "WORLD_HUMAN_PICNIC", 0, 1);
				}
			} break;
		case 37:
			Entity Scenarios37;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios37))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios37))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios37, "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS", 0, 1);
				}
			} break;
		case 38:
			Entity Scenarios38;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios38))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios38))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios38, "WORLD_HUMAN_PROSTITUTE_LOW_CLASS", 0, 1);
				}
			} break;
		case 39:
			Entity Scenarios39;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios39))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios39))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios39, "WORLD_HUMAN_PUSH_UPS", 0, 1);
				}
			} break;
		case 40:
			Entity Scenarios40;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios40))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios40))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios40, "WORLD_HUMAN_SEAT_LEDGE", 0, 1);
				}
			} break;
		case 41:
			Entity Scenarios41;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios41))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios41))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios41, "WORLD_HUMAN_SEAT_LEDGE_EATING", 0, 1);
				}
			} break;
		case 42:
			Entity Scenarios42;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios42))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios42))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios42, "WORLD_HUMAN_SEAT_STEPS", 0, 1);
				}
			} break;
		case 43:
			Entity Scenarios43;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios43))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios43))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios43, "WORLD_HUMAN_SEAT_WALL", 0, 1);
				}
			} break;
		case 44:
			Entity Scenarios44;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios44))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios44))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios44, "WORLD_HUMAN_SEAT_WALL_EATING", 0, 1);
				}
			} break;
		case 45:
			Entity Scenarios45;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios45))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios45))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios45, "WORLD_HUMAN_SEAT_WALL_TABLET", 0, 1);
				}
			} break;
		case 46:
			Entity Scenarios46;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios46))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios46))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios46, "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, 1);
				}
			} break;
		case 47:
			Entity Scenarios47;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios47))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios47))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios47, "WORLD_HUMAN_SIT_UPS", 0, 1);
				}
			} break;
		case 48:
			Entity Scenarios48;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios48))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios48))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios48, "WORLD_HUMAN_SMOKING", 0, 1);
				}
			} break;
		case 49:
			Entity Scenarios49;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios49))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios49))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios49, "WORLD_HUMAN_SMOKING_POT", 0, 1);
				}
			} break;
		case 50:
			Entity Scenarios50;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios50))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios50))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios50, "WORLD_HUMAN_STAND_FIRE", 0, 1);
				}
			} break;
		case 51:
			Entity Scenarios51;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios51))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios51))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios51, "WORLD_HUMAN_STAND_FISHING", 0, 1);
				}
			} break;
		case 52:
			Entity Scenarios52;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios52))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios52))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios52, "WORLD_HUMAN_STAND_IMPATIENT", 0, 1);
				}
			} break;
		case 53:
			Entity Scenarios53;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios53))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios53))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios53, "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT", 0, 1);
				}
			} break;
		case 54:
			Entity Scenarios54;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios54))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios54))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios54, "WORLD_HUMAN_STAND_MOBILE", 0, 1);
				}
			} break;
		case 55:
			Entity Scenarios55;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios55))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios55))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios55, "WORLD_HUMAN_STAND_MOBILE_UPRIGHT", 0, 1);
				}
			} break;
		case 56:
			Entity Scenarios56;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios56))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios56))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios56, "WORLD_HUMAN_STRIP_WATCH_STAND", 0, 1);
				}
			} break;
		case 57:
			Entity Scenarios57;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios57))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios57))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios57, "WORLD_HUMAN_STUPOR", 0, 1);
				}
			} break;
		case 58:
			Entity Scenarios58;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios58))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios58))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios58, "WORLD_HUMAN_SUNBATHE", 0, 1);
				}
			} break;
		case 59:
			Entity Scenarios59;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios59))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios59))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios59, "WORLD_HUMAN_SUNBATHE_BACK", 0, 1);
				}
			} break;
		case 60:
			Entity Scenarios60;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios60))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios60))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios60, "WORLD_HUMAN_SUPERHERO", 0, 1);
				}
			} break;
		case 61:
			Entity Scenarios61;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios61))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios61))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios61, "WORLD_HUMAN_SWIMMING", 0, 1);
				}
			} break;
		case 62:
			Entity Scenarios62;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios62))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios62))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios62, "WORLD_HUMAN_TENNIS_PLAYER", 0, 1);
				}
			} break;
		case 63:
			Entity Scenarios63;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios63))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios63))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios63, "WORLD_HUMAN_TOURIST_MAP", 0, 1);
				}
			}
			break;
		case 64:
			Entity Scenarios64;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios64))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios64))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios64, "WORLD_HUMAN_TOURIST_MOBILE", 0, 1);
				}
			}
			break;
		case 65:
			Entity Scenarios65;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios65))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios65))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios65, "WORLD_HUMAN_VEHICLE_MECHANIC", 0, 1);
				}
			}
			break;
		case 66:
			Entity Scenarios66;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios66))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios66))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios66, "WORLD_HUMAN_WELDING", 0, 1);
				}
			}
			break;
		case 67:
			Entity Scenarios67;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios67))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios67))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios67, "WORLD_HUMAN_WINDOW_SHOP_BROWSE", 0, 1);
				}
			}
			break;
		case 68:
			Entity Scenarios68;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios68))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios68))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios68, "WORLD_HUMAN_YOGA", 0, 1);
				}
			}
			break;
		case 69:
			Entity Scenarios69;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios69))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios69))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios69, "PROP_HUMAN_ATM", 0, 1);
				}
			}
			break;
		case 70:
			Entity Scenarios70;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios70))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios70))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios70, "PROP_HUMAN_BBQ", 0, 1);
				}
			}
			break;
		case 71:
			Entity Scenarios71;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios71))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios71))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios71, "PROP_HUMAN_BUM_BIN", 0, 1);
				}
			}
			break;
		case 72:
			Entity Scenarios72;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios72))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios72))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios72, "PROP_HUMAN_BUM_SHOPPING_CART", 0, 1);
				}
			}
			break;
		case 73:
			Entity Scenarios73;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios73))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios73))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios73, "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, 1);
				}
			} break;
		case 74:
			Entity Scenarios74;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios74))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios74))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios74, "PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY", 0, 1);
				}
			}
			break;
		case 75:
			Entity Scenarios75;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios75))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios75))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios75, "PROP_HUMAN_MUSCLE_CHIN_UPS_PRISON", 0, 1);
				}
			}
			break;
		case 76:
			Entity Scenarios76;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios76))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios76))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios76, "PROP_HUMAN_PARKING_METER", 0, 1);
				}
			}
			break;
		case 77:
			Entity Scenarios77;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios77))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios77))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios77, "PROP_HUMAN_SEAT_ARMCHAIR", 0, 1);
				}
			}
			break;
		case 78:
			Entity Scenarios78;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios78))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios78))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios78, "PROP_HUMAN_SEAT_BAR", 0, 1);
				}
			}
			break;
		case 79:
			Entity Scenarios79;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios79))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios79))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios79, "PROP_HUMAN_SEAT_BENCH", 0, 1);
				}
			}
			break;
		case 80:
			Entity Scenarios80;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios80))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios80))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios80, "PROP_HUMAN_SEAT_BENCH_DRINK", 0, 1);
				}
			}
			break;
		case 81:
			Entity Scenarios81;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios81))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios81))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios81, "PROP_HUMAN_SEAT_BENCH_DRINK_BEER", 0, 1);
				}
			}
			break;
		case 82:
			Entity Scenarios82;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios82))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios82))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios82, "PROP_HUMAN_SEAT_BENCH_FOOD", 0, 1);
				}
			}
			break;
		case 83:
			Entity Scenarios83;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios83))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios83))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios83, "PROP_HUMAN_SEAT_BUS_STOP_WAIT", 0, 1);
				}
			}
			break;
		case 84:
			Entity Scenarios84;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios84))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios84))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios84, "PROP_HUMAN_SEAT_CHAIR", 0, 1);
				}
			}
			break;
		case 85:
			Entity Scenarios85;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios85))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios85))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios85, "PROP_HUMAN_SEAT_CHAIR_DRINK", 0, 1);
				}
			}
			break;
		case 86:
			Entity Scenarios86;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios86))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios86))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios86, "PROP_HUMAN_SEAT_CHAIR_DRINK_BEER", 0, 1);
				}
			}
			break;
		case 87:
			Entity Scenarios87;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios87))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios87))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios87, "PROP_HUMAN_SEAT_CHAIR_FOOD", 0, 1);
				}
			}
			break;
		case 88:
			Entity Scenarios88;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios88))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios88))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios88, "PROP_HUMAN_SEAT_CHAIR_UPRIGHT", 0, 1);
				}
			}
			break;
		case 89:
			Entity Scenarios89;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios89))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios89))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios89, "PROP_HUMAN_SEAT_CHAIR_MP_PLAYER", 0, 1);
				}
			}
			break;
		case 90:
			Entity Scenarios90;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios90))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios90))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios90, "PROP_HUMAN_SEAT_COMPUTER", 0, 1);
				}
			}
			break;
		case 91:
			Entity Scenarios91;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios91))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios91))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios91, "PROP_HUMAN_SEAT_DECKCHAIR", 0, 1);
				}
			}
			break;
		case 92:
			Entity Scenarios92;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios92))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios92))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios92, "PROP_HUMAN_SEAT_DECKCHAIR_DRINK", 0, 1);
				}
			}
			break;
		case 93:
			Entity Scenarios93;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios93))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios93))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios93, "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, 1);
				}
			}
			break;
		case 94:
			Entity Scenarios94;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios94))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios94))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios94, "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS_PRISON", 0, 1);
				}
			}
			break;
		case 95:
			Entity Scenarios95;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios95))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios95))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios95, "PROP_HUMAN_SEAT_SEWING", 0, 1);
				}
			}
			break;
		case 96:
			Entity Scenarios96;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios96))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios96))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios96, "PROP_HUMAN_SEAT_STRIP_WATCH", 0, 1);
				}
			}
			break;
		case 97:
			Entity Scenarios97;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios97))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios97))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios97, "PROP_HUMAN_SEAT_SUNLOUNGER", 0, 1);
				}
			}
			break;
		case 98:
			Entity Scenarios98;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios98))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios98))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios98, "PROP_HUMAN_STAND_IMPATIENT", 0, 1);
				}
			}
			break;
		case 99:
			Entity Scenarios99;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios99))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios99))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios99, "CODE_HUMAN_COWER", 0, 1);
				}
			}
			break;
		case 100:
			Entity Scenarios100;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios100))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios100))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios100, "CODE_HUMAN_CROSS_ROAD_WAIT", 0, 1);
				}
			}
			break;
		case 101:
			Entity Scenarios101;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios101))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios101))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios101, "CODE_HUMAN_PARK_CAR", 0, 1);
				}
			}
			break;
		case 102:
			Entity Scenarios102;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios102))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios102))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios102, "PROP_HUMAN_MOVIE_BULB", 0, 1);
				}
			}
			break;
		case 103:
			Entity Scenarios103;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios103))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios103))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios103, "PROP_HUMAN_MOVIE_STUDIO_LIGHT", 0, 1);
				}
			}
			break;
		case 104:
			Entity Scenarios104;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios104))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios104))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios104, "CODE_HUMAN_MEDIC_KNEEL", 0, 1);
				}
			}
			break;
		case 105:
			Entity Scenarios105;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios105))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios105))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios105, "CODE_HUMAN_MEDIC_TEND_TO_DEAD", 0, 1);
				}
			}
			break;
		case 106:
			Entity Scenarios106;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios106))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios106))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios106, "CODE_HUMAN_MEDIC_TIME_OF_DEATH", 0, 1);
				}
			}
			break;
		case 107:
			Entity Scenarios107;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios107))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios107))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios107, "CODE_HUMAN_POLICE_CROWD_CONTROL", 0, 1);
				}
			}
			break;
		case 108:
			Entity Scenarios108;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios108))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios108))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios108, "CODE_HUMAN_POLICE_INVESTIGATE", 0, 1);
				}
			}
			break;
		case 109:
			Entity Scenarios109;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios109))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios109))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios109, "CODE_HUMAN_STAND_COWER", 0, 1);
				}
			}
			break;
		case 110:
			Entity Scenarios110;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios110))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios110))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios110, "EAR_TO_TEXT", 0, 1);
				}
			}
			break;
		case 111:
			Entity Scenarios111;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios111))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios111))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios111, "EAR_TO_TEXT_FAT", 0, 1);
				}
			}
			break;
		case 112:
			Entity Scenarios112;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Scenarios112))
			{
				if (ENTITY::IS_ENTITY_A_PED(Scenarios112))
				{
					AI::TASK_START_SCENARIO_IN_PLACE(Scenarios112, "WORLD_HUMAN_MUSICIAN", 0, 2);
				}
			}
			break;
		}
		break;
#pragma endregion 
#pragma region Ped Weapon Giver
	case Ped_WeaponGiver:

		addTitle("Ped Weapon Giver");
		addOption("Give RPG"); //1
		addOption("Give Minigun"); //2
		addOption("Give Combat MG"); //3
		addOption("Give Flare Gun"); //4
		addOption("Give Assault Rifle"); //5
		addOption("Give Grenade Launcher"); //6
		addOption("Give Heavy Sniper"); //7
		switch (getOption())
		{
		case 1:
			Entity ent3;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent3))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent3))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent3, 0xB1CA77B1, 9999, 1); // 1
				}
			} break;
		case 2:
			Entity ent4;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent4))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent4))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent4, 0x42BF8A85, 9999, 1); // 2
				}
			} break;
		case 3:
			Entity ent5;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent5))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent5))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent5, 0x7FD62962, 9999, 1); //3
				}
			} break;
		case 4:
			Entity ent6;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent6))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent6))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent6, 0x47757124, 9999, 1); //4
				}
			} break;
		case 5:
			Entity ent7;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent7))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent7))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent7, 0xBFEFFF6D, 9999, 1); //5
				}
			} break;
		case 6:
			Entity ent8;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent8))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent8))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent8, 0xA284510B, 9999, 1); //6
				}
			} break;
		case 7:
			Entity ent9;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent9))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent9))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent9, 0x0C472FE2, 9999, 1); //7
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region Ped Animations
	case Ped_Animations:

		addTitle("Ped Animations");
		addSubmenuOption("Sport Animations", Sport_Animations);
		addSubmenuOption("Sex Animations", Sex_Animations);
		addSubmenuOption("Dance Animations", Dance_Animations);
		break;
#pragma endregion
#pragma region Sport Animations
	case Sport_Animations:

		addTitle("Sport Animations");
		addOption("Situps"); //1
		addOption("Pushups"); //2
		addOption("Bench Press"); //3
		addOption("Chin Ups"); //4
		addOption("Free Weights"); //5
		addOption("Flex Side"); //6
		addOption("Flex Front"); //7
		switch (getOption())
		{
		case 1:
			Entity ent10;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent10))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent10))
				{
					doAnimation(ent10, "amb@world_human_sit_ups@male@base", "base");
				}
			}
			break;
		case 2:
			Entity ent11;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent11))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent11))
				{
					doAnimation(ent11, "amb@world_human_push_ups@male@base", "base");
				}
			}
			break;
		case 3:
			Entity ent12;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent12))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent12))
				{
					doAnimation(ent12, "amb@prop_human_seat_muscle_bench_press@base", "base");
				}
			}
			break;
		case 4:
			Entity ent13;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent13))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent13))
				{
					doAnimation(ent13, "amb@prop_human_muscle_chin_ups@male@base", "base");
				}
			}
			break;
		case 5:
			Entity ent14;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent14))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent14))
				{
					doAnimation(ent14, "amb@world_human_muscle_free_weights@male@barbell@base", "base");
				}
			}
			break;
		case 6:
			Entity ent15;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent15))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent15))
				{
					doAnimation(ent15, "amb@world_human_muscle_flex@arms_at_side@base", "base");
				}
			}
			break;
		case 7:
			Entity ent16;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent16))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent16))
				{
					doAnimation(ent16, "amb@world_human_muscle_flex@arms_in_front@base", "base");
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region Sex Animations
	case Sex_Animations:

		addTitle("Sex Animations");
		addOption("Fuck"); //1
		addOption("Fuck 2"); //2
		addOption("Car Sex (Male)"); //3
		addOption("Car Sex (Female)"); //4
		addOption("Drunk Car Sex (Male)"); //5
		addOption("Drunk Car Sex (Female)"); //6
		addOption("Prostitue Male Sex"); //7
		addOption("Prostitue Female Sex"); //8
		addOption("Prostitue Male BJ"); //9
		addOption("Prostitue Female BJ"); //10
		switch (getOption())
		{
		case 1:
			Entity ent17;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent17))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent17))
				{
					doAnimation(ent17, "rcmpaparazzo_2", "shag_loop_a");
				}
			}
			break;
		case 2:
			Entity ent18;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent18))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent18))
				{
					doAnimation(ent18, "rcmpaparazzo_2", "shag_loop_poppy");
				}
			}
			break;
		case 3:
			Entity ent19;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent19))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent19))
				{
					doAnimation(ent19, "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_m");
				}
			}
			break;
		case 4:
			Entity ent20;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent20))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent20))
				{
					doAnimation(ent20, "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_f");
				}
			}
			break;
		case 5:
			Entity ent21;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent21))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent21))
				{
					doAnimation(ent21, "random@drunk_driver_2", "cardrunksex_loop_m");
				}
			}
			break;
		case 6:
			Entity ent22;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent22))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent22))
				{
					doAnimation(ent22, "random@drunk_driver_2", "cardrunksex_loop_f");
				}
			}
			break;
		case 7:
			Entity ent23;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent23))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent23))
				{
					doAnimation(ent23, "mini@prostitutes@sexnorm_veh", "sex_loop_male");
				}
			}
			break;
		case 8:
			Entity ent24;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent24))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent24))
				{
					doAnimation(ent24, "mini@prostitutes@sexnorm_veh", "sex_loop_prostitute");
				}
			}
			break;
		case 9:
			Entity ent25;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent25))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent25))
				{
					doAnimation(ent25, "mini@prostitutes@sexnorm_veh", "bj_loop_male");
				}
			}
			break;
		case 10:
			Entity ent26;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent26))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent26))
				{
					doAnimation(ent26, "mini@prostitutes@sexnorm_veh", "bj_loop_prostitute");
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region Dance Animations
	case Dance_Animations:

		addTitle("Dance Animations");
		addOption("Pole Dance"); //1
		addOption("Pole Dance 2"); //2
		addOption("Pole Dance 3"); //3
		addOption("Private Dance"); //4
		addOption("Tap Dancing Heaven"); //5
		addOption("Buttwag Dance"); //6
		addOption("Verse Dance"); //7
		addOption("Heaven Dance"); //8
		switch (getOption())
		{
		case 1:
			Entity ent27;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent27))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent27))
				{
					doAnimation(ent27, "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
				}
			}
			break;
		case 2:
			Entity ent28;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent28))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent28))
				{
					doAnimation(ent28, "mini@strip_club@pole_dance@pole_dance2", "pd_dance_02");
				}
			}
			break;
		case 3:
			Entity ent29;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent29))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent29))
				{
					doAnimation(ent29, "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03");
				}
			}
			break;
		case 4:
			Entity ent30;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent30))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent30))
				{
					doAnimation(ent30, "mini@strip_club@private_dance@part1", "priv_dance_p1");
				}
			}
			break;
		case 5:
			Entity ent31;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent31))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent31))
				{
					doAnimation(ent31, "special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel");
				}
			}
			break;
		case 6:
			Entity ent32;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent32))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent32))
				{
					doAnimation(ent32, "special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag");
				}
			}
			break;
		case 7:
			Entity ent33;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent33))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent33))
				{
					doAnimation(ent33, "special_ped@mountain_dancer@monologue_4@monologue_4a", "mnt_dnc_verse");
				}
			}
			break;
		case 8:
			Entity ent34;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &ent34))
			{
				if (ENTITY::IS_ENTITY_A_PED(ent34))
				{
					doAnimation(ent34, "special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven");
				}
			}
			break;
		}
		break;
#pragma endregion
#pragma region Vision Options
	case Vision_Options:

		addTitle("Vision Options");
		addOption("Stop Visions"); //1
		addOption("Switch HUD In"); //2
		addOption("Switch HUD Out"); //3
		addOption("Focus In"); //4
		addOption("Focus Out"); //5
		addOption("Minigame End Neutral"); //7
		addOption("Minigame End Trevor");  //8
		addOption("Minigame End Franklin"); //9
		addOption("Minigame End Michael"); //10
		addOption("Minigame Transition Out"); //11
		addOption("Minigame Transition In"); //12
		addOption("Switch Short Neutral In"); //13
		addOption("Switch Short Franklin In"); //15
		addOption("Switch Short Trevor In"); //16
		addOption("Switch Short Michael In"); //17
		addOption("Switch Open Michael In"); //18
		addOption("Switch Open Franklin In"); //19
		addOption("Switch Open Trevor In"); //20
		addOption("Switch HUD Michael Out"); //21
		addOption("Switch HUD Franklin Out"); //22
		addOption("Switch HUD Trevor Out"); //23
		addOption("Switch Short Franklin Mid"); //24
		addOption("Switch Short Michael Mid"); //25
		addOption("Switch Short Trevor Mid"); //26
		addOption("Death Fail Out"); //27
		addOption("Cam Push In Neutral"); //28
		addOption("Cam Push In Franklin"); //29
		addOption("Cam Push In Michael"); //30
		addOption("Cam Push In Trevor"); //31
		addOption("Switch Open MichaelIn"); //32
		addOption("Switch Scene Franklin"); //33
		addOption("Switch Scene Trevor"); //34
		addOption("Switch Scene Michael"); //35
		addOption("Switch Scene Neutral"); //36
		addOption("MP Celeb Win"); //37
		addOption("MP Celeb Win Out"); //38
		addOption("MP Celeb Lose"); //39
		addOption("MP Celeb Lose Out"); //40
		addOption("Death Fail Neutral In"); //41
		addOption("Death Fail MP Dark"); //42
		addOption("Death Fail MP In"); //43
		addOption("MP Celeb Preload Fade"); //44
		addOption("Peyote End Out"); //45
		addOption("Peyote End In"); //46
		addOption("Peyote In"); //47
		addOption("Peyote Out"); //48
		addOption("MP Race Crash"); //49
		addOption("Success Franklin"); //50
		addOption("Success Trevor"); //51
		addOption("Success Michael"); //52
		addOption("Drugs Michael Aliens Fight In"); //53
		addOption("Drugs Michael Aliens Fight"); //54
		addOption("Drugs Michael Aliens Fight Out"); //55
		addOption("Drugs Trevor Clowns Fight In"); //56
		addOption("Drugs Trevor Clowns Fight"); //57
		addOption("Drugs Trevor Clowns Fight Out"); //58
		addOption("Heist Celeb Pass"); //59
		addOption("Heist Celeb Pass BW"); //60
		addOption("Heist Celeb End"); //61
		addOption("Heist Celeb Toast"); //62
		addOption("Menu MG Heist In"); //63
		addOption("Menu MG Tournament In"); //64
		addOption("Menu MG Selection In"); //65
		addOption("Chop Vision"); //66
		addOption("DMT flight intro"); //67
		addOption("DMT flight"); //68
		addOption("Drugs Driving In"); //69
		addOption("Drugs Driving Out"); //70
		addOption("Switch Open Neutral FIB"); //71
		addOption("Heist Locate"); //72
		addOption("MP job load"); //73
		addOption("Race Turbo"); //74
		addOption("MP Intro Logo"); //75
		addOption("Heist Trip Skip Fade"); //76
		addOption("Menu MG Heist Out"); //77
		addOption("MP Corona Switch"); //78
		addOption("Menu MG SelectionTint"); //79
		addOption("Success Neutral"); //80
		addOption("Explosion Josh"); //81
		addOption("Sniper Overlay"); //82
		addOption("Rampage Out"); //83
		addOption("Rampage"); //84
		addOption("Dont Taze Me Bro"); //85
		addOption("Death Fail Out"); //86
		switch (getOption())
		{
		case 1:
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchHUDIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchHUDOut");
			GRAPHICS::STOP_SCREEN_EFFECT("FocusIn");
			GRAPHICS::STOP_SCREEN_EFFECT("FocusOut");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameEndNeutral");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameEndTrevor");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameEndFranklin");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameEndMichael");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameTransitionOut");
			GRAPHICS::STOP_SCREEN_EFFECT("MinigameTransitionIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortNeutralIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortFranklinIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortTrevorIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortMichaelIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchOpenMichaelIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchOpenFranklinIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchOpenTrevorIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchHUDMichaelOut");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchHUDFranklinOut");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchHUDTrevorOut");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortFranklinMid");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortMichaelMid");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchShortTrevorMid");
			GRAPHICS::STOP_SCREEN_EFFECT("DeathFailOut");
			GRAPHICS::STOP_SCREEN_EFFECT("CamPushInNeutral");
			GRAPHICS::STOP_SCREEN_EFFECT("CamPushInFranklin");
			GRAPHICS::STOP_SCREEN_EFFECT("CamPushInMichael");
			GRAPHICS::STOP_SCREEN_EFFECT("CamPushInTrevor");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchOpenMichaelIn");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchSceneFranklin");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchSceneTrevor");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchSceneMichael");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchSceneNeutral");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_Celeb_Win");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_Celeb_Win_Out");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_Celeb_Lose");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_Celeb_Lose_Out");
			GRAPHICS::STOP_SCREEN_EFFECT("DeathFailNeutralIn");
			GRAPHICS::STOP_SCREEN_EFFECT("DeathFailMPDark");
			GRAPHICS::STOP_SCREEN_EFFECT("DeathFailMPIn");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_Celeb_Preload_Fade");
			GRAPHICS::STOP_SCREEN_EFFECT("PeyoteEndOut");
			GRAPHICS::STOP_SCREEN_EFFECT("PeyoteEndIn");
			GRAPHICS::STOP_SCREEN_EFFECT("PeyoteIn");
			GRAPHICS::STOP_SCREEN_EFFECT("PeyoteOut");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_race_crash");
			GRAPHICS::STOP_SCREEN_EFFECT("SuccessFranklin");
			GRAPHICS::STOP_SCREEN_EFFECT("SuccessTrevor");
			GRAPHICS::STOP_SCREEN_EFFECT("SuccessMichael");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsMichaelAliensFightIn");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsMichaelAliensFight");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsMichaelAliensFightOut");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsTrevorClownsFightIn");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsTrevorClownsFight");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsTrevorClownsFightOut");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistCelebPass");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistCelebPassBW");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistCelebEnd");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistCelebToast");
			GRAPHICS::STOP_SCREEN_EFFECT("MenuMGHeistIn");
			GRAPHICS::STOP_SCREEN_EFFECT("MenuMGTournamentIn");
			GRAPHICS::STOP_SCREEN_EFFECT("MenuMGSelectionIn");
			GRAPHICS::STOP_SCREEN_EFFECT("ChopVision");
			GRAPHICS::STOP_SCREEN_EFFECT("DMT_flight_intro");
			GRAPHICS::STOP_SCREEN_EFFECT("DMT_flight");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsDrivingIn");
			GRAPHICS::STOP_SCREEN_EFFECT("DrugsDrivingOut");
			GRAPHICS::STOP_SCREEN_EFFECT("SwitchOpenNeutralFIB5");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistLocate");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_job_load");
			GRAPHICS::STOP_SCREEN_EFFECT("RaceTurbo");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_intro_logo");
			GRAPHICS::STOP_SCREEN_EFFECT("HeistTripSkipFade");
			GRAPHICS::STOP_SCREEN_EFFECT("MenuMGHeistOut");
			GRAPHICS::STOP_SCREEN_EFFECT("MP_corona_switch");
			GRAPHICS::STOP_SCREEN_EFFECT("MenuMGSelectionTint");
			GRAPHICS::STOP_SCREEN_EFFECT("SuccessNeutral");
			GRAPHICS::STOP_SCREEN_EFFECT("ExplosionJosh3");
			GRAPHICS::STOP_SCREEN_EFFECT("SniperOverlay");
			GRAPHICS::STOP_SCREEN_EFFECT("RampageOut");
			GRAPHICS::STOP_SCREEN_EFFECT("Rampage");
			GRAPHICS::STOP_SCREEN_EFFECT("Dont_tazeme_bro");
			GRAPHICS::STOP_SCREEN_EFFECT("DeathFailOut"); break;
			//GRAPHICS::START_SCREEN_EFFECT("RaceTurbo", 0, 0);
		case 2:
			GRAPHICS::START_SCREEN_EFFECT("SwitchHUDIn", 0, 0); break;
		case 3:
			GRAPHICS::START_SCREEN_EFFECT("SwitchHUDOut", 0, 0); break;
		case 4:
			GRAPHICS::START_SCREEN_EFFECT("FocusIn", 0, 0); break;
		case 5:
			GRAPHICS::START_SCREEN_EFFECT("FocusOut", 0, 0); break;
		case 6:
			GRAPHICS::START_SCREEN_EFFECT("MinigameEndNeutral", 0, 0); break;
		case 7:
			GRAPHICS::START_SCREEN_EFFECT("MinigameEndTrevor", 0, 0); break;
		case 8:
			GRAPHICS::START_SCREEN_EFFECT("MinigameEndFranklin", 0, 0); break;
		case 9:
			GRAPHICS::START_SCREEN_EFFECT("MinigameEndMichael", 0, 0); break;
		case 10:
			GRAPHICS::START_SCREEN_EFFECT("MinigameTransitionOut", 0, 0); break;
		case 11:
			GRAPHICS::START_SCREEN_EFFECT("MinigameTransitionIn", 0, 0); break;
		case 12:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortNeutralIn", 0, 0); break;
		case 14:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortFranklinIn", 0, 0); break;
		case 15:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortTrevorIn", 0, 0); break;
		case 16:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortMichaelIn", 0, 0); break;
		case 17:
			GRAPHICS::START_SCREEN_EFFECT("SwitchOpenMichaelIn", 0, 0); break;
		case 18:
			GRAPHICS::START_SCREEN_EFFECT("SwitchOpenFranklinIn", 0, 0); break;
		case 19:
			GRAPHICS::START_SCREEN_EFFECT("SwitchOpenTrevorIn", 0, 0); break;
		case 20:
			GRAPHICS::START_SCREEN_EFFECT("SwitchHUDMichaelOut", 0, 0); break;
		case 21:
			GRAPHICS::START_SCREEN_EFFECT("SwitchHUDFranklinOut", 0, 0); break;
		case 22:
			GRAPHICS::START_SCREEN_EFFECT("SwitchHUDTrevorOut", 0, 0); break;
		case 23:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortFranklinMid", 0, 0); break;
		case 24:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortMichaelMid", 0, 0); break;
		case 25:
			GRAPHICS::START_SCREEN_EFFECT("SwitchShortTrevorMid", 0, 0); break;
		case 26:
			GRAPHICS::START_SCREEN_EFFECT("DeathFailOut", 0, 0); break;
		case 27:
			GRAPHICS::START_SCREEN_EFFECT("CamPushInNeutral", 0, 0); break;
		case 28:
			GRAPHICS::START_SCREEN_EFFECT("CamPushInFranklin", 0, 0); break;
		case 29:
			GRAPHICS::START_SCREEN_EFFECT("CamPushInMichael", 0, 0); break;
		case 30:
			GRAPHICS::START_SCREEN_EFFECT("CamPushInTrevor", 0, 0); break;
		case 31:
			GRAPHICS::START_SCREEN_EFFECT("SwitchOpenMichaelIn", 0, 0); break;
		case 32:
			GRAPHICS::START_SCREEN_EFFECT("SwitchSceneFranklin", 0, 0); break;
		case 33:
			GRAPHICS::START_SCREEN_EFFECT("SwitchSceneTrevor", 0, 0); break;
		case 34:
			GRAPHICS::START_SCREEN_EFFECT("SwitchSceneMichael", 0, 0); break;
		case 35:
			GRAPHICS::START_SCREEN_EFFECT("SwitchSceneNeutral", 0, 0); break;
		case 36:
			GRAPHICS::START_SCREEN_EFFECT("MP_Celeb_Win", 0, 0); break;
		case 37:
			GRAPHICS::START_SCREEN_EFFECT("MP_Celeb_Win_Out", 0, 0); break;
		case 38:
			GRAPHICS::START_SCREEN_EFFECT("MP_Celeb_Lose", 0, 0); break;
		case 39:
			GRAPHICS::START_SCREEN_EFFECT("MP_Celeb_Lose_Out", 0, 0); break;
		case 40:
			GRAPHICS::START_SCREEN_EFFECT("DeathFailNeutralIn", 0, 0); break;
		case 41:
			GRAPHICS::START_SCREEN_EFFECT("DeathFailMPDark", 0, 0); break;
		case 42:
			GRAPHICS::START_SCREEN_EFFECT("DeathFailMPIn", 0, 0); break;
		case 43:
			GRAPHICS::START_SCREEN_EFFECT("MP_Celeb_Preload_Fade", 0, 0); break;
		case 44:
			GRAPHICS::START_SCREEN_EFFECT("PeyoteEndOut", 0, 0); break;
		case 45:
			GRAPHICS::START_SCREEN_EFFECT("PeyoteEndIn", 0, 0); break;
		case 46:
			GRAPHICS::START_SCREEN_EFFECT("PeyoteIn", 0, 0); break;
		case 47:
			GRAPHICS::START_SCREEN_EFFECT("PeyoteOut", 0, 0); break;
		case 48:
			GRAPHICS::START_SCREEN_EFFECT("MP_race_crash", 0, 0); break;
		case 50:
			GRAPHICS::START_SCREEN_EFFECT("SuccessFranklin", 0, 0); break;
		case 51:
			GRAPHICS::START_SCREEN_EFFECT("SuccessTrevor", 0, 0); break;
		case 52:
			GRAPHICS::START_SCREEN_EFFECT("SuccessMichael", 0, 0); break;
		case 53:
			GRAPHICS::START_SCREEN_EFFECT("DrugsMichaelAliensFightIn", 0, 0); break;
		case 54:
			GRAPHICS::START_SCREEN_EFFECT("DrugsMichaelAliensFight", 0, 0); break;
		case 55:
			GRAPHICS::START_SCREEN_EFFECT("DrugsMichaelAliensFightOut", 0, 0); break;
		case 56:
			GRAPHICS::START_SCREEN_EFFECT("DrugsTrevorClownsFightIn", 0, 0); break;
		case 57:
			GRAPHICS::START_SCREEN_EFFECT("DrugsTrevorClownsFight", 0, 0); break;
		case 58:
			GRAPHICS::START_SCREEN_EFFECT("DrugsTrevorClownsFightOut", 0, 0); break;
		case 59:
			GRAPHICS::START_SCREEN_EFFECT("HeistCelebPass", 0, 0); break;
		case 60:
			GRAPHICS::START_SCREEN_EFFECT("HeistCelebPassBW", 0, 0); break;
		case 61:
			GRAPHICS::START_SCREEN_EFFECT("HeistCelebEnd", 0, 0); break;
		case 62:
			GRAPHICS::START_SCREEN_EFFECT("HeistCelebToast", 0, 0); break;
		case 63:
			GRAPHICS::START_SCREEN_EFFECT("MenuMGHeistIn", 0, 0); break;
		case 64:
			GRAPHICS::START_SCREEN_EFFECT("MenuMGTournamentIn", 0, 0); break;
		case 65:
			GRAPHICS::START_SCREEN_EFFECT("MenuMGSelectionIn", 0, 0); break;
		case 66:
			GRAPHICS::START_SCREEN_EFFECT("ChopVision", 0, 0); break;
		case 67:
			GRAPHICS::START_SCREEN_EFFECT("DMT_flight_intro", 0, 0); break;
		case 68:
			GRAPHICS::START_SCREEN_EFFECT("DMT_flight", 0, 0); break;
		case 69:
			GRAPHICS::START_SCREEN_EFFECT("DrugsDrivingIn", 0, 0); break;
		case 70:
			GRAPHICS::START_SCREEN_EFFECT("DrugsDrivingOut", 0, 0); break;
		case 71:
			GRAPHICS::START_SCREEN_EFFECT("SwitchOpenNeutralFIB5", 0, 0); break;
		case 72:
			GRAPHICS::START_SCREEN_EFFECT("HeistLocate", 0, 0); break;
		case 73:
			GRAPHICS::START_SCREEN_EFFECT("MP_job_load", 0, 0); break;
		case 74:
			GRAPHICS::START_SCREEN_EFFECT("RaceTurbo", 0, 0); break;
		case 75:
			GRAPHICS::START_SCREEN_EFFECT("MP_intro_logo", 0, 0); break;
		case 76:
			GRAPHICS::START_SCREEN_EFFECT("HeistTripSkipFade", 0, 0); break;
		case 77:
			GRAPHICS::START_SCREEN_EFFECT("MenuMGHeistOut", 0, 0); break;
		case 78:
			GRAPHICS::START_SCREEN_EFFECT("MP_corona_switch", 0, 0); break;
		case 79:
			GRAPHICS::START_SCREEN_EFFECT("MenuMGSelectionTint", 0, 0); break;
		case 80:
			GRAPHICS::START_SCREEN_EFFECT("SuccessNeutral", 0, 0); break;
		case 81:
			GRAPHICS::START_SCREEN_EFFECT("ExplosionJosh3", 0, 0); break;
		case 82:
			GRAPHICS::START_SCREEN_EFFECT("SniperOverlay", 0, 0); break;
		case 83:
			GRAPHICS::START_SCREEN_EFFECT("RampageOut", 0, 0); break;
		case 84:
			GRAPHICS::START_SCREEN_EFFECT("Rampage", 0, 0); break;
		case 85:
			GRAPHICS::START_SCREEN_EFFECT("Dont_tazeme_bro", 0, 0); break;
		case 86:
			GRAPHICS::START_SCREEN_EFFECT("DeathFailOut", 0, 0); break;
		}
		break;
#pragma endregion
#pragma region Animation Menu
	case Animations_Menu:

		addTitle("Animation Menu");
		addSubmenuOption("Sport Options", Sport_Options); //1
		addSubmenuOption("Sex Options", Sex_Options); //2
		addSubmenuOption("Dance Options", Dance_Options); //3
		addSubmenuOption("SuperHero Options", SuperHero_Options); //4
		addSubmenuOption("Misc Options", Misc_OptionsAnims); //5
		addSubmenuOption("Police Options", Police_OptionsAnims); //6
		addSubmenuOption("Paparazzi Options", Paparazzi_OptionsAnims); //7
		addSubmenuOption("Cower Options", Cower_OptionsAnims); //8
		addOption("Stop Tasks"); //9
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); break;
		}
		break;
		break;
#pragma endregion
#pragma region Sport Options
	case Sport_Options:

		addTitle("Sport Options");
		addOption("Situps");
		addOption("Pushups");
		addOption("Bench Press");
		addOption("Chin Ups");
		addOption("Free Weights");
		addOption("Flex Side");
		addOption("Flex Front");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_sit_ups@male@base", "base"); break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_push_ups@male@base", "base"); break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@prop_human_seat_muscle_bench_press@base", "base"); break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@prop_human_muscle_chin_ups@male@base", "base"); break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_free_weights@male@barbell@base", "base"); break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_flex@arms_at_side@base", "base"); break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_flex@arms_in_front@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Wank Options
	case Wank_OptionsAnims:
		addTitle("Wank Options");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		addOption("Wank In A Car");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb", "base");
			break;

		}
		break;
#pragma endregion
#pragma region Cower Options
	case Cower_OptionsAnims:

		addTitle("Cower Options");
		addOption("Cower Female Base");
		addOption("Cower Female Enter");
		addOption("Cower Female Exit");
		addOption("Cower Female Idle A");
		addOption("Cower Female React Cowering");
		addOption("Cower Male Base");
		addOption("Cower Male Enter");
		addOption("Cower Male Exit");
		addOption("Cower Male Idle A");
		addOption("Cower Male Idle B");
		addOption("Cower Male React Cowering");
		addOption("Cower Female Stand Base");
		addOption("Cower Female Stand Enter");
		addOption("Cower Female Stand Exit");
		addOption("Cower Female Stand Idle A");
		addOption("Cower Male Stand React Cowering");
		addOption("Cower Male Stand Base");
		addOption("Cower Male Stand Enter");
		addOption("Cower Male Stand Exit");
		addOption("Cower Male Stand Idle A");
		addOption("Cower Male Stand React Cowering");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@female@base", "base");
			break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@female@enter", "enter");
			break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@female@exit", "exit_flee");
			break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@female@idle_a", "idle_c");
			break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@female@react_cowering", "base_back_left");
			break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@base", "base");
			break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@enter", "enter");
			break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@exit", "exit_flee");
			break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@idle_a ", "idle_b");
			break;
		case 10:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@idle_b", "idle_d");
			break;
		case 11:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower@male@react_cowering", "base_back_left");
			break;
		case 12:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@female@base", "base");
			break;
		case 13:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@female@enter", "enter");
			break;
		case 14:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@female@exit", "exit_flee");
			break;
		case 15:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@female@idle_a", "idle_c");
			break;
		case 16:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@female@react_cowering", "base_back_left_exit");
			break;
		case 17:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@male@base", "base");
			break;
		case 18:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@male@enter", "enter");
			break;
		case 19:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@male@exit", "exit_flee");
			break;
		case 20:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@male@idle_a", "idle_b");
			break;
		case 21:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_cower_stand@male@react_cowering ", "base_right");
			break;
		}
		break;
#pragma endregion
#pragma region Police Options
	case Police_OptionsAnims:

		addTitle("Police Options");
		addOption("Police Crowd Control Base");
		addOption("Police Crowd Control Intro");
		addOption("Police Crowd Control A");
		addOption("Police Crowd Control B");
		addOption("Police Investigate Base");
		addOption("Police Investigate Intro");
		addOption("Police Investigate A");
		addOption("Police Investigate B");
		addOption("Police Vehicle Car Base");
		addOption("Police Vehicle Car Idle A");
		addOption("Police Vehicle Car Idle B");
		addOption("Police Bike Front Base");
		addOption("Police Down Town");
		addOption("Police Paleto Bay");
		addOption("Police Rockford");
		addOption("Police Sandy Shores");
		addOption("Police South Central");
		addOption("Police Vespucci");
		addOption("Police Vinewood");
		addOption("Police Bike Front Base");
		addOption("Police Bike Front Ds");
		addOption("Police Bike Front Ds 2");
		addOption("Police Bike Front Ps");
		addOption("Police Bike Front Ps 2");
		addOption("Police Bike Rear Base");
		addOption("Police Bike Rear Ds");
		addOption("Police Bike Rear Ds 2");
		addOption("Police Bike Rear Ps");
		addOption("Police Bike Rear Ps 2");
		addOption("Police Bike Busted");
		addOption("Police Drive By Bike Front 1H");
		addOption("Police Drive By Bike Front Grenade");
		addOption("Police Drive By Bike Front Grenade 2");
		addOption("Police Drive By Bike Front Unarmed");
		addOption("Police Drive By Bike Rear 1H");
		addOption("Police Drive By Bike Rear Grenade");
		addOption("Police Drive By Bike Rear Grenade 2");
		addOption("Police Drive By Bike Rear Unarmed");
		addOption("Police Van Exit To Aim");
		addOption("Police Van Exit To Aim 2");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_crowd_control@base", "base");
			break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_crowd_control@idle_intro", "idle_intro");
			break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_crowd_control@idle_a", "idle_a");
			break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_crowd_control@idle_b", "idle_d");
			break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_investigate@base", "base");
			break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_investigate@idle_intro", "idle_intro");
			break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_investigate@idle_a", "idle_a");
			break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@code_human_police_investigate@idle_b", "idle_f");
			break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_vehicle_police_carbase", "base");
			break;
		case 10:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_vehicle_police_caridle_a", "idle_b");
			break;
		case 11:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_vehicle_police_caridle_b", "idle_e");
			break;
		case 12:
			doAnimation(PLAYER::PLAYER_PED_ID(), "anim@veh@bike@police@front@base", "horn_intro");
			break;
		case 13:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@down_town", "down_town_cam");
			break;
		case 14:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@paleto_bay", "paleto_bay_cam");
			break;
		case 15:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@rockford", "rockford_cam");
			break;
		case 16:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@sandy_shores", "sandy_shores_cam");
			break;
		case 17:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@south_central_a", "south_central_a_cam");
			break;
		case 18:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@vespucci", "vespucci_cam");
			break;
		case 19:
			doAnimation(PLAYER::PLAYER_PED_ID(), "respawn@police@vinewood", "vinewood_cam");
			break;
		case 20:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@front@base", "shunt_from_right");
			break;
		case 21:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@front@ds", "dead_fall_out");
			break;
		case 22:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@front@ds", "jack_dead_victim");
			break;
		case 23:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@front@ps", "jack_dead_victim");
			break;
		case 24:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@front@ps", "get_on_quick");
			break;
		case 25:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@rear@base", "shunt_from_back");
			break;
		case 26:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@rear@ds", "get_out");
			break;
		case 27:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@rear@ds", "jack_base_perp");
			break;
		case 28:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@rear@ps", "jack_base_perp");
			break;
		case 29:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@bike@police@rear@ps", "get_in");
			break;
		case 30:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@busted_bike@police@", "busted");
			break;
		case 31:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@front@1h", "intro_0");
			break;
		case 32:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@front@grenade", "intro_0");
			break;
		case 33:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@front@grenade", "sweep_blocked");
			break;
		case 34:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@front@unarmed", "intro_180l");
			break;
		case 35:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@rear@1h ", "intro_0");
			break;
		case 36:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@rear@grenade", "intro_180l");
			break;
		case 37:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@rear@grenade", "outro_180l");
			break;
		case 38:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@drivebybike@police@rear@unarmed", "outro_180l");
			break;
		case 39:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@van@policet@ds@exit_to_aim", "get_out_east_ccw");
			break;
		case 40:
			doAnimation(PLAYER::PLAYER_PED_ID(), "veh@van@policet@ps@exit_to_aim", "get_out_east");
			break;
		}
		break;
#pragma endregion
#pragma region Mini Games
	case Main_MiniGames:
		addTitle("Mini Games");
		addSubmenuOption("Zombie Attack", Mini_Games);
		addSubmenuOption("Create Escort", Create_Escort_Options);
		addSubmenuOption("Funny Options", funny_options);
		break;
#pragma endregion
#pragma region Mini Games
	case funny_options:
		addTitle("Funny Options");
		addBoolOption("Rich Ppower!", iamrich);
		addBoolOption("Caos Mode", Caosmode);
		addBoolOption("Money Power", banknotesfunny);
		addOption("Stop Task");
		switch (getOption())
		{
		case 1: iamrich = !iamrich; break;
		case 2: Caosmode = !Caosmode;
			doAnimation(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "electrocute"); break;
		case 3: banknotesfunny = !banknotesfunny; break;
		case 4: AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); break;
		}
		break;
#pragma endregion
#pragma region Mini Games
	case Mini_Games:
		addTitle("Zombie Attack");
		addTeleportOption("Teleport To Camp Battle", -1653.552734, -3149.775391, 13.992676);
		addOption("Zombie Attack");
		addOption("Spawn Supplies");
		switch (getOption())
		{
		case 2:
		{
			int SpawnedPed[20];
			char* PedNameArray[20];
			int SpawnedPed_;
			if (RequestNetworkControl(PLAYER::GET_PLAYER_PED(selectedPlayer)))
			{
				if (STREAMING::IS_MODEL_IN_CDIMAGE(0xAC4B4506))
				{
					if (STREAMING::IS_MODEL_VALID(0xAC4B4506))
					{
						STREAMING::REQUEST_MODEL(0xAC4B4506);
						if (STREAMING::HAS_MODEL_LOADED(0xAC4B4506))
						{
							int ped1;
							int ped2;
							int ped3;
							int ped4;
							int ped5;
							int ped6;
							int ped7;
							int ped8;
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY((ped2, ped3, ped4, ped5, ped6, ped7, ped8));
							Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

							SpawnedPed[SpawnedPed_] = PED::CREATE_PED(0x1A, 0x7FD62962, coords.x, coords.y + 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(SpawnedPed[SpawnedPed_], 0x42BF8A85, 9999, 1);

							ped1 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x, coords.y + 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped2, 0x7FD62962, 9999, 1);

							ped2 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x, coords.y + 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped3, 0x7FD62962, 9999, 1);

							SpawnedPed[SpawnedPed_] = PED::CREATE_PED(0x1A, 0x7FD62962, coords.x + 25.0, coords.y, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(SpawnedPed[SpawnedPed_], 0x42BF8A85, 9999, 1);

							ped1 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x, coords.y + 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped2, 0x7FD62962, 9999, 1);

							ped2 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x + 25.0, coords.y, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped3, 0x7FD62962, 9999, 1);

							ped4 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x + 25.0, coords.y, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped4, 0xBFEFFF6D, 9999, 1);

							SpawnedPed[SpawnedPed_] = PED::CREATE_PED(0x1A, 0x7FD62962, coords.x, coords.y - 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(SpawnedPed[SpawnedPed_], 0x42BF8A85, 9999, 1);

							ped1 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x, coords.y - 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped2, 0x7FD62962, 9999, 1);

							ped2 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x, coords.y - 25.0, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped3, 0x7FD62962, 9999, 1);

							SpawnedPed[SpawnedPed_] = PED::CREATE_PED(0x1A, 0x7FD62962, coords.x - 25.0, coords.y, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(SpawnedPed[SpawnedPed_], 0x42BF8A85, 9999, 1);

							ped2 = PED::CREATE_PED(0x1A, 0xAC4B4506, coords.x - 25.0, coords.y, coords.z, 204.8112f, 1, 0);
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped3, 0x7FD62962, 9999, 1);
						}
					}
				}
			}
		case 3:
		{
			int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
			//AMMO
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FLAREGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_HOMINGLAUNCHER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MINIGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RPG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SNIPER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SHOTGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SMG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_PISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK_MP"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			//HEALT
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			//SNAKS
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			//WEAPON
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_PARACHUTE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_LOUDHAILER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_LASSO"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FIREEXTINGUISHER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_NIGHTSTICK"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_CROWBAR"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HAMMER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BAT"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_KNIFE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SMOKEGRENADE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PETROLCAN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MOLOTOV"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_Shoot"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_STICKYBOMB"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GRENADE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MINIGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_RPG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GRENADELAUNCHER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_COMBATMG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYSNIPER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SNIPERRIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ASSAULTSHOTGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PUMPSHOTGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SAWNOFFSHOTGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ADVANCEDRIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_CARBINERIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ASSAULTRIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SMG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MICROSMG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_APPISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_COMBATPISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FIREWORK"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HOMINGLAUNCHER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PROXMINE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FLAREGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MARKSMANRIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYSHOTGUN"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MUSKET"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_VINTAGEPISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_DAGGER"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SPECIALCARBINE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYPISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GUSENBERG"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SNSPISTOL"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BOTTLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BULLPUPRIFLE"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICK_WEAPON_COMBATPDW"), coords.x + 5.0, coords.y, coords.z, 0, 9999, 1, 0, 1);
			//ARMOUR
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x + 5.0, coords.y, coords.z, 0, 100000, 1, 0, 1);
		} break;
		}
		break;
		}
		break;
#pragma endregion
#pragma region Paparazzi Options
	case Paparazzi_OptionsAnims:

		addTitle("Paparazzi Options");
		addOption("Paparazzi Male Base");
		addOption("Paparazzi Male Enter");
		addOption("Paparazzi Male Exit");
		addOption("Paparazzi Male Idle A");
		addOption("Paparazzi Escape In A Car");
		addOption("Paparazzi Escape On Foot");
		addOption("Paparazzi Pap Anims");
		addOption("Paparazzi Peek");
		addOption("Paparazzi Trans");
		addOption("Paparazzi Wait");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_paparazzi@male@base", "base");
			break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_paparazzi@male@enter", "enter");
			break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_paparazzi@male@exit", "exit");
			break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_paparazzi@male@idle_a", "idle_a");
			break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@escape_paparazzi@incar@", "idle_d");
			break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@escape_paparazzi@standing@", "idle_d");
			break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@paparazzi@pap_anims", "sweep_low");
			break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@paparazzi@peek", "right_come_here");
			break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@paparazzi@trans", "trans_right_to_wait");
			break;
		case 10:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@paparazzi@wait", "wait_a");
			break;
		}
		break;
#pragma endregion
#pragma region Dance Options
	case Dance_Options:

		addTitle("Dance Options");
		addOption("Pole Dance");
		addOption("Pole Dance 2");
		addOption("Pole Dance 3");
		addOption("Private Dance");
		addOption("Tap Dancing Heaven");
		addOption("Buttwag Dance");
		addOption("Verse Dance");
		addOption("Heaven Dance");
		addOption("Pole Dance On Stage Enter");
		addOption("Pole Dance On Stage Exit");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance2", "pd_dance_02"); break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03"); break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel"); break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag"); break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_1@monologue_1a", "mnt_dnc_verse"); break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_4@monologue_4a", "mtn_dnc_if_you_want_to_get_to_heaven"); break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@stage_enter ", "stage_enter"); break;

		}
		break;
#pragma endregion
#pragma region Sex Options
	case Sex_Options:

		addTitle("Sex Options");
		addOption("Fuck");
		addOption("Fuck 2");
		addOption("Car Sex (Male)");
		addOption("Car Sex (Female)");
		addOption("Drunk Car Sex (Male)");
		addOption("Drunk Car Sex (Female)");
		addOption("Prostitue Male Sex");
		addOption("Prostitue Female Sex");
		addOption("Prostitue Male BJ");
		addOption("Prostitue Female BJ");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmpaparazzo_2", "shag_loop_a"); break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "rcmpaparazzo_2", "shag_loop_poppy"); break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_m"); break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_f"); break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@drunk_driver_2", "cardrunksex_loop_m"); break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@drunk_driver_2", "cardrunksex_loop_f"); break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "sex_loop_male"); break;
		case 8:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "sex_loop_prostitute"); break;
		case 9:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "bj_loop_male"); break;
		case 10:
			doAnimation(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "bj_loop_prostitute"); break;

		}
		break;
#pragma endregion
#pragma region SuperHero Options
	case SuperHero_Options:

		addTitle("SuperHero Options");
		addOption("Space Pistol");
		addOption("Space Rifle");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_superhero@male@space_pistol@base", "base"); break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "amb@world_human_superhero@male@space_rifle@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Misc Options
	case Misc_OptionsAnims:

		addTitle("Misc Options");
		addOption("Tazer");
		addOption("Stun Fire");
		addOption("Electrocute");
		addOption("Wave Yo Arms");
		addOption("Cop Kneeling Arrest");
		addOption("Cop Hands Up");
		addOption("Trevor Smoking Meth");
		switch (getOption())
		{
		case 1:
			doAnimation(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "electrocute"); break;
		case 2:
			doAnimation(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "on_fire"); break;
		case 3:
			doAnimation(PLAYER::PLAYER_PED_ID(), "stungun@standing", "damage"); break;
		case 4:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@car_thief@victimpoints_ig_3", "arms_waving"); break;
		case 5:
			doAnimation(PLAYER::PLAYER_PED_ID(), "random@arrests", "kneeling_arrest_idle"); break;
		case 6:
			doAnimation(PLAYER::PLAYER_PED_ID(), "creatures@rottweiler@move", "dump_enter"); break;
		case 7:
			doAnimation(PLAYER::PLAYER_PED_ID(), "timetable@trevor@smoking_meth@base", "base"); break;

		}
		break;
#pragma endregion
#pragma region Outfit Options
	case Outfit_Options:

		addTitle("Outfit Options");
		addOption("Male Police Officer");
		addOption("Female Police Officer");
		addOption("Male Dumpster");
		addOption("Female Dumpster");
		addOption("Male Invisible");
		addOption("Female Invisible");
		addOption("Pilot");
		addOption("Ballas Member");
		addOption("Thug");
		addOption("Prostitute");
		addOption("Buff");
		addOption("Santa");
		addOption("Elf");
		addOption("Snowman");
		switch (getOption())
		{
		case 1:
			ResetAppearance();
			changeAppearance("TORSO", 0, 0);
			changeAppearance("GLASSES", 6, 1);
			changeAppearance("LEGS", 35, 0);
			changeAppearance("SHOES", 25, 0);
			changeAppearance("SPECIAL2", 58, 0);
			changeAppearance("TORSO2", 55, 0);
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, 46, 0, 0); break;
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 30, 0, 0); break;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1D073A89, 9999, 1); break;
		case 2:
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, 45, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 57, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 34, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 29, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, 64, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, 35, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 48, 0, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1D073A89, 9999, 1);
			break;
		case 3:
			ResetAppearance();
			changeAppearance("HATS", 6, 0);
			changeAppearance("TORSO", 1, 0);
			changeAppearance("LEGS", 36, 0);
			changeAppearance("SHOES", 27, 0);
			changeAppearance("SPECIAL2", 59, 1);
			changeAppearance("TORSO2", 57, 0);
			break;
		case 4:
			ResetAppearance();
			changeAppearance("HATS", 13, 0);
			changeAppearance("TORSO", 1, 0);
			changeAppearance("LEGS", 35, 0);
			changeAppearance("SHOES", 26, 0);
			changeAppearance("SPECIAL2", 36, 1);
			changeAppearance("TORSO2", 50, 0);
			break;
		case 5:
			ResetAppearance();
			changeAppearance("TORSO", 3, 0);
			changeAppearance("MASK", 52, 0);
			changeAppearance("LEGS", 11, 0);
			changeAppearance("SHOES", 13, 0);
			changeAppearance("TORSO2", 15, 0);
			break;
		case 6:
			ResetAppearance();
			changeAppearance("HATS", 0, 0);
			changeAppearance("TORSO", 8, 0);
			changeAppearance("LEGS", 13, 0);
			changeAppearance("SHOES", 12, 0);
			changeAppearance("SPECIAL2", 2, 0);
			changeAppearance("TORSO2", 0, 16);
			break;
		case 7:
			ResetAppearance();
			changeAppearance("HATS", 20, 0);
			changeAppearance("GLASSES", 6, 0);
			changeAppearance("TORSO", 16, 0);
			changeAppearance("LEGS", 30, 0);
			changeAppearance("HANDS", 39, 4);
			changeAppearance("SHOES", 24, 0);
			changeAppearance("SPECIAL2", 15, 0);
			changeAppearance("TORSO2", 48, 0);
			break;
		case 8:
			ResetAppearance();
			changeAppearance("HATS", 10, 7);
			changeAppearance("GLASSES", 17, 6);
			changeAppearance("MASK", 51, 6);
			changeAppearance("TORSO", 14, 0);
			changeAppearance("LEGS", 5, 9);
			changeAppearance("SHOES", 9, 5);
			changeAppearance("SPECIAL2", 23, 0);
			changeAppearance("TORSO2", 7, 9);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1B06D571, 9999, 5); break;
		case 9:
			ResetAppearance();
			changeAppearance("HATS", 46, 1);
			changeAppearance("GLASSES", 17, 6);
			changeAppearance("MASK", 51, 7);
			changeAppearance("TORSO", 22, 0);
			changeAppearance("LEGS", 7, 0);
			changeAppearance("HANDS", 44, 0);
			changeAppearance("SHOES", 12, 6);
			changeAppearance("SPECIAL2", 15, 0);
			changeAppearance("TORSO2", 14, 7);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x1B06D571, 9999, 5); break;
		case 10:
			ResetAppearance();
			changeAppearance("TORSO", 15, 0);
			changeAppearance("LEGS", 15, 0);
			changeAppearance("SHOES", 14, 0);
			changeAppearance("SPECIAL1", 2, 0);
			changeAppearance("SPECIAL2", 2, 0);
			changeAppearance("TORSO2", 0, 16);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x92A27487, 9999, 1); break;
		case 11:
			ResetAppearance();
			changeAppearance("HATS", 40, 0);
			changeAppearance("MASK", 28, 0);
			changeAppearance("TORSO", 44, 0);
			changeAppearance("LEGS", 34, 0);
			changeAppearance("HANDS", 45, 0);
			changeAppearance("SHOES", 25, 0);
			changeAppearance("SPECIAL2", 56, 1);
			changeAppearance("TORSO2", 53, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x0A3D4D34, 9999, 1); break;
		case 12:
			ResetAppearance();
			changeAppearance("MASK", 8, 0);
			changeAppearance("TORSO", 12, 0);
			changeAppearance("LEGS", 19, 0);
			changeAppearance("SHOES", 4, 4);
			changeAppearance("SPECIAL1", 10, 0);
			changeAppearance("SPECIAL2", 21, 2);
			changeAppearance("TORSO2", 19, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x3656C8C1, 9999, 1); break;
		case 13:
			ResetAppearance();
			changeAppearance("MASK", 34, 0);
			changeAppearance("TORSO", 4, 0);
			changeAppearance("LEGS", 19, 1);
			changeAppearance("SHOES", 22, 1);
			changeAppearance("SPECIAL1", 18, 0);
			changeAppearance("SPECIAL2", 28, 8);
			changeAppearance("TORSO2", 19, 1);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x3656C8C1, 9999, 1); break;
		case 14:
			ResetAppearance();
			changeAppearance("MASK", 10, 0);
			changeAppearance("TORSO", 12, 0);
			changeAppearance("LEGS", 20, 0);
			changeAppearance("SHOES", 18, 1);
			changeAppearance("SPECIAL1", 24, 2);
			changeAppearance("SPECIAL2", 22, 4);
			changeAppearance("TORSO2", 25, 7);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 0x3656C8C1, 9999, 1); break;
		}
		break;
#pragma endregion
#pragma region Component Options
	case Component_Options:

		addTitle("Component Options");
		addOption("Reset Appearance");
		addOption("Yellow Dev T-Shirt");
		addOption("Blue Dev T-Shirt");
		addOption("Black Dev T-Shirt");
		addIntOption("Variation Option", &VariationOption, 0, 20, true);
		addIntOption("Hats", &HatsOptions, 0, 54, true);
		addIntOption("Glasses", &GlassesOptions, 0, 24, true);
		addIntOption("Ears", &EarsOptions, 0, 2, true);
		addIntOption("Face", &FaceOptions, 0, 100, true);
		addIntOption("Mask", &MaskOptions, 0, 58, true);
		addIntOption("Hair", &HairOptions, 0, 24, true);
		addIntOption("Torso", &TorsoOptions, 0, 100, true);
		addIntOption("Legs", &LegsOptions, 0, 44, true);
		addIntOption("Hands", &HandsOptions, 0, 51, true);
		addIntOption("Shoes", &ShoesOptions, 0, 31, true);
		addIntOption("Special", &SpecialOptions, 0, 73, true);
		addIntOption("Special 2", &Special2Options, 0, 56, true);
		addIntOption("Special 3", &Special3Options, 0, 13, true);
		addIntOption("Texture", &TextureOptions, 0, 10, true);
		addIntOption("Torso 2", &Torso2Options, 0, 71, true);
		switch (getOption())
		{
		case 1:
			PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
			PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0);
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, 0, 0, 0);
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 12, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 13, 0, 0, 0);
			break;
		case 2:
			PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
			PED::_0x70559AC7(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_001")); break;
		case 3:
			PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
			PED::_0x70559AC7(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_002")); break;
		case 4:
			PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
			PED::_0x70559AC7(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_000")); break;
		case 6:
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, HatsOptions, VariationOption, 0); break;
		case 7:
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, GlassesOptions, VariationOption, 0); break;
		case 8:
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, EarsOptions, VariationOption, 0); break;
		case 9:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, FaceOptions, VariationOption, 0); break;
		case 10:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, MaskOptions, VariationOption, 0); break;
		case 11:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, HairOptions, VariationOption, 0); break;
		case 12:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, TorsoOptions, VariationOption, 0); break;
		case 13:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, LegsOptions, VariationOption, 0); break;
		case 14:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, HandsOptions, VariationOption, 0); break;
		case 15:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, ShoesOptions, VariationOption, 0); break;
		case 16:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, SpecialOptions, VariationOption, 0); break;
		case 17:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, Special2Options, VariationOption, 0); break;
		case 18:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, Special3Options, VariationOption, 0); break;
		case 19:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, TextureOptions, VariationOption, 0); break;
		case 20:
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, Torso2Options, VariationOption, 0); break;
		}
		break;
#pragma endregion
#pragma region Wheather Options
	case Weather_Options:

		addTitle("Weather Options");
		addOption("Blizzard");
		addOption("Clear");
		addOption("Clearing");
		addOption("Clouds");
		addOption("Extra Sunny");
		addOption("Foggy");
		addOption("Hulk Weather");
		addOption("Overcast");
		addOption("Rain");
		addOption("Smog");
		addOption("Snow");
		addOption("Snow Light");
		addOption("Thunder");
		addOption("XMas Snow");
		addIntOption("Hour", &AddOneHour, 0, 23, true);
		addBoolOption("Toggle XMas", Toggle_XMas);
		switch (getOption())
		{
		case 1:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("BLIZZARD");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("BLIZZARD");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("BLIZZARD");
			GAMEPLAY::SET_OVERRIDE_WEATHER("BLIZZARD"); break;
		case 2:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLEAR");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEAR");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
			GAMEPLAY::SET_OVERRIDE_WEATHER("CLEAR"); break;
		case 3:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLEARING");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEARING");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEARING");
			GAMEPLAY::SET_OVERRIDE_WEATHER("CLEARING"); break;
		case 4:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLOUDS");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLOUDS");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("CLOUDS");
			GAMEPLAY::SET_OVERRIDE_WEATHER("CLOUDS"); break;
		case 5:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("EXTRASUNNY");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("EXTRASUNNY");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("EXTRASUNNY");
			GAMEPLAY::SET_OVERRIDE_WEATHER("EXTRASUNNY"); break;
		case 6:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("FOGGY");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("FOGGY");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("FOGGY");
			GAMEPLAY::SET_OVERRIDE_WEATHER("FOGGY"); break;
		case 7:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("NEUTRAL");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("NEUTRAL");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("NEUTRAL");
			GAMEPLAY::SET_OVERRIDE_WEATHER("NEUTRAL"); break;
		case 8:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("OVERCAST");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("OVERCAST");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("OVERCAST");
			GAMEPLAY::SET_OVERRIDE_WEATHER("OVERCAST"); break;
		case 9:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("RAIN");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("RAIN");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("RAIN");
			GAMEPLAY::SET_OVERRIDE_WEATHER("RAIN"); break;
		case 10:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("SMOG");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SMOG");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SMOG");
			GAMEPLAY::SET_OVERRIDE_WEATHER("SMOG"); break;
		case 11:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("SNOW");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOW");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOW");
			GAMEPLAY::SET_OVERRIDE_WEATHER("SNOW"); break;
		case 12:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("SNOWLIGHT");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOWLIGHT");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("SNOWLIGHT");
			GAMEPLAY::SET_OVERRIDE_WEATHER("SNOWLIGHT"); break;
		case 13:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("THUNDER");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("THUNDER");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("THUNDER");
			GAMEPLAY::SET_OVERRIDE_WEATHER("THUNDER"); break;
		case 14:
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("XMAS");
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS");
			GAMEPLAY::SET_WEATHER_TYPE_NOW("XMAS");
			GAMEPLAY::SET_OVERRIDE_WEATHER("XMAS"); break;
		case 15:
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(AddOneHour, 0, 0); break;
		case 16: Toggle_XMas = !Toggle_XMas; break;
		}
		break;
#pragma endregion
#pragma region Map Optios
	case Map_Options:

		addTitle("Map Options");
		addOption("Load AirCraft Carrier"); //1
		addOption("Remove AirCraft Carrier"); //2
		addOption("Load Yacht"); //3
		addOption("Remove Yacht"); //4
		addOption("Load RedCarpet"); //5
		addOption("Remove RedCarpet"); //6
		addOption("Load North Yankton"); //7
		addOption("Remove North Yankton"); //8
		addOption("Load UFO"); //9
		addOption("Remove UFO"); //10
		addOption("Load Food"); //11
		addOption("Remove Food"); //12
		addOption("Load Burger Shot"); //13
		addOption("Remove Burger Shot"); //14
		addOption("Load Layer"); //15
		addOption("Remove Layer"); //16
		addOption("Load Destroyed Hospital"); //17
		addOption("Remove Destroyed Hospital"); //18
		switch (getOption())
		{
		case 1:
			STREAMING::REQUEST_IPL("hei_carrier");
			STREAMING::REQUEST_IPL("hei_carrier_int1");
			STREAMING::REQUEST_IPL("hei_carrier_int2");
			STREAMING::REQUEST_IPL("hei_carrier_int3");
			STREAMING::REQUEST_IPL("hei_carrier_int4");
			STREAMING::REQUEST_IPL("hei_carrier_int5");
			STREAMING::REQUEST_IPL("hei_carrier_int6");
			STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
			STREAMING::REQUEST_IPL("hei_carrier_LODLights");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid2;
				vehid2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 3034.984, -4631.044, 15.26225 };
				ENTITY::SET_ENTITY_COORDS(vehid2, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 3034.984, -4631.044, 15.26225 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 2:
			STREAMING::REMOVE_IPL("hei_carrier");
			STREAMING::REMOVE_IPL("hei_carrier_int1");
			STREAMING::REMOVE_IPL("hei_carrier_int2");
			STREAMING::REMOVE_IPL("hei_carrier_int3");
			STREAMING::REMOVE_IPL("hei_carrier_int4");
			STREAMING::REMOVE_IPL("hei_carrier_int5");
			STREAMING::REMOVE_IPL("hei_carrier_int6");
			STREAMING::REMOVE_IPL("hei_carrier_DistantLights");
			STREAMING::REMOVE_IPL("hei_carrier_LODLights");
			break;
		case 3:
			STREAMING::REQUEST_IPL("smboat");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid;
				vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { -2044.123f, -1031.369f, 12.0f };
				ENTITY::SET_ENTITY_COORDS(vehid, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { -2044.123f, -1031.369f, 12.0f };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 4: STREAMING::REMOVE_IPL("smboat"); break;
		case 5:
			STREAMING::REQUEST_IPL("redCarpet");
			STREAMING::REQUEST_IPL("shr_int");
			STREAMING::REQUEST_IPL("SpaceInterior");
			STREAMING::REQUEST_IPL("CJ_IOABoat");
			STREAMING::REQUEST_IPL("cs3_07_mpgates");
			STREAMING::REQUEST_IPL("V_Michael_FameShame");
			STREAMING::REQUEST_IPL("V_Michael_JewelHeist");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid3;
				vehid3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 290.924164, 175.247375, 104.150650 };
				ENTITY::SET_ENTITY_COORDS(vehid3, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 290.924164, 175.247375, 104.150650 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 6:
			STREAMING::REMOVE_IPL("redCarpet");
			STREAMING::REMOVE_IPL("shr_int");
			STREAMING::REMOVE_IPL("SpaceInterior");
			STREAMING::REMOVE_IPL("CJ_IOABoat");
			STREAMING::REMOVE_IPL("cs3_07_mpgates");
			STREAMING::REMOVE_IPL("V_Michael_FameShame");
			STREAMING::REMOVE_IPL("V_Michael_JewelHeist");
			break;
		case 7:
			STREAMING::REQUEST_IPL("prologue01");
			STREAMING::REQUEST_IPL("prologue01c");
			STREAMING::REQUEST_IPL("prologue01d");
			STREAMING::REQUEST_IPL("prologue01e");
			STREAMING::REQUEST_IPL("prologue01f");
			STREAMING::REQUEST_IPL("prologue01g");
			STREAMING::REQUEST_IPL("prologue01h");
			STREAMING::REQUEST_IPL("prologue01i");
			STREAMING::REQUEST_IPL("prologue01j");
			STREAMING::REQUEST_IPL("prologue01k");
			STREAMING::REQUEST_IPL("prologue01z");
			STREAMING::REQUEST_IPL("prologue02");
			STREAMING::REQUEST_IPL("prologue03");
			STREAMING::REQUEST_IPL("prologue03b");
			STREAMING::REQUEST_IPL("prologue04");
			STREAMING::REQUEST_IPL("prologue04b");
			STREAMING::REQUEST_IPL("prologue05");
			STREAMING::REQUEST_IPL("prologue05b");
			STREAMING::REQUEST_IPL("prologue06");
			STREAMING::REQUEST_IPL("prologue06b");
			STREAMING::REQUEST_IPL("prologuerd");
			STREAMING::REQUEST_IPL("prologuerdb");
			STREAMING::REQUEST_IPL("prologue_m2_door");
			STREAMING::REQUEST_IPL("prologue_LODLights");
			STREAMING::REQUEST_IPL("prologue_DistantLights");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid4;
				vehid4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 3217.6970214844, -4834.826171875, 111.81479644775 };
				ENTITY::SET_ENTITY_COORDS(vehid4, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 3217.6970214844, -4834.826171875, 111.81479644775 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			} break;
		case 8:
			STREAMING::REMOVE_IPL("prologue01");
			STREAMING::REMOVE_IPL("prologue01c");
			STREAMING::REMOVE_IPL("prologue01d");
			STREAMING::REMOVE_IPL("prologue01e");
			STREAMING::REMOVE_IPL("prologue01f");
			STREAMING::REMOVE_IPL("prologue01g");
			STREAMING::REMOVE_IPL("prologue01h");
			STREAMING::REMOVE_IPL("prologue01i");
			STREAMING::REMOVE_IPL("prologue01j");
			STREAMING::REMOVE_IPL("prologue01k");
			STREAMING::REMOVE_IPL("prologue01z");
			STREAMING::REMOVE_IPL("prologue02");
			STREAMING::REMOVE_IPL("prologue03");
			STREAMING::REMOVE_IPL("prologue03b");
			STREAMING::REMOVE_IPL("prologue04");
			STREAMING::REMOVE_IPL("prologue04b");
			STREAMING::REMOVE_IPL("prologue05");
			STREAMING::REMOVE_IPL("prologue05b");
			STREAMING::REMOVE_IPL("prologue06");
			STREAMING::REMOVE_IPL("prologue06b");
			STREAMING::REMOVE_IPL("prologuerd");
			STREAMING::REMOVE_IPL("prologuerdb");
			STREAMING::REMOVE_IPL("prologue_m2_door");
			STREAMING::REMOVE_IPL("prologue_LODLights");
			STREAMING::REMOVE_IPL("prologue_DistantLights");
			break;
		case 9:
			STREAMING::REQUEST_IPL("UFO");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid5;
				vehid5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { -2051.99463f, 3237.05835f, 1456.97021f };
				ENTITY::SET_ENTITY_COORDS(vehid5, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { -2051.99463f, 3237.05835f, 1456.97021f };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 10: STREAMING::REMOVE_IPL("UFO"); break;
		case 11:
			STREAMING::REQUEST_IPL("CS1_02_cf_onmission1");
			STREAMING::REQUEST_IPL("CS1_02_cf_onmission2");
			STREAMING::REQUEST_IPL("CS1_02_cf_onmission3");
			STREAMING::REQUEST_IPL("CS1_02_cf_onmission4");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid5;
				vehid5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { -146.3837f, 6161.5f, 30.2062f };
				ENTITY::SET_ENTITY_COORDS(vehid5, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { -146.3837f, 6161.5f, 30.2062f };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 12:
			STREAMING::REMOVE_IPL("CS1_02_cf_onmission1");
			STREAMING::REMOVE_IPL("CS1_02_cf_onmission2");
			STREAMING::REMOVE_IPL("CS1_02_cf_onmission3");
			STREAMING::REMOVE_IPL("CS1_02_cf_onmission4");
			break;
		case 13:
			STREAMING::REQUEST_IPL("Coroner_Int_on");
			STREAMING::REQUEST_IPL("Coroner_Int_off");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid5;
				vehid5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 243.7397, -1375.94031, 39.534317 };
				ENTITY::SET_ENTITY_COORDS(vehid5, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 243.7397, -1375.94031, 39.534317 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 14: STREAMING::REMOVE_IPL("Coroner_Int_on");
			STREAMING::REMOVE_IPL("Coroner_Int_off"); break;
		case 15:
			STREAMING::REQUEST_IPL("farmint");
			STREAMING::REQUEST_IPL("farm_props");
			STREAMING::REQUEST_IPL("farm");
			STREAMING::REQUEST_IPL("farm_burnt");
			STREAMING::REQUEST_IPL("farm_burnt_props");
			STREAMING::REQUEST_IPL("farmint_cap");
			STREAMING::REQUEST_IPL("farmint");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid5;
				vehid5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 2439.892, 4969.99268, 47.534317 };
				ENTITY::SET_ENTITY_COORDS(vehid5, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 2439.892, 4969.99268, 47.534317 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 16:
			STREAMING::REMOVE_IPL("farmint");
			STREAMING::REMOVE_IPL("farm_props");
			STREAMING::REMOVE_IPL("farmint");
			STREAMING::REMOVE_IPL("farm_props");
			STREAMING::REMOVE_IPL("farm");
			STREAMING::REMOVE_IPL("farm_burnt");
			STREAMING::REMOVE_IPL("farm_burnt_props");
			STREAMING::REMOVE_IPL("farmint_cap");
			STREAMING::REMOVE_IPL("farmint");
			break;
		case 17:
			STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
			STREAMING::REQUEST_IPL("RC12B_Destroyed");
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int vehid5;
				vehid5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 coords = { 316.8073, -593.3502, 43.29187 };
				ENTITY::SET_ENTITY_COORDS(vehid5, coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			else
			{
				Vector3 coords = { 316.8073, -593.3502, 43.29187 };
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
			}
			break;
		case 18:
			STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
			STREAMING::REMOVE_IPL("RC12B_Destroyed");
			break;
		}
		break;
#pragma endregion
#pragma region Ped Spawner
	case Ped_Spawner:

		addTitle("Ped Spawner");
		AddOptionPedSpawner("Beach Girl", 808859815);
		AddOptionPedSpawner("Alien", 0x64611296);
		AddOptionPedSpawner("Beach Bae", 0x9CF26183);
		AddOptionPedSpawner("Stripper", 0x2970A494);
		AddOptionPedSpawner("Pilot", -163714847);
		AddOptionPedSpawner("Pissed Guy", 0x9194CE03);
		AddOptionPedSpawner("Gunman", 0xB881AEE);
		AddOptionPedSpawner("Prisoner", 0xB1BB9B59);
		AddOptionPedSpawner("SWAT", 0x8D8F1B10);
		AddOptionPedSpawner("Clown", 0x4498DDE);
		AddOptionPedSpawner("Bugstars", 0x48114518);
		AddOptionPedSpawner("Dildo Dipper", 0x5442C66B);
		AddOptionPedSpawner("Fat Lady", 0xB5CF80E4);
		AddOptionPedSpawner("Hobo", 0x55446010);
		AddOptionPedSpawner("Astronaut", 0xE7B31432);
		AddOptionPedSpawner("Firefighter", -1229853272);
		AddOptionPedSpawner("Johhny", 0x87CA80AE);
		AddOptionPedSpawner("FBI Suit", 0x3AE4A33B);
		AddOptionPedSpawner("Zombie", 0xAC4B4506);
		AddOptionPedSpawner("Buff Dude", 0xDA116E7E);
		AddOptionPedSpawner("Impotenet Rage", 880829941);
		AddOptionPedSpawner("Franklin", 0x9B22DBAF);
		AddOptionPedSpawner("Trevor", 0x9B810FA2);
		AddOptionPedSpawner("Micheal", 0xD7114C9);
		AddOptionPedSpawner("Dude With Pants Down", 2109968527);
		AddOptionPedSpawner("Hoe With Skirt Up", 602513566);
		AddOptionPedSpawner("Slenderman", 0x92991b72);
		AddOptionPedSpawner("Bigfoot", 1641334641);
		AddOptionPedSpawner("The Guy Who Isnt Real", 3459037009);
		AddOptionPedSpawner("Space Ranger", 1011059922);
		AddOptionPedSpawner("Drunk Mexican", 3367706194);
		AddOptionPedSpawner("Classy Stripper", -2126242959);
		AddOptionPedSpawner("Gang Member", -1031795266);
		AddOptionPedSpawner("Space Monkey", -598109171);
		AddOptionPedSpawner("Hunter", -837606178);
		AddOptionPedSpawner("Lester", 1302784073);
		AddOptionPedSpawner("Mark", -304305299);
		AddOptionPedSpawner("Wade", -1835459726);
		AddOptionPedSpawner("Porn Dudes", 793443893);
		AddOptionPedSpawner("Jimmy", 1459905209);
		AddOptionPedSpawner("Lamar", 1706635382);
		AddOptionPedSpawner("Mrs Phillips", 946007720);
		AddOptionPedSpawner("Muscl Beach Dude", -920443780);
		AddOptionPedSpawner("Dirt Bike Guy", 1694362237);
		AddOptionPedSpawner("Dirt Bike Guy 2", 1694362237);
		AddOptionPedSpawner("Dirt Bike Guy 3", 2007797722);
		AddOptionPedSpawner("Priest", 1681385341);
		AddOptionPedSpawner("Mime", 1021093698);
		AddOptionPedSpawner("Ron", -1124046095);
		AddOptionPedSpawner("Office Lady", -1106743555);
		AddOptionPedSpawner("Tonya", -892841148);
		AddOptionPedSpawner("Maude", 1005070462);
		AddOptionPedSpawner("Marnie", 411185872);
		AddOptionPedSpawner("Old Lady / Black Lady", -1606864033);
		AddOptionPedSpawner("Nice Chick With Tits", -96953009);
		AddOptionPedSpawner("Nigel", -927525251);
		AddOptionPedSpawner("Tanisha", 226559113);
		AddOptionPedSpawner("Russian Drunk", 1024089777);
		AddOptionPedSpawner("Bartender", 2014052797);
		AddOptionPedSpawner("Migrant Female", -715445259);
		AddOptionPedSpawner("Migrant Male", -317922106);
		AddOptionPedSpawner("Bouncer", -1613485779);
		AddOptionPedSpawner("Hair Dresser", 1099825042);
		AddOptionPedSpawner("Scientist", 1092080539);
		AddOptionPedSpawner("Misty", -785842275);
		AddOptionPedSpawner("Female Fatbla ", -88831029);
		AddOptionPedSpawner("Female Fatcult", -1244692252);
		AddOptionPedSpawner("Female Fatwhite", 951767867);
		AddOptionPedSpawner("Female Ktown", 1388848350);
		AddOptionPedSpawner("Female Ktown 2", 1090617681);
		AddOptionPedSpawner("Female Prol Host", 379310561);
		AddOptionPedSpawner("Female Salton", -569505431);
		AddOptionPedSpawner("Female Skidrow", -1332260293);
		AddOptionPedSpawner("Female Soucent MC", -840346158);
		AddOptionPedSpawner("Female Soucent", 1951946145);
		AddOptionPedSpawner("Female Soucent 2", -215821512);
		AddOptionPedSpawner("Female Tourist", 1347814329);
		AddOptionPedSpawner("Female Tramp Beach", -1935621530);
		AddOptionPedSpawner("Female Tramp", 1224306523);
		AddOptionPedSpawner("Female Genstreet", 1640504453);
		AddOptionPedSpawner("Female Indian", -1160266880);
		AddOptionPedSpawner("Female Ktown", 1204772502);
		AddOptionPedSpawner("Female Salton", -855671414);
		AddOptionPedSpawner("Female Soucent", 1039800368);
		AddOptionPedSpawner("Female Soucent 2", -1519524074);
		AddOptionPedSpawner("Female Beach", -945854168);
		AddOptionPedSpawner("Female Bevhills", 1146800212);
		AddOptionPedSpawner("Female Bevhills 2", 1546450936);
		AddOptionPedSpawner("Female Bevhills 3", 549978415);
		AddOptionPedSpawner("Female Bevhills 4", 920595805);
		AddOptionPedSpawner("Female Business", 664399832);
		AddOptionPedSpawner("Female Business 2", 826475330);
		AddOptionPedSpawner("Female Business 3", -1366884940);
		AddOptionPedSpawner("Female Business 4", -1211756494);
		AddOptionPedSpawner("Female Eastsa", -173013091);
		AddOptionPedSpawner("Female Eastsa 2", 70821038);
		AddOptionPedSpawner("Female Eastsa 3", 1371553700);
		AddOptionPedSpawner("Female Epsilon", 1755064960);
		AddOptionPedSpawner("Female Fitness", 1165780219);
		AddOptionPedSpawner("Female Fitness 2", 331645324);
		AddOptionPedSpawner("Female Genhot", 793439294);
		AddOptionPedSpawner("Female Golfer", 2111372120);
		AddOptionPedSpawner("Female Hiker", 813893651);
		AddOptionPedSpawner("Female Hippie", 343259175);
		AddOptionPedSpawner("Female Hipster", -21092220985);
		AddOptionPedSpawner("Female Hipster 2", -1745486195);
		AddOptionPedSpawner("Female Hipster 3", -1514497514);
		AddOptionPedSpawner("Female Hipster 4", 429425116);
		AddOptionPedSpawner("Female Indian", 153984193);
		AddOptionPedSpawner("Female Juggalo", -619494093);
		AddOptionPedSpawner("Female Runner", -951490775);
		AddOptionPedSpawner("Female Rur Meth", 1064866854);
		AddOptionPedSpawner("Female Scdressy", -614546432);
		AddOptionPedSpawner("Female Skater", 1767892582);
		AddOptionPedSpawner("Female Soucent", 744758650);
		AddOptionPedSpawner("Female Soucent 2", 1519319503);
		AddOptionPedSpawner("Female Soucent 3", -2018356203);
		AddOptionPedSpawner("Female Tennis", 1426880966);
		AddOptionPedSpawner("Female Topless", -1661836925);
		AddOptionPedSpawner("Female Tourist", 1446741360);
		AddOptionPedSpawner("Female Tourist", -1859912896);
		AddOptionPedSpawner("Female Vinewood", 435429221);
		AddOptionPedSpawner("Female Vinewood 2", -625565461);
		AddOptionPedSpawner("Female Vinewood 3", 933092024);
		AddOptionPedSpawner("Female Vinewood 4", -85696186);
		AddOptionPedSpawner("Female Yoga 1", -1004861906);
		AddOptionPedSpawner("Male Acult ", 1413662315);
		AddOptionPedSpawner("Male Afriamer", -781039234);
		AddOptionPedSpawner("Male Beach", 1077785853);
		AddOptionPedSpawner("Male Beach 2", 2021631368);
		AddOptionPedSpawner("Male Bevhills", 1423699487);
		AddOptionPedSpawner("Male Bevhills 2", 1068876755);
		AddOptionPedSpawner("Male Business", 2120901815);
		AddOptionPedSpawner("Male Eastsa", -106498753);
		AddOptionPedSpawner("Male Eastsa 2", 131961260);
		AddOptionPedSpawner("Male Farmer", -1806291497);
		AddOptionPedSpawner("Male Fatlatin", 1641152947);
		AddOptionPedSpawner("Male Genfat", 115168927);
		AddOptionPedSpawner("Male Genfat 2", 330231874);
		AddOptionPedSpawner("Male Golfer", -1444213182);
		AddOptionPedSpawner("Male Has Jew", 1809430156);
		AddOptionPedSpawner("Male Hillbilly", 1822107721);
		AddOptionPedSpawner("Male Hillbilly 2", 2064532783);
		AddOptionPedSpawner("Male Indian", -573920724);
		AddOptionPedSpawner("Male Ktown", -782401935);
		AddOptionPedSpawner("Male Malibu", 803106487);
		AddOptionPedSpawner("Male Mexcntry", -578715987);
		AddOptionPedSpawner("Male Mexican Labor", -1302522190);
		AddOptionPedSpawner("Male Og Boss", 1746653202);
		AddOptionPedSpawner("Male Papa Razzi", -322270187);
		AddOptionPedSpawner("Male Polynesian", -1445349730);
		AddOptionPedSpawner("Male Prol Host", -1760377969);
		AddOptionPedSpawner("Male Rur meth", 1001210244);
		AddOptionPedSpawner("Male Salton", 1328415626);
		AddOptionPedSpawner("Male Salton 2", 1626646295);
		AddOptionPedSpawner("Male Salton 3", -1299428795);
		AddOptionPedSpawner("Male Salton 4", -1773858377);
		AddOptionPedSpawner("Male Skater", -640198516);
		AddOptionPedSpawner("Male Skidrow", 32417469);
		AddOptionPedSpawner("Male Socenlat", 193817059);
		AddOptionPedSpawner("Male Soucent", 1750583735);
		AddOptionPedSpawner("Male Soucent 2", -1620232223);
		AddOptionPedSpawner("Male Soucent 3", -1948675910);
		AddOptionPedSpawner("Male Soucent 4", -1023672578);
		AddOptionPedSpawner("Male Stlat 2", -1029146878);
		AddOptionPedSpawner("Male Tennis", 1416254276);
		AddOptionPedSpawner("Male Tourist", -929103484);
		AddOptionPedSpawner("Male Tramp beach", 1404403376);
		AddOptionPedSpawner("Male Tramp", 516505552);
		AddOptionPedSpawner("Male Tranvest", -521758348);
		AddOptionPedSpawner("Male Tranvest 2", -150026812);
		AddOptionPedSpawner("Male Acult", 1430544400);
		AddOptionPedSpawner("Male Acult 2", 1268862154);
		AddOptionPedSpawner("Male Beach", -2077764712);
		AddOptionPedSpawner("Male Genstreet", -1386944600);
		AddOptionPedSpawner("Male Ktown", 355916122);
		AddOptionPedSpawner("Male Salton", 539004493);
		AddOptionPedSpawner("Male Soucent", 718836251);
		AddOptionPedSpawner("Male Soucent 2", 1082572151);
		AddOptionPedSpawner("Male Soucent 3", 238213328);
		AddOptionPedSpawner("Male Tramp", 390939205);
		AddOptionPedSpawner("Male Acult", -1251702741);
		AddOptionPedSpawner("Male Acult 2", -2132435154);
		AddOptionPedSpawner("Male Beachvesp", 2114544056);
		AddOptionPedSpawner("Male Beachvesp 2", -900269486);
		AddOptionPedSpawner("Male Beach", -771835772);
		AddOptionPedSpawner("Male Beach 2", 600300561);
		AddOptionPedSpawner("Male Beach 3", -408329255);
		AddOptionPedSpawner("Male Bevhills", 1982350912);
		AddOptionPedSpawner("Male Bevhills 2", 1720428295);
		AddOptionPedSpawner("Male Break dancer ", 933205398);
		AddOptionPedSpawner("Male Busicas", -1697435671);
		AddOptionPedSpawner("Male Business", -912318012);
		AddOptionPedSpawner("Male Business 2", -1280051738);
		AddOptionPedSpawner("Male Business 3", -1589423867);
		AddOptionPedSpawner("Male Cyclist", -37334073);
		AddOptionPedSpawner("Male Dhill", -12678997);
		AddOptionPedSpawner("Male Downtown", 766375082);
		AddOptionPedSpawner("Male Eastsa", -1538846349);
		AddOptionPedSpawner("Male Eastsa 2", 377976310);
		AddOptionPedSpawner("Male Epsilon", 2010389054);
		AddOptionPedSpawner("Male Epsilon 2", -1434255461);
		AddOptionPedSpawner("Male Gay", -775102410);
		AddOptionPedSpawner("Male Gay 2", -1519253631);
		AddOptionPedSpawner("Male Genstreet", -1736970383);
		AddOptionPedSpawner("Male Genstreet 2", 891398354);
		AddOptionPedSpawner("Male Golfer", -685776591);
		AddOptionPedSpawner("Male Has Jew", -512913663);
		AddOptionPedSpawner("Male Hiker", 1358380044);
		AddOptionPedSpawner("Male Hippy", 2097407511);
		AddOptionPedSpawner("Male Hipster", 587703123);
		AddOptionPedSpawner("Male Hipster 2", 349505262);
		AddOptionPedSpawner("Male Hipster 3", 1312913862);
		AddOptionPedSpawner("Male Indian", 706935758);
		AddOptionPedSpawner("Male Jetski", 767028979);
		AddOptionPedSpawner("Male Juggalo", -1849016788);
		AddOptionPedSpawner("Male Ktown", 452351020);
		AddOptionPedSpawner("Male Ktown 2", 696250687);
		AddOptionPedSpawner("Male Latino", 321657486);
		AddOptionPedSpawner("Male Meth Head", 1768677545);
		AddOptionPedSpawner("Male Mexican Thug", 810804565);
		AddOptionPedSpawner("Male Musclbeach", 1264920838);
		AddOptionPedSpawner("Male Musclbeach 2", -920443780);
		AddOptionPedSpawner("Male Polynesian", -2088436577);
		AddOptionPedSpawner("Male Roadcyc", -178150202);
		AddOptionPedSpawner("Male Runner", 623927022);
		AddOptionPedSpawner("Male Runner 2", -2076336881);
		AddOptionPedSpawner("Male Salton", -681546704);
		AddOptionPedSpawner("Male Skater", -1044093321);
		AddOptionPedSpawner("Male Skater 2", -1342520604);
		AddOptionPedSpawner("Male Soucent", -417940021);
		AddOptionPedSpawner("Male Soucent 2", -1398552374);
		AddOptionPedSpawner("Male Soucent 3", -1007618204);
		AddOptionPedSpawner("Male Soucent 4", -1976105999);
		AddOptionPedSpawner("Male Stbla", -812470807);
		AddOptionPedSpawner("Male Stbla 2", -1731772337);
		AddOptionPedSpawner("Male Stlat", -2039163396);
		AddOptionPedSpawner("Male Stwhi", 605602864);
		AddOptionPedSpawner("Male Stwhi 2", 919005580);
		AddOptionPedSpawner("Male Sunbathe", -1222037748);
		AddOptionPedSpawner("Male Surfer", -356333586);
		AddOptionPedSpawner("Male Vindouche", -1047300121);
		AddOptionPedSpawner("Male Vinewood", 1264851357);
		AddOptionPedSpawner("Male Vinewood 2", 1561705728);
		AddOptionPedSpawner("Male Vinewood 3", 534725268);
		AddOptionPedSpawner("Male Vinewood 4", 835315305);
		AddOptionPedSpawner("Male Yoga", -1425378987);
		AddOptionPedSpawner("Abigail", -1988720319);
		AddOptionPedSpawner("Anita", 117698822);
		AddOptionPedSpawner("Anton", -1513650250);
		AddOptionPedSpawner("Ballas Og", -1410400252);
		AddOptionPedSpawner("Bride", -2101379423);
		AddOptionPedSpawner("Burger Drug", -1931689897);
		AddOptionPedSpawner("Chines Goon", -1463670378);
		AddOptionPedSpawner("Cletus", -890640939);
		AddOptionPedSpawner("Cop", -1699520669);
		AddOptionPedSpawner("Customer", -1538297973);
		AddOptionPedSpawner("Denise Friend", -1249041111);
		AddOptionPedSpawner("Janitor", -1040164288);
		AddOptionPedSpawner("Maude", -1127975477);
		AddOptionPedSpawner("Merry Weather", 1631478380);
		AddOptionPedSpawner("Ortega", -1059388209);
		AddOptionPedSpawner("Oscar", -199280229);
		AddOptionPedSpawner("Prologue Driver", -267695653);
		AddOptionPedSpawner("Prolsec", 2141384740);
		AddOptionPedSpawner("Hipster", 569740212);
		AddOptionPedSpawner("Marine", 1634506681);
		AddOptionPedSpawner("Mexican", -162605104);
		AddOptionPedSpawner("Reporter", 776079908);
		AddOptionPedSpawner("Roccopelosi", -1436281204);
		AddOptionPedSpawner("Stripper", -1360365899);
		AddOptionPedSpawner("Traffic Warden", -567724045);
		AddOptionPedSpawner("Female Ballas", 361513884);
		AddOptionPedSpawner("Female Families", 1309468115);
		AddOptionPedSpawner("Female Lost", -44746786);
		AddOptionPedSpawner("Female Vagos", 1520708641);
		AddOptionPedSpawner("Male Arm Boss", -236444766);
		AddOptionPedSpawner("Male Arm Goon", -39239064);
		AddOptionPedSpawner("Male Arm Lieut", -412008429);
		AddOptionPedSpawner("Male Chem Work", -166363761);
		AddOptionPedSpawner("Male Chines Boss", -1176698112);
		AddOptionPedSpawner("Male Chines Cold", 275618457);
		AddOptionPedSpawner("Male Chines Goon", 2119136831);
		AddOptionPedSpawner("Male Chines Goon 2", -9308122);
		AddOptionPedSpawner("Male Korean Boss", 891945583);
		AddOptionPedSpawner("Male Mexican Boss", 1466037421);
		AddOptionPedSpawner("Male Mexican Boss 2", 1226102803);
		AddOptionPedSpawner("Male Arm Goon 2", -984709238);
		AddOptionPedSpawner("Male Azteca", 1752208920);
		AddOptionPedSpawner("Male Balla East", -198252413);
		AddOptionPedSpawner("Male Balla Orig", 588969535);
		AddOptionPedSpawner("Male Ballas Out", 599294057);
		AddOptionPedSpawner("Male Famca", -398748745);
		AddOptionPedSpawner("Male Famdnf", -613248456);
		AddOptionPedSpawner("Male Famfor", -2077218039);
		AddOptionPedSpawner("Male Korean", 611648169);
		AddOptionPedSpawner("Male Korean 2", -1880237687);
		AddOptionPedSpawner("Male Korean Lieut", 2093736314);
		AddOptionPedSpawner("Male Lost", 1330042375);
		AddOptionPedSpawner("Male Lost 2", 1032073858);
		AddOptionPedSpawner("Male Lost 3", 850468060);
		AddOptionPedSpawner("Male Mexican Gang", -1109568186);
		AddOptionPedSpawner("Male Mexicangoon", 653210662);
		AddOptionPedSpawner("Male Mexicangoon 2", 832784782);
		AddOptionPedSpawner("Male Mexicangoon 3", -1773333796);
		AddOptionPedSpawner("Male Pologoon", 1329576454);
		AddOptionPedSpawner("Male Pologoon 2", -1561829034);
		AddOptionPedSpawner("Male Salvaboss", -1872961334);
		AddOptionPedSpawner("Male Salvagoon", 663522487);
		AddOptionPedSpawner("Male Salvagoon 2", 846439045);
		AddOptionPedSpawner("Male Salvagoon 3", 62440720);
		AddOptionPedSpawner("Male Stream Punk", -48477765);
		AddOptionPedSpawner("Male Stream Punk 2", 228715206);
		AddOptionPedSpawner("Abigail", 1074457665);
		AddOptionPedSpawner("Ashley", 2129936603);
		AddOptionPedSpawner("Bank Man", -1868718465);
		AddOptionPedSpawner("Barry", 797459875);
		AddOptionPedSpawner("Best Men", 1464257942);
		AddOptionPedSpawner("Beverly", -1113448868);
		AddOptionPedSpawner("Bride", 1633872967);
		AddOptionPedSpawner("Car Guy", -2063996617);
		AddOptionPedSpawner("Car Guy 2", 1975732938);
		AddOptionPedSpawner("Casey", -520477356);
		AddOptionPedSpawner("Chef", 1240128502);
		AddOptionPedSpawner("Chengsr", -1427838341);
		AddOptionPedSpawner("Chris Formage", 678319271);
		AddOptionPedSpawner("Clay", 1825562762);
		AddOptionPedSpawner("Clay Pain", -1660909656);
		AddOptionPedSpawner("Cletus", -429715051);
		AddOptionPedSpawner("Dale", 1182012905);
		AddOptionPedSpawner("Dreyfuss", -628553422);
		AddOptionPedSpawner("Janet", 225287241);
		AddOptionPedSpawner("Jewelass", 257763003);
		AddOptionPedSpawner("Jimmy Boston", -308279251);
		AddOptionPedSpawner("Joe Minuteman", -1105179493);
		AddOptionPedSpawner("Josef", -518348876);
		AddOptionPedSpawner("Josh", 2040438510);
		AddOptionPedSpawner("Kerry Mcintosh", 1530648845);
		AddOptionPedSpawner("Lifeinvad", 1401530684);
		AddOptionPedSpawner("Lifeinvad 2", 666718676);
		AddOptionPedSpawner("Magenta", -52653814);
		AddOptionPedSpawner("Manuel", -46035440);
		AddOptionPedSpawner("Maryann", -1552967674);
		AddOptionPedSpawner("Natalia", -568861381);
		AddOptionPedSpawner("Old Man", 1906124788);
		AddOptionPedSpawner("Old Man 2", -283816889);
		AddOptionPedSpawner("Oneil", 768005095);
		AddOptionPedSpawner("Ortega", 648372919);
		AddOptionPedSpawner("Paper", -1717894970);
		AddOptionPedSpawner("Prolsec", 666086773);
		AddOptionPedSpawner("Hic", 1165307954);
		AddOptionPedSpawner("Hipster", -554721426);
		AddOptionPedSpawner("Mexican", -424905564);
		AddOptionPedSpawner("Roccopelosi", -709209345);
		AddOptionPedSpawner("Screen_writer", -1689993);
		AddOptionPedSpawner("Talina", -409745176);
		AddOptionPedSpawner("Terry", 1728056212);
		AddOptionPedSpawner("Tom Epsilon", -847807830);
		AddOptionPedSpawner("Traffic Warden", 1461287021);
		AddOptionPedSpawner("Tyler Dix", 1382414087);
		AddOptionPedSpawner("Zimbor", 188012277);
		AddOptionPedSpawner("Female Barber", 373000027);
		AddOptionPedSpawner("Female Maid", -527186490);
		AddOptionPedSpawner("Female Shop High", -1371020112);
		AddOptionPedSpawner("Female Sweat Shop", 824925120);
		AddOptionPedSpawner("Female Air Hostess", 1567728751);
		AddOptionPedSpawner("Female Bay Watch", 1250841910);
		AddOptionPedSpawner("Female Cop", 368603149);
		AddOptionPedSpawner("Female Factory", 1777626099);
		AddOptionPedSpawner("Female Hooker", 42647445);
		AddOptionPedSpawner("Female Hooker 2", 348382215);
		AddOptionPedSpawner("Female Hooker 3", 51789996);
		AddOptionPedSpawner("Female Movie Prem", 587253782);
		AddOptionPedSpawner("Female Ranger", -1614285257);
		AddOptionPedSpawner("Female Scrubs", -1420211530);
		AddOptionPedSpawner("Female Sheriff", 1096929346);
		AddOptionPedSpawner("Female Shop Low", -1452399100);
		AddOptionPedSpawner("Female Shop Mid", 1055701597);
		AddOptionPedSpawner("Female Stripper Lite", 1544875514);
		AddOptionPedSpawner("Female Stripper", 1381498905);
		AddOptionPedSpawner("Female Stripper 2", 1846523796);
		AddOptionPedSpawner("Female Sweat Shop", -2063419726);
		AddOptionPedSpawner("Male Ammucountry", 233415434);
		AddOptionPedSpawner("Male Armoured", -1782092083);
		AddOptionPedSpawner("Male Armoured 2", 1669696074);
		AddOptionPedSpawner("Male Autoshop", 68070371);
		AddOptionPedSpawner("Male Autoshop", -261389155);
		AddOptionPedSpawner("Male Chemsec", 788443093);
		AddOptionPedSpawner("Male Ciasec", 1650288984);
		AddOptionPedSpawner("Male Cntrybar", 436345731);
		AddOptionPedSpawner("Male Dock Work", 349680864);
		AddOptionPedSpawner("Male Doctor", -730659924);
		AddOptionPedSpawner("Male Fib Office", -306416314);
		AddOptionPedSpawner("Male Fib Office 2", 653289389);
		AddOptionPedSpawner("Male Gaffer", -1453933154);
		AddOptionPedSpawner("Male Gardener", 1240094341);
		AddOptionPedSpawner("Male Gentransport", 411102470);
		AddOptionPedSpawner("Male High Sec", -245247470);
		AddOptionPedSpawner("Male High Sec 2", 691061163);
		AddOptionPedSpawner("Male Janitor", -1452549652);
		AddOptionPedSpawner("Male Lathandy", -1635724594);
		AddOptionPedSpawner("Male Lifeinvad", -570394627);
		AddOptionPedSpawner("Male Linecook", -610530921);
		AddOptionPedSpawner("Male Lsmetro", 1985653476);
		AddOptionPedSpawner("Male Mariachi", 2124742566);
		AddOptionPedSpawner("Male Marine", -220552467);
		AddOptionPedSpawner("Male Marine 2", -265970301);
		AddOptionPedSpawner("Male Movie Prem", -664900312);
		AddOptionPedSpawner("Male Movies Pace", -407694286);
		AddOptionPedSpawner("Male Paramedic", -1286380898);
		AddOptionPedSpawner("Male Pilot", -413447396);
		AddOptionPedSpawner("Male Postal", 1650036788);
		AddOptionPedSpawner("Male Postal 2", 1936142927);
		AddOptionPedSpawner("Male Prison Guard", 1456041926);
		AddOptionPedSpawner("Male Security", -681004504);
		AddOptionPedSpawner("Male Snow Cop", 451459928);
		AddOptionPedSpawner("Male Strperf", 2035992488);
		AddOptionPedSpawner("Male Strpreach", 469792763);
		AddOptionPedSpawner("Male Strvend", -829353047);
		AddOptionPedSpawner("Male Trucker", 1498487404);
		AddOptionPedSpawner("Male Ups", -1614577886);
		AddOptionPedSpawner("Male Ups  2", -792862442);
		AddOptionPedSpawner("Male Busker", -1382092357);
		AddOptionPedSpawner("Male Airworker", 1644266841);
		AddOptionPedSpawner("Male Ammucity", -1643617475);
		AddOptionPedSpawner("Male Armymech", 1657546978);
		AddOptionPedSpawner("Male Autopsy", -1306051250);
		AddOptionPedSpawner("Male Barman", -442429178);
		AddOptionPedSpawner("Male Bay Watch", 189425762);
		AddOptionPedSpawner("Male Black Ops", -1275859404);
		AddOptionPedSpawner("Male Black Ops 2", 2047212121);
		AddOptionPedSpawner("Male Busboy", -654717625);
		AddOptionPedSpawner("Male Chef", 261586155);
		AddOptionPedSpawner("Male Construck", -673538407);
		AddOptionPedSpawner("Male Construck 2", -973145378);
		AddOptionPedSpawner("Male Cop", 1581098148);
		AddOptionPedSpawner("Male Dealer", -459818001);
		AddOptionPedSpawner("Male Devin Sec", -1688898956);
		AddOptionPedSpawner("Male Dock Work", -2039072303);
		AddOptionPedSpawner("Male Door Man", 579932932);
		AddOptionPedSpawner("Male Dw Service", 1976765073);
		AddOptionPedSpawner("Male Dw Service 2", -175076858);
		AddOptionPedSpawner("Male Factory", 1097048408);
		AddOptionPedSpawner("Male Garbage", -294281201);
		AddOptionPedSpawner("Male Grip", 815693290);
		AddOptionPedSpawner("Male Hway Cop", 1939545845);
		AddOptionPedSpawner("Male Marine", 1702441027);
		AddOptionPedSpawner("Male Marine 2", 1490458366);
		AddOptionPedSpawner("Male Marine 3", 1925237458);
		AddOptionPedSpawner("Male Pestcont", 1209091352);
		AddOptionPedSpawner("Male Pilot", -1422914553);
		AddOptionPedSpawner("Male Prismuscl", 1596003233);
		AddOptionPedSpawner("Male Ranger", -277793362);
		AddOptionPedSpawner("Male Robber", -1067576423);
		AddOptionPedSpawner("Male Sheriff", -1320879687);
		AddOptionPedSpawner("Male Shop Mask", 1846684678);
		AddOptionPedSpawner("Male Strvend", -1837161693);
		AddOptionPedSpawner("Male Uscg", -905948951);
		AddOptionPedSpawner("Male Valet", 999748158);
		AddOptionPedSpawner("Male Waiter", -1387498932);
		AddOptionPedSpawner("Male Winclean", 1426951581);
		AddOptionPedSpawner("Male Xmech", 1142162924);
		AddOptionPedSpawner("Male Xmech 2", -1105135100);
		AddOptionPedSpawner("Female Corpse", 773063444);
		AddOptionPedSpawner("Female Miranda", 1095737979);
		AddOptionPedSpawner("Female Promourn", -1576494617);
		AddOptionPedSpawner("Female Moviestar", 894928436);
		AddOptionPedSpawner("Female Prolhost", -988619485);
		AddOptionPedSpawner("Female Comjane", -1230338610);
		AddOptionPedSpawner("Female Corpse", -1670377315);
		AddOptionPedSpawner("Female Corpse 2", 228356856);
		AddOptionPedSpawner("Female Hotposh", -1768198658);
		AddOptionPedSpawner("Female Jewelass", -254493138);
		AddOptionPedSpawner("Female Mistress", 1573528872);
		AddOptionPedSpawner("Female Princess", -756833660);
		AddOptionPedSpawner("Female Spyactress", 1535236204);
		AddOptionPedSpawner("Male Aldinapoli", -252946718);
		AddOptionPedSpawner("Male Bank Man", -1022961931);
		AddOptionPedSpawner("Male Bike Mire", 1984382277);
		AddOptionPedSpawner("Male Fibar Chitect", 874722259);
		AddOptionPedSpawner("Male Filmdirector", 728636342);
		AddOptionPedSpawner("Male Glen Stank", 1169888870);
		AddOptionPedSpawner("Male Griff", -1001079621);
		AddOptionPedSpawner("Male Jewelsec", -1395868234);
		AddOptionPedSpawner("Male Jewelthief", -422822692);
		AddOptionPedSpawner("Male Mark Fost", 479578891);
		AddOptionPedSpawner("Male Party Target", -2114499097);
		AddOptionPedSpawner("Male Prolsec", 1888624839);
		AddOptionPedSpawner("Male Promourn", -829029621);
		AddOptionPedSpawner("Male Rivalpap", 1624626906);
		AddOptionPedSpawner("Male Spyactor", -1408326184);
		AddOptionPedSpawner("Male Willyfist", -1871275377);
		AddOptionPedSpawner("Male Finguru", 1189322339);
		AddOptionPedSpawner("Male Taphill Billy", -1709285806);
		AddOptionPedSpawner("Male Tramp", 1787764635);
		AddOptionPedSpawner("Male Abner", -257153498);
		AddOptionPedSpawner("Male Antonb", -815646164);
		AddOptionPedSpawner("Male Babyd", -636391810);
		AddOptionPedSpawner("Male Baygor", 1380197501);
		AddOptionPedSpawner("Male Cyclist", 755956971);
		AddOptionPedSpawner("Male Fibmugger", -2051422616);
		AddOptionPedSpawner("Male Guido", -961242577);
		AddOptionPedSpawner("Male Gunvend", -1289578670);
		AddOptionPedSpawner("Male Hippie", -264140789);
		AddOptionPedSpawner("Male Mani", -927261102);
		AddOptionPedSpawner("Male Military Bum", 1191548746);
		AddOptionPedSpawner("Male Paparazzi", 1346941736);
		AddOptionPedSpawner("Male Party", 921110016);
		AddOptionPedSpawner("Male Proldriver", -2057423197);
		AddOptionPedSpawner("Male Sbike", 1794381917);
		AddOptionPedSpawner("Male Staggrm", -1852518909);
		AddOptionPedSpawner("Male Tattoo", -1800524916);
		AddOptionPedSpawner("Driver", 994527967);
		AddOptionPedSpawner("Hacker", -1715797768);
		AddOptionPedSpawner("Amanda Townley", 1830688247);
		AddOptionPedSpawner("Andreas", 1206185632);
		AddOptionPedSpawner("Ballasog", -1492432238);
		AddOptionPedSpawner("Brad", -1111799518);
		AddOptionPedSpawner("Davenorton", 365775923);
		AddOptionPedSpawner("Denise", -2113195075);
		AddOptionPedSpawner("Devin", 1952555184);
		AddOptionPedSpawner("Dom", -1674727288);
		AddOptionPedSpawner("Dr Fried Lander", -872673803);
		AddOptionPedSpawner("Fabien", -795819184);
		AddOptionPedSpawner("Floyd", -1313761614);
		AddOptionPedSpawner("Jay Norris", 2050158196);
		AddOptionPedSpawner("Lazlow", -538688539);
		AddOptionPedSpawner("Milton", -886023758);
		AddOptionPedSpawner("Molly", -1358701087);
		AddOptionPedSpawner("Omega", 1625728984);
		AddOptionPedSpawner("Patricia", -982642292);
		AddOptionPedSpawner("Siemonyetarian", 1283141381);
		AddOptionPedSpawner("Solomon", -2034368986);
		AddOptionPedSpawner("Stevehains", 941695432);
		AddOptionPedSpawner("Stretch", 915948376);
		AddOptionPedSpawner("Taocheng", -597926235);
		AddOptionPedSpawner("Taostranslator", 2089096292);
		AddOptionPedSpawner("Tennis Coach", -1573167273);
		AddOptionPedSpawner("Tracy Disanto", -566941131);
		AddOptionPedSpawner("Dead Hooker", 1943971979);
		AddOptionPedSpawner("Stripper Lite", 695248020);
		AddOptionPedSpawner("Headtargets", 1173958009);
		AddOptionPedSpawner("Claude", -1057787465);
		AddOptionPedSpawner("Famdd", 866411749);
		AddOptionPedSpawner("Fibsec", 1558115333);
		AddOptionPedSpawner("Marston", 943915367);
		AddOptionPedSpawner("Niko", -287649847);
		AddOptionPedSpawner("Shop Keeper", 416176080);
		break;
#pragma endregion
#pragma region Weapon Options
	case Weapon_Options:
		WeaponSprite();
		addTitle("Weapon Options");
		addSubmenuOption("Object Gun Options", Fun_Gun_Options);
		addSubmenuOption("Weapon Tint Options", WeaponTint);
		addSubmenuOption("Weapon Attachments Options", Weapon_Attachments_Options);
		addBoolOption("Explosive Ammo", explosive_ammo);
		addBoolOption("Fire Gun", fire_gun);
		addBoolOption("Toggle Object Gun", Fun_Gun);
		addOption("Give Self Stun Gun");
		addBoolOption("Gravity Gun", GravityGunLoop2);
		//addBoolOption("Gravity Gun 2", GravityGunLoop2);
		addBoolOption("Car Gun", CarGun);
		addBoolOption("Unlimited Ammo", Unlimited_Ammo);
		addBoolOption("Aimbot", Aimbot_Toggle);
		addIntOption("Weapon Damage Modifier", &WeaponModifer, 0, 100, true); //castRayTestBool
		addBoolOption("raycast test", castRayTestBool);
		addBoolOption("Aimbot Head", aimbot);
		addBoolOption("Ironman", nocliploop);
		//addBoolOption("RPG Gun", RPG_GUN);
		//addBoolOption("Teleport Gun", Teleport_gun);
		switch (getOption())
		{
		case 4: explosive_ammo = !explosive_ammo; break;
		case 5: fire_gun = !fire_gun; break;
		case 6: Fun_Gun = !Fun_Gun; break;
		case 7: WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x3656C8C1, 9999, 1); break;
		case 8: GravityGunLoop2 = !GravityGunLoop2; break;
		case 9: CarGun = !CarGun; break;
		case 10: Unlimited_Ammo = !Unlimited_Ammo; break;
		case 11: Aimbot_Toggle = !Aimbot_Toggle; break;
		case 12: PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), WeaponModifer); break;
		case 13: castRayTestBool = !castRayTestBool; break;
		case 14: aimbot = !aimbot; break;
		case 15: nocliploop = !nocliploop; break;
		}
		break;
#pragma endregion
#pragma region Weapon Tint
	case WeaponTint:
		WeaponSprite();
		addTitle("Weapon Tint");
		addWeapTintOption("Default", 0);
		addWeapTintOption("Green", 1);
		addWeapTintOption("Gold", 2);
		addWeapTintOption("Pink", 3);
		addWeapTintOption("Army", 4);
		addWeapTintOption("LSPD", 5);
		addWeapTintOption("Orange", 6);
		addWeapTintOption("Platinum", 7);
		addWeapTintOption("Rainbow Flare Smoke", 8);
		break;
#pragma endregion
#pragma region Weapon Attachments Options
	case Weapon_Attachments_Options:
		WeaponSprite();
		addTitle("Weapon Attachments Options");
		addSubmenuOption("Pistols Attachments", Pistol_Attachments);
		addSubmenuOption("SMG Attachments", SMG_Attachments);
		addSubmenuOption("MG Attachments", MG_Attachments);
		addSubmenuOption("Assault Rifles Attachments", Assault_Rifles_Attachments);
		addSubmenuOption("Shotguns Attachments", Shotguns_Attachments);
		addSubmenuOption("Snipers Attachments", Snipers_Attachments);
		addSubmenuOption("Other Weapon Attachments", Other_Attachments);
		break;
#pragma endregion

#pragma region Pistol
	case PistolAtt:
		WeaponSprite();
		addTitle("Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_pistol"), GAMEPLAY::GET_HASH_KEY("component_pistol_clip_01"));
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_pistol"), GAMEPLAY::GET_HASH_KEY("component_pistol_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_pistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_pistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
		break;
#pragma endregion
#pragma region Combat Pistol
	case CombatPistol:
		WeaponSprite();
		addTitle("Combat Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_combatpistol"), GAMEPLAY::GET_HASH_KEY("component_combatpistol_clip_01"));
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_combatpistol"), GAMEPLAY::GET_HASH_KEY("component_combatpistol_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_combatpistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_combatpistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
		break;
#pragma endregion
#pragma region AP Pistol
	case APPistol:
		WeaponSprite();
		addTitle("AP Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_appistol"), GAMEPLAY::GET_HASH_KEY("component_appistol_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_appistol"), GAMEPLAY::GET_HASH_KEY("component_appistol_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_appistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_appistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
#pragma endregion
#pragma region 50 Pistol
	case Pistol50:
		WeaponSprite();
		addTitle(".50 Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_pistol50"), GAMEPLAY::GET_HASH_KEY("component_pistol50_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_pistol50"), GAMEPLAY::GET_HASH_KEY("component_pistol50_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_pistol50"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		break;
#pragma endregion
#pragma region SNS Pistol
	case SNSPistol:
		WeaponSprite();
		addTitle("SNS Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_snspistol"), GAMEPLAY::GET_HASH_KEY("component_snspistol_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_snspistol"), GAMEPLAY::GET_HASH_KEY("component_snspistol_clip_02"));
		break;
#pragma endregion
#pragma region Heavy Pistol
	case HeavyPistol:
		WeaponSprite();
		addTitle("Heavy Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_heavypistol"), GAMEPLAY::GET_HASH_KEY("component_heavypistol_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_heavypistol"), GAMEPLAY::GET_HASH_KEY("component_heavypistol_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_heavypistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_heavypistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
		break;
#pragma endregion
#pragma region Vintage Pistol
	case VintagePistol:
		WeaponSprite();
		addTitle("Vintage Pistol");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_vintagepistol"), GAMEPLAY::GET_HASH_KEY("component_vintagepistol_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_vintagepistol"), GAMEPLAY::GET_HASH_KEY("component_vintagepistol_clip_02"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_vintagepistol"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
		break;
#pragma endregion
#pragma region SMG Attachments
	case SMG_Attachments:
		WeaponSprite();
		addTitle("SMG Attachments");
		addSubmenuOption("Micro SMG", MicroSMGAttch);
		addSubmenuOption("SMG", SMGAttch);
		addSubmenuOption("Assault SMG", AssaultSMG);
		break;
#pragma endregion
#pragma region Micro SMG
	case MicroSMGAttch:
		WeaponSprite();
		addTitle("Micro SMG");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), GAMEPLAY::GET_HASH_KEY("component_microsmg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), GAMEPLAY::GET_HASH_KEY("component_microsmg_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), GAMEPLAY::GET_HASH_KEY("component_at_pi_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), GAMEPLAY::GET_HASH_KEY("component_at_scope_macro"));
		break;
#pragma endregion
#pragma region SMG
	case SMGAttch:
		WeaponSprite();
		addTitle("SMG");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_smg"), GAMEPLAY::GET_HASH_KEY("component_smg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_smg"), GAMEPLAY::GET_HASH_KEY("component_smg_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_smg"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_smg"), GAMEPLAY::GET_HASH_KEY("component_at_pi_supp"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_smg"), GAMEPLAY::GET_HASH_KEY("component_at_scope_macro"));
		break;
#pragma endregion
#pragma region Assault SMG
	case AssaultSMG:
		WeaponSprite();
		addTitle("Assault SMG");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_assaultsmg"), GAMEPLAY::GET_HASH_KEY("component_assaultsmg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_assaultsmg"), GAMEPLAY::GET_HASH_KEY("component_assaultsmg_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_assaultsmg"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_assaultsmg"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_assaultsmg"), GAMEPLAY::GET_HASH_KEY("component_at_scope_macro"));
		break;
#pragma endregion
#pragma region MG Attachments
	case MG_Attachments:
		WeaponSprite();
		addTitle("MG Attachments");
		addSubmenuOption("MG", MGAttch);
		addSubmenuOption("Combat MG", CombatMGAttch);
		break;
#pragma endregion
#pragma region MG
	case MGAttch:
		WeaponSprite();
		addTitle("MG");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_mg"), GAMEPLAY::GET_HASH_KEY("component_mg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_mg"), GAMEPLAY::GET_HASH_KEY("component_mg_clip_02"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_mg"), GAMEPLAY::GET_HASH_KEY("component_at_scope_small"));
		break;
#pragma endregion
#pragma region Combat MG
	case CombatMGAttch:
		WeaponSprite();
		addTitle("Combat MG");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_combatmg"), GAMEPLAY::GET_HASH_KEY("component_combatmg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_combatmg"), GAMEPLAY::GET_HASH_KEY("component_combatmg_clip_02"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_combatmg"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_combatmg"), GAMEPLAY::GET_HASH_KEY("component_at_scope_medium"));
		break;
#pragma endregion
#pragma region Assault Rifles Attachments
	case Assault_Rifles_Attachments:
		WeaponSprite();
		addTitle("Assault Rifles Attachments");
		addSubmenuOption("Combat PDW Rifle", CombatpdwAttch);
		addSubmenuOption("Assault Rifle", AssaultRifleAttch);
		addSubmenuOption("Carbine Rifle", CarbineRifleAttch);
		addSubmenuOption("Advanced Rifle", AdvancedRifleAttch);
		addSubmenuOption("Special Carbine Rifle", SpecialCarbineAttch);
		addSubmenuOption("Bullpup Rifle", BullpupRifleAttch);
		break;
#pragma endregion
#pragma region Combat PDW Rifle
	case CombatpdwAttch:
		WeaponSprite();
		addTitle("Combat PDW Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_combatpdw"), GAMEPLAY::GET_HASH_KEY("component_combatpdw_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_combatpdw"), GAMEPLAY::GET_HASH_KEY("component_combatpdw_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_combatpdw"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_combatpdw"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_combatpdw"), GAMEPLAY::GET_HASH_KEY("component_at_scope_small"));
		break;
#pragma endregion
#pragma region Assault Rifle
	case AssaultRifleAttch:
		WeaponSprite();
		addTitle("Assault Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_assaultrifle_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_assaultrifle_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_at_scope_macro"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		break;
#pragma endregion
#pragma region Carbine Rifle
	case CarbineRifleAttch:
		WeaponSprite();
		addTitle("Carbine Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_carbinerifle_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_carbinerifle_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_at_scope_medium"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Advanced Rifle
	case AdvancedRifleAttch:
		WeaponSprite();
		addTitle("Advanced Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_advancedrifle"), GAMEPLAY::GET_HASH_KEY("component_advancedrifle_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_advancedrifle"), GAMEPLAY::GET_HASH_KEY("component_advancedrifle_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_advancedrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_advancedrifle"), GAMEPLAY::GET_HASH_KEY("component_at_scope_small"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_advancedrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Special Carbine Rifle
	case SpecialCarbineAttch:
		WeaponSprite();
		addTitle("Special Carbine Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_specialcarbine_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_specialcarbine_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_at_scope_medium"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		break;
#pragma endregion
#pragma region Bullpup Rifle
	case BullpupRifleAttch:
		WeaponSprite();
		addTitle("Bullpup Rifle");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_bullpuprifle_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_bullpuprifle_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_at_scope_small"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Shotguns Attachments
	case Shotguns_Attachments:
		WeaponSprite();
		addTitle("Shotguns Attachments");
		addSubmenuOption("Pump Shotgun", PumpShotgun);
		addSubmenuOption("Assault Shotgun", AssaultShotgun);
		addSubmenuOption("Bullpup Shotgun", BullpupShotgun);
		addSubmenuOption("Heavy Shotgun", HeavyShotgun);
		break;
#pragma endregion
#pragma region Heavy Shotgun
	case PumpShotgun:
		WeaponSprite();
		addTitle("Pump Shotgun");
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_pumpshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_pumpshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_sr_supp"));
		break;
#pragma endregion
#pragma region Assault Shotgun
	case AssaultShotgun:
		WeaponSprite();
		addTitle("Assault Shotgun");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_assaultshotgun"), GAMEPLAY::GET_HASH_KEY("component_assaultshotgun_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_assaultshotgun"), GAMEPLAY::GET_HASH_KEY("component_assaultshotgun_clip_02"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_assaultshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_assaultshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Bullpup Shotgun
	case BullpupShotgun:
		WeaponSprite();
		addTitle("Bullpup Shotgun");
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_bullpupshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_bullpupshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_bullpupshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		break;
#pragma endregion
#pragma region Heavy Shotgun
	case HeavyShotgun:
		WeaponSprite();
		addTitle("Heavy Shotgun");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_heavyshotgun"), GAMEPLAY::GET_HASH_KEY("component_heavyshotgun_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_heavyshotgun"), GAMEPLAY::GET_HASH_KEY("component_heavyshotgun_clip_02"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_heavyshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_heavyshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_heavyshotgun"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Snipers Attachments
	case Snipers_Attachments:
		WeaponSprite();
		addTitle("Snipers Attachments");
		addSubmenuOption("Sniper Rifle", SniperrifleAttch);
		addSubmenuOption("Heavy Sniper Rifle", HeavySniperAttch);
		addSubmenuOption("Marksman Sniper Rifle", MarksmanRifleAttch);
		break;
#pragma endregion
#pragma region Sniper Rifle
	case SniperrifleAttch:
		WeaponSprite();
		addTitle("Sniper Rifle");
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_sniperrifle"), GAMEPLAY::GET_HASH_KEY("component_at_scope_max"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_sniperrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp_02"));
		break;
#pragma endregion
#pragma region Heavy Sniper Rifle
	case HeavySniperAttch:
		WeaponSprite();
		addTitle("Heavy Sniper Rifle");
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_heavysniper"), GAMEPLAY::GET_HASH_KEY("component_at_scope_max"));
		break;
#pragma endregion
#pragma region Marksman Sniper Rifle
	case MarksmanRifleAttch:
		WeaponSprite();
		addTitle("Marksman Sniper Rifle");
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_marksmanrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Grip", GAMEPLAY::GET_HASH_KEY("weapon_marksmanrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Silencer", GAMEPLAY::GET_HASH_KEY("weapon_marksmanrifle"), GAMEPLAY::GET_HASH_KEY("component_at_ar_supp"));
		break;
#pragma endregion
#pragma region Other Weapon Attachments
	case Other_Attachments:
		WeaponSprite();
		addTitle("Other Weapon Attachments");
		addSubmenuOption("Gusenberg", GusenbergAttch);
		addSubmenuOption("Grenade Launcher", GrenadeLauncherAttch);
		break;
#pragma endregion
#pragma region Gusenberg
	case GusenbergAttch:
		WeaponSprite();
		addTitle("Gusenberg");
		addWeapAttachOption("Extended Mag", GAMEPLAY::GET_HASH_KEY("weapon_gusenberg"), GAMEPLAY::GET_HASH_KEY("component_gusenberg_clip_01"));
		addWeapAttachOption("Extended Mag 2", GAMEPLAY::GET_HASH_KEY("weapon_gusenberg"), GAMEPLAY::GET_HASH_KEY("component_gusenberg_clip_02"));
		break;
#pragma endregion
#pragma region Grenade Launcher
	case GrenadeLauncherAttch:
		WeaponSprite();
		addTitle("Grenade Launcher");
		addWeapAttachOption("Grip Mag", GAMEPLAY::GET_HASH_KEY("weapon_grenadelauncher"), GAMEPLAY::GET_HASH_KEY("component_at_ar_afgrip"));
		addWeapAttachOption("Flash Light", GAMEPLAY::GET_HASH_KEY("weapon_grenadelauncher"), GAMEPLAY::GET_HASH_KEY("component_at_ar_flsh"));
		addWeapAttachOption("Scope", GAMEPLAY::GET_HASH_KEY("weapon_grenadelauncher"), GAMEPLAY::GET_HASH_KEY("component_at_scope_small"));
		break;
#pragma endregion
#pragma region Fun Gun Options
	case Fun_Gun_Options:
		WeaponSprite();
		addTitle("Object Gun Options");
		addOption("Set Item To  Dildo");
		addOption("Set Item To Alien Egg");
		addOption("Set Item To White Block");
		addOption("Set Item To Shit");
		addOption("Set Item To Tarp Body");
		switch (getOption())
		{
		case 1: FunGunItem = GAMEPLAY::GET_HASH_KEY("prop_cs_dildo_01"); break;
		case 2: FunGunItem = 1803116220; break;
		case 3: FunGunItem = -1007599668; break;
		case 4: FunGunItem = -2071359746; break;
		case 5: FunGunItem = -1240857364; break;
		}
		break;
#pragma endregion
#pragma region Teleport Menu
	case Teleport_Options:

		addTitle("Teleport Menu");
		addOption("Waypoint");
		addOption("Get Coords");
		addTeleportOption("Airport Top", -1030.025146, -3015.658691, 49.091133);
		addTeleportOption("Airport Bottom", -1500.652588f, -2858.271729f, 13.954378f);
		addTeleportOption("Airport Office", -1559.734741, -3237.086182, 29.634100);
		addTeleportOption("Franklins Crib", 8.069606, 537.153015, 176.028015);
		addTeleportOption("Micheals Crib", -813.176453, 179.232452, 72.159149);
		addTeleportOption("Trever Crib", 1974.7580, 3819.4570, 3.4363);
		addTeleportOption("Morningwood Ammunation", -1330.267822, -390.644684, 36.602779);
		addTeleportOption("Burton LS Customs", -384.217834, -118.733658, 38.689579);
		addTeleportOption("10 Car Garage", 228.7188, -989.9847, -99.0);
		addTeleportOption("Paleto Bank", -107.862190, 6466.428223, 31.626722);
		addTeleportOption("Mount Chilliad", 501.980743, 5604.786133, 797.909363);
		addTeleportOption("Trevor Airfield", 1704.752686, 3275.902832, 41.157715);
		addTeleportOption("Secret Army Tower", -2358.946045, 3252.216797, 101.450424);
		addTeleportOption("Secret Island", -2167.429932, 5190.774414, 16.238092);
		addTeleportOption("Desert Night Club", 1956.499878, 3083.499756, 46.781418);
		addTeleportOption("FIB Building", 135.534073, -749.334595, 258.151764);
		addTeleportOption("IAA Building", 121.494728, -622.014954, 206.046783);
		addTeleportOption("Lab Upper Level", 3618.517822, 3740.693604, 28.690096);
		addTeleportOption("Lab Lower Level", 3526.256836, 3706.816895, 20.991793);
		addTeleportOption("Eclipse Tower Apartment", -810.110901, 300.467865, 86.118515);
		addTeleportOption("Tinsel Tower Apartment", -641.864624, 24.014740, 39.351025);
		addTeleportOption("Bank Vault", 263.021759, 220.656754, 106.282593);
		addTeleportOption("Lazer Spawn 1", -2150.634277, 3234.995117, 32.810455);
		addTeleportOption("Lazer Spawn 2", -2246.638672, 3230.022949, 32.810146);
		addTeleportOption("Lazer Spawn 3", -2138.139893, 3056.729736, 32.809875);
		addTeleportOption("Lazer Spawn 4", -2022.258423, 2973.546875, 33.118137);
		addTeleportOption("Lazer Spawn 5", -2007.929932, 3098.386475, 32.810257);
		addTeleportOption("Bridge Top", -546.417297, -2229.224365, 122.364899);
		addTeleportOption("Trevor's Torture Room", 136.323441, -2203.203857, 7.309136);
		addTeleportOption("Maze Tower", -73.92588, -818.455078, 326.174377);
		addTeleportOption("Construction Tower", -143.881927, -984.810852, 269.134308);
		addTeleportOption("LSPD Station", 446.413544, -985.128113, 30.689520);
		addTeleportOption("Clock Tower", -1238.675537, -847.954590, 85.161690);
		addTeleportOption("Sniper Tower", -550.989380, -193.862366, 76.499336);
		addTeleportOption("Merryweather", 568.406006, -3125.799805, 18.768612);
		addTeleportOption("Meth Lab", 1397.5240, 3607.4230, 38.9419);
		addTeleportOption("Emergency HeliPad", 308.9238, -1458.9330, 46.5095);
		addTeleportOption("HeliPad", -736.7500, -1437.7500, 5.0003);
		addTeleportOption("Under the bridge Glitch", 721.6599, -1000.6510, 23.5455);
		addTeleportOption("Alta St Apartment Enter", -266.0524, -968.6304, 31.2243);
		addTeleportOption("Police HeliPad", 369.4300, -1601.8320, 36.9502);
		addTeleportOption("Police Parking Roof", 334.2101, -1644.7660, 98.4960);
		addTeleportOption("Lester's House", 1248.1830, -1728.1040, 56.0000);
		addTeleportOption("Waynes Cousins House", -1159.0340, -1521.1800, 10.6327);
		addTeleportOption("Airport Terminal", -1561.5250, -3232.3460, 26.3361);
		addTeleportOption("Crane(1)", -167.9822, -1001.9265, 296.2061);
		addTeleportOption("Crane(2) Balcony", -120.3508, -977.8608, 304.2478);
		addTeleportOption("Crane 3 (Scenic)", -119.859985, -976.43866, 306.3385);
		addTeleportOption("Ontop of Vinewood Logo", 776.8780, 1175.6080, 345.9564);
		addTeleportOption("City Wall(Glitch)", -254.9432, -147.3534, 42.7314);
		addTeleportOption("Far Away Beach", 178.3295, 7041.8220, 1.8671);
		addTeleportOption("Coral Reef", 106.6972, 7282.0550, 1.8821);
		addTeleportOption("Underwater Ocean", 103.4720, 7744.1870, -158.1106);
		addTeleportOption("Dirtbike Trail", -1202.0910, 2802.4400, 14.8256);
		addTeleportOption("Private Hangout(Creek)", -463.6622, 4483.6540, 36.0373);
		addTeleportOption("Private hangout 2(Waterfall)", -597.9525, 4475.2910, 25.6890);
		addTeleportOption("Ontop of Waterfall", -540.4822, 4402.3590, 34.3786);
		addTeleportOption("Canyon Bridge/Tunnel/TrainTracks", -530.6747, 4534.9960, 89.0457);
		addTeleportOption("Calafia Bridge(Near Canyon bridge)", -175.2189, 4244.1940, 44.0730);
		addTeleportOption("Inside Casino", 937.4756, 42.4248, 80.8990);
		addTeleportOption("Lookout", -179.9843, 6150.4780, 42.6373);
		addTeleportOption("Behind Bar In Strip Club", 126.1211, -1278.5130, 29.2696);
		addTeleportOption("EMPTY CLOSED IN ROOM", 134.1213, -1289.5810, 29.2696);
		addTeleportOption("Inside Gun range", 22.8730, -1073.8800, 29.7970);
		addTeleportOption("Ammunation Office", 12.4553, -1110.2580, 29.7970);
		addTeleportOption("Just Above the Clouds", -149.3451, 7130.2460, 700.1167);
		addTeleportOption("HIGH IN THE SKY!!!!", -129.9640, 8130.8730, 6705.6510);
		addTeleportOption("Underground Tunnel", 16.9691, -646.1804, 16.0881);
		addTeleportOption("Tunnel Loop", -4.5786, -742.4279, 16.5030);
		addTeleportOption("Tunnel exit", 1033.7290, -270.5642, 50.8552);
		addTeleportOption("I Don't Know Where", -1907.3500, -577.2352, 20.1223);
		addTeleportOption("On top of Light house", 3433.6570, 5175.4090, 35.8053);
		addTeleportOption("Water Fountain", -104.8196, -856.3741, 41.0868);
		addTeleportOption("Water Fountain With Cube", -131.0631, -865.8098, 29.4677);
		addTeleportOption("Inside Jonny Tung", -879.0649, -247.7447, 40.1937);
		addTeleportOption("Vesupucci House Glitch", -976.0147, 2.1502, 2.1502);
		addTeleportOption("GO Postal", 78.9777, 113.4168, 81.1687);
		addTeleportOption("GO Postal 2", 67.4079, 123.5255, 86.1291);
		addTeleportOption("Under Roof", -1883.7390, 2062.8590, 144.8217);
		addTeleportOption("RockfordHill", -869.2877, -250.0446, 39.7795);
		addTeleportOption("PaletoBay Shed", -179.0000, 6150.0000, 42.0000);
		addTeleportOption("Luxury Auto", -783.1708, -246.4606, 37.0212);
		addTeleportOption("DelPerroPier", -1600.0930, -1041.8920, 13.0209);
		addTeleportOption("Middle of Ferris Wheel", -1664.1670, -1126.5330, 32.1513);
		addTeleportOption("Cherry Popper Stand", -1645.5460, -1102.3670, 13.4518);
		addTeleportOption("Cherry Popper 2", 1685.9830, -1104.1350, 13.1523);
		addTeleportOption("Building Wireframe", -129.3836, -951.1331, 218.8816);
		addTeleportOption("Mechanic Glitch", 546.0365, -183.3675, 54.4982);
		addTeleportOption("Land Act Dam", 1655.8130, 0.8890, 173.7747);
		addTeleportOption("Garage(Second Room)", 222.5924, -968.1003, -98.9999);
		addTeleportOption("Humane Lab(Waterbody)", 3524.0700, 3711.9500, 20.9913);
		addTeleportOption("Track", 1226.7500, 125.5000, 81.8394);
		addTeleportOption("Paleto Cove", -1441.6340, 5410.9190, 24.5786);
		addTeleportOption("Vinewood Garage(Storymode)", -66.8998, 81.6470, 71.5300);
		addTeleportOption("Mount Josiah", -1186.1070, 3849.7530, 489.0641);
		addTeleportOption("Theatre Balcony", 335.4643, 170.8678, 111.4973);
		addTeleportOption("Elysian Island Base", 574.3914, -3121.3220, 18.7687);
		addTeleportOption("Prison", 1679.0490, 2513.7110, 45.5649);
		addTeleportOption("Prison Gym", 1640.7910, 2530.0440, 45.5649);
		addTeleportOption("Trapped In Box", -655.6762, -160.8557, 42.1480);
		addTeleportOption("Horses Head", -690.9756, -243.3482, 45.8285);
		addTeleportOption("Tongva Valley", -1523.1900, 1494.3620, 111.5874);
		addTeleportOption("Pretty Hill", -2130.4500, -101.4395, 46.5871);
		addTeleportOption("Mount Gordo", 2948.4480, 5323.8120, 101.1872);
		addTeleportOption("Prison Tower", 1541.6290, 2470.1400, 62.8751);
		addTeleportOption("Another pool", -1197.1560, -246.1534, 37.9545);
		addTeleportOption("Ghost Mountain", 3056.7250, 5622.6430, 205.2412);
		addTeleportOption("Cave", -1909.6820, 1389.1480, 218.4604);
		addTeleportOption("MogShot Stand", -1641.5500, -1097.6340, 13.4500);
		addTeleportOption("MogShot 2", -1682.1570, -1107.2580, 13.1523);
		addTeleportOption("Gifts At The Pier", -1639.9170, -1092.0860, 13.5766);
		addTeleportOption("Gifts At The Pier 2", -1678.2000, -1110.5410, 13.1523);
		addTeleportOption("The Oriental TS(L)", 282.2156, 199.8016, 104.3740);
		addTeleportOption("The Oriental TS(R)", 314.1337, 188.3539, 103.9276);
		addTeleportOption("Cannibal Camp", -1170.1150, 4926.1340, 224.3552);
		addTeleportOption("Cannibal Camp Roof", -1143.1450, 4951.1880, 230.1531);
		addTeleportOption("Cannibal Mountain top", -935.9363, 4836.7470, 310.5199);
		addTeleportOption("Building Glitch", -91.6870, 33.0948, 71.4655);
		addTeleportOption("Dock(Near Lighthouse)", 3369.2240, 5184.1500, 1.4602);
		addTeleportOption("Winding stairs", 3336.1740, 5172.9410, 18.3161);
		addTeleportOption("Creek(Mountain Tower)", 2784.6060, 6000.8770, 357.2007);
		addTeleportOption("Pool", -17.1920, 340.4356, 111.3410);
		addTeleportOption("Inside Store", -1244.1380, -1454.9980, 4.3478);
		addTeleportOption("Hidden beach", 3852.0770, 3625.5670, 9.2139);
		addTeleportOption("Submarine Location", -1606.2000, 5266.9700, -1.4726);
		addTeleportOption("Punpkin Patch", 3285.2290, 5183.5380, 18.4154);
		addTeleportOption("Trapped In Steel", 149.4357, -769.7214, 262.8629);
		switch (getOption())
		{
		case 1:
			int WaypointHandle;
			WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
			if (UI::DOES_BLIP_EXIST(WaypointHandle))
			{
				Vector3 Waypointpos = UI::GET_BLIP_COORDS(WaypointHandle);
				Waypointpos.z += 25.0f;
				int Handle = PLAYER::PLAYER_PED_ID();
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
					Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::SET_ENTITY_COORDS(Handle, Waypointpos.x, Waypointpos.y, Waypointpos.z, 0, 0, 0, 1);
			}
		case 2:
			Vector3 pos;
			pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			printf("\tPosition = {%f, %f, %f};\n", pos.x, pos.y, pos.z);
			ShowMessageOnScreen("~b~ Position = %f   %f   %f", pos.x, pos.y, pos.z);
		}
		break;
#pragma endregion
#pragma region Vehicle Options
	case Vehicle_Menu:

		addTitle("Vehicle Menu");
		addSubmenuOption("Vehicle Options", Vehicle_Options);
		//addSubmenuOption("Vehicle Attach Options", Attach_Vehicle_Options);
		//addSubmenuOption("Spawn 10 Vehicles", Spawn10Vehicles);
		break;
#pragma endregion
#pragma region Attach Vehicle Options
	case Attach_Vehicle_Options:

		addTitle("Vehicle Attach Option");
		addSubmenuOption("Spawn / Attach To Vehicle", Attach_To_Vehicle);
		addSubmenuOption("Edit Object X, Y, Z, H", Edit_Object_X_Y_Z_H);
		switch (getOption())
		{
		case 1: break;
		}
		break;
		break;
#pragma endregion
#pragma region Spawn / Attach To Vehicle
	case Attach_To_Vehicle:

		addTitle("Spawn / Attach To Vehicle");
		addOption("Shipping Container");
		switch (getOption())
		{
		case 1:
			Entity Object = ObjectType = -629735826;
			ObjectSpawnerVeh = true;
			ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(ENTITY::GET_ENTITY_TYPE(Object), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0x0, 0x0, VehObjx, VehObjy, VehObjz, VehObjx2, VehObjy2, VehObjz2, VehObjx3, VehObjy3, VehObjz3, 1000, 1, 1, false, 1, 2);
			break;
		}
		break;
		break;
#pragma endregion
#pragma region Vehicle Menu
	case Vehicle_Options:

		addTitle("Vehicle Options");
		addSubmenuOption("Colour Options", Colour_Options); //1
		addSubmenuOption("Vehicle Weapons", Vehicle_Weapons); //2
		addSubmenuOption("Handling Options", Handling_Options); //3
		addSubmenuOption("Mod Shop", Mod_Shop); //4
		addBoolOption("Flux Color", FluxCar); //6
		addBoolOption("SeatBelt", Seat_Belt); //6
		addOption("Fix & Clean"); //7
		addOption("Flip Vehicle Upright"); //8
		addOption("Max Mods With Chrome Paint"); //9
		addOption("Max Mods Without Paint"); //10
		addBoolOption("God Mode Vehicle", GodMode_Vehicle); //11
		addBoolOption("God Mode Vehicle Loop", GodMode_VehicleLoop); //12
		addBoolOption("Invisible Vehicle", Invisible_Vehicle); //13
		addBoolOption("Collision", Toggle_Collision); //14
		addBoolOption("Lower", Toggle_Lower); //15
		addBoolOption("Low Rider", Toggle_Lower2); //16
		addOption("Change License Plate"); //17
		addOption("Lock Doors"); //18
		addOption("Unlock Doors"); //19
		addBoolOption("Drive On Walls", tWallCrawlVehLoop); //22
		addBoolOption("Vehicle Aiming Lasers", drawLasers); //23
		addSubmenuOption("Neon Options", Speedometer_Options); //24
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: FluxCar = !FluxCar; break;
		case 6:
			if (!Seat_Belt)
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
			else
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
			Seat_Belt = !Seat_Belt; break;
		case 7:
			int myvehicle;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0))
			{
				myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					VEHICLE::SET_VEHICLE_FIXED(myvehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(myvehicle, 0.0f);
				}
			} break;
		case 8:
			Vehicle VehicleHandle;
			VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(VehicleHandle); break;
		case 9:
			int MaxMods;
			MaxMods = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_COLOURS(MaxMods, 120, 120);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(MaxMods, 120, 120);
			VEHICLE::TOGGLE_VEHICLE_MOD(MaxMods, 18, 1);
			VEHICLE::TOGGLE_VEHICLE_MOD(MaxMods, 22, 1);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 16, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 12, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 11, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 14, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 15, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 13, 2, 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MaxMods, 6);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(MaxMods, 5);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 23, 19, 1);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 0, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 1, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 2, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 3, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 4, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 5, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 6, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 7, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 8, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 9, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods, 10, 1, 0);
			break;
		case 10:
			int MaxMods2;
			MaxMods2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::TOGGLE_VEHICLE_MOD(MaxMods2, 18, 1);
			VEHICLE::TOGGLE_VEHICLE_MOD(MaxMods2, 22, 1);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 16, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 12, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 11, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 14, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 15, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 13, 2, 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MaxMods2, 6);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(MaxMods2, 5);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 23, 19, 1);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 0, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 1, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 2, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 3, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 4, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 5, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 6, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 7, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 8, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 9, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MaxMods2, 10, 1, 0);
			break;
		case 11:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				int car;
				car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), PLAYER::PLAYER_ID());
				if (ENTITY::DOES_ENTITY_EXIST(car) && ENTITY::IS_ENTITY_A_VEHICLE(car))
				{
					if (!GodMode_Vehicle)
					{
						VEHICLE::SET_VEHICLE_FIXED(car);
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(car, false);
						ENTITY::SET_ENTITY_INVINCIBLE(car, true);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(car, false);
						GodMode_Vehicle = true;
					}
					else if (GodMode_Vehicle)
					{
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(car, true);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(car, true);
						GodMode_Vehicle = false;
						ENTITY::SET_ENTITY_INVINCIBLE(car, false);
						GodMode_Vehicle = !GodMode_Vehicle; break;
					}
				}
			} break;
		case 12: GodMode_VehicleLoop = !GodMode_VehicleLoop; break;
		case 13:
			int MyCar;
			if (PED::IS_PED_IN_ANY_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_ID(), 0), 0))
			{
				MyCar = PED::GET_VEHICLE_PED_IS_IN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_ID(), 0), 0);
				if (ENTITY::DOES_ENTITY_EXIST(MyCar) && ENTITY::IS_ENTITY_A_VEHICLE(MyCar))
				{
					if (!Invisible_Vehicle)
					{
						ENTITY::SET_ENTITY_VISIBLE(MyCar, false);
						Invisible_Vehicle = true;
					}
					else if (Invisible_Vehicle)
					{
						ENTITY::SET_ENTITY_VISIBLE(MyCar, true);
						Invisible_Vehicle = false;
						Invisible_Vehicle = !Invisible_Vehicle;
					}
				}
			}break;
		case 14:
			int MyVeh;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0))
			{
				MyVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);
				if (ENTITY::DOES_ENTITY_EXIST(MyVeh) && ENTITY::IS_ENTITY_A_VEHICLE(MyVeh) && !Toggle_Collision)
				{
					ENTITY::SET_ENTITY_COLLISION(MyVeh, 0, false);
					Toggle_Collision = true;
				}
				else if (ENTITY::DOES_ENTITY_EXIST(MyVeh) && ENTITY::IS_ENTITY_A_VEHICLE(MyVeh) && Toggle_Collision)
				{
					ENTITY::SET_ENTITY_COLLISION(MyVeh, 0, true);
					Toggle_Collision = false;
				}
				Toggle_Collision = !Toggle_Collision;
			} break;
		case 15: Toggle_Lower = !Toggle_Lower; break;
		case 16: Toggle_Lower2 = !Toggle_Lower2; break;
		case 17: break;
		case 18:
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(Vehicle, 4); break;
		case 19:
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(Vehicle2, 0); break;
		case 20: tWallCrawlVehLoop = !tWallCrawlVehLoop; break; //drawLasers
		case 21: drawLasers = !drawLasers; break; //drawLasers
		}
		break;
#pragma endregion
#pragma region Neons
	case Speedometer_Options:
		addTitle("Neons Menu");
		addBoolOption("Neons", Neons_);
		addNeonsOption("~b~Blue", 0, 43, 255);
		addNeonsOption("~r~Red", 255, 0, 0);
		addNeonsOption("~g~Green", 0, 255, 43);
		addNeonsOption("~o~Orange", 255, 128, 0);
		addNeonsOption("~p~Purple", 196, 0, 255);
		addBoolOption("~b~F~r~L~g~A~p~S~o~H~w~I~b~N~r~G", LoopNeons_);
		addBoolOption("Paint Car Flux", LoopNeons2_);
		addOption("---SPEDOOMETER---");
		addBoolOption("Paint Car Flux", LoopNeons2_);
		switch (getOption())
		{
		case 1: Neons_ = !Neons_; break;
		case 7: LoopNeons_ = !LoopNeons_; break;
		case 8: LoopNeons2_ = !LoopNeons2_;  break;
		}
		break;
#pragma endregion
#pragma region Handling Options
	case Handling_Options:

		addTitle("Handling Options");
		addBoolOption("Super Grip", SuperGrip); //1 
		addBoolOption("Nitrous Mod", superveh); //2
		addBoolOption("Drift Mod", drift); //3
		addBoolOption("Flying Vehicle", Flying_Vehicle); //4
		addBoolOption("Flying Vehicle v2", Flying_Vehicle2); //5
		addBoolOption("Flying Vehicle v3", flyingcar); //6
		switch (getOption())
		{
		case 1:
			if (SuperGrip)
				*(float*)0x82003A48 = 0.50f;
			if (!SuperGrip)
				*(float*)0x82003A48 = 0.16666667f;
			SuperGrip = !SuperGrip;
			break;
		case 2: superveh = !superveh; break;
		case 3:
			int vehicle;
			vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			if (!drift)
			{
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 0);
				NotifyAboveMap("~b~ Slidey car turned off."); //Slidey car turned off.
			}
			else if (drift)
			{
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, 1);
				NotifyAboveMap("~b~ Time to drift!, This is terrible (Not my fault it's using one of rockstars natives)");
			}
			drift = !drift;
			break;
		case 4: Flying_Vehicle = !Flying_Vehicle; break;
		case 5: Flying_Vehicle2 = !Flying_Vehicle2; break;
		case 6: flyingcar = !flyingcar; break;
		}
		break;
#pragma endregion
#pragma region Mod Shop
	case Mod_Shop:
		//
		ModShop_Sprite();
		addTitle("Mod Shop");
		addSubmenuOption("Performance", Performance_ModShop);
		addSubmenuOption("Body", Body_ModShop);
		addSubmenuOption("Horns", Horns_ModShop);
		addSubmenuOption("Wheels", Wheels_ModShop);
		addSubmenuOption("Armour", Armour_ModShop);
		addSubmenuOption("Window Tint", WindowTint_ModShop);
		addSubmenuOption("Neons Menu", NeonsMenu_ModShop);
		addSubmenuOption("Open/Remove Options", OpenRemove_ModShop);
		addBoolOption("Xenon Headlights", NULL);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Wheels
	case Wheels_ModShop:
		//
		ModShop_Sprite();
		addTitle("Wheels");
		addSubmenuOption("High End", HighEnd_ModShop); //1
		addSubmenuOption("Lowrider", Lowrider_ModShop); //2
		addSubmenuOption("Muscle", Muscle_ModShop); //3
		addSubmenuOption("Offroad", Offroad_ModShop); //4
		addSubmenuOption("Sport", Sport_ModShop); //5
		addSubmenuOption("SUV", SUV_ModShop); //6
		addSubmenuOption("Tuner", Tunner_ModShop); //7
		addSubmenuOption("Motorcycle", Motorcycle_ModShop); //8
		addSubmenuOption("Tyre Smoke", TireSmoke_ModShop); //9
		addOption("Custom Tires"); //10
		switch (getOption())
		{
		case 11:
			EnableVehicleMods();
			int SetCustomTires;
			SetCustomTires = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(SetCustomTires, 23, 0, 1);
			VEHICLE::SET_VEHICLE_MOD(SetCustomTires, 24, 0, 1); break;
		}
		break;
#pragma endregion
#pragma region Tyre Smoke
	case TireSmoke_ModShop:
		//
		ModShop_Sprite();
		addTitle("Tyre Smoke");
		addOption("Red Tyre Smoke"); //1
		addOption("Blue Tyre Smoke"); //2
		addOption("Green Tyre Smoke"); //3
		addOption("Purple Tyre Smoke"); //4
		addOption("Yellow Tyre Smoke"); //5
		addOption("Black Tyre Smoke"); //6
		addOption("White Tyre Smoke"); //7
		addOption("Pink Tyre Smoke"); //8
		addOption("Cyan Tyre Smoke"); //9
		addOption("Gold Tyre Smoke"); //10
		addOption("Orange Tyre Smoke"); //11
		addOption("Patriot Tyre Smoke"); //12
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int RedSmoke;
			RedSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(RedSmoke, 209, 0, 0); break;
		case 2:
			EnableVehicleMods();
			int GreenSmoke;
			GreenSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(GreenSmoke, 0, 255, 0); break;
		case 3:
			EnableVehicleMods();
			int BlueSmoke;
			BlueSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(BlueSmoke, 43, 0, 255); break;
		case 4:
			EnableVehicleMods();
			int PurpleSmoke;
			PurpleSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PurpleSmoke, 127, 0, 255); break;
		case 5:
			EnableVehicleMods();
			int YellowSmoke;
			YellowSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(YellowSmoke, 255, 255, 0); break;
		case 6:
			EnableVehicleMods();
			int BlackSmoke;
			BlackSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(BlackSmoke, 0, 0, 0); break;
		case 7:
			EnableVehicleMods();
			int WhiteSmoke;
			WhiteSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(WhiteSmoke, 255, 255, 255); break;
		case 8:
			EnableVehicleMods();
			int PinkSmoke;
			PinkSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PinkSmoke, 255, 20, 174); break;
		case 9:
			EnableVehicleMods();
			int CyanSmoke;
			CyanSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(CyanSmoke, 0, 255, 255); break;
		case 10:
			EnableVehicleMods();
			int GoldSmoke;
			GoldSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(GoldSmoke, 218, 165, 32); break;
		case 11:
			EnableVehicleMods();
			int OrangeSmoke;
			OrangeSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(OrangeSmoke, 255, 140, 0); break;
		case 12:
			EnableVehicleMods();
			int PatriotSmoke;
			PatriotSmoke = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PatriotSmoke, 0, 0, 0); break;
		}
		break;
#pragma endregion
#pragma region High End
	case HighEnd_ModShop:
		//
		ModShop_Sprite();
		addTitle("High End");
		addOption("Stock Wheels"); //1
		addOption("Shadow"); //2
		addOption("Hypher"); //3
		addOption("Blade"); //4
		addOption("Diamond"); //5
		addOption("Supa Gee"); //6
		addOption("Chromatic Z"); //7
		addOption("Mercie Ch.Lip"); //8
		addOption("Obey RS"); //9
		addOption("GT Chrome"); //10
		addOption("Cheetah RR"); //11
		addOption("Solar"); //12
		addOption("Split Ten"); //13
		addOption("Dash VIP"); //14
		addOption("LozSpeed Ten"); //15
		addOption("Carbon Inferno"); //16
		addOption("Carbon Shadow"); //17
		addOption("Carbonic Z"); //18
		addOption("Carbon Solar"); //19
		addOption("Cheetah Carbon R"); //20
		addOption("Carbon S Racer"); //21
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int HEStockWheels;
			HEStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEStockWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(HEStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int HEShadowWheels;
			HEShadowWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEShadowWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEShadowWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(HEShadowWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int HEHypherWheels;
			HEHypherWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEHypherWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEHypherWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(HEHypherWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int HEBladeWheels;
			HEBladeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEBladeWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEBladeWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(HEBladeWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int HEDiamondWheels;
			HEDiamondWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEDiamondWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEDiamondWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(HEDiamondWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int HESupaGeeWheels;
			HESupaGeeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HESupaGeeWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HESupaGeeWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(HESupaGeeWheels, 23, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int HEChromaticZWheels;
			HEChromaticZWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEChromaticZWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEChromaticZWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(HEChromaticZWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int HEMercieChLipWheels;
			HEMercieChLipWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEMercieChLipWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEMercieChLipWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(HEMercieChLipWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int HEObeyRSWheels;
			HEObeyRSWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEObeyRSWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEObeyRSWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(HEObeyRSWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int HEGTChromeWheels;
			HEGTChromeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEGTChromeWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEGTChromeWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(HEGTChromeWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int HECheetahRRWheels;
			HECheetahRRWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECheetahRRWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECheetahRRWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(HECheetahRRWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int HESolarWheels;
			HESolarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HESolarWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HESolarWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(HESolarWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int HESplitTenWheels;
			HESplitTenWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HESplitTenWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HESplitTenWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(HESplitTenWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int HEDashVIPWheels;
			HEDashVIPWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HEDashVIPWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HEDashVIPWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(HEDashVIPWheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int HELozSpeedTenWheels;
			HELozSpeedTenWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HELozSpeedTenWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HELozSpeedTenWheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(HELozSpeedTenWheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int HECarbonInfernoWheels;
			HECarbonInfernoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECarbonInfernoWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECarbonInfernoWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(HECarbonInfernoWheels, 24, 14, 0); break;
		case 17:
			EnableVehicleMods();
			int HECarbonShadowWheels;
			HECarbonShadowWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECarbonShadowWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECarbonShadowWheels, 23, 15, 0);
			VEHICLE::SET_VEHICLE_MOD(HECarbonShadowWheels, 24, 15, 0); break;
		case 18:
			EnableVehicleMods();
			int HECarbonicZWheels;
			HECarbonicZWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECarbonicZWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECarbonicZWheels, 23, 16, 0);
			VEHICLE::SET_VEHICLE_MOD(HECarbonicZWheels, 24, 16, 0); break;
		case 19:
			EnableVehicleMods();
			int HECarbonSolarWheels;
			HECarbonSolarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECarbonSolarWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECarbonSolarWheels, 23, 17, 0);
			VEHICLE::SET_VEHICLE_MOD(HECarbonSolarWheels, 24, 17, 0); break;
		case 20:
			EnableVehicleMods();
			int HECheetahCarbonRWheels;
			HECheetahCarbonRWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECheetahCarbonRWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECheetahCarbonRWheels, 23, 18, 0);
			VEHICLE::SET_VEHICLE_MOD(HECheetahCarbonRWheels, 24, 18, 0); break;
		case 21:
			EnableVehicleMods();
			int HECarbonSRacerWheels;
			HECarbonSRacerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(HECarbonSRacerWheels, 7);
			VEHICLE::SET_VEHICLE_MOD(HECarbonSRacerWheels, 23, 19, 0);
			VEHICLE::SET_VEHICLE_MOD(HECarbonSRacerWheels, 24, 19, 0); break;
		}
		break;
#pragma endregion
#pragma region Lowrider
	case Lowrider_ModShop:
		ModShop_Sprite();
		addTitle("Lowrider");
		addOption("Stock Wheels"); //1
		addOption("Flare"); //2
		addOption("Wired"); //3
		addOption("Triple Golds"); //4
		addOption("Big Worm"); //5
		addOption("Seven Fives"); //6
		addOption("Split Six"); //7
		addOption("Fresh Mesh"); //8
		addOption("Lead Sled"); //9
		addOption("Turbine"); //10
		addOption("Super Fin"); //11
		addOption("Classic Rod"); //12
		addOption("Dollar"); //13
		addOption("Dukes"); //14
		addOption("Low Five"); //15
		addOption("Gooch"); //16
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int LStockWheels;
			LStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LStockWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(LStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int LFlareWheels;
			LFlareWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LFlareWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LFlareWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(LFlareWheels, 23, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int LWiredWheels;
			LWiredWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LWiredWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LWiredWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(LWiredWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int LTripleGoldsWheels;
			LTripleGoldsWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LTripleGoldsWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LTripleGoldsWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(LTripleGoldsWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int LBigWormWheels;
			LBigWormWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LBigWormWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LBigWormWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(LBigWormWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int LSevenFivesWheels;
			LSevenFivesWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LSevenFivesWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LSevenFivesWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(LSevenFivesWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int LSplitSixWheels;
			LSplitSixWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LSplitSixWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LSplitSixWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(LSplitSixWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int LFreshMeshWheels;
			LFreshMeshWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LFreshMeshWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LFreshMeshWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(LFreshMeshWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int LLeadSledWheels;
			LLeadSledWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LLeadSledWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LLeadSledWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(LLeadSledWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int LTurbineWheels;
			LTurbineWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LTurbineWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LTurbineWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(LTurbineWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int LSuperFinWheels;
			LSuperFinWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LSuperFinWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LSuperFinWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(LSuperFinWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int LClassicRodWheels;
			LClassicRodWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LClassicRodWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LClassicRodWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(LClassicRodWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int LDollarWheels;
			LDollarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LDollarWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LDollarWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(LDollarWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int LDukesWheels;
			LDukesWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LDukesWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LDukesWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(LDukesWheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int LLowFiveWheels;
			LLowFiveWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LLowFiveWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LLowFiveWheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(LLowFiveWheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int LGoochWheels;
			LGoochWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(LGoochWheels, 2);
			VEHICLE::SET_VEHICLE_MOD(LGoochWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(LGoochWheels, 24, 14, 0); break;
		}
		break;
#pragma endregion
#pragma region Muscle
	case Muscle_ModShop:
		//
		ModShop_Sprite();
		addTitle("Muscle");
		addOption("Stock Wheels"); //1
		addOption("Classic Five"); //2
		addOption("Dukes"); //3
		addOption("Muscle Freak"); //4
		addOption("Kracka"); //5
		addOption("Azreal"); //6
		addOption("Mecha"); //7
		addOption("Black Top"); //8
		addOption("Drag SPL"); //9
		addOption("Revolver"); //10
		addOption("Classic Rod"); //11
		addOption("Fairlie"); //12
		addOption("Spooner"); //13
		addOption("Five Star"); //14
		addOption("Old School"); //15
		addOption("El Jefe"); //16
		addOption("Dodman"); //17
		addOption("Six Gun"); //18
		addOption("Mercenary"); //19
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int MStockWheels;
			MStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MStockWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(MStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int MClassicFiveWheels;
			MClassicFiveWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MClassicFiveWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MClassicFiveWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(MClassicFiveWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int MDukesWheels;
			MDukesWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MDukesWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MDukesWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(MDukesWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int MMuscleFreakWheels;
			MMuscleFreakWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MMuscleFreakWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MMuscleFreakWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(MMuscleFreakWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int MKrackaWheels;
			MKrackaWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MKrackaWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MKrackaWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(MKrackaWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int MAzrealWheels;
			MAzrealWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MAzrealWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MAzrealWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(MAzrealWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int MMechaWheels;
			MMechaWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MMechaWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MMechaWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(MMechaWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int MBlackTopWheels;
			MBlackTopWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MBlackTopWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MBlackTopWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(MBlackTopWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int MDragSPLWheels;
			MDragSPLWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MDragSPLWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MDragSPLWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(MDragSPLWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int MRevolverWheels;
			MRevolverWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MRevolverWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MRevolverWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(MRevolverWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int MClassicRodWheels;
			MClassicRodWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MClassicRodWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MClassicRodWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(MClassicRodWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int MFairlieWheels;
			MFairlieWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MFairlieWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MFairlieWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(MFairlieWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int MSpoonerWheels;
			MSpoonerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MSpoonerWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MSpoonerWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(MSpoonerWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int MFiveStarWheels;
			MFiveStarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MFiveStarWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MFiveStarWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(MFiveStarWheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int MOldSchoolWheels;
			MOldSchoolWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MOldSchoolWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MOldSchoolWheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(MOldSchoolWheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int MElJefeWheels;
			MElJefeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MElJefeWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MElJefeWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(MElJefeWheels, 24, 14, 0); break;
		case 17:
			EnableVehicleMods();
			int MDodmanWheels;
			MDodmanWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MDodmanWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MDodmanWheels, 23, 15, 0);
			VEHICLE::SET_VEHICLE_MOD(MDodmanWheels, 24, 15, 0); break;
		case 18:
			EnableVehicleMods();
			int MSixGunWheels;
			MSixGunWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MSixGunWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MSixGunWheels, 23, 16, 0);
			VEHICLE::SET_VEHICLE_MOD(MSixGunWheels, 24, 16, 0); break;
		case 19:
			EnableVehicleMods();
			int MMercenaryWheels;
			MMercenaryWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(MMercenaryWheels, 1);
			VEHICLE::SET_VEHICLE_MOD(MMercenaryWheels, 23, 17, 0);
			VEHICLE::SET_VEHICLE_MOD(MMercenaryWheels, 24, 17, 0); break;
		}
		break;
#pragma endregion
#pragma region Offroad
	case Offroad_ModShop:
		//
		ModShop_Sprite();
		addTitle("OffRoad");
		addOption("Stock Wheels"); //1
		addOption("Raider"); //2
		addOption("Mudslinger"); //3
		addOption("Nevis"); //4
		addOption("Cairngorm"); //5
		addOption("Amazon"); //6
		addOption("Challenge"); //7
		addOption("Dune Basher"); //8
		addOption("Classic Rod"); //9
		addOption("Five Star"); //10
		addOption("Rock Crawler"); //11
		addOption("Mil Spec Steelie"); //12
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int ORStockWheels;
			ORStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORStockWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(ORStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int ORRaiderWheels;
			ORRaiderWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORRaiderWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORRaiderWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(ORRaiderWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int ORMudslingerWheels;
			ORMudslingerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORMudslingerWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORMudslingerWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(ORMudslingerWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int ORNevisWheels;
			ORNevisWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORNevisWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORNevisWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(ORNevisWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int ORCairngormWheels;
			ORCairngormWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORCairngormWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORCairngormWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(ORCairngormWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int ORAmazonWheels;
			ORAmazonWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORAmazonWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORAmazonWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(ORAmazonWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int ORChallengerWheels;
			ORChallengerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORChallengerWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORChallengerWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(ORChallengerWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int ORDuneBasherWheels;
			ORDuneBasherWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORDuneBasherWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORDuneBasherWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(ORDuneBasherWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int ORFiveStarWheels;
			ORFiveStarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORFiveStarWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORFiveStarWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(ORFiveStarWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int ORRockCrawlerWheels;
			ORRockCrawlerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORRockCrawlerWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORRockCrawlerWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(ORRockCrawlerWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int ORMilSpecSteelieRodWheels;
			ORMilSpecSteelieRodWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(ORMilSpecSteelieRodWheels, 4);
			VEHICLE::SET_VEHICLE_MOD(ORMilSpecSteelieRodWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(ORMilSpecSteelieRodWheels, 24, 9, 0); break;
		}
		break;
#pragma endregion
#pragma region Sport
	case Sport_ModShop:
		ModShop_Sprite();
		addTitle("Sport");
		addOption("Stock Wheels"); //1
		addOption("Inferno"); //2
		addOption("Deep Five"); //3
		addOption("Lozspeed Mk.V"); //4
		addOption("Diamond Cut"); //5
		addOption("Chrono"); //6
		addOption("Feroci RR"); //7
		addOption("FiftyNine"); //8
		addOption("Mercie"); //9
		addOption("Synthetic Z"); //10
		addOption("Organic Type 0"); //11
		addOption("Endo v.1"); //12
		addOption("GT One"); //13
		addOption("Duper 7"); //14
		addOption("Uzer"); //15
		addOption("GroundRide"); //16
		addOption("S Racer"); //17
		addOption("Venum"); //18
		addOption("Cosmo"); //19
		addOption("Dash VIP"); //20
		addOption("Ice Kid"); //21
		addOption("Ruff Weld"); //22
		addOption("Wangan Master"); //23
		addOption("Super Five"); //24
		addOption("Endo v2"); //25
		addOption("Split Six"); //26
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int SStockWheels;
			SStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SStockWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(SStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int SInfernoWheels;
			SInfernoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SInfernoWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SInfernoWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(SInfernoWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int SDeepFiveWheels;
			SDeepFiveWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDeepFiveWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SDeepFiveWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(SDeepFiveWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int SLozspeedMkVWheels;
			SLozspeedMkVWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SLozspeedMkVWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SLozspeedMkVWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(SLozspeedMkVWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int SDiamondCutWheels;
			SDiamondCutWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDiamondCutWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SDiamondCutWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(SDiamondCutWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int SChronoWheels;
			SChronoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SChronoWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SChronoWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(SChronoWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int SFerociRRWheels;
			SFerociRRWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SFerociRRWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SFerociRRWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(SFerociRRWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int SFiftyNineWheels;
			SFiftyNineWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SFiftyNineWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SFiftyNineWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(SFiftyNineWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int SMercieWheels;
			SMercieWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SMercieWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SMercieWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(SMercieWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int SSyntheticZWheels;
			SSyntheticZWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSyntheticZWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SSyntheticZWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(SSyntheticZWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int SOrganicType0Wheels;
			SOrganicType0Wheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SOrganicType0Wheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SOrganicType0Wheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(SOrganicType0Wheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int SEndov1Wheels;
			SEndov1Wheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SEndov1Wheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SEndov1Wheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(SEndov1Wheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int SGTOneWheels;
			SGTOneWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SGTOneWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SGTOneWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(SGTOneWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int SDuper7Wheels;
			SDuper7Wheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDuper7Wheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SDuper7Wheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(SDuper7Wheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int SUzerWheels;
			SUzerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SUzerWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SUzerWheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(SUzerWheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int SGroundRideWheels;
			SGroundRideWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SGroundRideWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SGroundRideWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(SGroundRideWheels, 24, 14, 0); break;
		case 17:
			EnableVehicleMods();
			int SSRacerWheels;
			SSRacerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSRacerWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SSRacerWheels, 23, 15, 0);
			VEHICLE::SET_VEHICLE_MOD(SSRacerWheels, 24, 15, 0); break;
		case 18:
			EnableVehicleMods();
			int SVenumWheels;
			SVenumWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SVenumWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SVenumWheels, 23, 16, 0);
			VEHICLE::SET_VEHICLE_MOD(SVenumWheels, 24, 16, 0); break;
		case 19:
			EnableVehicleMods();
			int SCosmoWheels;
			SCosmoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SCosmoWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SCosmoWheels, 23, 17, 0);
			VEHICLE::SET_VEHICLE_MOD(SCosmoWheels, 24, 17, 0); break;
		case 20:
			EnableVehicleMods();
			int SDashVIPWheels;
			SDashVIPWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDashVIPWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SDashVIPWheels, 23, 18, 0);
			VEHICLE::SET_VEHICLE_MOD(SDashVIPWheels, 24, 18, 0); break;
		case 21:
			EnableVehicleMods();
			int SIceKidWheels;
			SIceKidWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SIceKidWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SIceKidWheels, 23, 19, 0);
			VEHICLE::SET_VEHICLE_MOD(SIceKidWheels, 24, 19, 0);  break;
		case 22:
			EnableVehicleMods();
			int SRuffWeldWheels;
			SRuffWeldWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SRuffWeldWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SRuffWeldWheels, 23, 20, 0);
			VEHICLE::SET_VEHICLE_MOD(SRuffWeldWheels, 24, 20, 0); break;
		case 23:
			EnableVehicleMods();
			int SWanganMasterWheels;
			SWanganMasterWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SWanganMasterWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SWanganMasterWheels, 23, 21, 0);
			VEHICLE::SET_VEHICLE_MOD(SWanganMasterWheels, 24, 21, 0); break;
		case 24:
			EnableVehicleMods();
			int SSuperFiveWheels;
			SSuperFiveWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSuperFiveWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SSuperFiveWheels, 23, 22, 0);
			VEHICLE::SET_VEHICLE_MOD(SSuperFiveWheels, 24, 22, 0); break;
		case 25:
			EnableVehicleMods();
			int SEndov2Wheels;
			SEndov2Wheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SEndov2Wheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SEndov2Wheels, 23, 23, 0);
			VEHICLE::SET_VEHICLE_MOD(SEndov2Wheels, 23, 23, 0); break;
		case 26:
			EnableVehicleMods();
			int SSplitSixWheels;
			SSplitSixWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSplitSixWheels, 0);
			VEHICLE::SET_VEHICLE_MOD(SSplitSixWheels, 23, 24, 0);
			VEHICLE::SET_VEHICLE_MOD(SSplitSixWheels, 24, 24, 0); break;
		}
		break;
#pragma endregion
#pragma region SUV
	case SUV_ModShop:
		ModShop_Sprite();
		addTitle("SUV");
		addOption("Stock Wheels"); //1
		addOption("VIP"); //2
		addOption("Benefactor"); //3
		addOption("Cosmo"); //4
		addOption("Bippu"); //5
		addOption("Royal Six"); //6 
		addOption("Fagorme"); //7
		addOption("Deluxe"); //8
		addOption("Iced Out"); //9
		addOption("Cognoscenti"); //10
		addOption("LozSpeed Ten"); //11
		addOption("Supernova"); //12
		addOption("Obey RS"); //13
		addOption("LozSpeed Baller"); //14 
		addOption("Extravaganzo"); //15
		addOption("Split Six"); //16
		addOption("Empowered"); //17
		addOption("Sunrise"); //18
		addOption("Dash VIP"); //19
		addOption("Cutter"); //20
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int SStockWheels;
			SStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SStockWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(SStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int SVIPWheels;
			SVIPWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SVIPWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SVIPWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(SVIPWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int SBenefactorWheels;
			SBenefactorWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SBenefactorWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SBenefactorWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(SBenefactorWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int SCosmoWheels;
			SCosmoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SCosmoWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SCosmoWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(SCosmoWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int SBippuWheels;
			SBippuWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SBippuWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SBippuWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(SBippuWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int SRoyalSixWheels;
			SRoyalSixWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SRoyalSixWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SRoyalSixWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(SRoyalSixWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int SFagormeWheels;
			SFagormeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SFagormeWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SFagormeWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(SFagormeWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int SDeluxeWheels;
			SDeluxeWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDeluxeWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SDeluxeWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(SDeluxeWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int SIcedOutWheels;
			SIcedOutWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SIcedOutWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SIcedOutWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(SIcedOutWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int SCognoscentiWheels;
			SCognoscentiWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SCognoscentiWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SCognoscentiWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(SCognoscentiWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int SLozSpeedTenWheels;
			SLozSpeedTenWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SLozSpeedTenWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SLozSpeedTenWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(SLozSpeedTenWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int SSupernovaWheels;
			SSupernovaWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSupernovaWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SSupernovaWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(SSupernovaWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int SObeyRSWheels;
			SObeyRSWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SObeyRSWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SObeyRSWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(SObeyRSWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int SLozSpeedBallerWheels;
			SLozSpeedBallerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SLozSpeedBallerWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SLozSpeedBallerWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(SLozSpeedBallerWheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int SExtravaganzoWheels;
			SExtravaganzoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SExtravaganzoWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SExtravaganzoWheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(SExtravaganzoWheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int SSplitSixWheels;
			SSplitSixWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSplitSixWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SSplitSixWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(SSplitSixWheels, 24, 14, 0); break;
		case 17:
			EnableVehicleMods();
			int SEmpoweredWheels;
			SEmpoweredWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SEmpoweredWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SEmpoweredWheels, 23, 15, 0); break;
		case 18:
			EnableVehicleMods();
			int SSunriseWheels;
			SSunriseWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SSunriseWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SSunriseWheels, 23, 16, 0);
			VEHICLE::SET_VEHICLE_MOD(SSunriseWheels, 24, 16, 0); break;
		case 19:
			EnableVehicleMods();
			int SDashVIPWheels;
			SDashVIPWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SDashVIPWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SDashVIPWheels, 23, 17, 0);
			VEHICLE::SET_VEHICLE_MOD(SDashVIPWheels, 24, 17, 0); break;
		case 20:
			EnableVehicleMods();
			int SCutterWheels;
			SCutterWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(SCutterWheels, 3);
			VEHICLE::SET_VEHICLE_MOD(SCutterWheels, 23, 18, 0);
			VEHICLE::SET_VEHICLE_MOD(SCutterWheels, 24, 18, 0); break;
		}
		break;
#pragma endregion
#pragma region Tuner
	case Tunner_ModShop:
		ModShop_Sprite();
		addTitle("Tuner");
		addOption("Stock Wheels"); //1
		addOption("Cosmo"); //2
		addOption("Super Mesh"); //3
		addOption("Outsider"); //4
		addOption("Rollas"); //5
		addOption("Driftmeister"); //6
		addOption("Slicer"); //7
		addOption("El Quatro"); //8
		addOption("Dubbed"); //9
		addOption("Five Star"); //10
		addOption("Slideways"); //11
		addOption("Apex"); //12
		addOption("Stanced EG"); //13
		addOption("Countersteer"); //14
		addOption("Endo v.1"); //15
		addOption("Endo v.2 Dish"); //16
		addOption("Gruppe Z"); //17
		addOption("Choku-Dori"); //18
		addOption("Chicane"); //19
		addOption("Saisoku"); //20
		addOption("Dished Eight"); //21
		addOption("Fujiwara"); //22
		addOption("Zokusha"); //23
		addOption("Battle VIII"); //24
		addOption("Rally Master"); //25
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int TStockWheels;
			TStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TStockWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(TStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int TCosmoWheels;
			TCosmoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TCosmoWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TCosmoWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(TCosmoWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int TSuperMeshWheels;
			TSuperMeshWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSuperMeshWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TSuperMeshWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(TSuperMeshWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int TOutsiderWheels;
			TOutsiderWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TOutsiderWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TOutsiderWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(TOutsiderWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int TRollasWheels;
			TRollasWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TRollasWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TRollasWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(TRollasWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int TDriftmeisterWheels;
			TDriftmeisterWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TDriftmeisterWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TDriftmeisterWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(TDriftmeisterWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int TSlicerWheels;
			TSlicerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSlicerWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TSlicerWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(TSlicerWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int TElQuatroWheels;
			TElQuatroWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TElQuatroWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TElQuatroWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(TElQuatroWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int TDubbedWheels;
			TDubbedWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TDubbedWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TDubbedWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(TDubbedWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int TFiveStarWheels;
			TFiveStarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TFiveStarWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TFiveStarWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(TFiveStarWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int TSlidewaysWheels;
			TSlidewaysWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSlidewaysWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TSlidewaysWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(TSlidewaysWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int TApexWheels;
			TApexWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TApexWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TApexWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(TApexWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int TStancedEGWheels;
			TStancedEGWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TStancedEGWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TStancedEGWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(TStancedEGWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int TCountersteerWheels;
			TCountersteerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TCountersteerWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TCountersteerWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(TCountersteerWheels, 24, 12, 0); break;
		case 15:
			EnableVehicleMods();
			int TEndov1Wheels;
			TEndov1Wheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TEndov1Wheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TEndov1Wheels, 23, 13, 0);
			VEHICLE::SET_VEHICLE_MOD(TEndov1Wheels, 24, 13, 0); break;
		case 16:
			EnableVehicleMods();
			int TEndov2DishWheels;
			TEndov2DishWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TEndov2DishWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TEndov2DishWheels, 23, 14, 0);
			VEHICLE::SET_VEHICLE_MOD(TEndov2DishWheels, 24, 14, 0); break;
		case 17:
			EnableVehicleMods();
			int TGruppeZWheels;
			TGruppeZWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TGruppeZWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TGruppeZWheels, 23, 15, 0);
			VEHICLE::SET_VEHICLE_MOD(TGruppeZWheels, 24, 15, 0); break;
		case 18:
			EnableVehicleMods();
			int TChokuDoriWheels;
			TChokuDoriWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TChokuDoriWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TChokuDoriWheels, 23, 16, 0);
			VEHICLE::SET_VEHICLE_MOD(TChokuDoriWheels, 24, 16, 0); break;
		case 19:
			EnableVehicleMods();
			int TChicaneWheels;
			TChicaneWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TChicaneWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TChicaneWheels, 23, 17, 0);
			VEHICLE::SET_VEHICLE_MOD(TChicaneWheels, 24, 17, 0); break;
		case 20:
			EnableVehicleMods();
			int TSaisokuWheels;
			TSaisokuWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSaisokuWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TSaisokuWheels, 23, 18, 0);
			VEHICLE::SET_VEHICLE_MOD(TSaisokuWheels, 24, 18, 0); break;
		case 21:
			EnableVehicleMods();
			int TDishedEightWheels;
			TDishedEightWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TDishedEightWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TDishedEightWheels, 23, 19, 0);
			VEHICLE::SET_VEHICLE_MOD(TDishedEightWheels, 24, 19, 0); break;
		case 22:
			EnableVehicleMods();
			int TFujiwaraWheels;
			TFujiwaraWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TFujiwaraWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TFujiwaraWheels, 23, 20, 0);
			VEHICLE::SET_VEHICLE_MOD(TFujiwaraWheels, 24, 20, 0); break;
		case 23:
			EnableVehicleMods();
			int TZokushaWheels;
			TZokushaWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TZokushaWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TZokushaWheels, 23, 21, 0);
			VEHICLE::SET_VEHICLE_MOD(TZokushaWheels, 24, 21, 0); break;
		case 24:
			EnableVehicleMods();
			int TBattleVIIIWheels;
			TBattleVIIIWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TBattleVIIIWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TBattleVIIIWheels, 23, 22, 0);
			VEHICLE::SET_VEHICLE_MOD(TBattleVIIIWheels, 24, 22, 0); break;
		case 25:
			EnableVehicleMods();
			int TRallyMasterWheels;
			TRallyMasterWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TRallyMasterWheels, 5);
			VEHICLE::SET_VEHICLE_MOD(TRallyMasterWheels, 23, 23, 0);
			VEHICLE::SET_VEHICLE_MOD(TRallyMasterWheels, 24, 23, 0); break;
		}
		break;
#pragma endregion
#pragma region Motorcycle
	case Motorcycle_ModShop:
		ModShop_Sprite();
		addTitle("Motorcycle");
		addOption("Stock Wheels"); //1
		addOption("Speedway"); //2
		addOption("Street Special"); //3
		addOption("Racer"); //4
		addOption("Track Star"); //5
		addOption("Overlord"); //6
		addOption("Trident"); //7
		addOption("Triple Threat"); //8
		addOption("Stilleto"); //9
		addOption("Wires"); //10
		addOption("Bobber"); //11
		addOption("Solidus"); //12
		addOption("Ice Shield"); //13
		addOption("Loops"); //14
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int TStockWheels;
			TStockWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TStockWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TStockWheels, 23, -1, 0);
			VEHICLE::SET_VEHICLE_MOD(TStockWheels, 24, -1, 0); break;
		case 2:
			EnableVehicleMods();
			int TCosmoWheels;
			TCosmoWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TCosmoWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TCosmoWheels, 23, 0, 0);
			VEHICLE::SET_VEHICLE_MOD(TCosmoWheels, 24, 0, 0); break;
		case 3:
			EnableVehicleMods();
			int TSuperMeshWheels;
			TSuperMeshWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSuperMeshWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TSuperMeshWheels, 23, 1, 0);
			VEHICLE::SET_VEHICLE_MOD(TSuperMeshWheels, 24, 1, 0); break;
		case 4:
			EnableVehicleMods();
			int TOutsiderWheels;
			TOutsiderWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TOutsiderWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TOutsiderWheels, 23, 2, 0);
			VEHICLE::SET_VEHICLE_MOD(TOutsiderWheels, 24, 2, 0); break;
		case 5:
			EnableVehicleMods();
			int TRollasWheels;
			TRollasWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TRollasWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TRollasWheels, 23, 3, 0);
			VEHICLE::SET_VEHICLE_MOD(TRollasWheels, 24, 3, 0); break;
		case 6:
			EnableVehicleMods();
			int TDriftmeisterWheels;
			TDriftmeisterWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TDriftmeisterWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TDriftmeisterWheels, 23, 4, 0);
			VEHICLE::SET_VEHICLE_MOD(TDriftmeisterWheels, 24, 4, 0); break;
		case 7:
			EnableVehicleMods();
			int TSlicerWheels;
			TSlicerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSlicerWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TSlicerWheels, 23, 5, 0);
			VEHICLE::SET_VEHICLE_MOD(TSlicerWheels, 24, 5, 0); break;
		case 8:
			EnableVehicleMods();
			int TElQuatroWheels;
			TElQuatroWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TElQuatroWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TElQuatroWheels, 23, 6, 0);
			VEHICLE::SET_VEHICLE_MOD(TElQuatroWheels, 24, 6, 0); break;
		case 9:
			EnableVehicleMods();
			int TDubbedWheels;
			TDubbedWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TDubbedWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TDubbedWheels, 23, 7, 0);
			VEHICLE::SET_VEHICLE_MOD(TDubbedWheels, 24, 7, 0); break;
		case 10:
			EnableVehicleMods();
			int TFiveStarWheels;
			TFiveStarWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TFiveStarWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TFiveStarWheels, 23, 8, 0);
			VEHICLE::SET_VEHICLE_MOD(TFiveStarWheels, 24, 8, 0); break;
		case 11:
			EnableVehicleMods();
			int TSlidewaysWheels;
			TSlidewaysWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TSlidewaysWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TSlidewaysWheels, 23, 9, 0);
			VEHICLE::SET_VEHICLE_MOD(TSlidewaysWheels, 24, 9, 0); break;
		case 12:
			EnableVehicleMods();
			int TApexWheels;
			TApexWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TApexWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TApexWheels, 23, 10, 0);
			VEHICLE::SET_VEHICLE_MOD(TApexWheels, 24, 10, 0); break;
		case 13:
			EnableVehicleMods();
			int TStancedEGWheels;
			TStancedEGWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TStancedEGWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TStancedEGWheels, 23, 11, 0);
			VEHICLE::SET_VEHICLE_MOD(TStancedEGWheels, 24, 11, 0); break;
		case 14:
			EnableVehicleMods();
			int TCountersteerWheels;
			TCountersteerWheels = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(TCountersteerWheels, 6);
			VEHICLE::SET_VEHICLE_MOD(TCountersteerWheels, 23, 12, 0);
			VEHICLE::SET_VEHICLE_MOD(TCountersteerWheels, 24, 12, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Armour
	case Armour_ModShop:
		ModShop_Sprite();
		addTitle("Armour");
		addOption("20% Armour");
		addOption("40% Armour");
		addOption("60% Armour");
		addOption("80% Armour");
		addOption("100% Armour");
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Armour20;
			Armour20 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Armour20, 16, 0, 0);
			break;
		case 2:
			EnableVehicleMods();
			int Armour40;
			Armour40 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Armour40, 16, 1, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Armour60;
			Armour60 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Armour60, 16, 2, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Armour80;
			Armour80 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Armour80, 16, 3, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Armour100;
			Armour100 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Armour100, 16, 4, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Window Tint
	case WindowTint_ModShop:
		ModShop_Sprite();
		addTitle("Window Tint");
		addOption("Stock Window Tint");
		addOption("Limo Window Tint");
		addOption("Dark Window Tint");
		addOption("Light Window Tint");
		addOption("Fully Black Window Tint");
		addOption("Green Window Tint");
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockWindowTint;
			StockWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(StockWindowTint, -1); break;
		case 2:
			EnableVehicleMods();
			int LimoWindowTint;
			LimoWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(LimoWindowTint, 1); break;
		case 3:
			EnableVehicleMods();
			int DarkWindowTint;
			DarkWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(DarkWindowTint, 2); break;
		case 4:
			EnableVehicleMods();
			int LightWindowTint;
			LightWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(LightWindowTint, 3); break;
		case 5:
			EnableVehicleMods();
			int FullyBlackedWindowTint;
			FullyBlackedWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(FullyBlackedWindowTint, 5); break;
		case 6:
			EnableVehicleMods();
			int GreenWindowTint;
			GreenWindowTint = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(GreenWindowTint, 6); break;
		}
		break;
#pragma endregion
#pragma region Body
	case Body_ModShop:
		ModShop_Sprite();
		addTitle("Body");
		addSubmenuOption("Front Bumbers", FbMenu);
		addSubmenuOption("Rear Bumpers", RbMenu);
		addSubmenuOption("Side Skirts", SkMenu);
		addSubmenuOption("Interiors/Chassis", InteriorMenu);
		addSubmenuOption("Hoods", HoodMenu);
		addSubmenuOption("Left Fenders", LFenderMenu);
		addSubmenuOption("Right Fenders", RFenderMenu);
		addSubmenuOption("Roofs", RoofMenu);
		addSubmenuOption("Spoilers", SpoilerMenu);
		addSubmenuOption("Grills", GrillMenu);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Front Bumbers
	case FbMenu:
		ModShop_Sprite();
		addTitle("Front Bumbers");
		addOption("Stock Front Bumper"); //1
		addOption("Front Bumper 1"); //2
		addOption("Front Bumper 2"); //3
		addOption("Front Bumper 3"); //4
		addOption("Front Bumper 4"); //5
		addOption("Front Bumper 5"); //6
		addOption("Front Bumper 6"); //7
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockFrontBumper;
			StockFrontBumper = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockFrontBumper, 1);
			break;
		case 2:
			EnableVehicleMods();
			int FrontBumper1;
			FrontBumper1 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper1, 1, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int FrontBumper2;
			FrontBumper2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper2, 1, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int FrontBumper3;
			FrontBumper3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper3, 1, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int FrontBumper4;
			FrontBumper4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper4, 1, 3, 0);
			break;
		case 6:
			EnableVehicleMods();
			int FrontBumper5;
			FrontBumper5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper5, 1, 4, 0);
			break;
		case 7:
			EnableVehicleMods();
			int FrontBumper6;
			FrontBumper6 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(FrontBumper6, 1, 5, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Rear Bumpers
	case RbMenu:
		ModShop_Sprite();
		addTitle("Rear Bumpers");
		addOption("Stock Rear Bumper"); //1
		addOption("Rear Bumper 1"); //2
		addOption("Rear Bumper 2"); //3
		addOption("Rear Bumper 3"); //4
		addOption("Rear Bumper 4"); //5
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockReartBumper;
			StockReartBumper = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockReartBumper, 2);
			break;
		case 2:
			EnableVehicleMods();
			int RearBumper2;
			RearBumper2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RearBumper2, 2, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int RearBumper3;
			RearBumper3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RearBumper3, 2, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int RearBumper4;
			RearBumper4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RearBumper4, 2, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int RearBumper5;
			RearBumper5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RearBumper5, 2, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Side Skirts
	case SkMenu:
		ModShop_Sprite();
		addTitle("Side Skirts");
		addOption("Stock Side Skirts"); //1
		addOption("Side Skirts 1"); //2
		addOption("Side Skirts 2"); //3
		addOption("Side Skirts 3"); //4
		addOption("Side Skirts 4"); //5
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockSk;
			StockSk = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockSk, 3);
			break;
		case 2:
			EnableVehicleMods();
			int SideSk2;
			SideSk2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(SideSk2, 3, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int SideSk3;
			SideSk3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(SideSk3, 3, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int SideSk4;
			SideSk4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(SideSk4, 3, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int SideSk5;
			SideSk5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(SideSk5, 3, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Interiors/Chassis
	case InteriorMenu:
		ModShop_Sprite();
		addTitle("Interiors/Chassis");
		addOption("Stock Interior/Chassis"); //1
		addOption("Interior/Chassis 1"); //2
		addOption("Interior/Chassis 2"); //3
		addOption("Interior/Chassis 3"); //4
		addOption("Interior/Chassis 4"); //5
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockInteriorChassis;
			StockInteriorChassis = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockInteriorChassis, 5);
			break;
		case 2:
			EnableVehicleMods();
			int InteriorChassis2;
			InteriorChassis2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(InteriorChassis2, 5, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int InteriorChassis3;
			InteriorChassis3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(InteriorChassis3, 5, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int InteriorChassis4;
			InteriorChassis4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(InteriorChassis4, 5, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int InteriorChassis5;
			InteriorChassis5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(InteriorChassis5, 5, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Hoods
	case HoodMenu:
		ModShop_Sprite();
		addTitle("Hoods");
		addOption("Stock Hood"); //1
		addOption("Hood Upgrade 1"); //2
		addOption("Hood Upgrade 2"); //3
		addOption("Hood Upgrade 3"); //4
		addOption("Hood Upgrade 4"); //5
		addOption("Hood Upgrade 5"); //6
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockHood;
			StockHood = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockHood, 7);
			break;
		case 2:
			EnableVehicleMods();
			int Hook2;
			Hook2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Hook2, 7, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Hook3;
			Hook3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Hook3, 7, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Hook4;
			Hook4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Hook4, 7, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Hook5;
			Hook5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Hook5, 7, 3, 0);
			break;
		case 6:
			EnableVehicleMods();
			int Hook6;
			Hook6 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Hook6, 7, 4, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Left Fenders
	case LFenderMenu:
		ModShop_Sprite();
		addTitle("Left Fenders");
		addOption("Stock Left Fender"); //1
		addOption("Left Fender Upgrade 1"); //2
		addOption("Left Fender Upgrade 2"); //3
		addOption("Left Fender Upgrade 3"); //4
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockLFender;
			StockLFender = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockLFender, 8);
			break;
		case 2:
			EnableVehicleMods();
			int LFender2;
			LFender2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(LFender2, 8, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int LFender3;
			LFender3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(LFender3, 8, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int LFender4;
			LFender4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(LFender4, 8, 2, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Right Fenders
	case RFenderMenu:
		ModShop_Sprite();
		addTitle("Right Fenders");
		addOption("Stock Right Fender"); //1
		addOption("Right Fender Upgrade 1"); //2
		addOption("Right Fender Upgrade 2"); //3
		addOption("Right Fender Upgrade 3"); //4
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockRFender;
			StockRFender = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockRFender, 9);
			break;
		case 2:
			EnableVehicleMods();
			int RFender2;
			RFender2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RFender2, 9, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int RFender3;
			RFender3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RFender3, 9, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int RFender4;
			RFender4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(RFender4, 9, 2, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Roofs
	case RoofMenu:
		ModShop_Sprite();
		addTitle("Roofs");
		addOption("Stock Roof"); //1
		addOption("Roof Upgrade 1"); //2
		addOption("Roof Upgrade 2"); //3
		addOption("Roof Upgrade 3"); //4
		addOption("Roof Upgrade 4"); //5
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockRoof;
			StockRoof = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockRoof, 10);
			break;
		case 2:
			EnableVehicleMods();
			int Roof2;
			Roof2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Roof2, 10, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Roof3;
			Roof3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Roof3, 10, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Roof4;
			Roof4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Roof4, 10, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Roof5;
			Roof5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Roof5, 10, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Spoilers
	case SpoilerMenu:
		ModShop_Sprite();
		addTitle("Spoilers");
		addOption("Stock Spoiler"); //1
		addOption("Spoiler 1"); //2
		addOption("Spoiler 2"); //3
		addOption("Spoiler 3"); //4
		addOption("Spoiler 4"); //5
		addOption("Spoiler 5"); //6
		addOption("Spoiler 6"); //7
		addOption("Spoiler 7"); //8
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockSpoiler;
			StockSpoiler = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockSpoiler, 0);
			break;
		case 2:
			EnableVehicleMods();
			int Spoiler2;
			Spoiler2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler2, 0, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Spoiler3;
			Spoiler3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler3, 0, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Spoiler4;
			Spoiler4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler4, 0, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Spoiler5;
			Spoiler5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler5, 0, 3, 0);
			break;
		case 6:
			EnableVehicleMods();
			int Spoiler6;
			Spoiler6 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler6, 0, 4, 0);
			break;
		case 7:
			EnableVehicleMods();
			int Spoiler7;
			Spoiler7 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler7, 0, 5, 0);
			break;
		case 8:
			EnableVehicleMods();
			int Spoiler8;
			Spoiler8 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Spoiler8, 0, 6, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Grills
	case GrillMenu:
		ModShop_Sprite();
		addTitle("Grills");
		addOption("Stock Grille"); //1
		addOption("Grille Upgrade 1"); //2
		addOption("Grille Upgrade 2"); //3
		addOption("Grille Upgrade 3"); //4
		addOption("Grille Upgrade 4"); //5
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int StockGrill;
			StockGrill = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(StockGrill, 6);
			break;
		case 2:
			EnableVehicleMods();
			int Grill2;
			Grill2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Grill2, 6, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Grill3;
			Grill3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Grill3, 6, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Grill4;
			Grill4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Grill4, 6, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Grill5;
			Grill5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Grill5, 6, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Horns
	case Horns_ModShop:
		ModShop_Sprite();
		addTitle("Horns");
		addOption("Stock Horn");
		addOption("Truck"); //0
		addOption("Cop");
		addOption("Clown");
		addOption("Musical 1");
		addOption("Musical 2");
		addOption("Musical 3");
		addOption("Musical 4");
		addOption("Musical 5");
		addOption("Classical 1");
		addOption("Classical 2");
		addOption("Classical 3");
		addOption("Classical 4");
		addOption("Classical 5");
		addOption("Classical 6");
		addOption("Classical 7");
		addOption("Do");
		addOption("Re");
		addOption("Mi");
		addOption("Fa");
		addOption("Sol");
		addOption("La");
		addOption("Ti");
		addOption("Do (High)");
		addOption("Jazz 1");
		addOption("Jazz 2");
		addOption("Jazz 3");
		addOption("Jazz Loop");
		addOption("Star Spangled Banner 1");
		addOption("Star Spangled Banner 2");
		addOption("Star Spangled Banner 3");
		addOption("Star Spangled Banner 4");
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 14);
			break;;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 14, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 14, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 14, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Vehicle5;
			Vehicle5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle5, 14, 3, 0);
			break;
		case 6:
			EnableVehicleMods();
			int Vehicle6;
			Vehicle6 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle6, 14, 4, 0);
			break;
		case 7:
			EnableVehicleMods();
			int Vehicle7;
			Vehicle7 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle7, 14, 5, 0);
			break;
		case 8:
			EnableVehicleMods();
			int Vehicle8;
			Vehicle8 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle8, 14, 6, 0);
			break;
		case 9:
			EnableVehicleMods();
			int Vehicle9;
			Vehicle9 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle9, 14, 7, 0);
			break;
		case 10:
			EnableVehicleMods();
			int Vehicle10;
			Vehicle10 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle10, 14, 8, 0);
			break;
		case 11:
			EnableVehicleMods();
			int Vehicle11;
			Vehicle11 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle11, 14, 9, 0);
			break;
		case 12:
			EnableVehicleMods();
			int Vehicle12;
			Vehicle12 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle12, 14, 10, 0);
			break;
		case 13:
			EnableVehicleMods();
			int Vehicle13;
			Vehicle13 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle13, 14, 11, 0);
			break;
		case 14:
			EnableVehicleMods();
			int Vehicle14;
			Vehicle14 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle14, 14, 12, 0);
			break;
		case 15:
			EnableVehicleMods();
			int Vehicle15;
			Vehicle15 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle15, 14, 13, 0);
			break;
		case 16:
			EnableVehicleMods();
			int Vehicle16;
			Vehicle16 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle16, 14, 14, 0);
			break;
		case 17:
			EnableVehicleMods();
			int Vehicle17;
			Vehicle17 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle17, 14, 15, 0);
			break;
		case 18:
			EnableVehicleMods();
			int Vehicle18;
			Vehicle18 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle18, 14, 16, 0);
			break;
		case 19:
			EnableVehicleMods();
			int Vehicle19;
			Vehicle19 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle19, 14, 17, 0);
			break;
		case 20:
			EnableVehicleMods();
			int Vehicle20;
			Vehicle20 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle20, 14, 18, 0);
			break;
		case 21:
			EnableVehicleMods();
			int Vehicle21;
			Vehicle21 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle21, 14, 19, 0);
			break;
		case 22:
			EnableVehicleMods();
			int Vehicle22;
			Vehicle22 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle22, 14, 20, 0);
			break;
		case 23:
			EnableVehicleMods();
			int Vehicle23;
			Vehicle23 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle23, 14, 21, 0);
			break;
		case 24:
			EnableVehicleMods();
			int Vehicle24;
			Vehicle24 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle24, 14, 22, 0);
			break;
		case 25:
			EnableVehicleMods();
			int Vehicle25;
			Vehicle25 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle25, 14, 23, 0);
			break;
		case 26:
			EnableVehicleMods();
			int Vehicle26;
			Vehicle26 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle26, 14, 24, 0);
			break;
		case 27:
			EnableVehicleMods();
			int Vehicle27;
			Vehicle27 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle27, 14, 25, 0);
			break;
		case 28:
			EnableVehicleMods();
			int Vehicle28;
			Vehicle28 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle28, 14, 26, 0);
			break;
		case 29:
			EnableVehicleMods();
			int Vehicle29;
			Vehicle29 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle29, 14, 27, 0);
			break;
		case 30:
			EnableVehicleMods();
			int Vehicle30;
			Vehicle30 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle30, 14, 28, 0);
			break;
		case 31:
			EnableVehicleMods();
			int Vehicle31;
			Vehicle31 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle31, 14, 29, 0);
			break;
		case 32:
			EnableVehicleMods();
			int Vehicle32;
			Vehicle32 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle32, 14, 30, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Performance
	case Performance_ModShop:
		ModShop_Sprite();
		addTitle("Performance");
		addSubmenuOption("Engine", Engine_ModShop); //1
		addSubmenuOption("Transmission", Transmission_ModShop); //2
		addSubmenuOption("Brakes", Brakes_ModShop); //3
		addSubmenuOption("Suspension", Suspension_ModShop); //4
		addSubmenuOption("Exhaust", Exhaust_ModShop); //5
		addBoolOption("Turbo", ToggleTurbo); //6
		switch (getOption())
		{
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6:
			EnableVehicleMods();
			if (!ToggleTurbo)
			{
				int Vehicle;
				Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::TOGGLE_VEHICLE_MOD(Vehicle, 18, 1);
				ToggleTurbo = true;
			}
			else if (ToggleTurbo)
			{
				int Vehicle;
				Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::TOGGLE_VEHICLE_MOD(Vehicle, 18, 0);
				ToggleTurbo = false;
				ToggleTurbo = !ToggleTurbo; break;
			}
		}
		break;
#pragma endregion
#pragma region Engine
	case Engine_ModShop:
		ModShop_Sprite();
		addTitle("Engine");
		addOption("Stock Engine"); //1
		addOption("Engine Upgrade 1"); //2
		addOption("Engine Upgrade 2"); //3
		addOption("Engine Upgrade 3"); //4
		addOption("Engine Upgrade 4"); //5
		addIntOption("Set Custom Engine", &SetEngine, 0, 1000, true); //6
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 11);
			break;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 11, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 11, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 11, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Vehicle5;
			Vehicle5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle5, 11, 3, 0);
			break;
		case 6:
			EnableVehicleMods();
			int Vehicle6;
			Vehicle6 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle6, 11, SetEngine, 0);
			//VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehicle6, SetEngine);
			break;
		}
		break;
#pragma endregion
#pragma region Transmission
	case Transmission_ModShop:
		ModShop_Sprite();
		addTitle("Transmission");
		addOption("Stock Transmission"); //1
		addOption("Street Transmission"); //2
		addOption("Sports Transmission"); //3
		addOption("Race Transmission"); //4
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 13);
			break;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 13, 1, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 13, 2, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 13, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Brakes
	case Brakes_ModShop:
		ModShop_Sprite();
		addTitle("Brakes");
		addOption("Stock Brakes"); //1
		addOption("Street Brakes"); //2
		addOption("Sports Brakes"); //3
		addOption("Race Brakes"); //4
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 12);
			break;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 12, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 12, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 12, 2, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Suspension
	case Suspension_ModShop:
		ModShop_Sprite();
		addTitle("Suspension");
		addOption("Stock Suspension"); //1
		addOption("Lowered Suspension"); //2
		addOption("Street Suspension"); //3
		addOption("Sports Suspension"); //4
		addOption("Competition Suspension"); //6
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 15);
			break;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 15, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 15, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 15, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Vehicle5;
			Vehicle5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle5, 15, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Exhaust
	case Exhaust_ModShop:
		ModShop_Sprite();
		addTitle("Exhaust");
		addOption("Stock Exhaust"); //1
		addOption("Exhaust 1"); //2
		addOption("Exhaust 2"); //3
		addOption("Exhaust 3"); //4
		addOption("Exhaust 4"); //6
		switch (getOption())
		{
		case 1:
			EnableVehicleMods();
			int Vehicle;
			Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::REMOVE_VEHICLE_MOD(Vehicle, 4);
			break;
		case 2:
			EnableVehicleMods();
			int Vehicle2;
			Vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle2, 4, 0, 0);
			break;
		case 3:
			EnableVehicleMods();
			int Vehicle3;
			Vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle3, 4, 1, 0);
			break;
		case 4:
			EnableVehicleMods();
			int Vehicle4;
			Vehicle4 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle4, 4, 2, 0);
			break;
		case 5:
			EnableVehicleMods();
			int Vehicle5;
			Vehicle5 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_MOD(Vehicle5, 4, 3, 0);
			break;
		}
		break;
#pragma endregion
#pragma region Funny Cars
	case Funny_Cars:

		addTitle("Funny Cars");
		addSubmenuOption("UFO Saucer", UFOSaucer);
		addSubmenuOption("Bumper Car", BumperCar);
		addSubmenuOption("Trolley Car", TrolleyCar);
		addSubmenuOption("Toilet Car", ToiletCar);
		addSubmenuOption("Couch Car", CouchCar);
		addSubmenuOption("Wheel Chair Car", WheelChairCar);
		addSubmenuOption("Wheel Barrow Car", WheelBarrowCar);
		addSubmenuOption("Ramp Car", RampCar);
		addSubmenuOption("Monster Truck Ramp Car", Monster_Truck_Ramp_Car);
		addSubmenuOption("Custome Funny Car", Ramp_Car);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region UFO Saucer
	case UFOSaucer:

		addTitle("UFO Saucer");
		ObjectSpawnerOption("Spawn UFO", 0xB467C540);
		addVehicleOption("Skylift", 0x3E48BF23);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, 0.0, 3.9, 0.0, 0.0, 0.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Trolley Car
	case TrolleyCar:

		addTitle("Trolley Car");
		ObjectSpawnerOption("Spawn Trolley", 1395334609);
		SpawnVehiclesAtAll("Carbon RS", 0x00ABB0C0);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Toilet Car
	case ToiletCar:

		addTitle("Toilet Car");
		ObjectSpawnerOption("Spawn Toilet", 1872312775);
		SpawnVehiclesAtAll("Blazer", 0x8125BCF9);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, -0.4f, 0.1f, 0.0, 0.0, 180, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Couch Car
	case CouchCar:

		addTitle("Couch Car");
		ObjectSpawnerOption("Spawn Couch", -1964110779);
		SpawnVehiclesAtAll("Spawn Dune Buggy", 0x9CF21E0F);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, -0.4f, 0.1f, 0.0, 0.0, 180.0f, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Wheel Chair Car
	case WheelChairCar:

		addTitle("Wheel Chair Car");
		ObjectSpawnerOption("Spawn Wheel Chair", 1262298127);
		SpawnVehiclesAtAll("Spawn Caddy", 0x44623884);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, -0.27, -0.24, 0.13f, 0.0, 0.0, 180.0f, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion

#pragma region Wheel Barrow Car
	case WheelBarrowCar:

		addTitle("Wheel Barrow Car");
		ObjectSpawnerOption("Spawn Wheel Barrow", 1262298127);
		SpawnVehiclesAtAll("Spawn Caddy", 0x44623884);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, -0.62, 0.12, 0.0, 41.0, 90.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Ramp Car
	case RampCar:

		addTitle("Ramp Car");
		ObjectSpawnerOption("Spawn Shipping Container", -629735826); //1
		addOption("Attach Object 1 To Car"); //2
		addOption("Attach Object 2 To Car"); //3
		addOption("Attach Object 3 To Car"); //4
		switch (getOption())
		{
		case 2:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, 0.0, 6.82, -2. - 43, -9. - 54, 0.0, 0.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		case 3:
			Entity Object2;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object2))
			{
				int vehicle2;
				vehicle2 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, vehicle2, -1, 2.45, 6.82, -2. - 43, -9. - 54, 0.0, 0.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object2, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object2, 1, 0);
			} break; //12
		case 4:
			Entity Object3;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object3))
			{
				int vehicle3;
				vehicle3 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, vehicle3, -1, -2. - 45, 6.82, -2. - 43, -9. - 54, 0.0, 0.0, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object3, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object3, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Monster Truck Ramp Car
	case Monster_Truck_Ramp_Car:

		addTitle("Monster Truck Ramp Car");
		ObjectSpawnerOption("Spawn Barge", -1669978330);
		addVehicleOption("Monster", 0xCD93A7DB);
		addOption("Attach Object To Car"); //2
		switch (getOption())
		{
		case 3:
			Entity Object;
			if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &Object))
			{
				int vehicle;
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VehObjx3 = 0.0;
				VehObjy3 = 6.82;
				VehObjx2 = -0. - 46;
				VehObjy2 = -9.99;
				VehObjz2 = 0.0;
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, vehicle, -1, VehObjx3, VehObjy3, VehObjz3, VehObjx2, VehObjy2, VehObjz2, 0, 0, 0, 0, 2, 1);
				ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
				ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
			} break; //12
		}
		break;
#pragma endregion
#pragma region Spawn Objects
	case Object_Spawner:
		addTitle("Spawn Obects");
		addSubmenuOption("Object Editor ~r~>", Object_Menu, "List of objects spawneds.");
		addSubmenuOption("Object Bypass ~r~>", ObjectBypass);
		addOption("Weed");
		addOption("Oil Slick");
		addOption("Windmill");
		addOption("Dummy");
		addOption("Heist EMP");
		addOption("Cable Car");
		addOption("Tram");
		addOption("Barge");
		addOption("Carrier Defense");
		addOption("Radar");
		addOption("Orange Ball");
		switch (getOption())
		{
		case 1:
			break;
		case 2:	break;
		case 3:
			ObjectString = "prop_weed_01";
			LoadingObject = true;	break;
		case 4:
			ObjectString = "p_oil_slick_01";
			LoadingObject = true;	break;
		case 5:
			ObjectString = "prop_windmill_01";
			LoadingObject = true;	break;
		case 6:
			ObjectString = "prop_dummy_01";
			LoadingObject = true;	break;
		case 7:
			ObjectString = "hei_prop_heist_emp";
			LoadingObject = true;	break;
		case 8:
			ObjectString = "p_cablecar_s";
			LoadingObject = true;	break;
		case 9:
			ObjectString = "p_tram_crash_s";
			LoadingObject = true;	break;
		case 10:
			ObjectString = "prop_lev_des_barge_02";
			LoadingObject = true;	break;
		case 11:
			ObjectString = "hei_prop_carrier_defense_01";
			LoadingObject = true;	break;
		case 12:
			ObjectString = "prop_air_bigradar";
			LoadingObject = true;	break;
		case 13:
			ObjectString = "prop_juicestand";
			LoadingObject = true;	break;
		}
		break;
#pragma endregion 
#pragma region FullAttacList
	case ObjectBypass:
		addTitle("Object List");
		for (llvar = 0; llvar < 3415; llvar++)
		{
			addBypassOption(AllPROPS[llvar]);
		}
		break;

#pragma endregion
#pragma region Manager 
	case Object_Menu:
		attacheropt = false;
		attacheropt2 = false;
		attacheropt3 = false;
		attacheropt4 = false;
		attacheropt5 = false;
		addTitle("Object Manager");
		for (int i = 0; i < 14; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[i]))
				addOption(ObjectNameArray[i]);
			else
				addOption("Not Found");
		}
		if (optionPress)
		{
			SelectedObject = currentOption - 1;
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]))
			{
				changeSubmenu(Object_Movement);
			}
			else
			{
				drawNotification("~r~Spawn Object\nTo Open Object Editor");
			}
		}
		break;
#pragma endregion
#pragma region Movement
	case Object_Movement:
		makerobject();
		addTitle(ObjectNameArray[SelectedObject]);
		addBoolOption("Advanced Movement", AdvOpt);
		addOption("Delete");
		addOption("------------ VEHICLE ------------");
		addOption("Attach Object To Vehicle");
		addBoolOption("Vehicle Visible", invisibleveh);
		addOption("------------ PLAYER ------------");
		addOption("Attach Object");
		addOption("Attach Object Head");
		addOption("Attach Object Arm");
		addOption("Attach Object Arm 2");
		addOption("------------ MOVEMENT ------------");
		addX("X", &XCoord, -255.0f, 255.0f, true);
		addY("Y", &YCoord, -255.0f, 255.0f, true);
		addZ("Z", &ZCoord, -255.0f, 255.0f, true);
		addRoll("Roll", &RollCoord, -255.0f, 255.0f, true);
		addPitch("Pitch", &PitchCoord, -255.0f, 255.0f, true);
		addYaw("Yaw", &YawCoord, -255.0f, 255.0f, true);
		switch (getOption())
		{
		case 1:
			if (!AdvOpt)
			{
				NotifyAboveMap("~g~Advanced Enabled");
				//SpectateMode(true, SpawnedObject[SelectedObject]);
			}
			else if (AdvOpt)
			{
				NotifyAboveMap("~g~Advanced Disabled");
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
			}
			AdvOpt = !AdvOpt;
			//spectatormode = !spectatormode;
			//spectatormode1 = !spectatormode1;
			//spectatormode2 = !spectatormode2; 
			break;
		case 2:
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				DeleteEntity(SpawnedObject[SelectedObject]);
				char buf[100];
				_snprintf(buf, sizeof(buf), "Deleted: ~b~%s", ObjectNameArray[SelectedObject]);
				drawNotification(buf);
			} break;
		case 4: attacheropt = !attacheropt; break;
		case 5: invisibleveh = !invisibleveh; break;
		case 7: attacheropt2 = !attacheropt2; break;
		case 8: attacheropt3 = !attacheropt3; break;
		case 9: attacheropt4 = !attacheropt4; break;
		case 10:  attacheropt5 = !attacheropt5; break;
		}
		break;
#pragma endregion
#pragma region Vehicle Weapons
	case Vehicle_Weapons:

		addTitle("Vehicle Weapons");
		addBoolOption("Shoot Rockets", ShootRockets);
		addBoolOption("Shoot Green Lazers", ShootGreenLazers);
		addBoolOption("Shoot Red Lazers", ShootRedLazers);
		addBoolOption("Shoot Flares", ShootFlares);
		addBoolOption("Shoot Snowballs", ShootSnowballs);
		addBoolOption("Shoot Smokes", ShootSmokes);
		addBoolOption("Vehicle Machineguns", VehicleMachineguns);
		addBoolOption("Vehicle Fireworks", VehicleFireworks);
		addBoolOption("Super Machineguns", SuperMachineguns);
		switch (getOption())
		{
		case 1: ShootRockets = !ShootRockets; break;
		case 2: ShootGreenLazers = !ShootGreenLazers; break;
		case 3: ShootRedLazers = !ShootRedLazers; break;
		case 4: ShootFlares = !ShootFlares; break;
		case 5: ShootSnowballs = !ShootSnowballs; break;
		case 6: ShootSmokes = !ShootSmokes; break;
		case 7: VehicleMachineguns = !VehicleMachineguns; break;
		case 8: VehicleFireworks = !VehicleFireworks; break;
		case 9: SuperMachineguns = !SuperMachineguns; break;
		}
		break;
#pragma endregion
#pragma region Colour Options
	case Colour_Options:
		ModShop_Sprite();
		addTitle("Colour Options");
		addSubmenuOption("Custome Paint RGB Menu", Custome_PaintMenu);
		addSubmenuOption("Rim Paints", Rim_Paints);
		addBoolOption("Rainbow Car", Toggle_RainBowCar);//3
		addOption("Random Color"); //4
		addOption("Rainbow Color V2");
		addPresetVehicleColour("Chrome", 120);
		addSubmenuOption("Classic/Metallic Colours", Classic_Metallic);
		addSubmenuOption("Matte Colours", Matte_Colours);
		addSubmenuOption("Metals Colours", Metals_Colours);
		addSubmenuOption("Custome Paint Menu", Custome_Paint_Menu);
		addIntOption("Set Alpha", &Set_AlphaTo2, 0, 255, true, true);
		switch (getOption())
		{
		case 3: Toggle_RainBowCar = !Toggle_RainBowCar; break;
		case 4:
			int vehicle;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle) && ENTITY::IS_ENTITY_A_VEHICLE(vehicle))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
					VEHICLE::SET_VEHICLE_COLOURS(vehicle, irand(0, 255, 200), irand(0, 255, -40));
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, irand(0, 255, 30), irand(0, 255, 400));
				}
			}break;
		case 5:
			Primary_Paint = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
				Primary_Paint2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
				Primary_Paint3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
			Secondary_Paint3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
				Secondary_Paint4 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
				Secondary_Paint5 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
			break;
		case 10:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			ENTITY::SET_ENTITY_ALPHA(CPaintMenu, Set_AlphaTo2, false); break;
		}
		break;
#pragma endregion
#pragma region Custome Paint Menu
	case Custome_Paint_Menu:
		ModShop_Sprite();
		addTitle("Colour Options");
		addOption("Default Paint"); //1 
		addOption("Pink & Blue Paint"); //2
		addOption("Teal Blue Paint"); //3
		addOption("Tan Yellow & Blue Paint"); //4
		addOption("Purple & Green Paint"); //5
		addOption("Lime Green & Silver Paint"); //6
		addOption("Lime Yellow & Lime Green Paint"); //7
		addOption("Lime Green & White Paint"); //9
		switch (getOption())
		{
		case 1:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 92, 80, 248);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 42, 15, 160);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 2:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 154, 337, 171);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 16, 148, 180);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 3:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 14, 135, 130);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 28, 203, 226);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 4:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 156, 221, 199);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 21, 61, 211);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 5:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 70, 5, 121);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 122, 160, 20);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 6:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 4, 194, 74);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 87, 116, 166);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 7:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 43, 252, 146);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 215, 223, 202);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		case 8:
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 180, 250, 102);
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 110, 192, 72);
			VEHICLE::SET_VEHICLE_COLOURS(CPaintMenu, 131, 131);
			break;
		}
		break;
#pragma endregion
#pragma region Metals Colours
	case Metals_Colours:
		ModShop_Sprite();
		addTitle("Metals Colours");
		addPresetVehicleColour("Brushed Steel", 117);
		addPresetVehicleColour("Brushed Black Steel", 118);
		addPresetVehicleColour("Brushed Aluminum", 119);
		addPresetVehicleColour("Pure Gold", 158);
		addPresetVehicleColour("Brushed Gold", 159);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Matte Colours
	case Matte_Colours:
		ModShop_Sprite();
		addTitle("Matte Colours");
		addPresetVehicleColour("Black", 12);
		addPresetVehicleColour("Gray", 13);
		addPresetVehicleColour("Light Gray", 14);
		addPresetVehicleColour("Ice White", 131);
		addPresetVehicleColour("Blue", 83);
		addPresetVehicleColour("Dark Blue", 82);
		addPresetVehicleColour("Midnight Blue", 84);
		addPresetVehicleColour("Midnight Purple", 149);
		addPresetVehicleColour("Schafter Purple", 148);
		addPresetVehicleColour("Red", 39);
		addPresetVehicleColour("Dark Red", 40);
		addPresetVehicleColour("Orange", 41);
		addPresetVehicleColour("Yellow", 42);
		addPresetVehicleColour("Lime Green", 55);
		addPresetVehicleColour("Green", 128);
		addPresetVehicleColour("Forest Green", 151);
		addPresetVehicleColour("Foliage Green", 155);
		addPresetVehicleColour("Olive Darb", 152);
		addPresetVehicleColour("Dark Earth", 153);
		addPresetVehicleColour("Desert Tan", 154);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Classic/Metallic Colours
	case Classic_Metallic:
		ModShop_Sprite();
		addTitle("Classic/Metallic Colours");
		addPresetVehicleColour("Black", 0);
		addPresetVehicleColour("Carbon Black", 147);
		addPresetVehicleColour("Graphite", 1);
		addPresetVehicleColour("Anhracite Black", 11);
		addPresetVehicleColour("Black Steel", 2);
		addPresetVehicleColour("Dark Steel", 3);
		addPresetVehicleColour("Silver", 4);
		addPresetVehicleColour("Bluish Silver", 5);
		addPresetVehicleColour("Rolled Steel", 6);
		addPresetVehicleColour("Shadow Silver", 7);
		addPresetVehicleColour("Stone Silver", 8);
		addPresetVehicleColour("Midnight Silver", 9);
		addPresetVehicleColour("Cast Iron Silver", 10);
		addPresetVehicleColour("Red", 27);
		addPresetVehicleColour("Torino Red", 28);
		addPresetVehicleColour("Formula Red", 29);
		addPresetVehicleColour("Lava Red", 150);
		addPresetVehicleColour("Blaze Red", 30);
		addPresetVehicleColour("Grace Red", 31);
		addPresetVehicleColour("Garnet Red", 32);
		addPresetVehicleColour("Cabernet Red", 34);
		addPresetVehicleColour("Wine Red", 143);
		addPresetVehicleColour("Candy Red", 35);
		addPresetVehicleColour("Hot Pink", 135);
		addPresetVehicleColour("Pfsiter Pink", 137);
		addPresetVehicleColour("Salmon Pink", 136);
		addPresetVehicleColour("Sunrise Orange", 36);
		addPresetVehicleColour("Orange", 38);
		addPresetVehicleColour("Bright Orange", 138);
		addPresetVehicleColour("Gold", 99);
		addPresetVehicleColour("Bronze", 90);
		addPresetVehicleColour("Yellow", 88);
		addPresetVehicleColour("Race Yellow", 89);
		addPresetVehicleColour("Dew Yellow", 91);
		addPresetVehicleColour("Dark Green", 49);
		addPresetVehicleColour("Racing Green", 50);
		addPresetVehicleColour("Sea Green", 51);
		addPresetVehicleColour("Olive Green", 52);
		addPresetVehicleColour("Bright Green", 53);
		addPresetVehicleColour("Gasoline Green", 54);
		addPresetVehicleColour("Lime Green", 92);
		addPresetVehicleColour("Midnight Blue", 141);
		addPresetVehicleColour("Galaxy Blue", 61);
		addPresetVehicleColour("Dark Blue", 62);
		addPresetVehicleColour("Saxon Blue", 63);
		addPresetVehicleColour("Blue", 64);
		addPresetVehicleColour("Mariner Blue", 65);
		addPresetVehicleColour("Harbor Blue", 66);
		addPresetVehicleColour("Diamond Blue", 67);
		addPresetVehicleColour("Surf Blue", 68);
		addPresetVehicleColour("Nautical Blue", 69);
		addPresetVehicleColour("Racing Blue", 73);
		addPresetVehicleColour("Ultra Blue", 70);
		addPresetVehicleColour("Light Blue", 74);
		addPresetVehicleColour("Chocolate Brown", 96);
		addPresetVehicleColour("Bison Brown", 101);
		addPresetVehicleColour("Creeen Brown", 95);
		addPresetVehicleColour("Feltzer Brown", 94);
		addPresetVehicleColour("Maple Brown", 97);
		addPresetVehicleColour("Beechwood Brown", 103);
		addPresetVehicleColour("Sienna Brown", 104);
		addPresetVehicleColour("Saddle Brown", 98);
		addPresetVehicleColour("Moss Brown", 100);
		addPresetVehicleColour("Woodbeech Brown", 102);
		addPresetVehicleColour("Straw Brown", 99);
		addPresetVehicleColour("Sandy Brown", 105);
		addPresetVehicleColour("Bleached Brown", 106);
		addPresetVehicleColour("Schafter Purple", 71);
		addPresetVehicleColour("Spinnaker Purple", 72);
		addPresetVehicleColour("Midnight Purple", 142);
		addPresetVehicleColour("Bright Purple", 145);
		addPresetVehicleColour("Cream", 107);
		addPresetVehicleColour("Ice White", 111);
		addPresetVehicleColour("Frost White", 112);
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Rim Paints
	case Rim_Paints:
		ModShop_Sprite();
		addTitle("Rim Paints");
		addOption("Lime Green");
		addOption("Black");
		addOption("White");
		addOption("Blue");
		addOption("Hot Pink");
		addOption("Purple");
		addOption("Red");
		switch (getOption())
		{
		case 1:
			int RLimeGreen;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RLimeGreen = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RLimeGreen) && ENTITY::IS_ENTITY_A_VEHICLE(RLimeGreen))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RLimeGreen, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RLimeGreen, 0, 92);
				}
			} break;
		case 2:
			int RBlack;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RBlack = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RBlack) && ENTITY::IS_ENTITY_A_VEHICLE(RBlack))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RBlack, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RBlack, 0, 0);
				}
			} break;
		case 3:
			int RWhite;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RWhite = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RWhite) && ENTITY::IS_ENTITY_A_VEHICLE(RWhite))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RWhite, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RWhite, 0, 112);
				}
			} break;
		case 4:
			int RBlue;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RBlue = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RBlue) && ENTITY::IS_ENTITY_A_VEHICLE(RBlue))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RBlue, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RBlue, 0, 140);
				}
			} break;
		case 5:
			int RHotPink;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RHotPink = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RHotPink) && ENTITY::IS_ENTITY_A_VEHICLE(RHotPink))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RHotPink, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RHotPink, 0, 135);
				}
			} break;
		case 6:
			int RPurple;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RPurple = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RPurple) && ENTITY::IS_ENTITY_A_VEHICLE(RPurple))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RPurple, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RPurple, 0, 145);
				}
			} break;
		case 7:
			int RRed;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				RRed = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(RRed) && ENTITY::IS_ENTITY_A_VEHICLE(RRed))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(RRed, 0.0f);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(RRed, 0, 29);
				}
			} break;
		}
		break;
#pragma endregion
#pragma region Custome Paint Menu
	case Custome_PaintMenu:
		ModShop_Sprite();
		addTitle("Custome Paint RGB Menu");
		addIntOption("Primary Red", &Primary_Paint, 0, 255, true); //1 
		addIntOption("Primary Green", &Primary_Paint2, 0, 255, true); //2
		addIntOption("Primary Blue", &Primary_Paint3, 0, 255, true); //3
		addIntOption("Secondary Red", &Secondary_Paint3, 0, 255, true); //4
		addIntOption("Secondary Green", &Secondary_Paint4, 0, 255, true); //5 
		addIntOption("Secondary Blue", &Secondary_Paint5, 0, 255, true); //6
		addIntOption("Paint Rim", &Secondary_Paint, 0, 255, true); //7
		addIntOption("Paint Rim 2", &Secondary_Paint2, 0, 255, true); //8
		switch (getOption())
		{
		case 1:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 2:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 3:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 4:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 5:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 6:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 7:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		case 8:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(CPaintMenu, Secondary_Paint, Secondary_Paint2);
				}
			} break;
		}
		break;
#pragma endregion
#pragma region Vehicle Spawner
	case Vehicle_Spawner:
		VehicleSpawner_Sprite();
		addTitle("Vehicle Spawner");
		addSubmenuOption("Favorites", Vehicle_Favorites);
		addSubmenuOption("Super", Vehicle_Super);
		addSubmenuOption("Sports", Vehicle_Sports);
		addSubmenuOption("Coupes", Vehicle_Coupes);
		addSubmenuOption("Sedans", Vehicle_Sedans);
		addSubmenuOption("Emergency", Vehicle_Emergency);
		addSubmenuOption("Off Road", Vehicle_OffRoad);
		addSubmenuOption("Muscle", Vehicle_Muscle);
		addSubmenuOption("SUVs", Vehicle_SUVs);
		addSubmenuOption("Motorcycles", Vehicle_Motorcycles);
		addSubmenuOption("Helicopters", Vehicle_Helicopters);
		addSubmenuOption("Planes", Vehicle_Planes);
		addSubmenuOption("Commercial", Vehicle_Commercial);
		addSubmenuOption("Bicycles", Vehicle_Bicycles);
		addSubmenuOption("Boats", Vehicle_Boats);
		addSubmenuOption("Industrial", Vehicle_Industrial);
		addSubmenuOption("Utility", Vehicle_Utility);
		addSubmenuOption("Trailers", Vehicle_Trailers);
		addSubmenuOption("Compacts", Vehicle_Compacts);
		addSubmenuOption("Military", Vehicle_Military);
		addSubmenuOption("Service", Vehicle_Service);
		addSubmenuOption("Sports Classics", Vehicle_SportsClassics);
		addSubmenuOption("Vans", Vehicle_Vans);
		addSubmenuOption("Trains", Vehicle_Train);
		break;
#pragma endregion
#pragma region Trains
	case Vehicle_Train:
		VehicleSpawner_Sprite();
		addTitle("Trains");
		addVehicleOption("Freight Train", 0x3D6AAA9B);
		addVehicleOption("Train Well Car", 0x0AFD22A6);
		addVehicleOption("Train Container", 0x36DCFF98);
		addVehicleOption("Train Container Livery", 0x0E512E79);
		addVehicleOption("Train Boxcar", 0x264D9262);
		addVehicleOption("Freight Train Flatbed", 0xD1ABB666);
		addVehicleOption("Metro Train", 0x33C9E158);
		break;
#pragma endregion
#pragma region Favorites
	case Vehicle_Favorites:
		VehicleSpawner_Sprite();
		addTitle("Favorites");
		addVehicleOption("Hydra", 0x39D6E83F);
		addVehicleOption("Lazer", 0xB39B0AE6);
		addVehicleOption("Hakuchou", 0x4B6C568A);
		addVehicleOption("Buzzard", 0x2F03547B);
		addVehicleOption("Tank", 0x2EA68690);
		addVehicleOption("FIB", 0x432EA949);
		addVehicleOption("FIB2", 0x9DC66994);
		addVehicleOption("Police", 0x71FA16EA);
		addVehicleOption("Police Buffalo", 0x9F05F101);
		addVehicleOption("Unmarked", 0x8A63C7B9);
		addVehicleOption("Jester2", 0xBE0E6126);
		addVehicleOption("Dubsta 6x6", 0xB6410173);
		addVehicleOption("Monster", 0xCD93A7DB);
		addVehicleOption("Mesa(Mercs)", 0x84F42E51);
		addVehicleOption("Phantom", 0x809AA4CB);
		addVehicleOption("Bus", 0xD577C962);
		addVehicleOption("Speeder", 0x0DC60D2B);
		addVehicleOption("Blimp", 0xF7004C86);
		addVehicleOption("Jumbo Jet", 0x3F119114);
		addVehicleOption("Insurgent", 0x9114EADA);
		addVehicleOption("Technical", 0x83051506);
		addVehicleOption("Cargo Plane", 0x15F27762);
		addVehicleOption("Dozer", 0x7074F39D);
		break;
#pragma endregion
#pragma region Super
	case Vehicle_Super:
		VehicleSpawner_Sprite();
		addTitle("Super");
		addVehicleOption("Adder", 0xB779A091);
		addVehicleOption("Bullet", 0x9AE6DDA1);
		addVehicleOption("Cheetah", 0xB1D95DA0);
		addVehicleOption("EntityXF", 0xB2FE5CF9);
		addVehicleOption("Infernus", 0x18F25AC7);
		addVehicleOption("TurismoR", 0x185484E1);
		addVehicleOption("Vacca", 0x142E0DC3);
		addVehicleOption("Voltic", 0x9F4B77BE);
		addVehicleOption("Zentorno", 0xAC5DF515);
		addVehicleOption("Osiris", 0x767164D6);
		addVehicleOption("T20", 0x6322B39A);
		break;
#pragma endregion
#pragma region Sports
	case Vehicle_Sports:
		VehicleSpawner_Sprite();
		addTitle("Sports");
		addVehicleOption("9F", 0x3D8FA25C);
		addVehicleOption("9F Convertible", 0xA8E38B01);
		addVehicleOption("Alpha", 0x2DB8D1AA);
		addVehicleOption("Banshee", 0xC1E908D2);
		addVehicleOption("Buffalo", 0xEDD516C6);
		addVehicleOption("Franklins Buffalo", 0x2BEC3CBE);
		addVehicleOption("Carbonizzare", 0x7B8AB45F);
		addVehicleOption("Comet", 0xC1AE4D16);
		addVehicleOption("Coquette", 0x067BC037);
		addVehicleOption("Elegy", 0xDE3D9D22);
		addVehicleOption("Feltzer", 0x8911B9F5);
		addVehicleOption("FuroreGT", 0xBF1691E0);
		addVehicleOption("Fusilade", 0x1DC0BA53);
		addVehicleOption("Kumura", 0xAE2BFE94);
		addVehicleOption("Kumura2", 0x187D938D);
		addVehicleOption("Futo", 0x7836CE2F);
		addVehicleOption("Jester", 0xB2A716A3);
		addVehicleOption("Jester2", 0xBE0E6126);
		addVehicleOption("Khamelion", 0x206D1B68);
		addVehicleOption("Massacro", 0xF77ADE32);
		addVehicleOption("Massacro2", 0xDA5819A3);
		addVehicleOption("Penumbra", 0xE9805550);
		addVehicleOption("Rapid GT", 0x8CB29A14);
		addVehicleOption("Rapid GT Convertible", 0x679450AF);
		addVehicleOption("Schwartzer", 0xD37B7976);
		addVehicleOption("Sultan", 0x39DA2754);
		addVehicleOption("Surano", 0x16E478C1);
		break;
#pragma endregion
#pragma region Coupes
	case Vehicle_Coupes:
		VehicleSpawner_Sprite();
		addTitle("Coupes");
		addVehicleOption("Cognoscenti", 0x13B57D8A);
		addVehicleOption("Exemplar", 0xFFB15B5E);
		addVehicleOption("F620", 0xDCBCBE48);
		addVehicleOption("Felon", 0xE8A8BDA8);
		addVehicleOption("Felon2", 0xFAAD85EE);
		addVehicleOption("Jackal", 0xDAC67112);
		addVehicleOption("Oracle", 0x506434F6);
		addVehicleOption("Oracle2", 0xE18195B2);
		addVehicleOption("Sentinel", 0x50732C82);
		addVehicleOption("Sentinel2", 0x3412AE2D);
		addVehicleOption("Zion", 0xBD1B39C3);
		addVehicleOption("Zion2", 0xB8E2AE18);
		addVehicleOption("Windsor", 0x5E4327C8);
		break;
#pragma endregion
#pragma region Sedans
	case Vehicle_Sedans:
		VehicleSpawner_Sprite();
		addTitle("Sedans");
		addVehicleOption("Asea", 0x94204D89);
		addVehicleOption("Snow Asea", 0x9441D8D5);
		addVehicleOption("Asterope", 0x8E9254FB);
		addVehicleOption("Emperor", 0xD7278283);
		addVehicleOption("Rusty Emperor", 0x8FC3AADC);
		addVehicleOption("Snow Emperor", 0xB5FCF74E);
		addVehicleOption("Fugitive", 0x71CB2FFB);
		addVehicleOption("Glendale", 0x047A6BC1);
		addVehicleOption("Ingot", 0xB3206692);
		addVehicleOption("Intruder", 0x34DD8AA1);
		addVehicleOption("Premier", 0x8FB66F9B);
		addVehicleOption("Primo", 0xBB6B404F);
		addVehicleOption("Regina", 0xFF22D208);
		addVehicleOption("Romero Hearse", 0x2560B2FC);
		addVehicleOption("Schafter", 0xB52B5113);
		addVehicleOption("Stanier", 0xA7EDE74D);
		addVehicleOption("Stratum", 0x66B4FC45);
		addVehicleOption("Stretch", 0x8B13F083);
		addVehicleOption("Super Diamond", 0x42F2ED16);
		addVehicleOption("Surge", 0x8F0E3594);
		addVehicleOption("Tailgater", 0xC3DDFDCE);
		addVehicleOption("Warrener", 0x51D83328);
		addVehicleOption("Washington", 0x69F06B57);
		break;
#pragma endregion
#pragma region Emergency
	case Vehicle_Emergency:
		VehicleSpawner_Sprite();
		addTitle("Emergency");
		addVehicleOption("Ambulance", 0x45D56ADA);
		addVehicleOption("FIB", 0x432EA949);
		addVehicleOption("FIB2", 0x9DC66994);
		addVehicleOption("Fire Truck", 0x73920F8E);
		addVehicleOption("Life Guard", 0x1BF8D381);
		addVehicleOption("Park Ranger", 0x2C33B46E);
		addVehicleOption("Police Bike", 0xFDEFAEC3);
		addVehicleOption("Police Cruiser", 0x79FBB0C5);
		addVehicleOption("Police", 0x71FA16EA);
		addVehicleOption("Police Buffalo", 0x9F05F101);
		addVehicleOption("Prison Bus", 0x885F3671);
		addVehicleOption("Riot", 0xB822A1AA);
		addVehicleOption("Police Van", 0x1B38E955);
		addVehicleOption("Sheriff Cruiser", 0x9BAA707C);
		addVehicleOption("Sheriff SUV", 0x72935408);
		addVehicleOption("Snow Police Rancher", 0xA46462F7);
		addVehicleOption("Snow Police Esperanto", 0x95F4C618);
		addVehicleOption("Unmarked", 0x8A63C7B9);
		break;
#pragma endregion
#pragma region OffRoad
	case Vehicle_OffRoad:
		VehicleSpawner_Sprite();
		addTitle("Off Road");
		addVehicleOption("Brawler", 0xA7CE1BC5);
		addVehicleOption("Bifta", 0xEB298297);
		addVehicleOption("Blazer", 0x8125BCF9);
		addVehicleOption("Lifeguard Blazer", 0xFD231729);
		addVehicleOption("Trevors Blazer", 0xFD231729);
		addVehicleOption("Bodhi", 0xAA699BB6);
		addVehicleOption("Dubsta 6x6", 0xB6410173);
		addVehicleOption("Dune", 0x9CF21E0F);
		addVehicleOption("Duneloader", 0x698521E3);
		addVehicleOption("Injection", 0x432AA566);
		addVehicleOption("Kalahari", 0x05852838);
		addVehicleOption("Monster", 0xCD93A7DB);
		addVehicleOption("Mesa(Mercs)", 0x84F42E51);
		addVehicleOption("RancherXL", 0x6210CBB0);
		addVehicleOption("Rusty Rebel", 0xB802DD46);
		addVehicleOption("Clean Rebel", 0x8612B64B);
		addVehicleOption("SandkingSWB", 0x3AF8C345);
		addVehicleOption("SandkingXL", 0xB9210FD0);
		addVehicleOption("Snow Rancher", 0x7341576B);
		addVehicleOption("Space Docker", 0x1FD824AF);
		addVehicleOption("Insurgent", 0x9114EADA);
		addVehicleOption("Insurgent2", 0x7B7E56F0);
		break;
#pragma endregion
#pragma region Muscle
	case Vehicle_Muscle:
		VehicleSpawner_Sprite();
		addTitle("Muscle");
		addVehicleOption("Chino", 0x14D69010);
		addVehicleOption("Blackfin", 0x2EC385FE);
		addVehicleOption("Blade", 0xB820ED5E);
		addVehicleOption("Buccaneer", 0xD756460C);
		addVehicleOption("Dominator", 0x04CE68AC);
		addVehicleOption("Gauntlet", 0x94B395C5);
		addVehicleOption("Hotknife", 0x0239E390);
		addVehicleOption("Phoenix", 0x831A21D5);
		addVehicleOption("Picador", 0x59E0FBF3);
		addVehicleOption("Rat Loader", 0xD83C13CE);
		addVehicleOption("Rat Loader2", 0xDCE1D9F7);
		addVehicleOption("Ruiner", 0xF26CEFF9);
		addVehicleOption("SabreGT", 0x9B909C94);
		addVehicleOption("SlamVan", 0x2B7F9DE3);
		addVehicleOption("Vigero", 0xCEC6B9B7);
		addVehicleOption("Voodoo", 0x1F3766E3);
		addVehicleOption("Slamvan2", 0x31ADBBFC);
		addVehicleOption("Virgo", 0xE2504942);
		break;
#pragma endregion
#pragma region SUVs
	case Vehicle_SUVs:
		VehicleSpawner_Sprite();
		addTitle("SUVs");
		addVehicleOption("Baller", 0xCFCA3668);
		addVehicleOption("Baller2", 0x08852855);
		addVehicleOption("BeeJayXL", 0x32B29A4B);
		addVehicleOption("Old Cavalcade", 0x779F23AA);
		addVehicleOption("New Cavalcade", 0xD0EB2BE5);
		addVehicleOption("Dubsta", 0x462FE277);
		addVehicleOption("Dubsta2", 0xE882E5F6);
		addVehicleOption("FQ2", 0xBC32A33B);
		addVehicleOption("Granger", 0x9628879C);
		addVehicleOption("Gresley", 0xA3FC0F4D);
		addVehicleOption("Habanero", 0x34B7390F);
		addVehicleOption("HuntleyS", 0x1D06D681);
		addVehicleOption("Landstalker", 0x4BA4E8DC);
		addVehicleOption("Mesa", 0x36848602);
		addVehicleOption("Snow Mesa", 0xD36A4B44);
		addVehicleOption("Patriot", 0xCFCFEB3B);
		addVehicleOption("Radius", 0x9D96B45B);
		addVehicleOption("Rocoto", 0x7F5C91F1);
		addVehicleOption("Seminole", 0x48CECED3);
		addVehicleOption("Serrano", 0x4FB1A214);
		break;
#pragma endregion
#pragma region Motorcycles
	case Vehicle_Motorcycles:
		VehicleSpawner_Sprite();
		addTitle("Motorcycles");
		addVehicleOption("Vindicator", 0xAF599F01);
		addVehicleOption("Akuma", 0x63ABADE7);
		addVehicleOption("Bagger", 0x806B9CC3);
		addVehicleOption("Bati801", 0xF9300CC5);
		addVehicleOption("Bati801RR", 0xCADD5D2D);
		addVehicleOption("Carbon RS", 0x00ABB0C0);
		addVehicleOption("Daemon", 0x77934CEE);
		addVehicleOption("DoubleT", 0x9C669788);
		addVehicleOption("Faggio", 0x0350D1AB);
		addVehicleOption("Hakuchou", 0x4B6C568A);
		addVehicleOption("Hexer", 0x11F76C14);
		addVehicleOption("Lectro", 0x26321E67);
		addVehicleOption("Enduro", 0x6882FA73);
		addVehicleOption("Innovation", 0x44C4E977);
		addVehicleOption("Nemesis", 0xDA288376);
		addVehicleOption("PCJ600", 0xC9CEAF06);
		addVehicleOption("Ruffian", 0xCABD11E8);
		addVehicleOption("Sanchez", 0x2EF89E46);
		addVehicleOption("Sanchez2", 0xA960B13E);
		addVehicleOption("Sovereign", 0x2C509634);
		addVehicleOption("Thrust", 0x6D6F8F43);
		addVehicleOption("Vader", 0xF79A00F7);
		break;
#pragma endregion
#pragma region Helicopters
	case Vehicle_Helicopters:
		VehicleSpawner_Sprite();
		addTitle("Helicopters");
		addVehicleOption("Annihilator", 0x31F0B376);
		addVehicleOption("Buzzard(No Guns)", 0x2C75F0DD);
		addVehicleOption("Buzzard", 0x2F03547B);
		addVehicleOption("Cargobob", 0xFCFCB68B);
		addVehicleOption("Medic Cargobob", 0x60A7EA10);
		addVehicleOption("Trevors CargoBob", 0x53174EEF);
		addVehicleOption("Frogger", 0x2C634FBD);
		addVehicleOption("FIB/Trevors Frogger", 0x742E9AC0);
		addVehicleOption("Maverick", 0x9D0450CA);
		addVehicleOption("Police Maverick", 0x1517D4D9);
		addVehicleOption("Skylift", 0x3E48BF23);
		addVehicleOption("Swift", 0xEBC24DF2);
		addVehicleOption("Valkyrie", 0xA09E15FD);
		addVehicleOption("Swift(Gold)", 0x4019CB4C);
		addVehicleOption("Savage", 0xFB133A17);
		break;
#pragma endregion
#pragma region Planes
	case Vehicle_Planes:
		VehicleSpawner_Sprite();
		//Planes_Sprite();
		addTitle("Planes");
		addVehicleOption("Blimp", 0xF7004C86);
		addVehicleOption("Besra", 0x6CBD1D6D);
		addVehicleOption("Cargo Plane", 0x15F27762);
		addVehicleOption("Cuban 800", 0xD9927FE3);
		addVehicleOption("Duster", 0x39D6779E);
		addVehicleOption("Jumbo Jet", 0x3F119114);
		addVehicleOption("Luxor", 0x250B0C5E);
		addVehicleOption("Luxor(Gold)", 0xB79F589E);
		addVehicleOption("Mallard", 0x81794C70);
		addVehicleOption("Mammatus", 0x97E55D11);
		addVehicleOption("MilJet", 0x09D80F93);
		addVehicleOption("Lazer", 0xB39B0AE6);
		addVehicleOption("Shamal", 0xB79C1BF5);
		addVehicleOption("Titan", 0x761E2AD3);
		addVehicleOption("Velum", 0x9C429B6A);
		addVehicleOption("Velum2", 0x403820E8);
		addVehicleOption("Vestra", 0x4FF77E37);
		break;
#pragma endregion
#pragma region Commercial
	case Vehicle_Commercial:
		VehicleSpawner_Sprite();
		addTitle("Commercial");
		addVehicleOption("Benson", 0x7A61B330);
		addVehicleOption("Biff", 0x32B91AE8);
		addVehicleOption("Hauler", 0x5A82F9AE);
		addVehicleOption("Mule", 0x35ED670B);
		addVehicleOption("Mule2", 0x85A5B471);
		addVehicleOption("Packer", 0x21EEE87D);
		addVehicleOption("Phantom", 0x809AA4CB);
		addVehicleOption("Pounder", 0x7DE35E7D);
		addVehicleOption("Stockade", 0x6827CF72);
		addVehicleOption("Snow Stockade", 0xF337AB36);
		break;
#pragma endregion
#pragma region Bicycles
	case Vehicle_Bicycles:
		VehicleSpawner_Sprite();
		//Bike_Sprite();
		addTitle("Bicycles");
		addVehicleOption("BMX", 0x43779C54);
		addVehicleOption("Scorcher", 0xF4E1AA15);
		addVehicleOption("Cruiser", 0x1ABA13B5);
		addVehicleOption("Fixter", 0xCE23D3BF);
		addVehicleOption("TriCycles", 0xE823FB48);
		addVehicleOption("Whippet", 0x4339CD69);
		addVehicleOption("Endurex", 0xB67597EC);
		break;
#pragma endregion
#pragma region Boats
	case Vehicle_Boats:
		VehicleSpawner_Sprite();
		addTitle("Boats");
		addVehicleOption("Dinghy", 0x3D961290);
		addVehicleOption("Dinghy3", 0x1E5E54EA);
		addVehicleOption("Jetmax", 0x33581161);
		addVehicleOption("Marquis", 0xC1CE1183);
		addVehicleOption("Seashark", 0xC2974024);
		addVehicleOption("Lifeguard Seashark", 0xDB4388E4);
		addVehicleOption("Squalo", 0x17DF5EC2);
		addVehicleOption("Suntrap", 0xEF2295C9);
		addVehicleOption("Tropic", 0x1149422F);
		addVehicleOption("Speeder", 0x0DC60D2B);
		addVehicleOption("Police Boat", 0xE2E7D4AB);
		addVehicleOption("Submersible", 0x2DFF622F);
		addVehicleOption("Toro", 0x3FD5AA2F);
		break;
#pragma endregion
#pragma region Industrial
	case Vehicle_Industrial:
		VehicleSpawner_Sprite();
		addTitle("Industrial");
		addVehicleOption("Dock Handler", 0x1A7FCEFA);
		addVehicleOption("Dozer", 0x7074F39D);
		addVehicleOption("Dump", 0x810369E2);
		addVehicleOption("Flatbed", 0x50B0215A);
		addVehicleOption("Mixer", 0xD138A6BB);
		addVehicleOption("Mixer2", 0x1C534995);
		addVehicleOption("Rubble", 0x9A5B1DCC);
		addVehicleOption("Tipper", 0x02E19879);
		addVehicleOption("Tipper2", 0xC7824E5E);
		addVehicleOption("Guardian", 0x825A9F4C);
		break;
#pragma endregion
#pragma region Utility
	case Vehicle_Utility:
		VehicleSpawner_Sprite();
		addTitle("Utility");
		addVehicleOption("Airtug", 0x5D0AAC8F);
		addVehicleOption("Bison", 0xFEFD644F);
		addVehicleOption("Bison2", 0x7B8297C5);
		addVehicleOption("Bison3", 0x67B3F020);
		addVehicleOption("BobcatXL", 0x3FC5D440);
		addVehicleOption("Caddy", 0x44623884);
		addVehicleOption("Caddy2", 0xDFF0594C);
		addVehicleOption("Cutter", 0xC3FBA120);
		addVehicleOption("Docktug", 0xCB44B1CA);
		addVehicleOption("Fieldmaster", 0x843B73DE);
		addVehicleOption("Forklift", 0x58E49664);
		addVehicleOption("Lawn Mower", 0x6A4BD8F6);
		addVehicleOption("Ripley", 0xCD935EF9);
		addVehicleOption("Sadler", 0xDC434E51);
		addVehicleOption("Snow Sadler", 0x2BC345D1);
		addVehicleOption("Scrap Truck", 0x9A9FD3DF);
		addVehicleOption("Small Tow Truck", 0xE5A2D6C6);
		addVehicleOption("Big Tow Truck", 0xB12314E0);
		addVehicleOption("Tractor", 0x61D6BA8C);
		addVehicleOption("Snow Tractor", 0x562A97BD);
		addVehicleOption("Utility Truck", 0x1ED0A534);
		addVehicleOption("Utility Truck2", 0x34E6BF6B);
		addVehicleOption("Utility Truck3", 0x7F2153DF);
		break;
#pragma endregion
#pragma region Trailers
	case Vehicle_Trailers:
		//VehicleSpawner_Sprite();
		addTitle("Trailers");
		addVehicleOption("Car Carrier", 0x7BE032C6);
		addVehicleOption("Marquis Trailer", 0x6A59902D);
		addVehicleOption("Super Car Carrier", 0x7CAB34D0);
		addVehicleOption("Log Trailer", 0x782A236D);
		addVehicleOption("Metal Trailer", 0xCBB2BE0E);
		addVehicleOption("Random Ad Trailer", 0xA1DA3C91);
		addVehicleOption("Big Goods Trailer", 0x8548036D);
		addVehicleOption("Flatbed Trailer", 0xAF62F6B2);
		addVehicleOption("Fame Or Shame Trailer", 0x967620BE);
		addVehicleOption("Army Trailer", 0xA7FF33F5);
		addVehicleOption("Army Trailer2", 0x9E6B14D6);
		addVehicleOption("Army Trailer3", 0xB8081009);
		addVehicleOption("Boat Trailer", 0x1F3D44B5);
		addVehicleOption("Dock Trailer", 0x806EFBEE);
		addVehicleOption("Freight Trailer", 0xD1ABB666);
		addVehicleOption("Construction Trailer", 0x2A72BEAB);
		addVehicleOption("Tanker Trailer", 0xD46F4737);
		addVehicleOption("Tanker Trailer2", 0x74998082);
		break;
#pragma endregion
#pragma region Compacts
	case Vehicle_Compacts:
		//VehicleSpawner_Sprite();
		addTitle("Compacts");
		addVehicleOption("Blista", 0xEB70965F);
		addVehicleOption("Dilettante", 0xBC993509);
		addVehicleOption("Issi", 0xB9CB3B69);
		addVehicleOption("Panto", 0xE644E480);
		addVehicleOption("Prairie", 0xA988D3A2);
		addVehicleOption("Rhapsody", 0x322CF98F);
		break;
#pragma endregion
#pragma region Military
	case Vehicle_Military:
		//VehicleSpawner_Sprite();
		addTitle("Military");
		addVehicleOption("Barracks", 0xCEEA3F4B);
		addVehicleOption("Barracks Semi", 0x4008EABB);
		addVehicleOption("Barracks3", 0x2592B5CF);
		addVehicleOption("Crusader", 0x132D5A1A);
		addVehicleOption("Tank", 0x2EA68690);
		break;
#pragma endregion
#pragma region Service
	case Vehicle_Service:
		//VehicleSpawner_Sprite();
		addTitle("Service");
		addVehicleOption("Airport Bus", 0x4C80EB0E);
		addVehicleOption("Bus", 0xD577C962);
		addVehicleOption("Dashound", 0x84718D34);
		addVehicleOption("Shuttle", 0xBE819C63);
		addVehicleOption("Taxi", 0xC703DB5F);
		addVehicleOption("Tourbus", 0x73B1C3CB);
		addVehicleOption("Trashmaster", 0x72435A19);
		addVehicleOption("Trash2", 0x72435A19);
		break;
#pragma endregion
#pragma region SportsClassics
	case Vehicle_SportsClassics:
		//VehicleSpawner_Sprite();
		addTitle("Sports Classics");
		addVehicleOption("Coquette Classic", 0x3C4E2113);
		addVehicleOption("JB700", 0x3EAB5555);
		addVehicleOption("Manana", 0x81634188);
		addVehicleOption("Monroe", 0xE62B361B);
		addVehicleOption("Peyote", 0x6D19CCBC);
		addVehicleOption("Pigalle", 0x404B6381);
		addVehicleOption("Roosevelt", 0x06FF6914);
		addVehicleOption("Stinger", 0x5C23AF9B);
		addVehicleOption("StingerGT", 0x82E499FA);
		addVehicleOption("Tornado", 0x1BB290BC);
		addVehicleOption("Tornado2", 0x5B42A5C4);
		addVehicleOption("Tornado3", 0x690A4153);
		addVehicleOption("Tornado4", 0x86CF7CDD);
		addVehicleOption("ZType", 0x2D3BD401);
		addVehicleOption("Stirling GT", 0xA29D6D10);
		addVehicleOption("Casco", 0x3822BDFE);
		break;
#pragma endregion
#pragma region Vans
	case Vehicle_Vans:
		//VehicleSpawner_Sprite();
		addTitle("Vans");
		addVehicleOption("Boxville", 0x898ECCEA);
		addVehicleOption("Boxville2", 0xF21B33BE);
		addVehicleOption("Boxville3", 0x07405E08);
		addVehicleOption("Boxville4", 0x1A79847A);
		addVehicleOption("Burrito", 0xAFBB2CA4);
		addVehicleOption("Burrito2", 0xC9E8FF76);
		addVehicleOption("Burrito3", 0x98171BD3);
		addVehicleOption("Burrito4", 0x353B561D);
		addVehicleOption("Snow Burrito", 0x437CF2A0);
		addVehicleOption("Gang Burrito", 0x97FA4F36);
		addVehicleOption("Gang Burrito2", 0x11AA0E14);
		addVehicleOption("Camper", 0x6FD95F68);
		addVehicleOption("Journey", 0xF8D48E7A);
		addVehicleOption("Minivan", 0xED7EADA4);
		addVehicleOption("Paradise", 0x58B3979C);
		addVehicleOption("Pony", 0xF8DE29A8);
		addVehicleOption("Weed Van", 0x38408341);
		addVehicleOption("Weazel News", 0x4543B74D);
		addVehicleOption("Deludamol", 0x961AFEF7);
		addVehicleOption("Speedo", 0xCFB3870C);
		addVehicleOption("Clown Van", 0x2B6DC64A);
		addVehicleOption("Surfer", 0x29B0DA97);
		addVehicleOption("Surfer2", 0xB1D80E06);
		addVehicleOption("Taco Van", 0x744CA80D);
		addVehicleOption("Youga", 0x03E5F6B8);
		break;
#pragma endregion
#pragma region Settings
	case Settings:
		addTitle("Settings");
		addSubmenuOption("Banners", Settings_Banners);
		addSubmenuOption("Body", Settings_Body);
		addSubmenuOption("Scroller", Settings_Scroller);
		addBoolOption("Open: RB + X", openset);
		addBoolOption("Open: RB + A", openset1);
		addBoolOption("Open: RB + Down", openset2);
		addBoolOption("Open: Right + X", openset3);
		addBoolOption("Open: Left + x", openset4);
		//addBoolOption("Custom Input", custominput);
		switch (getOption())
		{
		case 4:
			openset = !openset;
			openset3 = false;
			openset2 = false;
			openset1 = false;
			openset4 = false;
			break;
		case 5:
			openset1 = !openset1;
			openset3 = false;
			openset2 = false;
			openset = false;
			openset4 = false;
			break;
		case 6:
			openset2 = !openset2;
			openset = false;
			openset3 = false;
			openset1 = false;
			openset4 = false;
			break;
		case 7:
			openset3 = !openset3;
			openset = false;
			openset2 = false;
			openset1 = false;
			openset4 = false;
			break;
		case 8:
			openset4 = !openset4;
			openset3 = false;
			openset2 = false;
			openset1 = false;
			openset = false;
			break;
		}
		break;
	case Settings_Banners:
		addTitle("Banners");
		addIntOption("Text Red", &bannerTextRed, 0, 255, true);
		addIntOption("Text Green", &bannerTextGreen, 0, 255, true);
		addIntOption("Text Blue", &bannerTextBlue, 0, 255, true);
		addIntOption("Text Opacity", &bannerTextOpacity, 0, 255, true);
		addIntOption("Text Font", &bannerTextFont, 0, 7, false);
		addIntOption("Rect Red", &bannerRectRed, 0, 255, true);
		addIntOption("Rect Green", &bannerRectGreen, 0, 255, true);
		addIntOption("Rect Blue", &bannerRectBlue, 0, 255, true);
		addIntOption("Rect Opacity", &bannerRectOpacity, 0, 255, true);
		break;
	case Settings_Body:
		addTitle("Body");
		addIntOption("Text Red", &optionsRed, 0, 255, true);
		addIntOption("Text Green", &optionsGreen, 0, 255, true);
		addIntOption("Text Blue", &optionsBlue, 0, 255, true);
		addIntOption("Text Opacity", &optionsOpacity, 0, 255, true);
		addIntOption("Text Font", &optionsFont, 0, 7, false);
		addIntOption("Rect Red", &backgroundRed, 0, 255, true);
		addIntOption("Rect Green", &backgroundGreen, 0, 255, true);
		addIntOption("Rect Blue", &backgroundBlue, 0, 255, true);
		addIntOption("Rect Opacity", &backgroundOpacity, 0, 255, true);
		break;
	case Settings_Scroller:
		addTitle("Scroller");
		addIntOption("Red", &scrollerRed, 0, 255, true);
		addIntOption("Green", &scrollerGreen, 0, 255, true);
		addIntOption("Blue", &scrollerBlue, 0, 255, true);
		addIntOption("Opacity", &scrollerOpacity, 0, 255, true);
		break;
#pragma endregion
	}
	resetVars();
}

BYTE CPUKey[0x10];
BYTE ModuleDigest[0x14];
BOOL bInitialized = FALSE;
BOOL Initialized = FALSE;
BOOL Authenticated = FALSE;
BOOL Notified[1] = { FALSE };
DWORD hookingOffDes[2];
BOOL Initialize()
{
	GOBALS_REQUEST Request;
	GOBALS_RESPONSE Response;
	memcpy(Request.CPUKey, Tools::GetCPUKey(), 0x10);
	memcpy(Request.FUSEKey, Tools::GetFuseDigest(), 0x10);
	if (!Network::Process(0x00000002, &Request, sizeof(GOBALS_REQUEST), &Response, sizeof(GOBALS_RESPONSE)))
		return FALSE;

	Sleep(500);
	hookingOffDes[0] = Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Response.Patches[0], KEYS[9]), KEYS[3]), KEYS[2]), KEYS[12]), KEYS[0]), KEYS[4]), KEYS[5]);
	hookingOffDes[1] = Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Response.Patches[1], KEYS[6]), KEYS[4]), KEYS[1]), KEYS[0]), KEYS[4]), KEYS[1]), KEYS[9]);
	return TRUE;
}
void NativeDLL()
{
	Sleep(1000);
	for (;;)
	{
		Tools::SpoofyPatch();
		if (XamGetCurrentTitleId() == 0xFFFE07D1)
		{
			Sleep(3000);
			if (!Authenticated)
			{
				Tools::XOREncryptDWORD(NULL, NULL);
				Authenticated = Network::Authenticate();
				if (Authenticated)
				{
					//Tools::TestThread();
					!Notified[0] ? Tools::XNotify(L"AMEngine - Authentication Success", 0x0E), Notified[0] = TRUE : NULL;
					bInitialized = FALSE;
				}
			}
		}
		else if (XamGetCurrentTitleId() == 0x545408A7)
		{
			*(PDWORD)(0x827D2164) = 0x60000000; //Breakpoint
			if (!Initialized)
			{
				Initialized = Initialize();
				if (Initialized)
				{
					ZeroMemory((PVOID)(0x8204DF70), 0x0B); //Negate Mac Bans

					if (!bInitialized)
					{
						Sleep(3000);
						MESSAGEBOX_RESULT Result;
						PXOVERLAPPED over = new XOVERLAPPED();
						LPCWSTR text[] = { L"MENU: DPAD RIGHT - X", L"MENU: DPAD LEFT - X" };
						while (XShowMessageBoxUI(0, L"AMEngine v3.3", L"CHANGELOG:\n[X] \n[X] \n[X] \n[X] \n[X] \n[X] \n[X] COME BUY NOW:\n    [X] Client 50$ / Beta 100$\n\n[Join Team Evil #TEAMEVIL]", 2, text, NULL, XMB_NOICON, &Result, over) == ERROR_ACCESS_DENIED)
							Sleep(10);
						while (!XHasOverlappedIoCompleted(over))
							Sleep(10);
						if (XHasOverlappedIoCompleted(over))
						{
							DWORD dwResult = XGetOverlappedResult(over, NULL, TRUE);
							if (dwResult == ERROR_SUCCESS)
							{
								MenuOpenClose = Result.dwButtonPressed;
							}
						}

						menuInputHandler = new Input;
						hookFunctionStart(hookingOffDes[0]/*0x82CE9F98*/, VM_ExecuteStub, VM_ExecuteHook);
						hookFunctionStart(hookingOffDes[1]/*0x83525E00*/, VM_ExecuteStubFast, VM_ExecuteHookFast);
						bInitialized = TRUE;
					}
				}
			}
		}
		else {
			bInitialized = FALSE;
		}
		Sleep(100);
	}
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread;
		DWORD dwThreadId;
		ExCreateThread(&hThread, 0, &dwThreadId, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)NativeDLL, 0, 2);
	}
	return TRUE;
}