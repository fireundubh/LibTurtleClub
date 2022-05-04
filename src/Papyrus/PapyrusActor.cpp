#pragma once

#pragma warning(disable : 4100)

#include "PapyrusActor.h"


namespace PapyrusActor
{
	auto GetFactionStates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> std::vector<bool>
	{
		std::vector<bool> vec;

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
			return vec;
		}

		if (!a_factions) {
			a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
			return vec;
		}

		for (auto* form : a_factions->forms) {
			if (form) {
				auto* faction = form->As<RE::TESFaction>();

				vec.push_back(faction != nullptr && a_actor->IsInFaction(faction));

				continue;
			}

			vec.push_back(false);
		}

		return vec;
	}

	auto GetWornEquipment(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, bool a_leftWeapon, bool a_rightWeapon) -> std::vector<RE::TESForm*>
	{
		std::vector<RE::TESForm*> vec;

		std::vector<std::uint32_t> a_slots = {};

		if (!a_actor) {
			a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kInfo);
			return vec;
		}

		auto* changes = a_actor->GetInventoryChanges();

		if (!changes) {
			a_vm->TraceStack("akActor does not have inventory", a_stackID, Severity::kInfo);
			return vec;
		}

		vec.push_back(changes->GetArmorInSlot(31));
		vec.push_back(changes->GetArmorInSlot(32));
		vec.push_back(changes->GetArmorInSlot(33));
		vec.push_back(changes->GetArmorInSlot(35));
		vec.push_back(changes->GetArmorInSlot(36));
		vec.push_back(changes->GetArmorInSlot(37));
		vec.push_back(changes->GetArmorInSlot(39));
		vec.push_back(changes->GetArmorInSlot(42));

		if (a_leftWeapon) {
			auto* lweapon = a_actor->GetEquippedObject(true);
			vec.push_back(lweapon);
		}

		if (a_rightWeapon) {
			auto* rweapon = a_actor->GetEquippedObject(false);
			vec.push_back(rweapon);
		}

		return vec;
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusActor - cannot get VMState"sv);
			return false;
		}

		a_vm->RegisterFunction("GetFactionStates"sv, PROJECT_NAME, GetFactionStates);
		a_vm->RegisterFunction("GetWornEquipment"sv, PROJECT_NAME, GetWornEquipment);

		return true;
	}
}