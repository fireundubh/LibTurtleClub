#pragma once

#include "PapyrusActor.h"


auto PapyrusActor::ActorHasAnyKeyword(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_keywords) -> bool
{
	if (!a_actor)
	{
		a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	if (!a_keywords)
	{
		a_vm->TraceStack("akKeywords cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	for (auto& form : a_keywords->forms)
	{
		if (form == nullptr)
			continue;

		auto* const keyword = form->As<RE::BGSKeyword>();

		if (keyword && a_actor->HasKeyword(keyword))
			return true;
	}

	return false;
}


auto PapyrusActor::ActorIsInAnyFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> bool
{
	if (!a_actor)
	{
		a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	if (!a_factions)
	{
		a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	auto* base = a_actor->GetActorBase();

	if (base)
	{
		auto* factionChanges = a_actor->extraList.GetByType<RE::ExtraFactionChanges>();

		if (factionChanges)
		{
			for (auto& change : factionChanges->factionChanges)
			{
				if (a_factions->HasForm(change.faction) && change.rank > -1)
				{
					return true;
				}
			}
		}
		
		for (auto& factionInfo : base->factions)
		{
			if (a_factions->HasForm(factionInfo.faction) && factionInfo.rank > -1)
			{
				return true;
			}
		}
	}

	return false;
}


auto PapyrusActor::ActorIsInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::TESFaction* a_faction) -> bool
{
	if (!a_actor)
	{
		a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	if (!a_faction)
	{
		a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
		return false;
	}

	auto* base = a_actor->GetActorBase();
	
	if (base)
	{
		auto* factionChanges = a_actor->extraList.GetByType<RE::ExtraFactionChanges>();

		if (factionChanges)
		{
			for (auto& change : factionChanges->factionChanges)
			{
				if (change.faction == a_faction && change.rank > -1)
				{
					return true;
				}
			}
		}
		
		for (auto& factionInfo : base->factions)
		{
			if (factionInfo.faction == a_faction && factionInfo.rank > -1)
			{
				return true;
			}
		}
	}

	return false;
}


auto PapyrusActor::GetFactionStates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> std::vector<bool>
{
	std::vector<bool> vec;

	if (!a_actor)
	{
		a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	if (!a_factions)
	{
		a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	for (auto* form : a_factions->forms)
	{
		if (form)
		{
			auto* faction = form->As<RE::TESFaction>();

			vec.push_back(faction == nullptr ? false : a_actor->IsInFaction(faction));

			continue;
		}

		vec.push_back(false);
	}

	return vec;
}


auto PapyrusActor::GetWornEquipment(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> std::vector<RE::TESForm*>
{
	std::vector<RE::TESForm*> vec;

	if (!a_actor)
	{
		a_vm->TraceStack("akActor cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	auto* changes = a_actor->GetInventoryChanges();

	if (!changes)
	{
		a_vm->TraceStack("akActor does not have any inventory", a_stackID, Severity::kWarning);
		return vec;
	}

	for (auto slot : SLOTS)
	{
		auto* const armor = changes->GetArmorInSlot(slot);
		vec.push_back(armor);
	}

	auto* lweapon = a_actor->GetEquippedObject(true);
	auto* rweapon = a_actor->GetEquippedObject(false);

	vec.push_back(lweapon);
	vec.push_back(rweapon);

	return vec;
}


auto PapyrusActor::RegisterFuncs(VM* a_vm) -> bool
{
	if (!a_vm)
	{
		logger::info("PapyrusActor - cannot get VMState");
		return false;
	}

	a_vm->RegisterFunction("ActorHasAnyKeyword", "TurtleClub", ActorHasAnyKeyword);
	a_vm->RegisterFunction("ActorIsInAnyFaction", "TurtleClub", ActorIsInAnyFaction);
	a_vm->RegisterFunction("ActorIsInFaction", "TurtleClub", ActorIsInFaction);
	a_vm->RegisterFunction("GetFactionStates", "TurtleClub", GetFactionStates);
	a_vm->RegisterFunction("GetWornEquipment", "TurtleClub", GetWornEquipment);

	return true;
}
