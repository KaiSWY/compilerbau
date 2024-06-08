PROG faculty.

VAR
    ?int i.
    !int fac.
END_VAR

EXEC
    fac = 1.
    while (i > 0) do
        fac *= i.
        i -= 1.
    endwhile
END_EXEC
