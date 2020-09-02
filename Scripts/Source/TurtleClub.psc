ScriptName TurtleClub Hidden


{ Actor }

; Returns true if akActor has any keyword in akKeywords
Bool Function ActorHasAnyKeyword(Actor akActor, FormList akKeywords) Global Native

; Returns true if akActor is a member of any faction in akFactions (faction rank must be > -1)
Bool Function ActorIsInAnyFaction(Actor akActor, FormList akFactions) Global Native

; Returns true if akActor is a member of akFaction (faction rank must be > -1)
Bool Function ActorIsInFaction(Actor akActor, Faction akFaction) Global Native

; Iterates through akFactions, returning IsInFaction array for akActor (does not evaluate faction rank)
Bool[] Function GetFactionStates(Actor akActor, FormList akFactions) Global Native

; Returns array of forms equipped by akActor in slots 31, 32, 33, 35, 36, 37, 39, and 42
Form[] Function GetWornEquipment(Actor akActor) Global Native


{ Faction }

; Sets akFaction as ally or friend to each faction in akFactions
Function SetAllies(Faction akFaction, FormList akFactions, Bool abSelfIsFriendToOther = False, Bool abOtherIsFriendToSelf = False) Global Native

; Sets akFaction as enemy or neutral to each faction in akFactions
Function SetEnemies(Faction akFaction, FormList akFactions, Bool abSelfIsNeutralToOther = False, Bool abOtherIsNeutralToSelf = False) Global Native


{ Misc }

; Search akFormlist for akBaseObjects
Bool[] Function SearchListForForms(FormList akFormList, Form[] akNeedles) Global Native

; Search formlists in akFormlist for akBaseObject
Bool[] Function SearchListsForForm(FormList akFormList, Form akNeedle) Global Native

; Returns true if current game time (converted to 24-hour clock) is between afMin and less than afMax
Bool Function InRangeGameTime(Float afMin, Float afMax) Global Native

; Returns index to akPlayerRace in akRaces after checking if akPlayerRace is mapped to aiFactionIndex
Int Function LookupRaceWeightIndex(Int aiFactionIndex, Race akPlayerRace, Race[] akRaces) Global Native


{ String }

; Returns asSource as array of String split by asDelimiter
String[] Function SplitString(String asSource, String asDelimiter) Global Native

; Returns asSource as array of Float split by asDelimiter
Float[] Function StrToFloatArray(String asSource, String asDelimiter) Global Native

; Returns asSource as array of Int split by asDelimiter
Int[] Function StrToIntArray(String asSource, String asDelimiter) Global Native

; Returns asSource wrapped to column aiMaxLength with lines delimited by newline character
String Function WrapString(String asSource, Int aiMaxLength) Global Native
