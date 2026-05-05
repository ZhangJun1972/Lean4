/-
Copyright (c) 2024 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Time.Format.Modifier
import Init.Data.String.TakeDrop
import Init.Data.String.Search

public section

/-!
This module defines the `Formatter` types. It is based on the Java's `DateTimeFormatter` format.
-/

namespace Std
namespace Time
open Internal
open Std.Internal.Parsec.String
open Std.Internal.Parsec Lean PlainTime PlainDate TimeZone DateTime

set_option linter.all true

/--
The part of a formatting string. A string is just a text and a modifier is in the format described in
the `Modifier` type.
-/
inductive FormatPart
  /--
  A string literal.
  -/
  | string (val : String)

  /--
  A modifier that renders some data into text.
  -/
  | modifier (modifier : Modifier)
  deriving Repr

instance : Coe String FormatPart where
  coe := .string

instance : Coe Modifier FormatPart where
  coe := .modifier

/--
The format of date and time string.
-/
abbrev FormatString := List FormatPart

/--
If the format is aware of some timezone data it parses or if it parses any timezone.
-/
inductive Awareness

  /--
  The format only parses a single timezone.
  -/
  | only : TimeZone → Awareness

  /--
  The format parses any timezone.
  -/
  | any

namespace Awareness

instance : Coe TimeZone Awareness where
  coe := .only

set_option linter.missingDocs false in  -- TODO
@[simp, expose /- for codegen -/]
def type (x : Awareness) : Type :=
  match x with
  | .any => ZonedDateTime
  | .only tz => DateTime tz

private instance : Inhabited (type aw) where
  default := by
    simp [type]
    split <;> exact Inhabited.default

private def getD (x : Awareness) (default : TimeZone) : TimeZone :=
  match x with
  | .any => default
  | .only tz => tz

end Awareness

/--
Configuration options for formatting and parsing date/time strings.
-/
structure FormatConfig where
  /--
  Whether to allow leap seconds, such as `2016-12-31T23:59:60Z`.
  Default is `false`.
  -/
  allowLeapSeconds : Bool := false

deriving Inhabited, Repr

/--
A specification on how to format a data or parse some string.
-/
structure Format (awareness : Awareness) where
  /--
  Configuration options for formatting behavior.
  -/
  config : FormatConfig

  /--
  The format string used for parsing and formatting.
  -/
  string : FormatString
  deriving Inhabited, Repr

private def parseFormatPart : Parser FormatPart
  := (.modifier <$> parseModifier)
  <|> (pchar '\\') *> any <&> (.string ∘ toString)
  <|> (pchar '\"' *>  many1Chars (satisfy (· ≠ '\"')) <* pchar '\"') <&> .string
  <|> (pchar '\'' *>  many1Chars (satisfy (· ≠ '\'')) <* pchar '\'') <&> .string
  <|> many1Chars (satisfy (fun x => ¬Char.isAlpha x ∧ x ≠ '\'' ∧ x ≠ '\"')) <&> .string

private def specParser : Parser FormatString :=
  (Array.toList <$> many parseFormatPart) <* eof

private def specParse (s : String) : Except String FormatString :=
  specParser.run s

-- Pretty printer

private def leftPad (n : Nat) (a : Char) (s : String) : String :=
  "".pushn a (n -  s.length) ++ s

private def rightPad (n : Nat) (a : Char) (s : String) : String :=
  s ++ "".pushn a (n - s.length)

private def pad (size : Nat)  (n : Int) (cut : Bool := false) : String :=
  let (sign, n) := if n < 0 then ("-", -n) else ("", n)

  let numStr := toString n
  if numStr.length > size then
    sign ++ if cut then numStr.drop (numStr.length - size) |>.copy else numStr
  else
    sign ++ leftPad size '0' numStr

private def rightTruncate (size : Nat)  (n : Int) (cut : Bool := false) : String :=
  let (sign, n) := if n < 0 then ("-", -n) else ("", n)

  let numStr := toString n
  if numStr.length > size then
    sign ++ if cut then numStr.take size |>.copy else numStr
  else
    sign ++ rightPad size '0' numStr

/- Locale-sensitive: will be parameterized by a LocaleSymbols structure. -/
section Locale

private def formatMonthLong : Month.Ordinal → String
  | ⟨1, _⟩ => "January"
  | ⟨2, _⟩ => "February"
  | ⟨3, _⟩ => "March"
  | ⟨4, _⟩ => "April"
  | ⟨5, _⟩ => "May"
  | ⟨6, _⟩ => "June"
  | ⟨7, _⟩ => "July"
  | ⟨8, _⟩ => "August"
  | ⟨9, _⟩ => "September"
  | ⟨10, _⟩ => "October"
  | ⟨11, _⟩ => "November"
  | ⟨12, _⟩ => "December"

private def formatMonthShort : Month.Ordinal → String
  | ⟨1, _⟩ => "Jan"
  | ⟨2, _⟩ => "Feb"
  | ⟨3, _⟩ => "Mar"
  | ⟨4, _⟩ => "Apr"
  | ⟨5, _⟩ => "May"
  | ⟨6, _⟩ => "Jun"
  | ⟨7, _⟩ => "Jul"
  | ⟨8, _⟩ => "Aug"
  | ⟨9, _⟩ => "Sep"
  | ⟨10, _⟩ => "Oct"
  | ⟨11, _⟩ => "Nov"
  | ⟨12, _⟩ => "Dec"

private def formatMonthNarrow : Month.Ordinal → String
  | ⟨1, _⟩  => "J"
  | ⟨2, _⟩  => "F"
  | ⟨3, _⟩  => "M"
  | ⟨4, _⟩  => "A"
  | ⟨5, _⟩  => "M"
  | ⟨6, _⟩  => "J"
  | ⟨7, _⟩  => "J"
  | ⟨8, _⟩  => "A"
  | ⟨9, _⟩  => "S"
  | ⟨10, _⟩ => "O"
  | ⟨11, _⟩ => "N"
  | ⟨12, _⟩ => "D"

private def formatWeekdayLong : Weekday → String
  | .sunday => "Sunday"
  | .monday => "Monday"
  | .tuesday => "Tuesday"
  | .wednesday => "Wednesday"
  | .thursday => "Thursday"
  | .friday => "Friday"
  | .saturday => "Saturday"

private def formatWeekdayShort : Weekday → String
  | .sunday => "Sun"
  | .monday => "Mon"
  | .tuesday => "Tue"
  | .wednesday => "Wed"
  | .thursday => "Thu"
  | .friday => "Fri"
  | .saturday => "Sat"

private def formatWeekdayNarrow : Weekday → String
  | .sunday => "S"
  | .monday => "M"
  | .tuesday => "T"
  | .wednesday => "W"
  | .thursday => "T"
  | .friday => "F"
  | .saturday => "S"

private def formatEraShort : Year.Era → String
  | .bce => "BC"
  | .ce  => "AD"

private def formatEraLong : Year.Era → String
  | .bce => "Before Christ"
  | .ce  => "Anno Domini"

private def formatEraNarrow : Year.Era → String
  | .bce => "B"
  | .ce  => "A"

private def formatQuarterNumber : Month.Quarter → String
  |⟨1, _⟩ => "1"
  |⟨2, _⟩ => "2"
  |⟨3, _⟩ => "3"
  |⟨4, _⟩ => "4"

private def formatQuarterShort : Month.Quarter → String
  | ⟨1, _⟩ => "Q1"
  | ⟨2, _⟩ => "Q2"
  | ⟨3, _⟩ => "Q3"
  | ⟨4, _⟩ => "Q4"

private def formatQuarterLong : Month.Quarter → String
  | ⟨1, _⟩ => "1st quarter"
  | ⟨2, _⟩ => "2nd quarter"
  | ⟨3, _⟩ => "3rd quarter"
  | ⟨4, _⟩ => "4th quarter"

private def formatMarkerShort (marker : HourMarker) : String :=
  match marker with
  | .am => "AM"
  | .pm => "PM"

private def formatMarkerLong (marker : HourMarker) : String :=
  match marker with
  | .am => "ante meridiem"
  | .pm => "post meridiem"

private def formatMarkerNarrow (marker : HourMarker) : String :=
  match marker with
  | .am => "a"
  | .pm => "p"

private def formatDayPeriodShort : DayPeriod → String
  | .am => "AM"
  | .pm => "PM"
  | .noon => "noon"
  | .midnight => "midnight"

private def formatDayPeriodLong : DayPeriod → String
  | .am => "AM"
  | .pm => "PM"
  | .noon => "noon"
  | .midnight => "midnight"

private def formatDayPeriodNarrow : DayPeriod → String
  | .am => "a"
  | .pm => "p"
  | .noon => "n"
  | .midnight => "mi"

private def formatExtendedDayPeriodShort : ExtendedDayPeriod → String
  | .midnight => "midnight"
  | .night => "at night"
  | .morning => "in the morning"
  | .noon => "noon"
  | .afternoon => "in the afternoon"
  | .evening => "in the evening"

private def formatExtendedDayPeriodNarrow : ExtendedDayPeriod → String
  | .midnight => "mi"
  | .night => "at night"
  | .morning => "in the morning"
  | .noon => "n"
  | .afternoon => "in the afternoon"
  | .evening => "in the evening"

end Locale

private def toIsoString (offset : Offset) (withMinutes : Bool) (withSeconds : Bool) (colon : Bool) : String :=
  let (sign, time) := if offset.second.val ≥ 0 then ("+", offset.second) else ("-", -offset.second)
  let time := PlainTime.ofSeconds time
  let pad := leftPad 2 '0' ∘ toString

  let data := s!"{sign}{pad time.hour.val}"
  let data := if withMinutes then s!"{data}{if colon then ":" else ""}{pad time.minute.val}" else data
  let data := if withSeconds ∧ time.second.val ≠ 0 then s!"{data}{if colon then ":" else ""}{pad time.second.val}" else data

  data

private def toLocalizedGMT (offset : Offset) (full : Bool) : String :=
  if offset.second.val = 0 then
    "GMT"
  else
    let (sign, time) := if offset.second.val ≥ 0 then ("+", offset.second) else ("-", -offset.second)
    let time := PlainTime.ofSeconds time
    let hour :=
      if full then
        leftPad 2 '0' (toString time.hour.val)
      else
        toString time.hour.val
    let hasMinute := full ∨ time.minute.val ≠ 0 ∨ time.second.val ≠ 0
    let withMinute :=
      if hasMinute then
        s!"GMT{sign}{hour}:{leftPad 2 '0' (toString time.minute.val)}"
      else
        s!"GMT{sign}{hour}"
    if time.second.val ≠ 0 then
      s!"{withMinute}:{leftPad 2 '0' (toString time.second.val)}"
    else
      withMinute

private def isUTCLabel (input : String) : Bool :=
  input = "Z"
  ∨ input = "UTC"
  ∨ input = "GMT"
  ∨ input = "+00"
  ∨ input = "+0000"
  ∨ input = "+00:00"
  ∨ input = "GMT+0"
  ∨ input = "GMT+00:00"

private def normalizeZoneName (input : String) (_ : Bool) : String :=
  if isUTCLabel input then "Z" else input

set_option linter.missingDocs false in  -- TODO
@[expose /- for codegen -/]
def TypeFormat : Modifier → Type
  | .G _ => Year.Era
  | .y _ => Year.Offset
  | .Y _ => Year.Offset
  | .u _ => Year.Offset
  | .D _ => Sigma Day.Ordinal.OfYear
  | .M _ => Month.Ordinal
  | .L _ => Month.Ordinal
  | .d _ => Day.Ordinal
  | .Q _ => Month.Quarter
  | .q _ => Month.Quarter
  | .w _ => Week.Ordinal
  | .W _ => Week.Ordinal.OfMonth
  | .E _ => Weekday
  | .e _ => Weekday
  | .c _ => Weekday
  | .F _ => Bounded.LE 1 5
  | .a _ => HourMarker
  | .b _ => DayPeriod
  | .B _ => ExtendedDayPeriod
  | .h _ => Bounded.LE 1 12
  | .K _ => Bounded.LE 0 11
  | .k _ => Bounded.LE 1 24
  | .H _ => Hour.Ordinal
  | .m _ => Minute.Ordinal
  | .s _ => Second.Ordinal true
  | .S _ => Nanosecond.Ordinal
  | .A _ => Millisecond.Offset
  | .n _ => Nanosecond.Ordinal
  | .N _ => Nanosecond.Offset
  | .V _ => String
  | .z _ => String
  | .v _ => String
  | .O _ => Offset
  | .X _ => Offset
  | .x _ => Offset
  | .Z _ => Offset

private def formatWith (modifier : Modifier) (data: TypeFormat modifier) : String :=
  match modifier with
  | .G format =>
    match format with
    | .short => formatEraShort data
    | .full => formatEraLong data
    | .narrow => formatEraNarrow data
    | .twoLetterShort => formatEraShort data
  | .y format =>
    let info := data.toInt
    let info := if info ≤ 0 then -info + 1 else info
    match format with
    | .any => pad 0 info
    | .twoDigit => pad 2 (info % 100)
    | .fourDigit => pad 4 info
    | .extended n => pad n info
  | .Y format =>
    let info := data.toInt
    let info := if info ≤ 0 then -info + 1 else info
    match format with
    | .any => pad 0 info
    | .twoDigit => pad 2 (info % 100)
    | .fourDigit => pad 4 info
    | .extended n => pad n info
  | .u format =>
    match format with
    | .any => pad 0 (data.toInt)
    | .twoDigit => pad 2 (data.toInt % 100)
    | .fourDigit => pad 4 data.toInt
    | .extended n => pad n data.toInt
  | .D format =>
    pad format.padding data.snd.val
  | .M format | .L format =>
    match format with
    | .inl format => pad format.padding data.val
    | .inr .short => formatMonthShort data
    | .inr .full => formatMonthLong data
    | .inr .narrow => formatMonthNarrow data
    | .inr .twoLetterShort => formatMonthShort data
  | .d format =>
    pad format.padding data.val
  | .Q format | .q format =>
    match format with
    | .inl format => pad format.padding data.val
    | .inr .short => formatQuarterShort data
    | .inr .full => formatQuarterLong data
    | .inr .narrow => formatQuarterNumber data
    | .inr .twoLetterShort => formatQuarterShort data
  | .w format =>
    pad format.padding data.val
  | .W format =>
    pad format.padding data.val
  | .E format =>
    match format with
    | .short => formatWeekdayShort data
    | .full => formatWeekdayLong data
    | .narrow => formatWeekdayNarrow data
    | .twoLetterShort =>
      match data with
      | .sunday => "Su"
      | .monday => "Mo"
      | .tuesday => "Tu"
      | .wednesday => "We"
      | .thursday => "Th"
      | .friday => "Fr"
      | .saturday => "Sa"
  | .e format | .c format =>
    match format with
    | .inl format => pad format.padding data.toOrdinal.val
    | .inr .short => formatWeekdayShort data
    | .inr .full => formatWeekdayLong data
    | .inr .narrow => formatWeekdayNarrow data
    | .inr .twoLetterShort =>
      match data with
      | .sunday => "Su"
      | .monday => "Mo"
      | .tuesday => "Tu"
      | .wednesday => "We"
      | .thursday => "Th"
      | .friday => "Fr"
      | .saturday => "Sa"
  | .F format =>
    pad format.padding data.val
  | .a format =>
    match format with
    | .short => formatMarkerShort data
    | .full => formatMarkerLong data
    | .narrow => formatMarkerNarrow data
    | .twoLetterShort => formatMarkerShort data
  | .b format =>
    match format with
    | .short => formatDayPeriodShort data
    | .full => formatDayPeriodLong data
    | .narrow => formatDayPeriodNarrow data
    | .twoLetterShort => formatDayPeriodShort data
  | .B format =>
    match format with
    | .short | .full | .twoLetterShort => formatExtendedDayPeriodShort data
    | .narrow => formatExtendedDayPeriodNarrow data
  | .h format => pad format.padding data.val
  | .K format => pad format.padding (data.val % 12)
  | .k format => pad format.padding data.val
  | .H format => pad format.padding data.val
  | .m format => pad format.padding data.val
  | .s format => pad format.padding data.val
  | .S format =>
    match format with
    | .nano => pad 9 data.val
    | .truncated n => ((leftPad 9 '0' (toString data.val)).take n).toString
  | .A format =>
    pad format.padding data.val
  | .n format =>
    pad format.padding data.val
  | .N format =>
    pad format.padding data.val
  | .V format =>
    match format with
    | .unknown => "unk"
    | .short | .full => if isUTCLabel data then "Z" else data
  | .z format =>
    match format with
    | .short => normalizeZoneName data false
    | .full => normalizeZoneName data true
  | .v format =>
    match format with
    | .short => normalizeZoneName data false
    | .full => normalizeZoneName data true
  | .O format =>
    match format with
    | .short => toLocalizedGMT data false
    | .full => toLocalizedGMT data true
  | .X format =>
    if data.second == 0 then
      "Z"
    else
      match format with
        | .hour => toIsoString data (data.second.val % 3600 ≠ 0) false false
        | .hourMinute => toIsoString data true false false
        | .hourMinuteColon => toIsoString data true false true
        | .hourMinuteSecond => toIsoString data true true false
        | .hourMinuteSecondColon => toIsoString data true true true
  | .x format =>
    match format with
    | .hour =>
      toIsoString data (data.second.val % 3600 ≠ 0) false false
    | .hourMinute =>
      toIsoString data true false false
    | .hourMinuteColon =>
      toIsoString data true false true
    | .hourMinuteSecond =>
      toIsoString data true (data.second.val % 60 ≠ 0) false
    | .hourMinuteSecondColon =>
      toIsoString data true true true
  | .Z format =>
    match format with
    | .hourMinute =>
      toIsoString data true false false
    | .full =>
      toLocalizedGMT data true
    | .hourMinuteSecondColon =>
      if data.second == 0
        then "Z"
        else toIsoString data true true true




private def dateFromModifier (date : DateTime tz) : TypeFormat modifier :=
  match modifier with
  | .G _ => date.era
  | .y _ => date.year
  | .Y _ => date.date.get.date.weekBasedYear
  | .u _ => date.year
  | .D _ => Sigma.mk _ date.dayOfYear
  | .M _ => date.month
  | .L _ => date.month
  | .d _ => date.day
  | .Q _ => date.quarter
  | .q _ => date.quarter
  | .w _ => date.date.get.date.weekOfYear
  | .W _ => date.date.get.date.alignedWeekOfMonth .sunday
  | .E _ =>  date.weekday
  | .e _ => date.weekday
  | .c _ => date.weekday
  | .F _ => date.weekOfMonth
  | .a _ => HourMarker.ofOrdinal date.hour
  | .b _ =>
    let h := date.hour.val
    let m := date.minute.val
    let s := date.date.get.time.second.val
    let n := date.nanosecond.val
    if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
    else if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
    else if h < 12 then .am
    else .pm
  | .B _ =>
    let h := date.hour.val
    let m := date.minute.val
    let s := date.date.get.time.second.val
    let n := date.nanosecond.val
    if h = 0 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .midnight
    else if h = 12 ∧ m = 0 ∧ s = 0 ∧ n = 0 then .noon
    else if h < 6 ∨ h ≥ 21 then .night
    else if h < 12 then .morning
    else if h < 18 then .afternoon
    else .evening
  | .h _ => HourMarker.toRelative date.hour |>.fst
  | .K _ => date.hour.emod 12 (by decide)
  | .k _ => date.hour.shiftTo1BasedHour
  | .H _ => date.hour
  | .m _ => date.minute
  | .s _ => date.date.get.time.second
  | .S _ => date.nanosecond
  | .A _ => date.date.get.time.toMilliseconds
  | .n _ => date.nanosecond
  | .N _ => date.date.get.time.toNanoseconds
  | .V _ => tz.name
  | .z .short => tz.abbreviation
  | .z .full => tz.name
  | .v .short => tz.abbreviation
  | .v .full => tz.name
  | .O _ => tz.offset
  | .X _ => tz.offset
  | .x _ => tz.offset
  | .Z _ => tz.offset

/- Locale-sensitive: will be parameterized by a LocaleSymbols structure. -/
section Locale

private def parseMonthLong : Parser Month.Ordinal
   := pstring "January" *> pure ⟨1, by decide⟩
  <|> pstring "February" *> pure ⟨2, by decide⟩
  <|> pstring "March" *> pure ⟨3, by decide⟩
  <|> pstring "April" *> pure ⟨4, by decide⟩
  <|> pstring "May" *> pure ⟨5, by decide⟩
  <|> pstring "June" *> pure ⟨6, by decide⟩
  <|> pstring "July" *> pure ⟨7, by decide⟩
  <|> pstring "August" *> pure ⟨8, by decide⟩
  <|> pstring "September" *> pure ⟨9, by decide⟩
  <|> pstring "October" *> pure ⟨10, by decide⟩
  <|> pstring "November" *> pure ⟨11, by decide⟩
  <|> pstring "December" *> pure ⟨12, by decide⟩

/--
Parses a short value of a `Month.Ordinal`
-/
def parseMonthShort : Parser Month.Ordinal
   := pstring "Jan" *> pure ⟨1, by decide⟩
  <|> pstring "Feb" *> pure ⟨2, by decide⟩
  <|> pstring "Mar" *> pure ⟨3, by decide⟩
  <|> pstring "Apr" *> pure ⟨4, by decide⟩
  <|> pstring "May" *> pure ⟨5, by decide⟩
  <|> pstring "Jun" *> pure ⟨6, by decide⟩
  <|> pstring "Jul" *> pure ⟨7, by decide⟩
  <|> pstring "Aug" *> pure ⟨8, by decide⟩
  <|> pstring "Sep" *> pure ⟨9, by decide⟩
  <|> pstring "Oct" *> pure ⟨10, by decide⟩
  <|> pstring "Nov" *> pure ⟨11, by decide⟩
  <|> pstring "Dec" *> pure ⟨12, by decide⟩

-- Narrow month letters are inherently ambiguous (J=Jan/Jun/Jul, M=Mar/May, A=Apr/Aug).
-- Parsing uses the first (earliest) month for each letter.
private def parseMonthNarrow : Parser Month.Ordinal
   := pstring "J" *> pure ⟨1, by decide⟩  -- Jan (Jun/Jul also start with J)
  <|> pstring "F" *> pure ⟨2, by decide⟩
  <|> pstring "M" *> pure ⟨3, by decide⟩  -- Mar (May also starts with M)
  <|> pstring "A" *> pure ⟨4, by decide⟩  -- Apr (Aug also starts with A)
  <|> pstring "S" *> pure ⟨9, by decide⟩
  <|> pstring "O" *> pure ⟨10, by decide⟩
  <|> pstring "N" *> pure ⟨11, by decide⟩
  <|> pstring "D" *> pure ⟨12, by decide⟩

private def parseWeekdayLong : Parser Weekday
   := pstring "Sunday" *> pure Weekday.sunday
  <|> pstring "Monday" *> pure Weekday.monday
  <|> pstring "Tuesday" *> pure Weekday.tuesday
  <|> pstring "Wednesday" *> pure Weekday.wednesday
  <|> pstring "Thursday" *> pure Weekday.thursday
  <|> pstring "Friday" *> pure Weekday.friday
  <|> pstring "Saturday" *> pure Weekday.saturday

private def parseWeekdayShort : Parser Weekday
   := pstring "Sun" *> pure Weekday.sunday
  <|> pstring "Mon" *> pure Weekday.monday
  <|> pstring "Tue" *> pure Weekday.tuesday
  <|> pstring "Wed" *> pure Weekday.wednesday
  <|> pstring "Thu" *> pure Weekday.thursday
  <|> pstring "Fri" *> pure Weekday.friday
  <|> pstring "Sat" *> pure Weekday.saturday

-- Narrow weekday letters are inherently ambiguous (S=Sun/Sat, T=Tue/Thu).
-- Parsing uses the first (earliest) weekday for each letter.
private def parseWeekdayNarrow : Parser Weekday
   := pstring "S" *> pure Weekday.sunday  -- Sun (Sat also starts with S)
  <|> pstring "M" *> pure Weekday.monday
  <|> pstring "T" *> pure Weekday.tuesday  -- Tue (Thu also starts with T)
  <|> pstring "W" *> pure Weekday.wednesday
  <|> pstring "F" *> pure Weekday.friday

private def parseWeekdaytwoLetterShort : Parser Weekday
   := pstring "Su" *> pure Weekday.sunday
  <|> pstring "Mo" *> pure Weekday.monday
  <|> pstring "Tu" *> pure Weekday.tuesday
  <|> pstring "We" *> pure Weekday.wednesday
  <|> pstring "Th" *> pure Weekday.thursday
  <|> pstring "Fr" *> pure Weekday.friday
  <|> pstring "Sa" *> pure Weekday.saturday

private def parseEraShort : Parser Year.Era
   := pstring "BC" *> pure Year.Era.bce
  <|> pstring "AD" *> pure Year.Era.ce

private def parseEraLong : Parser Year.Era
   := pstring "Before Christ" *> pure Year.Era.bce
  <|> pstring "Anno Domini" *> pure Year.Era.ce

private def parseEraNarrow : Parser Year.Era
   := pstring "B" *> pure Year.Era.bce
  <|> pstring "A" *> pure Year.Era.ce

private def parseQuarterNumber : Parser Month.Quarter
   := pstring "1" *> pure ⟨1, by decide⟩
  <|> pstring "2" *> pure ⟨2, by decide⟩
  <|> pstring "3" *> pure ⟨3, by decide⟩
  <|> pstring "4" *> pure ⟨4, by decide⟩

private def parseQuarterLong : Parser Month.Quarter
   := pstring "1st quarter" *> pure ⟨1, by decide⟩
  <|> pstring "2nd quarter" *> pure ⟨2, by decide⟩
  <|> pstring "3rd quarter" *> pure ⟨3, by decide⟩
  <|> pstring "4th quarter" *> pure ⟨4, by decide⟩

private def parseQuarterShort : Parser Month.Quarter
   := pstring "Q1" *> pure ⟨1, by decide⟩
  <|> pstring "Q2" *> pure ⟨2, by decide⟩
  <|> pstring "Q3" *> pure ⟨3, by decide⟩
  <|> pstring "Q4" *> pure ⟨4, by decide⟩

private def parseMarkerShort : Parser HourMarker
   := pstring "AM" *> pure HourMarker.am
  <|> pstring "PM" *> pure HourMarker.pm

private def parseMarkerLong : Parser HourMarker
   := pstring "ante meridiem" *> pure HourMarker.am
  <|> pstring "post meridiem" *> pure HourMarker.pm
  <|> parseMarkerShort

private def parseMarkerNarrow : Parser HourMarker
   := pstring "A" *> pure HourMarker.am
  <|> pstring "a" *> pure HourMarker.am
  <|> pstring "P" *> pure HourMarker.pm
  <|> pstring "p" *> pure HourMarker.pm

private def parseDayPeriodShort : Parser DayPeriod
   := pstring "noon"     *> pure DayPeriod.noon
  <|> pstring "midnight" *> pure DayPeriod.midnight
  <|> pstring "AM"       *> pure DayPeriod.am
  <|> pstring "PM"       *> pure DayPeriod.pm

private def parseDayPeriodLong : Parser DayPeriod
   := pstring "noon"          *> pure DayPeriod.noon
  <|> pstring "midnight"      *> pure DayPeriod.midnight
  <|> pstring "AM"            *> pure DayPeriod.am
  <|> pstring "PM"            *> pure DayPeriod.pm
  <|> pstring "ante meridiem" *> pure DayPeriod.am
  <|> pstring "post meridiem" *> pure DayPeriod.pm

private def parseDayPeriodNarrow : Parser DayPeriod
   := pstring "midnight" *> pure DayPeriod.midnight
  <|> pstring "noon"     *> pure DayPeriod.noon
  <|> pstring "mi"       *> pure DayPeriod.midnight
  <|> pstring "n"        *> pure DayPeriod.noon
  <|> pstring "a"        *> pure DayPeriod.am
  <|> pstring "p"        *> pure DayPeriod.pm

private def parseExtendedDayPeriodShort : Parser ExtendedDayPeriod
   := pstring "midnight"          *> pure .midnight
  <|> pstring "at night"          *> pure .night
  <|> pstring "in the morning"    *> pure .morning
  <|> pstring "noon"              *> pure .noon
  <|> pstring "in the afternoon"  *> pure .afternoon
  <|> pstring "in the evening"    *> pure .evening

private def parseExtendedDayPeriodNarrow : Parser ExtendedDayPeriod
   := pstring "midnight"          *> pure .midnight
  <|> pstring "mi"                *> pure .midnight
  <|> pstring "at night"          *> pure .night
  <|> pstring "in the morning"    *> pure .morning
  <|> pstring "noon"              *> pure .noon
  <|> pstring "n"                 *> pure .noon
  <|> pstring "in the afternoon"  *> pure .afternoon
  <|> pstring "in the evening"    *> pure .evening

end Locale

private def exactly (parse : Parser α) (size : Nat) : Parser (Array α) :=
  let rec go (acc : Array α) (count : Nat) : Parser (Array α) :=
    if count ≥ size then
      pure acc
    else do
      let res ← parse
      go (acc.push res) count.succ
  termination_by size - count

  go #[] 12

private def exactlyChars (parse : Parser Char) (size : Nat) : Parser String :=
  let rec go (acc : String) (count : Nat) : Parser String :=
    if count ≥ size then
      pure acc
    else do
      let res ← parse
      go (acc.push res) count.succ
  termination_by size - count

  go "" 0

private def parseSigned (parser : Parser Nat) : Parser Int := do
  let signed ← optional (pstring "-")
  let res ← parser
  return if signed.isSome then -res else res

private def parseNum (size : Nat) : Parser Nat :=
  String.toNat! <$> exactlyChars (satisfy Char.isDigit) size

private def parseNum1or2 : Parser Nat := do
  let first ← exactlyChars (satisfy Char.isDigit) 1
  let second ← optional (exactlyChars (satisfy Char.isDigit) 1)
  pure <| String.toNat! (first ++ second.getD "")

private def parseAtLeastNum (size : Nat) : Parser Nat :=
  String.toNat! <$> do
    let start ← exactlyChars (satisfy Char.isDigit) size
    let end_ ← manyChars (satisfy Char.isDigit)
    pure (start ++ end_)

private def parseFlexibleNum (size : Nat) : Parser Nat :=
  if size = 1 then parseAtLeastNum 1 else parseNum size

private def parseFractionNum (size : Nat) (pad : Nat) : Parser Nat :=
  String.toNat! <$> rightPad pad '0' <$> exactlyChars (satisfy Char.isDigit) size

private def parseIdentifier : Parser String :=
  many1Chars (satisfy (fun x => x.isAlpha ∨ x.isDigit ∨ x = '_' ∨ x = '-' ∨ x = '/'))

private def parseNatToBounded { n m : Nat } (parser : Parser Nat) : Parser (Bounded.LE n m) := do
  let res ← parser
  if h : n ≤ res ∧ res ≤ m then
    return Bounded.LE.ofNat' res h
  else
    fail s!"need a natural number in the interval of {n} to {m}"

private inductive Reason
  | yes
  | no
  | optional

private inductive HourDigits
  | two
  | oneOrTwo

private def parseOffset (withMinutes : Reason) (withSeconds : Reason) (withColon : Bool) (hourDigits := HourDigits.two) : Parser Offset := do
  let sign ← (pchar '+' *> pure 1) <|> (pchar '-' *> pure (-1))
  let hourParser : Parser Nat :=
    match hourDigits with
    | .two => parseNum 2
    | .oneOrTwo => parseNum1or2
  let hours : Hour.Offset ← UnitVal.ofInt <$> hourParser

  if hours.val < 0 ∨ hours.val > 23 then
    fail s!"invalid hour offset: {hours.val}. Must be between 0 and 23."

  let colon := if withColon then pchar ':' else pure ':'

  let parseUnit {n} (reason : Reason) : Parser (Option (UnitVal n)) :=
    match reason with
    | .yes => some <$> (colon *> UnitVal.ofInt <$> parseNum 2)
    | .no => pure none
    | .optional => optional (colon *> UnitVal.ofInt <$> parseNum 2)

  let minutes : Option Minute.Offset ← parseUnit withMinutes

  if let some m := minutes then
    if m.val > 59 then
      fail s!"invalid minute offset: {m.val}. Must be between 0 and 59."

  let seconds : Option Second.Offset ← parseUnit withSeconds

  if let some s := seconds then
    if s.val > 59 then
      fail s!"invalid second offset: {s.val}. Must be between 0 and 59."

  let hours := hours.toSeconds + (minutes.getD 0).toSeconds + (seconds.getD 0)

  return Offset.ofSeconds ⟨hours.val * sign⟩

private def parseLocalizedGMT (full : Bool) : Parser Offset := do
  skipString "GMT"
  let parseOff :=
    match full with
    | true => parseOffset .yes .optional true
    | false => parseOffset .optional .optional true (hourDigits := .oneOrTwo)
  let res ← optional parseOff
  pure (res.getD Offset.zero)

private def parseWith (config : FormatConfig) : (mod : Modifier) → Parser (TypeFormat mod)
  | .G format =>
    match format with
    | .short => parseEraShort
    | .full => parseEraLong
    | .narrow => parseEraNarrow
    | .twoLetterShort => parseEraShort
  | .y format =>
    match format with
    | .any => Int.ofNat <$> parseAtLeastNum 1
    | .twoDigit => (2000 + ·) <$> Int.ofNat <$> parseNum 2
    | .fourDigit => Int.ofNat <$> parseNum 4
    | .extended n =>
      Int.ofNat <$> (if n = 3 then parseAtLeastNum 3 else parseNum n)
  | .Y format =>
    match format with
    | .any => Int.ofNat <$> parseAtLeastNum 1
    | .twoDigit => (2000 + ·) <$> Int.ofNat <$> parseNum 2
    | .fourDigit => Int.ofNat <$> parseNum 4
    | .extended n =>
      Int.ofNat <$> (if n = 3 then parseAtLeastNum 3 else parseNum n)
  | .u format =>
    match format with
    | .any => parseSigned <| parseAtLeastNum 1
    | .twoDigit => (2000 + ·) <$> Int.ofNat <$> parseNum 2
    | .fourDigit => parseSigned <| parseNum 4
    | .extended n =>
      parseSigned <| (if n = 3 then parseAtLeastNum 3 else parseNum n)
  | .D format => Sigma.mk true <$> parseNatToBounded (parseFlexibleNum format.padding)
  | .M format | .L format =>
    match format with
    | .inl format => parseNatToBounded (parseFlexibleNum format.padding)
    | .inr .short => parseMonthShort
    | .inr .full => parseMonthLong
    | .inr .narrow => parseMonthNarrow
    | .inr .twoLetterShort => parseMonthShort
  | .d format => parseNatToBounded (parseFlexibleNum format.padding)
  | .Q format | .q format =>
    match format with
    | .inl format => parseNatToBounded (parseFlexibleNum format.padding)
    | .inr .short => parseQuarterShort
    | .inr .full => parseQuarterLong
    | .inr .narrow => parseQuarterNumber
    | .inr .twoLetterShort => parseQuarterShort
  | .w format => parseNatToBounded (parseFlexibleNum format.padding)
  | .W format => parseNatToBounded (parseFlexibleNum format.padding)
  | .E format =>
    match format with
    | .short => parseWeekdayShort
    | .full => parseWeekdayLong
    | .narrow => parseWeekdayNarrow
    | .twoLetterShort => parseWeekdaytwoLetterShort
  | .e format | .c format =>
    match format with
    | .inl format =>
      -- Parse ISO ordinal (Mon=1..Sun=7) and convert to Weekday
      Weekday.ofOrdinal <$>
        (parseNatToBounded (parseFlexibleNum format.padding) : Parser Weekday.Ordinal)
    | .inr .short => parseWeekdayShort
    | .inr .full => parseWeekdayLong
    | .inr .narrow => parseWeekdayNarrow
    | .inr .twoLetterShort => parseWeekdaytwoLetterShort
  | .F format => parseNatToBounded (parseFlexibleNum format.padding)
  | .a format =>
    match format with
    | .short => parseMarkerShort
    | .full => parseMarkerLong
    | .narrow => parseMarkerNarrow
    | .twoLetterShort => parseMarkerShort
  | .b format =>
    match format with
    | .short => parseDayPeriodShort
    | .full => parseDayPeriodLong
    | .narrow => parseDayPeriodNarrow
    | .twoLetterShort => parseDayPeriodShort
  | .B format =>
    match format with
    | .short | .full | .twoLetterShort => parseExtendedDayPeriodShort
    | .narrow => parseExtendedDayPeriodNarrow
  | .h format => parseNatToBounded (parseFlexibleNum format.padding)
  | .K format => parseNatToBounded (parseFlexibleNum format.padding)
  | .k format => parseNatToBounded (parseFlexibleNum format.padding)
  | .H format => parseNatToBounded (parseFlexibleNum format.padding)
  | .m format => parseNatToBounded (parseFlexibleNum format.padding)
  | .s format =>
    if config.allowLeapSeconds then
      parseNatToBounded (parseFlexibleNum format.padding)
    else do
      let res : Bounded.LE 0 59 ← parseNatToBounded (parseFlexibleNum format.padding)
      return res.expandTop (by decide)
  | .S format =>
    match format with
    | .nano => parseNatToBounded (parseFlexibleNum 9)
    | .truncated n => parseNatToBounded (parseFractionNum n 9)
  | .A format => Millisecond.Offset.ofNat <$> (parseFlexibleNum format.padding)
  | .n format => parseNatToBounded (parseFlexibleNum format.padding)
  | .N format => Nanosecond.Offset.ofNat <$> (parseFlexibleNum format.padding)
  | .V .unknown => pstring "unk" *> pure "unk"
  | .V .short | .V .full => parseIdentifier
  | .z format =>
    match format with
    | .short => parseIdentifier
    | .full => parseIdentifier
  | .v format =>
    match format with
    | .short => parseIdentifier
    | .full => parseIdentifier
  | .O format =>
    match format with
    | .short => parseLocalizedGMT false
    | .full => parseLocalizedGMT true
  | .X format =>
    let p : Parser Offset :=
      match format with
        | .hour => parseOffset .optional .no false
        | .hourMinute => parseOffset .yes .no false
        | .hourMinuteColon => parseOffset .yes .no true
        | .hourMinuteSecond => parseOffset .yes .optional false
        | .hourMinuteSecondColon => parseOffset .yes .optional true
    p <|> (pstring "Z" *> pure (Offset.ofSeconds 0))
  | .x format =>
    match format with
    | .hour =>
      parseOffset .optional .no false
    | .hourMinute =>
      parseOffset .yes .no false
    | .hourMinuteColon =>
      parseOffset .yes .no true
    | .hourMinuteSecond =>
      parseOffset .yes .optional false
    | .hourMinuteSecondColon =>
      parseOffset .yes .optional true
  | .Z format =>
    match format with
    | .hourMinute =>
      parseOffset .yes .optional false
    | .full =>
      parseLocalizedGMT true
    | .hourMinuteSecondColon =>
      (skipString "Z" *> pure Offset.zero)
      <|> (parseOffset .yes .optional true)

private def formatPartWithDate (date : DateTime tz) (part : FormatPart) : String :=
  match part with
  | .modifier mod => formatWith mod (dateFromModifier date)
  | .string s => s

set_option linter.missingDocs false in  -- TODO
@[simp, expose /- for codegen -/]
def FormatType (result : Type) : FormatString → Type
  | .modifier entry :: xs => (TypeFormat entry) → (FormatType result xs)
  | .string _ :: xs => (FormatType result xs)
  | [] => result

namespace Format

private structure DateBuilder where
  G : Option Year.Era := none
  y : Option Year.Offset := none
  Y : Option Year.Offset := none
  u : Option Year.Offset := none
  D : Option (Sigma Day.Ordinal.OfYear) := none
  month : Option Month.Ordinal := none
  d : Option Day.Ordinal := none
  quarter : Option Month.Quarter := none
  w : Option Week.Ordinal := none
  W : Option (Bounded.LE 1 6) := none
  E : Option Weekday := none
  weekday : Option Weekday := none
  F : Option (Bounded.LE 1 5) := none
  a : Option HourMarker := none
  b : Option DayPeriod := none
  B : Option ExtendedDayPeriod := none
  h : Option (Bounded.LE 1 12) := none
  K : Option (Bounded.LE 0 11) := none
  k : Option (Bounded.LE 1 24) := none
  H : Option Hour.Ordinal := none
  m : Option Minute.Ordinal := none
  s : Option (Second.Ordinal true) := none
  S : Option Nanosecond.Ordinal := none
  A : Option Millisecond.Offset := none
  n : Option Nanosecond.Ordinal := none
  N : Option Nanosecond.Offset := none
  V : Option String := none
  z : Option String := none
  zabbrev : Option String := none
  v : Option String := none
  vabbrev : Option String := none
  O : Option Offset := none
  X : Option Offset := none
  x : Option Offset := none
  Z : Option Offset := none

namespace DateBuilder

private def insert (date : DateBuilder) (modifier : Modifier) (data : TypeFormat modifier) : DateBuilder :=
  match modifier with
  | .G _ => { date with G := some data }
  | .y _ => { date with y := some data }
  | .Y _ => { date with Y := some data }
  | .u _ => { date with u := some data }
  | .D _ => { date with D := some data }
  | .M _ => { date with month := some data }
  | .L _ => { date with month := some data }
  | .d _ => { date with d := some data }
  | .Q _ => { date with quarter := some data }
  | .q _ => { date with quarter := some data }
  | .w _ => { date with w := some data }
  | .W _ => { date with W := some data }
  | .E _ => { date with E := some data }
  | .e _ => { date with weekday := some data }
  | .c _ => { date with weekday := some data }
  | .F _ => { date with F := some data }
  | .a _ => { date with a := some data }
  | .b _ => { date with b := some data }
  | .B _ => { date with B := some data }
  | .h _ => { date with h := some data }
  | .K _ => { date with K := some data }
  | .k _ => { date with k := some data }
  | .H _ => { date with H := some data }
  | .m _ => { date with m := some data }
  | .s _ => { date with s := some data }
  | .S _ => { date with S := some data }
  | .A _ => { date with A := some data }
  | .n _ => { date with n := some data }
  | .N _ => { date with N := some data }
  | .V _ => { date with V := some data }
  | .z .full => { date with z := some data }
  | .z .short => { date with zabbrev := some data }
  | .v .full => { date with v := some data }
  | .v .short => { date with vabbrev := some data }
  | .O _ => { date with O := some data }
  | .X _ => { date with X := some data }
  | .x _ => { date with x := some data }
  | .Z _ => { date with Z := some data }

private def convertYearAndEra (year : Year.Offset) : Year.Era → Year.Offset
  | .ce => year
  | .bce => 1 - year

private def build (builder : DateBuilder) (aw : Awareness) : Except String aw.type := do
  let offset := builder.O <|> builder.X <|> builder.x <|> builder.Z |>.getD Offset.zero

  let tz : TimeZone := {
    offset,
    name := builder.V <|> builder.z <|> builder.v |>.getD (offset.toIsoString true),
    abbreviation := builder.zabbrev <|> builder.vabbrev |>.getD (offset.toIsoString true),
    isDST := false,
  }

  let era := (builder.G.getD .ce)

  let year
    := builder.u
    <|> builder.Y
    <|> ((convertYearAndEra · era) <$> builder.y)
    |>.getD 0

  let monthDay : Month.Ordinal × Day.Ordinal ←
    match builder.D with
    | none => pure (builder.month |>.getD ⟨1, by decide⟩, builder.d |>.getD ⟨1, by decide⟩)
    | some ⟨_, doy⟩ =>
      let v := doy.val
      if h : v ≤ .ofNat (if year.isLeap then 366 else 365) then
        let doy' : Day.Ordinal.OfYear year.isLeap := ⟨v, doy.property.1, h⟩
        let date := PlainDate.ofYearOrdinal year doy'
        pure (date.month, date.day)
      else
        throw s!"day {v} does not exist in year {year}"
  let month := monthDay.1
  let day := monthDay.2

  let hour : Option (Bounded.LE 0 23) :=
    if let some period := builder.b then
      match period with
      | .noon => some ⟨12, by decide⟩
      | .midnight => some ⟨0, by decide⟩
      | .am => (HourMarker.am.toAbsolute <$> builder.h : Option (Bounded.LE 0 23))
               <|> builder.K.map (·.expandTop (by decide))
      | .pm => (HourMarker.pm.toAbsolute <$> builder.h : Option (Bounded.LE 0 23))
               <|> builder.K.map (fun k => (k.add 12).expand (by decide) (by decide))
    else if let some period := builder.B then
      match period with
      | .midnight => some ⟨0, by decide⟩
      | .noon => some ⟨12, by decide⟩
      | .morning | .night =>
        (HourMarker.am.toAbsolute <$> builder.h : Option (Bounded.LE 0 23))
        <|> builder.K.map (·.expandTop (by decide))
      | .afternoon | .evening =>
        (HourMarker.pm.toAbsolute <$> builder.h : Option (Bounded.LE 0 23))
        <|> builder.K.map (fun k => (k.add 12).expand (by decide) (by decide))
    else if let some marker := builder.a then
      (marker.toAbsolute <$> builder.h : Option (Bounded.LE 0 23))
      <|> match marker with
          | .am => builder.K.map (·.expandTop (by decide))
          | .pm => builder.K.map (fun k => (k.add 12).expand (by decide) (by decide))
    else
      none

  let hour :=
    hour <|> (
      let one : Option (Bounded.LE 0 23) := builder.H
      let other : Option (Bounded.LE 0 23) := builder.k.map (·.emod 24 (by decide))
      (one <|> other))
      |>.getD ⟨0, by decide⟩

  let minute := builder.m |>.getD 0
  let second := builder.s |>.getD 0
  let nano := (builder.n <|> builder.S) |>.getD 0

  let time
    :=  PlainTime.ofNanoseconds <$> builder.N
    <|> PlainTime.ofMilliseconds <$> builder.A
    |>.getD (PlainTime.mk hour minute second nano)

  let datetime : Option PlainDateTime :=
    if valid : year.Valid month day then
      let date : PlainDate := { year, month, day, valid }
      some { date, time }
    else
      none

  match (match aw with
    | .only newTz => (ofPlainDateTime · newTz) <$> datetime
    | .any => (ZonedDateTime.ofPlainDateTime · (ZoneRules.ofTimeZone tz)) <$> datetime) with
  | some res => .ok res
  | none => .error "could not parse the date"

end DateBuilder

private def parseWithDate (date : DateBuilder) (config : FormatConfig) (mod : FormatPart) : Parser DateBuilder := do
  match mod with
  | .modifier s => do
    let res ← parseWith config s
    return date.insert s res
  | .string s => pstring s *> pure date

/--
Constructs a new `Format` specification for a date-time string. Modifiers can be combined to create
custom formats, such as "YYYY, MMMM, D".
-/
def spec (input : String) (config : FormatConfig := {}) : Except String (Format tz) := do
  let string ← specParser.run input
  return ⟨config, string⟩

/--
Builds a `Format` from the input string. If parsing fails, it will panic
-/
def spec! (input : String) (config : FormatConfig := {}) : Format tz :=
  match specParser.run input with
  | .ok res => ⟨config, res⟩
  | .error res => panic! res

/--
Type class for types that can be formatted as a `DateTime`.
-/
class FormattableTime (α : Type) where

  /--
  Converts a type `α` to a `DateTime` and a `TimeZone`.
  -/
  toDateTime : α → Σ tz, DateTime tz

instance : FormattableTime (DateTime tz) where
  toDateTime dt := ⟨tz, dt⟩

instance : FormattableTime ZonedDateTime where
  toDateTime dt := ⟨dt.timezone, dt.toDateTime⟩

instance : FormattableTime (Awareness.any.type) where
  toDateTime dt := ⟨dt.timezone, dt.toDateTime⟩

instance : FormattableTime (Awareness.only tz |>.type) where
  toDateTime dt := ⟨tz, by simp at dt; exact dt⟩
/--
Formats a `DateTime` value into a string using the given `Format`.
-/
def format [FormattableTime t] (format : Format aw) (date : t) : String :=
  let ⟨_, date⟩ := FormattableTime.toDateTime date

  let mapper (part : FormatPart) :=
    match aw with
    | .any => formatPartWithDate date part
    | .only tz => formatPartWithDate (date.convertTimeZone tz) part

  format.string.map mapper
  |> String.join

private def parser (format : FormatString) (config : FormatConfig) (aw : Awareness) : Parser (aw.type) :=
  let rec go (builder : DateBuilder) (x : FormatString) : Parser aw.type :=
    match x with
    | x :: xs => parseWithDate builder config x >>= (go · xs)
    | [] =>
      match builder.build aw with
      | .ok res => pure res
      | .error msg => fail msg
  go {} format

/--
Parser for a format with a builder.
-/
def builderParser (format: FormatString) (config : FormatConfig) (func: FormatType (Option α) format) : Parser α :=
  let rec go (format : FormatString) (func: FormatType (Option α) format) : Parser α :=
    match format with
    | .modifier x :: xs => do
      let res ← parseWith config x
      go xs (func res)
    | .string s :: xs => skipString s *> (go xs func)
    | [] =>
        match func with
        | some res => eof *> pure res
        | none => fail "invalid date."
  go format func

/--
Returns `true` if this format contains a timezone-offset specifier (`O`, `X`, `x`, or `Z`).
-/
def hasOffsetSpecifier (format : Format aw) : Bool :=
  format.string.any fun
    | .modifier (.O _) | .modifier (.X _) | .modifier (.x _) | .modifier (.Z _) => true
    | _ => false

/--
Returns `true` if this format contains a timezone-identifier specifier (`V` or `z`).
-/
def hasIdentifierSpecifier (format : Format aw) : Bool :=
  format.string.any fun
    | .modifier (.V _) | .modifier (.z _) | .modifier (.v _) => true
    | _ => false

/--
Parses the input string without checking for identifier-without-offset.
Use this only when you will subsequently resolve the identifier via a timezone database lookup.
For normal parsing, prefer `parse`.
-/
def parseUnchecked (format : Format aw) (input : String) : Except String aw.type :=
  (parser format.string format.config aw <* eof).run input

/--
Parses the input string into a `ZonedDateTime`.
Fails if the format contains a timezone identifier specifier (`z`/`V`) but no offset specifier
(`Z`/`X`/`x`/`O`): such formats cannot produce a correct UTC offset without a timezone database
lookup. Use `parseIO` (on `Format`) or `ZonedDateTime.parseIO` for that case.
-/
def parse (format : Format aw) (input : String) : Except String aw.type :=
  if format.hasIdentifierSpecifier && !format.hasOffsetSpecifier then
    .error "this format uses a timezone identifier without an offset specifier; \
            the correct UTC offset requires a timezone database lookup — use parseIO instead"
  else
    (parser format.string format.config aw <* eof).run input

/--
Parses the input string into a `ZoneDateTime` and panics if its wrong.
-/
def parse! (format : Format aw) (input : String) : aw.type :=
  match parse format input with
  | .ok res => res
  | .error err => panic! err

/--
Parses an input string using a builder function to produce a value.
-/
def parseBuilder (format : Format aw)  (builder : FormatType (Option α) format.string) (input : String) : Except String α :=
  (builderParser format.string format.config builder).run input

/--
Parses an input string using a builder function, panicking on errors.
-/
def parseBuilder! [Inhabited α] (format : Format aw)  (builder : FormatType (Option α) format.string) (input : String) : α :=
  match parseBuilder format builder input with
  | .ok res => res
  | .error err => panic! err

/--
Formats the date using the format into a String, using a `getInfo` function to get the information needed to build the `String`.
-/
def formatGeneric (format : Format aw) (getInfo : (typ : Modifier) → Option (TypeFormat typ)) : Option String :=
  let rec go (data : String) : (format : FormatString) → Option String
    | .modifier x :: xs => do go (data ++ formatWith x (← getInfo x)) xs
    | .string x :: xs => go (data ++ x) xs
    | [] => some data
  go "" format.string

/--
Constructs a `FormatType` function to format a date into a string using a `Format`.
-/
def formatBuilder (format : Format aw) : FormatType String format.string :=
  let rec go (data : String) : (format : FormatString) → FormatType String format
    | .modifier x :: xs => fun res => go (data ++ formatWith x res) xs
    | .string x :: xs => go (data ++ x) xs
    | [] => data
  go "" format.string

end Format

/--
A `MultiFormat` holds a list of `Format` alternatives tried in order when parsing.
Use it when a value can be represented in several equivalent formats.
-/
structure MultiFormat (awareness : Awareness) where
  /--
  The list of format alternatives, tried left-to-right.
  -/
  formats : { x : Array (Format awareness) // x.size > 0 }
  deriving Repr

instance : Inhabited (MultiFormat aw) where
  default := ⟨⟨#[default], by simp⟩⟩

namespace MultiFormat

/--
?
-/
def new (formats : Array (Format aw)) (proof : formats.size > 0 := by simp) : MultiFormat aw :=
  ⟨⟨formats, proof⟩⟩

/--
Parses the input string by trying each format in order, returning the first success.
-/
def parse (mf : MultiFormat aw) (input : String) : Except String aw.type :=
  mf.formats.val.foldl (init := .error s!"no format matched input: {input}")
    fun acc fmt => acc <|> fmt.parse input

/--
Parses the input string without timezone awareness checks, trying each format in order.
-/
def parseUnchecked (mf : MultiFormat aw) (input : String) : Except String aw.type :=
  mf.formats.val.foldl (init := .error s!"no format matched input: {input}")
    fun acc fmt => acc <|> fmt.parseUnchecked input

/--
Formats a date using the first format in the list.
-/
def format (mf : MultiFormat aw) (date : DateTime tz) : String :=
  let fmt := mf.formats.val[0]'(mf.formats.property)
  fmt.format date

end MultiFormat
end Time
end Std
