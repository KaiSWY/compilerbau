PROG calcN.

VAR
	!int result.
	?int n.
END_VAR

EXEC
    /* calc sum of n value */   
    for result = 0 . n > 0 . n -= 1 do
        result += n.
    endfor
END_EXEC
