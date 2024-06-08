PROG test1.

VAR
END_VAR

EXEC
/* for parser ok, but semantically not correct */
a = a + (b * c) + " as " + ds - ----d / 10 * (32.0000002323 / a + v).

a = " dsa da d" * dsa - asdas / "dsasdds".

if a == v && b >= a || ~ a == 2 && (l ~= "aaaa") then
endif

a = 0.1012.

END_EXEC
