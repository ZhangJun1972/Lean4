import Std.Time
open Std.Time

-- Shared fixtures (same as in timeFormats.lean)
def fmtDT (y : Int) (mo : Month.Ordinal) (d : Day.Ordinal)
    (h : Hour.Ordinal) (mi : Minute.Ordinal) (se : Second.Ordinal true)
    (ns : Nanosecond.Ordinal := 0) : PlainDateTime :=
  PlainDateTime.mk (PlainDate.ofYearMonthDayClip y mo d) (PlainTime.mk h mi se ns)

def fmtPD (y : Int) (mo : Month.Ordinal) (d : Day.Ordinal) : PlainDate :=
  PlainDate.ofYearMonthDayClip y mo d

def fmtPT (h : Hour.Ordinal) (mi : Minute.Ordinal) (se : Second.Ordinal true)
    (ns : Nanosecond.Ordinal := 0) : PlainTime := PlainTime.mk h mi se ns

/-
===========================
Bug-fix regression tests
===========================

These tests confirm bugs that have been fixed. They all pass.
-/

-- Bug 1 & 2: y/Y single-letter must apply era mapping (proleptic year → era year)
-- Year -100 = 101 BC → single y gives "101", not "-100"

/--
info: "101"
-/
#guard_msgs in
#eval (fmtDT (-100) 6 15 0 0 0).format "y"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 0 1 1 0 0 0).format "y"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT (-1) 1 1 0 0 0).format "y"

-- wider widths were already correct; confirm they still agree
/--
info: "101 01 0101"
-/
#guard_msgs in
#eval (fmtDT (-100) 6 15 0 0 0).format "y yy yyyy"

/--
info: "101"
-/
#guard_msgs in
#eval (fmtDT (-100) 6 15 0 0 0).format "yyy"

-- Y single-letter: week-based year 2019 for Dec 31 2018 (ISO week 1 of 2019)

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2018 12 31 12 0 0).format "Y"

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2019 1 1 0 0 0).format "Y"

-- Bug 3: ZonedDateTime `w` now uses ISO Monday-first (was Sunday-first)
-- Jan 6 2019 is Sunday: ISO week 1 (Mon Dec 31–Sun Jan 6), was US week 2
-- ZonedDateTime and PlainDateTime must now agree

/--
info: "1"
-/
#guard_msgs in
#eval zoned("2019-01-06T12:00:00+00:00").format "w"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2019 1 6 12 0 0).format "w"

-- Dec 31 2020 (Thu) = ISO week 53 of 2020; both must agree

/--
info: "53"
-/
#guard_msgs in
#eval zoned("2020-12-31T12:00:00+00:00").format "w"

/--
info: "53"
-/
#guard_msgs in
#eval (fmtDT 2020 12 31 12 0 0).format "w"

-- Dec 31 2018 (Mon) = ISO week 1 of 2019; both must agree

/--
info: "1"
-/
#guard_msgs in
#eval zoned("2018-12-31T12:00:00+00:00").format "w"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2018 12 31 12 0 0).format "w"

-- Bug 4: ZonedDateTime `Y` now uses ISO Monday-first (was Sunday-first)
-- Dec 31 2009 (Thu): ISO Y=2009 (the week's Thu is still in 2009),
-- was US Y=2010 (US week extends to Sat Jan 2 2010)

/--
info: "2009"
-/
#guard_msgs in
#eval zoned("2009-12-31T12:00:00+00:00").format "YYYY"

/--
info: "2009"
-/
#guard_msgs in
#eval (fmtDT 2009 12 31 12 0 0).format "YYYY"

-- Dec 31 2018 (Mon): both give 2019

/--
info: "2019"
-/
#guard_msgs in
#eval zoned("2018-12-31T12:00:00+00:00").format "YYYY"

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2018 12 31 12 0 0).format "YYYY"

-- Jan 6 2019 (Sun): ISO Y=2019; ZonedDateTime must agree with PlainDateTime

/--
info: "2019"
-/
#guard_msgs in
#eval zoned("2019-01-06T12:00:00+00:00").format "YYYY"

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2019 1 6 12 0 0).format "YYYY"

-- Bug 5: B (extended day period) was missing from PlainTime — now implemented

/--
info: "midnight"
-/
#guard_msgs in
#eval (fmtPT 0 0 0).format "B"

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtPT 3 0 0).format "B"

/--
info: "in the morning"
-/
#guard_msgs in
#eval (fmtPT 9 0 0).format "B"

/--
info: "noon"
-/
#guard_msgs in
#eval (fmtPT 12 0 0).format "B"

/--
info: "in the afternoon"
-/
#guard_msgs in
#eval (fmtPT 15 0 0).format "B"

/--
info: "in the evening"
-/
#guard_msgs in
#eval (fmtPT 19 0 0).format "B"

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtPT 22 0 0).format "B"

-- boundary: 1 second past midnight = night (not midnight)

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtPT 0 0 1).format "B"

-- boundary: 1 second past noon = afternoon (not noon)

/--
info: "in the afternoon"
-/
#guard_msgs in
#eval (fmtPT 12 0 1).format "B"

-- boundary: 05:59:59 = night (h=5 < 6); 20:59:59 = evening (18 ≤ h < 21)

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtPT 5 59 59).format "B"

/--
info: "in the evening"
-/
#guard_msgs in
#eval (fmtPT 20 59 59).format "B"

/-
===========================
Parsing bug-fix regression tests
===========================
-/

-- Bug fix: month defaulted to 0 (which wrapped to December via ofNatWrapping).
-- Parsing a format without a month field should default to January (1), not December (12).
def fmtParseYearDay : Format Awareness.any := datespec("uuuu-dd")

/--
info: Except.ok (zoned("2024-01-15T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtParseYearDay.parse "2024-15"

-- Bug fix: day defaulted to 0 (which wrapped to 31 via ofNatWrapping).
-- Parsing a format without a day field should default to day 1, not day 31.
-- Previously, parsing "2024-06" with "uuuu-MM" would error because June has only 30 days.
def fmtParseYearMonth : Format Awareness.any := datespec("uuuu-MM")

/--
info: Except.ok (zoned("2024-06-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtParseYearMonth.parse "2024-06"

-- Bug fix: parseMonthNarrow had duplicate alternatives for J (Jan/Jun/Jul), M (Mar/May),§
-- A (Apr/Aug), making the later alternatives unreachable dead code.
-- Narrow parsing now consistently takes the first (earliest) match per letter.
def fmtParseNarrowMonth : Format Awareness.any := datespec("MMMMM")

/-- info: Except.ok (zoned("0000-02-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "F"  -- Feb (unique)

/-- info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "J"  -- Jan (first of Jan/Jun/Jul)

/-- info: Except.ok (zoned("0000-03-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "M"  -- Mar (first of Mar/May)

/-- info: Except.ok (zoned("0000-04-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "A"  -- Apr (first of Apr/Aug)

/-- info: Except.ok (zoned("0000-09-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "S"  -- Sep (unique)

/-- info: Except.ok (zoned("0000-10-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "O"  -- Oct (unique)

/-- info: Except.ok (zoned("0000-11-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "N"  -- Nov (unique)

/-- info: Except.ok (zoned("0000-12-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowMonth.parse "D"  -- Dec (unique)

-- Bug fix: parseWeekdayNarrow had duplicate alternatives for S (Sun/Sat) and T (Tue/Thu),
-- making Saturday and Thursday unreachable.
def fmtParseNarrowWeekday : Format Awareness.any := datespec("EEEEE")

/-- info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowWeekday.parse "S"  -- Sunday (first of Sun/Sat)

/-- info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowWeekday.parse "T"  -- Tuesday (first of Tue/Thu)

/-- info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z")) -/
#guard_msgs in
#eval fmtParseNarrowWeekday.parse "F"  -- Friday (unique)

/-
===========================
Known bugs — tests encode correct expected behavior but FAIL.
When a bug is fixed, update the expected value here (tests become passing).
===========================
-/

-- ===========================
-- BUG: D (day-of-year) parsed but ignored in DateBuilder.build
--
-- `builder.D` is stored after parsing but never referenced in `build`.
-- Year, month, and day default to 0/1/1 regardless of the D value.
-- ISO 8601 ordinal date formats (e.g. "2024-366") are silently misparsed.
-- ===========================

def fmtOrdinal : Format Awareness.any := datespec("uuuu-DDD")

-- "2024-366" is December 31, 2024 (2024 is a leap year).
-- Currently returns January 1 because D is ignored.
/--
info: Except.ok (zoned("2024-12-31T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtOrdinal.parse "2024-366"

-- "2024-060" is February 29, 2024 (2024 is leap). Currently returns January 1.
/--
info: Except.ok (zoned("2024-02-29T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtOrdinal.parse "2024-060"

-- "2023-060" is March 1, 2023 (2023 is not leap, Feb has 28 days). Currently returns January 1.
/--
info: Except.ok (zoned("2023-03-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtOrdinal.parse "2023-060"

-- "2023-365" is December 31, 2023 (non-leap year). Currently returns January 1.
/--
info: Except.ok (zoned("2023-12-31T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtOrdinal.parse "2023-365"

-- ===========================
-- BUG: D parser hardcodes leap=true (Sigma.mk true), so day 366 is accepted
-- even for non-leap years. "2023-366" should fail (2023 has only 365 days).
-- Currently succeeds, returning January 1, 2023 (wrong).
-- ===========================

/--
info: Except.error "offset 8: day 366 does not exist in year 2023"
-/
#guard_msgs in
#eval fmtOrdinal.parse "2023-366"

-- ===========================
-- BUG: convertYearAndEra uses -(year+1) instead of -(year-1)
--
-- When parsing a year-of-era (y) together with a BC era (G), the build function
-- calls `convertYearAndEra era_year .bce = -(era_year + 1)`.
-- The correct inverse of the formatting formula `era_year = -proleptic + 1`
-- is `proleptic = 1 - era_year = -(era_year - 1)`.
-- The bug shifts all BC proleptic years off by 2.
-- ===========================

def fmtYearEra : Format Awareness.any := datespec("yyyy-MM-dd G")

-- 1 BC = proleptic year 0 (era_year=1, BC).
-- Currently: convertYearAndEra 1 .bce = -(1+1) = -2 → year -2 (wrong, 3 BC).
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtYearEra.parse "0001-01-01 BC"

-- 101 BC = proleptic year -100 (era_year=101, BC).
-- Currently: convertYearAndEra 101 .bce = -(101+1) = -102 → year -102 (wrong, 103 BC).
/--
info: Except.ok (zoned("-0100-06-15T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtYearEra.parse "0101-06-15 BC"

-- 2001 BC = proleptic year -2000 (era_year=2001, BC).
-- Currently: convertYearAndEra 2001 .bce = -(2001+1) = -2002 → year -2002 (wrong, 2003 BC).
/--
info: Except.ok (zoned("-2000-03-04T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtYearEra.parse "2001-03-04 BC"

-- ===========================
-- BUG: k (clock-hour-of-day, 1-24) parsing is off by one
--
-- DateBuilder.build computes hour from k as `(Bounded.LE.sub k 1)`, giving hour = k - 1.
-- But `shiftTo1BasedHour` maps hour=0 → k=24, hour=1..23 → k=1..23.
-- The correct inverse is: k=24 → hour=0, k=1..23 → hour=k.
-- The current formula shifts every parsed hour down by 1.
-- ===========================

def fmtClockHour : Format Awareness.any := datespec("kk:mm:ss")

-- k=24 represents midnight (00:00:00). Currently parses as 23:00:00.
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtClockHour.parse "24:00:00"

-- k=01 represents 01:00:00. Currently parses as 00:00:00.
/--
info: Except.ok (zoned("0000-01-01T01:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtClockHour.parse "01:00:00"

-- k=12 represents noon (12:00:00). Currently parses as 11:00:00.
/--
info: Except.ok (zoned("0000-01-01T12:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtClockHour.parse "12:00:00"

-- k=23 represents 23:00:00 (11 PM). Currently parses as 22:00:00.
/--
info: Except.ok (zoned("0000-01-01T23:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtClockHour.parse "23:00:00"

-- ===========================
-- BUG: convertYearAndEra is off by 2 for BCE dates.
--
-- The `y` formatter converts a proleptic year p ≤ 0 to the displayed era year
-- using:  display = -p + 1
-- so:  p = 0  → display 1 (1 BCE)
--      p = -1 → display 2 (2 BCE)
--      p = -99 → display 100 (100 BCE)
--
-- The inverse (used in build when parsing "y G") must be:
--   proleptic = 1 - display
--
-- But the implementation says:
--   | .bce => -(year + 1)     -- wrong: gives -year - 1, off by 2
-- It should be:
--   | .bce => 1 - year        -- correct: gives 1 - year
--
-- Effect: parsing any BCE date via "y G" (or "yyy GG" etc.) produces a
-- proleptic year that is 2 years too early.
-- ===========================

def fmtEraYear : Format Awareness.any := datespec("y GG")

-- "1 BC" = proleptic year 0 (1 BCE = astronomical year 0).
-- Currently produces year -2 (3 BCE) instead of year 0 (1 BCE).
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtEraYear.parse "1 BC"

-- "2 BC" = proleptic year -1. Currently produces year -3.
/--
info: Except.ok (zoned("-0001-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtEraYear.parse "2 BC"

-- "100 BC" = proleptic year -99. Currently produces year -101.
/--
info: Except.ok (zoned("-0099-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtEraYear.parse "100 BC"

-- Round-trip: format a BCE date then parse it back.
-- (fmtDT (-99) 6 15 0 0 0).format "y GG" = "100 BC"
-- Parsing "100 BC" should reconstruct proleptic year -99.
/--
info: Except.ok (zoned("-0099-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtEraYear.parse ((fmtDT (-99) 6 15 0 0 0).format "y GG")

-- ===========================
-- BUG: k (1-based 24-hour clock) is parsed as k-1 instead of the correct inverse.
--
-- The `k` formatter maps hour → 1-based-24h using:
--   hour = 0 (midnight) → k = 24
--   hour = 1            → k = 1
--   ...
--   hour = 23           → k = 23
--
-- The correct inverse is: hour = if k = 24 then 0 else k
--
-- But the `build` function uses:  hour = k - 1
-- so:  k = 24 → hour = 23 (wrong, should be 0)
--      k = 1  → hour = 0  (wrong, should be 1)
--      k = 12 → hour = 11 (wrong, should be 12)
-- ===========================

def fmtKLower : Format Awareness.any := datespec("kk")

-- Midnight (hour 0) is formatted as k=24; parsing "24" should give hour 0.
-- Currently gives hour 23 (11 PM) via k-1=23.
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKLower.parse "24"

-- 1 AM (hour 1) is formatted as k=01; parsing "01" should give hour 1.
-- Currently gives hour 0 (midnight) via k-1=0.
/--
info: Except.ok (zoned("0000-01-01T01:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKLower.parse "01"

-- Noon (hour 12) is formatted as k=12; parsing "12" should give hour 12.
-- Currently gives hour 11 (11 AM) via k-1=11.
/--
info: Except.ok (zoned("0000-01-01T12:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKLower.parse "12"

-- 11 PM (hour 23) is formatted as k=23; parsing "23" should give hour 23.
-- Currently gives hour 22 (10 PM) via k-1=22.
/--
info: Except.ok (zoned("0000-01-01T23:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKLower.parse "23"

-- ===========================
-- BUG: K (0-11 AM/PM clock hour) is parsed via K+1→toAbsolute, which is wrong.
--
-- The `K` formatter maps hour → 0-11 via hour % 12:
--   hour = 0  (midnight) → K = 0 AM
--   hour = 11 (11 AM)    → K = 11 AM
--   hour = 12 (noon)     → K = 0 PM
--   hour = 23 (11 PM)    → K = 11 PM
--
-- The correct inverse is: hour = K (AM) or K+12 (PM)
--
-- But the `build` function uses: K+1 → toAbsolute marker, which gives:
--   K=0  AM → toAbsolute .am  1 = 1   (wrong, should be 0)
--   K=11 AM → toAbsolute .am 12 = 0   (wrong, should be 11)
--   K=0  PM → toAbsolute .pm  1 = 13  (wrong, should be 12)
--   K=11 PM → toAbsolute .pm 12 = 12  (wrong, should be 23)
-- ===========================

def fmtKUpper : Format Awareness.any := datespec("KK a")

-- K=00 AM = midnight (hour 0). Currently gives 1 AM (hour 1) via K+1=1, toAbsolute .am 1=1.
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse "00 AM"

-- K=11 AM = 11 AM (hour 11). Currently gives midnight (hour 0) via K+1=12, toAbsolute .am 12=0.
/--
info: Except.ok (zoned("0000-01-01T11:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse "11 AM"

-- K=00 PM = noon (hour 12). Currently gives 1 PM (hour 13) via K+1=1, toAbsolute .pm 1=13.
/--
info: Except.ok (zoned("0000-01-01T12:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse "00 PM"

-- K=11 PM = 11 PM (hour 23). Currently gives noon (hour 12) via K+1=12, toAbsolute .pm 12=12.
/--
info: Except.ok (zoned("0000-01-01T23:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse "11 PM"

-- Round-trip: format midnight then parse it back.
-- (fmtPT 0 0 0).format "KK a" = "00 AM"; parsing "00 AM" should give hour 0.
/--
info: Except.ok (zoned("0000-01-01T00:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse ((fmtPT 0 0 0).format "KK a")

-- Round-trip: format 11 AM then parse it back.
-- (fmtPT 11 0 0).format "KK a" = "11 AM"; parsing "11 AM" should give hour 11.
/--
info: Except.ok (zoned("0000-01-01T11:00:00.000000000Z"))
-/
#guard_msgs in
#eval fmtKUpper.parse ((fmtPT 11 0 0).format "KK a")

-- ===========================
-- BUG: Month.Ordinal.toSeconds/toDays/toMinutes/toHours use the wrong array index.
-- The daysAcc array is 0-indexed with 12 elements (indices 0–11), where
-- index i gives the cumulative days before month (i+1). But the code uses
-- month.toNat (which is 1–12) as the array index directly, so it is always
-- off by one. For months 1–11 the result is shifted one month forward.
-- For December (toNat=12) the index is out of bounds → runtime panic.
-- ===========================

-- January (month.toNat=1 → reads daysAcc[1]=31 instead of daysAcc[0]=0).
-- Correct: 0 days before January. Current result: 31 days.
/-- info: 0 -/
#guard_msgs in
#eval (Month.Ordinal.toDays false 1).val

-- February (month.toNat=2 → reads daysAcc[2]=59 instead of daysAcc[1]=31).
-- Correct: 31 days before February. Current result: 59 days.
/-- info: 31 -/
#guard_msgs in
#eval (Month.Ordinal.toDays false 2).val

-- November (month.toNat=11 → reads daysAcc[11]=334 instead of daysAcc[10]=304).
-- Correct: 304 days before November. Current result: 334 days.
/-- info: 304 -/
#guard_msgs in
#eval (Month.Ordinal.toDays false 11).val

-- December crashes at runtime with "index out of bounds" (daysAcc has only 12
-- elements at indices 0–11, but the code reads index 12).
-- Correct: 334 days. Current result: panic.
