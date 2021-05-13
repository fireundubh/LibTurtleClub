#include "Registration.h"

#include "PapyrusActor.h"
#include "PapyrusMisc.h"

namespace Papyrus
{
	void Register()
	{
		const auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(PapyrusActor::RegisterFuncs);
		logger::info("Registered actor functions");

		papyrus->Register(PapyrusMisc::RegisterFuncs);
		logger::info("Registered misc functions");
	}
}