import Std.Time
open Std.Time

def RFC1123 : Format Awareness.any := datespec("eee, dd MMM uuuu HH:mm:ss ZZZ")
def ShortDate : Format Awareness.any := datespec("MM/dd/uuuu")
def LongDate : Format Awareness.any := datespec("MMMM D, uuuu")
def ShortDateTime : Format Awareness.any := datespec("MM/dd/uuuu HH:mm:ss")
def LongDateTime : Format Awareness.any := datespec("MMMM D, uuuu h:mm a")
def Time24Hour : Format Awareness.any := datespec("HH:mm:ss")
def Time12Hour : Format Awareness.any := datespec("hh:mm:ss a")
def FullDayTimeZone : Format Awareness.any := datespec("EEEE, MMMM dd, uuuu HH:mm:ss ZZZ")
def CustomDayTime : Format Awareness.any := datespec("EEE dd MMM uuuu HH:mm")
def EraDate : Format Awareness.any := datespec("MM D, uuuu G")
def DateSmall : Format Awareness.any := datespec("uu-MM-dd")

-- Dates

def brTZ : TimeZone := timezone("America/Sao_Paulo -03:00")
def jpTZ : TimeZone := timezone("Asia/Tokyo +09:00")

def date₁ := zoned("2014-06-16T03:03:03-03:00")

def time₁ := time("14:11:01")
def time₂ := time("03:11:01")

/--
info: "Monday, June 16, 2014 03:03:03 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format date₁

def tm := date₁.toTimestamp
def date₂ := DateTime.ofTimestamp tm brTZ

/--
info: "Monday, June 16, 2014 03:03:03 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format date₂

def tm₃ := date₁.toTimestamp
def date₃ := DateTime.ofTimestamp tm₃ brTZ

/--
info: "Monday, June 16, 2014 03:03:03 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format date₃

-- Section for testing timezone conversion.

-- the timestamp is always related to UTC.

/--
Timestamp: 1723739292
GMT: Thursday, 15 August 2024 16:28:12
BR: 15 August 2024 13:28:12 GMT-03:00
-/
def tm₄ : Second.Offset := 1723739292

def dateBR := DateTime.ofTimestamp (Timestamp.ofSecondsSinceUnixEpoch tm₄) brTZ
def dateJP := DateTime.ofTimestamp (Timestamp.ofSecondsSinceUnixEpoch tm₄) jpTZ
def dateUTC := DateTime.ofTimestamp (Timestamp.ofSecondsSinceUnixEpoch tm₄) .UTC

/--
info: "Thursday, August 15, 2024 13:28:12 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateBR

/--
info: "Friday, August 16, 2024 01:28:12 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateJP

/--
info: "Thursday, August 15, 2024 13:28:12 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateUTC.convertTimeZone brTZ)

/--
info: "Thursday, August 15, 2024 13:28:12 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateJP.convertTimeZone brTZ)

/--
info: "Thursday, August 15, 2024 16:28:12 +0000"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateUTC

/--
info: "Thursday, August 15, 2024 16:28:12 +0000"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateBR.convertTimeZone .UTC)

/--
info: "Thursday, August 15, 2024 16:28:12 +0000"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateJP.convertTimeZone .UTC)

/--
info: "Friday, August 16, 2024 01:28:12 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateJP

/--
info: "Friday, August 16, 2024 01:28:12 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateBR.convertTimeZone jpTZ)

/--
info: "Friday, August 16, 2024 01:28:12 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateUTC.convertTimeZone jpTZ)

/--
TM: 1723730627
GMT: Thursday, 15 August 2024 14:03:47
Your time zone: 15 August 2024 11:03:47 GMT-03:00
-/
def localTm : Second.Offset := 1723730627

/--
This PlainDate is relative to the local time.
-/
def PlainDate : PlainDateTime := Timestamp.toPlainDateTimeAssumingUTC (Timestamp.ofSecondsSinceUnixEpoch localTm)

def dateBR₁ := DateTime.ofPlainDateTime PlainDate brTZ
def dateJP₁ := DateTime.ofPlainDateTime PlainDate jpTZ
def dateUTC₁ := DateTime.ofPlainDateTime PlainDate .UTC

/--
info: "Thursday, August 15, 2024 14:03:47 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateBR₁

/--
info: "Thursday, August 15, 2024 14:03:47 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format dateJP₁

/--
info: "Thursday, August 15, 2024 23:03:47 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateUTC₁.convertTimeZone jpTZ)

/--
info: "Friday, August 16, 2024 02:03:47 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateBR₁.convertTimeZone jpTZ)

/--
info: "Thursday, August 15, 2024 14:03:47 +0900"
-/
#guard_msgs in
#eval FullDayTimeZone.format (dateJP₁.convertTimeZone jpTZ)

/--
info: "Monday, June 16, 2014 03:03:03 -0300"
-/
#guard_msgs in
#eval FullDayTimeZone.format date₂

/--
info: "14:11:01"
-/
#guard_msgs in
#eval Time24Hour.formatBuilder time₁.hour time₁.minute time₁.second

def l := Time12Hour.formatBuilder time₁.hour.toRelative time₁.minute time₁.second (if time₁.hour.val > 12 then HourMarker.pm else HourMarker.am)

/--
info: "02:11:01 PM"
-/
#guard_msgs in
#eval l
/--
info: "03:11:01 AM"
-/
#guard_msgs in
#eval Time12Hour.formatBuilder time₂.hour.toRelative time₂.minute time₂.second (if time₂.hour.val > 12 then HourMarker.pm else HourMarker.am)

/--
info: "2024-08-15T14:03:47-03:00"
-/
#guard_msgs in
#eval Formats.iso8601.format dateBR₁

/--
info: "2024-08-15T14:03:47Z"
-/
#guard_msgs in
#eval Formats.iso8601.format dateUTC₁

/--
info: "06/16/2014"
-/
#guard_msgs in
#eval ShortDate.formatBuilder date₁.month date₁.day date₁.year

/--
info: "0053-06-19"
-/
#guard_msgs in
#eval Formats.sqlDate.format (DateTime.ofPlainDate (PlainDate.ofDaysSinceUNIXEpoch ⟨-700000⟩) .UTC)

/--
info: "-0002-09-16"
-/
#guard_msgs in
#eval Formats.sqlDate.format (DateTime.ofPlainDate (PlainDate.ofDaysSinceUNIXEpoch ⟨-720000⟩) .UTC)

/--
info: "-0084-07-28"
-/
#guard_msgs in
#eval Formats.sqlDate.format (DateTime.ofPlainDate (PlainDate.ofDaysSinceUNIXEpoch ⟨-750000⟩) .UTC)

/--
info: "-0221-09-04"
-/
#guard_msgs in
#eval Formats.sqlDate.format (DateTime.ofPlainDate (PlainDate.ofDaysSinceUNIXEpoch ⟨-800000⟩) .UTC)

/--
info: date("-0221-09-04")
-/
#guard_msgs in
#eval PlainDate.ofDaysSinceUNIXEpoch ⟨-800000⟩

/--
info: date("-0221-09-04")
-/
#guard_msgs in
#eval PlainDate.ofDaysSinceUNIXEpoch ⟨-800000⟩

/--
info: date("2002-07-14")
-/
#guard_msgs in
#eval date("2002-07-14")

/--
info: time("14:13:12.000000000")
-/
#guard_msgs in
#eval time("14:13:12")

/--
info: zoned("2002-07-14T14:13:12.000000000Z")
-/
#guard_msgs in
#eval zoned("2002-07-14T14:13:12Z")

/--
info: zoned("2002-07-14T14:13:12.000000000+09:00")
-/
#guard_msgs in
#eval zoned("2002-07-14T14:13:12+09:00")

/--
info: "2002-07-14"
-/
#guard_msgs in
#eval zoned("2002-07-14T14:13:12+09:00").format "uuuu-MM-dd"

/--
info: "14-13-12"
-/
#guard_msgs in
#eval zoned("2002-07-14T14:13:12+09:00").format "HH-mm-ss"

/-
Format
-/

def time₄ := time("23:13:12.324354679")
def date₄ := date("2002-07-14")
def datetime₅ := PlainDateTime.mk (PlainDate.ofYearMonthDayClip (-2000) 3 4) (PlainTime.mk 12 23 12 0)
def datetime₄ := datetime("2002-07-14T23:13:12.324354679")
def zoned₄ := zoned("2002-07-14T23:13:12.324354679+09:00")
def zoned₅ := zoned("2002-07-14T23:13:12.324354679+00:00")
def tz : TimeZone := { offset := { second := -3600 }, name := "America/Sao_Paulo", abbreviation := "BRT", isDST := false}
def zoned₆ := ZonedDateTime.ofPlainDateTime (zoned₄.toPlainDateTime) (TimeZone.ZoneRules.ofTimeZone tz)

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval zoned₄.format "G GG GGG GGGG GGGGG"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval zoned₄.format "yy yyyy yyyyyyyyy"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval zoned₄.format "uu uuuu uuuuuuuuu"

/--
info: "195 195 195"
-/
#guard_msgs in
#eval zoned₄.format "D DD DDD"

/--
info: "14 14"
-/
#guard_msgs in
#eval zoned₄.format "d dd"

/--
info: "7 07 Jul July J"
-/
#guard_msgs in
#eval zoned₄.format "M MM MMM MMMM MMMMM"

/--
info: "3 03 3rd quarter 3"
-/
#guard_msgs in
#eval zoned₄.format "Q QQ QQQQ QQQQQ"

/--
info: "28 28"
-/
#guard_msgs in
#eval zoned₄.format "w ww"

/--
info: "3"
-/
#guard_msgs in
#eval zoned₄.format "W"

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval zoned₄.format "E EE EEE EEEE EEEEE"

/--
info: "7 07 Sun Sunday S"
-/
#guard_msgs in
#eval zoned₄.format "e ee eee eeee eeeee"

/--
info: "2"
-/
#guard_msgs in
#eval zoned₄.format "F"

/--
info: "11 11"
-/
#guard_msgs in
#eval zoned₄.format "h hh"

/--
info: "11 11"
-/
#guard_msgs in
#eval zoned₄.format "K KK"

/--
info: "23 23"
-/
#guard_msgs in
#eval zoned₄.format "k kk"

/--
info: "23 23"
-/
#guard_msgs in
#eval zoned₄.format "H HH"

/--
info: "13 13"
-/
#guard_msgs in
#eval zoned₄.format "m mm"

/--
info: "12 12"
-/
#guard_msgs in
#eval zoned₄.format "s ss"


/--
info: "3 32 324 3243 32435"
-/#guard_msgs in
#eval zoned₄.format "S SS SSS SSSS SSSSS"

/--
info: "83592324 83592324 83592324 83592324 083592324"
-/
#guard_msgs in
#eval zoned₄.format "A AA AAA AAAA AAAAAAAAA"

/--
info: "324354679 324354679 324354679 324354679 324354679"
-/
#guard_msgs in
#eval zoned₄.format "n nn nnn nnnn nnnnnnnnn"

/--
info: "83592324354679 83592324354679 83592324354679 83592324354679 83592324354679"
-/
#guard_msgs in
#eval zoned₄.format "N NN NNN NNNN NNNNNNNNN"

/--
info: "+09:00"
-/
#guard_msgs in
#eval zoned₄.format "VV"

/--
info: "+09:00 +09:00 +09:00 +09:00"
-/
#guard_msgs in
#eval zoned₄.format "z zz zzzz zzzz"

/--
info: "Z Z Z Z"
-/
#guard_msgs in
#eval zoned₅.format "z zz zzzz zzzz"

/--
info: "GMT+9 GMT+09:00"
-/
#guard_msgs in
#eval zoned₄.format "O OOOO"

/--
info: "+09 +0900 +09:00 +0900 +09:00"
-/
#guard_msgs in
#eval zoned₄.format "X XX XXX XXXX XXXXX"

/--
info: "+09 +0900 +09:00 +0900 +09:00"
-/
#guard_msgs in
#eval zoned₄.format "x xx xxx xxxx xxxxx"

/--
info: "Z Z Z Z Z"
-/
#guard_msgs in
#eval zoned₅.format "X XX XXX XXXX XXXXX"

/--
info: "+00 +0000 +00:00 +0000 +00:00"
-/
#guard_msgs in
#eval zoned₅.format "x xx xxx xxxx xxxxx"

/--
info: "+0900 +0900 +0900 GMT+09:00 +09:00"
-/
#guard_msgs in
#eval zoned₄.format "Z ZZ ZZZ ZZZZ ZZZZZ"

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval datetime₄.format "G GG GGG GGGG GGGGG"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval datetime₄.format "yy yyyy yyyyyyyyy"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval datetime₄.format "uu uuuu uuuuuuuuu"

/--
info: "195 195 195"
-/
#guard_msgs in
#eval datetime₄.format "D DD DDD"

/--
info: "7 07 Jul J"
-/
#guard_msgs in
#eval datetime₄.format "M MM MMM MMMMM"

/--
info: "14 14"
-/
#guard_msgs in
#eval datetime₄.format "d dd"

/--
info: "7 07 Jul July J"
-/
#guard_msgs in
#eval datetime₄.format "M MM MMM MMMM MMMMM"

/--
info: "14 14"
-/#guard_msgs in
#eval datetime₄.format "d dd"

/--
info: "3 03 3rd quarter 3"
-/
#guard_msgs in
#eval datetime₄.format "Q QQ QQQQ QQQQQ"

/--
info: "28 28"
-/
#guard_msgs in
#eval datetime₄.format "w ww"

/--
info: "3"
-/
#guard_msgs in
#eval datetime₄.format "W"

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval datetime₄.format "E EE EEE EEEE EEEEE"

/--
info: "7 07 Sun Sunday S"
-/
#guard_msgs in
#eval datetime₄.format "e ee eee eeee eeeee"

/--
info: "2"
-/
#guard_msgs in
#eval datetime₄.format "F"

/--
info: "11 11"
-/
#guard_msgs in
#eval datetime₄.format "h hh"

/--
info: "11 11"
-/
#guard_msgs in
#eval datetime₄.format "K KK"

/--
info: "23 23"
-/
#guard_msgs in
#eval datetime₄.format "k kk"

/--
info: "23 23"
-/
#guard_msgs in
#eval datetime₄.format "H HH"

/--
info: "13 13"
-/
#guard_msgs in
#eval datetime₄.format "m mm"

/--
info: "12 12"
-/
#guard_msgs in
#eval datetime₄.format "s ss"


/--
info: "3 32 324 3243 32435"
-/#guard_msgs in
#eval datetime₄.format "S SS SSS SSSS SSSSS"

/--
info: "3 32 324 3243 324354679"
-/
#guard_msgs in
#eval datetime₄.format "S SS SSS SSSS SSSSSSSSS"

/--
info: "83592324 83592324 83592324 83592324 083592324"
-/
#guard_msgs in
#eval datetime₄.format "A AA AAA AAAA AAAAAAAAA"

/--
info: "324354679 324354679 324354679 324354679 324354679"
-/
#guard_msgs in
#eval datetime₄.format "n nn nnn nnnn nnnnnnnnn"

/--
info: "83592324354679 83592324354679 83592324354679 83592324354679 83592324354679"
-/
#guard_msgs in
#eval datetime₄.format "N NN NNN NNNN NNNNNNNNN"

/--
info: "11 11"
-/
#guard_msgs in
#eval time₄.format "h hh"

/--
info: "11 11"
-/
#guard_msgs in
#eval time₄.format "K KK"

/--
info: "23 23"
-/
#guard_msgs in
#eval time₄.format "k kk"

/--
info: "23 23"
-/
#guard_msgs in
#eval time₄.format "H HH"

/--
info: "13 13"
-/
#guard_msgs in
#eval time₄.format "m mm"

/--
info: "12 12"
-/
#guard_msgs in
#eval time₄.format "s ss"


/--
info: "3 32 324 3243 32435"
-/#guard_msgs in
#eval time₄.format "S SS SSS SSSS SSSSS"

/--
info: "3 32 324 3243 324354679"
-/
#guard_msgs in
#eval time₄.format "S SS SSS SSSS SSSSSSSSS"

/--
info: "83592324 83592324 83592324 83592324 083592324"
-/
#guard_msgs in
#eval time₄.format "A AA AAA AAAA AAAAAAAAA"

/--
info: "324354679 324354679 324354679 324354679 324354679"
-/
#guard_msgs in
#eval time₄.format "n nn nnn nnnn nnnnnnnnn"

/--
info: "83592324354679 83592324354679 83592324354679 83592324354679 83592324354679"
-/
#guard_msgs in
#eval time₄.format "N NN NNN NNNN NNNNNNNNN"

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval date₄.format "G GG GGG GGGG GGGGG"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval date₄.format "yy yyyy yyyyyyyyy"

/--
info: "02 2002 000002002"
-/
#guard_msgs in
#eval date₄.format "uu uuuu uuuuuuuuu"

/--
info: "195 195 195"
-/
#guard_msgs in
#eval date₄.format "D DD DDD"

/--
info: "7 07 Jul J"
-/
#guard_msgs in
#eval date₄.format "M MM MMM MMMMM"

/--
info: "14 14"
-/
#guard_msgs in
#eval date₄.format "d dd"

/--
info: "7 07 Jul July J"
-/
#guard_msgs in
#eval date₄.format "M MM MMM MMMM MMMMM"

/--
info: "14 14"
-/#guard_msgs in
#eval date₄.format "d dd"

/--
info: "3 03 3rd quarter 3"
-/
#guard_msgs in
#eval date₄.format "Q QQ QQQQ QQQQQ"

/--
info: "28 28"
-/
#guard_msgs in
#eval date₄.format "w ww"

/--
info: "3"
-/
#guard_msgs in
#eval date₄.format "W"

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval date₄.format "E EE EEE EEEE EEEEE"

/--
info: "7 07 Sun Sunday S"
-/
#guard_msgs in
#eval date₄.format "e ee eee eeee eeeee"

/--
info: "2"
-/
#guard_msgs in
#eval date₄.format "F"

/--
info: "-2000 2001 BC"
-/
#guard_msgs in
#eval datetime₅.format "uuuu yyyy G"

/--
info: "2002 2002 AD"
-/
#guard_msgs in
#eval datetime₄.format "uuuu yyyy G"

/--
info: "BRT BRT BRT America/Sao_Paulo America/Sao_Paulo"
-/
#guard_msgs in
#eval zoned₆.format "z zz zzz zzzz zzzz"

/--
info: 1
-/
#guard_msgs in
#eval
  let t : ZonedDateTime := .ofPlainDateTime datetime("2018-12-31T12:00:00") (TimeZone.ZoneRules.ofTimeZone TimeZone.UTC)
  IO.println s!"{t.format "w"}"

/--
info: Except.error "offset 0: condition not satisfied"
-/
#guard_msgs in
#eval DateSmall.parse "-23-12-12"

/-
Truncation Test
-/

/--
info: ("19343232432-01-04T01:04:03.000000000",
 Except.error "offset 4: expected: -",
 datetime("1932-01-02T05:04:03.000000000"))
-/
#guard_msgs in
#eval
  let r := PlainDateTime.mk (PlainDate.ofYearMonthDayClip 19343232432 1 4) (PlainTime.mk 25 64 3 0)
  let s := r.format "uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSS"
  let r := PlainDateTime.parse s
  (s, r, datetime("1932-01-02T05:04:03.000000000"))

def tuple2Mk (a : f) (b : g) := some (a, b)
def tuple3Mk (a : f) (b : g) (c : h) := some (a, b, c)
def tuple4Mk (a : f) (b : g) (c : h) (d : i) := some (a, b, c, d)
def tuple5Mk (a : f) (b : g) (c : h) (d : i) (e : j) := some (a, b, c, d, e)
def tuple6Mk (a : f) (b : g) (c : h) (d : i) (e : j) (k : z) := some (a, b, c, d, e, k)


/-
Parsing Length Tests
-/

def uFormat : Format Awareness.any := datespec("u uu uuuu uuuuu")

#eval do assert! (uFormat.parseBuilder tuple4Mk "1 11 1211 12311" |>.isOk)
#eval do assert! (uFormat.parseBuilder tuple4Mk "12 11 1211 12311" |>.isOk)
#eval do assert! (uFormat.parseBuilder tuple4Mk "123443 11 1211 12311" |>.isOk)
#eval do assert! (uFormat.parseBuilder tuple4Mk "-1 11 1211 12311" |>.isOk)
#eval do assert! (uFormat.parseBuilder tuple4Mk "1 11 -1211 12311" |>.isOk)
#eval do assert! (uFormat.parseBuilder tuple4Mk "1 11 1211 -12311" |>.isOk)

#eval do assert! (not <| uFormat.parseBuilder tuple4Mk "1 -11 1211 12311" |>.isOk)
#eval do assert! (not <| uFormat.parseBuilder tuple4Mk "11 1211 12134" |>.isOk)
#eval do assert! (not <| uFormat.parseBuilder tuple4Mk "1 1 12 1234" |>.isOk)
#eval do assert! (not <| uFormat.parseBuilder tuple4Mk "1 11 1213 111123" |>.isOk)
#eval do assert! (not <| uFormat.parseBuilder tuple4Mk "1 367 1211 12311" |>.isOk)

def yFormat : Format Awareness.any := datespec("y yy yyyy yyyyy")

#eval do assert! (yFormat.parseBuilder tuple4Mk "1 11 1211 12311" |>.isOk)
#eval do assert! (yFormat.parseBuilder tuple4Mk "12 11 1211 12311" |>.isOk)
#eval do assert! (yFormat.parseBuilder tuple4Mk "123443 11 1211 12311" |>.isOk)

#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "-1 11 1211 12311" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 -11 1211 12311" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 11 -1211 12311" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 11 1211 -12311" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "11 1211 12134" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 1 12 1234" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 11 1213 111123" |>.isOk)
#eval do assert! (not <| yFormat.parseBuilder tuple4Mk "1 367 1211 12311" |>.isOk)

def dFormat : Format Awareness.any := datespec("D DD DDD")

#eval do assert! (dFormat.parseBuilder tuple3Mk "1 12 123" |>.isOk)
#eval do assert! (dFormat.parseBuilder tuple3Mk "323 12 123" |>.isOk)

#eval do assert! (not <| dFormat.parseBuilder tuple3Mk "1 12 1234" |>.isOk)
#eval do assert! (not <| dFormat.parseBuilder tuple3Mk "1 123 123" |>.isOk)
#eval do assert! (not <| dFormat.parseBuilder tuple3Mk "367 12 123" |>.isOk)

def dayOfMonthFormat : Format Awareness.any := datespec("d dd")

#eval do assert! (dayOfMonthFormat.parseBuilder tuple2Mk "1 12" |>.isOk)
#eval do assert! (dayOfMonthFormat.parseBuilder tuple2Mk "31 31" |>.isOk)

#eval do assert! (not <| dayOfMonthFormat.parseBuilder tuple2Mk "1 123" |>.isOk)
#eval do assert! (not <| dayOfMonthFormat.parseBuilder tuple2Mk "32 31" |>.isOk)

def wFormat : Format Awareness.any := datespec("w ww")

#eval do assert! (wFormat.parseBuilder tuple2Mk "1 01" |>.isOk)
#eval do assert! (wFormat.parseBuilder tuple2Mk "2 01" |>.isOk)

#eval do assert! (not <| wFormat.parseBuilder tuple2Mk "2 031" |>.isOk)
#eval do assert! (not <| wFormat.parseBuilder tuple2Mk "54 01" |>.isOk)

def qFormat : Format Awareness.any := datespec("q qq")

#eval do assert! (qFormat.parseBuilder tuple2Mk "1 02" |>.isOk)
#eval do assert! (qFormat.parseBuilder tuple2Mk "3 03" |>.isOk)

#eval do assert! (not <| qFormat.parseBuilder tuple2Mk "12 32" |>.isOk)
#eval do assert! (not <| qFormat.parseBuilder tuple2Mk "000001 003" |>.isOk)

def WFormat : Format Awareness.any := datespec("W")

#eval do assert! (WFormat.parseBuilder some "1" |>.isOk)
#eval do assert! (WFormat.parseBuilder some "3" |>.isOk)

#eval do assert! (not <| WFormat.parseBuilder some "12" |>.isOk)

def eFormat : Format Awareness.any := datespec("e ee")

#eval do assert! (eFormat.parseBuilder tuple2Mk "1 07" |>.isOk)
#eval do assert! (eFormat.parseBuilder tuple2Mk "3 03" |>.isOk)

#eval do assert! (not <| eFormat.parseBuilder tuple2Mk "12 32" |>.isOk)
#eval do assert! (not <| eFormat.parseBuilder tuple2Mk "000001 003" |>.isOk)

def FFormat : Format Awareness.any := datespec("F")

#eval do assert! (FFormat.parseBuilder some "1" |>.isOk)
#eval do assert! (FFormat.parseBuilder some "3" |>.isOk)

#eval do assert! (not <| FFormat.parseBuilder some "12" |>.isOk)
#eval do assert! (not <| FFormat.parseBuilder some "6" |>.isOk)

def hFormat : Format Awareness.any := datespec("h hh")

#eval do assert! (hFormat.parseBuilder tuple2Mk "1 09" |>.isOk)
#eval do assert! (hFormat.parseBuilder tuple2Mk "12 12" |>.isOk)

#eval do assert! (not <| hFormat.parseBuilder tuple2Mk "12 32" |>.isOk)
#eval do assert! (not <| hFormat.parseBuilder tuple2Mk "000001 003" |>.isOk)

/-
Error tests with some formats.
-/

/--
info: zoned("2002-07-14T14:13:12.000000000+23:59")
-/
#guard_msgs in
#eval zoned("2002-07-14T14:13:12+23:59")

/--
info: Except.error "offset 22: invalid hour offset: 24. Must be between 0 and 23."
-/
#guard_msgs in
#eval Formats.leanDateTimeWithZoneAlt.parse "2002-07-14T14:13:12+24:59"

/--
info: Except.error "offset 25: invalid minute offset: 60. Must be between 0 and 59."
-/
#guard_msgs in
#eval Formats.leanDateTimeWithZoneAlt.parse "2002-07-14T14:13:12+23:60"

/--
info: Except.ok (zoned("2002-07-14T14:13:12.000000000Z"))
-/
#guard_msgs in
#eval Formats.leanDateTimeWithZoneAlt.parse "2002-07-14T14:13:12+00:00"

/-
===========================
Additional format specifier tests – PlainDateTime, PlainDate, PlainTime
===========================
-/

-- Shared fixtures
def fmtDT (y : Int) (mo : Month.Ordinal) (d : Day.Ordinal)
    (h : Hour.Ordinal) (mi : Minute.Ordinal) (se : Second.Ordinal true)
    (ns : Nanosecond.Ordinal := 0) : PlainDateTime :=
  PlainDateTime.mk (PlainDate.ofYearMonthDayClip y mo d) (PlainTime.mk h mi se ns)

def fmtPD (y : Int) (mo : Month.Ordinal) (d : Day.Ordinal) : PlainDate :=
  PlainDate.ofYearMonthDayClip y mo d

def fmtPT (h : Hour.Ordinal) (mi : Minute.Ordinal) (se : Second.Ordinal true)
    (ns : Nanosecond.Ordinal := 0) : PlainTime :=
  PlainTime.mk h mi se ns

-- ===== G (ERA) =====

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval (fmtDT 2024 6 15 0 0 0).format "G GG GGG GGGG GGGGG"

/--
info: "BC BC BC Before Christ B"
-/
#guard_msgs in
#eval (fmtDT (-100) 6 15 0 0 0).format "G GG GGG GGGG GGGGG"

/--
info: "AD Anno Domini A"
-/
#guard_msgs in
#eval (fmtDT 1 1 1 0 0 0).format "G GGGG GGGGG"

/--
info: "BC Before Christ B"
-/
#guard_msgs in
#eval (fmtDT 0 1 1 0 0 0).format "G GGGG GGGGG"

/--
info: "BC Before Christ B"
-/
#guard_msgs in
#eval (fmtDT (-1) 1 1 0 0 0).format "G GGGG GGGGG"

-- ===== y (YEAR OF ERA) =====

/--
info: "2024 24 2024"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "y yy yyyy"

/--
info: "101 01 0101"
-/
#guard_msgs in
#eval (fmtDT (-100) 6 15 0 0 0).format "y yy yyyy"

/--
info: "1 01 0001"
-/
#guard_msgs in
#eval (fmtDT 1 1 1 0 0 0).format "y yy yyyy"

/--
info: "1 01"
-/
#guard_msgs in
#eval (fmtDT 0 6 1 0 0 0).format "y yy"

/--
info: "00"
-/
#guard_msgs in
#eval (fmtDT 2100 1 1 0 0 0).format "yy"

-- ===== Y (WEEK-BASED YEAR) =====
-- Dec 31 2018 is in ISO week 1 of 2019

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2018 12 31 12 0 0).format "YYYY"

/--
info: "2019"
-/
#guard_msgs in
#eval (fmtDT 2019 1 1 0 0 0).format "YYYY"

-- Dec 30 2019 is in ISO week 1 of 2020

/--
info: "2020"
-/
#guard_msgs in
#eval (fmtDT 2019 12 30 0 0 0).format "YYYY"

/--
info: "2020"
-/
#guard_msgs in
#eval (fmtDT 2020 12 31 0 0 0).format "YYYY"

-- Dec 31 2023 is in ISO week 52 of 2023

/--
info: "2023"
-/
#guard_msgs in
#eval (fmtDT 2023 12 31 23 59 59).format "YYYY"

-- ===== u (PROLEPTIC YEAR) =====

/--
info: "2024 2024"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "u uuuu"

/--
info: "-100 -0100"
-/
#guard_msgs in
#eval (fmtDT (-100) 1 1 0 0 0).format "u uuuu"

/--
info: "0000"
-/
#guard_msgs in
#eval (fmtDT 0 1 1 0 0 0).format "uuuu"

/--
info: "0001"
-/
#guard_msgs in
#eval (fmtDT 1 1 1 0 0 0).format "uuuu"

-- ===== D (DAY OF YEAR) =====

/--
info: "1 001"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "D DDD"

-- Feb 29 is day 60 in a leap year

/--
info: "60 060"
-/
#guard_msgs in
#eval (fmtDT 2024 2 29 0 0 0).format "D DDD"

-- Mar 1 is day 61 in a leap year, day 60 in a non-leap year

/--
info: "61 061"
-/
#guard_msgs in
#eval (fmtDT 2024 3 1 0 0 0).format "D DDD"

/--
info: "60 060"
-/
#guard_msgs in
#eval (fmtDT 2023 3 1 0 0 0).format "D DDD"

-- Dec 31: 366 in leap year, 365 in non-leap

/--
info: "366 366"
-/
#guard_msgs in
#eval (fmtDT 2024 12 31 0 0 0).format "D DDD"

/--
info: "365 365"
-/
#guard_msgs in
#eval (fmtDT 2023 12 31 0 0 0).format "D DDD"

/--
info: "59 059"
-/
#guard_msgs in
#eval (fmtDT 2023 2 28 0 0 0).format "D DDD"

-- July 4, 2024 = day 186

/--
info: "186"
-/
#guard_msgs in
#eval (fmtDT 2024 7 4 0 0 0).format "D"

-- ===== M / L (MONTH) =====

/--
info: "1 01 Jan January J"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "M MM MMM MMMM MMMMM"

/--
info: "6 06 Jun June J"
-/
#guard_msgs in
#eval (fmtDT 2024 6 1 0 0 0).format "M MM MMM MMMM MMMMM"

/--
info: "12 12 Dec December D"
-/
#guard_msgs in
#eval (fmtDT 2024 12 1 0 0 0).format "M MM MMM MMMM MMMMM"

/--
info: "February"
-/
#guard_msgs in
#eval (fmtDT 2024 2 1 0 0 0).format "MMMM"

/--
info: "1 01 Jan January J"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "L LL LLL LLLL LLLLL"

/--
info: "9 09 Sep September S"
-/
#guard_msgs in
#eval (fmtDT 2024 9 1 0 0 0).format "L LL LLL LLLL LLLLL"

-- ===== d (DAY OF MONTH) =====

/--
info: "1 01"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "d dd"

/--
info: "31 31"
-/
#guard_msgs in
#eval (fmtDT 2024 1 31 0 0 0).format "d dd"

/--
info: "29 29"
-/
#guard_msgs in
#eval (fmtDT 2024 2 29 0 0 0).format "d dd"

-- ===== Q / q (QUARTER) =====

/--
info: "1 01 Q1 1st quarter 1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "Q QQ QQQ QQQQ QQQQQ"

/--
info: "2 02 Q2 2nd quarter 2"
-/
#guard_msgs in
#eval (fmtDT 2024 4 1 0 0 0).format "Q QQ QQQ QQQQ QQQQQ"

/--
info: "3 03 Q3 3rd quarter 3"
-/
#guard_msgs in
#eval (fmtDT 2024 7 1 0 0 0).format "Q QQ QQQ QQQQ QQQQQ"

/--
info: "4 04 Q4 4th quarter 4"
-/
#guard_msgs in
#eval (fmtDT 2024 10 1 0 0 0).format "Q QQ QQQ QQQQ QQQQQ"

/--
info: "1 01 Q1 1st quarter 1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "q qq qqq qqqq qqqqq"

/--
info: "3 03 Q3 3rd quarter 3"
-/
#guard_msgs in
#eval (fmtDT 2024 7 1 0 0 0).format "q qq qqq qqqq qqqqq"

/--
info: "4 04 Q4 4th quarter 4"
-/
#guard_msgs in
#eval (fmtDT 2024 10 1 0 0 0).format "q qq qqq qqqq qqqqq"

-- ===== w (ISO WEEK OF YEAR) =====
-- Jan 1 2024 = week 1

/--
info: "1 01"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "w ww"

-- Jan 7 2024 = still week 1

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 7 0 0 0).format "w"

-- Dec 31 2024 = ISO week 1 of 2025

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 12 31 0 0 0).format "w"

-- Dec 31 2023 = ISO week 52 of 2023

/--
info: "52"
-/
#guard_msgs in
#eval (fmtDT 2023 12 31 23 59 59).format "w"

-- Dec 31 2020 = ISO week 53 of 2020

/--
info: "53"
-/
#guard_msgs in
#eval (fmtDT 2020 12 31 0 0 0).format "w"

-- ===== W (WEEK OF MONTH, Sunday-first) =====
-- April 2024 starts Monday; week boundaries: W1=Apr1-6, W2=Apr7-13, W3=Apr14-20, W4=Apr21-27, W5=Apr28-30

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 4 1 0 0 0).format "W"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 4 6 0 0 0).format "W"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT 2024 4 7 0 0 0).format "W"

/--
info: "3"
-/
#guard_msgs in
#eval (fmtDT 2024 4 14 0 0 0).format "W"

/--
info: "5"
-/
#guard_msgs in
#eval (fmtDT 2024 4 30 0 0 0).format "W"

-- May 2024 starts Wednesday: W1=May1-4, W2=May5-11

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 5 1 0 0 0).format "W"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT 2024 5 5 0 0 0).format "W"

-- November 2024 starts Friday: W1=Nov1-2, W2=Nov3-9

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 11 1 0 0 0).format "W"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT 2024 11 3 0 0 0).format "W"

-- ===== E / e / c (WEEKDAY) =====
-- 2024-01-01 = Monday, 2024-01-02 = Tuesday, 2024-01-06 = Saturday, 2024-01-07 = Sunday

/--
info: "Mon Mon Mon Monday M"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "E EE EEE EEEE EEEEE"

/--
info: "Tue Tue Tue Tuesday T"
-/
#guard_msgs in
#eval (fmtDT 2024 1 2 0 0 0).format "E EE EEE EEEE EEEEE"

/--
info: "Sat Sat Sat Saturday S"
-/
#guard_msgs in
#eval (fmtDT 2024 1 6 0 0 0).format "E EE EEE EEEE EEEEE"

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval (fmtDT 2024 1 7 0 0 0).format "E EE EEE EEEE EEEEE"

-- e: ISO numeric (Mon=1..Sun=7)

/--
info: "1 01 Mon Monday M"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "e ee eee eeee eeeee"

/--
info: "7 07 Sun Sunday S"
-/
#guard_msgs in
#eval (fmtDT 2024 1 7 0 0 0).format "e ee eee eeee eeeee"

-- c: stand-alone weekday

/--
info: "1 Mon Monday M"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "c ccc cccc ccccc"

/--
info: "7 Sun Sunday S"
-/
#guard_msgs in
#eval (fmtDT 2024 1 7 0 0 0).format "c ccc cccc ccccc"

-- ===== F (DAY-IN-MONTH: n-th occurrence of weekday) =====

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 4 1 0 0 0).format "F"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 4 7 0 0 0).format "F"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT 2024 4 8 0 0 0).format "F"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtDT 2024 4 14 0 0 0).format "F"

/--
info: "4"
-/
#guard_msgs in
#eval (fmtDT 2024 4 28 0 0 0).format "F"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 7 4 0 0 0).format "F"

-- ===== H / h / K / k (HOURS) =====
-- midnight: H=0, h=12, K=0, k=24

/--
info: "0 12 0 24"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "H h K k"

-- 1 AM: H=1, h=1, K=1, k=1

/--
info: "1 1 1 1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 1 0 0).format "H h K k"

-- 11 AM: H=11, h=11, K=11, k=11

/--
info: "11 11 11 11"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 11 0 0).format "H h K k"

-- noon: H=12, h=12, K=0, k=12

/--
info: "12 12 0 12"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "H h K k"

-- 1 PM: H=13, h=1, K=1, k=13

/--
info: "13 1 1 13"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 13 0 0).format "H h K k"

-- 11 PM: H=23, h=11, K=11, k=23

/--
info: "23 11 11 23"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 0 0).format "H h K k"

-- zero-padded

/--
info: "00 12 00 24"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "HH hh KK kk"

/--
info: "12 12 00 12"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "HH hh KK kk"

-- ===== a (AM/PM) =====

/--
info: "AM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "a"

/--
info: "AM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 11 59 59).format "a"

/--
info: "PM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "a"

/--
info: "PM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 59 59).format "a"

/--
info: "ante meridiem"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 9 0 0).format "aaaa"

/--
info: "post meridiem"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 15 0 0).format "aaaa"

/--
info: "a"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 9 0 0).format "aaaaa"

/--
info: "p"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 15 0 0).format "aaaaa"

-- ===== b (DAY PERIOD: noon / midnight / AM / PM) =====

/--
info: "midnight midnight midnight"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "b bb bbb"

/--
info: "noon noon noon"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "b bb bbb"

-- one second past midnight is AM, not midnight

/--
info: "AM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 1).format "b"

-- one second past noon is PM, not noon

/--
info: "PM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 1).format "b"

/--
info: "AM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 11 59 59).format "b"

/--
info: "PM"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 59 59).format "b"

-- PlainTime: b also works

/--
info: "midnight"
-/
#guard_msgs in
#eval (fmtPT 0 0 0).format "b"

/--
info: "noon"
-/
#guard_msgs in
#eval (fmtPT 12 0 0).format "b"

/--
info: "AM"
-/
#guard_msgs in
#eval (fmtPT 0 0 1).format "b"

-- ===== B (EXTENDED DAY PERIOD) =====

/--
info: "midnight"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "B"

-- h < 6 = night

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 3 0 0).format "B"

-- 6 ≤ h < 12 = morning

/--
info: "in the morning"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 9 0 0).format "B"

/--
info: "noon"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "B"

-- 12 < h < 18 = afternoon

/--
info: "in the afternoon"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 15 0 0).format "B"

-- 18 ≤ h < 21 = evening

/--
info: "in the evening"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 19 0 0).format "B"

-- h ≥ 21 = night

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 22 0 0).format "B"

-- boundary: 05:59:59 = night (h=5 < 6)

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 5 59 59).format "B"

-- boundary: 20:59:59 = evening (h=20, 18≤h<21)

/--
info: "in the evening"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 20 59 59).format "B"

-- one second past noon = afternoon (not "noon")

/--
info: "in the afternoon"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 1).format "B"

-- one second past midnight = night (h=0, not midnight because s≠0)

/--
info: "at night"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 1).format "B"

-- ===== m (MINUTE) =====

/--
info: "0 00"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "m mm"

/--
info: "30 30"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 30 0).format "m mm"

/--
info: "59 59"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 59 0).format "m mm"

/--
info: "5 05"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 5 0).format "m mm"

-- ===== s (SECOND) =====

/--
info: "0 00"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "s ss"

/--
info: "30 30"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 30).format "s ss"

/--
info: "59 59"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 59 59).format "s ss"

/--
info: "5 05"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 5).format "s ss"

-- ===== S (FRACTION OF SECOND: top-truncated nanoseconds) =====

/--
info: "1 12 123 1234 123456789"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 123456789).format "S SS SSS SSSS SSSSSSSSS"

/--
info: "9 98 987"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 987654321).format "S SS SSS"

-- 100 ms = 100000000 ns: S=1, SSS=100

/--
info: "1 100 100000000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 100000000).format "S SSS SSSSSSSSS"

-- zero nanoseconds

/--
info: "0 000 000000000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 0).format "S SSS SSSSSSSSS"

-- 1 nanosecond: SSSSSSSSS = 000000001

/--
info: "000000001"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 1).format "SSSSSSSSS"

/--
info: "5 50 500"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 500000000).format "S SS SSS"

-- ===== A (MILLISECOND OF DAY) =====

/--
info: "0"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0).format "A"

/--
info: "43200000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0).format "A"

/--
info: "86399000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 59 59).format "A"

-- 1 hour = 3600000 ms

/--
info: "3600000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 1 0 0).format "A"

-- 1 minute = 60000 ms

/--
info: "60000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 1 0).format "A"

-- 1 second = 1000 ms

/--
info: "1000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 1).format "A"

-- 999 ms (999000000 ns)

/--
info: "999"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 999000000).format "A"

-- ===== n (NANOSECOND) =====

/--
info: "0"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 0).format "n"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 1).format "n"

/--
info: "123456789"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 123456789).format "n"

/--
info: "999999999"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 999999999).format "n"

-- ===== N (NANOSECOND OF DAY) =====

/--
info: "0"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 0).format "N"

/--
info: "1"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 0 0 0 1).format "N"

-- noon = 12 * 3600 * 1_000_000_000 = 43200000000000

/--
info: "43200000000000"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 12 0 0 0).format "N"

-- 23:59:59.999999999

/--
info: "86399999999999"
-/
#guard_msgs in
#eval (fmtDT 2024 1 1 23 59 59 999999999).format "N"

-- ===== PlainDate spot checks =====

/--
info: "AD AD AD Anno Domini A"
-/
#guard_msgs in
#eval (fmtPD 2024 6 15).format "G GG GGG GGGG GGGGG"

/--
info: "BC Before Christ"
-/
#guard_msgs in
#eval (fmtPD (-100) 6 15).format "G GGGG"

/--
info: "2024 24 2024"
-/
#guard_msgs in
#eval (fmtPD 2024 1 1).format "y yy yyyy"

/--
info: "101 01"
-/
#guard_msgs in
#eval (fmtPD (-100) 1 1).format "y yy"

/--
info: "1 001"
-/
#guard_msgs in
#eval (fmtPD 2024 1 1).format "D DDD"

/--
info: "366"
-/
#guard_msgs in
#eval (fmtPD 2024 12 31).format "D"

/--
info: "365"
-/
#guard_msgs in
#eval (fmtPD 2023 12 31).format "D"

/--
info: "1 01 Q1 1st quarter"
-/
#guard_msgs in
#eval (fmtPD 2024 1 15).format "Q QQ QQQ QQQQ"

/--
info: "4 04 Q4 4th quarter"
-/
#guard_msgs in
#eval (fmtPD 2024 10 15).format "Q QQ QQQ QQQQ"

-- W (week of month, Sunday-first) on PlainDate

/--
info: "1"
-/
#guard_msgs in
#eval (fmtPD 2024 4 1).format "W"

/--
info: "2"
-/
#guard_msgs in
#eval (fmtPD 2024 4 7).format "W"

/--
info: "3"
-/
#guard_msgs in
#eval (fmtPD 2024 4 14).format "W"

/--
info: "Mon Mon Mon Monday M"
-/
#guard_msgs in
#eval (fmtPD 2024 1 1).format "E EE EEE EEEE EEEEE"

/--
info: "Sun Sun Sun Sunday S"
-/
#guard_msgs in
#eval (fmtPD 2024 1 7).format "E EE EEE EEEE EEEEE"

-- (Bug-fix regression tests have been moved to timeBugs.lean)
