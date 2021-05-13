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

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusActor - cannot get VMState");
			return false;
		}

		a_vm->RegisterFunction("GetFactionStates", PROJECT_NAME, GetFactionStates);

		return true;
	}
}