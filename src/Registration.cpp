#include "Registration.h"

#include "PapyrusActor.h"
#include "PapyrusFaction.h"
#include "PapyrusMisc.h"
#include "PapyrusString.h"

void Papyrus::Register()
{
	const auto papyrus = SKSE::GetPapyrusInterface();

	papyrus->Register(PapyrusActor::RegisterFuncs);
	logger::info("Registered actor functions");

	papyrus->Register(PapyrusFaction::RegisterFuncs);
	logger::info("Registered faction functions");

	papyrus->Register(PapyrusMisc::RegisterFuncs);
	logger::info("Registered misc functions");

	papyrus->Register(PapyrusString::RegisterFuncs);
	logger::info("Registered string functions");
}
