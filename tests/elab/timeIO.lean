import Std.Time
import Init
open Std.Time

/-
Test for quantity
-/

#eval do
  let res ← Database.defaultGetZoneRules "America/Sao_Paulo"
  if res.transitions.size < 1 then
    throw <| IO.userError "invalid quantity for America/Sao_Paulo"

/--
info: { second := 0 }
-/
#guard_msgs in
#eval do
  let res ← Database.defaultGetZoneRules "UTC"
  println! repr res.initialLocalTimeType.gmtOffset

/-
The idea is just to check if there's no errors while computing the local zone rules.
-/
#eval do
  discard <| Database.defaultGetLocalZoneRules

/-
Java:
2013-10-19T23:59:59-03:00[America/Sao_Paulo] 1382237999
2013-10-20T01:00-02:00[America/Sao_Paulo] 1382238000
2013-10-20T01:00:01-02:00[America/Sao_Paulo] 1382238001
-/

/--
info: 2013-10-19T23:59:59.000000000-03:00
2013-10-20T00:00:00.000000000-02:00
2013-10-20T00:00:01.000000000-02:00
-/
#guard_msgs in
#eval do
  let zr ← Database.defaultGetZoneRules "America/Sao_Paulo"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2013-10-19T23:59:59") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2013-10-20T00:00:00") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2013-10-20T00:00:01") zr |>.toLeanDateTimeWithZoneString}"

/-
Java:
2019-11-03T01:59:59-05:00[America/Chicago] 1572764399
2019-11-03T02:00-06:00[America/Chicago] 1572768000
2019-11-03T02:59:59-06:00[America/Chicago] 1572771599
-/

/--
info: 2019-11-03T01:59:59.000000000-05:00
2019-11-03T02:00:00.000000000-06:00
2019-11-03T02:59:59.000000000-06:00
-/
#guard_msgs in
#eval do
  let zr ← Database.defaultGetZoneRules "America/Chicago"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2019-11-03T01:59:59") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2019-11-03T02:00:00") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2019-11-03T02:59:59") zr |>.toLeanDateTimeWithZoneString}"

/-
Java:
2003-10-26T01:59:59-05:00[America/Monterrey] 1067151599
2003-10-26T02:00-06:00[America/Monterrey] 1067155200
2003-10-26T02:59:59-06:00[America/Monterrey] 1067158799
-/

/--
info: 2003-10-26T01:59:59.000000000-05:00
2003-10-26T02:00:00.000000000-06:00
2003-10-26T02:59:59.000000000-06:00
-/
#guard_msgs in
#eval do
  let zr ← Database.defaultGetZoneRules "America/Monterrey"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2003-10-26T01:59:59") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2003-10-26T02:00:00") zr |>.toLeanDateTimeWithZoneString}"
  println! "{ZonedDateTime.ofPlainDateTime datetime("2003-10-26T02:59:59") zr |>.toLeanDateTimeWithZoneString}"

-- ZoneRules.findTransitionForTimestamp: a timestamp one second before the first transition
-- uses initialLocalTimeType (LMT), not the first post-transition type.
/--
info: true
-/
#guard_msgs in
#eval show IO Bool from do
  let rules ← Database.defaultGetZoneRules "America/New_York"
  if h : 0 < rules.transitions.size then
    let first := rules.transitions[0]
    let beforeFirst := Timestamp.ofSecondsSinceUnixEpoch ⟨first.time.val - 1⟩
    let zdt := ZonedDateTime.ofTimestamp beforeFirst rules
    return zdt.timezone.name == rules.initialLocalTimeType.identifier
  else
    return true

-- ZonedDateTime.ofPlainDateTime resolves local wall-clock time using the correct offset sign.
-- UTC+2 → UTC+3 spring-forward at UTC t=3600: gap is local 03:00–04:00.
def bugZonePlus : TimeZone.ZoneRules :=
  let before : TimeZone.LocalTimeType := {
    gmtOffset := .ofSeconds 7200,
    isDst := false, abbreviation := "TST2",
    wall := .standard, utLocal := .ut, identifier := "Test/Plus2"
  }
  let after : TimeZone.LocalTimeType := {
    gmtOffset := .ofSeconds 10800,
    isDst := true, abbreviation := "TST3",
    wall := .standard, utLocal := .ut, identifier := "Test/Plus3"
  }
  { initialLocalTimeType := before, transitions := #[⟨3600, after⟩] }

/--
info: "Test/Plus2"
-/
#guard_msgs in
#eval
  let pdt : PlainDateTime :=
    ⟨PlainDate.ofYearMonthDayClip 1970 1 1, PlainTime.ofHourMinuteSecondsNano 2 30 0 0⟩
  (ZonedDateTime.ofPlainDateTime pdt bugZonePlus).timezone.name

/--
info: "Test/Plus3"
-/
#guard_msgs in
#eval
  let pdt : PlainDateTime :=
    ⟨PlainDate.ofYearMonthDayClip 1970 1 1, PlainTime.ofHourMinuteSecondsNano 4 30 0 0⟩
  (ZonedDateTime.ofPlainDateTime pdt bugZonePlus).timezone.name
