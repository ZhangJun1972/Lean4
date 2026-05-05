import Std.Time
open Std.Time

-- Reference date: Sunday, July 14, 2002 23:13:12.324354679 UTC+09:00 (Q3, week 28, day 195)
def td := zoned("2002-07-14T23:13:12.324354679+09:00")

-- Same date/time at UTC (for UTC timezone name tests)
def tdUTC := zoned("2002-07-14T23:13:12.324354679+00:00")

-- AM hour (09:13:12 for AM/PM tests)
def tdAM := zoned("2002-07-14T09:13:12.000000000+09:00")

-- Exact noon and midnight (for day-period tests)
def tdNoon := zoned("2002-07-14T12:00:00.000000000+09:00")
def tdMidnight := zoned("2002-07-14T00:00:00.000000000+09:00")
def tdWeekMonth := zoned("2002-08-05T23:13:12.324354679+09:00")

-- Named timezone (for z/V name tests)
def tokyoTZ : TimeZone := { offset := { second := 32400 }, name := "Asia/Tokyo", abbreviation := "JST", isDST := false }

def tdNamed := ZonedDateTime.ofPlainDateTime td.toPlainDateTime (TimeZone.ZoneRules.ofTimeZone tokyoTZ)

-- Week-based year boundary: Dec 31, 2018 is in ISO week 1 of 2019
def tdWeekBound := ZonedDateTime.ofPlainDateTime datetime("2018-12-31T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)

-- Additional week-based year boundary cases
-- Jan 1, 2017 (Sunday) → ISO week 52 of 2016
def tdWeekBound2 := ZonedDateTime.ofPlainDateTime datetime("2017-01-01T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)
-- Jan 2, 2017 (Monday) → ISO week 1 of 2017
def tdWeekBound3 := ZonedDateTime.ofPlainDateTime datetime("2017-01-02T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)
-- Dec 31, 2019 (Tuesday) → ISO week 1 of 2020
def tdWeekBound4 := ZonedDateTime.ofPlainDateTime datetime("2019-12-31T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)
-- Jan 1, 2021 (Friday) → ISO week 53 of 2020
def tdWeekBound5 := ZonedDateTime.ofPlainDateTime datetime("2021-01-01T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)
-- Jan 4, 2021 (Monday) → ISO week 1 of 2021
def tdWeekBound6 := ZonedDateTime.ofPlainDateTime datetime("2021-01-04T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)

-- Jan 1 (day 1) for D zero-padding tests
def tdJan1 := zoned("2002-01-01T12:00:00.000000000+09:00")

-- Exact noon/midnight with sub-second nanos (b bug fix verification)
def tdNoonNano     := zoned("2002-07-14T12:00:00.000000001+09:00")
def tdMidnightNano := zoned("2002-07-14T00:00:00.000000001+09:00")

-- Small fractional-second values (S truncation fix verification)
-- 10ms = 10_000_000 ns  →  "010..." not "100..."
def tdTenMs  := zoned("2002-07-14T23:13:12.010000000+09:00")
-- 1ms = 1_000_000 ns   →  "001..."
def tdOneMs  := zoned("2002-07-14T23:13:12.001000000+09:00")
-- 1ns = 1 ns           →  "000000001"
def tdOneNs  := zoned("2002-07-14T23:13:12.000000001+09:00")

-- PlainTime values for b-on-PlainTime tests
def ptNoon         := time("12:00:00.000000000")
def ptMidnight     := time("00:00:00.000000000")
def ptAM           := time("09:13:12.000000000")
def ptPM           := time("23:13:12.000000000")
def ptNoonNano     := time("12:00:00.000000001")
def ptMidnightNano := time("00:00:00.000000001")

-- Aligned week-of-month edge cases: Aug 1/4/5/11/12 2002
def tdAug1  := zoned("2002-08-01T12:00:00.000000000+09:00")  -- Thu, W=1 (week Jul28–Aug3)
def tdAug4  := zoned("2002-08-04T12:00:00.000000000+09:00")  -- Sun, W=2 (starts week Aug4–10)
def tdAug12 := zoned("2002-08-12T12:00:00.000000000+09:00")  -- Mon, W=3 (week Aug11–17)

-- ─────────────────────────────────────────────────────────────────────────────
-- G  Era
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval td.format "G GG GGG GGGG GGGGG"

-- ─────────────────────────────────────────────────────────────────────────────
-- y  Year of era
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "2002 02 2002 02002 000002002"
-/
#guard_msgs in
#eval td.format "y yy yyyy yyyyy yyyyyyyyy"

-- ─────────────────────────────────────────────────────────────────────────────
-- Y  Week-based year
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "2002 02 2002 02002 000002002"
-/
#guard_msgs in
#eval td.format "Y YY YYYY YYYYY YYYYYYYYY"

-- Boundary: Dec 31, 2018 belongs to ISO week 1 of 2019
/--
info: "2019 19 2019"
-/
#guard_msgs in
#eval tdWeekBound.format "Y YY YYYY"

-- ─────────────────────────────────────────────────────────────────────────────
-- u  Extended year (signed, no era flip)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "2002 02 2002 02002 000002002"
-/
#guard_msgs in
#eval td.format "u uu uuuu uuuuu uuuuuuuuu"

-- ─────────────────────────────────────────────────────────────────────────────
-- Q / q  Quarter (Q = formatting, q = standalone — same output here)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "3 03 Q3 3rd quarter 3"
-/
#guard_msgs in
#eval td.format "Q QQ QQQ QQQQ QQQQQ"

/--
info: "3 03 Q3 3rd quarter 3"
-/
#guard_msgs in
#eval td.format "q qq qqq qqqq qqqqq"

-- ─────────────────────────────────────────────────────────────────────────────
-- M / L  Month (M = formatting, L = standalone — same output here)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "7 07 Jul July J"
-/
#guard_msgs in
#eval td.format "M MM MMM MMMM MMMMM"

/--
info: "7 07 Jul July J"
-/
#guard_msgs in
#eval td.format "L LL LLL LLLL LLLLL"

-- ─────────────────────────────────────────────────────────────────────────────
-- w  Week of week-based year
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "28 28"
-/
#guard_msgs in
#eval td.format "w ww"

-- ─────────────────────────────────────────────────────────────────────────────
-- W  Week of month (Sun-first, US locale)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "3"
-/
#guard_msgs in
#eval td.format "W"

-- ─────────────────────────────────────────────────────────────────────────────
-- d  Day of month
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "14 14"
-/
#guard_msgs in
#eval td.format "d dd"

-- ─────────────────────────────────────────────────────────────────────────────
-- D  Day of year
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "195 195 195"
-/
#guard_msgs in
#eval td.format "D DD DDD"

-- ─────────────────────────────────────────────────────────────────────────────
-- F  Day-of-week-in-month / occurrence within the month
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "2"
-/
#guard_msgs in
#eval td.format "F"

/--
info: "2 1"
-/
#guard_msgs in
#eval tdWeekMonth.format "W F"

-- ─────────────────────────────────────────────────────────────────────────────
-- E  Day of week (text only)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval td.format "E EE EEE EEEE EEEEE"

-- ─────────────────────────────────────────────────────────────────────────────
-- e  Localized day of week (count 1-2 = numeric ordinal, 3-5 = text)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "7 07 Sun Sunday S"
-/
#guard_msgs in
#eval td.format "e ee eee eeee eeeee"

-- ─────────────────────────────────────────────────────────────────────────────
-- c  Standalone day of week (count 1 = numeric, 3-5 = text)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "7 Sun Sunday S"
-/
#guard_msgs in
#eval td.format "c ccc cccc ccccc"

-- ─────────────────────────────────────────────────────────────────────────────
-- a  AM/PM marker (counts 1-3 = short, 4 = full, 5 = narrow)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "PM"
-/
#guard_msgs in
#eval td.format "a"

/--
info: "AM"
-/
#guard_msgs in
#eval tdAM.format "a"

/--
info: "PM PM PM post meridiem p"
-/
#guard_msgs in
#eval td.format "a aa aaa aaaa aaaaa"

/--
info: "AM AM AM ante meridiem a"
-/
#guard_msgs in
#eval tdAM.format "a aa aaa aaaa aaaaa"

-- ─────────────────────────────────────────────────────────────────────────────
-- b  Day period (counts 1-3 = short, 4 = full, 5 = narrow)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "PM PM PM PM p"
-/
#guard_msgs in
#eval td.format "b bb bbb bbbb bbbbb"

/--
info: "AM AM AM AM a"
-/
#guard_msgs in
#eval tdAM.format "b bb bbb bbbb bbbbb"

/--
info: "noon noon noon noon n"
-/
#guard_msgs in
#eval tdNoon.format "b bb bbb bbbb bbbbb"

/--
info: "midnight midnight midnight midnight mi"
-/
#guard_msgs in
#eval tdMidnight.format "b bb bbb bbbb bbbbb"

-- ─────────────────────────────────────────────────────────────────────────────
-- H  Hour of day (0-23)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "23 23"
-/
#guard_msgs in
#eval td.format "H HH"

-- ─────────────────────────────────────────────────────────────────────────────
-- h  Clock hour of AM/PM (1-12)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "11 11"
-/
#guard_msgs in
#eval td.format "h hh"

-- ─────────────────────────────────────────────────────────────────────────────
-- K  Hour of AM/PM (0-11)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "11 11"
-/
#guard_msgs in
#eval td.format "K KK"

-- ─────────────────────────────────────────────────────────────────────────────
-- k  Clock hour of day (1-24)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "23 23"
-/
#guard_msgs in
#eval td.format "k kk"

-- ─────────────────────────────────────────────────────────────────────────────
-- m  Minute
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "13 13"
-/
#guard_msgs in
#eval td.format "m mm"

-- ─────────────────────────────────────────────────────────────────────────────
-- s  Second
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "12 12"
-/
#guard_msgs in
#eval td.format "s ss"

-- ─────────────────────────────────────────────────────────────────────────────
-- S  Fractional seconds (truncated from nanoseconds)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "3 32 324 3243 324354679"
-/
#guard_msgs in
#eval td.format "S SS SSS SSSS SSSSSSSSS"

-- ─────────────────────────────────────────────────────────────────────────────
-- A  Milliseconds since midnight
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "83592324 83592324 83592324 83592324 083592324"
-/
#guard_msgs in
#eval td.format "A AA AAA AAAA AAAAAAAAA"

-- ─────────────────────────────────────────────────────────────────────────────
-- n  Nanosecond (Lean/Java extension; minimum width, no truncation)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "324354679 324354679 324354679 324354679 324354679"
-/
#guard_msgs in
#eval td.format "n nn nnn nnnn nnnnnnnnn"

-- ─────────────────────────────────────────────────────────────────────────────
-- N  Nanoseconds since midnight (Lean/Java extension; minimum width, no truncation)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "83592324354679 83592324354679 83592324354679 83592324354679 83592324354679"
-/
#guard_msgs in
#eval td.format "N NN NNN NNNN NNNNNNNNN"

-- ─────────────────────────────────────────────────────────────────────────────
-- z  Time zone name (short = abbreviation/id, full = long name)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "+09:00 +09:00 +09:00 +09:00"
-/
#guard_msgs in
#eval td.format "z zz zzz zzzz"

/--
info: "Z Z Z Z"
-/
#guard_msgs in
#eval tdUTC.format "z zz zzz zzzz"

/--
info: "JST JST JST Asia/Tokyo"
-/
#guard_msgs in
#eval tdNamed.format "z zz zzz zzzz"

-- ─────────────────────────────────────────────────────────────────────────────
-- Z  Zone offset
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "+0900 +0900 +0900 GMT+09:00 +09:00"
-/
#guard_msgs in
#eval td.format "Z ZZ ZZZ ZZZZ ZZZZZ"

/--
info: "+0000 +0000 +0000 GMT Z"
-/
#guard_msgs in
#eval tdUTC.format "Z ZZ ZZZ ZZZZ ZZZZZ"

-- ─────────────────────────────────────────────────────────────────────────────
-- O  Localized GMT offset
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "GMT+9 GMT+09:00"
-/
#guard_msgs in
#eval td.format "O OOOO"

/--
info: "GMT GMT"
-/
#guard_msgs in
#eval tdUTC.format "O OOOO"

-- ─────────────────────────────────────────────────────────────────────────────
-- V  Zone ID: V=unknown placeholder ("unk"), VV=IANA ID; VVV/VVVV rejected
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "+09:00"
-/
#guard_msgs in
#eval td.format "VV"

-- UTC offset-only zone: normalized to "Z" (Java VV behavior)
/--
info: "Z"
-/
#guard_msgs in
#eval tdUTC.format "VV"

/--
info: "Asia/Tokyo"
-/
#guard_msgs in
#eval tdNamed.format "VV"

-- V (1 letter): Unicode CLDR unknown zone placeholder, always "unk"
/--
info: "unk"
-/
#guard_msgs in
#eval td.format "V"

/--
info: "error: offset 3: invalid quantity of characters for 'V': must be 1 or 2"
-/
#guard_msgs in
#eval td.format "VVV"

/--
info: "error: offset 4: invalid quantity of characters for 'V': must be 1 or 2"
-/
#guard_msgs in
#eval td.format "VVVV"

/--
info: "error: offset 3: invalid quantity of characters for 'd'"
-/
#guard_msgs in
#eval td.format "ddd"

/--
info: "error: offset 3: invalid quantity of characters for 'w'"
-/
#guard_msgs in
#eval td.format "www"

/--
info: "error: offset 2: invalid quantity of characters for 'W'"
-/
#guard_msgs in
#eval td.format "WW"

/--
info: "error: offset 2: invalid quantity of characters for 'F'"
-/
#guard_msgs in
#eval td.format "FF"

/--
info: "Su"
-/
#guard_msgs in
#eval td.format "EEEEEE"

/--
info: "Su"
-/
#guard_msgs in
#eval td.format "eeeeee"

/--
info: "error: offset 2: invalid quantity of characters for 'c'"
-/
#guard_msgs in
#eval td.format "cc"

/--
info: "Su"
-/
#guard_msgs in
#eval td.format "cccccc"

/--
info: "error: offset 6: invalid quantity of characters for 'a'"
-/
#guard_msgs in
#eval td.format "aaaaaa"

/--
info: "error: offset 3: invalid quantity of characters for 'H'"
-/
#guard_msgs in
#eval td.format "HHH"

-- ─────────────────────────────────────────────────────────────────────────────
-- v  Generic timezone name (no DST distinction; short = abbreviation, full = name)
-- ─────────────────────────────────────────────────────────────────────────────

-- offset-only zone: short = raw offset, full = raw offset (same as z)
/--
info: "+09:00 +09:00"
-/
#guard_msgs in
#eval td.format "v vvvv"

-- UTC offset-only: normalized to "Z" (same as z/VV)
/--
info: "Z Z"
-/
#guard_msgs in
#eval tdUTC.format "v vvvv"

-- named zone: short = abbreviation, full = IANA name
/--
info: "JST Asia/Tokyo"
-/
#guard_msgs in
#eval tdNamed.format "v vvvv"

-- ─────────────────────────────────────────────────────────────────────────────
-- X  ISO 8601 offset (uses Z for UTC)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "+09 +0900 +09:00 +0900 +09:00"
-/
#guard_msgs in
#eval td.format "X XX XXX XXXX XXXXX"

/--
info: "Z Z Z Z Z"
-/
#guard_msgs in
#eval tdUTC.format "X XX XXX XXXX XXXXX"

-- ─────────────────────────────────────────────────────────────────────────────
-- x  ISO 8601 offset (no Z for UTC)
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "+09 +0900 +09:00 +0900 +09:00"
-/
#guard_msgs in
#eval td.format "x xx xxx xxxx xxxxx"

/--
info: "+00 +0000 +00:00 +0000 +00:00"
-/
#guard_msgs in
#eval tdUTC.format "x xx xxx xxxx xxxxx"

-- ─────────────────────────────────────────────────────────────────────────────
-- Y  Week-based year: extended boundary cases
-- ─────────────────────────────────────────────────────────────────────────────

-- Jan 1, 2017 is Sunday → ISO week 52 of 2016 (week Dec 26–Jan 1, more days in 2016)
/--
info: "2016 16 2016"
-/
#guard_msgs in
#eval tdWeekBound2.format "Y YY YYYY"

-- Jan 2, 2017 is Monday → ISO week 1 of 2017 (week Jan 2–8, contains Jan 5 Thu)
/--
info: "2017 17 2017"
-/
#guard_msgs in
#eval tdWeekBound3.format "Y YY YYYY"

-- Dec 31, 2019 is Tuesday → belongs to ISO week 1 of 2020
/--
info: "2020 20 2020"
-/
#guard_msgs in
#eval tdWeekBound4.format "Y YY YYYY"

-- Jan 1, 2021 is Friday → ISO week 53 of 2020 (week Dec 28–Jan 3, more days in 2020)
/--
info: "2020 20 2020"
-/
#guard_msgs in
#eval tdWeekBound5.format "Y YY YYYY"

-- Jan 4, 2021 is Monday → ISO week 1 of 2021 (week Jan 4–10, contains Jan 7 Thu)
/--
info: "2021 21 2021"
-/
#guard_msgs in
#eval tdWeekBound6.format "Y YY YYYY"

-- ─────────────────────────────────────────────────────────────────────────────
-- w  Week of year paired with Y: check they agree at boundaries
-- ─────────────────────────────────────────────────────────────────────────────

-- Jan 1, 2017 (Sun) → ISO Y=2016 w=52
/--
info: "2016 52"
-/
#guard_msgs in
#eval tdWeekBound2.format "Y w"

-- Jan 2, 2017 (Mon) → ISO Y=2017 w=1
/--
info: "2017 1"
-/
#guard_msgs in
#eval tdWeekBound3.format "Y w"

-- Dec 31, 2019 (Tue) → ISO Y=2020 w=1 (week Dec 30–Jan 5, contains Jan 2 Thu)
/--
info: "2020 1"
-/
#guard_msgs in
#eval tdWeekBound4.format "Y w"

-- Jan 1, 2021 (Fri) → ISO Y=2020 w=53
/--
info: "2020 53"
-/
#guard_msgs in
#eval tdWeekBound5.format "Y w"

-- Jan 4, 2021 (Mon) → ISO Y=2021 w=1 (week Jan 4–10 is ISO week 1 of 2021)
/--
info: "2021 1"
-/
#guard_msgs in
#eval tdWeekBound6.format "Y w"

-- ─────────────────────────────────────────────────────────────────────────────
-- D  Day of year: zero-padding with count 1/2/3 for day 1
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "1 01 001"
-/
#guard_msgs in
#eval tdJan1.format "D DD DDD"

-- ─────────────────────────────────────────────────────────────────────────────
-- W  Week-of-month (US locale, Sun-first, minDays=1)
-- ─────────────────────────────────────────────────────────────────────────────

-- Aug 1 (Thu): week Jul 28–Aug 3, week 1 of Aug → W=1
/--
info: "1"
-/
#guard_msgs in
#eval tdAug1.format "W"

-- Aug 4 (Sun): starts week Aug 4–10, week 2 of Aug → W=2
/--
info: "2"
-/
#guard_msgs in
#eval tdAug4.format "W"

-- Aug 5 (Mon): in week Aug 4–10, week 2 of Aug → W=2
/--
info: "2"
-/
#guard_msgs in
#eval tdWeekMonth.format "W"

-- Aug 12 (Mon): in week Aug 11–17, week 3 of Aug → W=3
/--
info: "3"
-/
#guard_msgs in
#eval tdAug12.format "W"

-- ─────────────────────────────────────────────────────────────────────────────
-- h / K / k  Hour edge cases: midnight (H=0) and noon (H=12)
-- ─────────────────────────────────────────────────────────────────────────────

-- midnight: H=0, h=12, K=0, k=24
/--
info: "0 12 0 24"
-/
#guard_msgs in
#eval tdMidnight.format "H h K k"

-- noon: H=12, h=12, K=0, k=12
/--
info: "12 12 0 12"
-/
#guard_msgs in
#eval tdNoon.format "H h K k"

-- ─────────────────────────────────────────────────────────────────────────────
-- S  Fractional seconds: truncation for values < 10^8 nanoseconds
-- ─────────────────────────────────────────────────────────────────────────────

-- 10ms = 10_000_000 ns → left-pad to 9 → "010000000"
/--
info: "0 01 010 0100 010000000"
-/
#guard_msgs in
#eval tdTenMs.format "S SS SSS SSSS SSSSSSSSS"

-- 1ms = 1_000_000 ns → "001000000"
/--
info: "0 00 001 0010 001000000"
-/
#guard_msgs in
#eval tdOneMs.format "S SS SSS SSSS SSSSSSSSS"

-- 1ns → "000000001"
/--
info: "0 00 000 0000 000000001"
-/
#guard_msgs in
#eval tdOneNs.format "S SS SSS SSSS SSSSSSSSS"

-- zero nanoseconds → "000000000"
/--
info: "0 00 000 0000 000000000"
-/
#guard_msgs in
#eval tdNoon.format "S SS SSS SSSS SSSSSSSSS"

-- ─────────────────────────────────────────────────────────────────────────────
-- b  Day period: nanoseconds prevent noon/midnight classification
-- ─────────────────────────────────────────────────────────────────────────────

-- 12:00:00.000000001 → PM, not noon (non-zero nanosecond)
/--
info: "PM"
-/
#guard_msgs in
#eval tdNoonNano.format "b"

-- 00:00:00.000000001 → AM, not midnight
/--
info: "AM"
-/
#guard_msgs in
#eval tdMidnightNano.format "b"

-- exact noon and midnight still work
/--
info: "noon midnight"
-/
#guard_msgs in
#eval s!"{tdNoon.format "b"} {tdMidnight.format "b"}"

-- ─────────────────────────────────────────────────────────────────────────────
-- b  Day period on PlainTime
-- ─────────────────────────────────────────────────────────────────────────────

/--
info: "noon"
-/
#guard_msgs in
#eval ptNoon.format "b"

/--
info: "midnight"
-/
#guard_msgs in
#eval ptMidnight.format "b"

/--
info: "AM"
-/
#guard_msgs in
#eval ptAM.format "b"

/--
info: "PM"
-/
#guard_msgs in
#eval ptPM.format "b"

-- non-zero nano at noon/midnight → falls back to AM/PM
/--
info: "PM"
-/
#guard_msgs in
#eval ptNoonNano.format "b"

/--
info: "AM"
-/
#guard_msgs in
#eval ptMidnightNano.format "b"
