/-
Copyright (c) 2024 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Time.Notation.Spec
public import Std.Time.Format.Modifier
public import Std.Time.Format.Basic
import all Std.Time.Format.Basic

public section

namespace Std
namespace Time
namespace Formats
open Internal

set_option linter.all true

/--
The ISO 8601 format, used for representing date and time in a standardized
format. The format follows the pattern `uuuu-MM-dd'T'HH:mm:ssXXX`.
-/
def iso8601 : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ssXXX")

/--
The americanDate format, which follows the pattern `MM-dd-uuuu`.
-/
def americanDate : Format Awareness.any := datespec("MM-dd-uuuu")

/--
The europeanDate format, which follows the pattern `dd-MM-uuuu`.
-/
def europeanDate : Format Awareness.any := datespec("dd-MM-uuuu")

/--
The time12Hour format, which follows the pattern `hh:mm:ss a` for representing time
in a 12-hour clock format with an upper case AM/PM marker.
-/
def time12Hour : Format Awareness.any := datespec("hh:mm:ss a")

/--
The Time24Hour format, which follows the pattern `HH:mm:ss` for representing time
in a 24-hour clock format.
-/
def time24Hour : Format Awareness.any := datespec("HH:mm:ss")

/--
The DateTimeZone24Hour format, which follows the pattern `uuuu-MM-dd:HH:mm:ss.SSSSSSSSS` for
representing date, time, and time zone.
-/
def dateTime24Hour : Format (.only .GMT) := datespec("uuuu-MM-dd:HH:mm:ss.SSSSSSSSS")

/--
The DateTimeWithZone format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZ`
for representing date, time, and time zone.
-/
def dateTimeWithZone : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZ")

/--
The leanTime24Hour format, which follows the pattern `HH:mm:ss.SSSSSSSSS` for representing time
in a 24-hour clock format. It uses the default value that can be parsed with the
notation of dates.
-/
def leanTime24Hour : Format Awareness.any := datespec("HH:mm:ss.SSSSSSSSS")

/--
The leanTime24HourNoNanos format, which follows the pattern `HH:mm:ss` for representing time
in a 24-hour clock format. It uses the default value that can be parsed with the
notation of dates.
-/
def leanTime24HourNoNanos : Format Awareness.any := datespec("HH:mm:ss")

/--
The leanDateTime24Hour format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSS` for
representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTime24Hour : Format (.only .GMT) := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSS")

/--
The leanDateTime24HourNoNanos format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss` for
representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTime24HourNoNanos : Format (.only .GMT) := datespec("uuuu-MM-dd'T'HH:mm:ss")

/--
The leanDateTimeWithZone format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZZZ`
for representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTimeWithZone : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZZZ")

/--
The leanDateTimeWithZoneNoNanos format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ssZZZZZ`
for representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTimeWithZoneNoNanos : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ssZZZZZ")

/--
The leanDateTimeWithIdentifier format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss[z]`
for representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTimeWithIdentifier : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss'['VV']'")

/--
The leanDateTimeWithIdentifierAndNanos format, which follows the pattern `uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSS'[z]'`
for representing date, time, and time zone. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDateTimeWithIdentifierAndNanos : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSS'['VV']'")

/--
The leanDateTimeWithZoneAndName format, which follows the pattern
`uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZZZ'['VV']'` for representing date, time, timezone offset,
and timezone identifier. This is the canonical Lean format used in `repr` for named timezones.
-/
def leanDateTimeWithZoneAndName : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSZZZZZ'['VV']'")

/--
The leanDateTimeWithZoneAndNameNoNanos format, which follows the pattern
`uuuu-MM-dd'T'HH:mm:ssZZZZZ'['zzzz']'` for representing date, time, timezone offset, and timezone
identifier without nanoseconds.
-/
def leanDateTimeWithZoneAndNameNoNanos : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ssZZZZZ'['VV']'")

/--
The Lean Date format, which follows the pattern `uuuu-MM-dd`. It uses the default value that can be parsed with the
notation of dates.
-/
def leanDate : Format Awareness.any := datespec("uuuu-MM-dd")

/--
The SQLDate format, which follows the pattern `uuuu-MM-dd` and is commonly used
in SQL databases to represent dates.
-/
def sqlDate : Format Awareness.any := datespec("uuuu-MM-dd")

/--
The LongDateFormat, which follows the pattern `EEEE, MMMM d, uuuu HH:mm:ss` for
representing a full date and time with the day of the week and month name.
-/
def longDateFormat : Format (.only .GMT) := datespec("EEEE, MMMM d, uuuu HH:mm:ss")

/--
The AscTime format, which follows the pattern `EEE MMM d HH:mm:ss uuuu`. This format
is often used in older systems for logging and time-stamping events.
-/
def ascTime : Format (.only .GMT) := datespec("EEE MMM d HH:mm:ss uuuu")

/--
The RFC822 format, which follows the pattern `eee, dd MMM uuuu HH:mm:ss ZZZ`.
This format is used in email headers and HTTP headers.
-/
def rfc822 : Format Awareness.any := datespec("eee, dd MMM uuuu HH:mm:ss ZZZ")

/--
The RFC850 format, which follows the pattern `eee, dd-MMM-yy HH:mm:ss ZZZ`.
This format is an older standard for representing date and time in headers.
-/
def rfc850 : Format Awareness.any := datespec("eee, dd-MMM-yy HH:mm:ss ZZZ")

/--
A `MultiFormat` that parses `leanDateTimeWithZone` with or without nanoseconds.
-/
def leanDateTimeWithZoneAlt : MultiFormat Awareness.any :=
  .new #[leanDateTimeWithZone, leanDateTimeWithZoneNoNanos]

/--
A `MultiFormat` that parses `leanDateTimeWithZoneAndName` with or without nanoseconds.
-/
def leanDateTimeWithZoneAndNameAlt : MultiFormat Awareness.any :=
  .new #[leanDateTimeWithZoneAndName, leanDateTimeWithZoneAndNameNoNanos]

/--
A `MultiFormat` that parses `leanDateTime24Hour` with or without nanoseconds.
-/
def leanDateTime24HourAlt : MultiFormat (.only .GMT) :=
  .new #[leanDateTime24Hour, leanDateTime24HourNoNanos]

/--
A `MultiFormat` that parses `leanTime24Hour` with or without nanoseconds.
-/
def leanTime24HourAlt : MultiFormat Awareness.any :=
  .new #[leanTime24Hour, leanTime24HourNoNanos]

/--
A `MultiFormat` that parses `leanDateTimeWithIdentifier` with or without nanoseconds.
-/
def leanDateTimeWithIdentifierAlt : MultiFormat Awareness.any :=
  .new #[leanDateTimeWithIdentifier, leanDateTimeWithIdentifierAndNanos]

end Formats

namespace Format

/--
Parses the input string, resolving any timezone identifier via the default timezone database.
For formats with a timezone identifier specifier but no offset specifier (e.g.
`uuuu-MM-dd'T'HH:mm:ss'['zzzz']'`), this performs a tzdb lookup to find the correct UTC offset.
For all other formats this behaves identically to `parse`.
-/
def parseIO (format : Format Awareness.any) (input : String) : IO ZonedDateTime := do
  if format.hasIdentifierSpecifier && !format.hasOffsetSpecifier then
    match format.parseUnchecked input with
    | .error err => throw <| IO.userError err
    | .ok zdt =>
      let rules ← Database.defaultGetZoneRules zdt.timezone.name
      pure <| ZonedDateTime.ofPlainDateTime zdt.toPlainDateTime rules
  else
    IO.ofExcept (format.parse input)

end Format

namespace TimeZone

/--
Parses a string into a `TimeZone` object. The input string must be in the format `"VV ZZZZZ"`.
-/
def fromTimeZone (input : String) : Except String TimeZone := do
  let spec : Format Awareness.any := datespec("VV ZZZZZ")
  spec.parseBuilder (fun id off => some (TimeZone.mk off id (off.toIsoString true) false)) input

namespace Offset

/--
Parses a string representing an offset into an `Offset` object. The input string must follow the `"xxx"` format.
-/
def fromOffset (input : String) : Except String Offset := do
  let spec : Format Awareness.any := datespec("xxx")
  spec.parseBuilder some input

end Offset
end TimeZone

namespace PlainDate

/--
Formats a `PlainDate` using a specific format.
-/
def format (date : PlainDate) (format : String) : String :=
  let format : Except String (Format Awareness.any) := Format.spec format
  match format with
  | .error err => s!"error: {err}"
  | .ok res =>
    let res := res.formatGeneric fun
      | .G _ => some date.era
      | .y _ => some date.year
      | .Y _ => some date.weekBasedYear
      | .u _ => some date.year
      | .D _ => some (Sigma.mk date.year.isLeap date.dayOfYear)
      | .Q _ | .q _ => some date.quarter
      | .w _ => some date.weekOfYear
      | .W _ => some (date.alignedWeekOfMonth .sunday)
      | .M _ | .L _ => some date.month
      | .d _ => some date.day
      | .E _ => some date.weekday
      | .e _ | .c _ => some date.weekday
      | .F _ => some date.weekOfMonth
      | _ => none
    match res with
    | some res => res
    | none => "invalid time"

/--
Parses a `String` in the `AmericanDate` or `SQLDate` format and returns a `PlainDate`.
-/
def parse (input : String) : Except String PlainDate :=
  Formats.americanDate.parseBuilder (fun m d y => PlainDate.ofYearMonthDay? y m d) input
  <|> Formats.sqlDate.parseBuilder PlainDate.ofYearMonthDay? input

def leanDateString (d : PlainDate) : String :=
  Formats.leanDate.formatBuilder d.year d.month d.day

instance : ToString PlainDate where
  toString := leanDateString

instance : Repr PlainDate where
  reprPrec d := Repr.addAppParen ("date(\"" ++ leanDateString d ++ "\")")

end PlainDate

namespace PlainTime

/--
Formats a `PlainTime` using a specific format.
-/
def format (time : PlainTime) (format : String) : String :=
  let format : Except String (Format Awareness.any) := Format.spec format
  match format with
  | .error err => s!"error: {err}"
  | .ok res =>
    let res := res.formatGeneric fun
      | .H _ => some time.hour
      | .k _ => some (time.hour.shiftTo1BasedHour)
      | .m _ => some time.minute
      | .n _ => some time.nanosecond
      | .s _ => some time.second
      | .a _ => some (HourMarker.ofOrdinal time.hour)
      | .b _ =>
        let h := time.hour.val
        let m := time.minute.val
        let s := time.second.val
        let n := time.nanosecond.val
        some <|
          if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
          else if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
          else if h < 12 then .am
          else .pm
      | .B _ =>
        let h := time.hour.val
        let m := time.minute.val
        let s := time.second.val
        let n := time.nanosecond.val
        some <|
          if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
          else if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
          else if h < 6 ∨ h ≥ 21 then .night
          else if h < 12 then .morning
          else if h < 18 then .afternoon
          else .evening
      | .h _ => some time.hour.toRelative
      | .K _ => some (time.hour.emod 12 (by decide))
      | .S _ => some time.nanosecond
      | .A _ => some time.toMilliseconds
      | .N _ => some time.toNanoseconds
      | _ => none
    match res with
    | some res => res
    | none => "invalid time"

/--
Parses a `String` in the `Time12Hour`, `Time24Hour`, or lean time (with optional nanoseconds) format
and returns a `PlainTime`.
-/
def parse (input : String) : Except String PlainTime :=
  Formats.time12Hour.parseBuilder (fun h m s a => do
    let value ← Internal.Bounded.ofInt? h.val
    some <| PlainTime.ofHourMinuteSeconds (HourMarker.toAbsolute a value) m s) input
  <|> Formats.leanTime24Hour.parseBuilder (fun h m s n => some <| PlainTime.ofHourMinuteSecondsNano h m s n) input
  <|> Formats.time24Hour.parseBuilder (fun h m s => some (PlainTime.ofHourMinuteSeconds h m s)) input

def leanTimeString (t : PlainTime) : String :=
  Formats.leanTime24Hour.formatBuilder t.hour t.minute t.second t.nanosecond

instance : ToString PlainTime where
  toString := leanTimeString

instance : Repr PlainTime where
  reprPrec data := Repr.addAppParen ("time(\"" ++ leanTimeString data ++ "\")")

end PlainTime

namespace ZonedDateTime

/--
Formats a `ZonedDateTime` using a specific format.
-/
def format (data: ZonedDateTime) (format : String) : String :=
  let format : Except String (Format Awareness.any) := Format.spec format
  match format with
  | .error err => s!"error: {err}"
  | .ok res => res.format data

/--
Parses a `String` in common zoned date-time formats and returns a `ZonedDateTime`.
This parser does not resolve timezone identifiers like `[Europe/Paris]`; use `parseIO` for that.
-/
-- Wraps Format.parse to fix type unification (Awareness.any.type vs ZonedDateTime).
private def parseFormat (fmt : Format Awareness.any) (input : String) : Except String ZonedDateTime :=
  fmt.parse input

def parse (input : String) : Except String ZonedDateTime :=
  parseFormat Formats.iso8601 input
  <|> parseFormat Formats.rfc822 input
  <|> parseFormat Formats.rfc850 input
  <|> parseFormat Formats.leanDateTimeWithZone input
  <|> parseFormat Formats.leanDateTimeWithZoneNoNanos input
  <|> parseFormat Formats.leanDateTimeWithZoneAndName input
  <|> parseFormat Formats.leanDateTimeWithZoneAndNameNoNanos input
  <|> parseFormat Formats.dateTimeWithZone input
  <|> parseFormat Formats.leanDateTimeWithIdentifier input
  <|> parseFormat Formats.leanDateTimeWithIdentifierAndNanos input

/--
Parses a `String` in common zoned date-time formats.
If the input uses a timezone identifier (for example, `[Europe/Paris]`), it resolves it using the default timezone database.
-/
def parseIO (input : String) : IO ZonedDateTime := do
  match parse input with
  | .ok zdt => pure zdt
  | .error err =>
    let identParse : Except String ZonedDateTime :=
      Formats.leanDateTimeWithIdentifier.parseUnchecked input
      <|> Formats.leanDateTimeWithIdentifierAndNanos.parseUnchecked input
    match identParse with
    | .ok zdt =>
      let rules ← Database.defaultGetZoneRules zdt.timezone.name
      pure <| ZonedDateTime.ofPlainDateTime zdt.toPlainDateTime rules
    | .error _ => throw <| IO.userError err

instance : ToString ZonedDateTime where
  toString data := Formats.leanDateTimeWithIdentifierAndNanos.format data

instance : Repr ZonedDateTime where
  reprPrec data :=
    let name := data.timezone.name
    let str :=
      if name == data.timezone.offset.toIsoString true then
        Formats.leanDateTimeWithZone.format data
      else
        Formats.leanDateTimeWithZoneAndName.format data
    Repr.addAppParen ("zoned(\"" ++ str ++ "\")")

end ZonedDateTime

namespace PlainDateTime

/--
Formats a `PlainDateTime` using a specific format.
-/
def format (date : PlainDateTime) (format : String) : String :=
  let format : Except String (Format Awareness.any) := Format.spec format
  match format with
  | .error err => s!"error: {err}"
  | .ok res =>
    let res := res.formatGeneric fun
      | .G _ => some date.era
      | .y _ => some date.year
      | .Y _ =>
        let week := date.weekOfYear
        some <|
          if date.month.val = 1 ∧ week.val ≥ 52 then
            date.year - 1
          else if date.month.val = 12 ∧ week.val = 1 then
            date.year + 1
          else
            date.year
      | .u _ => some date.year
      | .D _ => some (Sigma.mk date.year.isLeap date.dayOfYear)
      | .Q _ | .q _ => some date.quarter
      | .w _ => some date.weekOfYear
      | .W _ => some (date.date.alignedWeekOfMonth .sunday)
      | .M _ | .L _ => some date.month
      | .d _ => some date.day
      | .E _ => some date.weekday
      | .e _ | .c _ => some date.weekday
      | .F _ => some date.weekOfMonth
      | .H _ => some date.hour
      | .k _ => some date.hour.shiftTo1BasedHour
      | .m _ => some date.minute
      | .n _ => some date.nanosecond
      | .s _ => some date.time.second
      | .a _ => some (HourMarker.ofOrdinal date.hour)
      | .b _ =>
        let h := date.hour.val
        let m := date.minute.val
        let s := date.time.second.val
        let n := date.nanosecond.val
        some <|
          if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
          else if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
          else if h < 12 then .am
          else .pm
      | .B _ =>
        let h := date.hour.val
        let m := date.minute.val
        let s := date.time.second.val
        let n := date.nanosecond.val
        some <|
          if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
          else if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
          else if h < 6 ∨ h ≥ 21 then .night
          else if h < 12 then .morning
          else if h < 18 then .afternoon
          else .evening
      | .h _ => some date.hour.toRelative
      | .K _ => some (date.hour.emod 12 (by decide))
      | .S _ => some date.nanosecond
      | .A _ => some date.time.toMilliseconds
      | .N _ => some date.time.toNanoseconds
      | _ => none
    match res with
    | some res => res
    | none => "invalid time"

/--
Parses a `String` in the `AscTime`, `LongDate`, `DateTime`, or `LeanDateTime` format and returns a `PlainDateTime`.
-/
def parse (date : String) : Except String PlainDateTime :=
  (Formats.ascTime.parse date).map DateTime.toPlainDateTime
  <|> (Formats.longDateFormat.parse date).map DateTime.toPlainDateTime
  <|> (Formats.dateTime24Hour.parse date).map DateTime.toPlainDateTime
  <|> (Formats.leanDateTime24HourAlt.parse date).map DateTime.toPlainDateTime

def leanPlainDateTimeString (date : PlainDateTime) : String :=
  Formats.leanDateTime24Hour.formatBuilder date.year date.month date.day date.hour date.minute date.time.second date.nanosecond

instance : ToString PlainDateTime where
  toString := leanPlainDateTimeString

instance : Repr PlainDateTime where
  reprPrec data := Repr.addAppParen ("datetime(\"" ++ leanPlainDateTimeString data ++ "\")")

end PlainDateTime

namespace DateTime

/--
Formats a `DateTime` using a specific format.
-/
def format (data: DateTime tz) (format : String) : String :=
  let format : Except String (Format Awareness.any) := Format.spec format
  match format with
  | .error err => s!"error: {err}"
  | .ok res => res.format data

/--
Parses a `String` in the `AscTime` or `LongDate` format and returns a `DateTime`.
-/
def parse (date : String) : Except String (DateTime .GMT) :=
  Formats.ascTime.parse date
  <|> Formats.longDateFormat.parse date

instance : Repr (DateTime tz) where
  reprPrec data := Repr.addAppParen (Formats.leanDateTimeWithZone.format data)

instance : ToString (DateTime tz) where
  toString data := Formats.leanDateTimeWithZone.format data

end DateTime
