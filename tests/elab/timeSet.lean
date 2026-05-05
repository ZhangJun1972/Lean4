import Std.Time
open Std.Time

def ISO8601UTC : Format Awareness.any := datespec("uuuu-MM-dd'T'HH:mm:ss.SSSSSSSSSXXX")
def RFC1123 : Format Awareness.any := datespec("eee, dd MMM uuuu HH:mm:ss ZZZ")
def ShortDate : Format Awareness.any := datespec("MM/dd/uuuu")
def LongDate : Format Awareness.any := datespec("MMMM D, uuuu")
def ShortDateTime : Format Awareness.any := datespec("MM/dd/uuuu HH:mm:ss")
def LongDateTime : Format Awareness.any := datespec("MMMM dd, uuuu hh:mm a")
def Time24Hour : Format Awareness.any := datespec("HH:mm:ss")
def Time12Hour : Format Awareness.any := datespec("hh:mm:ss a")
def FullDayTimeZone : Format Awareness.any := datespec("EEEE, MMMM dd, uuuu HH:mm:ss ZZZ")
def CustomDayTime : Format Awareness.any := datespec("EEE dd MMM uuuu HH:mm")

def Full12HourWrong : Format Awareness.any := datespec("MM/dd/uuuu hh:mm:ss a XXX")

-- Dates

def brTZ : TimeZone := timezone("America/Sao_Paulo -03:00")
def jpTZ : TimeZone := timezone("Asia/Tokyo +09:00")

def date₁ := zoned("2014-06-16T10:03:03-03:00")

def time₁ := time("14:11:01")
def time₂ := time("03:11:01")

/--
info: "2014-06-16T10:03:03.000000100-03:00"
-/
#guard_msgs in
#eval
    let t : ZonedDateTime := ISO8601UTC.parse! "2014-06-16T10:03:03.000000100-03:00"
    ISO8601UTC.format t.toDateTime

/--
info: zoned("2014-06-30T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withDaysClip 31

/--
info: zoned("2014-07-01T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withDaysRollOver 31

/--
info: zoned("2014-05-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withMonthClip 5

/--
info: zoned("2014-05-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withMonthRollOver 5

/--
info: zoned("2016-06-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withYearClip 2016

/--
info: zoned("2016-06-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withYearRollOver 2016

/--
info: zoned("2014-06-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withDaysClip 16

/--
info: zoned("2014-06-16T10:45:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withMinutes 45


/--
info: zoned("2014-06-16T10:03:03.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withHours 10

/--
info: zoned("2014-06-16T10:03:59.000000000-03:00")
-/
#guard_msgs in
#eval date₁.withSeconds 59

/--
info: zoned("2014-06-16T10:03:03.000000002-03:00")
-/
#guard_msgs in
#eval date₁.withNanoseconds 2
