#pragma once

#include "PapyrusFaction.h"


auto PapyrusFaction::SetAllies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsFriendToOther, const bool a_otherIsFriendToSelf) -> void
{
	if (!a_faction)
	{
		a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
		return;
	}

	if (!a_factions)
	{
		a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
		return;
	}

	for (auto& form : a_factions->forms)
	{
		if (form == nullptr)
			continue;

		auto* const otherFaction = form->As<RE::TESFaction>();

		if (otherFaction == nullptr)
			continue;

		a_faction->SetFactionFightReaction(otherFaction, a_selfIsFriendToOther ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);
		otherFaction->SetFactionFightReaction(a_faction, a_otherIsFriendToSelf ? RE::FIGHT_REACTION::kFriend : RE::FIGHT_REACTION::kAlly);
	}

	auto* const processLists = RE::ProcessLists::GetSingleton();

	if (processLists)
	{
		processLists->ClearCachedFactionFightReactions();
	}
}


auto PapyrusFaction::SetEnemies(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::TESFaction* a_faction, RE::BGSListForm* a_factions, const bool a_selfIsNeutralToOther, const bool a_otherIsNeutralToSelf) -> void
{
	if (!a_faction)
	{
		a_vm->TraceStack("akFaction cannot be None", a_stackID, Severity::kWarning);
		return;
	}

	if (!a_factions)
	{
		a_vm->TraceStack("akFactions cannot be None", a_stackID, Severity::kWarning);
		return;
	}

	for (auto& form : a_factions->forms)
	{
		if (form == nullptr)
			continue;

		auto* const otherFaction = form->As<RE::TESFaction>();

		if (otherFaction == nullptr)
			continue;

		a_faction->SetFactionFightReaction(otherFaction, a_selfIsNeutralToOther ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);
		otherFaction->SetFactionFightReaction(a_faction, a_otherIsNeutralToSelf ? RE::FIGHT_REACTION::kNeutral : RE::FIGHT_REACTION::kEnemy);
	}

	auto* const processLists = RE::ProcessLists::GetSingleton();

	if (processLists)
	{
		processLists->ClearCachedFactionFightReactions();
	}
}


auto PapyrusFaction::RegisterFuncs(VM* a_vm) -> bool
{
	if (!a_vm)
	{
		logger::info("PapyrusFaction - cannot get VMState");
		return false;
	}

	a_vm->RegisterFunction("SetAllies", "TurtleClub", SetAllies);
	a_vm->RegisterFunction("SetEnemies", "TurtleClub", SetEnemies);

	return true;
}
