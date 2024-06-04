PROG ggt.

VAR
    ?!int a.
    ?int b.
END_VAR

EXEC
    if (a == 0) then
        a = b.
    else
        while (b ~= 0) do
            if (a > b) then
                a = (a - b).
            else
                b = (b - a).
            endif
        endwhile
    endif
END_EXEC
