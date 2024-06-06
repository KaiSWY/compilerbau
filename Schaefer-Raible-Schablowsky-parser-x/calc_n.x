PROG calcN

VAR
    	!int result.
	?int n.
END_VAR

EXEC
    /* calc sum of n value */   
    for count = 0 . count < n . count += 1 do
        result += (n + 1).
    endfor

    /* alternative rechnng */
    for count = 1 . count <= n . count += 1 do
	result += n.
    end_for
END_EXEC
